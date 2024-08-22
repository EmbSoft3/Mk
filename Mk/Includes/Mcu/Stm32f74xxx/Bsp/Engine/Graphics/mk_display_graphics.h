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
* @file mk_display_graphics.h
* @brief Déclaration des fonctions publiques dédiées au module 'Graphics'.
* @date 23 mars 2019
*
*/

#ifndef MK_DISPLAY_GRAPHICS_H
#define MK_DISPLAY_GRAPHICS_H

/**
 * @fn T_mkCode mk_graphics_clear ( uint32_t p_layer );
 * @brief Cette fonction efface un buffer graphique.
 *
 * @param[in] p_layer Ce paramètre contient l'identifiant du buffer à effacer. Les constantes suivantes peuvent être utilisées :
 *                    \li \ref K_MK_GRAPHICS_FOREGROUND : le buffer de premier plan est effacé.
 *                    \li \ref K_MK_GRAPHICS_BACKGROUND : le buffer d'arrière plan est effacé.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le moteur graphique a effacé le buffer.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas effacé le buffer car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas effacé le buffer car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas effacé le buffer car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_clear ( uint32_t p_layer );

/**
 * @fn T_mkCode mk_graphics_fill ( uint32_t p_layer, uint32_t p_argb );
 * @brief Cette fonction rempli la totalité d'un buffer graphique avec une couleur.
 *
 * @param[in] p_layer Ce paramètre contient l'identifiant du buffer à dessiner (layer). Les constantes suivantes peuvent être utilisées :
 *                    \li \ref K_MK_GRAPHICS_FOREGROUND : le buffer de premier plan est dessiné.
 *                    \li \ref K_MK_GRAPHICS_BACKGROUND : le buffer d'arrière plan est dessiné.
 * @param[in] p_argb  Ce paramètre contient la couleur du layer au format ARGB8888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le moteur graphique a dessiné le buffer.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas dessiné le buffer car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas dessiné le buffer car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas dessiné le buffer car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_fill ( uint32_t p_layer, uint32_t p_argb );

/**
 * @fn T_mkCode mk_graphics_setAlpha ( uint32_t p_layer, uint32_t p_alpha );
 * @brief Cette fonction configure la valeur alpha d'un layer.
 *
 * @param[in] p_layer Ce paramètre contient l'identifiant du layer à configurer. Les constantes suivantes peuvent être utilisées :
 *                    \li \ref K_MK_GRAPHICS_FOREGROUND : le layer de premier plan est configuré.
 *                    \li \ref K_MK_GRAPHICS_BACKGROUND : le layer d'arrière plan est configuré.
 * @param[in] p_alpha Ce paramètre contient la couleur du layer au format ARGB8888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le moteur graphique a configuré le layer.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas configuré le layer car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas configuré le layer car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas configuré le layer car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_setAlpha ( uint32_t p_layer, uint8_t p_alpha );

/**
 * @fn T_mkCode mk_graphics_drawPixel ( uint32_t p_layer, T_mkVect2D p_v, uint32_t p_argb );
 * @brief Cette fonction dessine un pixel sur l'écran. L'origine du pixel est le point TOP_LEFT. La régle de conversion des nombres flottant est
 *        la suivante : \n
 *        [ x_int, y_int ] = [ ceil ( p_x - 0.5 ), ceil ( p_y - 0.5 ) ]
 *
 * @param[in] p_layer Ce paramètre contient le layer où la figure doit être dessinée. Les constantes suivantes peuvent être utilisées :
 *                    \li \ref K_MK_GRAPHICS_FOREGROUND : la figure est dessinée au premier plan,
 *                    \li \ref K_MK_GRAPHICS_BACKGROUND : la figure est dessinée à l'arrière plan.
 * @param[in] p_v     Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                    \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_argb  Ce paramètre contient la couleur du pixel au format ARGB8888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas dessiné la figure car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_drawPixel ( uint32_t p_layer, T_mkVect2D p_v, uint32_t p_argb );

/**
 * @fn T_mkCode mk_graphics_drawRect ( uint32_t p_layer, uint32_t p_state, T_mkVect2D* p_v1, T_mkVect2D* p_v2, uint32_t p_argb );
 * @brief Cette fonction dessine un rectangle entre deux points. La régle de conversion des nombres flottant est la suivante : \n
 *        [ x_int, y_int ] = [ ceil ( p_x - 0.5 ), ceil ( p_y - 0.5 ) ]
 *
 * @param[in] p_layer  Ce paramètre contient le layer où la figure doit être dessinée. Les constantes suivantes peuvent être utilisées :
 *                     \li \ref K_MK_GRAPHICS_FOREGROUND : la figure est dessinée au premier plan,
 *                     \li \ref K_MK_GRAPHICS_BACKGROUND : la figure est dessinée à l'arrière plan.
 * @param[in] p_state  Ce paramètre contient le mode de dessin de la figure. Les constantes suivantes peuvent être utilisées :
 *                     \li \ref K_MK_GRAPHICS_SOLID : la figure est remplie,
 *                     \li \ref K_MK_GRAPHICS_EMPTY : la figure n'est pas remplie.
 * @param[in] p_v1     Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                     \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_v2     Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                     \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_argb   Ce paramètre contient la couleur du rectangle au format ARGB888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas dessiné la figure car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_drawRect ( uint32_t p_layer, uint32_t p_state, T_mkVect2D p_v1, T_mkVect2D p_v2, uint32_t p_argb );

/**
 * @fn T_mkCode mk_graphics_drawRoundRect ( uint32_t p_layer, uint32_t p_state, T_mkVect2D p_v1, T_mkVect2D p_v2, real32_t p_radius, uint32_t p_argb );
 * @brief Cette fonction dessine un rectangle arrondi entre deux points. La régle de conversion des nombres flottant est la suivante : \n
 *        [ x_int, y_int ] = [ ceil ( p_x - 0.5 ), ceil ( p_y - 0.5 ) ] \n
 *        L'arrondi est dessiné en utilisant l'algorithme d'Andres.
 *
 * @param[in] p_layer  Ce paramètre contient le layer où la figure doit être dessinée. Les constantes suivantes peuvent être utilisées :
 *                     \li \ref K_MK_GRAPHICS_FOREGROUND : la figure est dessinée au premier plan,
 *                     \li \ref K_MK_GRAPHICS_BACKGROUND : la figure est dessinée à l'arrière plan.
 * @param[in] p_state  Ce paramètre contient le mode de dessin de la figure. Les constantes suivantes peuvent être utilisées :
 *                     \li \ref K_MK_GRAPHICS_SOLID : la figure est remplie,
 *                     \li \ref K_MK_GRAPHICS_EMPTY : la figure n'est pas remplie.
 * @param[in] p_v1     Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                     \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_v2     Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                     \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_radius Ce paramètre contient le rayon de courbure des angles. Il évolue entre 0 et ( K_DISPLAY_HEIGHT / 2 ) + 0.5f.
 * @param[in] p_argb   Ce paramètre contient la couleur du rectangle au format ARGB888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas dessiné la figure car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_drawRoundRect ( uint32_t p_layer, uint32_t p_state, T_mkVect2D p_v1, T_mkVect2D p_v2, real32_t p_radius, uint32_t p_argb );

/**
 * @fn T_mkCode mk_graphics_drawLine ( uint32_t p_layer, T_mkVect2D p_v1, T_mkVect2D p_v2, uint32_t p_argb );
 * @brief Cette fonction dessine une ligne selon l'algorithme de Bresenham.
 *
 * @param[in] p_layer Ce paramètre contient le layer où la figure doit être dessinée. Les constantes suivantes peuvent être utilisées :
 *                    \li \ref K_MK_GRAPHICS_FOREGROUND : la figure est dessinée au premier plan,
 *                    \li \ref K_MK_GRAPHICS_BACKGROUND : la figure est dessinée à l'arrière plan.
 * @param[in] p_v1    Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                    \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_v2    Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                    \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_argb  Ce paramètre contient la couleur de la droite au format ARGB8888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas dessiné la figure car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_drawLine ( uint32_t p_layer, T_mkVect2D p_v1, T_mkVect2D p_v2, uint32_t p_argb );

/**
 * @fn T_mkCode mk_graphics_drawCircle ( uint32_t p_layer, uint32_t p_state, T_mkVect2D p_v, real32_t p_radius, uint32_t p_argb );
 * @brief Cette fonction dessine une cercle de diamètre ( 2.radius ) selon l'algorithme d'Andres. L'origine de la figure est le vecteur p_v.
 *        La régle de conversion des nombres flottant est la suivante : \n
 *        [ x_int, y_int ] = [ ceil ( p_x - 0.5 ), ceil ( p_y - 0.5 ) ]
 *
 * @param[in] p_layer  Ce paramètre contient le layer où la figure doit être dessinée. Les constantes suivantes peuvent être utilisées :
 *                     \li \ref K_MK_GRAPHICS_FOREGROUND : la figure est dessinée au premier plan,
 *                     \li \ref K_MK_GRAPHICS_BACKGROUND : la figure est dessinée à l'arrière plan.
 * @param[in] p_state  Ce paramètre contient le mode de dessin de la figure. Les constantes suivantes peuvent être utilisées :
 *                     \li \ref K_MK_GRAPHICS_SOLID : la figure est remplie,
 *                     \li \ref K_MK_GRAPHICS_EMPTY : la figure n'est pas remplie.
 * @param[in] p_v      Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                     \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_radius Ce paramètre contient le rayon du cercle. Il évolue entre 0 et ( \ref K_MK_DISPLAY_HEIGHT / 2 ) + 0.5f .
 * @param[in] p_argb   Ce paramètre contient la couleur du cercle au format ARGB8888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas dessiné la figure car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_drawCircle ( uint32_t p_layer, uint32_t p_state, T_mkVect2D p_v, real32_t p_radius, uint32_t p_argb );

/**
 * @fn T_mkCode mk_graphics_drawTriangle ( uint32_t p_layer, T_mkVect2D p_v1, T_mkVect2D p_v2, T_mkVect2D p_v3, uint32_t p_argb );
 * @brief Cette fonction dessine un triangle. Le remplissage s'effectue en utilisant la "TOP_LEFT_RULE".
 *
 * @param[in] p_layer Ce paramètre contient le layer où la figure doit être dessinée. Les constantes suivantes peuvent être utilisées :
 *                    \li \ref K_MK_GRAPHICS_FOREGROUND : la figure est dessinée au premier plan,
 *                    \li \ref K_MK_GRAPHICS_BACKGROUND : la figure est dessinée à l'arrière plan.
 * @param[in] p_v1    Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                    \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_v2    Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                    \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_v3    Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                    \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_argb  Ce paramètre contient la couleur du triangle au format ARGB8888.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le moteur graphique a dessiné la figure.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas dessiné la figure car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas dessiné la figure car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas dessiné la figure car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_drawTriangle ( uint32_t p_layer, T_mkVect2D p_v1, T_mkVect2D p_v2, T_mkVect2D p_v3, uint32_t p_argb );

/**
 * @fn T_mkCode mk_graphics_drawString ( uint32_t p_layer, T_mkVect2D p_v1, T_mkVect2D p_v2, T_str8 p_string, uint32_t p_argb );
 * @brief Cette fonction dessine une chaine de caractères. La régle de conversion des nombres flottant est la suivante : \n
 *        [ x_int, y_int ] = [ ceil ( p_x - 0.5 ), ceil ( p_y - 0.5 ) ] \n
 *
 * @param[in] p_layer  Ce paramètre contient le layer où la chaine de caractères doit être dessinée. Les constantes suivantes peuvent être utilisées :
 *                     \li \ref K_MK_GRAPHICS_FOREGROUND : la chaine de caractères est dessinée au premier plan,
 *                     \li \ref K_MK_GRAPHICS_BACKGROUND : la chaine de caractères est dessinée à l'arrière plan.
 * @param[in] p_v1     Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                     \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_v2     Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                     \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 *
 * @param[in] p_string Ce paramètre contient l'adresse d'une chaine de caractères. Les caractères spéciaux "/n", "/r", "/t" peuvent être utilisés.
 *                     Ce paramètre est transmis par référence au moteur. Il ne doit pas être alloué dans un contexte local.
 * @param[in] p_style  Ce paramètre contient le style de la chaine de caractères. Il contient l'adresse d'une structure de type \ref T_mkTextStyle ou
 *                     la valeur \ref K_MK_NULL si le style par défaut doit être utilisé.
 *                     Ce paramètre est transmis par référence au moteur. Il ne doit pas être alloué dans un contexte local.
 * @param[in] p_cursor Ce paramètre contient les attributs du curseur de la chaine de caractères. Il contient l'adresse d'une structure de type
 *                     \ref T_mkTextCursor ou la valeur \ref K_MK_NULL si aucun curseur n'est nécessaire.
 *                     Ce paramètre est transmis par référence au moteur. Il ne doit pas être alloué dans un contexte local.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le moteur graphique a dessiné la chaine de caractères.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas dessiné la chaine de caractères car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas dessiné la chaine de caractères car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas dessiné la chaine de caractères car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_drawString ( uint32_t p_layer, T_mkVect2D p_v1, T_mkVect2D p_v2, T_str8 p_string, T_mkTextStyle* p_style, T_mkTextCursor* p_cursor );

/**
 * @fn T_mkCode mk_graphics_drawBitmap ( uint32_t p_layer, uint32_t* p_bitmap, T_mkVect2D p_v1, uint32_t p_column, uint32_t p_row );
 * @brief Cette fonction dessine un bitmap ARGB8888.
 *
 * @param[in] p_layer  Ce paramètre contient le layer où le bitmap doit être dessiné. Les constantes suivantes peuvent être utilisées :
 *                     \li \ref K_MK_GRAPHICS_FOREGROUND : le bitmap est dessiné au premier plan,
 *                     \li \ref K_MK_GRAPHICS_BACKGROUND : le bitmap est dessiné à l'arrière plan.
 * @param[in] p_bitmap Ce paramètre contient l'adresse du bitmap.
 * @param[in] p_v1     Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                     \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_column Ce paramètre contient le nombre de colonnes du bitmap. Il évolue de 0 à \ref K_MK_DISPLAY_WIDTH - 1.
 * @param[in] p_row    Ce paramètre contient le nombre de lignes du bitmap. Il évolue de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le moteur graphique a dessiné le bitmap.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas dessiné le bitmap car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas dessiné le bitmap car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas dessiné le bitmap car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_drawBitmap ( uint32_t p_layer, uint32_t* p_bitmap, T_mkVect2D p_v1, uint32_t p_column, uint32_t p_row );

/**
 * @fn T_mkCode mk_graphics_copy ( T_mkAddr p_addr, T_mkVect2D p_v, uint32_t p_direction, uint32_t p_layer, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction copie une figure de taille [p_width, p_height] stockée à un emplacement mémoire vers un autre emplacement mémoire.
 *        \li Lorsque le paramètre 'p_direction' contient la valeur \ref K_MK_GRAPHICS_ADDR_TO_FRAME, la figure est copiée de l'adresse source ('p_addr')
 *        vers un buffer graphique. L'adresse de celui-ci est définie par les coordonnées 'p_v' et le layer 'p_layer'.
 *        \li Lorsque le paramètre 'p_direction' contient la valeur \ref K_MK_GRAPHICS_FRAME_TO_ADDR, la figure est copiée du buffer graphique vers
 *        l'adresse source ('p_addr').\n
 *        Cette fonction ne réalise pas de conversion de format.
 *        Si le buffer graphique désigné par l'attribut p_layer est au format \ref K_MK_DISPLAY_RGB888, la copie est réalisée du format \ref K_DMA2D_FORMAT_RGB888
 *        vers le format \ref K_DMA2D_FORMAT_RGB888.
 *        Si le buffer graphique désigné par l'attribut p_layer est au format \ref K_MK_DISPLAY_ARGB8888, la copie est réalisée du format \ref K_DMA2D_FORMAT_ARGB8888
 *        vers le format \ref K_DMA2D_FORMAT_ARGB8888.
 *
 *
 * @param[in] p_addr      Ce paramètre contient l'adresse source.
 * @param[in] p_v         Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                        \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_direction Ce paramètre contient la direction du transfert. Les constantes suivantes peuvent être utilisées :
 *                        \li \ref K_MK_GRAPHICS_ADDR_TO_FRAME : la copie est réalisée de l'adresse source vers un buffer graphique
 *                        \li \ref K_MK_GRAPHICS_FRAME_TO_ADDR : la copie est réalisée du buffer graphique vers l'adresse source.
 * @param[in] p_layer     Ce paramètre contient le layer où la figure doit être dessinée. Les constantes suivantes peuvent être utilisées :
 *                        \li \ref K_MK_GRAPHICS_FOREGROUND : la copie est réalisée au premier plan,
 *                        \li \ref K_MK_GRAPHICS_BACKGROUND : la copie est réalisée à l'arrière plan.
 * @param[in] p_width     Ce paramètre contient la largeur de la figure à copier. Elle évolue de 0 à \ref K_MK_DISPLAY_WIDTH - 1.
 * @param[in] p_height    Ce paramètre contient la hauteur de la figure à copier. Elle évolue de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le moteur graphique a réalisé la copie.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas réalisée la copie car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas réalisée la copie car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas réalisée la copie car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_copy ( T_mkAddr p_addr, T_mkVect2D p_v, uint32_t p_direction, uint32_t p_layer, uint32_t p_width, uint32_t p_height );

/**
 * @fn T_mkCode mk_graphics_invcopy ( T_mkAddr p_addr, T_mkVect2D p_v, uint32_t p_direction, uint32_t p_layer, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction copie une figure de taille [p_width, p_height] stockée à un emplacement mémoire vers un autre emplacement mémoire.
 *        \li Lorsque le paramètre 'p_direction' contient la valeur \ref K_MK_GRAPHICS_ADDR_TO_FRAME, la figure est copiée de l'adresse source ('p_addr')
 *        vers un buffer graphique. L'adresse de celui-ci est définie par les coordonnées 'p_v' et le layer 'p_layer'.
 *        \li Lorsque le paramètre 'p_direction' contient la valeur \ref K_MK_GRAPHICS_FRAME_TO_ADDR, la figure est copiée du buffer graphique vers
 *        l'adresse source ('p_addr').\n
 *        Cette fonction réalise une conversion de format.
 *        Si le buffer graphique désigné par l'attribut p_layer est au format \ref K_MK_DISPLAY_RGB888, la copie est réalisée du format \ref K_DMA2D_FORMAT_ARGB8888
 *        vers le format \ref K_DMA2D_FORMAT_RGB888.
 *        Si le buffer graphique désigné par l'attribut p_layer est au format \ref K_MK_DISPLAY_ARGB8888, la copie est réalisée du format \ref K_MK_DISPLAY_RGB888
 *        vers le format \ref K_DMA2D_FORMAT_ARGB8888.
 *
 * @param[in] p_addr      Ce paramètre contient l'adresse source.
 * @param[in] p_v         Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                        \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_direction Ce paramètre contient la direction du transfert. Les constantes suivantes peuvent être utilisées :
 *                        \li \ref K_MK_GRAPHICS_ADDR_TO_FRAME : la copie est réalisée de l'adresse source vers un buffer graphique
 *                        \li \ref K_MK_GRAPHICS_FRAME_TO_ADDR : la copie est réalisée du buffer graphique vers l'adresse source.
 * @param[in] p_layer     Ce paramètre contient le layer où la figure doit être dessinée. Les constantes suivantes peuvent être utilisées :
 *                        \li \ref K_MK_GRAPHICS_FOREGROUND : la copie est réalisée au premier plan,
 *                        \li \ref K_MK_GRAPHICS_BACKGROUND : la copie est réalisée à l'arrière plan.
 * @param[in] p_width     Ce paramètre contient la largeur de la figure à copier. Elle évolue de 0 à \ref K_MK_DISPLAY_WIDTH - 1.
 * @param[in] p_height    Ce paramètre contient la hauteur de la figure à copier. Elle évolue de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le moteur graphique a réalisé la copie.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas réalisée la copie car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas réalisée la copie car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas réalisée la copie car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_invcopy ( T_mkAddr p_addr, T_mkVect2D p_v, uint32_t p_direction, uint32_t p_layer, uint32_t p_width, uint32_t p_height );

/**
 * @fn T_mkCode mk_graphics_plot ( uint32_t p_layer, T_mkVect2D p_v1, T_mkVect2D p_v2, uint32_t p_type, T_mkAddr p_addr );
 * @brief Cette fonction dessine un graphique de type 'p_type'.
 *
 * @param[in] p_layer Ce paramètre contient le layer où le graphique doit être dessiné. Les constantes suivantes peuvent être utilisées :
 *                    \li \ref K_MK_GRAPHICS_FOREGROUND : le graphique est dessiné au premier plan,
 *                    \li \ref K_MK_GRAPHICS_BACKGROUND : le graphique est dessiné à l'arrière plan.
 * @param[in] p_v1    Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                    \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_v2    Ce paramètre contient un vecteur deux dimensions. Les composantes x et y doivent être configurées respectivement de 0 à
 *                    \ref K_MK_DISPLAY_WIDTH - 1 et de 0 à \ref K_MK_DISPLAY_HEIGHT - 1.
 * @param[in] p_type Ce paramètre contient le type du graphique (\ref T_mkGraphType).
 * @param[in] p_addr Ce paramètre contient l'adresse d'un objet graphique (\ref T_mkGraph2D, ...)
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le moteur graphique a dessiné le graphique.
 *         \li \ref K_MK_ERROR_PARAM   : le moteur graphique n'a pas dessiné le graphique car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le moteur graphique n'a pas dessiné le graphique car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le moteur graphique n'a pas dessiné le graphique car un timeout s'est produit.
 *
 */

T_mkCode mk_graphics_plot ( uint32_t p_layer, T_mkVect2D p_v1, T_mkVect2D p_v2, uint32_t p_type, T_mkAddr p_addr );

/**
 *
 */

#endif


