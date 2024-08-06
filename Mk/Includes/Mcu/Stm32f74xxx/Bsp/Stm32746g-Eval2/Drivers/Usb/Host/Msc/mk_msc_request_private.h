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
* @file mk_msc_request_private.h
* @brief Déclaration des fonctions privées dédiées aux requêtes des périphériques de stockage.
* @date 18 mai 2020
*
*/

#ifndef MK_MSC_REQUEST_PRIVATE_H
#define MK_MSC_REQUEST_PRIVATE_H

/**
 * @fn T_mkCode mk_msc_reset ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction réinitialise un périphérique MSC et ses interfaces.
 *
 * @param[in] p_mscDevice Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[in] p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le périphérique MSC a été réinitialisé.
 *         \li \ref K_MK_ERROR_PARAM   : le périphérique MSC n'a pas été réinitialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le périphérique MSC n'a pas été réinitialisé car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : le périphérique MSC n'a pas été réinitialisé car une erreur de communication s'est produite.
 */

T_mkCode mk_msc_reset ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_msc_getMaxLUN ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe, uint8_t* p_numberOfLUN );
 * @brief Cette fonction récupére le nombre d'unité logique d'un périphérique MSC.
 *
 * @param[in, out] p_mscDevice   Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[in]      p_pipe        Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[out]     p_numberOfLUN Ce paramètre contient le nombre d'unité logique. Il évolue entre [0 et 15].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le nombre d'unité logique a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le nombre d'unité logique n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le nombre d'unité logique n'a pas été récupéré car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : le nombre d'unité logique n'a pas été récupéré car une erreur de communication s'est produite.
 */

T_mkCode mk_msc_getMaxLUN ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe, uint8_t* p_numberOfLUN );

/**
 * @fn T_mkCode mk_msc_clearHaltFeature ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe, T_mkHCDEndpointDescriptor* p_endpoint );
 * @brief Cette fonction réinitialise une terminaison d'un périphérique MSC. Elle doit être appelée lorsqu'un statut de type 'HALT' est rencontré.
 *
 * @param[in, out] p_mscDevice Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[in]      p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[out]     p_endpoint  Ce paramètre contient l'adresse de la terminaison à réinitialiser.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la terminaison a été réinitialisée.
 *         \li \ref K_MK_ERROR_PARAM   : la terminaison n'a pas été réinitialisée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la terminaison n'a pas été réinitialisée car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la terminaison n'a pas été réinitialisée car une erreur de communication s'est produite.
 */

T_mkCode mk_msc_clearHaltFeature ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe, T_mkHCDEndpointDescriptor* p_endpoint );

/**
 * @fn T_mkCode mk_msc_post ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe, T_mkMSCCommandBlockWrapper* p_cbw, T_mkMSCCommandStatusWrapper* p_csw, T_mkAddr p_buf )
 * @brief Cette fonction poste une commande encapsulée dans un 'Wrapper' sur le bus USB. L'identifiant et les caractéristiques de la commande doivent être stockés
 *        dans une structure de type \ref T_mkMSCCommandBlockWrapper.
 *
 * @param[in]      p_mscDevice Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[in]      p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_cbw       Ce paramètre contient l'adresse d'un wrapper de type \ref T_mkMSCCommandBlockWrapper.
 * @param[out]     p_csw       Ce paramètre contient l'adresse de la structure de statut.
 * @param[in, out] p_buf       Ce paramètre contient l'adresse du buffer de données.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande a été postée.
 *         \li \ref K_MK_ERROR_PARAM   : la commande n'a pas été postée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande n'a pas été postée car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la commande n'a pas été postée car une erreur de communication s'est produite .
 */

T_mkCode mk_msc_post ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe, T_mkMSCCommandBlockWrapper* p_cbw, T_mkMSCCommandStatusWrapper* p_csw, T_mkAddr p_buf );

/**
 *
 */

#endif

