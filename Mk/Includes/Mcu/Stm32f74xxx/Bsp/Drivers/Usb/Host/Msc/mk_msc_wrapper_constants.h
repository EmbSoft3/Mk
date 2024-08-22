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
* @file mk_msc_wrapper_constants.h
* @brief Déclaration des constantes dédiées aux wrappers des périphériques de stockage.
* @date 18 mai 2020
*
*/

#ifndef MK_MSC_WRAPPER_CONSTANTS_H
#define MK_MSC_WRAPPER_CONSTANTS_H

/**
 * @def K_MK_MSC_WRAPPER_SIZE
 * @brief Définition de la taille d'une structure de type \ref T_mkMSCCommandBlockWrapper [en multiple de mots 32 bits].
 */

#define K_MK_MSC_WRAPPER_SIZE 0x8

/**
 * @def K_MK_MSC_CMD_MAXIMUM_SIZE
 * @brief Définition de la taille maximale [en octets] d'une commande.
 */

#define K_MK_MSC_CMD_MAXIMUM_SIZE 0x10

/**
 * @def K_MK_MSC_CMD_BLOC_WRAPPER_SIZE
 * @brief Définition de la taille [en octets] d'un 'CommandBlocWrapper'.
 */

#define K_MK_MSC_CMD_BLOC_WRAPPER_SIZE 0x1F

/**
 * @def K_MK_MSC_CMD_STATUS_WRAPPER_SIZE
 * @brief Définition de la taille [en octets] d'un 'CommandStatusWrapper'.
 */

#define K_MK_MSC_CMD_STATUS_WRAPPER_SIZE 0x0D

/**
 *
 */

/**
 * @def K_MK_MSC_CMD_BLOC_WRAPPER_SIGNATURE
 * @brief Définition de la signature d'un 'CommandBlocWrapper'.
 */

#define K_MK_MSC_CMD_BLOC_WRAPPER_SIGNATURE 0x43425355

/**
 * @def K_MK_MSC_CMD_STATUS_WRAPPER_SIGNATURE
 * @brief Définition de la signature d'un 'CommandStatusWrapper'.
 */

#define K_MK_MSC_CMD_STATUS_WRAPPER_SIGNATURE 0x53425355

/**
 *
 */

#endif

