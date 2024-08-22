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
* @file mk_chromart_clear.c
* @brief Définition de la fonction mk_chromart_clear.
* @date 20 août 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_chromart_clear ( uint32_t* p_buf )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Configuration du canal DMA2D */
   dma2d_setMode ( K_DMA2D_REGISTER_TO_MEMORY );
   dma2d_setAddr ( K_DMA2D_MEM_OUTPUT, ( uint32_t ) p_buf );
   dma2d_setOffset ( K_DMA2D_MEM_OUTPUT, 0 );

   /* Configuration des caractéristique de la figure */
   dma2d_setColor ( K_DMA2D_PFC_OUTPUT, 0 );
   dma2d_setFormat ( K_DMA2D_PFC_OUTPUT, K_DMA2D_FORMAT_ARGB8888 );
   dma2d_setRectangle ( ( uint32_t ) g_mkDisplay.screen.width, ( uint32_t ) ( uint32_t ) g_mkDisplay.screen.height );

   /* Configuration de la bande passante du transfert */
   dma2d_setTimer ( K_MK_DISPLAY_DMA2D_FILL_BANDWIDTH );

   /* Déclenchement du transfert DMA2D */
   dma2d_start ( );

   /* Attendre jusqu'à la fin du transfert */
   l_result = mk_chromart_wait ( );

   /* Retour */
   return ( l_result );
}


