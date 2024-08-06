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
* @file mk_peripheral_dma2d_constants.h
* @brief Déclaration des constantes dédiées au périphérique DMA2D.
* @date 3 mars 2019
*
*/

#ifndef MK_PERIPHERAL_DMA2D_CONSTANTS_H
#define MK_PERIPHERAL_DMA2D_CONSTANTS_H

/**
 * @def K_DMA2D_CR
 * @brief Adresse du registre DMA2D_CR.
 */

#define K_DMA2D_CR ( addr_t ) 0x4002B000

/**
 * @def K_DMA2D_ISR
 * @brief Adresse du registre DMA2D_ISR.
 */

#define K_DMA2D_ISR ( addr_t ) 0x4002B004

/**
 * @def K_DMA2D_IFCR
 * @brief Adresse du registre DMA2D_IFCR.
 */

#define K_DMA2D_IFCR ( addr_t ) 0x4002B008

/**
 * @def K_DMA2D_NLR
 * @brief Adresse du registre DMA2D_NLR.
 */

#define K_DMA2D_NLR ( addr_t ) 0x4002B044

/**
 * @def K_DMA2D_LWR
 * @brief Adresse du registre DMA2D_LWR.
 */

#define K_DMA2D_LWR ( addr_t ) 0x4002B048

/**
 * @def K_DMA2D_AMTCR
 * @brief Adresse du registre DMA2D_AMTCR.
 */

#define K_DMA2D_AMTCR ( addr_t ) 0x4002B04C

/**
 * @def K_DMA2D_FGCMAR
 * @brief Adresse du registre DMA2D_FGCMAR.
 */

#define K_DMA2D_FGCMAR ( addr_t ) 0x4002B02C

/**
 * @def K_DMA2D_BGCMAR
 * @brief Adresse du registre DMA2D_BGCMAR.
 */

#define K_DMA2D_BGCMAR ( addr_t ) 0x4002B030

/**
 * @def K_DMA2D_MEMORY_TO_MEMORY
 * @brief Constante dédiée à la fonction dma2d_setMode(). \n
 *        Définition du mode permettant de copier une zone prédéfinie
 *        vers une destination sans traitement graphique.
 */

#define K_DMA2D_MEMORY_TO_MEMORY 0x00000000

/**
 * @def K_DMA2D_MEMORY_TO_MEMORY_WITH_PFC
 * @brief Constante dédiée à la fonction dma2d_setMode(). \n
 *        Définition du mode permettant de copier une zone prédéfinie
 *        vers une destination avec conversion de pixel.
 */

#define K_DMA2D_MEMORY_TO_MEMORY_WITH_PFC 0x00010000

/**
 * @def K_DMA2D_MEMORY_TO_MEMORY_WITH_PFC_AND_BLENDING
 * @brief Constante dédiée à la fonction dma2d_setMode(). \n
 *        Définition du mode permettant de copier une zone prédéfinie
 *        vers une destination avec conversion de pixel et blending.
 */

#define K_DMA2D_MEMORY_TO_MEMORY_WITH_PFC_AND_BLENDING 0x00020000

/**
 * @def K_DMA2D_REGISTER_TO_MEMORY
 * @brief Constante dédiée à la fonction dma2d_setMode(). \n
 *        Définition du mode permettant de remplir une zone prédéfinie
 *        avec une couleur donnée.
 */

#define K_DMA2D_REGISTER_TO_MEMORY 0x00030000

/**
 * @def K_DMA2D_MEM_OUTPUT
 * @brief Constante dédiée aux fonctions dma2d_setAddr (),
 *        et dma2d_setOffset(). \n
 *        Définition d'une constante permettant de configurer les
 *        caractéristiques mémoire de l'image de destination.
 */

#define K_DMA2D_MEM_OUTPUT ( addr_t ) 0x4002B03C

/**
 * @def K_DMA2D_MEM_FOREGROUND
 * @brief Constante dédiée aux fonctions dma2d_setAddr (),
 *        et dma2d_setOffset(). \n
 *        Définition d'une constante permettant de configurer les
 *        caractéristiques mémoire de l'image de premier plan.
 */

#define K_DMA2D_MEM_FOREGROUND ( addr_t ) 0x4002B00C

/**
 * @def K_DMA2D_MEM_BACKGROUND
 * @brief Constante dédiée aux fonctions dma2d_setAddr (),
 *        et dma2d_setOffset(). \n
 *        Définition d'une constante permettant de configurer les
 *        caractéristiques mémoire de l'image d'arrière plan.
 */

#define K_DMA2D_MEM_BACKGROUND ( addr_t ) 0x4002B014

/**
 * @def K_DMA2D_PFC_OUTPUT
 * @brief Constante dédiée aux fonctions dma2d_setFormat() et
 *        dma2d_setColor(). \n
 *        Définition d'une constante permettant de configurer les
 *        caractéristiques du FPC de l'image de destination.
 */

#define K_DMA2D_PFC_OUTPUT ( addr_t ) 0x4002B034

/**
 * @def K_DMA2D_PFC_FOREGROUND
 * @brief Constante dédiée aux fonctions dma2d_setFormat(),
 *        dma2d_setColor(), dma2d_setAlpha(), dma2d_setAlphaMode()
 *        dma2d_setClut() et dma2d_loadClut().\n
 *        Définition d'une constante permettant de configurer les
 *        caractéristiques du FPC de l'image de premier plan.
 */

#define K_DMA2D_PFC_FOREGROUND ( addr_t ) 0x4002B01C

/**
 * @def K_DMA2D_PFC_BACKGROUND
 * @brief Constante dédiée aux fonctions dma2d_setFormat(),
 *        dma2d_setColor(), dma2d_setAlpha(), dma2d_setAlphaMode()
 *        dma2d_setClut() et dma2d_loadClut().\n
 *        Définition d'une constante permettant de configurer les
 *        caractéristiques du FPC de l'image d'arrière plan.
 */

#define K_DMA2D_PFC_BACKGROUND ( addr_t ) 0x4002B024

/**
 * @def K_DMA2D_CLUT_FOREGROUND
 * @brief Constante dédiée à la fonction dma2d_fillClut(). \n
 *        Définition d'une constante permettant de configurer les
 *        entrées de la CLUT de premier plan.
 */

#define K_DMA2D_CLUT_FOREGROUND ( addr_t ) 0x4002B400

/**
 * @def K_DMA2D_CLUT_BACKGROUND
 * @brief Constante dédiée à la fonction dma2d_fillClut(). \n
 *        Définition d'une constante permettant de configurer les
 *        entrées de la CLUT d'arrière plan.
 */

#define K_DMA2D_CLUT_BACKGROUND ( addr_t ) 0x4002B800

/**
 * @def K_DMA2D_FORMAT_ARGB8888
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format ARGB8888. Cette constante peut être
 *        utilisée par les trois PFC.
 */

#define K_DMA2D_FORMAT_ARGB8888 0x00000000

/**
 * @def K_DMA2D_FORMAT_RGB888
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format RGB888. Cette constante peut être
 *        utilisée par les trois PFC.
 */

#define K_DMA2D_FORMAT_RGB888 0x00000001

/**
 * @def K_DMA2D_RGB565
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format RGB565. Cette constante peut être
 *        utilisée par les trois PFC.
 */

#define K_DMA2D_RGB565 0x00000002

/**
 * @def K_DMA2D_FORMAT_ARGB1555
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format ARGB1555. Cette constante peut être
 *        utilisée par les trois PFC.
 */

#define K_DMA2D_FORMAT_ARGB1555 0x00000003

/**
 * @def K_DMA2D_ARGB4444
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format ARGB4444. Cette constante peut être
 *        utilisée par les trois PFC.
 */
#define K_DMA2D_ARGB4444 0x00000004

/**
 * @def K_DMA2D_FORMAT_L8
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format L8. Cette constante peut être
 *        utilisée par les PFC de premier plan et d'arrière plan.
 */

#define K_DMA2D_FORMAT_L8 0x00000005

/**
 * @def K_DMA2D_FORMAT_AL44
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format AL44. Cette constante peut être
 *        utilisée par les PFC de premier plan et d'arrière plan.
 */

#define K_DMA2D_FORMAT_AL44 0x00000006

/**
 * @def K_DMA2D_FORMAT_AL88
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format AL88. Cette constante peut être
 *        utilisée par les PFC de premier plan et d'arrière plan.
 */

#define K_DMA2D_FORMAT_AL88 0x00000007

/**
 * @def K_DMA2D_FORMAT_L4
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format L4. Cette constante peut être
 *        utilisée par les PFC de premier plan et d'arrière plan.
 */

#define K_DMA2D_FORMAT_L4 0x00000008

/**
 * @def K_DMA2D_FORMAT_A8
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format A8. Cette constante peut être
 *        utilisée par les PFC de premier plan et d'arrière plan.
 */

#define K_DMA2D_FORMAT_A8 0x00000009

/**
 * @def K_DMA2D_FORMAT_A4
 * @brief Constante dédiée à la fonction dma2d_setFormat(). \n
 *        Définition du format A4. Cette constante peut être
 *        utilisée par les PFC de premier plan et d'arrière plan.
 */

#define K_DMA2D_FORMAT_A4 0x0000000A

/**
 * @def K_DMA2D_PFC_ALPHA_DISABLE
 * @brief Constante dédiée à la fonction dma2d_setAlphaMode(). \n
 *        Définition d'une constante qui désactive les traitements
 *        de blending effectué par les PFC de premier ou d'arrière.
 *        plan.
 */

#define K_DMA2D_PFC_ALPHA_DISABLE 0x00000000

/**
 * @def K_DMA2D_FPC_ALPHA_REPLACEMENT
 * @brief Constante dédiée à la fonction dma2d_setAlphaMode(). \n
 *        Définition d'une constante qui indique aux FPC de premier
 *        ou d'arrière plan de modifier le canal alpha du pixel
 *        courant par la valeur configurée avec la fonction
 *        dma2d_setAlpha().
 */

#define K_DMA2D_FPC_ALPHA_REPLACEMENT 0x00010000

/**
 * @def K_DMA2D_FPC_ALPHA_MULTIPLICATION
 * @brief Constante dédiée à la fonction dma2d_setAlphaMode(). \n
 *        Définition d'une constante qui indique aux FPC de premier
 *        ou d'arrière plan de modifier le canal alpha du pixel
 *        courant par la produit du canal alpha du pixel courant
 *        avec la valeur configurée avec la fonction dma2d_setAlpha().
 */

#define K_DMA2D_FPC_ALPHA_MULTIPLICATION 0x00020000

/**
 * @def K_DMA2D_CLUT_ARGB8888
 * @brief Constante dédiée à la fonction dma2d_setClut(). \n
 *        Définition du format ARGB8888 de la CLUT.
 */

#define K_DMA2D_CLUT_ARGB8888 0x00000000

/**
 * @def K_DMA2D_CLUT_RGB888
 * @brief Constante dédiée à la fonction dma2d_setClut(). \n
 *        Définition du format RGB888 de la CLUT.
 */

#define K_DMA2D_CLUT_RGB888 0x00000010

/**
 *
 */

#endif

