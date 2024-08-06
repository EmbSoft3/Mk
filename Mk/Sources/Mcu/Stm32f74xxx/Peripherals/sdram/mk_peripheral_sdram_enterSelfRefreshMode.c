/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_peripheral_sdram_enterSelfRefreshMode.c
* @brief Déclarationn de la fonction sdram_enterSelfRefreshMode.
* @date 24 févr. 2019
*
*/

#include "mk_peripheral_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t sdram_enterSelfRefreshMode ( uint32_t p_bank )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = K_SDRAM_BUSY;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Ecriture du registre FMC_SDCMR */
   _writeWord ( K_SDRAM_SDCMR, ( p_bank | 0x05 ) );

   /* Tant que la commande n'est pas transmise ou que l'échéance du timeout n'est */
   /* pas atteinte */
   while ( ( l_result == K_SDRAM_BUSY ) && ( l_counter < K_SDRAM_TIMEOUT ) )
   {
      /* Lecture du registre FMC_SDSR */
      l_result = _getField ( ( addr_t ) K_SDRAM_SDSR, 1, 5 );

      /* Actualisation du compteur */
      l_counter++;
   }

   /* Retour */
   return ( l_result );
}


