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
* @file mk_usb_initCore.c
* @brief Définition de la fonction mk_usb_initCore.
* @date 8 juin 2019
* @todo Terminer l'initialisation du mode OTG.
* @todo Modifier cette fonction afin de supporter l'initialisation du mode 'Device'.
*
*/

#include "mk_usb_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_usb_initCore ( T_mkAddr p_usb )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Configuration de la fréquence du PHY */
   usb_setPHYClock ( p_usb, K_USB_PHY_CLOCK_48MHZ );

   /* Réinitialisation du coeur USB */
   l_result = mk_usb_resetCore ( p_usb, K_MK_USB_RESET_TIMEOUT );

   /* Si la réinitialisation du coeur USB a réussi */
   if ( l_result == K_MK_OK )
   {
      /* Si le périphérique HS doit être configuré */
      if ( p_usb == K_USB_OTGHS )
      {
         /* Sélection du PHY ULPI */
         usb_selectPHY ( K_USB_PHY_HIGHSPEED_ULPI );

         /* Réinitialisation du coeur USB */
         l_result = mk_usb_resetCore ( p_usb, K_MK_USB_RESET_TIMEOUT );

         /* Si la réinitialisation du coeur USB a réussi */
         if ( l_result == K_MK_OK )
         {
            /* Configuration du PHY ULPI */
            usb_setULPI ( K_USB_ULPI_EXTERNAL_VBUS_COMPARATOR | K_USB_ULPI_EXTERNAL_SUPPLY |
                          K_USB_ULPI_COMPLEMENT_OUTPUT_NOT_QUALIFIED | K_USB_ULPI_EXTERNAL_CLOCK | K_USB_ULPI_TERMSEL |
                          K_USB_ULPI_CLOCK_POWERDOWN_DISABLED | K_USB_ULPI_AUTORESUME_ENABLED );

            /* Configuration du turnaround time entre l'horloge AHB et */
            /* l'horloge du PHY */
            usb_setTurnaroundTime ( p_usb, K_USB_HS_TRDT_AHB_30_MHZ_MIN );

            /* Activation de la DMA et onfiguration de la taille du burst */
            usb_enableDmaMode ( );
            usb_setBurstLength ( K_USB_BURST_4WORDS );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Activation des protocoles HNP et SRP */
         usb_enableSRPCapability ( p_usb );
         usb_enableHNPCapability ( p_usb );

         /* Autorisation de la modification de la période inter-trame en cours de fonctionnement */
         usb_enableFrameReload ( p_usb );
      }

      /* Sinon */
      else
      {
         /* Configuration du turnaround time entre l'horloge AHB et */
         /* l'horloge du PHY */
         usb_setTurnaroundTime ( p_usb, K_USB_FS_TRDT_AHB_32_MHZ_MIN );

         /* Activation du transcodeur USB */
         usb_enableTransceiver ( p_usb );
      }

      /* Remise à zéro des drapeaux d'interruption OTG */
      usb_clearOTGInterruptFlag ( p_usb, K_USB_OTG_ALL_INTERRUPTS );

      /* Remise à zéro des drapeaux d'interruptions du coeur USB */
      usb_clearCoreInterruptFlag ( p_usb, K_USB_CORE_ALL_INTERRUPTS );

      /* Activation des interruptions */
      usb_unmaskCoreInterrupts ( p_usb, K_USB_DISCONNECT_INTERRUPT |
                                 K_USB_ID_PIN_CHANGE_INTERRUPT | K_USB_START_OF_FRAME_INTERRUPT |
                                 K_USB_MODE_MISMATCH_INTERRUPT );

      /* Activation du drapeau d'interruption global */
      usb_unmaskInterrupts ( p_usb );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


