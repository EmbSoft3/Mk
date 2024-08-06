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
* @file mk_shell.c
* @brief Définition de la fonction mk_shell_handler.
* @date 9 mai 2023
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_shell ( T_mkAddr p_unused )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un gestionnaire de commandes */
   T_mkShell l_shell;

   /* Déclaration d'un message */
   T_mkShellMessage l_message;

   /* Initialisation du gestionnaire de commandes */
   l_result = mk_shell_init ( &l_shell );

   /* Boucle pour toujours */
   while ( 1 )
   {
      /* Analyse de la boite de messages pour savoir si une nouvelle commande est disponible */
      l_result = mk_mail_pend ( K_MK_NULL, g_mkShellMessageArea.mail, ( T_mkAddr ) &l_message, K_MK_TASK_WAIT_FOREVER );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Analyse et exécution de la commande */
         l_result = mk_shell_handle ( &l_shell, &l_message );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Supression warning */
   ( void ) p_unused;

   /* Retour */
   return;
}


