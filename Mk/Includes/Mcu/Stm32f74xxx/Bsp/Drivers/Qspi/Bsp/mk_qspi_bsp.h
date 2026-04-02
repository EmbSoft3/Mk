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
* @file mk_qspi_bsp.h
* @brief Déclaration des fonctions dédiées aux BSP du périphérique QSPI.
* @date 23 mars 2026
*
*/

#ifndef MK_QSPI_BSP_H
#define MK_QSPI_BSP_H

/**
 * @fn T_mkCode mk_qspi_bsp_init ( uint32_t p_mode );
 * @brief Cette fonction initialise le BSP du périphérique QSPI.
 *
 * @param[in] p_mode Ce paramètre indique si la mémoire doit être initialisée en mode 1 fil
 *                   (\ref K_QSPI_INSTRUCTION_SINGLE_MODE) ou 4 fils (\ref K_QSPI_INSTRUCTION_QUAD_MODE).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'initialisation de la mémoire a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'initialisation de la mémoire a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'initialisation de la mémoire a échoué car le bus QSPI n'est pas disponible.
 * 
 */

T_mkCode mk_qspi_bsp_init ( uint32_t p_mode );

/**
 *
 */

#endif
