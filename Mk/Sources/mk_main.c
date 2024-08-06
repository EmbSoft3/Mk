/**
*
* @copyright Copyright (C) 2018 RENARD Mathieu. All rights reserved.
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
* @file mk_main.c
* @brief Définition de la fonction principale.
* @date 6 janv. 2018
*
*/

#include "mk_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_initArea ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation des gestionnaires d'allocation dynamique USB_OTGHS et USB_OTGFS */
   l_result = mk_hcd_initArea ( );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_main ( void )
{
   /* Configuration des voyants lumineux */
   gpio_setMode ( K_GPIOF, K_GPIO_OUTPUT, 10 );
   gpio_setHigh ( K_GPIOF, 10 );

   /* Si l'initialisation du système a échoué */
   if (
         /* Initialisation du noyau */
         mk_init ( K_MK_MODE_FLOATING, g_mkProcessStack, K_MK_PROCESS_STACK_SIZE ) ||

         /* Initialisation du gestionnaire DMA */
         mk_dma_initHandler ( ) ||

         /* Initialisation des gestionnaires d'allocation dynamique */
         mk_initArea ( ) ||

         /* Initialisation du module de gestion des fonctions de rappel */
         mk_callback_init ( K_MK_TYPE_FLOATING ) ||

         /* Initialisation de la tâche de repos */
         mk_createIdle ( g_mkIdleStack, K_MK_TASK_IDLE_STACK_SIZE, mk_task_idle, ( T_mkAddr ) 'I' ) ||

         /* Initialisation des gestionnaires mémoire */
         mk_page_initHandler ( ) ||

         /* Initialisation du gestionnaire de programmes et bibliothèques externes */
         mk_loader_init ( ) ||

         /* Initialisation du moteur graphique */
         mk_display_initEngine ( ) ||

         /* Initialisation des terminaux d'entrées-sorties */
         mk_termio_init ( ) ||

         /* Initialisation du superviseur */
         mk_supervisor_initApplication ( ) ||

         /* Lançement du noyau avec un tick de 1ms */
         mk_start ( 27000 ) )
   {
      /* Si l'initialisation du système a échoué, on allume un voyant */
      gpio_setLow ( K_GPIOF, 10 );

      /* On exécute la fonction de de récupération */
      mk_recovery ( 0, 0 );
   }

   /* Boucle pour toujours */
   for ( ;; )
   {
      /* Ne rien faire */
      _nop ();
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_task_idle ( T_mkAddr p_param )
{
   /* Suppression warning */
   ( void ) p_param;

   /* Boucle pour toujours... */
   while ( 1 )
   {
      /* Ne rien faire */
      _nop ( );
   }

   /* Retour */
   return;
}





