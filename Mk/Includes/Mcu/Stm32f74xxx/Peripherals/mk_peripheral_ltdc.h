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
* @file mk_peripheral_ltdc.h
* @brief Déclaration des fonctions dédiées au périphérique LTDC.
* @date 17 févr. 2019
*
*/

#ifndef MK_PERIPHERAL_LTDC_H
#define MK_PERIPHERAL_LTDC_H

/**
 * @fn void ltdc_enable ( void );
 * @brief Cette fonction active le périphérique LTDC.
 * @return Sans objet.
 *
 */

void ltdc_enable ( void );

/**
 * @fn void ltdc_disable ( void );
 * @brief Cette fonction désactive le périphérique LTDC.
 * @return Sans objet.
 *
 */

void ltdc_disable ( void );

/**
 * @fn void ltdc_loadLayers ( void );
 * @brief  Cette fonction paramètre le moment où la nouvelle valeur des registres de configuration des layers devient effective.
 *         La mise à jour peut être immédiate ou programmée durant la période du Vertical Blanking (après la zone active).
 *
 * @param[ in ] p_type Cette constante contient l'instant où la nouvelle valeur des registres de configuration des layers devient
 *                     effective. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_LTDC_IMMEDIATE, \ref K_LTDC_VERTICAL_BLANKING
 *
 * @note Tant que les nouvelles valeurs ne sont pas chargées, la lecture des registres configurant les layers retourne l'ancienne valeur
 *       des registres.
 * @note La fonction \ref ltdc_isLayersLoaded permet de savoir si les dernières valeurs de registres ont été prises en compte.
 *
 * @return Sans objet.
 *
 */

void ltdc_loadLayers ( uint32_t p_type );

/**
 * @fn ltdc_setPolarity ( uint32_t p_flag );
 * @brief Cette fonction définie l'état actif (polarité) des signaux présents en paramètre à la valeur HIGH.
 *
 * @param[in] p_flag     Ce paramètre contient l'identifiant des signaux de commandes. Une combinaison des constantes suivantes
 *                       peuvent être utilisées : \n
 *                       \ref K_LTDC_HSYNC, \ref K_LTDC_VSYNC, \ref K_LTDC_DATA_ENABLE, \ref K_LTDC_PIXEL_CLOCK
 *
 * @return Sans objet.
 *
 */

void ltdc_setPolarity ( uint32_t p_flag );

/**
 * @fn ltdc_clearPolarity ( uint32_t p_flag );
 * @brief Cette fonction définie l'état actif (polarité) des signaux présents en paramètre à la valeur LOW.
 *
 * @param[in] p_flag     Ce paramètre contient l'identifiant des signaux de commandes. Une combinaison des constantes suivantes
 *                       peuvent être utilisées : \n
 *                       \ref K_LTDC_HSYNC, \ref K_LTDC_VSYNC, \ref K_LTDC_DATA_ENABLE, \ref K_LTDC_PIXEL_CLOCK
 *
 * @return Sans objet.
 *
 */

void ltdc_clearPolarity ( uint32_t p_flag );

/**
 * @fn ltdc_setWidth ( uint32_t p_hsync, uint32_t p_hbp, uint32_t p_hactive, uint32_t p_hfp );
 * @brief Cette fonction configure les caractéristiques horizontales de l'écran.
 *
 * @param[in] p_hsync   Ce paramètre contient la durée du pulse de synchronisation horizontale (en multiple de l'horloge pixel).
 *                      Cette durée peut évoluer entre [0 et 4095].
 * @param[in] p_hbp     Ce paramètre contient la durée du back-porch (en multiple de l'horloge pixel).
 *                      Cette durée peut évoluer entre [0 et 4095].
 * @param[in] p_hactive Ce paramètre contient la durée de la zone active (en multiple de l'horloge pixel).
 *                      Cette durée peut évoluer entre [0 et 4095].
 * @param[in] p_hfp     Ce paramètre contient la durée du front-porch (en multiple de l'horloge pixel).
 *                      Cette durée peut évoluer entre [0 et 4095].
 *
 * @note   Les données p_hsync, p_hbp, p_hfp sont des paramètres intrinsèques de l'écran. La donnée p_hactive est la largeur
 *         effective de l'écran.\n
 *         L'horloge pixel est égale à Freq ( SAI_R ) / K_CLOCK_SAIR_DIVn avec n = 2, 4, 8 ou 16.
 * @return Sans objet.
 *
 */

void ltdc_setWidth ( uint32_t p_hsync, uint32_t p_hbp, uint32_t p_hactive, uint32_t p_hfp );

/**
 * @fn void ltdc_setHeight ( uint32_t p_vsync, uint32_t p_vbp, uint32_t p_vactive, uint32_t p_vfp );
 * @brief Cette fonction configure les caractèristiques verticales de l'écran.
 *
 * @param[in] p_vsync   Ce paramètre contient la durée du pulse de synchronisation vertical (en multiple du scanline).
 *                      d'une colonne de l'écran. Cette durée peut évoluer entre [0 et 2047].
 * @param[in] p_vbp     Ce paramètre contient la durée du back-porch (en multiple du scanline).
 *                      Cette durée peut évoluer entre [0 et 2047].
 * @param[in] p_vactive Ce paramètre contient la durée de la zone active (en multiple du scanline).
 *                      Cette durée peut évoluer entre [0 et 2047].
 * @param[in] p_vfp     Ce paramètre contient la durée du front-porch (en multiple du scanline).
 *                      Cette durée peut évoluer entre [0 et 2047].
 *
 * @note   Les données p_vsync, p_vbp, p_vfp sont des paramètres intrinsèques de l'écran. La donnée p_vactive est la hauteur effective de
 *         l'écran.\n
 *         L'horloge pixel est égale à Freq ( SAI_R ) / K_CLOCK_SAIR_DIVn avec n = 2, 4, 8 ou 16.
 * @return Sans objet.
 *
 */

void ltdc_setHeight ( uint32_t p_vsync, uint32_t p_vbp, uint32_t p_vactive, uint32_t p_vfp );

/**
 * @fn void ltdc_setBackground ( void );
 * @brief Cette fonction configure la couleur d'arrière plan de l'écran.
 * @param[in] p_rgb Ce paramètre contient une couleur au format RGB888.
 *
 * @note La couleur d'arrière plan de l'écran est utilisé dans l'algorithme de blending avec les couleurs d'arrière plan des layers 1 et 2.
 * @return Sans objet.
 *
 */

void ltdc_setBackground ( uint32_t p_rgb );

/**
 * @fn void ltdc_enableDithering ( void );
 * @brief Cette fonction active le Dithering.
 * @return Sans objet.
 *
 */

void ltdc_enableDithering ( void );

/**
 * @fn void ltdc_enableDithering ( void );
 * @brief Cette fonction désactive le Dithering.
 * @return Sans objet.
 *
 */

void ltdc_disableDithering ( void );

/**
 * @fn void ltdc_enableReloadInterrupt ( void );
 * @brief Cette fonction active l'interruption indiquant que les registres configurant les layers ont été mis à jour.
 * @return Sans objet.
 *
 */

void ltdc_enableReloadInterrupt ( void );

/**
 * @fn void ltdc_enableTransferErrorInterrupt ( void );
 * @brief Cette fonction active l'interruption indiquant qu'une erreur sur le bus AHB s'est produite durant un transfert.
 * @return Sans objet.
 *
 */

void ltdc_enableTransferErrorInterrupt ( void );

/**
 * @fn void ltdc_enableFifoUnderrunInterrupt ( void );
 * @brief Cette fonction active l'interruption indiquant qu'une requête d'affichage a été effectuée alors que le FIFO était
 *        vide.
 * @return Sans objet.
 *
 */

void ltdc_enableFifoUnderrunInterrupt ( void );

/**
 * @fn void ltdc_enableLineInterrupt ( void );
 * @brief Cette fonction active l'interruption indiquant que la position de la ligne programmée par la
 *        fonction \ref ltdc_setLineInterrupt a été atteinte.
 * @return Sans objet.
 *
 */

void ltdc_enableLineInterrupt ( void );

/**
 * @fn void ltdc_disableReloadInterrupt ( void );
 * @brief Cette fonction désactive l'interruption indiquant que les registres configurant les layers ont été mis à jour.
 * @return Sans objet.
 *
 */

void ltdc_disableReloadInterrupt ( void );

/**
 * @fn void ltdc_disableTransferErrorInterrupt ( void );
 * @brief Cette fonction désactive l'interruption indiquant qu'une erreur sur le bus AHB s'est produite durant un transfert.
 * @return Sans objet.
 *
 */

void ltdc_disableTransferErrorInterrupt ( void );

/**
 * @fn void ltdc_disableFifoUnderrunInterrupt ( void );
 * @brief Cette fonction désactive l'interruption indiquant qu'une requête d'affichage a été effectuée alors que le FIFO était
 *        vide.
 * @return Sans objet.
 *
 */

void ltdc_disableFifoUnderrunInterrupt ( void );

/**
 * @fn void ltdc_disableLineInterrupt ( void );
 * @brief Cette fonction désactive l'interruption indiquant que la position de la ligne programmée par la
 *        fonction \ref ltdc_setLineInterrupt a été atteinte.
 * @return Sans objet.
 *
 */

void ltdc_disableLineInterrupt ( void );

/**
 * @fn void ltdc_clearReloadInterrupt ( void );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant que les registres configurant les layers ont été
 *        mis à jour.
 * @return Sans objet.
 *
 */

void ltdc_clearReloadInterrupt ( void );

/**
 * @fn void ltdc_clearTransferErrorInterruptFlag ( void );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant qu'une erreur sur le bus AHB s'est produite durant
 *        un transfert.
 * @return Sans objet.
 *
 */

void ltdc_clearTransferErrorInterruptFlag ( void );

/**
 * @fn void ltdc_clearFifoUnderrunInterrupt ( void );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant qu'une requête d'affichage a été effectuée alors que
 *        le FIFO était vide.
 * @return Sans objet.
 *
 */

void ltdc_clearFifoUnderrunInterrupt ( void );

/**
 * @fn void ltdc_clearLineInterrupt ( void );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant que la position de la ligne programmée par la
 *        fonction \ref ltdc_setLineInterrupt a été atteinte.
 * @return Sans objet.
 *
 */

void ltdc_clearLineInterrupt ( void );

/**
 * @fn void ltdc_setLineInterrupt ( void );
 * @brief Cette fonction configure le numéro de la ligne provoquant une interruption.
 *
 * @param[in] p_line Ce paramètre contient la somme des durées VSYNC et VBP additionné d'une fraction de la hauteur de
 *                   l'écran. Pour la ligne 0, ce paramètre vaut VSYNC + VDP.
 *                   Cette durée peut évoluer entre [0 et 2047].
 *
 * @note Les fonctions \ref ltdc_setWidth et \ref ltdc_setHeight configure les dimensions de l'écran en fonction des
 *       caractéristique de celui-ci.
 * @return Sans objet.
 *
 */

void ltdc_setLineInterrupt ( uint32_t p_line );

/**
 * @fn void ltdc_enableLookUpTable ( void_t p_layer );
 * @brief Cette fonction active la table de correspondance pour un des deux layers.
 *
 * @param[in] p_layer Ce paramètre contient le layer où la table doit être activée. Les constantes suivantes peuvent
 *                    être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.\n
 *       La CLUT (Color Look-Up Table) n'est applicable que pour les couleurs codées au format L8, AL44 et AL88. Elle utilise
 *       une table indexée pour convertir les couleurs L8, AL44 et AL888 au format RGB888.\n
 *       Dans les format L8 ou AL88, la CLUT possède 256 entrées. Sinon avec le format AL44, la CLUT possède 16 entrées.
 * @return Sans objet.
 *
 */

void ltdc_enableLookUpTable ( void_t p_layer );

/**
 * @fn void ltdc_disableLookUpTable ( void_t p_layer );
 * @brief Cette fonction désactive la table de correspondance pour un des deux layers.
 *
 * @param[in] p_layer Ce paramètre contient le layer où la table doit être désactivée. Les constantes suivantes peuvent
 *                    être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.\n
 *       La CLUT (Color Look-Up Table) n'est applicable que pour les couleurs codées au format L8, AL44 et AL88. Elle utilise
 *       une table indexée pour convertir les couleurs L8, AL44 et AL888 au format RGB888.\n
 *       Dans les format L8 ou AL88, la CLUT possède 256 entrées. Sinon avec le format AL44, la CLUT possède 16 entrées.
 * @return Sans objet.
 *
 */

void ltdc_disableLookUpTable ( void_t p_layer );

/**
 * @fn void ltdc_enableColorKeying ( void_t p_layer );
 * @brief Cette fonction active le "Color Keying" pour un des deux layers.
 *
 * @param[in] p_layer Ce paramètre contient le layer où le mécanisme doit être activé. Les constantes suivantes peuvent
 *                    être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.\n
 *       Le "Color Keying" est un procédé pouvant être appliqué pour modifier la valeur d'un pixel. Il consiste à configurer une
 *       clé ("color key") au format ARGB. Si durant l'affichage (après la convertion de format), le pixel courant est égale
 *       à la clé, alors tous ces canaux (ARGB) sont positionné à 0.
 * @return Sans objet.
 *
 */

void ltdc_enableColorKeying ( void_t p_layer );

/**
 * @fn void ltdc_disableColorKeying ( void_t p_layer );
 * @brief Cette fonction désactive le "Color Keying" pour un des deux layers.
 *
 * @param[in] p_layer Ce paramètre contient le layer où le mécanisme doit être désactivé. Les constantes suivantes peuvent
 *                    être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.\n
 *       Le "Color Keying" est un procédé pouvant être appliqué pour modifier la valeur d'un pixel. Il consiste à configurer une
 *       clé ("color key") au format ARGB. Si durant l'affichage (après la convertion de format), le pixel courant est égale
 *       à la clé, alors tous ces canaux (ARGB) sont positionné à 0.
 * @return Sans objet.
 *
 */

void ltdc_disableColorKeying ( void_t p_layer );

/**
 * @fn void ltdc_enableLayer ( void_t p_layer );
 * @brief Cette fonction active un des deux layers.
 *
 * @param[in] p_layer Ce paramètre contient le layer qui doit être activé. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.
 * @return Sans objet.
 *
 */

void ltdc_enableLayer ( void_t p_layer );

/**
 * @fn void ltdc_disableLayer ( void_t p_layer );
 * @brief Cette fonction désactive un des deux layers.
 *
 * @param[in] p_layer Ce paramètre contient le layer qui doit être désactivé. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.
 * @return Sans objet.
 *
 */

void ltdc_disableLayer ( void_t p_layer );

/**
 * @fn void ltdc_setLayer ( void_t p_layer, uint32_t p_hfirst, uint32_t p_hlast, uint32_t p_vfirst, uint32_t p_vlast );
 * @brief Cette fonction configure la fenêtre d'un des deux layers.
 *
 * @param[in] p_layer  Ce paramètre contient le layer à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 * @param[in] p_hfirst Ce paramètre contient le numéro du premier pixel horizontal. Le numéro est codé entre [0 et SCREEN_SIZE - 1].
 * @param[in] p_hlast  Ce paramètre contient le numéro du dernier pixel horizontal. Le numéro est codé entre [0 et SCREEN_SIZE - 1].
 * @param[in] p_vfirst Ce paramètre contient le numéro du premier pixel vertical. Le numéro est codé entre [0 et SCREEN_SIZE - 1].
 * @param[in] p_vlast  Ce paramètre contient le numéro du dernier pixel vertical. Le numéro est codé entre [0 et SCREEN_SIZE - 1].
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.
 * @warning Les fonctions \ref ltdc_setWidth et \ref ltdc_setHeight doivent être appelées avant l'exécution de cette fonction.
 * @return Sans objet.
 *
 */

void ltdc_setLayer ( void_t p_layer, uint32_t p_hfirst, uint32_t p_hlast, uint32_t p_vfirst, uint32_t p_vlast );

/**
 * @fn void ltdc_setColorKeying ( void_t p_layer, uint32_t p_rgb );
 * @brief Cette fonction configure la clé du mécanisme "Color Keying" d'un des deux layers.
 *
 * @param[in] p_layer Ce paramètre contient le layer à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 * @param[in] p_rgb   Ce paramètre contient une couleur au format RGB888.
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers (à vérifier, comportement
 *       contradictoire avec le datasheet page 511). \n
 *       La clé est au format RGB888, le périphérique convertit le pixel courant au format RGB888 si nécessaire puis le compare à
 *       la clé.
 * @return Sans objet.
 *
 */

void ltdc_setColorKeying ( void_t p_layer, uint32_t p_rgb );

/**
 * @fn void ltdc_setPixelFormat ( void_t p_layer, uint32_t p_format );
 * @brief Cette fonction configure le format des pixels d'un des deux layers.
 *
 * @param[in] p_layer Ce paramètre contient le layer à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 * @param[in] p_format Ce paramètre contient le format des pixels stocké en mémoire. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_LTDC_ARGB8888, \ref K_LTDC_RGB888, \ref K_LTDC_RGB565, \ref K_LTDC_ARBG1555, \ref K_LTDC_ARGB4444,
 *                     \ref K_LTDC_L8, \ref K_LTDC_AL44, \ref K_LTDC_AL88
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.
 * @return Sans objet.
 *
 */

void ltdc_setPixelFormat ( void_t p_layer, uint32_t p_format );

/**
 * @fn void ltdc_setConstantAlpha ( void_t p_layer, uint32_t p_alpha );
 * @brief Cette fonction configure la valeur du canal alpha d'un des deux layers.
 *
 * @param[in] p_layer Ce paramètre contient le layer à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 * @param[in] p_alpha Ce paramètre contient la valeur du canal alpha. La valeur peut évoluée de 0 (transparent) à 255 (opaque).
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.
 * @return Sans objet.
 *
 */

void ltdc_setConstantAlpha ( void_t p_layer, uint32_t p_alpha );

/**
 * @fn void ltdc_setDefaultColor ( void_t p_layer, uint32_t p_argb );
 * @brief Cette fonction configure la valeur de défaut des pixels d'un des deux layers. Cette valeur est utilisée sur les pixels en
 *        dehors de la fenêtre du layer ou encore quand le layer est désactivé.
 *
 * @param[in] p_layer Ce paramètre contient le layer à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 * @param[in] p_argb  Ce paramètre contient une couleur au format ARGB8888.
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.
 * @return Sans objet.
 *
 */

void ltdc_setDefaultColor ( void_t p_layer, uint32_t p_argb );

/**
 * @fn void ltdc_setBlendingFactors ( void_t p_layer, uint32_t p_factor1, uint32_t p_factor2 );
 * @brief Cette fonction configure les facteurs de transparence d'un des deux layers. L'algorithme de blending utilise l'équation
 *        suivante : \n BLENDING_COLOR = p_factor1 * CURRENT_LAYER_COLOR + p_factor2 * LAYER_SOUS_JACENT \n
 *        Le layer sous-jacent du layer 1 est la couleur d'arrière plan (\ref ltdc_setBackground), le layer sous-jacent du layer 2 est
 *        le layer 1. La valeur \n DEFAULT_ALPHA est configuré par la fonction \ref ltdc_setConstantAlpha.
 *
 * @param[in] p_layer   Ce paramètre contient le layer à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 * @param[in] p_factor1 Ce paramètre contient la valeur du facteur alpha 1. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_LTDC_BLENDING_FACTOR1_CONSTANT_ALPHA, \ref K_LTDC_BLENDING_FACTOR1_PXL_ALPHA_x_CONSTANT_ALPHA
 * @param[in] p_factor2 Ce paramètre contient la valeur du facteur alpha 2. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_LTDC_BLENDING_FACTOR2_1_DIFF_CONSTANT_ALPHA, \ref K_LTDC_BLENDING_FACTOR2_1_DIFF_PXL_ALPHA_x_CONSTANT_ALPHA
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.
 * @return Sans objet.
 *
 */

void ltdc_setBlendingFactors ( void_t p_layer, uint32_t p_factor1, uint32_t p_factor2 );

/**
 * @fn void ltdc_setFrameBuffer ( void_t p_layer, uint32_t p_addr, uint32_t p_pitch, uint32_t p_length, p_lineNumber );
 * @brief Cette fonction configure l'adresse du buffer stockant les pixels à affichés. Le format des pixels est défini par la
 *        fonction \ref ltdc_setPixelFormat).
 *
 * @param[in] p_layer      Ce paramètre contient le layer à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                         \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 * @param[in] p_addr       Ce paramètre contient l'adresse de base du buffer [sur 32bits]. La première valeur correspond
 *                         au pixel en haut à gauche de l'écran.
 * @param[in] p_length     Ce paramètre contient la longueur d'une ligne. La longueur d'une ligne est égale à la largeur de l'écran
 *                         multipliée par le nombre d'octets codant un pixel. La valeur est codée sur 13 bits.
 * @param[in] p_pitch      Ce paramètre contient le pas (en octets) entre deux lignes. La valeur est codée sur 13 bits.
 * @param[in] p_lineNumber Ce paramètre contient le nombre de lignes dans le buffer. La valeur est codée sur 11 bits.
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.
 * @return Sans objet.
 *
 */

void ltdc_setFrameBuffer ( void_t p_layer, uint32_t p_addr, uint32_t p_length, uint32_t p_pitch, uint32_t p_lineNumber );

/**
 * @fn void ltdc_setFrameAddr ( void_t p_layer, uint32_t p_addr );
 * @brief Cette fonction configure l'adresse de base du buffer stockant les pixels à affichés au format défini par la fonction
 *        \ref ltdc_setPixelFormat.
 *
 * @param[in] p_layer Ce paramètre contient le layer à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 * @param[in] p_addr  Ce paramètre contient l'adresse de base du buffer [sur 32bits]. La première valeur correspond
 *                    au pixel en haut à gauche de l'écran.
 *
 * @note La nouvelle configuration est prise en compte suite à l'appel de la fonction \ref ltdc_loadLayers.
 * @return Sans objet.
 *
 */

void ltdc_setFrameAddr ( void_t p_layer, uint32_t p_addr );

/**
 * @fn void ltdc_setClut ( void_t p_layer, uint32_t p_index, uint32_t p_rgb );
 * @brief Cette fonction configure la valeur des entrées de la CLUT (Color Look-Up Table). La table possède un
 *        maximum de 256 entrées. La CLUT ne peut servir que pour les formats suivants : L8, AL44, AL88.
 *
 * @param[in] p_layer Ce paramètre contient le layer à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 * @param[in] p_index Ce paramètre contient l'index de la CLUT à configurer. Il peut évoluer de 0 à 255.
 * @param[in] p_rgb   Ce paramètre contient une couleur au format RGB.
 *
 * @note Cette fonction doit être appelée uniquement durant les périodes de blanking ou lorsque le layer est désactivé.
 * @return Sans objet.
 *
 */

void ltdc_setClut ( void_t p_layer, uint32_t p_index, uint32_t p_rgb );

/**
 * @fn uint32_t ltdc_getConstantAlpha ( void_t p_layer );
 * @brief Cette fonction retourne la valeur du canal alpha d'un des deux layers.
 * @param[in] p_layer Ce paramètre contient l'identifiant du layer. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_LTDC_LAYER1 et \ref K_LTDC_LAYER2
 *
 * @return Cette fonction retourne la valeur du canal alpha d'un des deux layers (entre 0 et 255).
 *
 */

uint32_t ltdc_getConstantAlpha ( void_t p_layer );

/**
 * @fn uint32_t ltdc_getCurrentPosition ( void );
 * @brief Cette fonction retourne la position du curseur XY courante.
 * @return Cette fonction retourne une valeur sur 32 bits. Les bits 31 à 16 contient la position X et les bits
 *         15 à 0 réprésente la position Y.
 *
 */

uint32_t ltdc_getCurrentPosition ( void );

/**
 * @fn uint32_t ltdc_getHSyncStatus ( void );
 * @brief Cette fonction retourne le statut de la synchronisation horizontale.
 * @note La valeur retournée ne dépend pas de la polarité configurée avec les fonctions \ref ltdc_setPolarity et
 *       \ref ltdc_clearPolarity.
 * @return Cette fonction retourne la valeur logique "1" si la broche HSYNC est active, sinon la valeur 0.
 *
 */

uint32_t ltdc_getHSyncStatus ( void );

/**
 * @fn uint32_t ltdc_getVSyncStatus ( void );
 * @brief Cette fonction retourne le statut de la synchronisation verticale.
 * @note La valeur retournée ne dépend pas de la polarité configurée avec les fonctions \ref ltdc_setPolarity et
 *       \ref ltdc_clearPolarity.
 * @return Cette fonction retourne la valeur logique "1" si la broche VSYNC est active, sinon la valeur 0.
 *
 */

uint32_t ltdc_getVSyncStatus ( void );

/**
 * @fn uint32_t ltdc_getHDEnableStatus ( void );
 * @brief Cette fonction retourne le statut de la broche DE durant la synchronisation horizontale.
 * @note La valeur retournée ne dépend pas de la polarité configurée avec les fonctions \ref ltdc_setPolarity et
 *       \ref ltdc_clearPolarity.
 * @return Cette fonction retourne la valeur logique "1" si la broche DE est active, sinon la valeur 0.
 *
 */

uint32_t ltdc_getHDEnableStatus ( void );

/**
 * @fn uint32_t ltdc_getVDEnableStatus ( void );
 * @brief Cette fonction retourne le statut de la broche DE durant la synchronisation verticale.
 * @note La valeur retournée ne dépend pas de la polarité configurée avec les fonctions \ref ltdc_setPolarity et
 *       \ref ltdc_clearPolarity.
 * @return Cette fonction retourne la valeur logique "1" si la broche DE est active, sinon la valeur 0.
 *
 */

uint32_t ltdc_getVDEnableStatus ( void );

/**
 * @fn uint32_t ltdc_getReloadInterruptFlag ( void );
 * @brief Cette fonction retourne le drapeau d'interruption indiquant que les registres configurant les layers ont été
 *        mis à jour.
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t ltdc_getReloadInterruptFlag ( void );

/**
 * @fn uint32_t ltdc_getTransferErrorInterruptFlag ( void );
 * @brief Cette fonction retourne le drapeau d'interruption indiquant qu'une erreur sur le bus AHB s'est produite durant
 *        un transfert.
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t ltdc_getTransferErrorInterruptFlag ( void );

/**
 * @fn uint32_t ltdc_getFifoUnderrunInterruptFlag ( void );
 * @brief Cette fonction retourne le drapeau d'interruption indiquant qu'une requête d'affichage a été effectuée alors que
 *        le FIFO était vide.
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t ltdc_getFifoUnderrunInterruptFlag ( void );

/**
 * @fn uint32_t ltdc_getLineInterruptFlag ( void );
 * @brief Cette fonction retourne le drapeau d'interruption indiquant que la position de la ligne programmée par la
 *        fonction \ref ltdc_setLineInterrupt a été atteinte.
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t ltdc_getLineInterruptFlag ( void );

/**
 * @fn uint32_t ltdc_isLayersLoaded ( uint32_t p_type );
 * @brief Cette fonction indique si les registres configurant les layers ont été mis à jour.
 * @param[in] p_type Cette constante contient l'instant où la nouvelle valeur des registres configurant les layers devient
 *                   effective. Les constantes suivantes peuvent être utilisées : \n
 *                   \ref K_LTDC_IMMEDIATE, \ref K_LTDC_VERTICAL_BLANKING \n
 *                   Ce paramètre doit être identique au paramètre du dernier appel de la fonction \ref ltdc_loadLayers
 *
 * @return La valeur 1 si les nouvelles valeurs des registres configurant les layers n'est pas effective. Sinon la valeur 0.
 *
 */

uint32_t ltdc_isLayersLoaded ( uint32_t p_type );

/**
 * @fn uint32_t ltdc_getRedDitheringWidth ( void );
 * @brief Cette fonction retourne la largeur de la valeur ajoutée à la composante rouge (en bits) suite au mécanisme de dithering.
 * @return La largeur (en bits) de la valeur ajoutée à la composante rouge.
 *
 */

uint32_t ltdc_getRedDitheringWidth ( void );

/**
 * @fn uint32_t ltdc_getGreenDitheringWidth ( void );
 * @brief Cette fonction retourne la largeur de la valeur ajoutée à la composante verte (en bits) suite au mécanisme de dithering.
 * @return La largeur (en bits) de la valeur ajoutée à la composante verte.
 *
 */

uint32_t ltdc_getGreenDitheringWidth ( void );

/**
 * @fn uint32_t ltdc_getBlueDitheringWidth ( void );
 * @brief Cette fonction retourne la largeur de la valeur ajoutée à la composante bleu (en bits) suite au mécanisme de dithering.
 * @return La largeur (en bits) de la valeur ajoutée à la composante bleu.
 *
 */

uint32_t ltdc_getBlueDitheringWidth ( void );

/**
 *
 */

#endif
