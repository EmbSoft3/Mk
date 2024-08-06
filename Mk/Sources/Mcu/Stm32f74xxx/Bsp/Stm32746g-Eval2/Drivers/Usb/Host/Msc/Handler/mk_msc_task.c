/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
*
* This file is part of Mk.
*
* Mk is free software. Redistribution and use in source and binary forms, with or
* without modification, are permitted provided that the following conditions are
* met:
*
*    1. Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*    2. Redistributions in binary form must reproduce the above copyright notice,
*       this list of conditions and the following disclaimer in the documentation
*       and/or other materials provided with the distribution.
*    3. Neither the name of the copyright holder nor the names of its contributors
*       may be used to endorse or promote products derived from this software
*       without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @file mk_msc_task.c
* @brief Définition de la fonction mk_msc_task.
* @date 16 mai 2020
*
* @todo Désallouer la mémoire lors de la destruction du terminal.
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_initMSCHandler ( T_mkTermio* p_termio, T_mkMSCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Réinitialisation du gestionnaire MSC */
   _writeWords ( p_handler, 0, sizeof ( T_mkMSCHandler ) >> 2 );

   /* Configuration de la structure de données du terminal */
   l_result = mk_termio_setChild ( p_termio, ( T_mkMSCHandler* ) p_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire MSC */
      l_result = mk_msc_initHandler ( p_handler );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Affichage d'un message dans la console du superviseur pour indiquer */
      /* que l'initialisation a réussi. */
      l_result = mk_termio_log ( ( T_str8 ) "[MSC] ready;\n" );
   }

   /* Sinon */
   else
   {
      /* Affichage d'un message dans la console du superviseur pour indiquer */
      /* que l'initialisation a échoué. */
      l_result = mk_termio_log ( ( T_str8 ) "[MSC] failed;\n" );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_msc_task ( T_mkAddr p_param )
{
   /* Déclaration d'un gestionnaire de périphériques MSC */
   T_mkMSCHandler l_handler;

   /* Déclaration d'un message MSC */
   T_mkHCDMessage l_message = { 0, 0 };

   /* Initialisation du gestionnaire MSC */
   T_mkCode l_result = mk_msc_initMSCHandler ( ( T_mkTermio* ) p_param, &l_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Tant qu'aucune erreur critique ne s'est produite */
      while ( ( l_result & ( T_mkCode ) ( ~ ( K_MK_ERROR_TIMEOUT | K_MK_ERROR_COMM ) ) ) == K_MK_OK )
      {
         /* Analyse de la boite de messages pour savoir si le gestionnaire USB a transmis l'adresse */
         /* d'un nouveau périphérique MSC */
         l_result = mk_mail_pend ( K_MK_NULL, l_handler.messageArea->mail, ( T_mkAddr ) &l_message, K_MK_MSC_REFRESH_TIMEOUT );

         /* Si un nouveau périphérique MSC vient d'être connecté */
         if ( l_result == K_MK_OK )
         {
            /* Création d'un nouveau périphérique */
            l_result = mk_msc_createDevice ( &l_handler, l_message.device, l_message.interface );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Lancement de la séquence d'actualisation des périphériques MSC et gestion des requêtes utilisateurs */
         l_result |= mk_msc_handle ( &l_handler );

         /* Attente 10 ms */
         /* La fonction 'delay' est utilisée pour moduler la durée d'attente en fonction */
         /* de la durée d'attente de la requête */
         /*l_result |= mk_task_delay ( K_MK_MSC_REFRESH_TIMEOUT );*/
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
      /* Le gestionnaire MSC n'a pas été initialisé. */
   }

   /* Le résultat de la fonction n'est pas vérifié car l'intégrité du système n'est plus garantie. */
   /* Une erreur grave vient de se produire */
   /* La destruction du terminal est de la responsabilité du superviseur. */
   ( void ) mk_termio_report ( l_result );

   /* Blocage */
   while ( 1 );

   /* Retour */
   return;
}

