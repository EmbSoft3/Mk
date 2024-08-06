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
* @file mk_loader_srec_constants.h
* @brief Déclaration des constantes dédiées aux chargements des fichiers de programmation SREC.
* @date 20 déc. 2023
*
*/

#ifndef MK_LOADER_SREC_CONSTANTS_H
#define MK_LOADER_SREC_CONSTANTS_H

/**
 * @def K_MK_LOADER_SREC_FILEBUFSIZE
 * @brief Définition de la taille du buffer dédié au décodage des fichiers ".srec".
 */

#define K_MK_LOADER_SREC_FILEBUFSIZE 512

/**
 * @def K_MK_LOADER_SREC_RECORD_MAX_SIZE
 * @brief Définition de la taille maximale d'un record [en octets].
 *        Elle est définie de la manière suivante : Type<2> + ByteCount<2> + Addr_data <2*255> + Fin<2>
 */

#define K_MK_LOADER_SREC_RECORD_MAX_SIZE 516

/**
 *
 */

/**
 * @def K_MK_LOADER_SREC_MINIMAL_BYTE_COUNT
 * @brief Définition du nombre de données minimales présentes dans un record (address, data et checksum).
 *        Elle est définie de la manière suivante : 2 pour les adresses 16bits, 1 pour le checksum.
 */

#define K_MK_LOADER_SREC_MINIMAL_BYTE_COUNT 3

/**
 *
 */

/**
 * @def K_MK_LOADER_SREC_OFFSET_TYPE_FIELD
 * @brief Définition de l'offset du champ 'Type' dans un 'Record'.
 */

#define K_MK_LOADER_SREC_OFFSET_TYPE_FIELD 1

/**
 * @def K_MK_LOADER_SREC_OFFSET_BYTECOUNT_FIELD
 * @brief Définition de l'offset du champ 'ByteCount' dans un 'Record'.
 */

#define K_MK_LOADER_SREC_OFFSET_BYTECOUNT_FIELD 2

/**
 * @def K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD
 * @brief Définition de l'offset du champ 'Address' dans un 'Record'.
 */

#define K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD 4

/**
 *
 */

#endif


