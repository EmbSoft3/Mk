/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_display_request_types.h
* @brief Déclaration des types dédiés au module 'Request'.
* @date 30 oct. 2022
*
*/

#ifndef MK_DISPLAY_REQUEST_TYPES_H
#define MK_DISPLAY_REQUEST_TYPES_H

/**
 * @enum T_mkDisplayRequestType
 * @brief Déclaration de la structure T_mkDisplayRequestType.
 */

typedef enum T_mkDisplayRequestType
{
   K_MK_DISPLAY_REQUEST_TYPE_CONTAINER = 0x0,               /*!< Définition de l'identifiant d'une requête de type 'Container'. */
   K_MK_DISPLAY_REQUEST_TYPE_APPLICATION = 0x1,             /*!< Définition de l'identifiant d'une requête de type 'Application'. */
   K_MK_DISPLAY_REQUEST_TYPE_CHROMART = 0x2,                /*!< Définition de l'identifiant d'une requête de type 'Chromart'. */
   K_MK_DISPLAY_REQUEST_TYPE_ENGINE = 0x3                   /*!< Définition de l'identifiant d'une requête de type 'Engine'. */
} T_mkDisplayRequestType;

/**
 * @struct T_mkDisplayRequestContent
 * @brief Déclaration de la structure T_mkDisplayRequestContent.
 */

typedef union T_mkDisplayRequestContent T_mkDisplayRequestContent;
union T_mkDisplayRequestContent
{
   T_mkChromartRequest chromart;                            /*!< Ce membre contient les attributs d'une requête de type 'Chromart' (\ref T_mkChromartRequest). */
   T_mkContainerRequest container;                          /*!< Ce membre contient les attributs d'une requête de type 'Container' (\ref T_mkContainerRequest). */
   T_mkApplicationRequest application;                      /*!< Ce membre contient les attributs d'une requête de type 'Application' (\ref T_mkApplicationRequest). */
   T_mkDisplayEngineRequest engine;                         /*!< Ce membre contient les attributs d'une requête de type 'Engine' (\ref T_mkDisplayEngineRequest). */
};

/**
 * @struct T_mkDisplayRequest
 * @brief Déclaration de la structure T_mkDisplayRequest.
 */

typedef struct T_mkDisplayRequest T_mkDisplayRequest;
struct T_mkDisplayRequest
{
   T_mkDisplayRequestType type;                             /*!< Ce membre contient l'identifiant de la requête. */
   T_mkDisplayRequestContent content;                       /*!< Ce membre contient les attributs de la requête. */
};

/**
 *
 */

#endif

