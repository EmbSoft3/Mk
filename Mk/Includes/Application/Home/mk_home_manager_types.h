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
* @file mk_home_manager_types.h
* @brief Déclaration des types dédiés à la vue de gestion des ressources du système.
* @date 10 déc. 2023
*
*/

#ifndef MK_HOME_MANAGER_TYPES_H
#define MK_HOME_MANAGER_TYPES_H

/**
 * @struct T_mkHomeManagerApplicationButton
 * @brief Déclaration de la structure T_mkHomeManagerApplicationButton.
 *
 */

typedef struct T_mkHomeManagerApplicationButton T_mkHomeManagerApplicationButton;
struct T_mkHomeManagerApplicationButton
{
   T_mkTextStyle* nameStyle;                                                                          /*!< Ce membre contient l'adresse du style de la partie 'dénomination' d'un bouton applicatif. */
   T_mkTextStyle* defaultStyle;                                                                       /*!< Ce membre contient l'adresse du style de la partie 'auteur' d'un bouton applicatif. Il est dédié aux applications non privilégiées. */
   T_mkTextStyle* rightStyle;                                                                         /*!< Ce membre contient l'adresse du style de la partie 'droit' d'un bouton applicatif. Il est dédié aux applications privilégiées. */
   T_mkApplication* application;                                                                      /*!< Ce membre contient l'adresse d'une application. */
   T_mkButtonImage button;                                                                            /*!< Ce membre contient un bouton image. */
};

/**
 * @struct T_mkHomeManagerApplicationList
 * @brief Déclaration de la structure T_mkHomeManagerApplicationList.
 *
 */

typedef struct T_mkHomeManagerApplicationList T_mkHomeManagerApplicationList;
struct T_mkHomeManagerApplicationList
{
   T_mkFont font;                                                                                     /*!< Ce membre contient la police de caractères des boutons applicatifs. */
   T_mkFontPage page;                                                                                 /*!< Ce membre contient la page de caractères des boutons applicatifs. */
   T_mkTextStyle nameStyle;                                                                           /*!< Ce membre contient le style de la partie 'dénomination' des boutons applicatifs. */
   T_mkTextStyle rightStyle;                                                                          /*!< Ce membre contient le style de la partie 'auteur' d'un bouton applicatif. Il est dédié aux applications non privilégiées. */
   T_mkTextStyle defaultStyle;                                                                        /*!< Ce membre contient le style de la partie 'droit' d'un bouton applicatif. Il est dédié aux applications privilégiées. */
   T_mkHomeManagerApplicationButton app [ K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER ];      /*!< Ce membre contient les boutons de la barre applicative du manager. */
};

/**
 * @struct T_mkHomeManagerGraph2D
 * @brief Déclaration de la structure T_mkHomeManagerGraph2D.
 *
 */

typedef struct T_mkHomeManagerGraph2D T_mkHomeManagerGraph2D;
struct T_mkHomeManagerGraph2D
{
   T_mkGraph2D graph;                                                                                 /*!< Ce membre contient un graphique 2 dimensions. */
   real32_t buf [ 64 ];                                                                               /*!< Ce membre contient le buffer de points du graphique. */
};

/**
 * @struct T_mkHomeManagerStatus
 * @brief Déclaration de la structure T_mkHomeManagerStatus.
 *
 */

typedef struct T_mkHomeManagerStatus T_mkHomeManagerStatus;
struct T_mkHomeManagerStatus
{
   char8_t strApps [ 8 ];                                                                             /*!< Ce membre contient la chaine de caractères stockant le nombre d'applications installées sur le système (format [n]/[m]). */
   char8_t strTask [ 8 ];                                                                             /*!< Ce membre contient la chaine de caractères stockant le nombre de taches exécutées par le système (format [n]/[m]). */
   char8_t strSdram [ 8 ];                                                                            /*!< Ce membre contient la chaine de caractères stockant le nombre de pages mémoire SDRAM allouées par le système (format [n]/[m]). */
   char8_t strSram [ 8 ];                                                                             /*!< Ce membre contient la chaine de caractères stockant le nombre de pages mémoire SRAM allouées par le système (format [n]/[m]). */
   uint32_t appsNumber;                                                                               /*!< Ce membre contient le nombre d'application allouées en cours d'exécution. */
   uint32_t taskNumber;                                                                               /*!< Ce membre contient le nombre de tâches en cours d'exécution. */
   uint32_t sdramPageNumber;                                                                          /*!< Ce membre contient le nombre de pages de mémoire SDRAM en cours d'exécution. */
   uint32_t sramPageNumber;                                                                           /*!< Ce membre contient le nombre de pages de mémoire SRAM en cours d'exécution. */
   T_mkAddr addr;                                                                                     /*!< Ce membre contient l'adresse du logo placé devant chaque statut. */
   T_mkTextStyle defaultStyle;                                                                        /*!< Ce membre contient le style par défaut des chaines de caractères affichant les statuts. */
   T_mkButtonImage button;                                                                            /*!< Ce membre contient un bouton image. */
};

/**
 * @struct T_mkHomeManagerView
 * @brief Déclaration de la structure T_mkHomeManagerView.
 *
 */

typedef struct T_mkHomeManagerView T_mkHomeManagerView;
struct T_mkHomeManagerView
{
   uint32_t index;                                                                                    /*!< Ce membre contient l'index du bouton applicatif sélectionné. Il évolue entre [0 et K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER[ */
   T_mkContainer* container;                                                                          /*!< Ce membre contient le container de la vue. */
   T_mkScreen background;                                                                             /*!< Ce membre contient la figure d'arrière plan de la vue. */
   T_mkFigure backgroundFigure;                                                                       /*!< Ce membre contient la figure utilisée pour effacer les boutons du manager. */
   T_mkScreen screen;                                                                                 /*!< Ce membre contient la figure du premier plan de la vue. */
   T_mkHomeManagerGraph2D cpuLoad;                                                                    /*!< Ce membre contient les attributs du graphique affichant la charge CPU. */
   T_mkHomeManagerGraph2D frameRate;                                                                  /*!< Ce membre contient les attributs du graphique affichant le framerate. */
   T_mkHomeManagerApplicationList applicationList;                                                    /*!< Ce membre contient les attributs de la barre applicative. */
   T_mkHomeManagerApplicationButton* current;                                                         /*!< Ce membre contient l'adresse du bouton applicatif sélectionné. */
   T_mkHomeManagerStatus status;                                                                      /*!< Ce membre contient les attributs de la zone de statuts. */
};

/**
 *
 */

#endif



