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
* @file mk_hid_writeUsage.c
* @brief Définition de la fonction mk_hid_writeUsage.
* @date 6 janv. 2020
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_writeUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_parser != K_MK_NULL ) && ( p_table != K_MK_NULL ) && ( p_usage != K_MK_NULL ) )
   {
      /* Récupération de l'adresse associée à l'uage */
      p_parser->usageBuf = ( ( uint32_t* ) p_usage->first->addr ) + 1;

      /* Si l'item courant est un 'ReportID' */
      if ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_REPORT_ID )
      {
         /* Le 'Report ID' a une taille fixe de 8 bits */
         p_parser->usageSize = 8;
      }

      /* Sinon */
      else
      {
         /* Configuration de la taille de l'usage */
         p_parser->usageSize = p_table->global.reportSize;
      }

      /* Si l'entrée est de type constant */
      if ( (  p_usage->first->head.field.tag != K_MK_HID_ITEM_TAG_REPORT_ID ) && ( p_usage->first->head.field.tag != K_MK_HID_ITEM_TAG_USAGE ) )
      {
         /* Configuration de l'adresse de routage */
         p_parser->usageBuf = K_MK_NULL;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si l'usage ne doit pas être ignoré */
      if ( p_usage->first->addr != K_MK_INVALID_HANDLE )
      {
         /* Récupération de la valeur de l'usage */
         l_result = mk_hid_setUsageValue ( p_hidDevice, p_pipe, p_parser, p_table );
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



