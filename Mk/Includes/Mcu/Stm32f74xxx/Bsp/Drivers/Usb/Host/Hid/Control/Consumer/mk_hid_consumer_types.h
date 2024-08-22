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
* @file mk_hid_consumer_types.h
* @brief Déclaration des types dédiés aux objets 'Consumer'.
* @date 7 mars 2020
*
*/

#ifndef MK_HID_CONSUMER_TYPES_H
#define MK_HID_CONSUMER_TYPES_H

/**
 * @struct T_mkConsumerCode
 * @brief Surcharge de la structure T_mkButton en T_mkConsumerCode.
 *
 */

typedef struct T_mkButton T_mkConsumerCode;

/**
 * @struct T_mkConsumerLayer
 * @brief Déclaration de la structure T_mkConsumerLayer.
 *
 */

typedef struct T_mkConsumerLayer T_mkConsumerLayer;
struct T_mkConsumerLayer
{
   uint16_t type;                                                    /*!< Ce membre contient le type du contrôle applicatif (\ref K_MK_CONTROL_CONSUMER). La position de cet attribut ne doit pas être modifiée. */
   uint16_t id;                                                      /*!< Ce membre contient l'identifiant unique du contrôle applicatif \ref T_mkConsumerControl. La position de cet attribut ne doit pas être modifiée. */
};

/**
 * @struct T_mkConsumerCode
 * @brief Surcharge de la structure T_mkButton en T_mkConsumerCode.
 *
 */

typedef struct T_mkConsumerControl T_mkConsumerControl;
struct T_mkConsumerControl
{
   T_mkConsumerLayer layer;                                          /*!< Ce membre contient le registre d'identification du contrôle de type \ref T_mkConsumerControl. La position de cet attribut ne doit pas être modifiée. */
   T_mkConsumerCode* control;                                        /*!< Ce membre contient l'adresse d'un ou plusieurs sélecteurs. */
};

/**
 * @struct T_mkConsumerPool
 * @brief Déclaration de la structure T_mkConsumerPool.
 *
 */

typedef struct T_mkConsumerPool T_mkConsumerPool;
struct T_mkConsumerPool
{
   T_mkPoolArea area;                                                /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   T_mkPool* pool;                                                   /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les structures \ref T_mkConsumerControl. */
   T_mkConsumerControl heap [ K_MK_CONSUMER_NUMBER ];                /*!< Ce membre contient la mémoire dédiée aux structures \ref T_mkConsumerControl. */
};

/**
 *
 */

#endif

