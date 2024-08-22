/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_display_application_constants.h
* @brief Déclaration des constantes dédiées au module 'Application'.
* @date 17 août 2023
*
*/

#ifndef MK_DISPLAY_APPLICATION_CONSTANTS_H
#define MK_DISPLAY_APPLICATION_CONSTANTS_H

/**
 * @def K_MK_DISPLAY_APPLICATION_ELAPSE_TIMEOUT
 * @brief Définition de la durée du timeout de destruction des applications [en frame].
 */

#define K_MK_DISPLAY_APPLICATION_ELAPSE_TIMEOUT 1

/**
 *
 */

/**
 * @def K_MK_DISPLAY_APPLICATION_DEFAULT_PRIORITY
 * @brief Définition de l'identifiant par défaut des applications. \n
 */

#define K_MK_DISPLAY_APPLICATION_BASE_ID 0x1000

/**
 * @def K_MK_DISPLAY_APPLICATION_DEFAULT_PRIORITY
 * @brief Définition de la priorité par défaut des applications. \n
 */

#define K_MK_DISPLAY_APPLICATION_DEFAULT_PRIORITY 1

/**
 * @def K_MK_DISPLAY_APPLICATION_NUMBER
 * @brief Définition du nombre de structures \ref T_mkApplication pouvant être allouées dynamiquement.
 */

#define K_MK_DISPLAY_APPLICATION_NUMBER 16

/**
 * @def K_MK_DISPLAY_APPLICATION_AREA_SIZE
 * @brief Définition de la taille de la pool dédiée à l'allocation dynamique des structures \ref T_mkApplication.
 */

#define K_MK_DISPLAY_APPLICATION_AREA_SIZE ( sizeof ( T_mkApplication ) * K_MK_DISPLAY_APPLICATION_NUMBER )

/**
 * @def K_MK_DISPLAY_APPLICATION_AREA_SIZE
 * @brief Définition de la taille de la pool dédiée à l'allocation dynamique des structures \ref T_mkApplicationGarbageItem.
 */

#define K_MK_DISPLAY_GARBAGE_APPLICATION_AREA_SIZE ( sizeof ( T_mkApplicationGarbageItem ) * K_MK_DISPLAY_APPLICATION_NUMBER )

/**
 *
 */

/**
 * @def K_MK_DISPLAY_APPLICATION_START_ADDR
 * @brief Définition de l'adresse de début de la zone mémoire permettant le déploiement des applications externes.
 */


#define K_MK_DISPLAY_APPLICATION_START_ADDR ( K_MK_DISPLAY_FRAME_BUFFER_BANK1_BASE_ADDR + ( 2 * K_MK_DISPLAY_FRAME_BUFFER_NUMBER * K_MK_DISPLAY_FRAME_BUFFER_SIZE ) )

/**
 * @def K_MK_DISPLAY_APPLICATION_MEMORY_SIZE
 * @brief Définition de la taille de la zone mémoire permettant le déploiement des applications externes [en octets].
 *
 */

#define K_MK_DISPLAY_APPLICATION_MEMORY_SIZE ( K_MK_DISPLAY_FRAME_BUFFER_SIZE * 4 )

/**
 * @def K_MK_DISPLAY_APPLICATION_PAGE_SIZE
 * @brief Définition de la taille des pages mémoires où les applications dynamiques sont déployées [en octets].
 */


#define K_MK_DISPLAY_APPLICATION_PAGE_SIZE 0x10000

/**
 *
 */

/**
 * @def K_MK_DISPLAY_APPLICATION_ARGV_SIZE
 * @brief Définition de la taille [en multiple de mots 32bits] de la zone permettant de stocker
 *        les arguments d'une application exécutée en ligne de commande.
 */

#define K_MK_DISPLAY_APPLICATION_ARGV_SIZE 256

/**
 * @def K_MK_DISPLAY_APPLICATION_DYNAMICHEADER_MAGICNUMBER
 * @brief Définition de la valeur du magicNumber d'une entête d'application dynamique. \n
 */

#define K_MK_DISPLAY_APPLICATION_DYNAMICHEADER_MAGICNUMBER 0x44594E41

/**
 *
 */

#endif

