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
* @file mk_i2c_getHandle.c
* @brief Définition de la fonction mk_i2c_getHandle.
* @date 15 nov. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkTermio* mk_i2c_getTermioHandler ( uint32_t p_peripheralIdentifier )
{
   /* Déclaration d'un pointeur de terminal */
   T_mkTermio* l_termio = K_MK_NULL;

   /* Si le gestionnaire I2C1 doit être récupéré */
   if ( p_peripheralIdentifier == K_MK_I2C1 )
   {
      /* Actualisation de l'adresse du terminal */
      l_termio = g_mkTermioHandler.i2c1;
   }

   /* Sinon si le gestionnaire I2C2 doit être récupéré */
   else if ( p_peripheralIdentifier == K_MK_I2C2 )
   {
      /* Actualisation de l'adresse du terminal */
      l_termio = g_mkTermioHandler.i2c2;
   }

   /* Sinon si le gestionnaire I2C3 doit être récupéré */
   else if ( p_peripheralIdentifier == K_MK_I2C3 )
   {
      /* Actualisation de l'adresse du terminal */
      l_termio = g_mkTermioHandler.i2c3;
   }

   /* Sinon si le gestionnaire I2C4 doit être récupéré */
   else if ( p_peripheralIdentifier == K_MK_I2C4 )
   {
      /* Actualisation de l'adresse du terminal */
      l_termio = g_mkTermioHandler.i2c4;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_termio );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_i2c_getHandler ( T_mkI2CHandler** p_handler, uint32_t p_peripheralIdentifier )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de terminal */
   T_mkTermio* l_termio = K_MK_NULL;

   /* Si les paramètres sont valides */
   if ( p_handler != K_MK_NULL )
   {
      /* Récupération de l'adresse du terminal */
      l_termio = mk_i2c_getTermioHandler ( p_peripheralIdentifier );

      /* Si le terminal est valide */
      if ( l_termio != K_MK_NULL )
      {
         /* Récupération de l'adresse du gestionnaire */
         l_result = mk_termio_getChild ( l_termio, ( T_mkAddr* ) p_handler );
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


