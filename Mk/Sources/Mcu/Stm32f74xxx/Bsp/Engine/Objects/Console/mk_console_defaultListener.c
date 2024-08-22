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
* @file mk_console_defaultListener.c
* @brief Définition de la fonction mk_console_defaultListener.
* @date 13 févr. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_console_defaultListener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'adresse de la boite d'édition */
   T_mkEditField* l_editField = ( T_mkEditField* ) p_mkField->child;

   /* Récupération de l'adresse de la console */
   T_mkConsole* l_console = ( T_mkConsole* ) l_editField->child;

   /* Déclaration d'une variable stockant la longueur de la chaine de caractères du fichier d'entrée */
   uint32_t l_length = 0;

   /* Prise du sémaphore */
   l_result = mk_semaphore_take ( l_console->semaphore, K_MK_TASK_WAIT_FOREVER );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Exécution du listener par défaut */
      l_result = mk_editField_defaultListener ( p_mkContainer, p_mkField, p_mkAppCtrlId, p_mkAppCtrl, p_mkEvtCtrl, p_mkCtrlId );

      /* Libération du sémaphore (sans condition) */
      l_result |= mk_semaphore_release ( l_console->semaphore );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si un événement en relation avec le clavier s'est produit */
      if ( p_mkAppCtrlId == K_MK_CONTROL_KEYBOARD )
      {
         /* Si l'utilisateur appuyé sur la touche entrée */
         if ( ( p_mkField->focus == K_MK_FIELD_STATE_FOCUS ) && ( p_mkEvtCtrl == K_MK_EVENT_KEY_DOWN ) && ( p_mkCtrlId == K_MK_KEYBOARD_ENTER ) )
         {
            /* Récupération de la longueur de la chaine de caractères */
            /* Pas besoin de protection car c'est la chaine de caractères du prompt (accès réalisé uniquement par les listeners) */
            l_length = mk_utils_utfsize ( ( T_str8 ) l_editField->strAddr, l_console->foreground.window.style.fontEncoding );

            /* Si le fichier d'entrée a été ouvert */
            if ( l_console->prompt.file != K_MK_NULL )
            {
               /* Enrgistrement des caractères dans le fichier d'entrée */
               l_result = mk_console_writeFile ( l_console, l_console->prompt.file, l_editField->strAddr, l_length );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Si aucune erreur ne s'est produite et si un echo local doit être réalisé */
            if ( ( l_result == K_MK_OK ) && ( l_console->window.localEcho == K_MK_CONSOLE_LOCALECHO_ENABLED ) )
            {
               /* Affichage d'un message dans la console */
               l_result = mk_console_log ( l_console, l_editField->strAddr );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Réinitialisation de la chaine de caractères du prompt */
            _writeBytes ( l_console->prompt.buf, 0, l_console->prompt.bufSize );
            mk_editField_setTextBuffer ( &l_console->foreground.prompt, l_console->prompt.buf, l_console->prompt.bufSize );
         }

         /* Sinon si des caractères sont en train d'être saisis */
         else if ( ( p_mkField->focus == K_MK_FIELD_STATE_FOCUS ) && ( p_mkEvtCtrl == K_MK_EVENT_CHAR_DOWN ) &&
               ( p_mkField == &l_console->foreground.prompt.field ) )
         {
            /* Déclenchement d'un rafraichissement graphique (prompt) */
            mk_editField_setRefresh ( &l_console->foreground.prompt, K_MK_FIELD_REFRESH_ENABLED );
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

   /* Retour */
   return ( l_result );
}


