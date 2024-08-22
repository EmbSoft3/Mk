/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_qspi.h
* @brief Déclaration des fonctions publiques dédiées à la mémoire QSPI.
* @date 9 août 2024
*
*/

#ifndef MK_QSPI_H
#define MK_QSPI_H

/**
 * @fn T_mkCode mk_qspi_getMode ( uint32_t* p_mode );
 * @brief Cette fonction retourne le mode de fonctionnement de la mémoire QSPI.
 *
 * @param[out] p_mode Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                    Une des constante suivante peut être retournée :
 *                   \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la récupération du mode de fonctionnement a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la récupération du mode de fonctionnement a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : la récupération du mode de fonctionnement a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_getMode ( uint32_t* p_mode );

/**
 * @fn T_mkCode mk_qspi_setDummyCycle ( uint32_t p_mode, uint32_t p_dummyCycles );
 * @brief Cette fonction configure le nombre de cycles d'horloge insérés après chaque instruction de type 'FAST READ'.
 *
 * @param[in] p_mode        Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                          Une des constante suivante peut être utilisée :
 *                   \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 * @param[in] p_dummyCycles Ce paramètre contient le nombre de cycles d'horloge. Il évolue de [0 à 14].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la configuration a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la configuration a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : la configuration a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_setDummyCycle ( uint32_t p_mode, uint32_t p_dummyCycles );

/**
 * @fn T_mkCode mk_qspi_enableExtendedMode ( uint32_t p_mode );
 * @brief Cette fonction active le mode d'adressage étendu (32bits).
 *
 * @param[in] p_mode Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                   Une des constante suivante peut être utilisée :
 *                   \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'activation du mode étendu a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'activation du mode étendu a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'activation du mode étendu a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_enableExtendedMode ( uint32_t p_mode );

/**
 * @fn T_mkCode mk_qspi_disableExtendedMode ( uint32_t p_mode );
 * @brief Cette fonction désactive le mode d'adressage étendu (32bits).
 *
 * @param[in] p_mode Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                   Une des constante suivante peut être utilisée :
 *                   \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la désactivation du mode étendu a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la désactivation du mode étendu a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : la désactivation du mode étendu a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_disableExtendedMode ( uint32_t p_mode );

/**
 * @fn T_mkCode mk_qspi_erase ( uint32_t p_mode, uint32_t p_addr );
 * @brief Cette fonction efface un secteur de la mémoire QSPI. La taille et le nombre de secteurs sont définies par
 *        les constantes \ref K_MK_MICRON_N25Q512A_SECTOR_SIZE et \ref K_MK_MICRON_N25Q512A_SECTOR_NUMBER.
 *
 * @param[in] p_mode Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                   Une des constante suivante peut être utilisée :
 *                   \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 * @param[in] p_addr Ce paramètre contient l'adresse du secteur à effacer.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'effacement du secteur a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'effacement du secteur a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'effacement du secteur a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_erase ( uint32_t p_mode, uint32_t p_addr );

/**
 * @fn T_mkCode mk_qspi_eraseChip ( uint32_t p_mode );
 * @brief Cette fonction efface l'intégralité de la mémoire QSPI.
 *
 * @param[in] p_mode Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                   Une des constante suivante peut être utilisée :
 *                   \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'effacement de la mémoire a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'effacement de la mémoire a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'effacement de la mémoire a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_eraseChip ( uint32_t p_mode );

/**
 * @fn T_mkCode mk_qspi_writePage ( uint32_t p_mode, uint32_t p_addr, uint8_t* p_buf, uint16_t p_bufLength );
 * @brief Cette fonction écrit une page de la mémoire QSPI. Celle-ci doit préalablement avoir été effacée.
 *        La taille d'une page est définie par la constante \ref K_MK_MICRON_N25Q512A_PAGE_SIZE.
 *
 * @param[in] p_mode      Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                        Une des constante suivante peut être utilisée :
 *                        \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 * @param[in] p_addr      Ce paramètre contient l'adresse de la page à écrire.
 * @param[in] p_buf       Ce paramètre contient l'adresse du buffer de données à écrire dans la page.
 * @param[in] p_bufLength Ce paramètre contient la taille du buffer de données. Il évolue de [1 à \ref K_MK_MICRON_N25Q512A_PAGE_SIZE].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'écriture de la page mémoire a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'écriture de la page mémoire a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'écriture de la page mémoire a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'écriture de la page mémoire a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_writePage ( uint32_t p_mode, uint32_t p_addr, uint8_t* p_buf, uint16_t p_bufLength );

/**
 *
 */

#endif

