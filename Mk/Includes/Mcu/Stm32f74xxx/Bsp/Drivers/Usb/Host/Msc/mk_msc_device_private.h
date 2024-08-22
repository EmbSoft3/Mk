/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_msc_device_private.h
* @brief Déclaration des fonctions privées dédiées aux périphériques de stockage.
* @date 17 mai 2020
*
*/

#ifndef MK_MSC_DEVICE_PRIVATE_H
#define MK_MSC_DEVICE_PRIVATE_H

/**
 * @fn T_mkCode mk_msc_createDevice ( T_mkMSCHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface );
 * @brief Cette fonction alloue un nouveau périphérique MSC. Le nouveau périphérique est ajouté dans la liste des périphériques MSC.
 *
 * @param[in, out] p_handler   Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMSCHandler.
 * @param[in]      p_device    Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in]      p_interface Ce paramètre contient l'adresse d'une interface de description du périphérique MSC.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK           : le périphérique MSC a été alloué.
 *         \li \ref K_MK_ERROR_PARAM  : le périphérique MSC n'a pas été alloué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : le périphérique MSC n'a pas été alloué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC : le périphérique MSC n'a pas été alloué car une erreur d'allocation dynamique s'est produite.
 */

T_mkCode mk_msc_createDevice ( T_mkMSCHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface );

/**
 * @fn T_mkCode mk_msc_initDevice ( T_mkMSCHandler* p_handler, T_mkMSCDevice* p_mscDevice );
 * @brief Cette fonction initialise un périphérique MSC via un jeu de requêtes. L'état du périphérique MSC est mis à jour en fonction du statut de l'initialisation.
 *
 * @param[in, out]  p_handler   Ce paramètre contient l'adresse d'un gestionnaire MSC de type \ref T_mkMSCHandler.
 * @param[in]       p_mscDevice Ce paramètre contient l'adresse d'un périphérique MSC de type \ref T_mkMSCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le périphérique MSC a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM   : le périphérique MSC n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le périphérique MSC n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le périphérique MSC n'a pas été initialisé car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : le périphérique MSC n'a pas été initialisé car le périphérique n'a pas répondu à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : le périphérique MSC n'a pas été initialisé car une erreur de communication s'est produite.
 */

T_mkCode mk_msc_initDevice ( T_mkMSCHandler* p_handler, T_mkMSCDevice* p_mscDevice );

/**
 * @fn T_mkCode mk_msc_selectInterface ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction analyse puis sélectionne une interface du périphérique MSC. Seul Le protocole de transport BulkOnly est supporté. Dans le cas où aucun protocole
 *        supporté n'est trouvé, cette fonction bascule l'état du périphérique à \ref K_MK_MSC_DEVICE_NOT_SUPPORTED.
 *
 * @param[in] p_mscDevice Ce paramètre contient l'adresse d'un périphérique MSC de type \ref T_mkMSCDevice.
 * @param[in] p_pipe      Ce paramètre contient l'adresse d'un pipe. Le pipe doit communiquer sur la terminaison de contrôle.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'interface a été configurée.
 *         \li \ref K_MK_ERROR_PARAM   : l'interface n'a pas été configurée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'interface n'a pas été configurée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : l'interface n'a pas été configurée car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'interface n'a pas été configurée car le périphérique n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : l'interface n'a pas été configurée car une erreur de communication s'est produite.
 */

T_mkCode mk_msc_selectInterface ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_msc_deleteDevice ( T_mkMSCHandler* p_handler, T_mkMSCDevice* p_device );
 * @brief Cette fonction supprime l'intégralité de la mémoire allouée par un périphérique MSC. L'intégralité des interfaces MSC sont supprimées.
 *        Des événements \ref K_MK_EVENT_DISCONNECT sont envoyés au dispatcher pour chaque disque supprimé.
 *
 * @param[in, out]  p_handler Ce paramètre contient l'adresse d'un gestionnaire MSC de type \ref T_mkMSCHandler.
 * @param[in, out]  p_device  Ce paramètre contient l'adresse d'un périphérique MSC de type \ref T_mkMSCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le périphérique MSC a été désalloués.
 *         \li \ref K_MK_ERROR_PARAM : le périphérique MSC n'a pas été désalloué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le périphérique MSC n'a pas été désalloué car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_msc_deleteDevice ( T_mkMSCHandler* p_handler, T_mkMSCDevice* p_device );

/**
 * @fn T_mkCode mk_msc_deleteDeviceByInterface ( T_mkMSCHandler* p_handler, T_mkMSCDevice* p_mscDevice );
 * @brief Cette fonction supprime l'intégralité de la mémoire allouée par un périphérique MSC. Contrairement à la fonction \ref mk_msc_deleteDevice, seulement la mémoire allouée par
 *        l'interface du périphérique MSC est supprimée.
 *
 * @param[in, out]  p_handler   Ce paramètre contient l'adresse d'un gestionnaire MSC de type \ref T_mkMSCHandler.
 * @param[in, out]  p_mscDevice Ce paramètre contient l'adresse d'un périphérique MSC de type \ref T_mkMSCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le périphérique MSC a été désalloué.
 *         \li \ref K_MK_ERROR_PARAM : le périphérique MSC n'a pas été désalloué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le périphérique MSC n'a pas été désalloué car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_msc_deleteDeviceByInterface ( T_mkMSCHandler* p_handler, T_mkMSCDevice* p_mscDevice );

/**
 * @fn T_mkCode mk_msc_openPipe ( T_mkMSCDevice* p_mscDevice );
 * @brief Cette fonction ouvre les pipes de communication du périphérique MSC ('Control', 'BulkIn' et 'BulkOut').
 * @param[in, out] p_mscDevice Ce paramètre contient l'adresse d'un gestionnaire MSC de type \ref T_mkMSCHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les pipes de communication ont été ouvert.
 *         \li \ref K_MK_ERROR_PARAM   : les pipes de communication n'ont pas été ouvert car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : les pipes de communication n'ont pas été ouvert car aucun canal de communication n'est disponible.
 *         \li \ref K_MK_ERROR_ISR     : les pipes de communication n'ont pas été ouvert car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_NESTED  : les pipes de communication n'ont pas été ouvert car la tâche appelante est propriétaire d'un autre objet de synchronisation de type \ref T_mkMutex.
 */

T_mkCode mk_msc_openPipe ( T_mkMSCDevice* p_mscDevice );

/**
 * @fn T_mkCode mk_msc_closePipe ( T_mkMSCDevice* p_mscDevice );
 * @brief Cette fonction ferme les pipes de communication du périphérique MSC ('Control', 'BulkIn' et 'BulkOut').
 * @param[in, out] p_mscDevice Ce paramètre contient l'adresse d'un gestionnaire MSC de type \ref T_mkMSCHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les pipes ont été fermés.
 *         \li \ref K_MK_ERROR_PARAM   : les pipes de communication n'ont pas été fermés car au moins un paramètre est invalide.
 */

T_mkCode mk_msc_closePipe ( T_mkMSCDevice* p_mscDevice );

/**
 *
 */

#endif

