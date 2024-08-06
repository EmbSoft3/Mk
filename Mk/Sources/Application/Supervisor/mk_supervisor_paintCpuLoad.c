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
* @file mk_supervisor_paintCpuLoad.c
* @brief Définition de la fonction mk_supervisor_paintCpuLoad.
* @date 5 nov. 2023
*
*/

#include "mk_supervisor_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_supervisor_paintCpuLoad ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_idleLoad = 0;

   /* Déclaration d'un vecteur de travail */
   T_mkVect2D l_bottomRight = { 0, 0 };

   /* Récupération de la charge CPU de la tâche de repos */
   l_result = mk_task_getLoad ( mk_scheduler_getIdleTask ( ), &l_idleLoad );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Conversion de la charge CPU de la tâche de repos en chaine de caractères */
      ( void ) mk_utils_itoa ( 100 - l_idleLoad, ( T_str8 ) g_mkSupervisor.load.cpuBuffer, 10, 0 );

      /* Configuration de la position de la figure */
      mk_vect2d_setCoord ( &l_bottomRight, p_field->position.x + ( real32_t ) p_field->dimension.width - 1,
                           p_field->position.y + ( real32_t ) p_field->dimension.height - 1 );

      /* Si le framerate doit être affiché sur le premier plan */
      if ( g_mkSupervisor.load.foregroundEnabled == K_MK_TRUE )
      {
         /* Affichage de la charge CPU sur le premier plan */
         l_result = mk_graphics_drawString ( K_MK_GRAPHICS_FOREGROUND, p_field->position, l_bottomRight,
                                             ( T_str8 ) g_mkSupervisor.load.cpuBuffer, &g_mkSupervisor.load.style, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si le framerate doit être affiché sur le premier plan */
         if ( g_mkSupervisor.load.backgroundEnabled == K_MK_TRUE )
         {
            /* Affichage de la charge CPU sur l'arrière plan */
            l_result = mk_graphics_drawString ( K_MK_GRAPHICS_BACKGROUND, p_field->position, l_bottomRight,
                                                ( T_str8 ) g_mkSupervisor.load.cpuBuffer, &g_mkSupervisor.load.style, K_MK_NULL );
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

   /* Suppression warnings */
   ( void ) p_frameNumber; ( void ) p_container;

   /* Retour */
   return ( l_result);
}



