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
* @file mk_msc_post.c
* @brief Définition de la fonction mk_msc_post.
* @date 18 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_sendResetRequest ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Transmission d'une requête de réinitialisation */
   l_result = mk_msc_reset ( p_mscDevice, p_pipe );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_TIMEOUT ) )
   {
      /* Reconfiguration des tokens des pipes */
      p_mscDevice->inEndpoint->bToken = K_USB_PID_DATA0;
      p_mscDevice->outEndpoint->bToken = K_USB_PID_DATA0;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_recover ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Transfert d'une requête de réinitialisation */
   l_result = mk_msc_sendResetRequest ( p_mscDevice, p_pipe );

   /* Réinitialisation de la terminaison de type 'IN' */
   l_result |= mk_msc_clearHaltFeature ( p_mscDevice, p_pipe, p_mscDevice->inEndpoint );

   /* Réinitialisation de la terminaison de type 'OUT' */
   l_result |= mk_msc_clearHaltFeature ( p_mscDevice, p_pipe, p_mscDevice->outEndpoint );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_checkCmdStatusWrapper ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe, T_mkMSCCommandStatusWrapper* p_csw, T_mkMSCCommandBlockWrapper* p_cbw )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le statut est valide */
   if ( ( p_csw->dCSWSignature == K_MK_MSC_CMD_STATUS_WRAPPER_SIGNATURE ) &&
        ( p_csw->dCSWTag == p_cbw->dCBWTag ) )
   {
      /* Actualisation du statut du périphérique */
      p_mscDevice->status = p_csw->bCSWStatus;

      /* Si la commande a réussi */
      if ( p_mscDevice->status == K_MK_MSC_DEVICE_STATUS_CMD_PASSED )
      {
         /* Si une erreur d'interprétation s'est produite */
         if ( p_csw->dCSWDataResidue != 0 )
         {
            /* Actualisation du status du périphérique */
            p_mscDevice->status = K_MK_MSC_DEVICE_STATUS_REQUEST_NOT_COMPLETED;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si une erreur de type 'Phase Error' est présente */
      else if ( p_mscDevice->status == K_MK_MSC_DEVICE_STATUS_PHASE_ERROR )
      {
         /* Une requête de réinitialisation doit être transmise au périphérique */
         l_result = mk_msc_recover ( p_mscDevice, p_pipe );
      }

      /* Sinon */
      else
      {
         /* Actualisation du status du périphérique */
         p_mscDevice->status = K_MK_MSC_DEVICE_STATUS_CMD_FAILED;
      }
   }

   /* Sinon */
   else
   {
      /* Une requête de réinitialisation doit être transmise au périphérique */
      l_result = mk_msc_recover ( p_mscDevice, p_pipe );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_getCmdStatusWrapper ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe, T_mkMSCCommandBlockWrapper* p_cbw, T_mkMSCCommandStatusWrapper* p_csw )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Actualisation de la réponse */
   p_mscDevice->status = K_MK_MSC_DEVICE_STATUS_CMD_FAILED;

   /* Récupération du 'CommandStatusWrapper' */
   l_result = mk_hcd_sendPipe ( p_mscDevice->device, p_mscDevice->inEndpoint, &p_mscDevice->inPipe,
                              ( uint8_t* ) p_csw, K_MK_HCD_ENDPOINT_IN | K_MK_HCD_PID_TOOGLE, K_MK_MSC_CMD_STATUS_WRAPPER_SIZE );

   /* Si le périphérique a émis un STALL */
   if ( ( l_result == K_MK_ERROR_COMM ) || ( l_result == K_MK_ERROR_TIMEOUT ) || ( ( p_mscDevice->inPipe.status & K_MK_HCD_ERROR_STALL ) == K_MK_HCD_ERROR_STALL ) )
   {
      /* Réinitialisation de la terminaison de type 'IN' */
      l_result = mk_msc_clearHaltFeature ( p_mscDevice, p_pipe, p_mscDevice->inEndpoint );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Nouvelle tentative de récupération du 'CommandStatusWrapper' */
         l_result = mk_hcd_sendPipe ( p_mscDevice->device, p_mscDevice->inEndpoint, &p_mscDevice->inPipe,
                                    ( uint8_t* ) p_csw, K_MK_HCD_ENDPOINT_IN | K_MK_HCD_PID_TOOGLE, K_MK_MSC_CMD_STATUS_WRAPPER_SIZE );

         /* Si le périphérique a de nouveau émis un STALL */
         if ( ( l_result == K_MK_ERROR_COMM ) || ( l_result == K_MK_ERROR_TIMEOUT ) || ( ( p_mscDevice->inPipe.status & K_MK_HCD_ERROR_STALL ) == K_MK_HCD_ERROR_STALL ) )
         {
            /* Une requête de réinitialisation doit être transmise au périphérique */
            l_result |= mk_msc_recover ( p_mscDevice, p_pipe );
         }

         /* Sinon */
         else
         {
            /* Vérification du statut retourné par le périphérique */
            l_result |= mk_msc_checkCmdStatusWrapper ( p_mscDevice, p_pipe, p_csw, p_cbw );
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
      /* Vérification du statut retourné par le périphérique */
      l_result |= mk_msc_checkCmdStatusWrapper ( p_mscDevice, p_pipe, p_csw, p_cbw );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_post ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe, T_mkMSCCommandBlockWrapper* p_cbw, T_mkMSCCommandStatusWrapper* p_csw, T_mkAddr p_buf )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_mscDevice != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_cbw != K_MK_NULL ) && ( p_csw != K_MK_NULL )&& ( p_buf != K_MK_NULL ) )
   {
      /* Transmission de la requête */
      l_result = mk_hcd_sendPipe ( p_mscDevice->device, p_mscDevice->outEndpoint, &p_mscDevice->outPipe,
                                 ( uint8_t* ) p_cbw, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_TOOGLE, K_MK_MSC_CMD_BLOC_WRAPPER_SIZE );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si des données sont associées à la commande */
         if ( p_cbw->dCBWDataTransferLength != 0 )
         {
            /* Si la direction du transfert est de type 'Host To Device' */
            /* Il est nécessaire de transférer les données */
            if ( p_cbw->bmCBWFlags == K_MK_MSC_CMD_BLOC_WRAPPER_HOST_TO_DEVICE )
            {
               /* Transmission des données */
               l_result = mk_hcd_sendPipe ( p_mscDevice->device, p_mscDevice->outEndpoint, &p_mscDevice->outPipe,
                                          ( uint8_t* ) p_buf, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_TOOGLE, p_cbw->dCBWDataTransferLength );

               /* Si le périphérique a de nouveau émis un STALL */
               if ( ( p_mscDevice->outPipe.status & K_MK_HCD_ERROR_STALL ) == K_MK_HCD_ERROR_STALL )
               {
                  /* Réinitialisation de la terminaison de type 'IN' */
                  /* La réception d'un STALL n'est pas un comportement anormal, on écrase donc le résultat */
                  l_result = mk_msc_clearHaltFeature ( p_mscDevice, p_pipe, p_mscDevice->outEndpoint );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }
            }

            /* Sinon */
            /* Il est nécessaire de recevoir des données */
            else
            {
               /* Récupération des données */
               l_result = mk_hcd_sendPipe ( p_mscDevice->device, p_mscDevice->inEndpoint, &p_mscDevice->inPipe,
                                          ( uint8_t* ) p_buf, K_MK_HCD_ENDPOINT_IN | K_MK_HCD_PID_TOOGLE, p_cbw->dCBWDataTransferLength );

               /* Si le périphérique a de nouveau émis un STALL */
               if ( ( p_mscDevice->inPipe.status & K_MK_HCD_ERROR_STALL ) == K_MK_HCD_ERROR_STALL )
               {
                  /* Réinitialisation de la terminaison de type 'IN' */
                  /* La réception d'un STALL n'est pas un comportement anormal, on écrase donc le résultat */
                  l_result = mk_msc_clearHaltFeature ( p_mscDevice, p_pipe, p_mscDevice->inEndpoint );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }
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

      /* Récupération du 'CommandStatusWrapper' */
      l_result |= mk_msc_getCmdStatusWrapper ( p_mscDevice, p_pipe, p_cbw, p_csw );
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

