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
* @file mk_termio_constants.h
* @brief Déclaration des constantes dédiées aux terminaux d'entrées-sorties.
* @date 9 juin 2019
*
*/

#ifndef MK_TERMIO_CONSTANTS_H
#define MK_TERMIO_CONSTANTS_H

/**
 * @def K_MK_TERMIO_NUMBER
 * @brief Définition du nombre de terminaux pouvant être alloués dynamiquement.
 */

#define K_MK_TERMIO_NUMBER 15

/**
 * @def K_MK_TERMIO_TASK_PRIORITY
 * @brief Définition de la priorité des tâches dédiées au terminaux.
 */

#define K_MK_TERMIO_TASK_PRIORITY 2

/**
 *
 */

/**
 * @def K_MK_TERMIO_USB_OTGHS_PRIORITY
 * @brief Définition de la priorité de l'interruption USB_OTGHS.
 */

#define K_MK_TERMIO_USB_OTGHS_PRIORITY 13

/**
 * @def K_MK_TERMIO_USB_OTGFS_PRIORITY
 * @brief Définition de la priorité de l'interruption USB_OTGFS.
 */

#define K_MK_TERMIO_USB_OTGFS_PRIORITY 13

/**
 * @def K_MK_TERMIO_USB_OTGFS_PRIORITY
 * @brief Définition de la priorité de l'interruption MMC.
 */

#define K_MK_TERMIO_MMC_PRIORITY 13

/**
 * @def K_MK_TERMIO_I2C_EVENT_PRIORITY
 * @brief Définition de la priorité de l'interruption I2C.
 */

#define K_MK_TERMIO_I2C_EVENT_PRIORITY 13

/**
 * @def K_MK_TERMIO_USB_OTGFS_PRIORITY
 * @brief Définition de la priorité de l'interruption d'erreur I2C.
 */

#define K_MK_TERMIO_I2C_ERROR_PRIORITY 13

/**
 *
 */

/**
 * @def K_MK_TERMIO_INIT_TIMEOUT
 * @brief Définition du timeout d'initialisation des terminaux.
 */

#define K_MK_TERMIO_INIT_TIMEOUT 10000

/**
 *
 */

#endif

