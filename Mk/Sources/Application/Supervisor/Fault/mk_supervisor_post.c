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
* @file mk_supervisor_post.c
* @brief Définition de la fonction mk_supervisor_post.
* @date 4 avr. 2023
*
*/

#include "mk_supervisor_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_supervisor_post ( T_mkSupervisorFault p_fault, T_mkSupervisorMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement du type de l'erreur */
   p_message->fault = p_fault;

   /* Enregistrement de l'adresse de la tâche courante */
   p_message->task = g_mkScheduler.currentTask;

   /* Récupération de la valeur des registres du CPU */
   _mk_supervisor_dump ( &p_message->dump );

   /* Récupération des registres du scheduler */
   _copy ( ( T_mkAddr ) &p_message->scheduler, ( T_mkAddr ) &g_mkScheduler, sizeof ( T_mkScheduler ) );

   /* Transmission d'un message au supervisor */
   l_result = mk_mail_post ( g_mkSupervisor.message.mail, p_message, K_MK_STATE_READY, 0 );

   /* Retour */
   return ( l_result );
}

