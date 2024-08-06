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
* @file mk_display_container_types.h
* @brief Déclaration des types dédiés au module 'Container'.
* @date 4 mai 2019
*
*/

#ifndef K_MK_DISPLAY_CONTAINER_TYPES_H
#define K_MK_DISPLAY_CONTAINER_TYPES_H

/**
 * @enum T_mkContainerRequestType
 * @brief Déclaration de la structure T_mkContainerRequestType.
 */

typedef enum T_mkContainerRequestType
{
   K_MK_DISPLAY_REQUEST_CONTAINER_CREATE = 0x0,             /*!< Définition de l'identifiant de la requête 'Container-Create'. */
   K_MK_DISPLAY_REQUEST_CONTAINER_DELETE = 0x01,            /*!< Définition de l'identifiant de la requête 'Container-Delete'. */
   K_MK_DISPLAY_REQUEST_CONTAINER_ADD = 0x2,                /*!< Définition de l'identifiant de la requête 'Container-Add'. */
   K_MK_DISPLAY_REQUEST_CONTAINER_REMOVE = 0x3,             /*!< Définition de l'identifiant de la requête 'Container-Remove'. */
   K_MK_DISPLAY_REQUEST_CONTAINER_LISTENER = 0x4,           /*!< Définition de l'identifiant de la requête 'Container-Listener'. */
   K_MK_DISPLAY_REQUEST_FACTORY_ADD = 0x5,                  /*!< Définition de l'identifiant de la requête 'Factory-Add'. */
   K_MK_DISPLAY_REQUEST_FACTORY_REMOVE = 0x6                /*!< Définition de l'identifiant de la requête 'Factory-Remove'. */
} T_mkContainerRequestType;

/**
 * @struct T_mkContainer
 * @brief Déclaration de la structure T_mkContainer.
 */

struct T_mkContainer
{
   uint32_t type;                                           /*!< Ce membre contient le type du container (\ref K_MK_TYPE_PRIVILEGED ou \ref K_MK_TYPE_DEFAULT). */
   T_mkAddr factory;                                        /*!< Ce membre contient l'adresse de la factory (\ref T_mkFactory) propriétaire du container. */
   T_mkAddr owner;                                          /*!< Ce membre contient l'adresse de l'application propriétaire du container. */
   T_mkField* first;                                        /*!< Ce membre contient l'adresse du premier champ appartenant au container (premier élément de liste). */
   T_mkField* last;                                         /*!< Ce membre contient l'adresse du dernier champ appartenant container (dernier élément de liste). */
   T_mkListener listener;                                   /*!< Ce membre contient l'adresse de la fonction d'écoute du container. */
   T_mkContainer* next;                                     /*!< Ce membre contient l'adresse du prochain container de la liste. */
   T_mkContainer* previous;                                 /*!< Ce membre contient l'adresse du précédent container de la liste. */
};

/**
 * @struct T_mkContainerRequest
 * @brief Déclaration de la structure T_mkContainerRequest.
 */

typedef struct T_mkContainerRequest T_mkContainerRequest;
struct T_mkContainerRequest
{
   uint32_t id;                                             /*!< Ce membre contient l'identifiant de la requête (\ref T_mkContainerRequestType). */
   T_mkAddr container;                                      /*!< Ce membre contient l'adresse du container de type \ref T_mkContainer objet de la requête. */
   T_mkAddr field;                                          /*!< Ce membre contient l'adresse du champ de type \ref T_mkField objet de la requête. */
   T_mkListener listener;                                   /*!< Ce membre contient l'adresse de la fonction d'écoute du container. */
   T_mkCode* result;                                        /*!< Ce membre contient le code de retour de la requête. */
   T_mkCallback* callback;                                  /*!< Ce membre contient l'adresse d'une fonction de rappel de type \ref T_mkCallback. */
};

/**
 *
 */

#endif


