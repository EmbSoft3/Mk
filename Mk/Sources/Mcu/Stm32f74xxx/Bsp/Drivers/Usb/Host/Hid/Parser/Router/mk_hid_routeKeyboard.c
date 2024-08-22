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
* @file mk_hid_routeKeyboard.c
* @brief Définition de la fonction mk_hid_routeKeyboard.
* @date 15 déc. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_routeKeyUsageToKeyboard ( T_mkKeyboard* p_keyboard, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_keyNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de touche */
   T_mkKey** l_key;

   /* Déclaration d'un pointeur de bouton */
   T_mkKeyCode** l_keyButton;

   /* Si l'usage est codé au maximum sur 32 bits */
   if ( p_table->global.reportSize <= K_MK_HID_MAX_USAGE_SIZE )
   {
      /* Si l'usage courant est un modificateur */
      if ( ( p_usage->first->value >= K_MK_HID_KEY_PAGE_KEYBOARD_LEFT_CONTROL ) && ( p_usage->first->value <= K_MK_HID_KEY_PAGE_KEYBOARD_RIGHT_GUI ) )
      {
         /* Récupération de l'adresse du dernier bouton présent dans la chaine */
         l_keyButton = mk_hid_button_getLast ( &p_keyboard->modifier );

         /* Si aucun contrôle n'a été assigné à l'usage */
         if ( ( *l_keyButton ) == K_MK_NULL )
         {
            /* Création d'une table de bouton (la taille de destination est configurée dans cette fonction) */
            l_result = mk_hid_button_create ( p_table, p_usage, p_keyNumber );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Enregistrement de l'adresse mémoire de l'usage */
               ( *l_keyButton ) = p_usage->first->addr;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
               /* Une erreur grave s'est produite, il n'est pas nécessaire d'actualiser la variable d'état permettant de gérer */
               /* les usages alternatifs */
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
         /* Récupération de l'adresse de la dernière touche de la chaine */
         l_key = mk_hid_key_getLast ( ( T_mkKey** ) &p_keyboard->input );

         /* Les sélecteurs du clavier permettent de récupérer le code de la touche pressé ('Array'). Etant donné la variété de claviers différents ('AZERTY', 'QWERTY', ...), */
         /* la translation du code renvoyé par le clavier est réalisée par le dispatch. */
         /* Il est donc inutile d'assigner l'adresse d'une table de conversion à l'usage pour récupérer la valeur des sélecteurs */

         /* Si aucun contrôle n'a été assigné à l'usage */
         if ( ( *l_key ) == K_MK_NULL )
         {
            /* Création d'une table de boutons (la taille de destination est configurée dans cette fonction) */
            l_result = mk_hid_key_create ( p_table, p_usage, p_keyNumber );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Enregistrement de l'adresse mémoire de l'usage */
               ( *l_key ) = p_usage->first->addr;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
               /* Une erreur grave s'est produite, il n'est pas nécessaire d'actualiser la variable d'état permettant de gérer */
               /* les usages alternatifs */
            }
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
      /* La taille de l'usage est incompatible avec le driver, il n'est pas nécessaire d'actualiser la variable d'état permettant de gérer */
      /* les usages alternatifs car ils possèdent tous la même taille. */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_routeLedUsageToKeyboard ( T_mkKeyboard* p_keyboard, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_ledNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de led */
   T_mkLed** l_keyLed;

   /* Si l'usage est codé au maximum sur 32 bits */
   if ( p_table->global.reportSize <= K_MK_HID_MAX_USAGE_SIZE )
   {
      /* Récupération de l'adresse du dernier voyant présent dans la chaine */
      l_keyLed = mk_hid_led_getLast ( &p_keyboard->indicator );

      /* Si aucun contrôle n'a été assigné à l'usage */
      if ( ( *l_keyLed ) == K_MK_NULL )
      {
         /* Création d'une table de led (la taille de destination est configurée dans cette fonction) */
         l_result = mk_hid_led_create ( p_table, p_usage, p_ledNumber );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Enregistrement de l'adresse mémoire de l'usage */
            ( *l_keyLed ) = p_usage->first->addr;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
            /* Une erreur grave s'est produite, il n'est pas nécessaire d'actualiser la variable d'état permettant de gérer */
            /* les usages alternatifs */
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
      /* La taille de l'usage est incompatible avec le driver, il n'est pas nécessaire d'actualiser la variable d'état permettant de gérer */
      /* les usages alternatifs car ils possèdent tous la même taille. */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_routeKeyboard ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_page, uint32_t* p_usageUsed )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un clavier */
   T_mkKeyboard* l_keyboard;

   /* Déclaration d'une variable de travail */
   uint32_t l_counter;

   /* Si les paramètres sont valides */
   if ( ( p_table != K_MK_NULL ) && ( p_report != K_MK_NULL ) && ( p_usage != K_MK_NULL ) && ( p_usageUsed != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du contrôle de type keyboard */
      l_keyboard = p_report->addr;

      /* Actualisation de la variable d'état */
      /* Cette variable permet de savoir si l'intégralité des usages alternatifs doivent être analysés ou non */
      ( *p_usageUsed ) = 1;

      /* Si l'item courant est un item de type USAGE_MINIMUM */
      if ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MINIMUM )
      {
         /* Si la page courante est une page de type KEYBOARD_KEYPAD */
         if ( p_page == K_MK_HID_KEYBOARD_KEYPAD_PAGE )
         {
            /* Un clavier est considéré comme une entité constitué d'une ou plusieurs touches */
            /* Lorsqu'une pression est réalisée, le code associé à la touche (scancode) est renvoyé dans un sélecteur. */
            /* Il faut donc allouer un bouton par sélecteur et non pas un bouton par touche. */
            /* Récupération du nombre de selecteurs */
            l_counter = p_table->global.reportCount;

            /* Allocation d'un ou plusieurs sélecteurs dans la chaine */
            l_result = mk_hid_routeKeyUsageToKeyboard ( l_keyboard, p_table, p_usage, l_counter );
         }

         /* Sinon si la page courante est une page de type 'LED_PAGE' */
         else if ( p_page == K_MK_HID_LED_PAGE )
         {
            /* Un clavier possède une ou plusieurs LED indiquant l'état des touches CAPSLOCK, NUMLOCK, SCROLLLOCK, COMPOSE et KANA */
            /* Récupération du nombre d'indicateurs */
            l_counter = p_table->global.reportCount;

            /* Allocation d'une ou plusieurs led dans la chaine */
            l_result = mk_hid_routeLedUsageToKeyboard ( l_keyboard, p_table, p_usage, l_counter );
         }

         /* Sinon */
         else
         {
            /* L'usage courant (alternatif ou principal) n'est pas utilisé */
            /* On bascule la variable pour continuer l'analyse des usages alternatifs */
            ( *p_usageUsed ) = 0;
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
         /* L'item courant n'est pas un usage */
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



