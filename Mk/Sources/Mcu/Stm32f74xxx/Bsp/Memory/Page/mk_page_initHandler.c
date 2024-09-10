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
* @file mk_page_initHandler.c
* @brief Définition de la fonction mk_page_initHandler.
* @date 10 avr. 2023
*
*/

#include "mk_memory_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_page_initSDRAMHandler ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Initialisation de la zone mémoire dédiée au gestionnaire d'allocation dynamique */
   l_result = mk_pool_initArea ( &g_mkSDRAMHandler.area, ( uint32_t* ) K_MK_PAGE_SDRAM_START_ADDR, K_MK_PAGE_SDRAM_SIZE >> 2 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire mémoire */
      l_result = mk_pool_create ( &g_mkSDRAMHandler.area, &g_mkSDRAMHandler.pool, K_MK_AREA_PROTECTED, K_MK_PAGE_SDRAM_BLOCK_SIZE >> 2, K_MK_PAGE_SDRAM_SIZE / K_MK_PAGE_SDRAM_BLOCK_SIZE );
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

static T_mkCode mk_page_initSmallHandler ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de page */
   T_mkAddr l_page;

   /* Allocation d'une page mémoire */
   l_result = mk_page_alloc ( K_MK_PAGE_ID_SDRAM, &l_page, 0 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la zone mémoire dédiée au gestionnaire d'allocation dynamique */
      l_result = mk_pool_initArea ( &g_mkSmallHandler.area, ( uint32_t* ) l_page, K_MK_PAGE_SDRAM_BLOCK_SIZE >> 2 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation du gestionnaire mémoire */
         l_result = mk_pool_create ( &g_mkSmallHandler.area, &g_mkSmallHandler.pool, K_MK_AREA_PROTECTED, K_MK_PAGE_SDRAM_SMALL_BLOCK_SIZE >> 2, K_MK_PAGE_SDRAM_BLOCK_SIZE / K_MK_PAGE_SDRAM_SMALL_BLOCK_SIZE );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_page_initHandler ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation du gestionnaire d'allocation de la mémoire SDRAM */
   l_result = mk_page_initSDRAMHandler ( );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation de la mémoire réduite */
      l_result = mk_page_initSmallHandler ( );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


