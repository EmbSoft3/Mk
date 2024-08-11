/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_qspi_getMode.c
* @brief Définition de la fonction mk_qspi_getMode.
* @date 9 août 2024
*
*/

#include "mk_qspi_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_qspi_getMode ( uint32_t* p_mode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint8_t l_id = 0;

   /* La mémoire QSPI possède un registre de type non volatile définissant le mode de fonctionnement au démarrage de la mémoire. */
   /* Le but de cette fonction est de déterminer la valeur du mode initial (SINGLE, DUAL, QUAD). */
   /* Pour ce faire, on récupére l'identifiant fabricant de la mémoire et on le compare à une valeur prédéfinie. */

   /* Initialisation de la variable de retour */
   *p_mode = K_MK_QSPI_MODE_SINGLE;

   /* Lecture de l'identifiant fabricant en mode 'SINGLE' */
   l_result = mk_qspi_readRegister ( &l_id, K_MK_MICRON_N25Q512A_OPCODE_READ_ID, 1, K_MK_QSPI_MODE_SINGLE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si le mode 'SINGLE' n'est pas le mode recherché */
      if ( l_id != K_MK_MICRON_N25Q512A_MANUFACTURER_ID )
      {
         /* Initialisation de la variable de retour */
         *p_mode = K_MK_QSPI_MODE_DUAL;

         /* Lecture de l'identifiant fabricant en mode 'DUAL' */
         l_result = mk_qspi_readRegister ( &l_id, K_MK_MICRON_N25Q512A_OPCODE_READ_ID, 1, K_MK_QSPI_MODE_DUAL );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Si le mode 'DUAL' n'est pas le mode recherché */
            if ( l_id != K_MK_MICRON_N25Q512A_MANUFACTURER_ID )
            {
               /* Initialisation de la variable de retour */
               *p_mode = K_MK_QSPI_MODE_QUAD;

               /* Lecture de l'identifiant fabricant en mode 'QUAD' */
               l_result = mk_qspi_readRegister ( &l_id, K_MK_MICRON_N25Q512A_OPCODE_READ_ID, 1, K_MK_QSPI_MODE_QUAD );

               /* Si le mode 'QUAD' n'est pas le mode recherché */
               if ( l_id != K_MK_MICRON_N25Q512A_MANUFACTURER_ID )
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


