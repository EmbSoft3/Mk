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
* @file mk_hcd_device_constants.h
* @brief Déclaration des constantes dédiées aux périphériques USB.
* @date 12 oct. 2019
*
*/

#ifndef MK_HCD_DEVICE_CONSTANTS_H
#define MK_HCD_DEVICE_CONSTANTS_H

/**
 * @def K_MK_HCD_DEVICE_DESCRIPTOR_SIZE
 * @brief Définition de la taille d'un descripteur de périphérique [en octets].
 */

#define K_MK_HCD_DEVICE_DESCRIPTOR_SIZE 18

/**
 * @def K_MK_HCD_DEVICE_QUALIFIER_SIZE
 * @brief Définition de la taille d'un qualificateur de périphérique [en octets].
 */

#define K_MK_HCD_DEVICE_QUALIFIER_SIZE 10

/**
 * @def K_MK_HCD_CONFIGURATION_DESCRIPTOR_SIZE
 * @brief Définition de la taille de l'entête d'un descripteur de configuration [en octets].
 */

#define K_MK_HCD_CONFIGURATION_DESCRIPTOR_SIZE 9

/**
 * @def K_MK_HCD_STRING_DESCRIPTOR_SIZE
 * @brief Définition de la taille de l'entête du descripteur unicode [en octets].
 */

#define K_MK_HCD_STRING_DESCRIPTOR_SIZE 2

/**
 * @def K_MK_HCD_INTEFACE_DESCRIPTOR_SIZE
 * @brief Définition de la taille d'un descripteur d'interface [en octets].
 */

#define K_MK_HCD_INTEFACE_DESCRIPTOR_SIZE 9

/**
 * @def K_MK_HCD_ENDPOINT_DESCRIPTOR_SIZE
 * @brief Définition de la taille d'un descripteur de terminaison [en octets].
 */

#define K_MK_HCD_ENDPOINT_DESCRIPTOR_SIZE 7

/**
 * @def K_MK_HCD_AUDIO_ENDPOINT_DESCRIPTOR_SIZE
 * @brief Définition de la taille d'un descripteur de terminaison audio [en octets].
 */

#define K_MK_HCD_AUDIO_ENDPOINT_DESCRIPTOR_SIZE 9

/**
 * @def K_MK_HCD_DEVICE_STATUS_SIZE
 * @brief Définition de la taille du registre de statut du périphérique [en octets].
 */

#define K_MK_HCD_DEVICE_STATUS_SIZE 2

/**
 * @def K_MK_HCD_LANGID_SIZE
 * @brief Définition de la taille de l'identifiant des langages [en octets].
 */

#define K_MK_HCD_LANGID_SIZE 2

/**
 *
 */

#endif



