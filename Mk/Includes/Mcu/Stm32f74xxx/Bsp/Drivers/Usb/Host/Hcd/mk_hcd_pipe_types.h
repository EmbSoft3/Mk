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
* @file mk_hcd_pipe_types.h
* @brief Déclaration des types dédiés aux pipes USB.
* @date 8 oct. 2019
*
*/

#ifndef MK_HCD_PIPE_TYPES_H
#define MK_HCD_PIPE_TYPES_H

/**
 * @struct T_mkHCDPipeStatus
 * @brief Déclaration de l'énumération T_mkHCDPipeStatus.
 *
 */

typedef enum T_mkHCDPipeStatus
{
   K_MK_HCD_NO_FLAG = 0,                                                         /*!< Définition d'un code indiquant l'absence de statut. */
   K_MK_HCD_FLAG_XFER = 1,                                                       /*!< Définition d'un code indiquant la réussite d'un transfert USB. */
   K_MK_HCD_FLAG_CHH = 2,                                                        /*!< Définition d'un code indiquant l'arrêt d'un canal de communication suite à la réussite ou l'échec d'un transfert USB. */
   K_MK_HCD_ERROR_AHB = 4,                                                       /*!< Définition d'un code indiquant la détection d'une erreur AHB lors d'un transfert USB (DMA). */
   K_MK_HCD_ERROR_STALL = 8,                                                     /*!< Définition d'un code indiquant la détection d'une erreur STALL lors d'un transfert USB. */
   K_MK_HCD_FLAG_NAK = 16,                                                       /*!< Définition d'un code indiquant la détection d'un statut NAK lors d'un transfert USB. */
   K_MK_HCD_FLAG_ACK = 32,                                                       /*!< Définition d'un code indiquant la détection d'un statut ACK lors d'un transfert USB. */
   K_MK_HCD_FLAG_NYET = 64,                                                      /*!< Définition d'un code indiquant la détection d'un statut NYET lors d'un transfert USB. */
   K_MK_HCD_ERROR_TRANSACTION = 128,                                             /*!< Définition d'un code indiquant la détection d'une erreur CRC, TIMEOUT, STUFF ou EOP lors d'un transfert USB. */
   K_MK_HCD_ERROR_BABBLE = 256,                                                  /*!< Définition d'un code indiquant la détection d'une erreur BABBLE lors d'un transfert USB. */
   K_MK_HCD_ERROR_FRAME_OVERRUN = 512,                                           /*!< Définition d'un code indiquant la détection d'une erreur OVERRUN lors d'un transfert USB. */
   K_MK_HCD_ERROR_TOOGLE = 1024,                                                 /*!< Définition d'un code indiquant la détection d'une erreur TOOGLE lors d'un transfert USB. */

   K_MK_HCD_CHANNEL_ABORTED_MASK = 1932,                                         /*!< Définition d'un code indiquant si le transfert doit être arrêté ou non (combinaison de bits). */
   K_MK_HCD_CHANNEL_MASK = 2047,                                                 /*!< Définition d'un code addressant les bits du périphérique USB matériel. */

   K_MK_HCD_TRANSFER_ABORTED = 8192,                                             /*!< Définition d'un code indiquant l'arrêt d'un transfert suite à une erreur de communication. */
   K_MK_HCD_TRANSFER_DONE = 16384,                                               /*!< Définition d'un code indiquant la complétude d'un transfert. */
   K_MK_HCD_TRANSFER_DISABLED = 32768,                                           /*!< Définition d'un code indiquant la désactivation d'un canal de communication. */
   K_MK_HCD_TRANSFER_RESTART_SPLIT = 65536                                       /*!< Définition d'un code indiquant que la transaction de type SPLIT doit être réémise. */
} T_mkHCDPipeStatus;

/**
 * @struct T_mkHCDPipeEndpointType
 * @brief Déclaration de l'énumération T_mkHCDPipeEndpointType.
 *
 */

typedef enum T_mkHCDPipeEndpointType
{
   K_MK_HCD_ENDPOINT_CONTROL = 0x0,                                              /*!< Définition d'un code indiquant la configuration d'une terminaison USB en mode 'Control'. */
   K_MK_HCD_ENDPOINT_ISOCHRONOUS = 0x1,                                          /*!< Définition d'un code indiquant la configuration d'une terminaison USB en mode 'Isochronous'. */
   K_MK_HCD_ENDPOINT_BULK = 0x2,                                                 /*!< Définition d'un code indiquant la configuration d'une terminaison USB en mode 'Bulk'. */
   K_MK_HCD_ENDPOINT_INTERRUPT = 0x3                                             /*!< Définition d'un code indiquant la configuration d'une terminaison USB en mode 'Interrupt'. */
} T_mkHCDPipeEndpointType;

/**
 * @struct T_mkHCDPipeEndpointNumber
 * @brief Déclaration de l'énumération T_mkHCDPipeEndpointNumber.
 *
 */

typedef enum T_mkHCDPipeEndpointNumber
{
   K_MK_HCD_ENDPOINT0 = 0x0,                                                     /*!< Définition de l'identifiant de la terminaison 0. */
   K_MK_HCD_ENDPOINT1 = 0x1,                                                     /*!< Définition de l'identifiant de la terminaison 1. */
   K_MK_HCD_ENDPOINT2 = 0x2,                                                     /*!< Définition de l'identifiant de la terminaison 2. */
   K_MK_HCD_ENDPOINT3 = 0x3,                                                     /*!< Définition de l'identifiant de la terminaison 3. */
   K_MK_HCD_ENDPOINT4 = 0x4,                                                     /*!< Définition de l'identifiant de la terminaison 4. */
   K_MK_HCD_ENDPOINT5 = 0x5,                                                     /*!< Définition de l'identifiant de la terminaison 5. */
   K_MK_HCD_ENDPOINT6 = 0x6,                                                     /*!< Définition de l'identifiant de la terminaison 6. */
   K_MK_HCD_ENDPOINT7 = 0x7,                                                     /*!< Définition de l'identifiant de la terminaison 7. */
   K_MK_HCD_ENDPOINT8 = 0x8                                                      /*!< Définition de l'identifiant de la terminaison 8. */
} T_mkHCDPipeEndpointNumber;

/**
 * @struct T_mkHCDPipeEndpointPid
 * @brief Déclaration de l'énumération T_mkHCDPipeEndpointPid.
 *
 */

typedef enum T_mkHCDPipeEndpointPid
{
   K_MK_HCD_PID_DATA0 = 0x00000000,                                              /*!< Définition d'un code indiquant la sélection du token DATA0 lors du transfert du prochain paquet USB. */
   K_MK_HCD_PID_DATA1 = 0x20000000,                                              /*!< Définition d'un code indiquant la sélection du token DATA1 lors du transfert du prochain paquet USB. */
   K_MK_HCD_PID_DATA2 = 0x10000000,                                              /*!< Définition d'un code indiquant la sélection du token DATA2 lors du transfert du prochain paquet USB. */
   K_MK_HCD_PID_SETUP = 0x30000000,                                              /*!< Définition d'un code indiquant la sélection du token SETUP lors du transfert du prochain paquet USB. */
   K_MK_HCD_PID_MDATA = 0x30000000,                                              /*!< Définition d'un code indiquant la sélection du token MDATA lors du transfert du prochain paquet USB (identifiant identique à SETUP). */
   K_MK_HCD_PID_TOOGLE = 0x40000000                                              /*!< Définition d'un code permettant de permuter les token DATA0 et DATA1 lors du transfert du prochain paquet USB. */
} T_mkHCDPipeEndpointPid;

/**
 * @struct T_mkHCDPipeDirection
 * @brief Déclaration de l'énumération T_mkHCDPipeDirection.
 *
 */

typedef enum T_mkHCDPipeDirection
{
   K_MK_HCD_ENDPOINT_OUT = 0x00000000,                                           /*!< Définition de la direction de la communication lors du transfert du prochain paquet USB (host to device). */
   K_MK_HCD_ENDPOINT_IN = 0x01000000                                             /*!< Définition de la direction de la communication lors du transfert du prochain paquet USB (device to host). */
} T_mkHCDPipeDirection;

/**
 * @struct T_mkHCDChannelStatus
 * @brief Déclaration de l'énumération T_mkHCDChannelStatus.
 *
 */

typedef enum T_mkHCDChannelStatus
{
   K_MK_HCD_CHANNEL_NOT_USED = 0,                                                /*!< Code indiquant qu'un canal de communication est libre. */
   K_MK_HCD_CHANNEL_USED = 1                                                     /*!< Code indiquant qu'un canal de communication est utilisé. */
} T_mkHCDChannelStatus;

/**
 * @struct T_mkHCDPipe
 * @brief Déclaration de la structure T_mkHCDPipe.
 *
 */

typedef struct T_mkHCDPipe T_mkHCDPipe;
struct T_mkHCDPipe
{
   uint8_t  channel;                                                             /*!< Ce membre contient le numéro du canal USB de la terminaison. */
   uint8_t  endpointType;                                                        /*!< Ce membre contient le type de la terminaison (\ref T_mkHCDPipeEndpointType). */
   uint8_t  endpointDirection;                                                   /*!< Ce membre contient la direction de la terminaison (\ref T_mkHCDPipeDirection). */
   uint8_t  endpointNumber;                                                      /*!< Ce membre contient le numéro de la terminaison (\ref T_mkHCDPipeEndpointNumber). */
   uint16_t endpointMaxPacketSize;                                               /*!< Ce membre contient la taille maximale du paquet (MPS) supporté par la terminaison. */
   uint8_t  token;                                                               /*!< Ce membre contient la valeur du premier token à utiliser lors d'un nouveau transfert (\ref T_mkHCDPipeEndpointPid). */
   uint8_t  padding8;                                                            /*!< Ce champ est réservé pour un usage ultérieur - padding. */
   uint32_t numberOfPackets;                                                     /*!< Ce membre contient le nombre de paquets à transmettre dans la transaction. */
   uint32_t timeout;                                                             /*!< Ce membre contient la valeur du timeout de transmission (en ms). */
   T_mkHCDPipeStatus status;                                                     /*!< Ce membre contient le statut du dernier transfert réalisé par la terminaison. */
};

/**
 *
 */

#endif


