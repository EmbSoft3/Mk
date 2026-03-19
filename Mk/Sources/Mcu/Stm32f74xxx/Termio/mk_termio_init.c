/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_termio_create.c
* @brief Définition de la fonction mk_termio_create.
* @date 9 juin 2019
*
*/

#include "mk_termio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_termio_initEvent ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation du champ d'événement permettant la synchronisation entre les terminaux et le dispatcher */
   l_result = mk_event_create ( &g_mkTermioSync.event, K_MK_ID_EVENT_SIGNAL, K_MK_AREA_PROTECTED, 0 );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_termio_init ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Initialisation du gestionnaire de référencement des terminaux. */
   mk_termio_initHandler ( );

   /* Initialisation du gestionnaire d'allocation dynamique des terminaux */
   l_result = mk_termio_createHeap ( );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de l'événement permettant la synchronisation des */
      /* terminaux au démarrage. */
      l_result = mk_termio_initEvent ( );

      /* Pour le nombre de terminal à initialiser */
      for ( l_counter = 0; ( l_counter < K_MK_TERMIO_NUMBER ) && ( l_result == K_MK_OK ); l_counter++ )
      {
         /* Si le terminal doit être initialisé */
         if ( g_mkTermioCtrlBlock [ l_counter ].identifier != K_MK_TERMIO_NO )
         {
            /* Création du terminal du système de fichiers partagés */
            l_result |= mk_termio_create ( K_MK_NULL, g_mkTermioCtrlBlock [ l_counter ].identifier, g_mkTermioCtrlBlock [ l_counter ].priority,
               g_mkTermioCtrlBlock [ l_counter ].function, g_mkTermioCtrlBlock [ l_counter ].stackAddr, g_mkTermioCtrlBlock [ l_counter ].stackSize );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }
   }

   /* Retour */
   return ( l_result );
}




