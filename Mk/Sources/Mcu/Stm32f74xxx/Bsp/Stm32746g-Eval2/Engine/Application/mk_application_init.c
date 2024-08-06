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
* @file mk_application_init.c
* @brief Définition de la fonction mk_application_init.
* @date 6 mai 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_application_setIdentifier ( uint16_t* p_identifier, T_mkAddr p_baseAddr, T_mkAddr p_poolAddr, uint32_t p_size )
{
   /* Détermination de l'identifiant unique de l'application */
   *p_identifier = ( uint16_t ) ( K_MK_DISPLAY_APPLICATION_NUMBER - ( ( ( uint32_t ) p_baseAddr - ( uint32_t ) p_poolAddr ) / p_size ) - 1 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_application_setDispatcherAttributes ( T_mkApplication* p_application )
{
   /* Configuration des attributs de l'application à la valeur de défaut */
   p_application->attribute.stickResolution = K_MK_STICK_DEFAULT_RESOLUTION;
   p_application->attribute.pointerResolution = K_MK_POINTER_DEFAULT_RESOLUTION;
   p_application->attribute.mouseCursorLayer = K_MK_GRAPHICS_FOREGROUND;
   p_application->attribute.mouseCursorVisibility = K_MK_FIELD_VISIBLE;
   p_application->attribute.mouseCursorBitmap = K_MK_NULL;
   p_application->attribute.mouseCursorWidth = 0;
   p_application->attribute.mouseCursorHeight = 0;
   p_application->attribute.keyboardHoldRate = K_MK_KEYBOARD_HOLD_RATE;
   p_application->attribute.keyboardInhibitionDuration = K_MK_KEYBOARD_HOLD_INHIBITION_DURATION;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_application_init ( T_mkApplication* p_application, T_mkApplicationDescriptor* p_descriptor, uint32_t p_identifier, uint32_t p_priority )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_application != K_MK_NULL ) && ( p_application->task.addr == K_MK_NULL ) && ( p_descriptor != K_MK_NULL ) )
   {
      /* Copie du descripteur de l'application */
      _copy ( &p_application->descriptor, p_descriptor, sizeof ( T_mkApplicationDescriptor ) );

      /* Configuration de l'identifiant du contrôle */
      p_application->layer.type = K_MK_CONTROL_APPLICATION;

      /* Configuration de l'identifiant unique de l'application */
      mk_application_setIdentifier ( &p_application->layer.id, p_application, g_mkDisplay.handler.applicationArea.buf, sizeof ( T_mkApplication ) );

      /* Configuration de l'identifiant de la tâche */
      p_application->task.identifier = p_identifier;

      /* Configuration de la priorité de la tâche */
      p_application->task.priority = p_priority;

      /* Configuration des attributs de l'application (dispatcher) */
      mk_application_setDispatcherAttributes ( p_application );

      /* Modification de l'état de l'application */
      p_application->state = K_MK_APPLICATION_STATE_INSTALLED;
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


