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
* @file mk_home_types.h
* @brief Déclaration des types dédiés à l'application home.
* @date 6 mai 2019
*
*/

#ifndef MK_HOME_TYPES_H
#define MK_HOME_TYPES_H

/**
 * @struct T_mkHomeRessources
 * @brief Déclaration de la structure T_mkHomeRessources.
 *
 */

typedef struct T_mkHomeRessources T_mkHomeRessources;
struct T_mkHomeRessources
{
   T_mkPool* pool;                                                      /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement le logos des applications. */
   T_mkPoolArea area;                                                   /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   T_mkBMPFile applicationLogo [ K_MK_DISPLAY_APPLICATION_NUMBER ];     /*!< Ce membre contient les fichiers images dédiés au logo des applications. */
   T_mkBMPFile background;                                              /*!< Ce membre contient le fichier image stockant l'arrière plan de la vue principale. */
   T_mkBMPFile managerSystemStatusLogo;                                 /*!< Ce membre contient le fichier image stockant le logo du manager. */
};

/**
 * @struct T_mkHomeLayer
 * @brief Déclaration de la structure T_mkHomeLayer.
 *
 */

typedef struct T_mkHomeLayer T_mkHomeLayer;
struct T_mkHomeLayer
{
   T_mkContainer* container;                                            /*!< Ce membre contient le container de la vue. */
   T_mkLayer layers;                                                    /*!< Ce membre contient l'objet de configuration des layers de l'application home. */
};

/**
 * @struct T_mkHomeViews
 * @brief Déclaration de la structure T_mkHomeViews.
 *
 */

typedef struct T_mkHomeViews T_mkHomeViews;
struct T_mkHomeViews
{
   T_mkHomeRessources ressources;                                       /*!< Ce membre contient les ressources de l'application home. */
   T_mkHomeLayer layer;                                                 /*!< Ce membre contient les structures de configuration des layers de l'application home. */
   T_mkHomeManagerView manager;                                         /*!< Ce membre contient les attributs de la vue manager de l'application home. */
   T_mkHomeMainView main;                                               /*!< Ce membre contient les attributs de la vue principale de l'application home. */
};

/**
 * @struct T_mkHomePage
 * @brief Déclaration de la structure T_mkHomePage.
 *
 */

typedef struct T_mkHomePage T_mkHomePage;
struct T_mkHomePage
{
   uint32_t* pointer;                                                   /*!< Ce membre contient la prochaine adresse disponible dans la page mémoire allouée par l'application. */
   uint32_t* background;                                                /*!< Ce membre contient l'adresse où l'arrière plan de l'application home a été déployé. */
};

/**
 * @struct T_mkHomeStack
 * @brief Déclaration de la structure T_mkHomeStack.
 *
 */

typedef struct T_mkHomeStack T_mkHomeStack;
struct T_mkHomeStack
{
   uint32_t buf [ K_MK_HOME_STACK_SIZE ];                               /*!< Ce membre contient la stack de l'application. */
};

/**
 * @struct T_mkHomeApplication
 * @brief Déclaration de la structure T_mkHomeApplication.
 *
 */

typedef struct T_mkHomeApplication T_mkHomeApplication;
struct T_mkHomeApplication
{
   T_mkApplication* application;                                        /*!< Ce membre contient l'adresse de l'application home. */
   T_mkHomeStack stack;                                                 /*!< Ce membre contient la stack de l'application home. */
   T_mkHomePage page;                                                   /*!< Ce membre contient les attributs dédiés à la page de l'application home. */
   T_mkHomeViews view;                                                  /*!< Ce membre contient les objets présents sur le premier plan de l'application home. */
};

/**
 *
 */

#endif


