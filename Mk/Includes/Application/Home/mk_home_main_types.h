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
* @file mk_home_main_types.h
* @brief Déclaration des types dédiés à la vue principale de l'application home.
* @date 10 déc. 2023
*
*/

#ifndef MK_HOME_MAIN_TYPES_H
#define MK_HOME_MAIN_TYPES_H

/**
 * @struct T_mkHomeMainApplicationButton
 * @brief Déclaration de la structure T_mkHomeMainApplicationButton.
 *
 */

typedef struct T_mkHomeMainApplicationButton T_mkHomeMainApplicationButton;
struct T_mkHomeMainApplicationButton
{
   T_mkTextStyle* nameStyle;                                                                 /*!< Ce membre contient l'adresse du style d'un bouton applicatif. */
   T_mkApplication* application;                                                             /*!< Ce membre contient l'adresse d'une application. */
   T_mkButtonImage button;                                                                   /*!< Ce membre contient un bouton image. */
};

/**
 * @struct T_mkHomeMainApplicationList
 * @brief Déclaration de la structure T_mkHomeMainApplicationList.
 *
 */

typedef struct T_mkHomeMainApplicationList T_mkHomeMainApplicationList;
struct T_mkHomeMainApplicationList
{
   uint32_t appIndex;                                                                        /*!< Ce membre contient l'index du bouton applicatif sélectionné. Il évolue entre [0 et K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_NUMBER[ */
   uint32_t shiftIndex;                                                                      /*!< Ce membre contient l'index de la première application affichée dans la barre applicative. */
   T_mkFont font;                                                                            /*!< Ce membre contient la police de caractères des boutons applicatifs. */
   T_mkFontPage page;                                                                        /*!< Ce membre contient la page de caractères des boutons applicatifs. */
   T_mkTextStyle nameStyle;                                                                  /*!< Ce membre contient le style des boutons applicatifs. */
   T_mkTextStyle focusStyle;                                                                 /*!< Ce membre contient le style du bouton applicatif sélectionné par l'utilisateur. */
   T_mkHomeMainApplicationButton app [ K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_NUMBER ];   /*!< Ce membre contient les boutons de la barre applicative. */
};

/**
 * @struct T_mkHomeMainView
 * @brief Déclaration de la structure T_mkHomeMainView.
 *
 */

typedef struct T_mkHomeMainView T_mkHomeMainView;
struct T_mkHomeMainView
{
   T_mkContainer* container;                                                                 /*!< Ce membre contient le container de la vue principale. */
   T_mkScreen screen;                                                                        /*!< Ce membre contient l'écran de la vue principale. */
   T_mkButtonImage background;                                                               /*!< Ce membre contient l'arrière plan de la vue principale. */
   T_mkHomeMainApplicationList applicationList;                                              /*!< Ce membre contient les attributs de la barre applicative. */
};

/**
 *
 */

#endif


