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
* @file mk_mmc_task.c
* @brief Définition de la fonction mk_mmc_task.
* @date 3 juin 2020
* @todo Libérer la mémoire allouée par le terminal à la destruction de celui-ci.
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_initMMCHandler ( T_mkTermio* p_termio, T_mkMMCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Réinitialisation du gestionnaire MMC */
   _writeWords ( p_handler, 0, sizeof ( T_mkMMCHandler ) >> 2 );

   /* Configuration de la structure de données du terminal */
   l_result = mk_termio_setChild ( p_termio, ( T_mkMMCHandler* ) p_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire MMC */
      l_result = mk_mmc_initHandler ( p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Ouverture du pipe de communication */
         l_result = mk_mmc_openPipe ( p_handler );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Initialisation des broches GPIO du périphérique matériel */
            mk_mmc_initGPIO ( );

            /* Initialisation du périphérique matériel */
            mk_mmc_init ( );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
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
      l_result = mk_termio_log ( ( T_str8 ) "[MMC] ready;\n" );
   }

   /* Sinon */
   else
   {
      /* Affichage d'un message dans la console du superviseur pour indiquer */
      /* que l'initialisation a échoué. */
      l_result = mk_termio_log ( ( T_str8 ) "[MMC] failed;\n" );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_mmc_task ( T_mkAddr p_param )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un gestionnaire de périphériques MMC */
   T_mkMMCHandler l_handler;

   /* Initialisation du gestionnaire MMC */
   l_result = mk_mmc_initMMCHandler ( ( T_mkTermio* ) p_param, &l_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Boucle tant qu'une erreur critique n'est détectée */
      while ( ( l_result & ( T_mkCode ) ( ~ ( K_MK_ERROR_TIMEOUT | K_MK_ERROR_COMM ) ) ) == K_MK_OK )
      {
         /* Traitement des requêtes utilisateur et initialisation des périphériques MMC */
         /* présents sur le bus */
         l_result = mk_mmc_handle ( &l_handler );

         /* Attente 10 ms (modulo la durée passée à attendre la requête) */
         /*l_result |= mk_task_delay ( K_MK_MMC_REFRESH_TIMEOUT );*/
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
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
