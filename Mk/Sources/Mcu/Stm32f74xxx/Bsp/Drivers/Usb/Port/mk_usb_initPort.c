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
* @file mk_usb_initPort.c
* @brief Définition de la fonction mk_usb_initPort.
* @date 10 juin 2019
*
*/

#include "mk_usb_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_usb_initPort ( T_mkAddr p_usb, uint32_t p_resetTick )
{
   /* Note : */
   /* Ne pas modifier les caractéristiques des FIFOs en mode DMA */

   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Configuration de la taille du FIFO de réception */
   usb_setRxFifoSize ( p_usb, K_MK_USB_RXFIFO_SIZE );

   /* Configuration de l'adresse et de la taille du FIFO de transmission de type non périodique. */
   usb_setNonPeriodicTxFifoAddr ( p_usb, K_MK_USB_RXFIFO_SIZE );
   usb_setNonPeriodicTxFifoSize ( p_usb, K_MK_USB_TXFIFO_SIZE );

   /* Configuration de l'adresse et de la taille du FIFO de transmission de type périodique. */
   usb_setPeriodicTxFifoAddr ( p_usb, K_MK_USB_RXFIFO_SIZE + K_MK_USB_TXFIFO_SIZE );
   usb_setPeriodicTxFifoSize ( p_usb, K_MK_USB_TXFIFO_SIZE );

   /* Réinitialisation de l'intégralité des FIFO */
   l_result  = mk_usb_flushTxFifo ( p_usb, K_USB_TXFIFO_ALL, K_MK_USB_FIFO_TIMEOUT );
   l_result |= mk_usb_flushRxFifo ( p_usb, K_MK_USB_FIFO_TIMEOUT );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Reset du port USB */
      l_result = mk_usb_resetPort ( p_usb, p_resetTick );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


