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
* @file mk_hcd_types.h
* @brief Déclaration des types dédiés à l'USB.
* @date 12 juin 2019
*
*/

#ifndef MK_HCD_TYPES_H
#define MK_HCD_TYPES_H

/**
 * @struct T_mkHCDEventTag
 * @brief Déclaration de la structure T_mkHCDEventTag.
 *
 */

typedef enum T_mkHCDEventTag
{
   K_MK_HCD_DEVICE_CONNECTED_EVENT = 1,                           /*!< Définition d'un code signalant la connexion du premier périphérique sur le bus. */
   K_MK_HCD_DEVICE_DISCONNECTED_EVENT = 2,                        /*!< Définition d'un code signalant la déconnexion du premier périphérique sur le bus. */
   K_MK_HCD_DEVICE_ENABLED_EVENT = 4,                             /*!< Définition d'un code signalant la fin de la phase de reset du premier périphérique sur le bus. */
   K_MK_HCD_OVERCURRENT_EVENT = 8,                                /*!< Définition d'un code signalant une surcharge sur le bus. */
   K_MK_HCD_ID_PIN_EVENT = 16,                                    /*!< Définition d'un code signalant qu'un changement de mode s'est produit. */
   K_MK_HCD_REFRESH_EVENT = 32                                    /*!< Définition d'un code signalant qu'il est temps de rafraichir les périphériques USB sur le bus. */

} T_mkHCDEventTag;

/**
 * @struct T_mkHCDHandler
 * @brief Déclaration de la structure T_mkHCDHandler.
 *
 */

typedef struct T_mkHCDHandler T_mkHCDHandler;
struct T_mkHCDHandler
{
   T_mkAddr bus;                                                  /*!< Ce membre contient l'adresse du périphérique USB matériel dédié au gestionnaire (\ref K_USB_OTGHS et \ref K_USB_OTGFS) . */
   uint8_t packetBuf [ K_MK_USB_DEFAULT_MAX_PACKET_SIZE ];        /*!< Ce membre contient le buffer permettant de récupérer les paquets de données de taille 64 octets. */
   uint8_t sofTable [ K_MK_USB_CHANNEL_NUMBER ];                  /*!< Ce membre contient la table permettant de temporisé l'émission des tokens de type 'Nyet'. */
   uint8_t channelTable [ K_MK_USB_CHANNEL_NUMBER ];              /*!< Ce membre contient la table permettant l'allocation des canaux de communication. */
   T_mkEvent* channelEvent [ K_MK_USB_CHANNEL_NUMBER ];           /*!< Ce membre contient un registre d'événements permettant la gestion des interruptions relatives aux canaux de communication. */
   T_mkEvent* portEvent;                                          /*!< Ce membre contient un registre d'événements permettant le gestion des interruptions relatives au port USB. */
   T_mkMutex* channelMutex;                                       /*!< Ce membre contient un mutex permettant d'allouer les canaux de communication de manière sécurisée. */
   T_mkHCDDevice* device;                                         /*!< Ce membre contient l'adresse du premier périphérique USB connecté sur le bus. */
   T_mkHCDList hubList;                                           /*!< Ce membre contient l'arborescence des périphériques USB (liste de hubs). */
   uint32_t resetTick;                                            /*!< Ce membre contient la durée du reset à appliquer sur le port USB [en ms]. */
};



/**
 *
 */

#endif

