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
* @file mk_shell_init.c
* @brief Définition de la fonction mk_shell_init.
* @date 13 mai 2023
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_shell_initVariables ( T_mkShell* p_shell )
{
   /* Initialisation du buffer contenant le chemin du répertoire courant */
   _writeBytes ( &p_shell->currentDirectory, 0, K_MK_FILE_MAX_NAME_LENGTH + 1 );
   _copy ( &p_shell->currentDirectory, ( T_str8 ) K_MK_SHELL_EXTERNAL_COMMAND_PATH, 20 );

   /* Initialisation de la variable d'état */
   p_shell->reg.cmdInProgress = K_MK_SHELL_CMD_END;
   p_shell->reg.callback = K_MK_NULL;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shell_allocPage ( T_mkShell* p_shell )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Allocation d'une page mémoire */
   l_result = mk_page_alloc ( K_MK_PAGE_ID_SRAM, &p_shell->page.baseAddr, 0 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration des pointeurs mémoires */
      /* Attention à la taille de la page mémoire */
      p_shell->page.bufferAddr = ( uint8_t* ) p_shell->page.baseAddr;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_shell_init ( T_mkShell* p_shell )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation des variables */
   mk_shell_initVariables ( p_shell );

   /* Allocation d'une page mémoire */
   l_result = mk_shell_allocPage ( p_shell );

   /* Retour */
   return ( l_result );
}


