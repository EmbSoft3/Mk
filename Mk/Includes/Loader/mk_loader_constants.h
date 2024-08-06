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
* @file mk_loader_constants.h
* @brief Déclaration des constantes dédiées aux chargements des programmes et des bibliothèques externes.
* @date 14 janv. 2024
*
*/

#ifndef MK_LOADER_CONSTANTS_H
#define MK_LOADER_CONSTANTS_H

/**
 * @def K_MK_LOADER_MEMORY_PAGE_SIZE
 * @brief Définition de taille des pages mémoire utilisées pour charger les applications dynamiques [en octets].
 */

#define K_MK_LOADER_MEMORY_PAGE_SIZE K_MK_PAGE_SRAM_BLOCK_SIZE

/**
 * @def K_MK_LOADER_LIBRARY_ITEM_NUMBER
 * @brief Définition du nombre maximal de bibliothèques externes pouvant être chargées en mémoire.
 *        Les bibliothéques sont chargées dans des pages mémoire de taille \ref K_MK_LOADER_MEMORY_PAGE_SIZE octets.
 *
 */

#define K_MK_LOADER_LIBRARY_ITEM_NUMBER 16

/**
 *
 */

/**
 * @def K_MK_LOADER_MAGIC_NUMBER
 * @brief Définition du MagicNumber présent dans l'entête d'une application dynamique.
 */

#define K_MK_LOADER_MAGIC_NUMBER 0x53594D42

/**
 * @def K_MK_LOADER_MAGIC_NUMBER
 * @brief Définition de la taille minimale de l'entête d'une application dynamique.
 */

#define K_MK_LOADER_MINIMAL_SIZE 40

/**
 *
 */

#endif


