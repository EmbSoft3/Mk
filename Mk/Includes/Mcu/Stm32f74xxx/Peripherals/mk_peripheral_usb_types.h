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
* @file mk_peripheral_usb_types.h
* @brief Déclaration des types dédiés au périphérique USB.
* @date 25 mai 2019
*
*/

#ifndef MK_PERIPHERAL_USB_TYPES_H
#define MK_PERIPHERAL_USB_TYPES_H

/**
 * @struct T_USBOTGHostRxStatusField
 * @brief Déclaration du type T_USBOTGHostRxStatusField.
 */

typedef struct T_USBOTGHostRxStatusField T_USBOTGHostRxStatusField;
struct T_USBOTGHostRxStatusField
{
   unsigned_t channelNumber:4;                             /*!< Ce champ de bits contient le numéro du canal de réception du paquet. */
   unsigned_t count:11;                                    /*!< Ce champ de bits contient le nombre d'octets du paquet. */
   unsigned_t pid:2;                                       /*!< Ce champ de bits contient le PID du paquet. Il peut prendre les valeurs \ref K_USB_PID_DATA0, \ref K_USB_PID_DATA1, \ref K_USB_PID_DATA2 et \ref K_USB_PID_MDATA. */
   unsigned_t packetStatus:4;                              /*!< Ce champ de bits contient le status du paquet. Il peut prendre les valeurs \ref K_USB_IN_DATA_PACKET, \ref K_USB_IN_TRANSFER_COMPLETED, \ref K_USB_DATA_TOOGLE_ERROR et \ref K_USB_CHANNEL_HALTED. */
   unsigned_t rsv:11;                                      /*!< Ce champ de bits est reservé pour un usage ultérieur. */
};

/**
 * @struct T_USBOTGDeviceRxStatusField
 * @brief Déclaration du type T_USBOTGDeviceRxStatusField.
 */

typedef struct T_USBOTGDeviceRxStatusField T_USBOTGDeviceRxStatusField;
struct T_USBOTGDeviceRxStatusField
{
   unsigned_t endpointNumber:4;                            /*!< Ce champ de bits contient le numéro de la terminaison du paquet. */
   unsigned_t count:11;                                    /*!< Ce champ de bits contient le nombre d'octets du paquet. */
   unsigned_t pid:2;                                       /*!< Ce champ de bits contient le PID du paquet. Il peut prendre les valeurs \ref K_USB_PID_DATA0, \ref K_USB_PID_DATA1, \ref K_USB_PID_DATA2 et \ref K_USB_PID_MDATA. */
   unsigned_t packetStatus:4;                              /*!< Ce champ de bits contient le status du paquet. Il peut prendre les valeurs \ref K_USB_GLOBAL_OUT_NACK, \ref K_USB_OUT_DATA_PACKET, \ref K_USB_OUT_TRANSFER_COMPLETED, \ref K_USB_SETUP_TRANSACTION_COMPLETED et \ref K_USB_SETUP_DATA_PACKET_RECEIVED. */
   unsigned_t frameNumber:4;                               /*!< Ce champ de bits contient les 4 bits de poids faible du numéro de trame. */
   unsigned_t rsv:7;                                       /*!< Ce champ de bits est reservé pour un usage ultérieur. */
};

/**
 * @struct T_USBOTGRxStatus
 * @brief Déclaration du type T_USBOTGRxStatus.
 */

typedef union T_USBOTGRxStatus T_USBOTGRxStatus;
union T_USBOTGRxStatus
{
   T_USBOTGDeviceRxStatusField deviceField;                /*!< Ce membre contient le registre de status du mode 'Device'. */
   T_USBOTGHostRxStatusField hostField;                    /*!< Ce membre contient le registre de status du mode 'Host'. */
   uint32_t value;                                         /*!< Ce membre contient la valeur du registre. */
};

/**
 *
 */

/**
 * @struct T_USBOTGNonPeriodicTxStatusField
 * @brief Déclaration du type T_USBOTGNonPeriodicTxStatusField.
 */

typedef struct T_USBOTGNonPeriodicTxStatusField T_USBOTGNonPeriodicTxStatusField;
struct T_USBOTGNonPeriodicTxStatusField
{
   unsigned_t wordSpace:16;                                /*!< Ce champ de bits contient le nombre de mots 32bits disponibles dans le FIFO de transmission de type non périodique. */
   unsigned_t entrySpace:8;                                /*!< Ce champ de bits contient le nombre d'entrées disponibles dans la file de requêtes. */
   unsigned_t terminate:1;                                 /*!< Ce champ de bits indique si la dernière entrée est en cours de traitement <1> dans le file de requêtes ou non <0>. */
   unsigned_t currentEntry:2;                              /*!< Ce champ de bits contient le type de l'entrée en cours de traitement dans le file de requêtes. Il peut prendre les valeurs \ref K_USB_ENTRY_IN_OUT_TOKEN, \ref K_USB_ENTRY_ZERO_LENGTH_PACKET et \ref K_USB_ENTRY_CHANNEL_HALT. */
   unsigned_t channelNumber:4;                             /*!< Ce champ de bits contient le numéro de canal de l'entrée en cours de traitement dans la file de requêtes. */
   unsigned_t rsv:1;                                       /*!< Ce champ de bits est reservé pour un usage ultérieur. */
};

/**
 * @struct T_USBOTGNonPeriodicTxStatus
 * @brief Déclaration du type T_USBOTGNonPeriodicTxStatus.
 */

typedef union T_USBOTGNonPeriodicTxStatus T_USBOTGNonPeriodicTxStatus;
union T_USBOTGNonPeriodicTxStatus
{
   T_USBOTGNonPeriodicTxStatusField field;                 /*!< Ce membre contient le registre de status du FIFO de transmission de type non périodique. */
   uint32_t value;                                         /*!< Ce membre contient la valeur du registre. */
};

/**
 *
 */

/**
 * @struct T_USBOTGPeriodicTxStatusField
 * @brief Déclaration du type T_USBOTGPeriodicTxStatusField.
 */

typedef struct T_USBOTGPeriodicTxStatusField T_USBOTGPeriodicTxStatusField;
struct T_USBOTGPeriodicTxStatusField
{
   unsigned_t wordSpace:16;                                /*!< Ce champ de bits contient le nombre de mots 32bits disponibles dans le FIFO de transmission de type non périodique. */
   unsigned_t entrySpace:8;                                /*!< Ce champ de bits contient le nombre d'entrées disponibles dans la file de requêtes. */
   unsigned_t terminate:1;                                 /*!< Ce champ de bits indique si la dernière entrée est en cours de traitement <1> dans le file de requêtes ou non <0>. */
   unsigned_t currentEntry:2;                              /*!< Ce champ de bits contient le type de l'entrée en cours de traitement dans le file de requêtes. Il peut prendre les valeurs \ref K_USB_ENTRY_IN_OUT_TOKEN, \ref K_USB_ENTRY_ZERO_LENGTH_PACKET et \ref K_USB_DISABLE_CHANNEL_CMD. */
   unsigned_t channelNumber:4;                             /*!< Ce champ de bits contient le numéro de canal de l'entrée en cours de traitement dans la file de requêtes. */
   unsigned_t oddEven:1;                                   /*!< Ce champ de bits contient le type de trame. Il peut prendre les valeurs \ref K_USB_EVEN_FRAME et \ref K_USB_ODD_FRAME */
};

/**
 * @struct T_USBOTGPeriodicTxStatus
 * @brief Déclaration du type T_USBOTGPeriodicTxStatus.
 */

typedef union T_USBOTGPeriodicTxStatus T_USBOTGPeriodicTxStatus;
union T_USBOTGPeriodicTxStatus
{
   T_USBOTGPeriodicTxStatusField field;                    /*!< Ce membre contient le registre de status du FIFO de transmission de type périodique. */
   uint32_t value;                                         /*!< Ce membre contient la valeur du registre. */
};

/**
 *
 */

/**
 * @struct T_USBOTGChannelConfigurationField
 * @brief Déclaration du type T_USBOTGChannelConfigurationField.
 */

typedef struct T_USBOTGChannelConfigurationField T_USBOTGChannelConfigurationField;
struct T_USBOTGChannelConfigurationField
{
   unsigned_t maxPacketSize:11;                            /*!< Ce champ de bits indique la taille maximal d'un paquet [en octets]. */
   unsigned_t endPointNumber:4;                            /*!< Ce champ de bits contient l'identifiant de la terminaison. Il peut prendre les valeurs \ref K_USB_ENDPOINT0 à \ref K_USB_ENDPOINT5 pour le périphérique USB_OTG_FS ou les valeurs \ref K_USB_ENDPOINT0 à \ref K_USB_ENDPOINT8 pour le périphérique USB_OTG_LS.*/
   unsigned_t endPointDirection:1;                         /*!< Ce champ de bits contient la direction de la terminaison. Il peut prendre les valeurs suivantes \ref K_USB_IN_ENDPOINT et \ref K_USB_OUT_ENDPOINT. */
   unsigned_t rsv2:1;                                      /*!< Ce champ de bits est reservé pour un usage ultérieur. */
   unsigned_t speed:1;                                     /*!< Ce champ de bits contient la vitesse de fonctionnement du canal. Il peut prendre les valeurs \ref K_USB_FSHS_CHANNEL et \ref K_USB_LS_CHANNEL. */
   unsigned_t endPointType:2;                              /*!< Ce champ de bits contient le type de terminaison. Il peut prendre les valeurs \ref K_USB_CONTROL_ENDPOINT, \ref K_USB_ISOCHRONOUS_ENDPOINT, \ref K_USB_BULK_ENDPOINT ou \ref K_USB_INTERRUPT_ENDPOINT.*/
   unsigned_t transactionPerFrame:2;                       /*!< Ce champ de bits contient le nombre de transaction dans une trame. Il évolue entre [1 et 3]. */
   unsigned_t deviceAddr:7;                                /*!< Ce champ de bits contient l'adresse du périphérique. Il évolue entre [0 et 127]. */
   unsigned_t oddFrame:1;                                  /*!< Ce champ de bits contient la parité de la trame. Il peut prendre les valeurs \ref K_USB_EVEN_FRAME et \ref K_USB_ODD_FRAME. */
   unsigned_t rsv1:2;                                      /*!< Ce champ de bits est reservé pour un usage ultérieur. */
};

/**
 * @struct T_USBOTGSplitChannelField
 * @brief Déclaration du type T_USBOTGSplitChannelField.
 */

typedef struct T_USBOTGSplitChannelField T_USBOTGSplitChannelField;
struct T_USBOTGSplitChannelField
{
   unsigned_t portAddr:7;                                  /*!< Ce champ de bits stocke l'adresse du destinataire de la transaction de type 'SPLIT'. Il évolue entre [0 et 127]. */
   unsigned_t hubAddr:7;                                   /*!< Ce champ de bits stocke l'adresse du HUB. Il évolue entre [0 et 127]. */
   unsigned_t position:2;                                  /*!< Ce champ de bits indique si la totalité, le premier, le dernier ou le 'payloads' median doit être envoyé lors d'une transaction de type OUT. Il peut prendre les valeurs \ref K_USB_ALL_PAYLOADS, \ref K_USB_FIRST_PAYLOAD, \ref K_USB_MIDDLE_PAYLOAD et \ref K_USB_LAST_PAYLOAD. */
   unsigned_t transaction:1;                               /*!< Ce champ de bits indique au coeur d'effectuer une transaction de type COMPLETE_SPLIT. Il peut prendre les valeurs \ref K_USB_COMPLETE_SPLIT et \ref K_USB_START_SPLIT. */
   unsigned_t rsv:14;                                      /*!< Ce champ de bits est reservé pour un usage ultérieur. */
   unsigned_t split:1;                                     /*!< Ce champ de bits autorise le canal à effectuer des transactions de type SPLIT afin d'interfacer un bus HS avec un bus LS via un HUB. Il peut prendre les valeurs \ref K_USB_SPLIT_MODE_ENABLE et \ref K_USB_SPLIT_MODE_DISABLE. */
};

/**
 * @struct T_USBOTGTransferSizeChannelField
 * @brief Déclaration du type T_USBOTGTransferSizeChannelField.
 */

typedef struct T_USBOTGTransferSizeChannelField T_USBOTGTransferSizeChannelField;
struct T_USBOTGTransferSizeChannelField
{
   unsigned_t transferSize:19;                             /*!< Ce champ de bits défini, dans le cas d'une transaction de type OUT, le nombre d'octets qui constitue le transfert ou dans le cas d'une transaction de type IN, la taille du buffer de réception allouée par l'application (taille du buffer multiple de la taille maximal d'un paquet). */
   unsigned_t packetCount:10;                              /*!< Ce champ de bits défini le nombre de paquet constituant une transaction (transmission ou réception). */
   unsigned_t pid:2;                                       /*!< Ce champ de bits défini l'identifiant du paquet utilisé pour la première transaction. Il peut prendre les valeurs \ref K_USB_PID_DATA0, \ref K_USB_PID_DATA1, \ref K_USB_PID_DATA2, , \ref K_USB_PID_MDATA et \ref K_USB_PID_SETUP. */
   unsigned_t ping:1;                                      /*!< Ce champ de bits est reservé pour un usage ultérieur. */
};

/**
 * @struct T_USBOTGChannelConfiguration
 * @brief Déclaration du type T_USBOTGChannelConfiguration.
 */

typedef union T_USBOTGChannelConfiguration T_USBOTGChannelConfiguration;
union T_USBOTGChannelConfiguration
{
   T_USBOTGChannelConfigurationField field;                /*!< Ce membre contient le registre de configuration d'un canal de communication. */
   uint32_t value;                                         /*!< Ce membre contient la valeur du registre. */
};

/**
 * @struct T_USBOTGChannelConfiguration
 * @brief Déclaration du type T_USBOTGChannelConfiguration.
 */

typedef union T_USBOTGSplitChannel T_USBOTGSplitChannel;
union T_USBOTGSplitChannel
{
   T_USBOTGSplitChannelField field;                        /*!< Ce membre contient le registre de configuration de type SPLIT d'un canal de communication. */
   uint32_t value;                                         /*!< Ce membre contient la valeur du registre. */
};

/**
 * @struct T_USBOTGChannelConfiguration
 * @brief Déclaration du type T_USBOTGChannelConfiguration.
 */

typedef union T_USBOTGTransferSizeChannel T_USBOTGTransferSizeChannel;
union T_USBOTGTransferSizeChannel
{
   T_USBOTGTransferSizeChannelField field;                 /*!< Ce membre contient le registre de configuration d'un transfert d'un canal de communication. */
   uint32_t value;                                         /*!< Ce membre contient la valeur du registre. */
};

/**
 * @struct T_USBOTGChannel
 * @brief Déclaration du type T_USBOTGChannel.
 */

typedef struct T_USBOTGChannel T_USBOTGChannel;
struct T_USBOTGChannel
{
   uint32_t dmaAddr;                                       /*!< Ce membre contient l'adresse du buffer DMA. */
   T_USBOTGChannelConfiguration cfgRegister;               /*!< Ce membre contient le registre de configuration d'un canal de communication. */
   T_USBOTGSplitChannel splitRegister;                     /*!< Ce membre contient le registre de configuration de type SPLIT d'un canal de communication. */
   T_USBOTGTransferSizeChannel transferRegister;           /*!< Ce membre contient le registre de configuration d'un transfert sur le canal de communication. */
};

/**
 *
 */

/**
 * @struct T_USBOTGINEndpointConfigurationField
 * @brief Déclaration du type T_USBOTGINEndpointConfigurationField.
 */

typedef struct T_USBOTGINEndpointConfigurationField T_USBOTGINEndpointConfigurationField;
struct T_USBOTGINEndpointConfigurationField
{
   unsigned_t maxPacketSize:11;                            /*!< Ce membre contient la taille maximum d'un paquet [en octets]. Les valeurs 8, 16, 32 et 64 sont autorisées pour la terminaison 0 du périphérique USB_OTGFS. */
   unsigned_t rsv4:4;                                      /*!< Ce champ de bits est reservé. */
   unsigned_t active:1;                                    /*!< Ce champ indique si la terminaison est active dans la configuration courante. Il peut prendre les valeurs \ref K_USB_ENDPOINT_ACTIVE et \ref K_USB_ENDPOINT_NOT_ACTIVE. La terminaison 0 est toujours active. */
   unsigned_t rsv3:2;                                      /*!< Ce champ de bits est reservé. */
   unsigned_t endpointType:2;                              /*!< Ce membre contient le type de la terminaison. Il peut prendre les valeurs \ref K_USB_CONTROL_ENDPOINT, \ref K_USB_ISOCHRONOUS_ENDPOINT, \ref K_USB_BULK_ENDPOINT et \ref K_USB_INTERRUPT_ENDPOINT. La terminaison 0 est de type CONTROL. */
   unsigned_t rsv2:2;                                      /*!< Ce champ de bits est reservé. */
   unsigned_t fifoNumber:4;                                /*!< Ce membre contient le numéro du FIFO de transmission assigné à la terminaison. */
   unsigned_t rsv1:6;                                      /*!< Ce champ de bits est reservé. */
};

/**
 * @struct T_USBOTGINEndpointTransferSizeField
 * @brief Déclaration du type T_USBOTGINEndpointTransferSizeField.
 */

typedef struct T_USBOTGINEndpointTransferSizeField T_USBOTGINEndpointTransferSizeField;
struct T_USBOTGINEndpointTransferSizeField
{
   unsigned_t transferSize:19;                             /*!< Ce champ indique la taille d'une transaction [en octets]. La valeur évolue de [1 à 127] pour la terminaison 0. */
   unsigned_t packetCount:10;                              /*!< Ce champ indique le nombre total de paquets constituant une transaction. La terminaison 0 autorise un maximum de 3 paquets. */
   unsigned_t setupPacketCount:2;                          /*!< Ce champ indique le nombre de paquets de configuration 'SETUP' que la terminaison peut recevoir. Il peut prendre les valeurs 1, 2 ou 3. Ce champ n'est pas implémenté pour la terminaison 0. */
   unsigned_t rsv1:1;                                      /*!< Ce champ de bits est reservé. */
};

/**
 * @struct T_USBOTGINEndpointConfiguration
 * @brief Déclaration du type T_USBOTGINEndpointConfiguration.
 */

typedef union T_USBOTGINEndpointConfiguration T_USBOTGINEndpointConfiguration;
union T_USBOTGINEndpointConfiguration
{
   T_USBOTGINEndpointConfigurationField field;             /*!< Ce membre contient le registre de configuration d'une terminaison de type IN. */
   uint32_t value;                                         /*!< Ce membre contient la valeur du registre. */
};

/**
 * @struct T_USBOTGINEndpointTransferSize
 * @brief Déclaration du type T_USBOTGINEndpointTransferSize.
 */

typedef union T_USBOTGINEndpointTransferSize T_USBOTGINEndpointTransferSize;
union T_USBOTGINEndpointTransferSize
{
   T_USBOTGINEndpointTransferSizeField field;              /*!< Ce membre contient le registre de configuration d'un transfert sur une terminaison de type IN. */
   uint32_t value;                                         /*!< Ce membre contient la valeur du registre. */
};

/**
 * @struct T_USBOTGINEndpoint
 * @brief Déclaration du type T_USBOTGINEndpoint.
 */

typedef struct T_USBOTGINEndpoint T_USBOTGINEndpoint;
struct T_USBOTGINEndpoint
{
   uint32_t dmaAddr;                                       /*!< Ce membre contient l'adresse du buffer DMA. */
   T_USBOTGINEndpointConfiguration cfgRegister;            /*!< Ce membre contient le registre de configuration d'une terminaison de type IN. */
   T_USBOTGINEndpointTransferSize transferRegister;        /*!< Ce membre contient le registre de configuration d'un tranfert sur une terminaison de type IN. */
};

/**
 *
 */

/**
 * @struct T_USBOTGOUTEndpointConfigurationField
 * @brief Déclaration du type T_USBOTGOUTEndpointConfigurationField.
 */

typedef struct T_USBOTGOUTEndpointConfigurationField T_USBOTGOUTEndpointConfigurationField;
struct T_USBOTGOUTEndpointConfigurationField
{
   unsigned_t maxPacketSize:11;                            /*!< Ce membre contient la taille maximum d'un paquet [en octets]. Les valeurs 8, 16, 32 et 64 sont autorisées pour la terminaison 0 du périphérique USB_OTGFS. */
   unsigned_t rsv3:4;                                      /*!< Ce champ de bits est reservé. */
   unsigned_t active:1;                                    /*!< Ce champ indique si la terminaison est active dans la configuration courante. Il peut prendre les valeurs \ref K_USB_ENDPOINT_ACTIVE et \ref K_USB_ENDPOINT_NOT_ACTIVE. La terminaison 0 est toujours active. */
   unsigned_t rsv2:2;                                      /*!< Ce champ de bits est reservé. */
   unsigned_t endpointType:2;                              /*!< Ce membre contient le type de la terminaison. Il peut prendre les valeurs \ref K_USB_CONTROL_ENDPOINT, \ref K_USB_ISOCHRONOUS_ENDPOINT, \ref K_USB_BULK_ENDPOINT et \ref K_USB_INTERRUPT_ENDPOINT. La terminaison 0 est de type CONTROL. */
   unsigned_t snoopMode:1;                                 /*!< Ce champ de bits permet l'activation du mode 'SNOOP' qui permet de ne pas vérifier la conformité des paquets de type OUT avant de les transmettre à l'application. IL peut prendre les valeurs 1 (activé) ou 0 (désactivé). */
   unsigned_t rsv1:11;                                     /*!< Ce champ de bits est reservé. */
};

/**
 * @struct T_USBOTGOUTEndpointTransferSizeField
 * @brief Déclaration du type T_USBOTGOUTEndpointTransferSizeField.
 */

typedef struct T_USBOTGOUTEndpointTransferSizeField T_USBOTGOUTEndpointTransferSizeField;
struct T_USBOTGOUTEndpointTransferSizeField
{
   unsigned_t transferSize:19;                             /*!< Ce membre contient la taille d'une transaction [en octets]. La valeur évolue de [1 à 127] pour la terminaison 0. */
   unsigned_t packetCount:10;                              /*!< Ce champ indique le nombre total de paquets constituant une transaction. La terminaison 0 autorise uniquement 1 paquet. */
   unsigned_t setupPacketCount:2;                          /*!< Ce champ indique le nombre de paquets de type 'SETUP' qu'une terminaison de controle de type OUT peut recevoir. */
   unsigned_t rsv1:1;                                      /*!< Ce champ de bits est reservé. */
};

/**
 * @struct T_USBOTGOUTEndpointConfiguration
 * @brief Déclaration du type T_USBOTGOUTEndpointConfiguration.
 */

typedef union T_USBOTGOUTEndpointConfiguration T_USBOTGOUTEndpointConfiguration;
union T_USBOTGOUTEndpointConfiguration
{
   T_USBOTGOUTEndpointConfigurationField field;            /*!< Ce membre contient le registre de configuration d'une terminaison de type OUT. */
   uint32_t value;                                         /*!< Ce membre contient la valeur du registre. */
};

/**
 * @struct T_USBOTGOUTEndpointTransferSize
 * @brief Déclaration du type T_USBOTGOUTEndpointTransferSize.
 */

typedef union T_USBOTGOUTEndpointTransferSize T_USBOTGOUTEndpointTransferSize;
union T_USBOTGOUTEndpointTransferSize
{
   T_USBOTGOUTEndpointTransferSizeField field;             /*!< Ce membre contient le registre de configuration d'un transfert sur une terminaison de type OUT. */
   uint32_t value;                                         /*!< Ce membre contient la valeur du registre. */
};

/**
 * @struct T_USBOTGINEndpoint
 * @brief Déclaration du type T_USBOTGINEndpoint.
 */

typedef struct T_USBOTGOUTEndpoint T_USBOTGOUTEndpoint;
struct T_USBOTGOUTEndpoint
{
   uint32_t dmaAddr;                                       /*!< Ce membre contient l'adresse du buffer DMA. */
   T_USBOTGOUTEndpointConfiguration cfgRegister;           /*!< Ce membre contient le registre de configuration d'une terminaison de type OUT. */
   T_USBOTGOUTEndpointTransferSize transferRegister;       /*!< Ce membre contient le registre de configuration d'un tranfert sur une terminaison de type OUT. */
};

/**
 *
 */

#endif

