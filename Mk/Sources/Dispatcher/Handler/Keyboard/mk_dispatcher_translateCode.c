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
* @file mk_dispatcher_translateCode.c
* @brief Définition de la fonction mk_dispatcher_translateCode.
* @date 22 déc. 2019
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint16_t mk_dispatcher_getLookupTableOffset ( T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler )
{
   /* Déclaration de la variable de retour */
   uint16_t l_result = ( uint16_t ) ( ( p_keyboard->specialKey.numlock << 3 ) | ( p_keyboard->specialKey.capslock << 2 ) ) ;

   /* Si les modificateurs 'LSHIFT' ou 'RSHIFT' sont positionné */
   if ( ( p_keyHandler->modifier & K_MK_KEYBOARD_SHIFT ) != 0 )
   {
      /* Actualisation de la variable de retour */
      l_result |= 0x01;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le modificateur 'ALTGR' est positionné */
   if ( ( p_keyHandler->modifier & K_MK_KEYBOARD_RIGHT_ALT ) != 0 )
   {
      /* Actualisation de la variable de retour */
      l_result |= 0x02;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Détermination de l'offset du caractère */
   l_result = ( uint16_t ) ( ( l_result * K_MK_KEYBOARD_SUBTABLE_SIZE ) + ( uint16_t ) ( p_keyHandler->scancode & 0xFF ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_translateCode ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler, T_mkKey* p_key )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint16_t l_keyOffset = 0;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_message != K_MK_NULL ) && ( p_keyboard != K_MK_NULL ) && ( p_keyHandler != K_MK_NULL ) && ( p_key != K_MK_NULL ) )
   {
      /* Enregistrement du code caractère en utilisant le format d'une commande */
      p_keyHandler->scancode = ( uint16_t ) ( ( p_keyHandler->modifier << 8 ) | ( p_keyHandler->scancode ) ) ;

      /* Si au maximum un modificateur est sélectionné */
      if ( p_keyHandler->cmd == 0 )
      {
         /* Dans ce bloc l'algorithme ne sait toujours pas si la saisie de l'utilisateur est une commande ou un caractère affichable. */
         /* Il est nécessaire d'analyser le code caractère avec le contenu de la table de correspondance. */

         /* Détermination de l'offset du code affichable dans la table de correspondance générique */
         l_keyOffset = mk_dispatcher_getLookupTableOffset ( p_keyboard, p_keyHandler );

         /* Si le caractère est un caractère de type affichable */
         if ( g_mkHidLookupTable [ l_keyOffset ] != 0 )
         {
            /* Récupération de l'offset du code affichable dans la table de correspondance du clavier */
            l_keyOffset = ( uint8_t ) ( g_mkHidLookupTable [ l_keyOffset ] );

            /* Actualisation de la structure de sortie */
            p_key->key.scancode = ( uint16_t ) p_keyHandler->scancode;

            /* Si la table de correspondance est valide */
            if ( p_keyboard->lookup != K_MK_NULL )
            {
               /* Conversion du code caractère en UTF */
               p_key->key.ascii = ( uint8_t ) ( p_keyboard->lookup [ l_keyOffset ] & 0xFF );
               p_key->key.utf8  = mk_utils_codeToUtf8  ( p_keyboard->lookup [ l_keyOffset ] );
               p_key->key.utf16 = mk_utils_codeToUtf16 ( p_keyboard->lookup [ l_keyOffset ] );
               p_key->key.utf32 = mk_utils_codeToUtf32 ( p_keyboard->lookup [ l_keyOffset ] );
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
            /* Il est nécessaire d'actualiser la valeur du champ commande pour que l'algorithme sélectionne le bon type de message. */
            /* Actualisation de la variable indiquant à l'algorithme la présence d'une commande. */
            p_keyHandler->cmd = 1;
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}



