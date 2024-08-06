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
* @file mk_hcd_handleStartOfFrameInterrupt.c
* @brief Définition de la fonction mk_hcd_handleStartOfFrameInterrupt.
* @date 29 nov. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_hcd_handleStartOfFrameInterrupt ( T_mkHCDHandler* p_handler )
{
   /* Déclaration d'une variable de travail */
   uint32_t l_channel;

   /* Pour le nombre de canal de communication */
   for ( l_channel = K_USB_CHANNEL0 ; l_channel <= K_USB_CHANNEL15 ; l_channel++ )
   {
      /* Si un token NYET ou NAK a été temporisé */
      if ( p_handler->sofTable [ l_channel ] != 0 )
      {
         /* Décrémentation du compteur */
         p_handler->sofTable [ l_channel ] = ( uint8_t ) ( p_handler->sofTable [ l_channel ] - 1 );

         /* Si un token doit être envoyé sur le bus */
         if ( p_handler->sofTable [ l_channel ] == 0 )
         {
            /* Réactivation du canal */
            usb_enableChannel ( p_handler->bus, l_channel );
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

   /* Réinitialisation du drapeau d'interruption */
   usb_clearCoreInterruptFlag ( p_handler->bus, K_USB_START_OF_FRAME_INTERRUPT );

   /* Retour */
   return;
}
