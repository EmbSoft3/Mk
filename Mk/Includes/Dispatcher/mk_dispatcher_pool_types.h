/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_dispatcher_pool_types.h
* @brief Déclaration des types dédiés aux pools du dispatcher.
* @date 2 oct. 2021
*
*/

#ifndef MK_DISPATCHER_POOL_TYPES_H
#define MK_DISPATCHER_POOL_TYPES_H

/**
 * @struct T_mkDispatcherMailArea
 * @brief Déclaration de la structure T_mkDispatcherMailArea.
 *
 */

typedef struct T_mkDispatcherMailArea T_mkDispatcherMailArea;
struct T_mkDispatcherMailArea
{
   T_mkMail*    mail;                                                          /*!< Ce membre contient la boite de messages permettant l'émission de requêtes à destination du dispatcher. */
   T_mkPoolArea area;                                                          /*!< Ce membre contient les caractéristiques mémoire de la boite de messages. */
   uint32_t     heap [ K_MK_DISPATCHER_INCOMING_MESSAGE_AREA_SIZE ];           /*!< Ce membre contient la mémoire dédiée à la boite de messages. */
};

/**
 * @struct T_mkDispatcherHidArea
 * @brief Déclaration de la structure T_mkDispatcherHidArea.
 *
 */

typedef struct T_mkDispatcherHidArea T_mkDispatcherHidArea;
struct T_mkDispatcherHidArea
{
   T_mkMail*    mail;                                                          /*!< Ce membre contient la boite de messages permettant l'émission de requêtes à destination du terminal HID. */
   T_mkPoolArea area;                                                          /*!< Ce membre contient les caractéristiques mémoire de la boite de messages. */
   uint32_t     heap [ K_MK_DISPATCHER_HID_MESSAGE_AREA_SIZE ];                /*!< Ce membre contient la mémoire dédiée à la boite de messages. */
};

/**
 * @struct T_mkDispatcherListenerArea
 * @brief Déclaration de la structure T_mkDispatcherListenerArea.
 *
 */

typedef struct T_mkDispatcherListenerArea T_mkDispatcherListenerArea;
struct T_mkDispatcherListenerArea
{
   T_mkMail*    mail;                                                          /*!< Ce membre contient la boite de messages permettant l'émission de requêtes à destination de la tâche d'écoute. */
   T_mkPoolArea area;                                                          /*!< Ce membre contient les caractéristiques mémoire de la boite de messages. */
   uint32_t     heap [ K_MK_DISPATCHER_LISTENER_MESSAGE_AREA_SIZE ];           /*!< Ce membre contient la mémoire dédiée à la boite de messages. */
};

/**
 *
 */

#endif


