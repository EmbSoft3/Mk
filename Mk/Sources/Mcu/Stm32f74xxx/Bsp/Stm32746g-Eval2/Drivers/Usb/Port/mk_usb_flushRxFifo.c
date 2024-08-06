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
* @file mk_usb_flushRxFifo.c
* @brief Définition de la fonction mk_usb_flushRxFifo.
* @date 5 oct. 2019
*
*/

#include "mk_usb_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_usb_flushRxFifo ( T_mkAddr p_usb, uint32_t p_timeout )
{
   /* Déclaration d'une variable de travail */
   uint32_t l_status;

   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Réinitialisation du Fifo de réception */
   usb_flushRxFifo ( p_usb );

   /* Récupération du statut du FIFO de réception */
   l_status = usb_getFlushRxStatus ( p_usb );

   /* Tant que l'opération de flush n'est pas terminée et que le timeout n'est pas */
   /* arrivé à échéance */
   while ( ( l_status == K_USB_FLUSH_KO ) && ( p_timeout != 0 ) && ( l_result == K_MK_OK ) )
   {
      /* Attente 2 ms */
      l_result = mk_task_sleep ( 2 );

      /* Récupération du statut du FIFO de réception */
      l_status = usb_getFlushRxStatus ( p_usb );

      /* Actualisation du timeout */
      p_timeout--;
   }

   /* Analyse du résultat de la fonction */
   if ( ( l_result == K_MK_OK ) && ( l_status == K_USB_FLUSH_KO ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_INIT;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}



