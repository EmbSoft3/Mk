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
* @file mk_hid_readMultipleUsage.c
* @brief Définition de la fonction mk_hid_readMultipleUsage.
* @date 17 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_selectFirstAddress ( T_mkHIDUsageParser* p_parser, T_mkHIDUsage* p_usage )
{
   /* Si une adresse a été attribuée à l'usage */
   if ( p_usage->first->addr != K_MK_NULL )
   {
      /* Configuration de l'adresse de routage (elle est située sur le second mot de la structure) */
      p_parser->usageBuf = ( ( uint32_t* ) p_usage->first->addr ) + 1;
   }

   /* Sinon */
   else
   {
      /* Configuration de l'adresse de routage */
      p_parser->usageBuf = K_MK_NULL;
   }


   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_selectNextAddress ( T_mkHIDUsageParser* p_parser )
{
   /* Si une adresse a été assignée à l'usage */
   if ( p_parser->usageBuf != K_MK_NULL )
   {
      /* Configuration de la prochaine adresse */
      p_parser->usageBuf = ( uint32_t* ) ( * ( p_parser->usageBuf - 1 ) );

      /* Configuration de l'adresse de routage (elle est située sur le second mot de la structure) */
      p_parser->usageBuf = p_parser->usageBuf + 1;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_readMultipleUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_usageCounter;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_parser != K_MK_NULL ) && ( p_table != K_MK_NULL ) && ( p_usage != K_MK_NULL ) )
   {
      /* Configuration de l'adresse initiale */
      mk_hid_selectFirstAddress ( p_parser, p_usage );

      /* Pour l'ensemble des usages à récupérer */
      for ( l_usageCounter = 0 ; l_usageCounter < p_table->global.reportCount; l_usageCounter++ )
      {
         /* Configuration de la taille de l'usage */
         p_parser->usageSize = p_table->global.reportSize;

         /* Récupération de la valeur de l'usage */
         l_result = mk_hid_getUsageValue ( p_hidDevice, p_pipe, p_parser, p_table, p_usage->first->head.field.destinationSize );

         /* Dans le cas où l'entrée n'est pas tableau, l'adresse du prochain élément est indiquée par le pointeur next */
         /* contenu dans la première adresse de la structure précédente. */
         mk_hid_selectNextAddress ( p_parser );
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
