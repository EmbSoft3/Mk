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
* @file mk_peripheral_dma_getTransferHalfInterruptFlag.c
* @brief Définition de la fonction dma_getTransferHalfInterruptFlag.
* @date 27 oct. 2018
*
*/

#include "mk_peripheral_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t dma_getTransferHalfInterruptFlag ( void_t p_addr, uint32_t p_stream )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Si le drapeau d'interruption du flux numéro 0 doit être renvoyé */
   if ( p_stream == K_DMA_STREAM0 )
   {
      /* Récupération de la valeur du drapeau d'interruption */
      l_result = _getField ( ( addr_t ) p_addr, 1, 4 );
   }

   /* Sinon si le drapeau d'interruption du flux numéro 1 doit être renvoyé */
   else if ( p_stream == K_DMA_STREAM1 )
   {
      /* Récupération de la valeur du drapeau d'interruption */
      l_result = _getField ( ( addr_t ) p_addr, 1, 10 );
   }

   /* Sinon si le drapeau d'interruption du flux numéro 2 doit être renvoyé */
   else if ( p_stream == K_DMA_STREAM2 )
   {
      /* Récupération de la valeur du drapeau d'interruption */
      l_result = _getField ( ( addr_t ) p_addr, 1, 20 );
   }

   /* Sinon si le drapeau d'interruption du flux numéro 3 doit être renvoyé */
   else if ( p_stream == K_DMA_STREAM3 )
   {
      /* Récupération de la valeur du drapeau d'interruption */
      l_result = _getField ( ( addr_t ) p_addr, 1, 26 );
   }

   /* Sinon si le drapeau d'interruption du flux numéro 4 doit être renvoyé */
   else if ( p_stream == K_DMA_STREAM4 )
   {
      /* Récupération de la valeur du drapeau d'interruption */
      l_result = _getField ( ( addr_t ) p_addr + 1, 1, 4 );
   }

   /* Sinon si le drapeau d'interruption du flux numéro 5 doit être renvoyé */
   else if ( p_stream == K_DMA_STREAM5 )
   {
      /* Récupération de la valeur du drapeau d'interruption */
      l_result = _getField ( ( addr_t ) p_addr + 1, 1, 10 );
   }

   /* Sinon si le drapeau d'interruption du flux numéro 6 doit être renvoyé */
   else if ( p_stream == K_DMA_STREAM6 )
   {
      /* Récupération de la valeur du drapeau d'interruption */
      l_result = _getField ( ( addr_t ) p_addr + 1, 1, 20 );
   }

   /* Sinon si le drapeau d'interruption du flux numéro 7 doit être renvoyé */
   else if ( p_stream == K_DMA_STREAM7 )
   {
      /* Récupération de la valeur du drapeau d'interruption */
      l_result = _getField ( ( addr_t ) p_addr + 1, 1, 26 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}



