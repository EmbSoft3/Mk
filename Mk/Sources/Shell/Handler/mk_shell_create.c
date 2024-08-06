/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_shell_create.c
* @brief Définition de la fonction mk_shell_create.
* @date 10 mai 2023
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shell_createTaskPool ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Ecriture d'un pattern dans la stack des gestionnaires de commandes */
   _writeWords ( g_mkShellTaskArea.heap, K_MK_TASK_STACK_PATTERN, K_MK_SHELL_NUMBER * K_MK_SHELL_STACK_SIZE );

   /* Initialisation de la zone mémoire dédiées à l'allocation des stacks des gestionnaires de commandes */
   l_result = mk_pool_initArea ( &g_mkShellTaskArea.area, g_mkShellTaskArea.heap, K_MK_SHELL_NUMBER * K_MK_SHELL_STACK_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique des stacks des gestionnaires de commandes */
      l_result = mk_pool_create ( &g_mkShellTaskArea.area, &g_mkShellTaskArea.pool, K_MK_AREA_PROTECTED, K_MK_SHELL_STACK_SIZE, K_MK_SHELL_NUMBER );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shell_initPool ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &g_mkShellMessageArea.area, g_mkShellMessageArea.heap, K_MK_SHELL_INCOMING_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &g_mkShellMessageArea.mail, K_MK_AREA_PROTECTED, &g_mkShellMessageArea.area, K_MK_SHELL_INCOMING_MESSAGE_SIZE, K_MK_SHELL_MESSAGE_NUMBER );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_shell_create ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'un pointeur de tâche */
   T_mkTask* l_task = K_MK_NULL;

   /* Déclaration d'un TCB */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Initialisation du gestionnaire d'allocation dynamique des stacks des gestionnaires de commandes */
   l_result = mk_shell_createTaskPool ( );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la messagerie du gestionnaire de commandes */
      l_result = mk_shell_initPool ( );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Pour le nombre de gestionnaires de commandes à créer */
         for ( l_counter = 0 ; ( l_counter < K_MK_SHELL_NUMBER ) && ( l_result == K_MK_OK ) ; l_counter++ )
         {
            /* Configuration du registre de contrôle de la tâche */
            l_result = mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_PRIVILEGED, K_MK_TASK_ID_SHELL + l_counter, K_MK_SHELL_TASK_PRIORITY, K_MK_NULL );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Création de la tâche d'un gestionnaire de commandes */
               l_result = mk_task_create ( &l_task, K_MK_NULL, g_mkShellTaskArea.pool, &l_taskCtrlBlock, mk_shell, K_MK_NULL );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
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

   /* Retour */
   return ( l_result );
}


