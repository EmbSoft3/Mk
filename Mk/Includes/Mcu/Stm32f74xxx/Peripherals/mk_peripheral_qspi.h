/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_peripheral_qspi.h
* @brief Déclaration des fonctions dédiées au périphérique QSPI.
* @date 2 mai 2020
*
*/

#ifndef MK_PERIPHERAL_QSPI_H
#define MK_PERIPHERAL_QSPI_H

/**
 * @fn void qspi_enable ( void );
 * @brief Cette fonction active le périphérique QSPI.
 * @return Sans objet.
 *
 */

void qspi_enable ( void );

/**
 * @fn void qspi_disable ( void );
 * @brief Cette fonction désactive le périphérique QSPI.
 * @return Sans objet.
 *
 */

void qspi_disable ( void );

/**
 * @fn void qspi_enableDma ( void );
 * @brief Cette fonction est dédiée au mode 'Indirect'. Elle active le mode DMA.
 *
 * @return Sans objet.
 *
 */

void qspi_enableDma ( void );

/**
 * @fn void qspi_disableDma ( void );
 * @brief Cette fonction désactive le mode DMA.
 *
 * @return Sans objet.
 *
 */

void qspi_disableDma ( void );

/**
 * @fn void qspi_enableInterrupt ( uint32_t p_mask );
 * @brief Cette fonction active une ou plusieurs interruptions du périphérique QSPI.
 *
 * @param[in] p_mask Ce paramètre contient un masque d'interruption. Une combinaison des constantes suivantes
 *                   peut être utilisée : \n
 *                   \ref K_QSPI_TIMEOUT_INTERRUPT, \ref K_QSPI_STATUS_MATCH_INTERRUPT, \ref K_QSPI_FIFO_THRESHOLD_INTERRUPT,
 *                   \ref K_QSPI_TRANSFER_COMPLETE_INTERRUPT, \ref K_QSPI_TRANSFER_ERROR_INTERRUPT et \ref K_QSPI_ALL_INTERRUPT.
 *
 * @return Sans objet.
 *
 */

void qspi_enableInterrupt ( uint32_t p_mask );

/**
 * @fn void qspi_disableInterrupt ( uint32_t p_mask );
 * @brief Cette fonction désactive une ou plusieurs interruptions du périphérique QSPI.
 *
 * @param[in] p_mask Ce paramètre contient un masque d'interruption. Une combinaison des constantes suivantes
 *                   peut être utilisée : \n
 *                   \ref K_QSPI_TIMEOUT_INTERRUPT, \ref K_QSPI_STATUS_MATCH_INTERRUPT, \ref K_QSPI_FIFO_THRESHOLD_INTERRUPT,
 *                   \ref K_QSPI_TRANSFER_COMPLETE_INTERRUPT, \ref K_QSPI_TRANSFER_ERROR_INTERRUPT et \ref K_QSPI_ALL_INTERRUPT.
 *
 * @return Sans objet.
 *
 */

void qspi_disableInterrupt ( uint32_t p_mask );

/**
 * @fn void qspi_enableSingleFlashMode ( uint32_t p_flash );
 * @brief Cette fonction configure le périphérique QUADSPI pour n'adresser qu'une seule mémoire QSPI.
 *        Elle désactive le mode 'Dual'. Le paramètre 'p_flash' spécifie la FLASH qui doit être adressée.
 *
 * @param[in] p_flash Ce paramètre contient l'identifiant de la FLASH à adresser. Une des constantes suivantes peut être
 *                    utilisées : \n \ref K_QSPI_FLASH1 et \ref K_QSPI_FLASH2
 *
 * @return Sans objet.
 *
 */

void qspi_enableSingleFlashMode ( uint32_t p_flash );

/**
 * @fn void qspi_enableDualFlashMode ( void );
 * @brief Cette fonction configure le périphérique QUADSPI pour adresser les deux mémoires QSPI.
 * @return Sans objet.
 *
 */

void qspi_enableDualFlashMode ( void );

/**
 * @fn void qspi_setClock ( uint16_t p_prescaler );
 * @brief Cette fonction configure la vitesse de l'horloge QSPI :\n
 *        Fqspi = F_AHB / ( p_prescaler )
 *
 * @param[in] p_prescaler Ce paramètre contient la valeur du prédiviseur de l'horloge. Elle peut évoluer de 1 à 256. Les valeurs impaires
 *                        induisent un rapport cyclique différent de 50%.
 * @return Sans objet.
 *
 */

void qspi_setClock ( uint16_t p_prescaler );

/**
 * @fn void qspi_setFifoThresholdLevel ( uint8_t p_level );
 * @brief Cette fonction est dédiée au mode 'Indirect'. Elle configure l'instant de déclenchement de l'interruption FIFO_THRESHOLD.
 *        Si un canal DMA est actif, il doit être désactivé avant l'exécution de cette fonction.
 *
 * @param[in] p_level Ce paramètre contient le nombre d'octets disponibles provoquant le déclenchement de l'interruption. Ce nombre
 *                    peut évoluer de 1 à 32. Par exemple, si ce paramètre est positionné à 4, l'interruption se déclenche si au moins
 *                    4 octets sont présents dans le FIFO de réception.
 *
 * @return Sans objet.
 * @warning Après le contrôle unitaire de la fonction, il semble que le paramètre peut évoluer de 1 à 16.
 *
 */

void qspi_setFifoThresholdLevel ( uint8_t p_level );

/**
 * @fn void qspi_setSampleEdge ( uint32_t p_edge );
 * @brief Cette fonction configure le point d'échantillonnage des données fournis par la FLASH. En mode SDR (SingleDataRate), le périphérique
 *        QUADSPI pilote la transition des signaux sur chaque front descendant de l'horloge. Lorsqu'il reçoit des données en provenance de la
 *        FLASH, il suppose que le pilotage est réalisé aussi sur les fronts descendant. Par défaut, il acquière donc les signaux
 *        sur le prochain front montant. En mode SDR, cette fonction doit donc être exécutée avec le paramètre \ref K_QSPI_DEFAULT_EDGE
 *        lorsque la mémoire fournie les données sur front descendant ou avec le paramètre \ref K_QSPI_NEXT_EDGE si la mémoire fournit les données
 *        sur front montant.\n
 *        En mode DDR (DoubleDataRate), le périphérique pilote la transition des signaux sur chaque front descendant pour la phase d'instruction et
 *        sur les deux types de fronts pour les phases d'adresses, de paramètres et de données. Lorsqu'il reçoit des données en provenance de la FLASH,
 *        il suppose que le pilotage est aussi réalisé sur les deux types de fronts. La phase d'acquisition doit donc obligatoirement être réalisée
 *        sur le prochain front opposé. Il en résulte qu'en mode DDR, cette fonction ne peut être utilisée qu'avec le paramètre \ref K_QSPI_DEFAULT_EDGE.
 *
 * @param[in] p_edge Ce paramètre contient l'instant où les données transmises par la FLASH doivent être récupérées. Un des paramètres
 *                   suivant peut être utilisé : \n \ref K_QSPI_DEFAULT_EDGE et \ref K_QSPI_NEXT_EDGE.
 *
 * @return Sans objet.
 *
 */

void qspi_setSampleEdge ( uint32_t p_edge );

/**
 * @fn void qspi_abort ( void );
 * @brief Cette fonction stoppe le transfert QUADSPI en cours d'exécution. La fonction qspi_getAbortStatus() peut être utilisée pour récupérer le statut
 *        du transfert.
 * @return Sans objet.
 *
 */

void qspi_abort ( void );

/**
 * @fn uint32_t qspi_getAbortStatus ( void );
 * @brief Cette fonction indique si le transfert en cours a été arrêté ou non.
 * @return Cette fonction retourne la valeur \ref K_QSPI_ABORT_IN_PROGRESS si l'arrêt du transfert est toujours en cours ou la valeur K_QSPI_ABORT_OK
 *         dans le cas contraire.
 *
 */

uint32_t qspi_getAbortStatus ( void );

/**
 * @fn void qspi_setFlashSize ( uint8_t p_size );
 * @brief Cette fonction configure la taille en octets d'une ou plusieurs mémoires FLASH. Elle est exprimée de la manière suivante : \n
 *        FlashSize1<octets> + FlashSize2<octets> = 2^(p_size+1).
 *        Lorsque deux mémoires FLASH sont adressées, le paramètre 'p_size' est l'image de la taille des deux mémoires.
 *
 * @param[in] p_size Ce paramètre contient la taille des mémoires FLASH sur 5 bits.
 *
 * @return Sans objet.
 *
 * @warning En mode 'Indirect', l'espace que le périphérique QSPI peut adresser est de 4GB (32bits). Cependant, si le mode 'MemoryMapped' est utilisé, l'espace
 *          adressable par le périphérique est réduit à 256MB.
 *
 */

void qspi_setFlashSize ( uint8_t p_size );

/**
 * @fn void qspi_setChipSelectHighTime ( uint8_t p_cycle );
 * @brief Cette fonction configure la durée pendant lequel le signal CS est positionné au niveau logique 'HIGH' entre deux commandes QSPI.
 *
 * @param[in] p_cycle Ce paramètre contient le nombre de cycles d'horloge où le signal CS est positionné au niveau logique 'HIGH'.
 *                    Il évolue de [1 à 8] cycles.
 *
 * @return Sans objet.
 *
 */

void qspi_setChipSelectHighTime ( uint8_t p_cycle );

/**
 * @fn void qspi_setIdleClockState ( uint8_t p_state );
 * @brief Cette fonction configure l'état de repos du signal CLOCK entre deux commandes QSPI.
 *
 * @param[in] p_state Ce paramètre contient l'état de repos du signal CLOCK. Une des constantes suivantes peut être utilisée : \n
 *                    \ref K_QSPI_IDLE_CLOCK_LOW ou K_QSPI_IDLE_CLOCK_HIGH.
 *
 * @return Sans objet.
 *
 */

void qspi_setIdleClockState ( uint8_t p_state );

/**
 * @fn uint32_t qspi_getStatus ( uint32_t p_flag );
 * @brief Cette fonction retourne les statuts du périphérique QSPI.
 *
 * @param[in] p_flag Ce paramètre contient l'identifiant du statut à renvoyer. Une des constantes suivantes peut être utilisée : \n
 *                   \ref K_QSPI_BUSY_STATUS, \ref K_QSPI_TIMEOUT_STATUS, \ref K_QSPI_MATCH_STATUS,
 *                   \ref K_QSPI_FIFO_THRESHOLD_STATUS, \ref K_QSPI_TRANSFER_COMPLETE_STATUS et \ref K_QSPI_TRANSFER_ERROR_STATUS.
 *
 * @return Cette fonction retourne une des valeurs suivantes :\n
 *         \li \ref K_QSPI_BUSY_STATUS                 : la valeur K_QSPI_BUSY<1> lorsqu'un transfert est en cours, sinon la valeur K_QSPI_IDLE<0>.
 *         \li \ref K_QSPI_TIMEOUT_STATUS              : la valeur K_QSPI_TIMEOUT<1> lorsqu'un timeout s'est produit, sinon la valeur K_QSPI_IDLE<0>.
 *         \li \ref K_QSPI_MATCH_STATUS                : la valeur K_QSPI_MATCH<1> lorsqu'un 'Match' s'est produit, sinon la valeur K_QSPI_IDLE<0>.
 *         \li \ref K_QSPI_FIFO_THRESHOLD_STATUS       : la valeur K_QSPI_FIFO_THRESHOLD<1> lorsque le seuil de remplissage du FIFO est atteint, sinon la valeur K_QSPI_IDLE<0>.
 *         \li \ref K_QSPI_TRANSFER_COMPLETE_STATUS    : la valeur K_QSPI_TRANSFER_COMPLETE<1> lorsqu'un transfert est terminé (IndirectMode) ou annulé (tous les modes) sinon la valeur K_QSPI_IDLE<0>.
 *         \li \ref K_QSPI_TRANSFER_ERROR_STATUS       : la valeur K_QSPI_TRANSFER_ERROR<1> lorsqu'une adresse invalide est accédée (IndirectMode) sinon la valeur K_QSPI_IDLE<0>.
 *
 */

uint32_t qspi_getStatus ( uint32_t p_flag );

/**
 * @fn uint32_t qspi_getFifoStatus ( void );
 * @brief Cette fonction retourne le statut du FIFO du périphérique QSPI.
 *
 * @return Cette fonction retourne le nombre d'octets [de 0 à 32] contenus dans le FIFO. En mode 'MemoryMapped' et 'AutomaticPollingStatus', cette valeur est toujours nulle.
 *
 */

uint32_t qspi_getFifoStatus ( void );

/**
 * @fn void qspi_clearStatus ( uint32_t p_mask );
 * @brief Cette fonction réinitialise les statuts du périphérique QSPI.
 *
 * @param[in] p_mask Ce paramètre contient l'identifiant du statut à réinitialiser. Une des constantes suivantes peut être utilisée : \n
 *                   \ref K_QSPI_TIMEOUT_STATUS, \ref K_QSPI_MATCH_STATUS, \ref K_QSPI_TRANSFER_COMPLETE_STATUS et \ref K_QSPI_TRANSFER_ERROR_STATUS.
 *
 * @return Sans objet.
 *
 */

void qspi_clearStatus ( uint32_t p_mask );

/**
 * @fn void qspi_setTransferSize ( uint32_t p_size );
 * @brief Cette fonction configure le nombre de données à lire lors d'un transfert QSPI.
 *         Le comportement de cette fonction différe en fonction du mode de fonctionnement.\n *
 *        \li Pour le mode 'Indirect': la fonction configure le nombre de données à lire lors d'un transfert. Il peut évoluer de [$0 à $FFFFFFFF]. Une valeur de $FFFFFFFF signifie
 *                                     que la taille du transfert n'est pas définie. Une quantité d'octets égale à la taille de la flash est alors transférée. Si la taille de la flash
 *                                     et la taille du transfert sont configurés à 4GB, alors le périphérique continu les lectures indéfiniment.
 *        \li Pour le mode 'StatusPolling' : la fonction configure le nombre de données à lire lors d'un transfert. Il peut évoluer de [$0 à 3].
 *        \li Pour le mode 'MemoryMapped'  : la fonction n'a pas d'effet.
 *
 * @param[in] p_size Ce paramètre contient le nombre de données à lire lors d'un transfert QSPI. Il évolue selon la formule suivante (pour tous les modes) : \n p_size = NB_DONNEES_A_LIRE - 1;
 *
 * @warning Lorsque le mode 'DualFlash' est actif, le bit 0 est automatiquement positionné à 1 par le périphérique (taille de transfert paire uniquement).
 * @return Sans objet.
 *
 */

void qspi_setTransferSize ( uint32_t p_size );

/**
 * @fn void qspi_map ( uint32_t p_dataRate, uint32_t p_dummyCycleNumber, uint32_t p_instruction, uint32_t p_addressSize, uint32_t p_alternateSize, uint32_t p_dataSize );
 * @brief Cette fonction active le mode 'MemoryMappedMode'. Dans ce mode la FLASH est considérée comme une extension de la mémoire. Un maximum de 256MB de mémoire peut être accédés. Si un accés est réalisé en dehors
 *        de l'espace défini par la fonction \ref qspi_setFlashSize, une erreur de type 'HardFault' est générée (une erreur de type DMATransferError est généré dans le cas où l'accès est réalisé à partir d'une DMA).
 *        Les accès par octet, par demi-mot ou par mot sont autorisés. Lorsqu'une lecture est réalisée, le périphérique positionne en cache (dans le FIFO) les données présentes aux adresses successives. Un maximum
 *        de 32 octets peut être positionné dans le FIFO.
 *
 * @param[in] p_dataRate          Ce paramètre contient la vitesse de communication de l'interface QSPI, une combinaison des constantes suivantes peut être utilisée : \n
 *                                \li \ref K_QSPI_SDR_MODE : le mode 'SingleDataRate' est actif
 *                                \li \ref K_QSPI_DDR_MODE : le mode 'DoubleDataRate' est actif
 *                                En mode DDR, l'instant de déclenchement de la phase de données peut être configuré à l'aide d'une des constantes suivantes :
 *                                \li \ref K_QSPI_ANALOG_DELAY  : aucun délai supplémentaire n'est ajouté à la phase de latence (dummy cycle), le périphérique écrit les données sur le bus immédiatement après cette phase.
 *                                \li \ref K_QSPI_QUARTER_DELAY : un délai supplémentaire d'un quart de la fréquence QSPI est ajouté à la phase de latence (dummy cycle).
 *
 * @param[in] p_dummyCycleNumber  Ce paramètre contient le nombre de cycles de latence d'un transfert. Il évolue de [0 à 31].
 *
 * @param[in] p_instruction       Ce paramètre contient le code et le mode de transmission de l'instruction. L'instruction est codée sur 8 bits. Les constantes suivantes peuvent être utilisées pour configurer le nombre de lignes
 *                                de données :\n
 *                                \ref K_QSPI_INSTRUCTION_NO_LINE_MODE, \ref K_QSPI_INSTRUCTION_SINGLE_MODE, \ref K_QSPI_INSTRUCTION_DUAL_MODE et \ref K_QSPI_INSTRUCTION_QUAD_MODE.
 *                                La constante \ref K_QSPI_SEND_INSTRUCTION_ONLY_ONCE peut être utilisé pour indiquer au périphérique d'activer le mode 'ONE_INSTRUCTION_ONLY'.
 *
 * @param[in] p_addressSize       Ce paramètre contient la taille et le mode de transmission des adresses présentes dans une commande QSPI. Une combinaison des constantes suivantes peut être utilisée :
 *                                \li Taille : \ref K_QSPI_ADDRESS_SIZE_8BITS, \ref K_QSPI_ADDRESS_SIZE_16BITS, \ref K_QSPI_ADDRESS_SIZE_24BITS et \ref K_QSPI_ADDRESS_SIZE_32BITS.
 *                                \li Mode : \ref K_QSPI_ADDRESS_NO_LINE_MODE, \ref K_QSPI_ADDRESS_SINGLE_MODE, \ref K_QSPI_ADDRESS_DUAL_MODE et \ref K_QSPI_ADDRESS_QUAD_MODE.
 *
 * @param[in] p_alternateSize     Ce paramètre contient la taille et le mode de transmission des paramètres optionnels présent dans une commande QSPI. Une combinaison des constantes suivantes peut être utilisée :
 *                                \li Taille : \ref K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, \ref K_QSPI_ALTERNATE_BYTES_SIZE_16BITS, \ref K_QSPI_ALTERNATE_BYTES_SIZE_24BITS et \ref K_QSPI_ALTERNATE_BYTES_SIZE_32BITS.
 *                                \li Mode : \ref K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE, \ref K_QSPI_ALTERNATE_BYTES_SINGLE_MODE, \ref K_QSPI_ALTERNATE_BYTES_DUAL_MODE et \ref K_QSPI_ALTERNATE_BYTES_QUAD_MODE.
 *
 * @param[in] p_dataSize          Ce paramètre contient le mode de transmission des données présentes dans une commande QSPI. Une des constantes suivantes peut être utilisée : \n
 *                                \ref K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE, \ref K_QSPI_ALTERNATE_BYTES_SINGLE_MODE, \ref K_QSPI_ALTERNATE_BYTES_DUAL_MODE et \ref K_QSPI_ALTERNATE_BYTES_QUAD_MODE.
 *
 * @note Lorsque le mode SDR est actif, le périphérique QSPI pilote les signaux sur fronts descendant durant les phases d'instructions, d'adresse et de paramètre. Il pilote les signaux sur front montant
 *       ou descendant durant la phase de données.\n
 *       Lorsque le mode DDR est actif, le périphérique QSPI pilote les signaux sur front descendant durant la phase d'instruction, il pilote les signaux sur les deux types de fronts (montant et descendant)
 *       durant les phases d'adresse, de paramètre et de données. Il en résulte que la fréquence de communication est doublée.
 *
 * @return Sans objet.
 *
 */

void qspi_map ( uint32_t p_dataRate, uint32_t p_dummyCycleNumber, uint32_t p_instruction, uint32_t p_addressSize, uint32_t p_alternateSize, uint32_t p_dataSize );

/**
 * @fn void qspi_enableTimeoutCounter ( uint16_t p_cycle );
 * @brief Cette fonction est dédiée au mode 'MemoryMapped'. Elle positionne la broche 'CS' à l'état de repos si aucun transfert n'est
 *        réalisé dans le timeout imparti. Ce timeout est défini par le paramètre 'p_cycle' de la manière suivante :
 *        Timeout [sec] = p_cycle * (1/F_QSPI[Hz]) avec la F_QSPI la fréquence de l'horloge QSPI.\n
 *        Le timeout se déclenche lorsque le FIFO de réception est plein.\n
 *        Le positionnement de la broche CS à l'état de repos permet de réduire la consommation du périphérique QSPI.
 *
 * @param[in] p_cycle Ce paramètre contient le nombre de cycle intervenant dans le calcul du timeout. La valeur est codée sur 16 bits.
 *
 * @return Sans objet.
 *
 */

void qspi_enableTimeoutCounter ( uint16_t p_cycle );

/**
 * @fn void qspi_disableTimeoutCounter ( void );
 * @brief Cette fonction désactive le compteur gérant les timeout.

 * @return Sans objet.
 *
 */

void qspi_disableTimeoutCounter ( void );

/**
 * @fn void qspi_poll ( uint32_t p_dataRate, uint32_t p_dummyCycleNumber, uint32_t p_instruction, uint32_t p_addressSize, uint32_t p_alternateSize, uint32_t p_dataSize );
 * @brief Cette fonction active le mode 'StatusPollingMode'. Dans ce mode, le périphérique QSPI déclenche periodiquement des requêtes de statut afin de récupérer un maximum de 4 octets (fonction \ref qspi_setTransferSize).
 *        Le contenu de ces octets est comparé à un masque selon une méthode OR ou AND. Les caractéristiques de ce mode sont configurés à partir de la fonction \ref qspi_setStatusPollingMode.
 *        Une interruption peut être générée lorsqu'un match survient.
 *
 * @param[in] p_dataRate          Ce paramètre contient la vitesse de communication de l'interface QSPI, une combinaison des constantes suivantes peut être utilisée : \n
 *                                \li \ref K_QSPI_SDR_MODE : le mode 'SingleDataRate' est actif
 *                                \li \ref K_QSPI_DDR_MODE : le mode 'DoubleDataRate' est actif
 *                                En mode DDR, l'instant de déclenchement de la phase de données peut être configuré à l'aide d'une des constantes suivantes :
 *                                \li \ref K_QSPI_ANALOG_DELAY  : aucun délai supplémentaire n'est ajouté à la phase de latence (dummy cycle), le périphérique écrit les données sur le bus immédiatement après cette phase.
 *                                \li \ref K_QSPI_QUARTER_DELAY : un délai supplémentaire d'un quart de la fréquence QSPI est ajouté à la phase de latence (dummy cycle).
 *
 * @param[in] p_dummyCycleNumber  Ce paramètre contient le nombre de cycles de latence d'un transfert. Il évolue de [0 à 31].
 *
 * @param[in] p_instruction       Ce paramètre contient le code et le mode de transmission de l'instruction. L'instruction est codée sur 8 bits. Les constantes suivantes peuvent être utilisées pour configurer le nombre de lignes
 *                                de données :\n
 *                                \ref K_QSPI_INSTRUCTION_NO_LINE_MODE, \ref K_QSPI_INSTRUCTION_SINGLE_MODE, \ref K_QSPI_INSTRUCTION_DUAL_MODE et \ref K_QSPI_INSTRUCTION_QUAD_MODE.
 *                                La constante \ref K_QSPI_SEND_INSTRUCTION_ONLY_ONCE peut être utilisé pour indiquer au périphérique d'activer le mode 'ONE_INSTRUCTION_ONLY'.
 *
 * @param[in] p_addressSize       Ce paramètre contient la taille et le mode de transmission des adresses présentes dans une commande QSPI. Une combinaison des constantes suivantes peut être utilisée :
 *                                \li Taille : \ref K_QSPI_ADDRESS_SIZE_8BITS, \ref K_QSPI_ADDRESS_SIZE_16BITS, \ref K_QSPI_ADDRESS_SIZE_24BITS et \ref K_QSPI_ADDRESS_SIZE_32BITS.
 *                                \li Mode : \ref K_QSPI_ADDRESS_NO_LINE_MODE, \ref K_QSPI_ADDRESS_SINGLE_MODE, \ref K_QSPI_ADDRESS_DUAL_MODE et \ref K_QSPI_ADDRESS_QUAD_MODE.
 *
 * @param[in] p_alternateSize     Ce paramètre contient la taille et le mode de transmission des paramètres optionnels présent dans une commande QSPI. Une combinaison des constantes suivantes peut être utilisée :
 *                                \li Taille : \ref K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, \ref K_QSPI_ALTERNATE_BYTES_SIZE_16BITS, \ref K_QSPI_ALTERNATE_BYTES_SIZE_24BITS et \ref K_QSPI_ALTERNATE_BYTES_SIZE_32BITS.
 *                                \li Mode : \ref K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE, \ref K_QSPI_ALTERNATE_BYTES_SINGLE_MODE, \ref K_QSPI_ALTERNATE_BYTES_DUAL_MODE et \ref K_QSPI_ALTERNATE_BYTES_QUAD_MODE.
 *
 * @param[in] p_dataSize          Ce paramètre contient le mode de transmission des données présentes dans une commande QSPI. Une des constantes suivantes peut être utilisée : \n
 *                                \ref K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE, \ref K_QSPI_ALTERNATE_BYTES_SINGLE_MODE, \ref K_QSPI_ALTERNATE_BYTES_DUAL_MODE et \ref K_QSPI_ALTERNATE_BYTES_QUAD_MODE.
 *
 * @note Lorsque le mode SDR est actif, le périphérique QSPI pilote les signaux sur fronts descendant durant les phases d'instructions, d'adresse et de paramètre. Il pilote les signaux sur front montant
 *       ou descendant durant la phase de données.\n
 *       Lorsque le mode DDR est actif, le périphérique QSPI pilote les signaux sur front descendant durant la phase d'instruction, il pilote les signaux sur les deux types de fronts (montant et descendant)
 *       durant les phases d'adresse, de paramètre et de données. Il en résulte que la fréquence de communication est doublée.
 *
 * @return Sans objet.
 *
 */

void qspi_poll ( uint32_t p_dataRate, uint32_t p_dummyCycleNumber, uint32_t p_instruction, uint32_t p_addressSize, uint32_t p_alternateSize, uint32_t p_dataSize );

/**
 * @fn void qspi_setStatusPollingMode ( uint32_t p_matchType, uint32_t p_matchStop );
 * @brief Cette fonction est dédiée au mode 'AutomaticPollingMode'. Elle configure la méthode de comparaison à utiliser pour déterminer l'apparition d'un
 *        événement 'Match' ainsi que le comportement adopter par le périphérique lorsque le 'Match' est survenu.
 *
 * @param[in] p_matchType       Ce paramètre configure la méthode a utilisée pour déterminer l'apparition d'un événement 'Match'. Une des constantes suivantes
 *                              peut être utilisée : \n \ref K_QSPI_MATCH_OR et \ref K_QSPI_MATCH_AND.
 * @param[in] p_matchStop       Ce paramètre configure le comportement du module QSPI lorsqu'un événement 'Match' est survenu. Une des constantes suivantes
 *                              peut être utlisée : \n \ref K_QSPI_AUTOMATIC_POLLING_MODE_STOP_AFTER_MATCH et \ref K_QSPI_AUTOMATIC_POLLING_MODE_CONTINUE_AFTER_MATCH.
 * @param[in] p_pollingInterval Ce paramètre contient le nombre de cyles d'horloge QSPI entre deux commandes de lecture. Il est codé sur 32 bits.
 * @param[in] p_matchRegister   Ce paramètre contient la valeur du registre de comparaison.
 * @param[in] p_maskRegister    Ce paramètre contient le valeur du masque appliqué au registre de statut.
 *
 * @return Sans objet.
 *
 */

void qspi_setStatusPollingMode ( uint32_t p_matchType, uint32_t p_matchStop, uint32_t p_matchRegister, uint32_t p_maskRegister, uint16_t p_pollingInterval );

/**
 * @fn void qspi_read ( uint32_t p_dataRate, uint32_t p_dummyCycleNumber, uint32_t p_instruction, uint32_t p_addressSize, uint32_t p_alternateSize, uint32_t p_dataSize );
 * @brief Cette fonction active le mode 'IndirectReadMode'. Dans ce mode, les lectures sont réalisées directement par le CPU via les registres de données.
 *
 * @param[in] p_dataRate          Ce paramètre contient la vitesse de communication de l'interface QSPI, une combinaison des constantes suivantes peut être utilisée : \n
 *                                \li \ref K_QSPI_SDR_MODE : le mode 'SingleDataRate' est actif
 *                                \li \ref K_QSPI_DDR_MODE : le mode 'DoubleDataRate' est actif
 *                                En mode DDR, l'instant de déclenchement de la phase de données peut être configuré à l'aide d'une des constantes suivantes :
 *                                \li \ref K_QSPI_ANALOG_DELAY  : aucun délai supplémentaire n'est ajouté à la phase de latence (dummy cycle), le périphérique écrit les données sur le bus immédiatement après cette phase.
 *                                \li \ref K_QSPI_QUARTER_DELAY : un délai supplémentaire d'un quart de la fréquence QSPI est ajouté à la phase de latence (dummy cycle).
 *
 * @param[in] p_dummyCycleNumber  Ce paramètre contient le nombre de cycles de latence d'un transfert. Il évolue de [0 à 31].
 *
 * @param[in] p_instruction       Ce paramètre contient le code et le mode de transmission de l'instruction. L'instruction est codée sur 8 bits. Les constantes suivantes peuvent être utilisées pour configurer le nombre de lignes
 *                                de données :\n
 *                                \ref K_QSPI_INSTRUCTION_NO_LINE_MODE, \ref K_QSPI_INSTRUCTION_SINGLE_MODE, \ref K_QSPI_INSTRUCTION_DUAL_MODE et \ref K_QSPI_INSTRUCTION_QUAD_MODE.
 *                                La constante \ref K_QSPI_SEND_INSTRUCTION_ONLY_ONCE peut être utilisé pour indiquer au périphérique d'activer le mode 'ONE_INSTRUCTION_ONLY'.
 *
 * @param[in] p_addressSize       Ce paramètre contient la taille et le mode de transmission des adresses présentes dans une commande QSPI. Une combinaison des constantes suivantes peut être utilisée :
 *                                \li Taille : \ref K_QSPI_ADDRESS_SIZE_8BITS, \ref K_QSPI_ADDRESS_SIZE_16BITS, \ref K_QSPI_ADDRESS_SIZE_24BITS et \ref K_QSPI_ADDRESS_SIZE_32BITS.
 *                                \li Mode : \ref K_QSPI_ADDRESS_NO_LINE_MODE, \ref K_QSPI_ADDRESS_SINGLE_MODE, \ref K_QSPI_ADDRESS_DUAL_MODE et \ref K_QSPI_ADDRESS_QUAD_MODE.
 *
 * @param[in] p_alternateSize     Ce paramètre contient la taille et le mode de transmission des paramètres optionnels présent dans une commande QSPI. Une combinaison des constantes suivantes peut être utilisée :
 *                                \li Taille : \ref K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, \ref K_QSPI_ALTERNATE_BYTES_SIZE_16BITS, \ref K_QSPI_ALTERNATE_BYTES_SIZE_24BITS et \ref K_QSPI_ALTERNATE_BYTES_SIZE_32BITS.
 *                                \li Mode : \ref K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE, \ref K_QSPI_ALTERNATE_BYTES_SINGLE_MODE, \ref K_QSPI_ALTERNATE_BYTES_DUAL_MODE et \ref K_QSPI_ALTERNATE_BYTES_QUAD_MODE.
 *
 * @param[in] p_dataSize          Ce paramètre contient le mode de transmission des données présentes dans une commande QSPI. Une des constantes suivantes peut être utilisée : \n
 *                                \ref K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE, \ref K_QSPI_ALTERNATE_BYTES_SINGLE_MODE, \ref K_QSPI_ALTERNATE_BYTES_DUAL_MODE et \ref K_QSPI_ALTERNATE_BYTES_QUAD_MODE.
 *
 * @note Lorsque le mode SDR est actif, le périphérique QSPI pilote les signaux sur fronts descendant durant les phases d'instructions, d'adresse et de paramètre. Il pilote les signaux sur front montant
 *       ou descendant durant la phase de données. \n
 *       Lorsque le mode DDR est actif, le périphérique QSPI pilote les signaux sur front descendant durant la phase d'instruction, il pilote les signaux sur les deux types de fronts (montant et descendant)
 *       durant les phases d'adresse, de paramètre et de données. Il en résulte que la fréquence de communication est doublée.
 *
 * @return Sans objet.
 *
 */

void qspi_read ( uint32_t p_dataRate, uint32_t p_dummyCycleNumber, uint32_t p_instruction, uint32_t p_addressSize, uint32_t p_alternateSize, uint32_t p_dataSize );

/**
 * @fn void qspi_write ( uint32_t p_dataRate, uint32_t p_dummyCycleNumber, uint32_t p_instruction, uint32_t p_addressSize, uint32_t p_alternateSize, uint32_t p_dataSize );
 * @brief Cette fonction active le mode 'IndirectWriteMode'. Dans ce mode, les écritures sont réalisées directement par le CPU via les registres de données.
 *
 * @param[in] p_dataRate          Ce paramètre contient la vitesse de communication de l'interface QSPI, une combinaison des constantes suivantes peut être utilisée : \n
 *                                \li \ref K_QSPI_SDR_MODE : le mode 'SingleDataRate' est actif
 *                                \li \ref K_QSPI_DDR_MODE : le mode 'DoubleDataRate' est actif
 *                                En mode DDR, l'instant de déclenchement de la phase de données peut être configuré à l'aide d'une des constantes suivantes :
 *                                \li \ref K_QSPI_ANALOG_DELAY  : aucun délai supplémentaire n'est ajouté à la phase de latence (dummy cycle), le périphérique écrit les données sur le bus immédiatement après cette phase.
 *                                \li \ref K_QSPI_QUARTER_DELAY : un délai supplémentaire d'un quart de la fréquence QSPI est ajouté à la phase de latence (dummy cycle).
 *
 * @param[in] p_dummyCycleNumber  Ce paramètre contient le nombre de cycles de latence d'un transfert. Il évolue de [0 à 31].
 *
 * @param[in] p_instruction       Ce paramètre contient le code et le mode de transmission de l'instruction. L'instruction est codée sur 8 bits. Les constantes suivantes peuvent être utilisées pour configurer le nombre de lignes
 *                                de données :\n
 *                                \ref K_QSPI_INSTRUCTION_NO_LINE_MODE, \ref K_QSPI_INSTRUCTION_SINGLE_MODE, \ref K_QSPI_INSTRUCTION_DUAL_MODE et \ref K_QSPI_INSTRUCTION_QUAD_MODE.
 *                                La constante \ref K_QSPI_SEND_INSTRUCTION_ONLY_ONCE peut être utilisé pour indiquer au périphérique d'activer le mode 'ONE_INSTRUCTION_ONLY'.
 *
 * @param[in] p_addressSize       Ce paramètre contient la taille et le mode de transmission des adresses présentes dans une commande QSPI. Une combinaison des constantes suivantes peut être utilisée :
 *                                \li Taille : \ref K_QSPI_ADDRESS_SIZE_8BITS, \ref K_QSPI_ADDRESS_SIZE_16BITS, \ref K_QSPI_ADDRESS_SIZE_24BITS et \ref K_QSPI_ADDRESS_SIZE_32BITS.
 *                                \li Mode : \ref K_QSPI_ADDRESS_NO_LINE_MODE, \ref K_QSPI_ADDRESS_SINGLE_MODE, \ref K_QSPI_ADDRESS_DUAL_MODE et \ref K_QSPI_ADDRESS_QUAD_MODE.
 *
 * @param[in] p_alternateSize     Ce paramètre contient la taille et le mode de transmission des paramètres optionnels présent dans une commande QSPI. Une combinaison des constantes suivantes peut être utilisée :
 *                                \li Taille : \ref K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, \ref K_QSPI_ALTERNATE_BYTES_SIZE_16BITS, \ref K_QSPI_ALTERNATE_BYTES_SIZE_24BITS et \ref K_QSPI_ALTERNATE_BYTES_SIZE_32BITS.
 *                                \li Mode : \ref K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE, \ref K_QSPI_ALTERNATE_BYTES_SINGLE_MODE, \ref K_QSPI_ALTERNATE_BYTES_DUAL_MODE et \ref K_QSPI_ALTERNATE_BYTES_QUAD_MODE.
 *
 * @param[in] p_dataSize          Ce paramètre contient le mode de transmission des données présentes dans une commande QSPI. Une des constantes suivantes peut être utilisée : \n
 *                                \ref K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE, \ref K_QSPI_ALTERNATE_BYTES_SINGLE_MODE, \ref K_QSPI_ALTERNATE_BYTES_DUAL_MODE et \ref K_QSPI_ALTERNATE_BYTES_QUAD_MODE.
 *
 * @note Lorsque le mode SDR est actif, le périphérique QSPI pilote les signaux sur fronts descendant durant les phases d'instructions, d'adresse et de paramètre. Il pilote les signaux sur front montant
 *       ou descendant durant la phase de données. \n
 *       Lorsque le mode DDR est actif, le périphérique QSPI pilote les signaux sur front descendant durant la phase d'instruction, il pilote les signaux sur les deux types de fronts (montant et descendant)
 *       durant les phases d'adresse, de paramètre et de données. Il en résulte que la fréquence de communication est doublée.
 *
 * @return Sans objet.
 *
 */

void qspi_write ( uint32_t p_dataRate, uint32_t p_dummyCycleNumber, uint32_t p_instruction, uint32_t p_addressSize, uint32_t p_alternateSize, uint32_t p_dataSize );

/**
 * @fn void qspi_writeAddress ( uint32_t p_address );
 * @brief Cette fonction configure l'adresse présente dans une commande.
 * @param[in] p_address Ce paramètre contient l'adresse contenue dans la commande. Il est codée sur 32 bits.
 *
 * @return Sans objet.
 *
 */

void qspi_writeAddress ( uint32_t p_address );

/**
 * @fn void qspi_writeAlternateBytes ( uint32_t p_alternateByte );
 * @brief Cette fonction configure les paramètres optionnels présents dans une commande.
 * @param[in] p_alternateByte Ce paramètre contient les paramètres optionnels contenus dans la commande. Il est codée sur 32 bits.
 *
 * @return Sans objet.
 *
 */

void qspi_writeAlternateBytes ( uint32_t p_alternateByte );

/**
 * @fn void qspi_writeWord ( uint32_t p_data );
 * @brief Cette fonction écrit un mot 32 bits dans le buffer de transmission. La taille disponible dans le FIFO est décrémentée de 4 octets.
 * @param[in] p_data Ce paramètre contient la valeur du mot 32 bits à écrire.
 *
 * @return Sans objet.
 *
 */

void qspi_writeWord ( uint32_t p_data );

/**
 * @fn qspi_writeHalfWord ( uint16_t p_data );
 * @brief Cette fonction écrit un mot 16 bits dans le buffer de transmission. La taille disponible dans le FIFO est décrémentée de 2 octets.
 * @param[in] p_data Ce paramètre contient la valeur du mot 16 bits à écrire.
 *
 * @return Sans objet.
 *
 */

void qspi_writeHalfWord ( uint16_t p_data );

/**
 * @fn void qspi_writeByte ( uint8_t p_data );
 * @brief Cette fonction écrit un octet dans le buffer de transmission. La taille disponible dans le FIFO est décrémentée de 1 octets.
 * @param[in] p_data Ce paramètre contient la valeur de l'octet à écrire.
 *
 * @return Sans objet.
 *
 */

void qspi_writeByte ( uint8_t p_data );

/**
 * @fn uint32_t qspi_readWord ( void );
 * @brief Cette fonction lit un mot 32 bits dans le buffer de réception. La taille disponible dans le FIFO est incrémentée de 4 octets.
 * @return La valeur du mot 32 bits lu.
 *
 */

uint32_t qspi_readWord ( void );

/**
 * @fn uint16_t qspi_readHalfWord ( void );
 * @brief Cette fonction lit un mot 16 bits dans le buffer de réception. La taille disponible dans le FIFO est incrémentée de 2 octets.
 * @return La valeur du mot 16 bits lu.
 *
 */

uint16_t qspi_readHalfWord ( void );

/**
 * @fn uint8_t qspi_readByte ( void );
 * @brief Cette fonction lit un octet dans le buffer de réception. La taille disponible dans le FIFO est incrémentée de 1 octets.
 * @return La valeur de l'octet lu.
 *
 */

uint8_t qspi_readByte ( void );

/**
 *
 */

#endif

