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
* @file mk_dispatcher_types.h
* @brief Déclaration des types dédiés au dispatcher.
* @date 17 nov. 2019
*
*/

#ifndef MK_DISPATCHER_TYPES_H
#define MK_DISPATCHER_TYPES_H

/**
 * @struct T_mkDispatcherMessage
 * @brief Déclaration de la structure T_mkDispatcherMessage.
 *
 */

typedef struct T_mkDispatcherMessage T_mkDispatcherMessage;
struct T_mkDispatcherMessage
{
   T_mkAddr appCtrl;                                           /*!< Ce membre contient l'adresse d'un contrôle applicatif (ex: \ref T_mkMouse, \ref T_mkKeyboard, \ref T_mkGPIOCtrl, ...). */
   uint16_t ctrlEvt;                                           /*!< Ce membre contient le type d'un événement. (\ref T_mkCtrlEvent). */
   uint16_t padding16;                                         /*!< Padding. */
   uint32_t padding32;                                         /*!< Padding. */
   uint32_t tick;                                              /*!< Ce membre contient le tick de détection de l'événement. */
};

/**
 * @struct T_mkListenerMessage
 * @brief Déclaration de la structure T_mkListenerMessage.
 *
 */

typedef struct T_mkListenerMessage T_mkListenerMessage;
struct T_mkListenerMessage
{
   T_mkAddr appCtrl;                                           /*!< Ce membre contient l'adresse d'un contrôle applicatif (ex: \ref T_mkMouse, \ref T_mkKeyboard, \ref T_mkGPIOCtrl, ...). */
   uint16_t appCtrlID;                                         /*!< Ce membre contient l'identifiant du contrôle applicatif (\ref T_mkCtrlId). */
   uint16_t ctrlId;                                            /*!< Ce membre contient l'identifiant de l'événement (bouton droit, gauche , ...). */
   uint16_t ctrlEvt;                                           /*!< Ce membre contient le type d'un événement. (\ref T_mkCtrlEvent). */
   uint16_t padding;                                           /*!< Padding. */
   uint32_t tick;                                              /*!< Ce membre contient le tick de détection de l'événement. */
};

/**
 * @struct T_mkDispatcherAttributes
 * @brief Déclaration de la structure T_mkDispatcherAttributes.
 *
 */

typedef struct T_mkDispatcherAttributes T_mkDispatcherAttributes;
struct T_mkDispatcherAttributes
{
   real32_t pointerResolution;                                 /*!< Ce membre contient la résolution des pointeurs connectés au système (\ref K_MK_POINTER_DEFAULT_RESOLUTION par défaut). Une valeur négative inverse la direction des axes. */
   real32_t stickResolution;                                   /*!< Ce membre contient la résolution des sticks connectés au système (\ref K_MK_STICK_DEFAULT_RESOLUTION par défaut). Une valeur négative inverse la direction des axes. */
   uint32_t mouseCursorLayer;                                  /*!< Ce membre contient le layer où doit être dessiné le curseur des souris (\ref K_MK_GRAPHICS_BACKGROUND et \ref K_MK_GRAPHICS_FOREGROUND). */
   uint32_t mouseCursorVisibility;                             /*!< Ce membre contient la visibilité du curseur des souris (\ref K_MK_FIELD_VISIBLE et \ref K_MK_FIELD_INVISIBLE). */
   T_mkAddr mouseCursorBitmap;                                 /*!< Ce membre contient l'adresse du bitmap du curseur de la souris (valeur \ref K_MK_NULL si curseur par défaut). */
   uint32_t mouseCursorWidth;                                  /*!< Ce membre contient la largeur du bitmap du curseur [en pixel]. */
   uint32_t mouseCursorHeight;                                 /*!< Ce membre contient la hauteur du bitmap du curseur [en pixel]. */
   uint32_t keyboardInhibitionDuration;                        /*!< Ce membre contient la durée minimale [en ms] entre la génération d'un événement 'Down' et le premier événement 'Hold' d'un clavier (\ref K_MK_KEYBOARD_HOLD_INHIBITION_DURATION par défaut). */
   uint32_t keyboardHoldRate;                                  /*!< Ce membre contient la durée minimale [en ms] entre la génération de deux événements 'Hold' (\ref K_MK_KEYBOARD_HOLD_RATE par défaut). */
};

/**
 * @struct T_mkDispatcherHandler
 * @brief Déclaration de la structure T_mkDispatcherHandler.
 *
 */

typedef struct T_mkDispatcherHandler T_mkDispatcherHandler;
struct T_mkDispatcherHandler
{
   T_mkDispatcherAttributes attribute;                         /*!< Ce membre contient les attributs du dispatcher. */
   T_mkDispatcherMailArea* mailArea;                           /*!< Ce membre contient l'adresse du gestionnaire permettant l'émission de requêtes à destination du dispatcher. */
   T_mkDispatcherHidArea* hidArea;                             /*!< Ce membre contient l'adresse du gestionnaire permettant l'émission de requêtes à destination du terminal HID. */
   T_mkDispatcherListenerArea* listenerArea;                   /*!< Ce membre contient l'adresse du gestionnaire permettant l'émission de requêtes à destination de la tâche d'écoute. */
};

/**
 *
 */

#endif


