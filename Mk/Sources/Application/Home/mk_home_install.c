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
* @file mk_home_install.c
* @brief Définition de la fonction mk_home_install.
* @date 8 oct. 2023
*
* @todo Implémenter l'installation des applications dans un fichier d'initialisation (.ini).
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_createPong ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application;

   /* Récupération de l'adresse de la partition système */
   T_mkVolume* l_volume = mk_supervisor_getVolume ( );

   /* Installation de l'application Pong */
   l_result = mk_application_installDynamic ( &l_application, ( T_str8 ) "mk/apps/pong/pongGameRelease.elf",
                                              K_MK_NULL, l_volume, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_createShell ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application;

   /* Récupération de l'adresse de la partition système */
   T_mkVolume* l_volume = mk_supervisor_getVolume ( );

   /* Installation de l'application Pong */
   l_result = mk_application_installDynamic ( &l_application, ( T_str8 ) "mk/apps/shell/shellRelease.elf",
                                              K_MK_NULL, l_volume, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_createBlinkLed ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application;

   /* Récupération de l'adresse de la partition système */
   T_mkVolume* l_volume = mk_supervisor_getVolume ( );

   /* Installation de l'application BlinkLed */
   l_result = mk_application_installDynamic ( &l_application, ( T_str8 ) "mk/apps/blinkLed/blinkLedRelease.elf",
                                              ( T_mkAddr ) "1000", l_volume, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_home_install ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Installation des applications dynamiques */
   l_result  = mk_home_createPong ( );
   l_result |= mk_home_createShell ( );
   l_result |= mk_home_createBlinkLed ( );

   /* Retour */
   return ( l_result );
}
