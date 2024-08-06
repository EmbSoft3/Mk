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
* @file mk_hid_keyboard_setCountryCode.c
* @brief Définition de la fonction mk_hid_keyboard_setCountryCode.
* @date 19 déc. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_keyboard_setCountryCode ( T_mkKeyboard* p_keyboard, uint16_t p_countryCode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le paramètre est valide */
   if ( p_keyboard != K_MK_NULL )
   {
      /* Configuration du type du clavier */
      p_keyboard->layer.countryCode = ( uint16_t ) p_countryCode;

      /* Si le clavier est français */
      if ( p_countryCode == K_MK_HID_COUNTRY_FRENCH )
      {
         /* Pré-configuration du type du clavier en fonction du pays d'origine */
         p_keyboard->layer.lang = K_MK_KEYBOARD_AZERTY_FR;

         /* Configuration de la table de correspondance */
         p_keyboard->lookup = ( T_mkKeyboardLookup ) g_mkHidFrExtendedAzertyLookupTable;
      }

      /* Sinon si le code du pays est non renseigné */
      else if ( p_countryCode == K_MK_HID_COUNTRY_NOT_SUPPORTED )
      {
         /* Pré-configuration du type du clavier en fonction du pays d'origine */
         p_keyboard->layer.lang = K_MK_KEYBOARD_AZERTY_FR;

         /* Configuration de la table de correspondance */
         p_keyboard->lookup = ( T_mkKeyboardLookup )  g_mkHidFrExtendedAzertyLookupTable;
      }

      /* Sinon */
      else
      {
         /* Actualisation du type du clavier */
         p_keyboard->layer.lang = K_MK_KEYBOARD_QWERTY_US;

         /* Configuration de la table de correspondance */
         p_keyboard->lookup = K_MK_NULL;
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


