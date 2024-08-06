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
* @file mk_display_bmp_types.h
* @brief Déclaration des types dédiés au module 'BMP'.
* @date 2 oct. 2022
* @note https://www.fileformat.info/format/bmp/egff.htm
*
*/

#ifndef MK_DISPLAY_BMP_TYPES_H
#define MK_DISPLAY_BMP_TYPES_H

/**
 * @struct T_mkBMPFile
 * @brief Déclaration de la structure T_mkBMPFile.
 */

typedef struct T_mkBMPFile T_mkBMPFile;
struct T_mkBMPFile
{
   T_mkFile* file;                              /*!< Ce membre contient l'instance d'un fichier de type T_mkFile. */
   T_mkAddr baseAddr;                           /*!< Ce membre contient l'adresse mémoire où le bitmap a été déployé. */
   uint32_t type;                               /*!< Ce membre contient le type du bitmap \ref K_MK_BMP_HEADER_WIN1 à \ref K_MK_BMP_HEADER_WIN5. */
   uint32_t width;                              /*!< Ce membre contient la largeur du bitmap [en pixel]. */
   uint32_t height;                             /*!< Ce membre contient la hauteur du bitmap [en pixel]. */
   uint32_t topDownRowOrder;                    /*!< Ce membre contient le mode de dessin du bitmap (0->haut vers bas, 1->bas vers haut). */
   uint32_t imageSize;                          /*!< Ce membre contient la taille de l'image [en octets]. */
   uint32_t bitsPerPixel;                       /*!< Ce membre contient le nombre de bits par pixel dans le bitmap. */
   uint32_t compression;                        /*!< Ce membre contient le type de compression du bitmap. */
   uint32_t pixelArray;                         /*!< Ce membre contient l'offset du bitmap de données dans le fichier. */
};

/**
 * @struct T_mkBMPFileHeader
 * @brief Déclaration de la structure T_mkBMPFileHeader (BITMAPCOREHEADER).
 */

typedef struct T_mkBMPFileHeader T_mkBMPFileHeader;
struct T_mkBMPFileHeader
{
   uint16_t fileType;                           /*!< Ce membre contient la signature du fichier (\ref K_MK_BMP_SIGNATURE). */
   uint16_t lowFileSize;                        /*!< Ce membre contient la taille du fichier bitmap (poids faible). */
   uint16_t highFileSize;                       /*!< Ce membre contient la taille du fichier bitmap (poids fort). */
   uint16_t appsRsv1;                           /*!< Réservé. */
   uint16_t appsRsv2;                           /*!< Réservé. */
   uint16_t lowBitmapArrayOffset;               /*!< Ce membre contient l'offset du bitmap de données dans le fichier (poids faible). */
   uint16_t highBitmapArrayOffset;              /*!< Ce membre contient l'offset du bitmap de données dans le fichier (poids fort). */
   uint16_t lowHeaderSize;                      /*!< Ce membre contient la taille de la prochaine entête du bitmap (poids faible) - */
   uint16_t highHeaderSize;                     /*!< Ce membre contient la taille de la prochaine entête du bitmap (poids fort). */
   uint16_t padding;                            /*!< Padding. */
};

/**
 * @struct T_mkBMPRGBAMask
 * @brief Déclaration de la structure T_mkBMPRGBAMask.
 */

typedef struct T_mkBMPRGBAMask T_mkBMPRGBAMask;
struct T_mkBMPRGBAMask
{
   uint32_t red;                                /*!< Ce membre contient la composante rouge du masque. */
   uint32_t green;                              /*!< Ce membre contient la composante vert du masque. */
   uint32_t blue;                               /*!< Ce membre contient la composante bleu du masque. */
   uint32_t alpha;                              /*!< Ce membre contient la composante alpha du masque. */
};

/**
 * @struct T_mkBMPImageHeader
 * @brief Déclaration de la structure T_mkBMPImageHeader (OS22XBITMAPHEADER).
 */

typedef struct T_mkBMPImageHeader T_mkBMPImageHeader;
struct T_mkBMPImageHeader
{
   uint32_t headerSize;                         /*!< Ce membre contient la taille de cette entête (\ref K_MK_BMP_HEADER_WIN1 à \ref K_MK_BMP_HEADER_WIN5). */
   int32_t width;                               /*!< Ce membre contient la largeur du bitmap [en pixel]. */
   int32_t height;                              /*!< Ce membre contient la hauteur du bitmap [en pixel]. */
   uint16_t planes;                             /*!< Ce membre contient le nombre de plans (doit être 1). */
   uint16_t bitsPerPixel;                       /*!< Ce membre contient le nombre de bits par pixel (1, 4, 8, 16, 24 et 32). */
   uint32_t compression;                        /*!< Ce membre contient la méthode de compression utilisée (\ref K_MK_BMP_COMPRESSION_RGB, \ref K_MK_BMP_COMPRESSION_BITFIELDS et \ref K_MK_BMP_COMPRESSION_ALPHABITFIELDS). */
   uint32_t imageSize;                          /*!< Ce membre contient la taille du bitmap [en octet]. */
   int32_t xresolution;                         /*!< Ce membre contient la résolution horizontale de l'image [en pxl/m]. */
   int32_t yresolution;                         /*!< Ce membre contient la résolution verticale de l'image [en pxl/m]. */
   uint32_t coloursUsed;                        /*!< Ce membre contient le nombre de couleurs dans la palette. */
   uint32_t coloursImportant;                   /*!< Ce membre contient le nombre de couleurs importantes dans la palette. */
};

/**
 * @struct T_mkBMPW3Header
 * @brief Déclaration de la structure T_mkBMPW3Header (BITMAPV3INFOHEADER).
 * @note 3 versions existantes.
 */

typedef struct T_mkBMPW3Header T_mkBMPW3Header;
struct T_mkBMPW3Header
{
   T_mkBMPImageHeader imageHeader;              /*!< Ce membre contient le header générique d'un bitmap. */
   T_mkBMPRGBAMask mask;                        /*!< Ce membre contient la valeur du masque RGBA (champ présent si la méthode de compression est \ref K_MK_BMP_COMPRESSION_BITFIELDS). */
};

/**
 * @struct T_mkBMPW4Header
 * @brief Déclaration de la structure T_mkBMPW4Header (BITMAPV4HEADER).
 */

typedef struct T_mkBMPW4Header T_mkBMPW4Header;
struct T_mkBMPW4Header
{
   T_mkBMPImageHeader imageHeader;              /*!< Ce membre contient le header générique d'un bitmap. */
   T_mkBMPRGBAMask mask;                        /*!< Ce membre contient la valeur du masque RGB. */
   uint32_t csType;                             /*!< Ce membre contient le type de l'espace de couleur - 00h (calibrated RGB), 01h (device-dependent RGB), and 02h (device-dependent CMYK). */
   int32_t redx;                                /*!< Ce membre contient la coordonnée X de la terminaison rouge - applicable si csType = 00h (calibrated RGB). */
   int32_t redy;                                /*!< Ce membre contient la coordonnée Y de la terminaison rouge - applicable si csType = 00h (calibrated RGB). */
   int32_t redz;                                /*!< Ce membre contient la coordonnée Z de la terminaison rouge - applicable si csType = 00h (calibrated RGB). */
   int32_t greenx;                              /*!< Ce membre contient la coordonnée X de la terminaison verte - applicable si csType = 00h (calibrated RGB). */
   int32_t greeny;                              /*!< Ce membre contient la coordonnée Y de la terminaison verte - applicable si csType = 00h (calibrated RGB). */
   int32_t greenz;                              /*!< Ce membre contient la coordonnée Z de la terminaison verte - applicable si csType = 00h (calibrated RGB). */
   int32_t bluex;                               /*!< Ce membre contient la coordonnée X de la terminaison bleu - applicable si csType = 00h (calibrated RGB). */
   int32_t bluey;                               /*!< Ce membre contient la coordonnée Y de la terminaison bleu - applicable si csType = 00h (calibrated RGB). */
   int32_t bluez;                               /*!< Ce membre contient la coordonnée Z de la terminaison bleu - applicable si csType = 00h (calibrated RGB). */
   uint32_t gammaRed;                           /*!< Ce membre contient la coordonnée Rouge du Gamma. */
   uint32_t gammaGreen;                         /*!< Ce membre contient la coordonnée Verte du Gamma. */
   uint32_t gammaBlue;                          /*!< Ce membre contient la coordonnée Bleu du Gamma. */
};

/**
 * @struct T_mkBMPW5Header
 * @brief Déclaration de la structure T_mkBMPW5Header (BITMAPV5HEADER).
 */

typedef struct T_mkBMPW5Header T_mkBMPW5Header;
struct T_mkBMPW5Header
{
   T_mkBMPImageHeader imageHeader;              /*!< Ce membre contient le header générique d'un bitmap. */
   T_mkBMPRGBAMask mask;                        /*!< Ce membre contient la valeur du masque RGB. */
   uint32_t csType;                             /*!< Ce membre contient le type de l'espace de couleur - 00h (calibrated RGB), 01h (device-dependent RGB), and 02h (device-dependent CMYK). */
   int32_t redx;                                /*!< Ce membre contient la coordonnée X de la terminaison rouge - applicable si csType = 00h (calibrated RGB). */
   int32_t redy;                                /*!< Ce membre contient la coordonnée Y de la terminaison rouge - applicable si csType = 00h (calibrated RGB). */
   int32_t redz;                                /*!< Ce membre contient la coordonnée Z de la terminaison rouge - applicable si csType = 00h (calibrated RGB). */
   int32_t greenx;                              /*!< Ce membre contient la coordonnée X de la terminaison verte - applicable si csType = 00h (calibrated RGB). */
   int32_t greeny;                              /*!< Ce membre contient la coordonnée Y de la terminaison verte - applicable si csType = 00h (calibrated RGB). */
   int32_t greenz;                              /*!< Ce membre contient la coordonnée Z de la terminaison verte - applicable si csType = 00h (calibrated RGB). */
   int32_t bluex;                               /*!< Ce membre contient la coordonnée X de la terminaison bleu - applicable si csType = 00h (calibrated RGB). */
   int32_t bluey;                               /*!< Ce membre contient la coordonnée Y de la terminaison bleu - applicable si csType = 00h (calibrated RGB). */
   int32_t bluez;                               /*!< Ce membre contient la coordonnée Z de la terminaison bleu - applicable si csType = 00h (calibrated RGB). */
   uint32_t gammaRed;                           /*!< Ce membre contient la coordonnée Rouge du Gamma. */
   uint32_t gammaGreen;                         /*!< Ce membre contient la coordonnée Verte du Gamma. */
   uint32_t gammaBlue;                          /*!< Ce membre contient la coordonnée Bleu du Gamma. */
   uint32_t intent;                             /*!< Ce membre contient les informations de rendu du bitmap. */
   uint32_t profileData;                        /*!< Ce membre contient l'offset du profil de données par rapport au début de l'entête BITMAPV5HEADER. */
   uint32_t profileSize;                        /*!< Ce membre contient la taille du profil de données [en octets]. */
   uint32_t reserved;
};

/**
 * @union T_mkBMPHeader
 * @brief Déclaration de l'union T_mkBMPHeader.
 */

typedef union T_mkBMPHeader T_mkBMPHeader;
union T_mkBMPHeader
{
   T_mkBMPW3Header w3;                          /*!< Ce membre contient les champ d'une entête BITMAPV3INFOHEADER. */
   T_mkBMPW4Header w4;                          /*!< Ce membre contient les champ d'une entête BITMAPV4HEADER. */
   T_mkBMPW5Header w5;                          /*!< Ce membre contient les champ d'une entête BITMAPV5HEADER. */
};

/**
 *
 */

#endif


