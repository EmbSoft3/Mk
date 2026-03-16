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
* @file mk_gpio_expander_clear.c
* @brief Définition de la fonction mk_gpio_expander_clear.
* @date 20 déc. 2020
*
*/

#include "mk_gpio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_gpio_expander_clear ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_offset = ( p_pinNumber >> 3 );
   uint32_t l_shift  = ( p_pinNumber ) - ( l_offset << 3 );

   /* Définition du contenu de la trame I2C */
   uint8_t l_registerValue [ 1 ] = {
         ( uint8_t ) ( MK_GPIO_EXPANDER_CLEAR_REGISTER_ADDR + l_offset )
   };

   /* Si le paramètre est valide */
   if ( ( p_handler != K_MK_NULL ) && ( p_handler->device != K_MK_NULL ) )
   {
      /* Lecture du registre de réinitialisation du périphérique MFX */
      l_result = mk_gpio_expander_read ( p_handler, l_registerValue, 1 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Ecriture de la nouvelle valeur dans le registre */
         l_registerValue [ 0 ] &= ( uint8_t ) ( ~ ( 1 << l_shift ) );
         l_registerValue [ 0 ] |= ( uint8_t ) (   ( 1 << l_shift ) );

         /* Actualisation du registre */
         l_result = mk_gpio_expander_write ( p_handler, ( uint8_t ) ( MK_GPIO_EXPANDER_CLEAR_REGISTER_ADDR + l_offset ),
                                             l_registerValue [ 0 ] );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


