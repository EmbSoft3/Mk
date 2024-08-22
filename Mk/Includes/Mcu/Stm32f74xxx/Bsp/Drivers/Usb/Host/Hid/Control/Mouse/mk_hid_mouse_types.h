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
* @file mk_hid_mouse_types.h
* @brief Déclaration des types dédiés aux objets 'Mouse'.
* @date 31 oct. 2019
*
*/

#ifndef MK_HID_MOUSE_TYPES_H
#define MK_HID_MOUSE_TYPES_H

/**
 * @struct T_mkMouseLayer
 * @brief Déclaration de la structure T_mkMouseLayer.
 *
 */

typedef struct T_mkMouseLayer T_mkMouseLayer;
struct T_mkMouseLayer
{
   uint16_t type;                               /*!< Ce membre contient le type du contrôle applicatif (\ref K_MK_CONTROL_MOUSE). La position de cet attribut ne doit pas être modifiée. */
   uint16_t id;                                 /*!< Ce membre contient l'identifiant unique du contrôle applicatif \ref T_mkMouse. La position de cet attribut ne doit pas être modifiée. */
};

/**
 * @struct T_mkMouse
 * @brief Déclaration de la structure T_mkMouse.
 *
 */

typedef struct T_mkMouse T_mkMouse;
struct T_mkMouse
{
   T_mkMouseLayer layer;                        /*!< Ce membre contient le registre d'identification du contrôle de type \ref T_mkMouse. La position de cet attribut ne doit pas être modifiée. */
   T_mkAxis2 axis;                              /*!< Ce membre contient le contrôle de type \ref T_mkAxis2 de la souris. */

   T_mkWheel wheel;                             /*!< Ce membre contient le contrôle de type 'Wheel' de la souris. */
   T_mkWheel acPan;                             /*!< Ce membre contient le contrôle de type 'ACPAN' de la souris. */

   T_mkButton* button;                          /*!< Ce membre contient une liste de contrôle de type \ref T_mkButton dédié à la souris. */
   T_mkCursor cursor;                           /*!< Ce membre contient un objet graphique de type \ref T_mkCursor. */
};

/**
 * @struct T_mkMousePool
 * @brief Déclaration de la structure T_mkMousePool.
 *
 */

typedef struct T_mkMousePool T_mkMousePool;
struct T_mkMousePool
{
   T_mkPoolArea area;                           /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   T_mkPool* pool;                              /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les structures \ref T_mkMouse. */
   T_mkMouse heap [ K_MK_MOUSE_NUMBER ];        /*!< Ce membre contient la mémoire dédiée aux structures \ref T_mkMouse. */
};

/**
 *
 */

#endif

