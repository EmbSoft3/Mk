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
* @file mk_peripheral_dma2d.h
* @brief Déclaration des fonctions dédiées au périphérique DMA2D.
* @date 3 mars 2019
*
*/

#ifndef MK_PERIPHERAL_DMA2D_H
#define MK_PERIPHERAL_DMA2D_H

/**
 * @fn void dma2d_start ( void );
 * @brief Cette fonction démarre un transfert DMA. Elle peut être exécutée après la suspension d'un transfert pour
 *        le redémarrer.
 * @return Sans objet.
 *
 */

void dma2d_start ( void );

/**
 * @fn void dma2d_suspend ( void );
 * @brief Cette fonction suspend un transfert DMA démarré avec la fonction \ref dma2d_start. Elle permet aussi de
 *        suspendre le chargement automatique d'une CLUT.
 * @return Sans objet.
 *
 */

void dma2d_suspend ( void );

/**
 * @fn void dma2d_abort ( void );
 * @brief Cette fonction arrête un transfert DMA démarré avec la fonction \ref dma2d_start ou arrête un transfert
 *        suspendu avec la fonction \ref dma2d_suspend.\n
 *        L'arrêt d'un transfert ne déclenche pas l'interruption activée par la fonction
 *        \ref dma2d_enableTransferCompleteInterrupt.\n
 *        Cette fonction peut être utilisée pour arrêter le chargement automatique d'une CLUT.
 * @return Sans objet.
 *
 */

void dma2d_abort ( void );

/**
 * @fn void dma2d_setRectangle ( uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure le nombre de lignes et le nombre de pixels d'une ligne de la zone de dessin.
 *        La fonction \ref dma2d_setOffset configure la distance mémoire entre chaque pixel.
 *
 * @param[in] p_width  Ce paramètre contient le nombre de pixels d'une ligne sur 14bits.
 * @param[in] p_height Ce paramètre contient le nombre de ligne sur 16bits.
 *
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @return Sans objet.
 *
 */

void dma2d_setRectangle ( uint32_t p_width, uint32_t p_height );

/**
 * @fn void dma2d_setLineInterrupt ( uint32_t p_line );
 * @brief Cette fonction configure la ligne qui provoque le déclenchement de l'interruption Watermark. L'interruption
 *        se déclenche lorsque le dernier pixel de la ligne est transféré.
 *
 * @param[in] p_line Ce paramètre contient le numéro de la ligne déclenchant l'interruption sur 16 bits.
 *
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @return Sans objet.
 *
 */

void dma2d_setLineInterrupt ( uint32_t p_line );

/**
 * @fn void dma2d_enableTimer ( void );
 * @brief Cette fonction active le timer gérant les temps morts entre deux accès sur le bus AHB.
 * @return Sans objet.
 *
 */

void dma2d_enableTimer ( void );

/**
 * @fn void dma2d_disableTimer ( void );
 * @brief Cette fonction désactive le timer gérant les temps morts entre deux accès sur le bus AHB.
 * @return Sans objet.
 *
 */

void dma2d_disableTimer ( void );

/**
 * @fn void dma2d_setTimer ( uint32_t p_cycle );
 * @brief Cette fonction configure le temps mort entre deux accès consécutifs sur le bus AHB. Il garantit un temps
 *        minimum entre deux accès. *
 * @param[in] p_cycle Ce paramètre contient le nombre de cycles entre deux accès au bus. Il est exprimé en multiple
 *                    de la période HCLK sur 8 bits.
 *
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @return Sans objet.
 *
 */

void dma2d_setTimer ( uint32_t p_cycle );

/**
 * @fn void dma2d_setMode ( uint32_t p_mode );
 * @brief Cette fonction configure le type du transfert DMA. Les modes configurables sont les suivants : \n
 *
 *        \ref K_DMA2D_MEMORY_TO_MEMORY : \n
 *             Copie d'une zone prédéfinie vers une destination donnée sans traitement graphique. Les adresses de
 *             bases et les offsets sont configurées à partir des fonctions \ref dma2d_setAddr et \ref dma2d_setOffset
 *             avec la constante \ref K_DMA2D_MEM_FOREGROUND pour la source et la constante \ref K_DMA2D_MEM_OUTPUT pour
 *             la destination. \n La taille du transfert est configurée avec la fonction \ref dma2d_setRectangle.
 *
 *        \ref K_DMA2D_MEMORY_TO_MEMORY_WITH_PFC : \n
 *             Copie d'une zone prédéfinie vers une destination donnée avec conversion de pixels. Les adresses de
 *             bases et les offsets sont configurées à partir des fonctions \ref dma2d_setAddr et \ref dma2d_setOffset
 *             avec la constante \ref K_DMA2D_MEM_FOREGROUND pour la source et la constante \ref K_DMA2D_MEM_OUTPUT pour
 *             la destination. \n La taille du transfert est configurée avec la fonction \ref dma2d_setRectangle.
 *             Le format des pixels est configuré à partir de la fonction \ref dma2d_setFormat avec les constantes
 *             \ref K_DMA2D_PFC_FOREGROUND (source) et \ref K_DMA2D_PFC_OUTPUT (destination - CLUT interdit).\n
 *
 *        \ref K_DMA2D_MEMORY_TO_MEMORY_WITH_PFC_AND_BLENDING : \n
 *             Copie d'une zone prédéfinie vers une destination donnée avec conversion de pixels et blending.
 *             Les adresses de bases et les offsets sont configurées à partir des fonctions \ref dma2d_setAddr
 *             et \ref dma2d_setOffset avec les constantes \ref K_DMA2D_MEM_FOREGROUND et \ref K_DMA2D_MEM_BACKGROUND
 *             pour les sources et la constante \ref K_DMA2D_MEM_OUTPUT pour la destination.
 *             \n La taille du transfert est configurée avec la fonction \ref dma2d_setRectangle.
 *             Le format des pixels est configuré à partir de la fonction \ref dma2d_setFormat avec les constantes
 *             \ref K_DMA2D_PFC_FOREGROUND et \ref K_DMA2D_PFC_BACKGROUND  (sources) et \ref K_DMA2D_PFC_OUTPUT
 *             (destination - CLUT interdit).\n
 *             Les coeficients ALPHA sont configurés à partir des fonctions \ref dma2d_setAlpha,
 *             \ref dma2d_setAlphaMode et \ref dma2d_setColor avec les paramètres \ref K_DMA2D_PFC_FOREGROUND et
 *             \ref K_DMA2D_PFC_BACKGROUND.
 *
 *        \ref K_DMA2D_REGISTER_TO_MEMORY : \n
 *             Remplissage d'une zone prédéfinie avec une couleur donnée. La couleur est configurée à partir de la
 *             fonction \ref dma2d_setColor (constante \ref K_DMA2D_PFC_OUTPUT en paramètre).
 *             L'adresse de base et l'offset sont configurées à partir des fonctions \ref dma2d_setAddr et
 *             \ref dma2d_setOffset avec la constante \ref K_DMA2D_MEM_OUTPUT en paramètre.
 *             La taille du transfert est configurée avec la fonction \ref dma2d_setRectangle.
 *
 * @param[in] p_mode Ce paramètre contient le type du transfert DMA. Les constantes suivantes peuvent être
 *                   utilisées : \n
 *                   \ref K_DMA2D_MEMORY_TO_MEMORY, \ref K_DMA2D_MEMORY_TO_MEMORY_WITH_PFC,
 *                   \ref K_DMA2D_MEMORY_TO_MEMORY_WITH_PFC_AND_BLENDING, \ref K_DMA2D_REGISTER_TO_MEMORY
 *
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @return Sans objet.
 *
 */

void dma2d_setMode ( uint32_t p_mode );

/**
 * @fn void dma2d_setAddr ( void_t p_target, uint32_t p_baseAddr );
 * @brief Cette fonction configure l'adresse de base des données utilisées par un PFC.
 *
 * @param[in] p_target   Ce paramètre contient le FPC à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA2D_MEM_FOREGROUND, \ref K_DMA2D_MEM_BACKGROUND et \ref K_DMA2D_MEM_OUTPUT
 * @param[in] p_baseAddr Ce paramètre contient l'adresse de base des données sur 32 bits. L'adresse doit être
 *                       alignée avec le format utilisé (32bits, 16bits et 8bits).
 *
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @return Sans objet.
 *
 */

void dma2d_setAddr ( void_t p_target, uint32_t p_baseAddr );

/**
 * @fn void dma2d_setOffset ( void_t p_target, uint32_t p_offset );
 * @brief Cette fonction configure l'offset ajoutée par un PFC à la fin de chaque ligne. L'offset est ajoutée
 *        afin de déterminer l'adresse de la prochaine ligne.
 *
 * @param[in] p_target Ce paramètre contient le PFC à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_DMA2D_MEM_FOREGROUND, \ref K_DMA2D_MEM_BACKGROUND et \ref K_DMA2D_MEM_OUTPUT
 * @param[in] p_offset Ce paramètre contient la valeur de l'offset exprimée en pixels sur 14 bits.
 *
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @note Lorsqu'un pixel est codé sur 4 bits, une offset paire doit obligatoirement être configurée. Le format d'un
 *       pixel est configuré avec la fonction \ref dma2d_setFormat.
 * @return Sans objet.
 *
 */

void dma2d_setOffset ( void_t p_target, uint32_t p_offset );

/**
 * @fn void dma2d_setFormat ( void_t p_target, uint32_t p_format );
 * @brief Cette fonction configure le format d'un PFC.
 *
 * @param[in] p_target Ce paramètre contient le PFC à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_DMA2D_PFC_FOREGROUND, \ref K_DMA2D_PFC_BACKGROUND et \ref K_DMA2D_PFC_OUTPUT
 * @param[in] p_format Ce paramètre contient le format des pixels utilisés par le PFC. Les constantes suivantes
 *                     peuvent être utilisées : \n
 *                     \ref K_DMA2D_FORMAT_ARGB8888, \ref K_DMA2D_FORMAT_RGB888, \ref K_DMA2D_RGB565,
 *                     \ref K_DMA2D_FORMAT_ARGB1555, \ref K_DMA2D_ARGB4444, \ref K_DMA2D_FORMAT_L8,
 *                     \ref K_DMA2D_FORMAT_AL44, \ref K_DMA2D_FORMAT_AL88, \ref K_DMA2D_FORMAT_L4,
 *                     \ref K_DMA2D_FORMAT_A8 et \ref K_DMA2D_FORMAT_A4
 *
 * @warning Les constantes \ref K_DMA2D_FORMAT_L8, \ref K_DMA2D_FORMAT_AL44, \ref K_DMA2D_FORMAT_AL88,
 *          \ref K_DMA2D_FORMAT_L4, \ref K_DMA2D_FORMAT_A8 et \ref K_DMA2D_FORMAT_A4 ne peuvent pas être utilisées
 *          avec le paramètre \ref K_DMA2D_PFC_OUTPUT.
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @return Sans objet.
 *
 */

void dma2d_setFormat ( void_t p_target, uint32_t p_format );

/**
 * @fn void dma2d_setColor ( void_t p_target, uint32_t p_color );
 * @brief Cette fonction configure le couleur intervenant dans le calcul de blending des PFC de premier et d'arrière
 *        plan. En outre, elle configure la couleur de la zone de sortie quand le mode \ref K_DMA2D_REGISTER_TO_MEMORY
 *        est utilisé.
 *
 * @param[in] p_target Ce paramètre contient le PFC à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_DMA2D_PFC_FOREGROUND, \ref K_DMA2D_PFC_BACKGROUND et \ref K_DMA2D_PFC_OUTPUT
 * @param[in] p_color  Ce paramètre contient la couleur à configurer dans le FPC. \n
 *                     Le format RGB888 est utilisé pour les constantes \ref K_DMA2D_PFC_FOREGROUND, \ref K_DMA2D_PFC_BACKGROUND. \n
 *                     Les formats ARGB888, RGB888, RGB565, ARGB1555 et ARGB4444 peuvent être utilisé pour la constante
 *                     \ref K_DMA2D_PFC_OUTPUT.
 *
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @return Sans objet.
 *
 */

void dma2d_setColor ( void_t p_target, uint32_t p_color );

/**
 * @fn void dma2d_setAlpha ( void_t p_target, uint32_t p_alpha );
 * @brief Cette fonction configure la valeur alpha intervenant dans le calcul de blending des PFC de premier et d'arrière
 *        plan.
 *
 * @param[in] p_target Ce paramètre contient le PFC à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_DMA2D_PFC_FOREGROUND et \ref K_DMA2D_PFC_BACKGROUND
 * @param[in] p_alpha  Ce paramètre contient une valeur alpha sur 8bits.
 *
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @return Sans objet.
 *
 */

void dma2d_setAlpha ( void_t p_target, uint32_t p_alpha );

/**
 * @fn void dma2d_setAlphaMode ( void_t p_target, uint32_t p_mode );
 * @brief Cette fonction configure le mode de blending des PFC de premier et d'arrière plan.
 *
 * @param[in] p_target Ce paramètre contient le PFC à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_DMA2D_PFC_FOREGROUND et \ref K_DMA2D_PFC_BACKGROUND
 * @param[in] p_mode   Ce paramètre contient le mode à appliquer dans le calcul de blending. Les constantes suivantes peuvent
 *                     être utilisées : \n
 *                     \ref K_DMA2D_PFC_ALPHA_DISABLE, \ref K_DMA2D_FPC_ALPHA_REPLACEMENT et \ref K_DMA2D_FPC_ALPHA_MULTIPLICATION
 *
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @return Sans objet.
 *
 */

void dma2d_setAlphaMode ( void_t p_target, uint32_t p_mode );

/**
 * @fn void dma2d_setClut ( void_t p_target, uint32_t p_baseAddr, uint32_t p_format, uint32_t p_size );
 * @brief Cette fonction configure les attributs de la CLUT d'un PFC.
 *
 * @param[in] p_target   Ce paramètre contient le PFC à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA2D_PFC_FOREGROUND et \ref K_DMA2D_PFC_BACKGROUND
 * @param[in] p_baseAddr Ce paramètre contient l'adresse sur 32bits d'une table stockant les données à copier dans la CLUT.
 * @param[in] p_format   Ce paramètre contient le format des couleurs stocké dans la CLUT. Les constantes suivantes peuvent être
 *                       utilisées : \n \ref K_DMA2D_CLUT_ARGB8888 et \ref K_DMA2D_CLUT_RGB888
 * @param[in] p_size     Ce paramètre contient la taille de la CLUT, il peut évoluer entre 1 et 256.
 *
 * @note Cette fonction ne peut pas être utilisée lorsqu'un transfert est en cours.
 * @return Sans objet.
 *
 */

void dma2d_setClut ( void_t p_target, uint32_t* p_baseAddr, uint32_t p_format, uint32_t p_size );

/**
 * @fn void dma2d_loadClut ( void_t p_target );
 * @brief Cette fonction déclenche le processus de mise à jour automatique de la CLUT. Elle copie les données présentes
 *        dans une table vers les registres internes du PFC. L'adresse de la table est configurée avec la fonction
 *        \ref dma2d_setClut.
 *
 * @param[in] p_target Ce paramètre contient le PFC à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_DMA2D_PFC_FOREGROUND et \ref K_DMA2D_PFC_BACKGROUND
 *
 * @return Sans objet.
 *
 */

void dma2d_loadClut ( void_t p_target );

/**
 * @fn void dma2d_fillClut ( void_t p_target, uint32_t* p_buf, uint32_t p_length );
 * @brief Cette fonction met à jour manuellement la CLUT. Elle copie les données de la table en paramètre vers les registres
 *        internes du PFC. Les couleurs stockées dans la CLUT sont au format ARGB8888.
 *
 * @param[in] p_target Ce paramètre contient le PFC à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_DMA2D_CLUT_FOREGROUND et \ref K_DMA2D_CLUT_BACKGROUND
 * @param[in] p_buf    Ce paramètre contient l'adresse de la table contenant les données à copier dans la CLUT.
 * @param[in] p_length Ce paramètre représent la taille de la CLUT. Elle peut évoluer de 1 à 256.
 *
 * @note Cette fonction ne doit pas être utilisée quand un chargement automatique de la CLUT est en cours.
 * @return Sans objet.
 *
 */

void dma2d_fillClut ( void_t p_target, uint32_t* p_buf, uint32_t p_length );

/**
 * @fn void dma2d_enableConfigurationErrorInterrupt ( void );
 * @brief Cette fonction active l'interruption indiquant qu'une erreur de configuration est survenue. Les
 *        erreurs de configuration sont listées dans le paragraphe 9.3.11 du document STM32F746xx Reference Manual.
 *
 * @return Sans objet.
 *
 */

void dma2d_enableConfigurationErrorInterrupt ( void );

/**
 * @fn void dma2d_enableClutTransferCompleteInterrupt ( void );
 * @brief Cette fonction active l'interruption indiquant qu'une 'CLUT' a correctement été chargée avec les
 *        données présentes à l'adresse spécifié par la fonction \ref dma2d_setClut.
 *
 * @return Sans objet.
 *
 */

void dma2d_enableClutTransferCompleteInterrupt ( void );

/**
 * @fn void dma2d_enableClutAccessErrorInterrupt ( void );
 * @brief Cette fonction active l'interruption indiquant qu'un conflit est survenu entre le CPU et la DMA2D
 *        durant le chargement automatique d'une CLUT.
 *
 * @return Sans objet.
 *
 */

void dma2d_enableClutAccessErrorInterrupt ( void );

/**
 * @fn void dma2d_enableTransferWatermarkInterrupt ( void );
 * @brief Cette fonction active l'interruption indiquant que le dernier pixels d'une ligne a été écrit
 *        dans la zone de destination. La ligne est configurée avec la fonction \ref dma2d_setLineInterrupt.
 *
 * @return Sans objet.
 *
 */

void dma2d_enableTransferWatermarkInterrupt ( void );

/**
 * @fn void dma2d_enableTransferCompleteInterrupt ( void );
 * @brief Cette fonction active l'interruption indiquant que le transfert est terminé.
 *
 * @return Sans objet.
 *
 */

void dma2d_enableTransferCompleteInterrupt ( void );

/**
 * @fn void dma2d_enableTransferErrorInterrupt ( void );
 * @brief Cette fonction active l'interruption indiquant qu'une erreur de type AHB est survenue durant le
 *        transfert.
 *
 * @return Sans objet.
 *
 */

void dma2d_enableTransferErrorInterrupt ( void );

/**
 * @fn void dma2d_disableConfigurationErrorInterrupt ( void );
 * @brief Cette fonction désactive l'interruption indiquant qu'une erreur de configuration est survenue. Les
 *        erreurs de configuration sont listées dans le paragraphe 9.3.11 du document STM32F746xx Reference Manual.
 *
 * @return Sans objet.
 *
 */

void dma2d_disableConfigurationErrorInterrupt ( void );

/**
 * @fn void dma2d_disableClutTransferCompleteInterrupt ( void );
 * @brief Cette fonction désactive l'interruption indiquant qu'une 'CLUT' a correctement été chargée avec les
 *        données présentes à l'adresse spécifié par la fonction \ref dma2d_setClut.
 *
 * @return Sans objet.
 *
 */

void dma2d_disableClutTransferCompleteInterrupt ( void );

/**
 * @fn void dma2d_disableClutAccessErrorInterrupt ( void );
 * @brief Cette fonction désactive l'interruption indiquant qu'un conflit est survenu entre le CPU et la DMA2D
 *        durant le chargement automatique d'une CLUT.
 *
 * @return Sans objet.
 *
 */

void dma2d_disableClutAccessErrorInterrupt ( void );

/**
 * @fn void dma2d_disableTransferWatermarkInterrupt ( void );
 * @brief Cette fonction désactive l'interruption indiquant que le dernier pixels d'une ligne a été écrit
 *        dans la zone de destination. La ligne est configurée avec la fonction \ref dma2d_setLineInterrupt.
 *
 * @return Sans objet.
 *
 */

void dma2d_disableTransferWatermarkInterrupt ( void );

/**
 * @fn void dma2d_disableTransferCompleteInterrupt ( void );
 * @brief Cette fonction désactive l'interruption indiquant que le transfert est terminé.
 *
 * @return Sans objet.
 *
 */

void dma2d_disableTransferCompleteInterrupt ( void );

/**
 * @fn void dma2d_disableTransferErrorInterrupt ( void );
 * @brief Cette fonction désactive l'interruption indiquant qu'une erreur de type AHB est survenue durant le
 *        transfert.
 *
 * @return Sans objet.
 *
 */

void dma2d_disableTransferErrorInterrupt ( void );


/**
 * @fn void dma2d_clearConfigurationErrorInterruptFlag ( void );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant qu'une erreur de configuration est
 *        survenue. Les erreurs de configuration sont listées dans le paragraphe 9.3.11 du document
 *        STM32F746xx Reference Manual.
 *
 * @return Sans objet.
 *
 */

void dma2d_clearConfigurationErrorInterruptFlag ( void );

/**
 * @fn void dma2d_clearClutTransferCompleteInterruptFlag ( void );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant qu'une 'CLUT' a correctement été
 *        chargée avec les données présentes à l'adresse spécifié par la fonction \ref dma2d_setClut.
 *
 * @return Sans objet.
 *
 */

void dma2d_clearClutTransferCompleteInterruptFlag ( void );

/**
 * @fn void dma2d_clearClutAccessErrorInterruptFlag ( void );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant qu'un conflit est survenu entre
 *        le CPU et la DMA2D durant le chargement automatique d'une CLUT.
 *
 * @return Sans objet.
 *
 */

void dma2d_clearClutAccessErrorInterruptFlag ( void );

/**
 * @fn void dma2d_clearTransferWatermarkInterruptFlag ( void );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant que le dernier pixels d'une ligne
 *        a été écrit dans la zone de destination. La ligne est configurée avec la fonction
 *        \ref dma2d_setLineInterrupt.
 *
 * @return Sans objet.
 *
 */

void dma2d_clearTransferWatermarkInterruptFlag ( void );

/**
 * @fn void dma2d_clearTransferCompleteInterruptFlag ( void );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant que le transfert est terminé.
 *
 * @return Sans objet.
 *
 */

void dma2d_clearTransferCompleteInterruptFlag ( void );

/**
 * @fn void dma2d_clearTransferErrorInterruptFlag ( void );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant qu'une erreur de type AHB est
 *        survenue durant le transfert.
 *
 * @return Sans objet.
 *
 */

void dma2d_clearTransferErrorInterruptFlag ( void );

/**
 * @fn uint32_t dma2d_getConfigurationErrorInterruptFlag ( void );
 * @brief Cette fonction retourne la valeur du drapeau d'interruption indiquant qu'une erreur de configuration
 *        est survenue. Les erreurs de configuration sont listées dans le paragraphe 9.3.11 du document
 *        STM32F746xx Reference Manual</a>.
 *
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t dma2d_getConfigurationErrorInterruptFlag ( void );

/**
 * @fn uint32_t dma2d_getClutTransferCompleteInterruptFlag ( void );
 * @brief Cette fonction retourne la valeur du drapeau d'interruption indiquant qu'une 'CLUT' a correctement
 *        été chargée avec les données présentes à l'adresse spécifié par la fonction \ref dma2d_setClut.
 *
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t dma2d_getClutTransferCompleteInterruptFlag ( void );

/**
 * @fn uint32_t dma2d_getClutAccessErrorInterruptFlag ( void );
 * @brief Cette fonction retourne la valeur du drapeau d'interruption indiquant qu'un conflit est survenu
 *        entre le CPU et la DMA2D durant le chargement automatique d'une CLUT.
 *
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t dma2d_getClutAccessErrorInterruptFlag ( void );

/**
 * @fn uint32_t dma2d_getTransferWatermarkInterruptFlag ( void );
 * @brief Cette fonction retourne la valeur du drapeau d'interruption indiquant que le dernier pixels d'une
 *        ligne a été écrit dans la zone de destination. La ligne est configurée avec la fonction
 *        \ref dma2d_setLineInterrupt.
 *
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t dma2d_getTransferWatermarkInterruptFlag ( void );

/**
 * @fn uint32_t dma2d_getTransferCompleteInterruptFlag ( void );
 * @brief Cette fonction retourne la valeur du drapeau d'interruption indiquant que le transfert est terminé.
 *
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t dma2d_getTransferCompleteInterruptFlag ( void );

/**
 * @fn uint32_t dma2d_getTransferErrorInterruptFlag ( void );
 * @brief Cette fonction retourne la valeur du drapeau d'interruption indiquant qu'une erreur de type AHB
 *        est survenue durant le transfert.
 *
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t dma2d_getTransferErrorInterruptFlag ( void );

/**
 *
 */

#endif


