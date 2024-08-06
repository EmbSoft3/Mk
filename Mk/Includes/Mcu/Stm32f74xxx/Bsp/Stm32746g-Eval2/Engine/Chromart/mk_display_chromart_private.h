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
* @file mk_display_chromart_private.h
* @brief Déclaration des fonctions privées dédiées au module 'Chromart'.
* @date 23 avr. 2019
*
*/

#ifndef MK_DISPLAY_CHROMART_PRIVATE_H
#define MK_DISPLAY_CHROMART_PRIVATE_H

/**
 * @fn void mk_chromart_wait ( void );
 * @brief Cette fonction laisse la main à une autre tâche tant que le périphérique chromart est en activité.
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée correctement.
 *         \li \ref K_MK_ERROR_PARAM : la fonction a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : la fonction a échoué car elle a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_wait ( void );

/**
 * @fn T_mkCode mk_chromart_clear ( uint32_t* p_buf );
 * @brief Cette fonction efface la totalité du buffer graphique.
 * @param[in] p_buf Ce paramètre contient l'adresse d'un buffer graphique de taille \ref K_MK_DISPLAY_FRAME_BUFFER_SIZE.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : l'effacement du buffer graphique a réussi.
 *         \li \ref K_MK_ERROR_PARAM : l'effacement du buffer graphique a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : l'effacement du buffer graphique a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_clear ( uint32_t* p_buf );

/**
 * @fn T_mkCode mk_chromart_fill ( T_mkChromartRequest* p_request );
 * @brief Cette fonction dessine une figure de couleur [color], de coordonnées [x, y] et de taille [width, height] dans le buffer graphique identifié
 *        par le paramètre 'layer'. Le paramètre 'offset' spécifie la distance [en pxl] entre chaque ligne de la figure (valeur \ref K_MK_DISPLAY_WIDTH pour obtenir un rectangle).
 *
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane               : contient la position [x, y] et les dimensions [width, height] de la figure de destination.
 *                      \li p_request->content.fill.layer  : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.fill.offset : contient la valeur de l'offset [en pxl] entre 2 lignes du buffer de destination.
 *                      \li p_request->content.fill.color  : contient la couleur de la figure au format ARGB888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_fill ( T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_write ( T_mkChromartRequest* p_request );
 * @brief Cette fonction dessine une figure de coordonnées [x, y] et de taille [width, height] avec les données contenues dans le buffer 'foregroundAddr' à l'adresse de destination
 *        identifiée par le paramètre 'layer'. Les paramètres 'foregroundOffset' et 'destinationOffset" spécifie la distance [en pxl] entre chaque ligne des différents buffers
 *        (source et destination).
 *
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane                           : contient la position [x, y] et les dimensions [width, height] de la figure de destination.
 *                      \li p_request->content.write.layer             : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.write.foregroundAddr    : contient l'adresse de base du buffer source.
 *                      \li p_request->content.write.foregroundOffset  : contient la valeur de l'offset [en pxl] entre 2 lignes du du buffer source.
 *                      \li p_request->content.write.destinationOffset : contient la valeur de l'offset [en pxl] entre 2 lignes du du buffer de destination.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_write ( T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_copy ( T_mkTask* p_task, T_mkChromartRequest* p_request );
 * @brief Cette fonction copie une figure de taille [width, height] stockée à un emplacement mémoire vers un autre emplacement mémoire.
 *        \li Lorsque le paramètre 'direction' contient la valeur \ref K_MK_GRAPHICS_ADDR_TO_FRAME, la figure est copiée de l'adresse source 'sourceAddr' vers l'adresse de destination.
 *            L'adresse de destination est définie par les coordonnées [x, y] et le layer 'destinationLayer'.
 *        \li Lorsque le paramètre 'direction' contient la valeur \ref K_MK_GRAPHICS_FRAME_TO_ADDR, la figure est copiée de l'adresse de destination vers l'adresse source.\n
 *        Cette fonction ne réalise pas de conversion de format.
 *        Si le buffer graphique désigné par l'attribut p_request->content.copy.destinationLayer est au format \ref K_MK_DISPLAY_RGB888, la copie est réalisée du format
 *        \ref K_DMA2D_FORMAT_RGB888 vers le format \ref K_DMA2D_FORMAT_RGB888.
 *        Si le buffer graphique désigné par l'attribut p_request->content.copy.destinationLayer est au format \ref K_MK_DISPLAY_ARGB8888, la copie est réalisée du format
 *        \ref K_DMA2D_FORMAT_ARGB8888 vers le format \ref K_DMA2D_FORMAT_ARGB8888.
 *
 * @param[in] p_task    Ce paramètre contient l'adresse de la tâche ayant réalisée la requête. Si le transfert est réalisé depuis un buffer graphique (\ref K_MK_GRAPHICS_FRAME_TO_ADDR) vers
 *                      un emplacement mémoire protégé, alors la requête n'est pas réalisée. Cette condition ne s'applique qu'aux tâches non privilégiées.
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane                          : contient la position [x, y] et les dimensions [width, height] de la figure de destination.
 *                      \li p_request->content.copy.direction         : contient la direction du transfert (\ref K_MK_GRAPHICS_ADDR_TO_FRAME ou \ref K_MK_GRAPHICS_FRAME_TO_ADDR).
 *                      \li p_request->content.copy.sourceAddr        : contient l'adresse de base du buffer source.
 *                      \li p_request->content.copy.sourceOffset      : contient la valeur de l'offset [en pxl] entre 2 lignes du buffer source.
 *                      \li p_request->content.copy.destinationLayer  : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.copy.destinationOffset : contient la valeur de l'offset [en pxl] entre 2 lignes du buffer de destination.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_copy ( T_mkTask* p_task, T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_invcopy ( T_mkTask* p_task, T_mkChromartRequest* p_request );
 * @brief Cette fonction copie une figure de taille [width, height] stockée à un emplacement mémoire vers un autre emplacement mémoire.
 *        \li Lorsque le paramètre 'direction' contient la valeur \ref K_MK_GRAPHICS_ADDR_TO_FRAME, la figure est copiée de l'adresse source 'sourceAddr' vers l'adresse de destination.
 *        L'adresse de destination est définie par les coordonnées [x, y] et le layer 'destinationLayer'.
 *        \li Lorsque le paramètre 'direction' contient la valeur \ref K_MK_GRAPHICS_FRAME_TO_ADDR, la figure est copiée de l'adresse de destination vers l'adresse source.\n
 *        Cette fonction réalise une conversion de format.
 *        Si le buffer graphique désigné par l'attribut p_request->content.copy.destinationLayer est au format \ref K_MK_DISPLAY_RGB888, la copie est réalisée du format
 *        \ref K_DMA2D_FORMAT_ARGB8888 vers le format \ref K_DMA2D_FORMAT_RGB888.
 *        Si le buffer graphique désigné par l'attribut p_request->content.copy.destinationLayer est au format \ref K_MK_DISPLAY_ARGB8888, la copie est réalisée du format
 *        \ref K_DMA2D_FORMAT_RGB888 vers le format \ref K_DMA2D_FORMAT_ARGB8888.
 *
 * @param[in] p_task    Ce paramètre contient l'adresse de la tâche ayant réalisée la requête. Si le transfert est réalisé depuis un buffer graphique (\ref K_MK_GRAPHICS_FRAME_TO_ADDR) vers
 *                      un emplacement mémoire protégé, alors la requête n'est pas réalisée. Cette condition ne s'applique qu'aux tâches non privilégiées.
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane                          : contient la position [x, y] et les dimensions [width, height] de la figure de destination.
 *                      \li p_request->content.copy.direction         : contient la direction du transfert (\ref K_MK_GRAPHICS_ADDR_TO_FRAME ou \ref K_MK_GRAPHICS_FRAME_TO_ADDR).
 *                      \li p_request->content.copy.sourceAddr        : contient l'adresse de base du buffer source.
 *                      \li p_request->content.copy.sourceOffset      : contient la valeur de l'offset [en pxl] entre 2 lignes du buffer source.
 *                      \li p_request->content.copy.destinationLayer  : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.copy.destinationOffset : contient la valeur de l'offset [en pxl] entre 2 lignes du buffer de destination.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_invcopy ( T_mkTask* p_task, T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_blend ( T_mkChromartRequest* p_request );
 * @brief Cette fonction copie le résultat du blending de deux figures de taille [width; height] vers le buffer de destination identifié par les paramètres [x, y] et 'layer'.
 *        Les paramètres 'foregroundOffset', 'backgroundOffset' et 'destinationOffset" spécifie la distance [en pxl] entre chaque ligne des différents buffers
 *        (sources et destination).
 *
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane                           : contient la position [x, y] et les dimensions [width, height] de la figure de destination.
 *                      \li p_request->content.write.layer             : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.blend.foregroundAddr    : contient l'adresse de base du premier buffer utilisé dans le blending.
 *                      \li p_request->content.blend.backgroundAddr    : contient l'adresse de base du second buffer utilisé dans le blending.
 *                      \li p_request->content.blend.foregroundOffset  : contient la valeur de l'offset [en pxl] entre 2 lignes du premier buffer source.
 *                      \li p_request->content.blend.foregroundOffset  : contient la valeur de l'offset [en pxl] entre 2 lignes du second buffer source.
 *                      \li p_request->content.blend.destinationOffset : contient la valeur de l'offset [en pxl] entre 2 lignes du buffer de destination.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_blend ( T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_plot ( T_mkChromartRequest* p_request );
 * @brief Cette fonction dessine un vecteur de pixel.
 *
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane                  : contient la position [x, y] et les dimensions [width, height] du graphique.
 *                      \li p_request->content.plot.layer     : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.plot.bufAddr   : contient l'adresse du vecteur de pixels (stockage coordonnée Y).
 *                      \li p_request->content.plot.bufLength : contient la longueur du vecteur de pixels.
 *                      \li p_request->content.plot.color     : contient la couleur du vecteur de pixels.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné le vecteur.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné le vecteur car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné le vecteur car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_plot ( T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_drawString ( T_mkChromartRequest* p_request );
 * @brief Cette fonction dessine une chaine de caractères.
 *
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane                   : contient la position [x, y] et les dimensions [width, height] de la boite de texte.
 *                      \li p_request->content.string.layer    : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.string.baseAddr : contient l'adresse de la chaine de caractères.
 *                      \li p_request->content.styleAddr       : contient l'adresse d'une structure de type \ref T_mkTextStyle.
 *                      \li p_request->content.cursorAddr      : contient l'adresse d'une structure de type \ref T_mkTextCursor.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_drawString ( T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_drawLine ( T_mkChromartRequest* p_request );
 * @brief Cette fonction dessine une droite entre 2 points.
 *
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane              : contient la coordonnée [x1, y1] de la droite.
 *                      \li p_request->content.line.x(y)  : contient la coordonnée [x2, y2] de la droite.
 *                      \li p_request->content.line.layer : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.line.color : contient la couleur de la droite au format ARGB8888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_drawLine ( T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_drawCircle ( T_mkChromartRequest* p_request );
 * @brief Cette fonction dessine une cercle.
 *
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane                 : contient les coordonnées [x, y] du centre du cercle.
 *                      \li p_request->content.circle.radius : contient le rayon du cercle [en pxl].
 *                      \li p_request->content.circle.layer  : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.circle.state  : contient l'état du cercle (\ref K_MK_GRAPHICS_SOLID ou \ref K_MK_GRAPHICS_EMPTY).
 *                      \li p_request->content.circle.color  : contient la couleur du cercle au format ARGB8888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_drawCircle ( T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_drawTriangle ( T_mkChromartRequest* p_request );
 * @brief Cette fonction dessine une triangle.
 *
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane                  : contient les coordonnées [x1, y1] et [x2, y2] du triangle.
 *                      \li p_request->content.triangle.x(y)  : contient la coordonnée [x3, y3] du triangle.
 *                      \li p_request->content.triangle.layer : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.triangle.color : contient la couleur du triangle au format ARGB8888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_drawTriangle ( T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_drawRoundRect ( T_mkChromartRequest* p_request );
 * @brief Cette fonction dessine un rectangle avec des angles arrondis.
 *
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->plane                    : contient la position [x, y] et les dimensions [width, height] du rectangle.
 *                      \li p_request->content.roundRect.layer  : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.roundRect.radius : contient le rayon de courbure des angles du rectangle [en pxl].
 *                      \li p_request->content.roundRect.state  : contient l'état du rectangle (\ref K_MK_GRAPHICS_SOLID ou \ref K_MK_GRAPHICS_EMPTY).
 *                      \li p_request->content.roundRect.color  : contient la couleur du triangle au format ARGB8888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_chromart_drawRoundRect ( T_mkChromartRequest* p_request );

/**
 * @fn T_mkCode mk_chromart_load ( T_mkTask* p_task, T_mkChromartRequest* p_request );
 * @brief Cette fonction charge un fichier image de type ".bmp" dans la mémoire. Le fichier est convertit en 24 ou 32 bits en fonction du paramètre 'p_bytesPerPixel'. Il est organisé pour
 *        être dessiné du haut vers le bas. Seul les images 24bits et 32bits non compressé sont supportées.
 *
 * @param[in] p_task          Ce paramètre contient l'adresse de la tâche ayant réalisée la requête. Si le transfert est réalisé vers
 *                            un emplacement mémoire protégé, alors la requête n'est pas réalisée. Cette condition ne s'applique qu'aux tâches non privilégiées.
 * @param[in] p_request       Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                            \li p_request->content.load.bitmapAddr      : contient l'adresse d'un fichier de type \ref T_mkBMPFile.
 *                            \li p_request->content.load.destinationAddr : contient l'adresse de destination où l'image doit être chargée.
 *                            \li p_request->content.load.alpha           : contient la valeur de la composante "alpha" à écrire en mémoire. Cet attribut est dédié au image de résolution 24bits.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'image a été chargée en mémoire.
 *         \li \ref K_MK_ERROR_PARAM         : l'image n'a pas été chargée en mémoire car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : l'image n'a pas été chargée en mémoire car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'image n'a pas été chargée en mémoire car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'image n'a pas été chargée en mémoire car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'image n'a pas été chargée en mémoire car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'image n'a pas été chargée en mémoire car le fichier est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_NOT_SUPPORTED : l'image n'a pas été chargée en mémoire car son format n'est pas supporté.
 *         \li \ref K_MK_ERROR_RIGHT         : l'image n'a pas été chargée en mémoire car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_chromart_load ( T_mkTask* p_task, T_mkChromartRequest* p_request );

/**
 * @fn void mk_chromart_alpha ( T_mkTask* p_task, T_mkChromartRequest* p_request );
 * @brief Cette fonction configure la valeur alpha des layers de premier et d'arrière plan.
 * @param[in] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest. Les attributs suivants sont utilisés :\n
 *                      \li p_request->content.alpha.layer : contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *                      \li p_request->content.alpha.value : contient la nouvelle valeur alpha du layer.
 *
 * @return Sans objet.
 *
 */

void mk_chromart_alpha ( T_mkChromartRequest* p_request );

/**
 * @fn void _mk_chromart_drawCharacterFast ( uint32_t* p_destinationAddr, uint8_t* p_baseAddr, uint32_t p_color, uint32_t p_fontWidth, uint32_t p_fontHeight, uint32_t p_screenWidth );
 * @brief Cette fonction dessine le glyphe stocké à l'adresse [ p_baseAddr] à l'emplacement [ p_destinationAddr ]. Les pixels sont codés sur 32bits.
 *        L'adresse doit être alignée sur 32bits.
 *
 * @param[in] p_destinationAddr Ce paramètre contient l'adresse où le glyphe doit être dessiné.
 * @param[in] p_baseAddr        Ce paramètre contient l'adresse du bitmap stockant le glyphe.
 * @param[in] p_color           Ce paramètre contient la couleur du glyphe au format ARGB8888.
 * @param[in] p_fontWidth       Ce paramètre contient la largeur du glyphe [en bits].
 * @param[in] p_fontHeight      Ce paramètre contient la hauteur du glyphe [en bits].
 * @param[in] p_screenWidth     Ce paramètre contient la largeur de l'écran [en pixel].
 *
 * @return Sans objet.
 *
 */

void _mk_chromart_drawCharacterFast ( uint8_t* p_destinationAddr, uint8_t* p_baseAddr, uint32_t p_color, uint32_t p_fontWidth, uint32_t p_fontHeight, uint32_t p_screenWidth );

/**
 * @fn void _mk_chromart_drawCharacterFast24BPP ( uint8_t* p_destinationAddr, uint8_t* p_baseAddr, uint32_t p_color, uint32_t p_fontWidth, uint32_t p_fontHeight, uint32_t p_screenWidth );
 * @brief Cette fonction dessine le glyphe stocké à l'adresse [ p_baseAddr] à l'emplacement [ p_destinationAddr ]. Les pixels sont codés sur 24bits.
 *        Il n'y a pas de restriction d'alignement sur l'adresse.
 *
 * @param[in] p_destinationAddr Ce paramètre contient l'adresse où le glyphe doit être dessiné.
 * @param[in] p_baseAddr        Ce paramètre contient l'adresse du bitmap stockant le glyphe.
 * @param[in] p_color           Ce paramètre contient la couleur du glyphe au format ARGB8888.
 * @param[in] p_fontWidth       Ce paramètre contient la largeur du glyphe [en bits].
 * @param[in] p_fontHeight      Ce paramètre contient la hauteur du glyphe [en bits].
 * @param[in] p_screenWidth     Ce paramètre contient la largeur de l'écran [en pixel].
 *
 * @return Sans objet.
 *
 */

void _mk_chromart_drawCharacterFast24BPP ( uint8_t* p_destinationAddr, uint8_t* p_baseAddr, uint32_t p_color, uint32_t p_fontWidth, uint32_t p_fontHeight, uint32_t p_screenWidth );

/**
 * @fn T_mkCode mk_chromart_handleRequest ( T_mkTask* p_task, T_mkChromartRequest* p_request );
 * @brief Cette fonction est exécutée par le gestionnaire de requêtes. Elle identifie puis exécute les requêtes de dessin envoyées au moteur graphique.
 *
 * @param[in] p_task    Ce paramètre contient l'adresse de la tâche ayant réalisée la requête. Si le transfert est réalisé vers
 *                      un emplacement mémoire protégé, alors la requête n'est pas réalisée. Cette condition ne s'applique qu'aux tâches non privilégiées.
 * @param[in] p_request Ce paramètre contient le contenu de la requête envoyée par l'utilisateur.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : le moteur graphique a exécutée la requête.
 *         \li \ref K_MK_ERROR_PARAM         : le moteur graphique n'a pas exécutée la requête car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : le moteur graphique n'a pas exécutée la requête car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le moteur graphique n'a pas exécutée la requête car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : le moteur graphique n'a pas exécutée la requête car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : le moteur graphique n'a pas exécutée la requête car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : le moteur graphique n'a pas exécutée la requête car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_NOT_SUPPORTED : le moteur graphique n'a pas exécutée la requête car le format du fichier n'est pas supporté.
 *         \li \ref K_MK_ERROR_RIGHT         : le moteur graphique n'a pas exécutée la requête car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_chromart_handleRequest ( T_mkTask* p_task, T_mkChromartRequest* p_request );

/**
 *
 */

#endif
