/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_utils_rand.c
* @brief Définition de la fonction mk_utils_rand.
* @date 30 mai 2020
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

int32_t mk_utils_rand ( uint32_t* randomNumber )
{
   /* Déclaration de la variable de retour */
   int32_t l_result = 0;

   /* Déclaration d'une variable de travail */
   uint32_t l_status;

   /* Si le paramètre est valide */
   if ( randomNumber != K_MK_NULL )
   {
      /* Lecture du registre de statut du périphérique RNG */
      l_status = rng_getStatus ( K_RNG_SEED_ERROR_CURRENT_STATUS | K_RNG_CLOCK_ERROR_CURRENT_STATUS | K_RNG_READY_STATUS );

      /* Si aucune erreur ne s'est produite et si un nombre aléatoire est disponible */
      if ( l_status == K_RNG_READY_STATUS )
      {
         /* Récupération du nombre aléatoire */
         *randomNumber = rng_get ( );
      }

      /* Sinon si une erreur s'est produite */
      else if ( ( l_status & ( K_RNG_SEED_ERROR_CURRENT_STATUS | K_RNG_CLOCK_ERROR_CURRENT_STATUS ) ) != 0 )
      {
         /* Désactivation du module RNG */
         rng_disable ( );

         /* Attente */
         mk_utils_waitus ( 1 );

         /* Réactivation du module RNG */
         rng_enable ( );

         /* Actualisation de la variable de retour */
         l_result = ( -2 );
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = ( -3 );
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = ( -1 );
   }

   /* Retour */
   return ( l_result );
}



