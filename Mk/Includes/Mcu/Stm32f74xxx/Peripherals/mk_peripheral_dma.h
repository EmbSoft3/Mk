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
* @file mk_peripheral_dma.h
* @brief Déclaration des fonctions dédiées au périphérique DMA.
* @date 21 oct. 2018
*
*/

#ifndef MK_PERIPHERAL_DMA_H
#define MK_PERIPHERAL_DMA_H

/**
 * @fn void dma_enableStream ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction active un transfert de données DMA.
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note Avant l'appel de cette fonction, l'ensemble des drapeaux d'interruptions correspondant au flux DMA configuré doivent être
 *       réinitialisés. Les fonctions \ref dma_clearTransferCompleteInterruptFlag, \ref dma_clearTransferHalfInterruptFlag,
 *       \ref dma_clearTransferErrorInterruptFlag, \ref dma_clearDirectModeErrorInterruptFlag et \ref dma_clearFifoErrorInterruptFlag
 *       peuvent être utilisées.
 * @return Sans objet.
 *
 */

void dma_enableStream ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_disableStream ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction désactive un transfert DMA lancé. La désactivation devient effective lorsque la fonction \ref dma_getStatus
 *        retourne la valeur 0.
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return Sans objet.
 *
 */

void dma_disableStream ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_setChannel ( void_t p_addr, uint32_t p_stream, uint32_t p_channel );
 * @brief Cette fonction attribue un canal à un flux de donnée DMA.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_channel Ce paramètre contient le numéro du canal DMA. Les constantes suivantes peuvent être tuilisées : \n
 *                      \ref K_DMA_CHANNEL0 à \ref K_DMA_CHANNEL7
 *
 * @note   Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé. La fonction \ref dma_getStatus permet de
 *         s'assurer de la désactivation du flux.
 * @return Sans objet.
 *
 */

void dma_setChannel ( void_t p_addr, uint32_t p_stream, uint32_t p_channel );

/**
 * @fn void dma_setMemoryDataSize ( void_t p_addr, uint32_t p_stream, uint32_t p_size );
 * @brief Cette fonction configure la taille d'une transaction DMA.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_size    Ce paramètre contient la taille de la transaction. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_SIZE_8BITS, \ref K_DMA_SIZE_16BITS, \ref K_DMA_SIZE_32BITS
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_setMemoryDataSize ( void_t p_addr, uint32_t p_stream, uint32_t p_size );

/**
 * @fn void dma_setPeripheralDataSize ( void_t p_addr, uint32_t p_stream, uint32_t p_size );
 * @brief Cette fonction configure la taille d'une transaction DMA.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_size    Ce paramètre contient la taille de la transaction. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_SIZE_8BITS, \ref K_DMA_SIZE_16BITS, \ref K_DMA_SIZE_32BITS
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_setPeripheralDataSize ( void_t p_addr, uint32_t p_stream, uint32_t p_size );

/**
 * @fn void dma_setPriority ( void_t p_addr, uint32_t p_stream, uint32_t p_priority );
 * @brief Cette fonction configure la priorité du flux DMA.
 *
 * @param[in] p_addr     Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                       \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream   Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_priority Ce paramètre contient la priorité du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_PRIORITY_LOW, \ref K_DMA_PRIORITY_MEDIUM, \ref K_DMA_PRIORITY_HIGH, \ref K_DMA_PRIORITY_VERY_HIGH
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_setPriority ( void_t p_addr, uint32_t p_stream, uint32_t p_priority );

/**
 * @fn void dma_setDirection ( void_t p_addr, uint32_t p_stream, uint32_t p_mode );
 * @brief Cette fonction configure la direction du transfert DMA.
 *
 * @param[in] p_addr     Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                       \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream   Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_mode     Ce paramètre contient la direction du transfert DMA. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_DIRECTION_PERIPHERAL_TO_MEMORY, \ref K_DMA_DIRECTION_MEMORY_TO_PERIPHERAL,
 *                       \ref K_DMA_DIRECTION_MEMORY_TO_MEMORY
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @warning Seul la DMA2 peut effectuer des transfert mémoire à mémoire.
 * @return  Sans objet.
 *
 */

void dma_setDirection ( void_t p_addr, uint32_t p_stream, uint32_t p_mode );

/**
 * @fn void dma_setFlowCtrl ( void_t p_addr, uint32_t p_stream, uint32_t p_mode );
 * @brief Cette fonction configure le contrôleur de flux. Le contrôleur de flux est l'entité qui controle le nombre de données à transférer.
 *        Lorsque la DMA est le contrôleur de flux, le logiciel configure le nombre de données à transférer en utilisant la fonction
 *        \ref dma_setCount.\n
 *        Lorsque le périphérique est le contrôleur de flux, le nombre de données à transférer est inconnues. C'est le périphérique qui
 *        signal à la DMA la dernière données du transfert via le matériel. Seul le périphérique SDMMC1 supporte ce mode.
 *
 * @param[in] p_addr     Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                       \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream   Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_mode     Ce paramètre contient le contrôleur de flux. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_FLOW_CTRL_DMA, \ref K_DMA_FLOW_CTRL_PERIPHERAL,
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé. En mode memory-to-memory, le contrôleur de flux
 *          est obligatoirement la DMA.
 * @return  Sans objet.
 *
 */

void dma_setFlowCtrl ( void_t p_addr, uint32_t p_stream, uint32_t p_mode );

/**
 * @fn void dma_enableMemoryPostIncrementation ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction active le mode post-incrémentation. Dans ce mode, le pointeur de mémoire est incrémenté après chaque transfert.
 *        La valeur d'incrémentation est déterminée par la fonction \ref dma_setMemoryDataSize.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_enableMemoryPostIncrementation ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_disableMemoryPostIncrementation ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction désactive le mode post-incrémentation. Dans ce mode, le pointeur de mémoire est fixe.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_disableMemoryPostIncrementation ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_enablePeripheralPostIncrementation ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction active le mode post-incrémentation. Dans ce mode, le pointeur du périphérique est incrémenté après chaque transfert.
 *        La valeur d'incrémentation est déterminée par la fonction \ref dma_setPeripheralDataSize.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_enablePeripheralPostIncrementation ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_disablePeripheralPostIncrementation ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction désactive le mode post-incrémentation. Dans ce mode, le pointeur du périphérique est fixe.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_disablePeripheralPostIncrementation ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_setPeripheralOffset ( void_t p_addr, uint32_t p_stream, uint32_t p_mode );
 * @brief Cette fonction configure la valeur d'incrémentation du périphérique. Si la constante \ref K_DMA_PERIPHERAL_OFFSET_PSIZE est
 *        utilisée, la valeur d'incrémentation est déterminée par la fonction \ref dma_setPeripheralDataSize. Sinon lorsque la
 *        constante \ref K_DMA_PERIPHERAL_OFFSET_32BITS est utilisée, la valeur d'incrémentation est fixe et égale à 32 bits.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_mode  Ce paramètre contient la valeur d'incrémentation à appliquer. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_PERIPHERAL_OFFSET_PSIZE à \ref K_DMA_PERIPHERAL_OFFSET_32BITS
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.\n
 *          Si pour le périphérique, le mode post-incrémentation est désactivé, cette fonction n'a aucun effet.
 *          Lors de l'activation du flux, si le mode direct est activé ou si le mode burst n'est pas configuré en mode \ref K_DMA_BURST_SINGLE
 *          alors le matériel sélectionne automatiquement la valeur \ref K_DMA_PERIPHERAL_OFFSET_PSIZE.
 * @return  Sans objet.
 *
 */

void dma_setPeripheralOffset ( void_t p_addr, uint32_t p_stream, uint32_t p_mode );

/**
 * @fn void dma_setMemoryBurst ( void_t p_addr, uint32_t p_stream, uint32_t p_mode );
 * @brief Cette fonction configure le nombre de transactions constituant un burst. La taille d'une transaction peut être 1, 2 ou 4 octets.
 *        Lorsque le burst est configuré avec la constante \ref K_DMA_BURST_SINGLE, chaque requête DMA déclenche un transfert de taille
 *        1, 2 ou 4 octets dépendant de la valeur configurée avec la fonction \ref dma_setPeripheralDataSize.
 *        Sinon, lorsque le burst est configuré avec les constantes \ref K_DMA_BURST_4BEATS, \ref K_DMA_BURST_8BEATS ou
 *        \ref K_DMA_BURST_16BEATS, chaque requête DMA déclenche un transfert de taille (1, 2 ou 4 octets) * NOMBRE_TRANSACTIONS dépendant
 *        de la valeur configurée avec la fonction \ref dma_setMemoryDataSize.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_mode    Ce paramètre contient le nombre de transactions constituant un burst. Les constantes suivantes peuvent être
 *                      utilisées : \n
 *                      \ref K_DMA_BURST_SINGLE, \ref K_DMA_BURST_4BEATS, \ref K_DMA_BURST_8BEATS, \ref K_DMA_BURST_16BEATS
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @warning La taille du burst multipliées par la taille des données ne doit pas dépasser la taille du FIFO (16 octets).
 * @return  Sans objet.
 *
 */

void dma_setMemoryBurst ( void_t p_addr, uint32_t p_stream, uint32_t p_mode );

/**
 * @fn void dma_setPeripheralBurst ( void_t p_addr, uint32_t p_stream, uint32_t p_mode );
 * @brief Cette fonction configure le nombre de transactions constituant un burst. La taille d'une transaction peut être 1, 2 ou 4 octets.
 *        Lorsque le burst est configuré avec la constante \ref K_DMA_BURST_SINGLE, chaque requête DMA déclenche un transfert de taille
 *        1, 2 ou 4 octets dépendant de la valeur configurée avec la fonction \ref dma_setPeripheralDataSize.
 *        Sinon, lorsque le burst est configuré avec les constantes \ref K_DMA_BURST_4BEATS, \ref K_DMA_BURST_8BEATS ou
 *        \ref K_DMA_BURST_16BEATS, chaque requête DMA déclenche un transfert de taille (1, 2 ou 4 octets) * NOMBRE_TRANSACTIONS dépendant
 *        de la valeur configurée avec la fonction \ref dma_setPeripheralDataSize.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_mode    Ce paramètre contient le nombre de transactions constituant un burst. Les constantes suivantes peuvent être
 *                      utilisées : \n
 *                      \ref K_DMA_BURST_SINGLE, \ref K_DMA_BURST_4BEATS, \ref K_DMA_BURST_8BEATS, \ref K_DMA_BURST_16BEATS
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @warning La taille du burst multipliées par la taille des données ne doit pas dépasser la taille du FIFO (16 octets).
 * @return  Sans objet.
 *
 */

void dma_setPeripheralBurst ( void_t p_addr, uint32_t p_stream, uint32_t p_mode );


/**
 * @fn void dma_setFifoThreshold ( void_t p_addr, uint32_t p_stream, uint32_t p_threshold );
 * @brief Cette fonction configure le seuil de déclenchement du FIFO qui initie une transaction DMA.
 *
 * @param[in] p_addr     Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                       \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream   Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_threshold Ce paramètre contient le seuil de détection du FIFO. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_FIFO_THRESHOLD_25_PERCENTS_FULL, \ref K_DMA_FIFO_THRESHOLD_50_PERCENTS_FULL,
 *                       \ref K_DMA_FIFO_THRESHOLD_75_PERCENTS_FULL, \ref K_DMA_FIFO_THRESHOLD_100_PERCENTS_FULL
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @warning La valeur du seuil doit être un multiple entier de la taille de la transaction DMA. La taille d'une transaction doit être
 *          inférieure ou égale au seuil de déclenchement du FIFO.
 * @return  Sans objet.
 *
 */

void dma_setFifoThreshold ( void_t p_addr, uint32_t p_stream, uint32_t p_threshold );

/**
 * @fn void dma_enablePingPong ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction active le mode pingpong. la conséquence est que le pointeur mémoire de base est permuter à la fin du transfert
 *        DMA (zone 1 vers zone 2 ou inversement).
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_enablePingPong ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_disablePingPong ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction désactive le mode pingpong.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_disablePingPong ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_setMemoryTarget ( void_t p_addr, uint32_t p_stream, uint32_t p_target );
 * @brief Cette fonction sélectionne la première zone mémoire à utiliser en mode pingpong.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_target  Ce paramètre contient la zone mémoire à utiliser. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_MEM0 et \ref K_DMA_MEM1
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_setMemoryTarget ( void_t p_addr, uint32_t p_stream, uint32_t p_target );

/**
 * @fn void dma_enableCircularMode ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction active le mode buffer circulaire. Ce mode permet la gestion d'un flux de données continu.
 *        Dans ce mode, lorsque le transfert DMA est terminé, le nombre de données à transférer est automatiquement rechargé pour
 *        permettre aux requête DMA d'être déservies.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @warning Ce mode est interdit lorsque le périphérique est le contrôleur de flux. Ce contrôleur est configuré à partir de la
 *          fonction \ref dma_setFlowCtrl.
 * @return  Sans objet.
 *
 */

void dma_enableCircularMode ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_disableCircularMode ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction désactive le mode circulaire.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_disableCircularMode ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_enableDirectMode ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction active le mode direct. Dans ce mode, les seuils de déclenchement du FIFO ne sont pas utilisé. Ce mode est utilisé quand
 *        le système souhaite immédiatement déclencher un transfert après chaque requête DMA.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé. Ce mode ne peut pas être utilisé pour des
 *          transfert mémoire à mémoire.\n
 * @warning Il est nécessaire que la taille des transfert entre la source et la destination soit égales.
 * @return  Sans objet.
 *
 */

void dma_enableDirectMode ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_disableDirectMode ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction désactive le mode direct.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @warning Cette fonction active automatiquement le mode circulaire à l'activation du flux si le mode direct est désactivé et que le
 *          controleur de flux est le périphérique (A VERIFIER).
 * @return  Sans objet.
 *
 */

void dma_disableDirectMode ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_setPeripheralAddr ( void_t p_addr, uint32_t p_stream, uint32_t p_baseAddr );
 * @brief Cette fonction configure l'adresse de base du périphérique.
 *
 * @param[in] p_addr     Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                       \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream   Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_baseAddr Ce paramètre contient une adresse mémoire sur 32 bits.
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé.
 * @return  Sans objet.
 *
 */

void dma_setPeripheralAddr ( void_t p_addr, uint32_t p_stream, uint32_t p_baseAddr );

/**
 * @fn void dma_setMemoryAddr1 ( void_t p_addr, uint32_t p_stream, uint32_t p_baseAddr );
 * @brief Cette fonction configure l'adresse de base de la zone mémoire 1.
 *
 * @param[in] p_addr     Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                       \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream   Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_baseAddr Ce paramètre contient une adresse mémoire sur 32 bits.
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé ou lorsque le canal DMA est en mode pingpong et
 *          que la zone mémoire active est la zone mémoire 2.
 *          La fonction \ref dma_getMemoryTarget peut être utilisée pour connaitre la zone mémoire active.
 * @return  Sans objet.
 *
 */

void dma_setMemoryAddr1 ( void_t p_addr, uint32_t p_stream, uint32_t p_baseAddr );

/**
 * @fn void dma_setMemoryAddr2 ( void_t p_addr, uint32_t p_stream, uint32_t p_baseAddr );
 * @brief Cette fonction configure l'adresse de base de la zone mémoire 2.
 *
 * @param[in] p_addr     Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                       \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream   Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                       \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_baseAddr Ce paramètre contient une adresse mémoire sur 32 bits.
 *
 * @note    Cette fonction doit être appelée uniquement lorsque le flux DMA est désactivé ou lorsque le canal DMA est en mode pingpong et
 *          que la zone mémoire active est la zone mémoire 1.
 *          La fonction \ref dma_getMemoryTarget peut être utilisée pour connaitre la zone mémoire active.
 * @return  Sans objet.
 *
 */

void dma_setMemoryAddr2 ( void_t p_addr, uint32_t p_stream, uint32_t p_baseAddr );

/**
 * @fn dma_getCount ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction configure le nombre de données à transférer.
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_stream Ce paramètre contient une valeur entre 0 et 65535. Une valeur 0 n'aboutit à aucune transaction même si le flux est
 *                     activé.
 *
 * @return Sans objet.
 *
 */

void dma_setCount ( void_t p_addr, uint32_t p_stream, uint32_t p_count );

/**
 * @fn void dma_enableInterrupt ( void_t p_addr, uint32_t p_stream, uint32_t p_flag );
 * @brief Cette fonction active une ou plusieurs interruptions spécifiques.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_flag    Ce paramètre contient l'interruption à activer. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_INTERRUPT_TRANSFERT_COMPLETE, \ref K_DMA_INTERRUPT_TRANSFERT_HALF, \ref K_DMA_INTERRUPT_TRANSFERT_ERROR,
 *                      \ref K_DMA_INTERRUPT_TRANSFERT_DIRECT_MODE_ERROR
 *
 * @return  Sans objet.
 *
 */

void dma_enableInterrupt ( void_t p_addr, uint32_t p_stream, uint32_t p_flag );

/**
 * @fn void dma_disableInterrupt ( void_t p_addr, uint32_t p_stream, uint32_t p_flag );
 * @brief Cette fonction désactive une ou plusieurs interruptions spécifiques.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in] p_flag    Ce paramètre contient l'interruption à désactiver. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_INTERRUPT_TRANSFERT_COMPLETE, \ref K_DMA_INTERRUPT_TRANSFERT_HALF, \ref K_DMA_INTERRUPT_TRANSFERT_ERROR,
 *                      \ref K_DMA_INTERRUPT_TRANSFERT_DIRECT_MODE_ERROR
 *                      L'erreur de transfert est déclenchée lorsqu'une erreur d'accès DMA en lecture ou écriture survient le bus ou lorsque
 *                      en mode Pingpong, l'adresse de base est modifiée alors que la région était active.
 *                      L'erreur en mode direct se déclenche uniquement en mode "Peripheral To Memory" quand le pointeur mémoire est fixe et
 *                      qu'une requête DMA est déclenchée alors que la précédente n'a pas été entièrement traitée (transaction non accordée
 *                      par le bus).
 *
 * @return  Sans objet.
 *
 */

void dma_disableInterrupt ( void_t p_addr, uint32_t p_stream, uint32_t p_flag );

/**
 * @fn void dma_enableFifoErrorInterrupt ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction active l'interruption indiquant qu'une erreur de type FIFO est survenue. Les erreurs détectée sont l'overrun,
 *        l'underrun ou une configuration invalide.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return  Sans objet.
 *
 */

void dma_enableFifoErrorInterrupt ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_disableFifoErrorInterrupt ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction désactive l'interruption indiquant qu'une erreur de type FIFO est survenue.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return  Sans objet.
 *
 */

void dma_disableFifoErrorInterrupt ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_clearTransferCompleteInterruptFlag ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant la fin d'un transfert DMA.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return  Sans objet.
 *
 */

void dma_clearTransferCompleteInterruptFlag ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_clearTransferCompleteInterruptFlag ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant que la moitié d'un transfert DMA a été effectué.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return  Sans objet.
 *
 */

void dma_clearTransferHalfInterruptFlag ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_clearTransferErrorInterruptFlag ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant qu'une erreur est survenue durant le transfert DMA.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return  Sans objet.
 *
 */

void dma_clearTransferErrorInterruptFlag ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_clearDirectModeErrorInterruptFlag ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant qu'une erreur est survenue en mode Direct.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return  Sans objet.
 *
 */

void dma_clearDirectModeErrorInterruptFlag ( void_t p_addr, uint32_t p_stream );

/**
 * @fn void dma_clearDirectModeErrorInterruptFlag ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction remet à zéro le drapeau d'interruption indiquant qu'une erreur est survenue au niveau du FIFO DMA.
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                      \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream  Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return  Sans objet.
 *
 */

void dma_clearFifoErrorInterruptFlag ( void_t p_addr, uint32_t p_stream );

/**
 * @fn dma_getMemoryTarget ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction retourne le numéro de la zone mémoire en cours d'utilisation.
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return Cette fonction retourne la valeur 0 si la zone mémoire courante est la mémoire 1, sinon la valeur 1 pour la mémoire 2.
 *         Les constantes suivantes peuvent être utilisées : \n
 *         \ref K_DMA_MEM0, \ref K_DMA_MEM1.
 *
 * @note Les fonctions \ref dma_setMemoryAddr1 et \ref dma_setMemoryAddr2 permettent de configurer l'adresse des zones mémoires 1 et 2.
 *
 */

uint32_t dma_getMemoryTarget ( void_t p_addr, uint32_t p_stream );

/**
 * @fn dma_getCount ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction retourne le nombre de données en attente d'être transférées.
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return Cette fonction retourne une valeur entre 0 et 65535.
 *
 */

uint32_t dma_getCount ( void_t p_addr, uint32_t p_stream );

/**
 * @fn uint32_t dma_getNumberOfDataTransfered ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction retourne le nombre de données déjà transmise.
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return Cette fonction retourne une valeur entre 0 et 65535.
 *
 */

uint32_t dma_getNumberOfDataTransfered ( void_t p_addr, uint32_t p_stream );

/**
 * @fn dma_getStatus ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction retourne l'état d'un flux DMA.
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return Cette fonction retourne la valeur 1 lorsque le flux DMA est actif sinon la valeur 0.
 *
 */

uint32_t dma_getStatus ( void_t p_addr, uint32_t p_stream );

/**
 * @fn uint32_t dma_getFifoStatus ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction retourne l'état du buffer d'un flux DMA.
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return Cette fonction retourne l'état du FIFO. Les constantes suivantes peuvent être utilisées : \n
 *         \ref K_DMA_FIFO_IS_BETWEEN_0_25_PERCENTS, \ref K_DMA_FIFO_IS_BETWEEN_25_50_PERCENTS,
 *         \ref K_DMA_FIFO_IS_BETWEEN_50_75_PERCENTS, \ref K_DMA_FIFO_IS_BETWEEN_75_100_PERCENTS, \ref K_DMA_FIFO_IS_EMPTY et
 *         \ref K_DMA_FIFO_IS_FULL.
 *
 */

uint32_t dma_getFifoStatus ( void_t p_addr, uint32_t p_stream );

/**
 * @fn uint32_t dma_getTransferCompleteInterruptFlag ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction retourne la valeur du drapeau d'interruption "Transfert Complete".
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t dma_getTransferCompleteInterruptFlag ( void_t p_addr, uint32_t p_stream );

/**
 * @fn uint32_t dma_getTransferHalfInterruptFlag ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction retourne la valeur du drapeau d'interruption "Half Transfert".
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t dma_getTransferHalfInterruptFlag ( void_t p_addr, uint32_t p_stream );

/**
 * @fn uint32_t dma_getTransferErrorInterruptFlag ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction retourne la valeur du drapeau d'interruption "Transfert Error".
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t dma_getTransferErrorInterruptFlag ( void_t p_addr, uint32_t p_stream );

/**
 * @fn uint32_t dma_getDirectModeErrorInterruptFlag ( void_t p_addr, uint32_t p_stream );
 * @brief Cette fonction retourne la valeur du drapeau d'interruption "Direct Mode Error".
 *
 * @param[in] p_addr   Ce paramètre contient l'adresse de base du périphérique DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA1, \ref K_DMA2
 * @param[in] p_stream Ce paramètre contient le numéro du flux DMA. Les constantes suivantes peuvent être utilisées: \n
 *                     \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 *
 * @return Cette fonction retourne la valeur logique "1" si le drapeau est positionné, sinon la valeur 0.
 *
 */

uint32_t dma_getDirectModeErrorInterruptFlag ( void_t p_addr, uint32_t p_stream );

/**
 *
 */

#endif



