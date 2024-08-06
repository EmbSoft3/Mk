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
* @file mk_supervisor_recovery.c
* @brief Définition de la fonction mk_supervisor_recovery.
* @date 12 févr. 2023
*
*/

#include "mk_supervisor_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_supervisor_recovery ( T_mkSupervisor* p_supervisor, T_mkSupervisorCode p_code, T_mkTask* p_task, T_mkSupervisorMessage* p_message )
{
   /* Déclaration des variables de travail */
   char8_t l_strCode [ 9 ] = { 0 };

   /* Affichage de la console */
   mk_container_setVisibility ( g_mkDisplay.criticalContainer, K_MK_FIELD_VISIBLE );
   mk_container_setActivity ( g_mkDisplay.criticalContainer, K_MK_FIELD_ACTIF );

   /* Conversion du code d'erreur en chaine de caractères (base 10) */
   ( void ) mk_utils_itoa ( p_code, ( T_str8 ) l_strCode, 10, 0 );
   ( void ) mk_console_log ( &p_supervisor->console, ( T_str8 ) "[Recovery] [Code <" );
   ( void ) mk_console_print ( &p_supervisor->console, ( T_str8 ) l_strCode );
   ( void ) mk_console_print ( &p_supervisor->console, ( T_str8 ) "d>] ;\n" );

   /* Boucle pour toujours */
   for ( ;; )
   {
      /* Attente */
      ( void ) mk_task_sleep ( 2000 );
   }

   /* Suppression warning */
   ( void ) p_message;
   ( void ) p_task;

   /* Retour */
   return;
}
