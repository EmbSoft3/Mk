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
* @file mk_system_setting_init.c
* @brief Définition de la fonction mk_system_setting_init.
* @date 26 févr. 2019
*
*/

#include "mk_system_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_sysCode mk_system_setting_init ( void )
{
   /* Déclaration de la valeur de retour */
   T_sysCode l_result = K_SYS_ERROR_CELL_COMPENSATION;

   /* Déclaration d'une variable de statut */
   uint32_t l_status;

   /* Déclaration d'un compteur */
   uint32_t l_counter;

   /* Configuration des interruptions externes */
   for ( l_counter = 0 ; l_counter < K_EXTI_LINE_NUMBER ; l_counter++ )
   {
      /* Configuration la ligne courante */
      exti_disableInterrupt ( l_counter );
      exti_disableEvent ( l_counter );
      exti_disableRisingEdge ( l_counter );
      exti_disableFallingEdge ( l_counter );

      /* Réinitialisation du drapeau d'interruption */
      exti_clearRequest ( l_counter );
   }

   /* Activation de la permutation de 'bank' */
   syscfg_swapBank ( K_SYSCFG_BANK_SWAP_DISABLE );

   /* Activation de la compensation de cellule pour les broches */
   /* hautes vélocités */
   l_status = syscfg_cellCompensation ( K_SYSCFG_COMPENSATION_ENABLE, K_SYSCFG_COMPENSATION_TIMEOUT );

   /* Analyse du résultat */
   if ( l_status == K_SYSCFG_COMPENSATION_ENABLED )
   {
      /* Actualisation de la variable de retour */
      l_result = K_SYS_OK;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


