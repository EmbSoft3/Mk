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
* @file mk_usb_private.h"
* @brief Déclaration des fonctions privées du module USB.
* @date 8 juin 2019
*
*/

#ifndef MK_USB_PRIVATE_H
#define MK_USB_PRIVATE_H

/**
 * @fn void mk_usbhs_taskHostMode ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage du terminal USB_OTGHS (mode host).
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_usbhs_taskHostMode ( T_mkAddr p_param );

/**
 * @fn void mk_usbhs_taskDeviceMode ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage du terminal USB_OTGHS (mode device).
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_usbhs_taskDeviceMode ( T_mkAddr p_param );

/**
 * @fn void mk_usbfs_taskHostMode ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage du terminal USB_OTGFS (mode host).
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_usbfs_taskHostMode ( T_mkAddr p_param );

/**
 * @fn void mk_usbfs_taskDeviceMode ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage du terminal USB_OTGFS (mode device).
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_usbfs_taskDeviceMode ( T_mkAddr p_param );

/**
 * @fn void mk_usb_initGPIO ( T_mkAddr p_usb );
 * @brief Cette fonction initialise les broches d'un périphérique matériel.
 * @param[in] p_usb Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                  être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 *
 * @return Sans objet.
 *
 */

void mk_usb_initGPIO ( T_mkAddr p_usb );

/**
 * @fn T_mkUSBCode mk_usb_initCore ( T_mkAddr p_usb );
 * @brief Cette fonction initialise le coeur USB d'un périphérique matériel.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                  être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : l'initialisation du coeur USB a réussi.
 *         \li \ref K_MK_ERROR_INIT  : l'initialisation du coeur USB a échoué car le timeout est arrivé à échéance.
 *         \li \ref K_MK_ERROR_PARAM : l'initialisation du coeur USB a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : l'initialisation du coeur USB a échoué car cette fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_usb_initCore ( T_mkAddr p_usb );

/**
 * @fn T_mkCode mk_usb_resetCore ( T_mkAddr p_usb );
 * @brief Cette fonction reset le coeur USB d'un périphérique matériel.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                      être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 * @param[in] p_timeout Ce paramètre contient la durée du timeout [en multiple de 2 ms].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la réinitialisation du coeur USB a réussi.
 *         \li \ref K_MK_ERROR_INIT  : la réinitialisation du coeur USB a échoué car le timeout est arrivé à échéance.
 *         \li \ref K_MK_ERROR_PARAM : la réinitialisation du coeur USB a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : la réinitialisation du coeur USB a échoué car cette fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_usb_resetCore ( T_mkAddr p_usb, uint32_t p_timeout );

/**
 * @fn T_mkCode mk_usb_selectMode ( T_mkAddr p_usb, uint32_t* p_status );
 * @brief Cette fonction initialise le périphérique USB en mode host ou device.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                      être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 * @param[out] p_status Ce paramètre contient la valeur du mode de fonctionnement. Il peut prendre les valeurs suivantes :
 *                      \ref K_USB_HOST_MODE et \ref K_USB_DEVICE_MODE;
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : l'initialisation du périphérique a réussi.
 *         \li \ref K_MK_ERROR_PARAM : l'initialisation du périphérique a échoué. car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : l'initialisation a échoué car cette fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_usb_selectMode ( T_mkAddr p_usb, uint32_t* p_status );

/**
 * @fn T_mkCode mk_usb_initHost ( T_mkAddr p_usb );
 * @brief Cette fonction initialise le périphérique USB en mode host.
 * @param[in] p_usb Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                  être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : l'initialisation a réussi.
 *         \li \ref K_MK_ERROR_PARAM : l'initialisation a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : l'initialisation a échoué car cette fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_usb_initHost ( T_mkAddr p_usb );

/**
 * @fn void mk_usb_initDevice ( T_mkAddr p_usb );
 * @brief Cette fonction initialise le périphérique USB en mode device.
 * @param[in] p_usb Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                  être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
*
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK : Bypass du résultat de la fonction.
 *
 * @todo Implémenter cette fonction.
 *
 */

T_mkCode mk_usb_initDevice ( T_mkAddr p_usb );

/**
 * @fn void mk_usb_initPort ( T_mkAddr p_usb );
 * @brief Cette fonction initialise le port d'un périphérique USB.
 *
 * @param[in] p_usb       Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                        être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 * @param[in] p_resetTick Ce paramètre contient la durée du reset du port USB [en multiple de tick].
 *                        Par défaut, cette valeur est définie par la valeur \ref K_MK_USB_RESET_TICK.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : l'initialisation du port USB a réussi.
 *         \li \ref K_MK_ERROR_PARAM : l'initialisation du port USB a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : l'initialisation du port USB a échoué car cette fonction a été exécutée depuis un vecteur d'interruption.
 *
 * @note Cette fonction est dédiée au mode host.
 *
 */

T_mkCode mk_usb_initPort ( T_mkAddr p_usb, uint32_t p_resetTick );

/**
 * @fn void mk_usb_resetPort ( T_mkAddr p_usb );
 * @brief Cette fonction reset les périphériques connecté sur un port USB.
 *
 * @param[in] p_usb       Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                        être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 * @param[in] p_resetTick Ce paramètre contient la durée du reset du port USB [en multiple de tick].
 *                        Par défaut, cette valeur est définie par la valeur \ref K_MK_USB_RESET_TICK.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le reset du port USB a réussi.
 *         \li \ref K_MK_ERROR_PARAM : le reset du port USB a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le reset du port USB a échoué car cette fonction a été exécutée depuis un vecteur d'interruption.
 *
 *
 * @note Cette fonction est dédiée au mode host.
 *
 */

T_mkCode mk_usb_resetPort ( T_mkAddr p_usb, uint32_t p_resetTick );

/**
 * @fn uint32_t mk_usb_flushRxFifo ( T_mkAddr p_usb, uint32_t p_timeout );
 * @brief Cette fonction réinitialise le FIFO de réception.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                      être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 * @param[in] p_timeout Ce paramètre contient la valeur du timeout [en multiple de 2 ms].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la réinitialisation du FIFO a réussi.
 *         \li \ref K_MK_ERROR_INIT  : la réinitialisation du FIFO a échoué car le timeout est arrivé à échéance.
 *         \li \ref K_MK_ERROR_PARAM : la réinitialisation du FIFO a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : la réinitialisation du FIFO a échoué car cette fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_usb_flushRxFifo ( T_mkAddr p_usb, uint32_t p_timeout );

/**
 * @fn uint32_t mk_usb_flushTxFifo ( T_mkAddr p_usb, uint32_t p_fifoNumber, uint32_t p_timeout );
 * @brief Cette fonction réinitialise un ou plusieurs FIFO de transmission.
 *
 * @param[in] p_usb        Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                         être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 * @param[in] p_fifoNumber Ce paramètre contient le numéro du FIFO de transmission à réinitialiser. Les constantes
 *                         suivantes peuvent être utilisées : \n \ref K_USB_TXFIFO_0 à \ref K_USB_TXFIFO_15.
 *                         La constante K_USB_TXFIFO_ALL peut être utilisée pour réinitialiser tous les buffers
 *                         de transmission.
 * @param[in] p_timeout Ce paramètre contient la valeur du timeout [en multiple de 2 ms].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la réinitialisation du FIFO a réussi.
 *         \li \ref K_MK_ERROR_INIT  : la réinitialisation du FIFO a échoué car le timeout est arrivé à échéance.
 *         \li \ref K_MK_ERROR_PARAM : la réinitialisation du FIFO a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : la réinitialisation du FIFO a échoué car cette fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_usb_flushTxFifo ( T_mkAddr p_usb, uint32_t p_fifoNumber, uint32_t p_timeout );

/**
 * @fn uint32_t mk_usb_waitIdle ( T_mkAddr p_usb );
 * @brief Cette fonction attend tant que le coeur USB n'est pas au repos.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                      être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 * @param[in] p_timeout Ce paramètre contient la valeur du timeout [en multiple de 2 ms].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : l'état du coeur USB est l'état de repos.
 *         \li \ref K_MK_ERROR_INIT  : l'état du coeur USB n'est pas l'état de repos (échéance du timeout).
 *         \li \ref K_MK_ERROR_ISR   : l'état du coeur USB est inconnu car cette fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_usb_waitIdle ( T_mkAddr p_usb, uint32_t p_timeout );

/**
 * @fn uint32_t mk_usb_getChannel ( T_mkAddr p_usb );
 * @brief Cette fonction retourne le numéro d'un canal de communication au repos.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                  être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 *
 * @return Cette fonction retourne l'index d'un canal disponible ou la valeur \ref K_MK_USB_CHANNEL_NUMBER si aucun
 *         canal n'est disponible.
 *
 */

uint32_t mk_usb_getChannel ( T_mkAddr p_usb );

/**
 *
 */

#endif


