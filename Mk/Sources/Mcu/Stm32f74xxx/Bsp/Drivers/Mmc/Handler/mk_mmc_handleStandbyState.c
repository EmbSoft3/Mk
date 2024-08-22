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
* @file mk_mmc_handleStandbyState.c
* @brief Définition de la fonction mk_mmc_handleStandbyState.
* @date 1 juil. 2020
*
* @todo Configurer la fréquence d'horloge au début de la fonction.
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_post_sendAllCid ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration du CID */
   T_mkMMCCIDRegister l_cid = { 0 };

   /* Déclaration d'un pointeur de CID */
   uint32_t* l_pCid = ( uint32_t* ) &l_cid;

   /* Initialisation de la commande MMC */
   T_mkMMCCommand l_command = {
         K_MK_MMC_OPCODE_ALL_SEND_CID,          /* Code de la commande */
         0,                                     /* Argument de la commande */
         K_MMC_DIRECTION_CONTROLLER_TO_CARD,    /* Direction du transfert */
         0,                                     /* Nombre de données */
         0,                                     /* Timeout du transfert de données */
         K_MMC_LONG_RESPONSE,                   /* Longueur de la réponse */
         K_MK_MMC_CRC_BYPASS_DISABLED           /* Bypass CRC désactivé */
   };

   /* Transmission de la commande (CMD2) */
   l_result = mk_mmc_sendCmd ( p_handler, K_MK_NULL, &l_command, &l_cid, K_MK_NULL, &p_device->portStatus );

   /* Si une réponse a été reçue */
   if ( l_result == K_MK_OK )
   {
      /* Un 'Revert' de chaque octets du CID est réalisé car la structure CID est l'inverse */
      /* de la structure déclarée dans la spécification. */
      for ( l_counter = 1 ; l_counter < ( K_MK_MMC_CID_SIZE + 1 ) ; l_counter++ )
      {
         /* Réalisation d'un revert du CID */
         l_pCid [ l_counter ] = _revertWord ( &l_pCid [ l_counter ] );
      }

      /* Le CID contient quelques attributs devant être reporté dans la structure 'T_mkDisk' */
      /* On réalise une copie explicite. */

      /* Récupération de l'identifiant du vendeur */
      _copy ( p_device->disk->info.vendorIdentifier, l_cid.oemIdentifier, 2 );

      /* Récupération du nom du produit */
      _copy ( p_device->disk->info.productIdentifier, l_cid.productName, 5 );

      /* Récupération de la révision du disque */
      p_device->disk->info.productRevision [ 0 ] = ( char8_t ) ( ( ( l_cid.productRevision & 0xF0 ) >> 4 ) + 0x30 );
      p_device->disk->info.productRevision [ 1 ] = '.';
      p_device->disk->info.productRevision [ 2 ] = ( char8_t ) ( ( l_cid.productRevision & 0x0F ) + 0x30 );
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

T_mkCode mk_mmc_handleStandbyState ( T_mkMMCHandler* p_handler, T_mkMMCType p_type )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de périphérique */
   T_mkMMCDevice* l_device = K_MK_NULL;

   /* Cette fonction identifie l'intégralité des périphériques sur le bus. */
   /* Elle transmet la commande 'ALL_SEND_CID' (CMD2) en boucle tant qu'une réponse est obtenue. */
   /* Le nombre de périphériques présents sur le bus peut être déterminé avec cette méthode. */

   /* Si le paramètre est valide */
   if ( p_handler != K_MK_NULL )
   {
      /* Boucle tant que le processus d'énumération n'est pas terminé */
      while ( l_result == K_MK_OK )
      {
         /* Création d'un nouveau périphérique MMC */
         /* Le périphérique créé est stocké dans un liste du gestionnaire */
         l_result = mk_mmc_createDevice ( p_handler, &l_device );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Configuration du type de la carte */
            l_device->type = p_type;

            /* Transmission de la commande 'ALL_SEND_CID' (CMD2) */
            /* L'intégralité des périphériques présents sur le bus transmette leur 'CID' en utilisant */
            /* une logique à collecteur ouvert. */
            /* Lorsqu'un périphérique détecte que le niveau logique du bus ne correspond pas à son CID, */
            /* il se place en haute impédance jusqu'à la prochaine énumération. */
            l_result = mk_mmc_post_sendAllCid ( p_handler, l_device );

            /* Si aucune erreur ne s'est produite */
            /* Alors au moins un périhérique a répondu */
            if ( l_result == K_MK_OK )
            {
               /* L'état du périphérique passe de 'READY' à 'IDENTIFICATION' */
               l_device->state = K_MK_MMC_STATE_IDENTIFICATION;

               /* Transmission de la requête 'SEND_RELATIVE_ADDR' (CMD3) */
               /* Le maitre interroge le périphérique afin qu'il lui fournisse une adresse. */
               /* Cette adresse sera utilisée notamment pour sélectionner le périphérique en question. */
               l_result = mk_mmc_publishNewRCA ( p_handler, l_device );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* L'état du périphérique passe de 'IDENTIFICATION' à 'STANDBY' */
                  l_device->state = K_MK_MMC_STATE_STANDBY;
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

         /* Si une erreur s'est produite */
         if ( ( l_result != K_MK_OK ) && ( l_result != K_MK_ERROR_MALLOC ) )
         {
            /* Supression du périphérique alloué */
            l_result |= mk_mmc_deleteDevice ( p_handler, l_device, 0 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Si au moins un périphérique a été identifié, alors on bascule la variable de retour */
      /* à OK */
      if ( p_handler->list.first != K_MK_NULL )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_OK;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* A ce stade, la phase d'énumération des périphériques présents sur le bus est terminée */
      /* Ils peuvent maintenant fonctionner à leur fréquence nominale */

      /* Configuration de la fréquence d'horloge nominale */
      mk_mmc_setFrequency ( );
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
