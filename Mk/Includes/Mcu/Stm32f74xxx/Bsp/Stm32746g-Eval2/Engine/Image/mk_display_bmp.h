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
* @file mk_display_bmp.h
* @brief Déclaration des fonctions publiques dédiées au module 'BMP'.
* @date 2 oct. 2022
*
*/

#ifndef MK_DISPLAY_BMP_H
#define MK_DISPLAY_BMP_H

/**
 * @fn T_mkCode mk_bmp_open ( T_mkBMPFile* p_bitmap, T_mkVolume* p_volume, T_str8 p_filePath );
 * @brief Cette fonction ouvre un fichier image de type ".bmp".
 *
 * @param[in,out] p_bitmap        Ce paramètre contient l'adresse d'un fichier image de type \ref T_mkBMPFile.
 * @param[in]     p_volume        Ce paramètre contient l'adresse d'un volume de type \ref T_mkVolume où est stocké l'image. Il peut prendre la valeur \ref K_MK_NULL.
 * @param[in]     p_directoryPath Ce paramètre contient l'adresse d'une chaine de caractères stockant le répertoire où le fichier est présent. La chaine
 *                                de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets. Elle peut prendre la valeur "" si l'accès doit être réalisé de
 *                                manière absolu.
 *                                \n Lorsque le paramètre p_volume est non nul, l'accès est réalisé sur la partition définie par p_volume.
 *                                \n Lorsque le paramètre p_volume est nul, la partition à accéder doit être spécifiée de la manière suivante :
 *                                \n /dsk[n]/vol[k]/path/fileName.txt avec n compris entre [0 et K_MK_DISK_MAX_NUMBER] et k compris entre [0 et K_MK_VOLUME_MAX_NUMBER].
 *                                \n Par exemple la chaine "/dsk0/vol1/fileName.bmp" ouvre le fichier "fileName.bmp" du disque 0, partition 1.
 *                                La chaine "/disk3/vol0/path/fileName.bmp" ouvre le fichier "path/fileName.bmp" du disque 3, partition 0.
 *                                \n Les champs /dsk[n]/vol[k]/ peuvent être omis si l'accès est réalisé sur le disque système. Par exemple la chaine "path/image.bmp"
 *                                ouvre le fichier image.bmp présent dans le répertoire "path" de la partition système.
 * @param[in]     p_filePath      Ce paramètre contient l'adresse d'une chaine de caractères stockant le chemin est le nom de l'image. La chaine
 *                                de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets. Si le paramètre p_directoryPath vaut "", le chemin du fichier
 *                                doit être précisé de manière absolu depuis la racine.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : le fichier a été ouvert.
 *         \li \ref K_MK_ERROR_PARAM         : le fichier n'a pas été ouvert car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : le fichier n'a pas été ouvert car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le fichier n'a pas été ouvert car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : le fichier n'a pas été ouvert car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : le fichier n'a pas été ouvert car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : le fichier n'a pas été ouvert car le fichier est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_NOT_SUPPORTED : le fichier n'a pas été ouvert car son format n'est pas supporté.
 *         \li \ref K_MK_ERROR_RIGHT         : le fichier n'a pas été ouvert car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @note Un fichier ouvert doit être fermé avec la fonction \ref mk_bmp_close.
 *
 */

T_mkCode mk_bmp_open ( T_mkBMPFile* p_bitmap, T_mkVolume* p_volume, T_str8 p_directoryPath, T_str8 p_filePath );

/**
 * @fn T_mkCode mk_bmp_getSize (T_mkBMPFile* p_bitmap, int32_t* p_width, int32_t* p_height );
 * @brief Cette fonction récupère la taille [width, height] d'une image de type ".bmp".
 *
 * @param[in]  p_bitmap Ce paramètre contient l'adresse d'un fichier image de type \ref T_mkBMPFile.
 * @param[out] p_width  Ce paramètre contient la largeur du bitmap [en pxl].
 * @param[out] p_height Ce paramètre contient la hauteur du bitmap [en pxl].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : les attributs p_width et p_height ont été récupérés.
 *         \li \ref K_MK_ERROR_PARAM : les attributs p_width et p_height n'ont pas été récupérés car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_bmp_getSize (T_mkBMPFile* p_bitmap, uint32_t* p_width, uint32_t* p_height );

/**
 * @fn T_mkCode mk_bmp_load ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr, uint32_t p_bytesPerPixel, uint8_t p_alpha );
 * @brief Cette fonction charge un fichier image de type ".bmp" dans la mémoire. Le fichier est convertit en 24 ou 32 bits en fonction du paramètre 'p_bytesPerPixel'.
 *        Il est organisé pour être dessiné du haut vers le bas. Seul les images 24bits et 32bits non compressé sont supportées.
 *        La différence avec la fonction \ref mk_bmp_load2D est que le chargement de l'image n'est pas réalisé par le gestionnaire de requêtes (DMA2D).
 *
 * @param[in,out] p_bitmap        Ce paramètre contient l'adresse d'un fichier image de type \ref T_mkBMPFile.
 * @param[in]     p_addr          Ce paramètre contient l'adresse 32 bits où l'image doit être déployée.
 * @param[in]     p_bytesPerPixel Ce paramètre contient la résolution du buffer graphique où l'image doit être déployée (\ref K_MK_DISPLAY_RGB888 ou \ref K_MK_DISPLAY_ARGB8888).
 * @param[in]     p_alpha         Ce paramètre est dédié aux images de résolution 24bits. Il contient la valeur de la composante "alpha" à écrire en mémoire.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'image a été déployée en mémoire.
 *         \li \ref K_MK_ERROR_PARAM         : l'image n'a pas été déployée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : l'image n'a pas été déployée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'image n'a pas été déployée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'image n'a pas été déployée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'image n'a pas été déployée car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'image n'a pas été déployée car le fichier est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_NOT_SUPPORTED : l'image n'a pas été déployée car son format n'est pas supporté.
 *         \li \ref K_MK_ERROR_RIGHT         : l'image n'a pas été déployée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_bmp_load ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr, uint32_t p_bytesPerPixel, uint8_t p_alpha );

/**
 * @fn T_mkCode mk_bmp_load2D ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr, uint32_t p_bytesPerPixel, uint8_t p_alpha );
 * @brief Cette fonction charge un fichier image de type ".bmp" dans la mémoire. Le fichier est convertit en 24 ou 32 bits en fonction du paramètre 'p_bytesPerPixel'.
 *        Il est organisé pour être dessiné du haut vers le bas. Seul les images 24bits et 32bits non compressé sont supportées.
 *        La différence avec la fonction \ref mk_bmp_load est que le chargement de l'image est réalisé par le gestionnaire de requêtes (DMA2D).
 *
 * @param[in,out] p_bitmap        Ce paramètre contient l'adresse d'un fichier image de type \ref T_mkBMPFile. Il est transmis par référence au moteur. Il ne doit
 *                                pas être alloué dans un contexte local.
 * @param[in]     p_addr          Ce paramètre contient l'adresse 32 bits où l'image doit être déployée.
 * @param[in]     p_bytesPerPixel Ce paramètre contient la résolution du buffer graphique où l'image doit être déployée (\ref K_MK_DISPLAY_RGB888 ou \ref K_MK_DISPLAY_ARGB8888).
 * @param[in]     p_alpha         Ce paramètre est dédié aux images de résolution 24bits. Il contient la valeur de la composante "alpha" à écrire en mémoire.
 *
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'image a été déployée en mémoire.
 *         \li \ref K_MK_ERROR_PARAM         : l'image n'a pas été déployée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : l'image n'a pas été déployée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'image n'a pas été déployée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'image n'a pas été déployée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'image n'a pas été déployée car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'image n'a pas été déployée car le fichier est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_NOT_SUPPORTED : l'image n'a pas été déployée car son format n'est pas supporté.
 *         \li \ref K_MK_ERROR_RIGHT         : l'image n'a pas été déployée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_bmp_load2D ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr, uint32_t p_bytesPerPixel, uint8_t p_alpha );

/**
 * @fn T_mkCode mk_bmp_draw ( T_mkBMPFile* p_bitmap, uint32_t p_layer, T_mkVect2D p_v );
 * @brief Cette fonction dessine un fichier bitmap préalablement chargé par les fonctions \ref mk_bmp_load() ou \ref mk_bmp_load2D().
 *
 * @param[in] p_bitmap Ce paramètre contient l'adresse d'un fichier image de type \ref T_mkBMPFile.
 * @param[in] p_layer  Ce paramètre contient le layer où la figure doit être dessinée. Les constantes suivantes peuvent être utilisées :
 *                     \li \ref K_MK_GRAPHICS_FOREGROUND : le bitmap est dessiné au premier plan,
 *                     \li \ref K_MK_GRAPHICS_BACKGROUND : le bitmap est dessiné à l'arrière plan.
 * @param[in] p_v      Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                     \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le bitmap a été dessiné.
 *         \li \ref K_MK_ERROR_PARAM   : le bitmap n'a pas été dessiné car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le bitmap n'a pas été dessiné car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : le bitmap n'a pas été dessiné car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_bmp_draw ( T_mkBMPFile* p_bitmap, uint32_t p_layer, T_mkVect2D p_v );

/**
 * @fn T_mkCode mk_bmp_close ( T_mkBMPFile* p_bitmap );
 * @brief Cette fonction ferme un fichier image de type ".bmp".
 * @param[in,out] p_bitmap Ce paramètre contient l'adresse d'un fichier image de type \ref T_mkBMPFile.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le fichier a été fermé.
 *         \li \ref K_MK_ERROR_PARAM      : le fichier n'a pas été fermé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : le fichier n'a pas été fermé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le fichier n'a pas été fermé car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le fichier n'a pas été fermé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED : le fichier n'a pas été fermé car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT      : le fichier n'a pas été fermé car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_bmp_close ( T_mkBMPFile* p_bitmap );

/**
 *
 */

#endif

