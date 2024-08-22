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
* @file mk_hid_button_setType.c
* @brief Définition de la fonction mk_hid_button_setType.
* @date 3 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_button_setType ( T_mkButton* p_button, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_button != K_MK_NULL ) && ( p_table != K_MK_NULL ) && ( p_usage != K_MK_NULL ) )
   {
      /* Un bouton peut être caractérisé par les types 'Selector' (Sel), 'ON/OFF Controls' (OOC), 'Momentary Controls' (MC) et */
      /* 'One-Shot Controls' (OSC). */

      /* Lors du dispatch, les événements PRESS/RELEASE sont associés à un bouton momentanné (MC), les événements ON/OFF sont associés à un bouton */
      /* à verrou mécanique et l'événement PUSH est associé à un bouton de type (OSC). */

      /* Si l'usage est de type 'Variable' */
      if ( ( p_usage->last->value & K_MK_HID_ITEM_VARIABLE ) == K_MK_HID_ITEM_VARIABLE )
      {
         /* Si le bouton est de type 'Momentary' (MC) - PREFERRED_MAIN, ABSOLUTE */
         if ( ( ( p_usage->last->value & ( K_MK_HID_ITEM_NO_PREFERRED | K_MK_HID_ITEM_RELATIVE ) ) == 0 ) &&
                ( p_table->global.logicalMinimum == 0 ) && ( p_table->global.logicalMaximum == 1 ) )
         {
            /* Ce type de bouton est un bouton classique, la valeur 1 représente l'état PRESS (actif), la valeur 0 représente un état RELEASE (inactif). */
            /* Ce type caractérise les boutons d'une souris. */

            /* Actualisation de l'état du bouton */
            p_button->layer.type = K_MK_BUTTON_MOMENTARY_CONTROL;
         }

         /* Sinon si le bouton est de type 'OneShot' (OSC) - PREFERED_MAIN, RELATIVE */
         else if ( ( ( p_usage->last->value & ( K_MK_HID_ITEM_NO_PREFERRED | K_MK_HID_ITEM_RELATIVE ) ) == K_MK_HID_ITEM_RELATIVE ) &&
                   ( p_table->global.logicalMinimum == 0 ) && ( p_table->global.logicalMaximum == 1 ) )
         {
            /* Ce type de bouton génére un événement lors d'une transition 0 vers 1. Aucun événement n'est généré lors de la transition 1 vers 0. */
            /* Même si aucun événement n'est généré, la transition 1 vers 0 est requise pour générer les prochains événements. */

            /* Actualisation de l'état du bouton */
            p_button->layer.type = K_MK_BUTTON_ONE_SHOT_CONTROL;
         }

         /* Un bouton de type OOC peut être constitué de : */
         /* - 2 boutons (ON et OFF) codés sur 2 bits signés. La transition 0 à -1 code la valeur OFF tandis que la transition 0 à 1 code la valeur ON. */
         /* - 1 bouton ON/OFF momentanné codé sur 1 bit non signé. L'état ON et l'état OFF basculent chaque fois que le bouton est pressé ('Toogle'). */
         /* - 1 bouton ON/OFF à maintien codé sur 1 bit non signé. L'état ON est codé par la valeur 1, l'état OFF est codé par la valeur 0. */

         /* Sinon si le bouton est de type 'ON-OFF' (OOC) - NO_PREFERRED_MAIN, ABSOLUTE */
         else if ( ( ( p_usage->last->value & ( K_MK_HID_ITEM_NO_PREFERRED | K_MK_HID_ITEM_RELATIVE ) ) == K_MK_HID_ITEM_NO_PREFERRED ) &&
                   ( p_table->global.logicalMinimum == 0 ) && ( p_table->global.logicalMaximum == 1 ) )
         {
            /* Ce type de bouton est à double état, la valeur 1 réprésente l'état ON, la valeur 0 génére l'état OFF. */
            /* Il est semblable à un bouton de souris à l'exception qu'il ne revient pas automatiquement à son état de repos. */

            /* Actualisation de l'état du bouton */
            p_button->layer.type = K_MK_BUTTON_TOOGLE_ON_OFF_CONTROL;
         }

         /* Sinon si le bouton est de type 'ON-OFF' (OOC) - NO_PREFERRED_MAIN, RELATIVE */
         else if ( ( ( p_usage->last->value & ( K_MK_HID_ITEM_NO_PREFERRED | K_MK_HID_ITEM_RELATIVE ) ) == ( K_MK_HID_ITEM_NO_PREFERRED | K_MK_HID_ITEM_RELATIVE ) ) &&
                   ( p_table->global.logicalMinimum == -1 ) && ( p_table->global.logicalMaximum == 1 ) )
         {
            /* Ce type de bouton(s) est à double transition, la transition 0 vers 1 sélectionne l'état ON, la transition 0 vers -1 sélectionne l'état OFF */
            /* Les transitions -1 vers 0 et 1 vers 0 ne génére pas d'événement. */

            /* Actualisation de l'état du bouton */
            p_button->layer.type = K_MK_BUTTON_ON_OFF_CONTROL;
         }

         /* Sinon si le bouton est codé sur un BITMAP (Sel) */
         else if ( p_table->global.reportSize == 1 )
         {
            /* On rappel que pour simplifier le décodage, l'identification de chaque sélecteur (bit) doit être effectué par un usage présent dans un collection de type 'Logical'. */
            /* Pour un bouton, le sélecteur doit être de type 'Button'. Aucune instance de bouton n'est générée si le sélecteur n'est pas identifié. */

            /* L'etat du bouton est présent dans un champ de sélecteur (sur 1bit). */
            /* La valeur 1 réprésente l'état ON, la valeur 0 génére l'état OFF. */

            /* Actualisation de l'état du bouton */
            p_button->layer.type = K_MK_BUTTON_SELECTOR_CONTROL;
         }

         /* Sinon */
         else
         {
            /* Le type du bouton n'est pas identifié, aucun événement ne doit être généré. */
            /* Actualisation de l'état du bouton */
            p_button->layer.type = K_MK_BUTTON_UNKNOWN_CONTROL;
         }
      }

      /* Sinon */
      else
      {
         /* L'état du bouton est exprimé sous forme d'un sélecteur de type 'ARRAY'. */
         /* Ce type de codage ne permet pas de générér des événements car l'usage 'Button' nécessite la transmission d'un état. */
         /* Ce mode de codage doit être utilisé avec des 'Usage' explicite (ou complémenté) comme (STAT_READY, STAT_NOT_READY, ...). */
         /* Actualisation de l'état du bouton */
         p_button->layer.type = K_MK_BUTTON_SELECTOR_CONTROL;
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


