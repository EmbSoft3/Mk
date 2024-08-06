/**
*
* @copyright Copyright (C) 2018 RENARD Mathieu. All rights reserved.
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
* @file mk_peripheral_dma_constants.h
* @brief Déclaration des constantes dédiées au périphérique DMA.
* @date 21 oct. 2018
*
*/

#ifndef MK_PERIPHERAL_DMA_CONSTANTS_H
#define MK_PERIPHERAL_DMA_CONSTANTS_H

/**
 * @def K_DMA1
 * @brief Adresse de base du périphérique DMA1.
 */

#define K_DMA1 ( addr_t ) 0x40026000

/**
 * @def K_DMA2
 * @brief Adresse de base du périphérique DMA2.
 */

#define K_DMA2 ( addr_t ) 0x40026400

/**
 * @def K_DMA_STREAM0
 * @brief Offset du registre DMA_S0CR par rapport à l'adresse de base du périphérique DMA.
 */

#define K_DMA_STREAM0 0x00000000

/**
 * @def K_DMA_STREAM1
 * @brief Offset du registre DMA_S1CR par rapport à l'adresse de base du périphérique DMA.
 */

#define K_DMA_STREAM1 0x00000001

/**
 * @def K_DMA_STREAM2
 * @brief Offset du registre DMA_S2CR par rapport à l'adresse de base du périphérique DMA.
 */

#define K_DMA_STREAM2 0x00000002

/**
 * @def K_DMA_STREAM3
 * @brief Offset du registre DMA_S3CR par rapport à l'adresse de base du périphérique DMA.
 */

#define K_DMA_STREAM3 0x00000003

/**
 * @def K_DMA_STREAM4
 * @brief Offset du registre DMA_S4CR par rapport à l'adresse de base du périphérique DMA.
 */

#define K_DMA_STREAM4 0x00000004

/**
 * @def K_DMA_STREAM5
 * @brief Offset du registre DMA_S5CR par rapport à l'adresse de base du périphérique DMA.
 */

#define K_DMA_STREAM5 0x00000005

/**
 * @def K_DMA_STREAM6
 * @brief Offset du registre DMA_S6CR par rapport à l'adresse de base du périphérique DMA.
 */

#define K_DMA_STREAM6 0x00000006

/**
 * @def K_DMA_STREAM7
 * @brief Offset du registre DMA_S7CR par rapport à l'adresse de base du périphérique DMA.
 */

#define K_DMA_STREAM7 0x00000007

/**
 * @def K_DMA_CHANNEL0
 * @brief Constante dédiée à la fonction dma_setChannel(). \n
 *        Sélection du canal DMA.
 */

#define K_DMA_CHANNEL0 0x00000000

/**
 * @def K_DMA_CHANNEL1
 * @brief Constante dédiée à la fonction dma_setChannel(). \n
 *        Sélection du canal DMA.
 */

#define K_DMA_CHANNEL1 0x02000000

/**
 * @def K_DMA_CHANNEL2
 * @brief Constante dédiée à la fonction dma_setChannel(). \n
 *        Sélection du canal DMA.
 */

#define K_DMA_CHANNEL2 0x04000000

/**
 * @def K_DMA_CHANNEL3
 * @brief Constante dédiée à la fonction dma_setChannel(). \n
 *        Sélection du canal DMA.
 */

#define K_DMA_CHANNEL3 0x06000000

/**
 * @def K_DMA_CHANNEL4
 * @brief Constante dédiée à la fonction dma_setChannel(). \n
 *        Sélection du canal DMA.
 */

#define K_DMA_CHANNEL4 0x08000000

/**
 * @def K_DMA_CHANNEL5
 * @brief Constante dédiée à la fonction dma_setChannel(). \n
 *        Sélection du canal DMA.
 */

#define K_DMA_CHANNEL5 0x0A000000

/**
 * @def K_DMA_CHANNEL6
 * @brief Constante dédiée à la fonction dma_setChannel(). \n
 *        Sélection du canal DMA.
 */

#define K_DMA_CHANNEL6 0x0C000000

/**
 * @def K_DMA_CHANNEL7
 * @brief Constante dédiée à la fonction dma_setChannel(). \n
 *        Sélection du canal DMA.
 */

#define K_DMA_CHANNEL7 0x0E000000

/**
 * @def K_DMA_BURST_SINGLE
 * @brief Constante dédiée aux fonctions dma_setMemoryBurst() et dma_setPeripheralBurst(). \n
 *        Configuration des caractèristiques du mode BURST.
 */

#define K_DMA_BURST_SINGLE 0x00000000

/**
 * @def K_DMA_BURST_4BEATS
 * @brief Constante dédiée aux fonctions dma_setMemoryBurst() et dma_setPeripheralBurst(). \n
 *        Configuration des caractèristiques du mode BURST.
 */

#define K_DMA_BURST_4BEATS 0x00000001

/**
 * @def K_DMA_BURST_8BEATS
 * @brief Constante dédiée aux fonctions dma_setMemoryBurst() et dma_setPeripheralBurst(). \n
 *        Configuration des caractèristiques du mode BURST.
 */

#define K_DMA_BURST_8BEATS 0x00000002

/**
 * @def K_DMA_BURST_16BEATS
 * @brief Constante dédiée aux fonctions dma_setMemoryBurst() et dma_setPeripheralBurst(). \n
 *        Configuration des caractèristiques du mode BURST.
 */

#define K_DMA_BURST_16BEATS 0x0000003

/**
 * @def K_DMA_MEM0
 * @brief Constante dédiée aux fonctions dma_setMemoryTarget() et dma_getMemoryTarget(). \n
 *        Configuration et indication de la zone mémoire couramment utilisée durant le transfert.
 */

#define K_DMA_MEM0 0x00000000

/**
 * @def K_DMA_MEM1
 * @brief Constante dédiée aux fonctions dma_setMemoryTarget() et dma_getMemoryTarget(). \n
 *        Configuration et indication de la zone mémoire couramment utilisée durant le transfert.
 */

#define K_DMA_MEM1 0x00000001

/**
 * @def K_DMA_PRIORITY_LOW
 * @brief Constante dédiée à la fonction dma_setPriority(). \n
 *        Configuration de la priorité du flux DMA.
 */

#define K_DMA_PRIORITY_LOW 0x00000000

/**
 * @def K_DMA_PRIORITY_MEDIUM
 * @brief Constante dédiée à la fonction dma_setPriority(). \n
 *        Configuration de la priorité du flux DMA.
 */

#define K_DMA_PRIORITY_MEDIUM 0x00010000

/**
 * @def K_DMA_PRIORITY_HIGH
 * @brief Constante dédiée à la fonction dma_setPriority(). \n
 *        Configuration de la priorité du flux DMA.
 */

#define K_DMA_PRIORITY_HIGH 0x00020000

/**
 * @def K_DMA_PRIORITY_VERY_HIGH
 * @brief Constante dédiée à la fonction dma_setPriority(). \n
 *        Configuration de la priorité du flux DMA.
 */

#define K_DMA_PRIORITY_VERY_HIGH 0x00030000

/**
 * @def K_DMA_PERIPHERAL_OFFSET_PSIZE
 * @brief Constante dédiée à la fonction dma_setPeripheralOffset(). \n
 *        Configuration de la taille de l'offset appliquée à l'adresse du périphérique.
 */

#define K_DMA_PERIPHERAL_OFFSET_PSIZE 0x00000000

/**
 * @def K_DMA_PERIPHERAL_OFFSET_32BITS
 * @brief Constante dédiée à la fonction dma_setPeripheralOffset(). \n
 *        Configuration de la taille de l'offset appliquée à l'adresse du périphérique.
 */

#define K_DMA_PERIPHERAL_OFFSET_32BITS 0x00008000

/**
 * @def K_DMA_DIRECTION_PERIPHERAL_TO_MEMORY
 * @brief Constante dédiée à la fonction dma_setDirection(). \n
 *        Configuration de la direction du flux DMA.
 */

#define K_DMA_DIRECTION_PERIPHERAL_TO_MEMORY 0x00000000

/**
 * @def K_DMA_DIRECTION_MEMORY_TO_PERIPHERAL
 * @brief Constante dédiée à la fonction dma_setDirection(). \n
 *        Configuration de la direction du flux DMA.
 */

#define K_DMA_DIRECTION_MEMORY_TO_PERIPHERAL 0x00000040

/**
 * @def K_DMA_DIRECTION_MEMORY_TO_MEMORY
 * @brief Constante dédiée à la fonction dma_setDirection(). \n
 *        Configuration de la direction du flux DMA.
 */

#define K_DMA_DIRECTION_MEMORY_TO_MEMORY 0x00000080

/**
 * @def K_DMA_SIZE_8BITS
 * @brief Constante dédiée aux fonctions dma_setMemoryDataSize() et dma_setPeripheralDataSize(). \n
 *        Configuration de la taille des données d'entrée/sortie DMA.
 */

#define K_DMA_SIZE_8BITS 0x00000000

/**
 * @def K_DMA_SIZE_16BITS
 * @brief Constante dédiée aux fonctions dma_setMemoryDataSize() et dma_setPeripheralDataSize(). \n
 *        Configuration de la taille des données d'entrée/sortie DMA.
 */

#define K_DMA_SIZE_16BITS 0x00000001

/**
 * @def K_DMA_SIZE_32BITS
 * @brief Constante dédiée aux fonctions dma_setMemoryDataSize() et dma_setPeripheralDataSize(). \n
 *        Configuration de la taille des données d'entrée/sortie DMA.
 */

#define K_DMA_SIZE_32BITS 0x00000002

/**
 * @def K_DMA_FLOW_CTRL_DMA
 * @brief Constante dédiée à la fonction dma_setFlowCtrl(). \n
 *        Configuration du controleur de flux DMA.
 */

#define K_DMA_FLOW_CTRL_DMA 0x00000000

/**
 * @def K_DMA_FLOW_CTRL_PERIPHERAL
 * @brief Constante dédiée à la fonction dma_setFlowCtrl(). \n
 *        Configuration du controleur de flux DMA.
 * @note Uniquement le périphérique SDMMC1 supporte ce mode.
 */

#define K_DMA_FLOW_CTRL_PERIPHERAL 0x00000020

/**
 * @def K_DMA_FIFO_THRESHOLD_25_PERCENTS_FULL
 * @brief Constante dédiée à la fonction dma_setFifoThreshold(). \n
 *        Configuration du seuil de fonctionnement du FIFO associé à un flux.
 */

#define K_DMA_FIFO_THRESHOLD_25_PERCENTS_FULL 0x00000000

/**
 * @def K_DMA_FIFO_THRESHOLD_50_PERCENTS_FULL
 * @brief Constante dédiée à la fonction dma_setFifoThreshold(). \n
 *        Configuration du seuil de fonctionnement du FIFO associé à un flux.
 */

#define K_DMA_FIFO_THRESHOLD_50_PERCENTS_FULL 0x00000001

/**
 * @def K_DMA_FIFO_THRESHOLD_75_PERCENTS_FULL
 * @brief Constante dédiée à la fonction dma_setFifoThreshold(). \n
 *        Configuration du seuil de fonctionnement du FIFO associé à un flux.
 */

#define K_DMA_FIFO_THRESHOLD_75_PERCENTS_FULL 0x00000002

/**
 * @def K_DMA_FIFO_THRESHOLD_100_PERCENTS_FULL
 * @brief Constante dédiée à la fonction dma_setFifoThreshold(). \n
 *        Configuration du seuil de fonctionnement du FIFO associé à un flux.
 */

#define K_DMA_FIFO_THRESHOLD_100_PERCENTS_FULL 0x00000003

/**
 * @def K_DMA_FIFO_IS_BETWEEN_0_25_PERCENTS
 * @brief Constante dédiée à la fonction dma_getFifoStatus(). \n
 *        Récupération de l'état du FIFO.
 * @note L'intervalle est ]0;25[
 */

#define K_DMA_FIFO_IS_BETWEEN_0_25_PERCENTS 0x00000000

/**
 * @def K_DMA_FIFO_IS_BETWEEN_25_50_PERCENTS
 * @brief Constante dédiée à la fonction dma_getFifoStatus(). \n
 *        Récupération de l'état du FIFO.
 * @note L'intervalle est [25;50[
 */

#define K_DMA_FIFO_IS_BETWEEN_25_50_PERCENTS 0x00000001

/**
 * @def K_DMA_FIFO_IS_BETWEEN_50_75_PERCENTS
 * @brief Constante dédiée à la fonction dma_getFifoStatus(). \n
 *        Récupération de l'état du FIFO.
 * @note L'intervalle est [50;75[
 */

#define K_DMA_FIFO_IS_BETWEEN_50_75_PERCENTS 0x00000002

/**
 * @def K_DMA_FIFO_IS_BETWEEN_75_100_PERCENTS
 * @brief Constante dédiée à la fonction dma_getFifoStatus(). \n
 *        Récupération de l'état du FIFO.
 * @note L'intervalle est [75;100[
 */

#define K_DMA_FIFO_IS_BETWEEN_75_100_PERCENTS 0x00000003

/**
 * @def K_DMA_FIFO_IS_EMPTY
 * @brief Constante dédiée à la fonction dma_getFifoStatus(). \n
 *        Récupération de l'état du FIFO.
 */

#define K_DMA_FIFO_IS_EMPTY 0x00000004

/**
 * @def K_DMA_FIFO_IS_FULL
 * @brief Constante dédiée à la fonction dma_getFifoStatus(). \n
 *        Récupération de l'état du FIFO.
 */

#define K_DMA_FIFO_IS_FULL 0x00000005

/**
 * @def K_DMA_INTERRUPT_TRANSFERT_COMPLETE
 * @brief Constante dédiée aux fonctions dma_enableInterrupt() et dma_disableInterrupt(). \n
 *        Configuration des interruptions DMA.
 */

#define K_DMA_INTERRUPT_TRANSFERT_COMPLETE 0x00000010

/**
 * @def K_DMA_INTERRUPT_TRANSFERT_HALF
 * @brief Constante dédiée aux fonctions dma_enableInterrupt() et dma_disableInterrupt(). \n
 *        Configuration des interruptions DMA.
 */

#define K_DMA_INTERRUPT_TRANSFERT_HALF 0x00000008

/**
 * @def K_DMA_INTERRUPT_TRANSFERT_ERROR
 * @brief Constante dédiée aux fonctions dma_enableInterrupt() et dma_disableInterrupt(). \n
 *        Configuration des interruptions DMA.
 */

#define K_DMA_INTERRUPT_TRANSFERT_ERROR 0x00000004

/**
 * @def K_DMA_INTERRUPT_TRANSFERT_DIRECT_MODE_ERROR
 * @brief Constante dédiée aux fonctions dma_enableInterrupt() et dma_disableInterrupt(). \n
 *        Configuration des interruptions DMA.
 */

#define K_DMA_INTERRUPT_TRANSFERT_DIRECT_MODE_ERROR 0x00000002

/**
 *
 */

#endif


