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
* @file mk_msc_wrap.c
* @brief Définition de la fonction mk_msc_wrap.
* @date 18 mai 2020
* @todo Ecrire un nombre aléatoire dans le tag.
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_wrap ( T_mkMSCCommandBlockWrapper* p_cbw, T_mkAddr p_cmd, uint8_t p_cmdLength, uint8_t p_direction, uint8_t p_lun, uint32_t p_blocLength )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   int32_t l_ret;

   /* Si les paramètres sont valides */
   if ( ( p_cbw != K_MK_NULL ) && ( p_cmd != K_MK_NULL ) &&
        ( p_cmdLength < K_MK_MSC_CMD_MAXIMUM_SIZE ) && ( p_lun < K_MK_MSC_MAX_LUN ) )
   {
      /* Réinitialisation de la structure */
      _writeWords ( p_cbw, 0x00, K_MK_MSC_WRAPPER_SIZE );

      /* Configuration du Command-Bloc-Wrapper */
      p_cbw->dCBWSignature = K_MK_MSC_CMD_BLOC_WRAPPER_SIGNATURE;    /* Ecriture de la signature. */
      p_cbw->dCBWDataTransferLength = p_blocLength;                  /* Ecriture de la taille du bloc de données. */
      p_cbw->bmCBWFlags = p_direction;                               /* Ecriture de la direction du transfert. */
      p_cbw->bCBWLUN = p_lun;                                        /* Ecriture du numéro de l'unité logique. */
      p_cbw->bCBWCBLength = p_cmdLength;                             /* Ecriture de la taille de la commande. */

      /* Génération d'un nombre aléatoire dans le tag */
      l_ret = mk_utils_rand ( &p_cbw->dCBWTag );

      /* Si une erreur s'est produite */
      if ( l_ret != 0 )
      {
         /* Ecriture du tag avec la valeur du tick courant */
         p_cbw->dCBWTag = mk_getTick ();
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Copie de la commande dans le 'Wrapper' */
      _copy ( p_cbw->CBWCB, p_cmd, p_cmdLength );
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

