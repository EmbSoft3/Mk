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
* @file mk_home_main.c
* @brief Définition de la fonction mk_home_main.
* @date 5 mai 2019
*
*/

#include "mk_home_api.h"
/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_handleCPULoad ( T_mkHomeApplication* p_home )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_idleLoad = 0;

   /* Récupération de la charge CPU */
   l_result =  mk_task_getLoad ( mk_scheduler_getIdleTask ( ), &l_idleLoad );

   /* Actualisation des données du graphique */
   mk_graph2D_addFirstInt32 ( &p_home->view.manager.cpuLoad.graph, ( int32_t ) ( 100 - l_idleLoad ), 0, 100 );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_home_handleFrameRate ( T_mkHomeApplication* p_home )
{
   /* Déclaration d'une variable de travail */
   uint32_t l_frameRate = 0;

   /* Récupération de la charge CPU */
   l_frameRate = mk_display_getFramerate ( );

   /* Actualisation des données du graphique */
   mk_graph2D_addFirstInt32 ( &p_home->view.manager.frameRate.graph, ( int32_t ) l_frameRate, 0, 60 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_home_main ( T_mkAddr p_param )
{
   /* Déclaration d'une structure contenant les métadonnées de l'application */
   /* Cette tâche est persistante, on peut donc déclarer la structure dans la stack. */
   T_mkApplicationMetadata l_homeMetadata = {
         ( T_str8 ) "Home",
         ( T_str8 ) "MkSoft",
         ( T_str8 ) "1.0.0",
         ( T_str8 ) "Le gestionnaire d'application du système.",
         ( T_str8 ) "mk/apps/home/mk_application.bmp",
         K_MK_NULL
   };

   /* L'application home est statique. */
   /* On peut récupérer son adresse directement dans le paramètre de la tâche. */

   /* Récupération de l'adresse de l'application 'Home' */
   T_mkHomeApplication* l_home = ( T_mkHomeApplication* ) p_param;

   /* Configuration des métadonnées de l'application */
   T_mkCode l_result = mk_application_setMetadata ( ( T_mkApplication* ) l_home->application, &l_homeMetadata, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de l'application */
      l_result = mk_home_init ( ( T_mkHomeApplication* ) p_param );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Boucle pour toujours */
         while ( 1 )
         {
            /* Détermination du framerate et de la charge CPU pour le manager */
            mk_home_handleFrameRate ( l_home );
            mk_home_handleCPULoad ( l_home );

            /* Attente */
            mk_task_sleep ( 100 );
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Le résultat de la fonction n'est pas vérifié car l'intégrité du système n'est plus garantie. */
   /* Une erreur grave vient de se produire */
   /* La destruction de l'application est de la responsabilité du superviseur. */
   ( void ) mk_display_report ( l_result );

   /* Blocage */
   while ( 1 );

   /* Retour */
   return;
}



