/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_supervisor_types.h
* @brief Déclaration des types dédiés au superviseur.
* @date 4 janv. 2023
*
*/

#ifndef MK_SUPERVISOR_TYPES_H
#define MK_SUPERVISOR_TYPES_H

/**
 * @struct T_mkSupervisorStack
 * @brief Déclaration de la structure T_mkSupervisorStack.
 *
 */

typedef struct T_mkSupervisorStack T_mkSupervisorStack;
struct T_mkSupervisorStack
{
   uint32_t buf [ K_MK_SUPERVISOR_APPLICATION_STACK_SIZE ];    /*!< Ce membre contient la stack de l'application. */
};

/**
 * @struct T_mkSupervisorMessageArea
 * @brief Déclaration de la structure T_mkSupervisorMessageArea.
 *
 */

typedef struct T_mkSupervisorMessageArea T_mkSupervisorMessageArea;
struct T_mkSupervisorMessageArea
{
   T_mkMail* mail;                                             /*!< Ce membre contient la boite de messages permettant l'émission de requêtes à destination du superviseur. */
   T_mkPoolArea area;                                          /*!< Ce membre contient les caractéristiques mémoire de la boite de messages. */
   uint32_t heap [ K_MK_SUPERVISOR_MESSAGE_AREA_SIZE ];        /*!< Ce membre contient la mémoire dédiée à la boite de messages. */
};

/**
 * @struct T_mkSupervisorMemoryPage
 * @brief Déclaration de la structure T_mkSupervisorMemoryPage.
 *
 */

typedef struct T_mkSupervisorMemoryPage T_mkSupervisorMemoryPage;
struct T_mkSupervisorMemoryPage
{
   T_mkAddr baseAddr;                                          /*!< Ce membre contient l'adresse de base de la page mémoire allouée par le superviseur. */
   T_mkAddr windowCache;                                       /*!< Ce membre contient l'adresse du cache dédié à la fenêtre de la console. */
   T_mkAddr promptCache;                                       /*!< Ce membre contient l'adresse du cache dédié à la boite de saisie de la console. */
   T_mkAddr windowAddr;                                        /*!< Ce membre contient l'adresse du buffer stockant les caractères de la fenêtre de la console. */
   T_mkAddr promptAddr;                                        /*!< Ce membre contient l'adresse du buffer stockant les caractères de la boite de saisie de la console. */
   T_mkAddr reportAddr;                                        /*!< Ce membre contient l'adresse du buffer stockant le contenu du rapport d'erreur. */
};

/**
 * @struct T_mkSupervisorLayer
 * @brief Déclaration de la structure T_mkSupervisorLayer.
 *
 */

typedef struct T_mkSupervisorLayer T_mkSupervisorLayer;
struct T_mkSupervisorLayer
{
   T_mkLayer layers;                                           /*!< Ce membre contient l'objet de configuration des layers du superviseur. */
};

/**
 * @struct T_mkSupervisorLoad
 * @brief Déclaration de la structure T_mkSupervisorLoad.
 *
 */

typedef struct T_mkSupervisorLoad T_mkSupervisorLoad;
struct T_mkSupervisorLoad
{
   T_mkFigure cpu;                                             /*!< Ce membre contient la figure qui affiche la charge CPU. */
   T_mkFigure frameRate;                                       /*!< Ce membre contient la figure qui affiche le frameRate. */
   T_mkTextStyle style;                                        /*!< Ce membre contient le style des figures qui affiche le frameRate et la charge CPU. */
   vuint16_t foregroundEnabled;                                /*!< Ce membre contient la valeur \ref K_MK_TRUE si l'affichage du framerate et de la charge CPU doit être réalisé sur le premier plan sinon la valeur \ref K_MK_FALSE. */
   vuint16_t backgroundEnabled;                                /*!< Ce membre contient la valeur \ref K_MK_TRUE si l'affichage du framerate et de la charge CPU doit être réalisé sur l'arrière plan sinon la valeur \ref K_MK_FALSE. */
   char8_t cpuBuffer [ 4 ];                                    /*!< Ce membre contient la valeur de la charge CPU en [ASCII]. */
   char8_t frameRateBuffer [ 4 ];                              /*!< Ce membre contient la valeur du frameRate en [ASCII]. */
};

/**
 * @struct T_mkSupervisor
 * @brief Déclaration de la structure T_mkSupervisor.
 *
 */

typedef struct T_mkSupervisor T_mkSupervisor;
struct T_mkSupervisor
{
   T_mkVolume* volume;                                         /*!< Ce membre contient l'adresse de la partition où est stocké le système d'exploitation. */
   T_mkApplication application;                                /*!< Ce membre contient l'instance applicative du superviseur. */
   T_mkSupervisorStack stack;                                  /*!< Ce membre contient la stack de l'application. */
   T_mkSupervisorMessageArea message;                          /*!< Ce membre contient les données relatives à la messagerie du superviseur. */
   T_mkSupervisorMemoryPage page;                              /*!< Ce membre contient les données relatives aux pages de mémoire du superviseur. */
   T_mkSupervisorLayer layer;                                  /*!< Ce membre contient la structure de configuration des layers du superviseur. */
   T_mkConsole console;                                        /*!< Ce membre contient l'instance de la console du superviseur. */
   T_mkSupervisorLoad load;                                    /*!< Ce membre contient les données relatives à la charge CPU et au framerate. */
};

/**
 *
 */

#endif


