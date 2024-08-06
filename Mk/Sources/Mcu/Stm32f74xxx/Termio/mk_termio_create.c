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
* @date 23 juil. 2019
*
*/

#include "mk_termio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_termio_launch ( T_mkTermio* p_termio, T_mkTaskCtrlBlock* p_taskCtrlBlock, uint32_t* p_stackAddr, uint32_t p_stackSize, T_mkAddress p_function, T_mkAddr p_arg )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Si le terminal peut être lancée */
   if ( p_termio->task == K_MK_NULL )
   {
      /* Ecriture d'un pattern dans la stack du terminal */
      _writeWords ( p_stackAddr, K_MK_TASK_STACK_PATTERN, p_stackSize );

      /* Initialisation de la stack du terminal */
      l_result = mk_stack_create ( &p_termio->stack, K_MK_TYPE_DEFAULT, p_stackAddr, p_stackSize );

      /* Si l'initialisation de la stack à réussie */
      if ( l_result == K_MK_OK )
      {
         /* Création de la tâche du terminal */
         l_result = mk_task_create ( &p_termio->task, &p_termio->stack, K_MK_NULL, p_taskCtrlBlock, p_function, p_arg );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_termio_create ( T_mkTermio** p_termio, uint32_t p_identifier, uint32_t p_priority, T_mkAddress p_function, uint32_t* p_stackAddr, uint32_t p_stackSize )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de terminal */
   T_mkTermio* l_termio;

   /* Déclaration d'un registre de contrôle */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Déclaration des variables de travail */
   uint32_t l_isr, l_right;

   /* Récupération du statut d'interruption */
   l_isr = mk_scheduler_isr ( );

   /* Si la fonction n'est pas exécutée dans un vecteur d'interruption */
   if ( l_isr == K_MK_ISR_NO )
   {
      /* Récupération du niveau d'exécution de la tâche courante */
      l_right = _mk_scheduler_privileged ( );

      /* Si les droits sont suffisants pour exécuter cette fonction */
      if ( l_right != K_MK_MODE_THREAD )
      {
         /* Allocation d'un terminal */
         l_termio = ( T_mkTermio* ) mk_pool_alloc ( g_mkTermioArea.pool, K_MK_POOL_CLEAR );

         /* Si l'allocation a réussi */
         if ( l_termio != K_MK_NULL )
         {
            /* Initialisation de la tâche du terminal */
            l_termio->task = K_MK_NULL;

            /* Référencement du terminal */
            l_result = mk_termio_link ( l_termio, p_identifier );

            /* Si le référencement a réussi */
            if ( l_result == K_MK_OK )
            {
               /* Configuration du registre de contrôle de la nouvelle tâche */
               l_result = mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_PRIVILEGED, p_identifier, p_priority, K_MK_NULL );

               /* Si la configuration du registre de contrôle a réussi */
               if ( l_result == K_MK_OK )
               {
                  /* Initialisation de la tâche du terminal */
                  l_result = mk_termio_launch ( l_termio, &l_taskCtrlBlock, p_stackAddr, p_stackSize, p_function, ( T_mkAddr ) l_termio );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Si la création du terminal a réussi */
               if ( ( l_result == K_MK_OK ) && ( l_termio->task != K_MK_NULL ) )
               {
                  /* Enregistrement de l'adresse du terminal */
                  *p_termio = l_termio;
               }

               /* Sinon */
               else
               {
                  /* Suppression du reférencement */
                  l_result = mk_termio_unlink ( p_identifier );
               }

               /* Si une erreur s'est produite */
               if ( l_result != K_MK_OK )
               {
                  /* Destruction du terminal */
                  l_result |= mk_termio_delete ( l_termio );
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
               /* Libération de la mémoire allouée */
               l_result |= mk_pool_free ( g_mkTermioArea.pool, l_termio );
            }
         }

         /* Sinon */
         else
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_MALLOC;
         }
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_RIGHT;
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_ISR;
   }

   /* Retour */
   return ( l_result );
}

