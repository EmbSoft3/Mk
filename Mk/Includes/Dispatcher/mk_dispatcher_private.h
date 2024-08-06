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
* @file mk_dispatcher_private.h
* @brief Déclaration des fonctions privées dédiées au dispatcher.
* @date 17 nov. 2019
*
*/

#ifndef MK_DISPATCHER_PRIVATE_H
#define MK_DISPATCHER_PRIVATE_H

/**
 * @fn void mk_dispatcher_task ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage du dispatcher.
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_dispatcher_task ( T_mkAddr p_param );

/**
 * @fn T_mkCode mk_dispatcher_initHandler ( T_mkDispatcherHandler* p_handler );
 * @brief Cette fonction initialise un dispatcher de type \ref T_mkDispatcherHandler.
 * @param[in, out] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK           : le dispatcher a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM  : le dispatcher n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : le dispatcher n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC : le dispatcher n'a pas été initialisé en raison d'une erreur d'allocation dynamique.
 */

T_mkCode mk_dispatcher_initHandler ( T_mkDispatcherHandler* p_handler );

/**
 * @fn T_mkCode mk_dispatcher_handleMessage ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );
 * @brief Cette fonction traite les messages reçus par le dispatcher.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK          : le message a été traité sans renconter d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : le message n'a pas été traité car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le message n'a pas été traité car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : le message n'a pas été traité car une tâche de type non privilégié ne peut pas utiliser une broche GPIO protégée.
 *
 */

T_mkCode mk_dispatcher_handleMessage ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );

/**
 * @fn T_mkCode mk_dispatcher_handleMouse ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );
 * @brief Cette fonction génére un ou plusieurs événements en relation avec une souris.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération des événements a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération des événements a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération des événements a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération des événements a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération des événements a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleMouse ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );

/**
 * @fn T_mkCode mk_dispatcher_handleJoystick ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );
 * @brief Cette fonction génére un ou plusieurs événements en relation avec un joystick.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération des événements a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération des événements a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération des événements a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération des événements a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération des événements a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleJoystick ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );

/**
 * @fn T_mkCode mk_dispatcher_handleKeyboard ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );
 * @brief Cette fonction génére un ou plusieurs événements en relation avec un clavier.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération des événements a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération des événements a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération des événements a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération des événements a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération des événements a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleKeyboard ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );

/**
 * @fn T_mkCode mk_dispatcher_handleConsumer ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );
 * @brief Cette fonction génére un ou plusieurs événements en relation avec un consumer.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération des événements a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération des événements a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération des événements a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération des événements a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération des événements a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleConsumer ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );

/**
 * @fn T_mkCode mk_dispatcher_handleGpio ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );
 * @brief Cette fonction génére un ou plusieurs événements en relation avec une broche GPIO.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération des événements a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération des événements a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération des événements a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération des événements a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération des événements a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleGpio ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );

/**
 * @fn T_mkCode mk_dispatcher_handleVolume ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );
 * @brief Cette fonction génére un ou plusieurs événements en relation avec une partition.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération des événements a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération des événements a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération des événements a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération des événements a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération des événements a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleVolume ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );

/**
 * @fn T_mkCode mk_dispatcher_handleDisk ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );
 * @brief Cette fonction génére un ou plusieurs événements en relation avec un disque dur.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération des événements a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération des événements a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération des événements a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération des événements a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération des événements a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleDisk ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );

/**
 * @fn T_mkCode mk_dispatcher_handleApplication ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );
 * @brief Cette fonction génére un ou plusieurs événements en relation avec une application.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération des événements a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération des événements a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération des événements a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération des événements a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération des événements a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleApplication ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message );

/**
 * @fn T_mkCode mk_dispatcher_handleButton ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_button );
 * @brief Cette fonction génére un ou plusieurs événements en relation avec un bouton poussoir.
 *
 * @param[in] p_handler     Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message     Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 * @param[in] p_appCtrlId Ce paramètre contient l'identifiant du contrôle applicatif qui a déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl   Ce paramètre contient l'adresse du contrôle applicatif qui a déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...).
 * @param[in] p_button      Ce paramètre contient l'adresse d'un bouton de type \ref T_mkButton.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération des événements a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération des événements a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération des événements a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération des événements a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération des événements a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleButton ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_button );

/**
 * @fn T_mkCode mk_dispatcher_handleHatSwitch ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_switch );
 * @brief Cette fonction génére un ou plusieurs événements en relation avec un interrupteur à chapeau.
 *
 * @param[in] p_handler     Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message     Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 * @param[in] p_appCtrlId Ce paramètre contient l'identifiant du contrôle applicatif qui a déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl   Ce paramètre contient l'adresse du contrôle applicatif qui a déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...).
 * @param[in] p_switch      Ce paramètre contient l'adresse d'un interrupteur à chapeau de type \ref T_mkHatSwitch.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération des événements a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération des événements a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération des événements a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération des événements a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération des événements a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleHatSwitch ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_switch );

/**
 * @fn T_mkCode mk_dispatcher_handleThrottle ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_throttle );
 * @brief Cette fonction génére un événement en relation avec une manette.
 *
 * @param[in] p_handler     Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message     Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 * @param[in] p_appCtrlId Ce paramètre contient l'identifiant du contrôle applicatif qui a déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl   Ce paramètre contient l'adresse du contrôle applicatif qui a déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...).
 * @param[in] p_throttle    Ce paramètre contient l'adresse d'une manette de type \ref T_mkThrottle.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération de l'événement a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération de l'événement a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération de l'événement a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération de l'événement a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération de l'événement a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleThrottle ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_throttle );

/**
 * @fn T_mkCode mk_dispatcher_handleConsumerCode ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_consumerCode );
 * @brief Cette fonction génére un événement en relation avec un consumer.
 *
 * @param[in] p_handler      Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message      Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 * @param[in] p_appCtrlId    Ce paramètre contient l'identifiant du contrôle applicatif qui a déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl    Ce paramètre contient l'adresse du contrôle applicatif qui a déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...).
 * @param[in] p_consumerCode Ce paramètre contient l'adresse d'une manette de type \ref T_mkConsumerCode.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération de l'événement a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération de l'événement a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération de l'événement a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération de l'événement a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération de l'événement a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleConsumerCode ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_consumerCode );

/**
 * @fn T_mkCode mk_dispatcher_handlePointer ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_axis );
 * @brief Cette fonction génére un événement en relation avec un pointeur.
 *
 * @param[in] p_handler     Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message     Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 * @param[in] p_appCtrlId   Ce paramètre contient l'identifiant du contrôle applicatif qui a déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl   Ce paramètre contient l'adresse du contrôle applicatif qui a déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...).
 * @param[in] p_axis        Ce paramètre contient l'adresse d'un pointeur deux dimensions de type \ref T_mkAxis2.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération de l'événement a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération de l'événement a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération de l'événement a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération de l'événement a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération de l'événement a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handlePointer ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_axis );

/**
 * @fn T_mkCode mk_dispatcher_handleStick ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_axis );
 * @brief Cette fonction génére un événement en relation avec un stick.
 *
 * @param[in] p_handler     Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message     Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 * @param[in] p_appCtrlId   Ce paramètre contient l'identifiant du contrôle applicatif qui a déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl     Ce paramètre contient l'adresse du contrôle applicatif qui a déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...).
 * @param[in] p_axis        Ce paramètre contient l'adresse d'un stick trois dimensions de type \ref T_mkStick3.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération de l'événement a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération de l'événement a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération de l'événement a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération de l'événement a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération de l'événement a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleStick ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_axis );

/**
 * @fn T_mkCode mk_dispatcher_handleWheel ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_wheel );
 * @brief Cette fonction génére un événement en relation avec une molette verticale.
 *
 * @param[in] p_handler     Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message     Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 * @param[in] p_appCtrlId   Ce paramètre contient l'identifiant du contrôle applicatif qui a déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl     Ce paramètre contient l'adresse du contrôle applicatif qui a déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...).
 * @param[in] p_wheel       Ce paramètre contient l'adresse d'une molette de type \ref T_mkWheel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération de l'événement a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération de l'événement a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération de l'événement a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération de l'événement a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération de l'événement a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleWheel ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_wheel );

/**
 * @fn T_mkCode mk_dispatcher_handleACPan ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_acPan );
 * @brief Cette fonction génére un événement en relation avec une molette horizontale.
 *
 * @param[in] p_handler     Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message     Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 * @param[in] p_appCtrlId   Ce paramètre contient l'identifiant du contrôle applicatif qui a déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl     Ce paramètre contient l'adresse du contrôle applicatif qui a déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...).
 * @param[in] p_acPan       Ce paramètre contient l'adresse d'une molette de type \ref T_mkWheel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération de l'événement a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération de l'événement a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération de l'événement a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération de l'événement a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération de l'événement a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleACPan ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_acPan );

/**
 * @fn T_mkCode mk_dispatcher_postEvent ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, T_mkAddr p_ctrlAddr, uint16_t p_appId, uint16_t p_id );
 * @brief Cette fonction poste un événement à destination de la tâche d'écoute.
 *
 * @param[in] p_handler  Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_message  Ce paramètre contient l'adresse d'un message de type \ref T_mkDispatcherMessage.
 * @param[in] p_ctrlAddr Ce paramètre contient l'adresse du contrôle applicatif qui a déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...).
 * @param[in] p_appId    Ce paramètre contient l'identifiant du contrôle applicatif qui a déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_id       Ce paramètre contient l'identifiant de l'événement.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la transmission de l'événement a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la transmission de l'événement a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la transmission de l'événement a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la transmission de l'événement a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la transmission de l'événement a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_postEvent ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, T_mkAddr p_ctrlAddr, uint16_t p_appId, uint16_t p_id );

/**
 *
 */

#endif


