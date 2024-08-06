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
* @file mk_termio_delete.c
* @brief Définition de la fonction mk_termio_delete.
* @date 22 juil. 2019
*
*/

#include "mk_termio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_termio_delete ( T_mkTermio* p_termio )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'une tâche */
   T_mkTask* l_task;

   /* Déclaration d'une variable stockant le masque d'interruption */
   uint32_t l_mask;

   /* Déclaration des variables de travail */
   uint32_t l_isr, l_right;

   /* Si le paramètre est valide */
   if ( p_termio != K_MK_NULL )
   {
      /* Récupération du statut d'interruption */
      l_isr = mk_scheduler_isr ( );

      /* Si la fonction n'est pas exécutée depuis un vecteur d'interruption */
      if ( l_isr == K_MK_ISR_NO )
      {
         /* Récupération du niveau d'exécution de la tâche courante */
         l_right = _mk_scheduler_privileged ( );

         /* Si les droits sont suffisants pour exécuter cette fonction */
         if ( l_right != K_MK_MODE_THREAD )
         {
            /* Récupération de l'adresse de la tâche du terminal */
            l_task = p_termio->task;

            /* Entrée en section critique */
            /* Il n'est pas nécessaire de récupérer la valeur du masque car cette fonction ne peut pas être */
            /* exécutée dans un vecteur d'interruption. */
            l_mask = _mk_scheduler_mask ( K_MK_SCHEDULER_MASK_PRIORITY );

            /* Réinitialisation de l'attribut 'Child' */
            p_termio->child = K_MK_NULL;

            /* Suppression de la mémoire attribuée au terminal */
            l_result = mk_pool_free ( g_mkTermioArea.pool, ( T_mkAddr ) p_termio );

            /* Si la suppression de la mémoire a réussi */
            if ( l_result == K_MK_OK )
            {
               /* Suppression de la tâche */
               l_result = mk_task_terminate ( l_task );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Sortie de la section critique */
            _mk_scheduler_unmask ( l_mask );
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
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


