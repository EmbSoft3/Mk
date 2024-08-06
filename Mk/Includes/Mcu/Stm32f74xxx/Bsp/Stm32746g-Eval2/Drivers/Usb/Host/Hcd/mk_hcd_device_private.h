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
* @file mk_hcd_device_private.h
* @brief Déclaration des fonctions privées dédiées aux périphériques USB.
* @date 11 oct. 2019
*
*/

#ifndef MK_HCD_DEVICE_PRIVATE_H
#define MK_HCD_DEVICE_PRIVATE_H

/**
 * @fn T_mkCode mk_hcd_enumerate ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction déclenche la procédure d'énumération d'un périphérique. Si celle-ci réussie,
 *        la procédure de dispatch est déclenchée (\ref mk_hcd_dispatchDevice).
 *
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in, out] p_device  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'énumération a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'énumération a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'énumération a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'énumération a échoué car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : l'énumération a échoué car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @note Dans le cas où l'énumération a échoué, l'état du périphérique USB peut être vérifié en analysant l'attribut "state" de la
 *       structure \ref T_mkHCDDevice.
 */

T_mkCode mk_hcd_enumerate ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_dispatchDevice ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction dispatch l'adresse d'un périphérique USB à un terminal de traitement.
 *        Le terminal est choisi en fonction du type du périphérique USB (HID, MSC,...).
 *
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in, out] p_device  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le dispatch a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le dispatch a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le dispatch a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le dispatch a échoué car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le dispatch a échoué car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_dispatchDevice ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_getDeviceDescriptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction récupère le descripteur de périphérique.
 *
 * @param[in, out] p_device Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe   Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le descripteur de périphérique a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le descripteur de périphérique n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le descripteur de périphérique n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le descripteur de périphérique n'a pas été récupéré car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le descripteur de périphérique n'a pas été récupéré car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_getDeviceDescriptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_getDeviceQualifier ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction récupère le qualificateur de périphérique.
 *
 * @param[in, out] p_device Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe   Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le qualificateur de périphérique a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le qualificateur de périphérique n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le qualificateur de périphérique n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le qualificateur de périphérique n'a pas été récupéré car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le qualificateur de périphérique n'a pas été récupéré car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_getDeviceQualifier ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_getStringDescriptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint8_t* p_string, uint16_t* p_length, uint16_t p_langid );
 * @brief Cette fonction récupère la chaine de caractères unicode identifiant le périphérique. Lorsque le paramètre 'p_langid' prend la valeur
 *        \ref K_MK_HCD_LANGID_INDEX, la chaine de caractères à l'index '1' est retournée. Sinon la chaine de caractères correspondant au langage spécifié est renvoyée.
 *
 * @param[in, out] p_device  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[out]     p_string  Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in, out] p_length  Ce paramètre contient la longueur du buffer utilisateur. Si la chaine est récupérée, ce paramètre est mis à jour avec la longueur de la chaine renvoyée.
 * @param[in]      p_langid  Ce paramètre contient l'identifiant de langage de la chaine de caractères.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la chaine de caractères a été récupérée.
 *         \li \ref K_MK_ERROR_PARAM         : la chaine de caractères n'a pas été récupérée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : la chaine de caractères n'a pas été récupérée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la chaine de caractères n'a pas été récupérée car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM          : la chaine de caractères n'a pas été récupérée car une erreur de communication s'est produite. Le statut
 *                                             de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : la chaine de caractères n'a pas été récupérée car le langage spécifié n'est pas supporté.
 */

T_mkCode mk_hcd_getStringDescriptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint8_t* p_string, uint16_t* p_length, uint16_t p_langid );

/**
 * @fn T_mkCode mk_hcd_setDeviceAddress ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction configure l'adresse d'un périphérique.
 *
 * @param[in, out] p_device Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe   Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'adresse du périphérique a été configurée.
 *         \li \ref K_MK_ERROR_PARAM   : l'adresse du périphérique n'a pas été configurée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'adresse du périphérique n'a pas été configurée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'adresse du périphérique n'a pas été configurée car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : l'adresse du périphérique n'a pas été configurée car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_setDeviceAddress ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_getDeviceStatus ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkHCDDeviceStatus* p_status );
 * @brief Cette fonction récupère le registre de statut d'un périphérique.
 *
 * @param[in, out] p_device  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[out]     p_status  Ce paramètre contient l'adresse d'un registre de statut de type \ref T_mkHCDDeviceStatus.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le registre de statut a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le registre de statut n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le registre de statut n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le registre de statut n'a pas été récupéré car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le registre de statut n'a pas été récupéré car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_getDeviceStatus ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkHCDDeviceStatus* p_status );

/**
 * @fn T_mkCode mk_hcd_getConfigurationDescriptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint16_t p_length );
 * @brief Cette fonction récupère le descripteur de configuration, les descripteurs d'interface et les descripteurs de terminaison.
 *
 * @param[in, out] p_device  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_length  Ce paramètre contient le nombre d'octets que le périphérique USB doit transmettre au maitre suite à la réception de la commande
 *                           de transmission du descripteur de configuration.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les descripteurs ont été récupérés.
 *         \li \ref K_MK_ERROR_PARAM   : les descripteurs n'ont pas été récupérés car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : les descripteurs n'ont pas été récupérés car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : les descripteurs n'ont pas été récupérés car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : les descripteurs n'ont pas été récupérés car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *         \li \ref K_MK_ERROR_MALLOC  : les descripteurs n'ont pas été récupérés en raison d'une erreur d'allocation dynamique.
 *
 * @note La structure \ref T_mkHCDDevice supporte uniquement une configuration. Les descripteurs d'interface et de terminaison sont alloués dynamiquement.
 * @warning Cette fonction est de type récursive.
 *
 */

T_mkCode mk_hcd_getConfigurationDescriptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint16_t p_length );

/**
 * @fn T_mkCode mk_hcd_getSpecialDesciptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkHCDInterfaceDescriptor* p_interface, T_mkAddr p_buf, uint32_t p_register );
 * @brief Cette fonction permet de récupérer des descripteurs spécifiques contenus dans une interface d'un descripteur de configuration.
 *
 * @param[in, out] p_device    Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_interface Ce paramètre contient l'adresse de l'interface contenant le descripteur spécifique.
 * @param[in]      p_buf       Ce paramètre contient l'adresse où doit être stocké le descripteur spécifique.
 * @param[in]      p_register  Ce paramètre contient une combinaison des champs 'length' et 'class' organisée de la manière suivante : \n
 *                             p_register = class<15:8> | length<7:0>
 *                             avec 'length' la longueur du descripteur (valeur inférieure tolérée) et 'class', l'identifiant du descripteur recherché.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le descripteur a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le descripteur n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le descripteur n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le descripteur n'a pas été récupéré car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le descripteur n'a pas été récupéré car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @note La structure \ref T_mkHCDDevice supporte uniquement une configuration. Si l'interface possède plusieurs interfaces avec la même classe, alors
 *       la première interface trouvée est renvoyée.
 *
 */

T_mkCode mk_hcd_getSpecialDesciptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkHCDInterfaceDescriptor* p_interface, T_mkAddr p_buf, uint32_t p_register );

/**
 * @fn T_mkCode mk_hcd_setDeviceConfiguration ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction active la première configuration d'un périphérique.
 *
 * @param[in]      p_device Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe   Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la configuration a été activée.
 *         \li \ref K_MK_ERROR_PARAM   : la configuration n'a pas été activée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la configuration n'a pas été activée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la configuration n'a pas été activée car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : la configuration n'a pas été activée car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_setDeviceConfiguration ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_setInterface ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint16_t p_interface, uint16_t p_alternateSetting );
 * @brief Cette fonction active une interface alternative d'une configuration.
 *
 * @param[in]      p_device           Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe             Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_interface        Ce paramètre contient le numéro de l'interface primaire.
 * @param[in]      p_alternateSetting Ce paramètre contient le numéro de l'interface alternative.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'interface alternative a été activée.
 *         \li \ref K_MK_ERROR_PARAM   : l'interface alternative n'a pas été activée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'interface alternative n'a pas été activée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'interface alternative n'a pas été activée car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : l'interface alternative n'a pas été activée car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_setInterface ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint16_t p_interface, uint16_t p_alternateSetting );

/**
 * @fn T_mkCode mk_hcd_setFeature ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint16_t p_value, uint16_t p_index );
 * @brief Cette fonction active une feature d'un périphérique.
 *
 * @param[in]      p_device Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe   Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_value  Ce paramètre contient la valeur de la feature.
 * @param[in]      p_index  Ce paramètre contient l'index de la feature.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la feature a été activée.
 *         \li \ref K_MK_ERROR_PARAM   : la feature n'a pas été activée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la feature n'a pas été activée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la feature n'a pas été activée car le périphérique cible n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : la feature n'a pas été activée car une erreur de communication s'est produite. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_setFeature ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint16_t p_value, uint16_t p_index );

/**
 *
 */

#endif


