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
* @file mk_supervisor_svcFault.c
* @brief Définition de la fonction mk_supervisor_svcFault.
* @date 4 avr. 2023
*
*/

#include "mk_supervisor_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_supervisor_svcFault ( T_mkAddr p_mkCode, T_mkAddr p_mkObject, T_mkAddr p_mkStatus )
{
   /* Déclaration d'un message */
   K_MK_PRIVILEGED_STATIC_MEMORY T_mkSupervisorMessage l_message = { 0 };

   /* Récupération du statut d'interruption */
   l_message.svc.isr = ( uint32_t ) p_mkStatus;

   /* Récupération de l'identifiant de l'erreur */
   l_message.svc.fault = ( T_mkSVCError ) p_mkCode;

   /* Récupération de la valeur du gestionnaire SVC */
   _copy ( ( T_mkAddr ) &l_message.svc.object, ( T_mkAddr ) p_mkObject, sizeof ( T_mkSVCObject ) );

   /* Transmission d'un message au superviseur afin qu'il édite un rapport d'erreur. */
   ( void ) mk_supervisor_post ( K_MK_SUPERVISOR_SVCFAULT, &l_message );

   /* Retour */
   return;
}
