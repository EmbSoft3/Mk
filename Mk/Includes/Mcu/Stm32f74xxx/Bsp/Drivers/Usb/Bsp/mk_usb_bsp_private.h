/**
*
* @copyright Copyright (C) 2026 RENARD Mathieu. All rights reserved.
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
* @file mk_usb_bsp_private.h
* @brief Déclaration des fonctions privées dédiées aux BSP USB.
* @date 18 mars 2026
*
*/

#ifndef MK_USB_BSP_PRIVATE_H
#define MK_USB_BSP_PRIVATE_H

/**
 * @fn T_mkCode mk_usb_bsp_init ( T_mkAddr p_usb );
 * @brief Cette fonction initialise le BSP SD/MMC.
 * @param[in] p_usb Ce paramètre contient l'adresse de base d'un périphérique USB. Les constantes suivantes peuvent
 *                  être utilisés : \n \ref K_USB_OTGHS et \ref K_USB_OTGFS
 * 
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'initialisation du BSP a été exécutée sans renconter d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : l'initialisation du BSP a échouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'initialisation du BSP a échouée car la messagerie GPIO est pleine.
 *         \li \ref K_MK_ERROR_ISR     : l'initialisation du BSP a échouée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM    : l'initialisation du BSP a échouée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'initialisation du BSP a échouée car un timeout de communication s'est produit.
 *         \li \ref K_MK_ERROR_RIGHT   : l'initialisation du BSP a échouée car une tâche non privilégiée ne peut pas modifier une broche protégée.
 *
 */

T_mkCode mk_usb_bsp_init ( T_mkAddr p_usb );

/**
 *
 */

#endif
