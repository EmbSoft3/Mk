/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_display_bmp_constants.h
* @brief Déclaration des constantes dédiées au module 'BMP'.
* @date 2 oct. 2022
*
*/

#ifndef MK_DISPLAY_BMP_CONSTANTS_H
#define MK_DISPLAY_BMP_CONSTANTS_H

/**
 * @def K_MK_BMP_SIGNATURE
 * @brief Cette constante définit la signature d'un fichier BMP.
 */

#define K_MK_BMP_SIGNATURE 0x4D42

/**
 * @def K_MK_BMP_PIXEL_TABLE_SIZE
 * @brief Définition de la taille de la table permettant de charger un bitmap 24bits en mémoire.
 *        Cette table définit la taille des requêtes de lecture effectuées.
 *        Elle doit être strictement supérieure à 1 pixel.
 */

#define K_MK_BMP_PIXEL_TABLE_SIZE 480

/**
 * @def K_MK_BMP_HEADER_SIZE
 * @brief Définition de la taille de la première entête du bitmap [en octet].
 */

#define K_MK_BMP_HEADER_SIZE 0x0E

/**
 * @def K_MK_BMP_HEADER_WIN1
 * @brief Définition de l'identifiant d'une entête de type WIN1.
 */

#define K_MK_BMP_HEADER_WIN1 0x0000

/**
 * @def K_MK_BMP_HEADER_WIN2_OS2V1
 * @brief Définition de l'identifiant d'une entête de type OS2V1.
 */

#define K_MK_BMP_HEADER_WIN2_OS2V1 0x000C

/**
 * @def K_MK_BMP_HEADER_OS2V2_TINY
 * @brief Définition de l'identifiant d'une entête de type OS2V2_TINY.
 */

#define K_MK_BMP_HEADER_OS2V2_TINY 0x0010

/**
 * @def K_MK_BMP_HEADER_OS2V2
 * @brief Définition de l'identifiant d'une entête de type OS2V2.
 */

#define K_MK_BMP_HEADER_OS2V2 0x0040

/**
 * @def K_MK_BMP_HEADER_WIN3V1
 * @brief Définition de l'identifiant d'une entête de type WIN3V1.
 */

#define K_MK_BMP_HEADER_WIN3V1 0x0028

/**
 * @def K_MK_BMP_HEADER_WIN3V2
 * @brief Définition de l'identifiant d'une entête de type WIN3V2.
 */

#define K_MK_BMP_HEADER_WIN3V2 0x0034

/**
 * @def K_MK_BMP_HEADER_WIN3V3
 * @brief Définition de l'identifiant d'une entête de type WIN3V3.
 */

#define K_MK_BMP_HEADER_WIN3V3 0x0038

/**
 * @def K_MK_BMP_HEADER_WIN4
 * @brief Définition de l'identifiant d'une entête de type WIN4.
 */

#define K_MK_BMP_HEADER_WIN4 0x006C

/**
 * @def K_MK_BMP_HEADER_WIN5
 * @brief Définition de l'identifiant d'une entête de type WIN5.
 */

#define K_MK_BMP_HEADER_WIN5 0x007C

/**
 *
 */

/**
 * @def K_MK_BMP_COMPRESSION_RGB
 * @brief Définition de l'identifiant indiquant que le bitmap n'est pas compressé.
 */

#define K_MK_BMP_COMPRESSION_RGB 0x0000

/**
 * @def K_MK_BMP_COMPRESSION_BITFIELDS
 * @brief Définition de l'identifiant indiquant que le bitmap est compressé avec la méthode BITFIELD.
 */

#define K_MK_BMP_COMPRESSION_BITFIELDS 0x0003

/**
 * @def K_MK_BMP_COMPRESSION_ALPHABITFIELDS
 * @brief Définition de l'identifiant indiquant que le bitmap est compressé avec la méthode ALPHA_BITFIELD.
 */

#define K_MK_BMP_COMPRESSION_ALPHABITFIELDS 0x0006

/**
 *
 */

/**
 * @def K_MK_BMP_LCS_CALIBRATED_RGB
 * @brief Définition de l'identifiant indiquant un espace de couleur RGB.
 */

#define K_MK_BMP_LCS_CALIBRATED_RGB 0x0000

/**
 *
 */

#endif

