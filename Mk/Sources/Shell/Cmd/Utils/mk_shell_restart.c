/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_shell_restart.c
* @brief Définition de la fonction mk_shell_restart.
* @date 3 août 2024
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_shell_restart ( T_mkShell* p_shell, T_mkConsole* p_console, T_mkAddr p_addr, T_str8 p_str, uint32_t p_cmdLength )
{
   /* Prototype de la commande */
   /* restart */

   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si la première phase de la commande doit être réalisée */
   if ( p_addr == K_MK_NULL )
   {
      /* Cette commande est en deux phases */
      p_shell->reg.cmdInProgress = K_MK_SHELL_CMD_IN_PROGRESS;
      p_shell->reg.callback = mk_shell_restart;
      p_shell->reg.addr = K_MK_NOT_NULL;

      /* Demande de confirmation */
      l_result = mk_console_print ( p_console, ( T_str8 ) "Confirm restart (y/n) ?\r\n\r\n" );
   }

   /* Sinon, deuxième phase */
   else
   {
      /* Fin de la commande */
      p_shell->reg.cmdInProgress = K_MK_SHELL_CMD_END;

      /* Si le reset doit être lancé */
      if ( p_str [ 0 ] == ( char8_t ) 'y' )
      {
         /* Reset du système */
         cortex_resetSystem ( );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Suppression warning */
   ( void ) p_cmdLength;

   /* Retour */
   return ( l_result );
}


