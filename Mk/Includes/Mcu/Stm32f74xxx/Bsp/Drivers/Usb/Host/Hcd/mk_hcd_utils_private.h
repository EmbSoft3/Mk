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
* @file mk_hcd_utils_private.h
* @brief Déclaration des fonctions utilitaires dédiées à l'USB.
* @date 11 oct. 2019
*
*/

#ifndef MK_HCD_UTILS_PRIVATE_H
#define MK_HCD_UTILS_PRIVATE_H

/**
 * @fn T_mkCode mk_hcd_setAddress ( T_mkHCDDevice* p_device );
 * @brief Cette fonction configure l'adresse 7bits d'un périphérique USB.
 * @param[in, out] p_device Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : l'adresse USB a été configurée.
 *         \li \ref K_MK_ERROR_PARAM : l'adresse USB n'a pas été configurée car le paramètre est invalide.
 */

T_mkCode mk_hcd_setAddress ( T_mkHCDDevice* p_device );

/**
 * @fn T_mkCode mk_hcd_getAddress ( T_mkHCDDevice* p_device, uint8_t* p_address );
 * @brief Cette fonction retourne l'adresse 7bits d'un périphérique USB.
 *
 * @param[in]  p_device  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[out] p_address Ce paramètre contient l'adresse du périphérique USB sur 7bits.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée correctement. L'adresse est présente dans le paramètre p_address.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas exécutée correctement car au moins un paramètre est invalide.
 */

T_mkCode mk_hcd_getAddress ( T_mkHCDDevice* p_device, uint8_t* p_address );

/**
 * @fn T_mkCode mk_hcd_searchEndpoint ( T_mkHCDInterfaceDescriptor* p_interface, T_mkHCDEndpointDescriptor** p_endpoint, uint32_t p_type, uint32_t p_direction );
 * @brief Cette fonction retourne l'adresse de la première terminaison ayant le type et la direction spécifiée en paramètre.
 *
 * @param[in]  p_interface Ce paramètre contient l'adresse de l'interface dont les terminaisons doivent être analysées.
 * @param[out] p_endpoint  Ce paramètre contient l'adresse de la terminaison trouvée ou la valeur \ref K_MK_NULL si aucune terminaison n'a été trouvée.
 * @param[in]  p_type      Ce paramètre contient le type de la terminaison recherchée. Les constantes suivantes peuvent être utilisées :\n
 *                         \ref K_USB_CONTROL_ENDPOINT, \ref K_USB_ISOCHRONOUS_ENDPOINT, \ref K_USB_BULK_ENDPOINT et \ref K_USB_INTERRUPT_ENDPOINT
 * @param[in]  p_direction Ce paramètre contient la direction de la terminaison recherchée. Les constants suivantes peuvent être utilisées :\n
 *                         \ref K_USB_OUT_ENDPOINT et \ref K_USB_IN_ENDPOINT
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée correctement. Le résultat de la recherche est présent dans le paramètre 'p_endpoint'.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas exécutée correctement car au moins un paramètre est invalide.
 */

T_mkCode mk_hcd_searchEndpoint ( T_mkHCDInterfaceDescriptor* p_interface, T_mkHCDEndpointDescriptor** p_endpoint, uint32_t p_type, uint32_t p_direction );

/**
 * @fn uint32_t mk_hcd_getTimeRemaining ( T_mkHCDDevice* p_device, uint32_t p_timeout );
 * @brief Cette fonction indique si l'intervalle de rafraichissement d'une terminaison est terminé ou non. Si oui, elle réintialise
 *        la temporisation.
 *
 * @param[in]  p_device   Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in]  p_endpoint Ce paramètre contient l'adresse d'une terminaison USB de type \ref T_mkHCDEndpointDescriptor.
 * @param[out] p_timeout  Ce paramètre contient la valeur de l'intervalle de repos [en ms].
 *
 * @return Cette fonction retourne la valeur nulle si l'intervalle de rafraichissement est terminé, sinon une valeur non
 *         nulle.
 */

uint32_t mk_hcd_getTimeRemaining ( T_mkHCDDevice* p_device, T_mkHCDEndpointDescriptor* p_endpoint, uint32_t p_timeout );

/**
 *
 */

#endif


