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
* @file mk_qspi_setDummyCycle.c
* @brief Définition de la fonction mk_qspi_setDummyCycle.
* @date 9 août 2024
*
*/

#include "mk_qspi_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_qspi_setDummyCycle ( uint32_t p_mode, uint32_t p_dummyCycles )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un registre de configuration de type volatile */
   T_MicronN25Q512A_ConfigurationRegister l_configurationRegister = { 0 };

   /* Lecture du registre de configuration */
   l_result = mk_qspi_readRegister ( &l_configurationRegister, K_MK_MICRON_N25Q512A_OPCODE_READ_CONFIGURATION, 1, p_mode );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si le nombre de dummyCycle doit être configuré */
      if ( l_configurationRegister.field.dummyClockCycle != p_dummyCycles )
      {
         /* Autorisation d'une écriture */
         l_result = mk_qspi_writeInstruction ( K_MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE, p_mode );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation de la valeur du registre de configuration */
            l_configurationRegister.field.dummyClockCycle = ( uint8_t ) ( p_dummyCycles & 0xF ); ;

            /* Ecriture du registre de configuration */
            l_result = mk_qspi_writeRegister ( &l_configurationRegister, K_MK_MICRON_N25Q512A_OPCODE_WRITE_CONFIGURATION, 1, p_mode );

            /* Si l'opération a réussi */
            if ( l_result == K_MK_OK )
            {
               /* Vérification de la nouvelle valeur du registre */
               /* Si la commande a correctement été exécutée, la lecture doit être réalisée en QUADMODE */
               l_result = mk_qspi_readRegister ( &l_configurationRegister, K_MK_MICRON_N25Q512A_OPCODE_READ_CONFIGURATION, 1, p_mode );

               /* Si le mode 4 fils n'est pas actif */
               if ( l_configurationRegister.field.dummyClockCycle != p_dummyCycles )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_MK_ERROR_COMM;
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
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}
