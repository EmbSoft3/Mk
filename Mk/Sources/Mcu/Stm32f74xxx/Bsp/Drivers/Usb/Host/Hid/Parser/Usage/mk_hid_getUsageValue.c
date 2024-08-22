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
* @file mk_hid_getUsageValue.c
* @brief Définition de la fonction mk_hid_getUsageValue.
* @date 7 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_resetResult ( uint8_t* p_usageBuf, uint16_t p_usageSize )
{
   /* Déclaration des variables de comptage */
   uint32_t l_counter = 0, l_bitCounter = 0, l_byteCounter = 0;

   /* Si le résultat doit être stocké */
   if ( p_usageBuf != K_MK_NULL )
   {
      /* Pour la taille de l'usage en octets */
      for ( l_counter = 0 ; l_counter < p_usageSize ; l_counter++ )
      {
         /* Réinitialisation du bit courant */
         p_usageBuf [ l_byteCounter ] =  p_usageBuf [ l_byteCounter ] & ( uint8_t ) ( ~ ( 1 << l_bitCounter ) );

         /* Si l'octet courant a été effacé */
         if ( l_bitCounter == 7 )
         {
            /* Actualisation du compteur d'octets */
            l_byteCounter = l_byteCounter + 1;

            /* Actualisation du compteur de bits */
            l_bitCounter = 0;
         }

         /* Sinon */
         else
         {
            /* Actualisation du compteur de bits */
            l_bitCounter = l_bitCounter + 1;
         }
      }
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

static void mk_hid_setResult ( uint32_t* p_usageBuf, uint32_t p_value )
{
   /* Si le résultat doit être stocké */
   if ( p_usageBuf != K_MK_NULL )
   {
      /* Actualisation du résultat */
      ( *p_usageBuf ) = ( *p_usageBuf ) | p_value;
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

static void mk_hid_convertResult ( T_mkHIDReportTable* p_table, uint32_t* p_usageBuf, uint32_t p_usageSize )
{
   /* Déclaration d'une variable de travail */
   uint32_t l_tmp = ( *p_usageBuf );

   /* Déclaration d'une variable stockant le signe de la grandeur */
   uint32_t l_sign;

   /* Si le résultat peut s'étendre sur une plage négative alors, d'après la norme, le résultat est signé */
   /* Si la variable est de type signée et si la longueur de celle-ci est inférieur à K_MK_HID_MAX_USAGE_SIZE */
   /* Les variables de type 'Array' n'exécute pas ce code car 'LogicalMinimum' et 'LogicalMaximum' sont positif' */
   if ( ( p_usageBuf != K_MK_NULL ) && ( p_usageSize <= K_MK_HID_MAX_USAGE_SIZE ) &&
      ( ( p_table->global.logicalMinimum < 0 ) || ( p_table->global.logicalMaximum < 0 ) ) )
   {
      /* Détermination du signe de la grandeur */
      l_sign = l_tmp & ( uint32_t ) ( 1 << ( p_table->global.reportSize - 1 ) );

      /* Si la grandeur est négative */
      if ( l_sign > 0 )
      {
         /* Conversion de la valeur négative sur 'n' bits en valeur positive sur 32bits */
         l_tmp = ( ( ~ l_tmp ) + 1 ) & ( 0xFFFFFFFF >> ( K_MK_HID_MAX_USAGE_SIZE - p_table->global.reportSize ) );

         /* Conversion de la valeur positif en valeur négative sur 32bits */
         l_tmp = ( ( ~ l_tmp ) + 1 );

         /* Enregistrement du résultat */
         ( *p_usageBuf ) = l_tmp;
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
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_hid_setUsageBuffer ( T_mkHIDUsageParser* p_parser, uint32_t p_remainingSize, uint32_t p_currentByteOffset, uint32_t p_currentBitOffset )
{
   /* Déclaration des variables de travail */
   uint32_t l_chunk, l_shift;

   /* Détermination de la valeur de décalage */
   l_shift = ( uint32_t ) ( ( ( ~p_remainingSize ) + 1 ) & 0x7 );

   /* Récupération du morceau de données sur l'octet courant */
   l_chunk = ( uint32_t ) g_mkHIDPacketBuf [ p_parser->byteOffset ] & ( uint32_t ) ( 0xFF >> l_shift );

   /* Décalage du buffer de données pour les prochaines itérations */
   g_mkHIDPacketBuf [ p_parser->byteOffset ] = ( uint8_t ) ( g_mkHIDPacketBuf [ p_parser->byteOffset ] >> p_remainingSize );

   /* Actualisation de la valeur de l'usage */
   mk_hid_setResult ( &p_parser->usageBuf [ p_currentByteOffset ], ( l_chunk << p_currentBitOffset ) );

   /* Retour */
   return ( l_chunk );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_requestUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable stockant le nombre de données à récupérer */
   uint16_t l_packetLength = 0;

   /* Si la terminaison utilisée est de type 'INTERRUPT_IN' */
   if ( p_parser->endpointType == K_USB_INTERRUPT_ENDPOINT )
   {
      /* Détermination de la taille des données à récupérer */
      l_packetLength = p_hidDevice->inEndpoint->wMaxPacketSize;

      /* Si le nombre de données à récupérer est inférieure à la taille maximale d'un paquet */
      if ( p_parser->byteRemaining < l_packetLength )
      {
         /* Actualisation de la taille des données à récupérer */
         l_packetLength = ( uint16_t ) p_parser->byteRemaining;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Transmission d'une requête d'interruption */
      /* Des octets de padding seront ajouté si la taille du 'Report' est inférieure à la taille d'un paquet */
      /* Une transaction supplémentaire sera réémise si la taille du 'Report' est supérieure à la taille maximale d'un paquet. */
      l_result = mk_hid_getInterrupt ( p_hidDevice, p_pipe, g_mkHIDPacketBuf, l_packetLength );
   }

   /* Sinon */
   else
   {
      /* Détermination de la taille des données à récupérer */
      l_packetLength = p_hidDevice->device->deviceDescriptor.bMaxPacketSize0;

      /* Si le nombre de données à récupérer est inférieure à la taille maximale d'un paquet */
      if ( p_parser->byteRemaining < l_packetLength )
      {
         /* Actualisation de la taille des données à récupérer */
         l_packetLength = ( uint16_t ) p_parser->byteRemaining;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Transmissin d'une requête */
      /* Des octets de padding seront ajoutés si la taille du 'Report' est inférieure à la taille d'un paquet */
      /* Une transaction supplémentaire sera réémise si la taille du report est supérieure à la taille maximale d'un paquet. */
      l_result = mk_hcd_sendPipe ( p_hidDevice->device, K_MK_NULL, p_pipe, ( uint8_t* ) g_mkHIDPacketBuf,
                                   ( uint32_t ) ( K_MK_HCD_ENDPOINT_IN | K_MK_HCD_PID_DATA1 ), l_packetLength );
   }

   /* Si le paquet n'est pas acquitté, une erreur s'est produite */
   if ( ( p_pipe->status & K_MK_HCD_FLAG_ACK ) != K_MK_HCD_FLAG_ACK )
   {
      /* Actualisation de l'état du périphérique */
      p_hidDevice->state |= K_MK_HID_DEVICE_ERROR_STATE;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Actualisation du nombre de données restantes */
   p_parser->byteRemaining = p_parser->byteRemaining - ( uint32_t ) l_packetLength;

   /* Actualisation de l'offset du buffer et du nombre de bits disponibles */
   p_parser->byteOffset = 0; p_parser->bitAvailable = 8;

   /* Actualisation de la variable de comptage */
   p_parser->bitNumber = ( uint32_t ) p_hidDevice->inEndpoint->wMaxPacketSize * 8;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_getUsageValue ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, uint16_t p_destinationSize )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_chunk;

   /* Déclaration d'une variable stockant l'offset de mise à jour du résultat (entre 0 et 31) */
   uint32_t l_bitOffset = 0;

   /* Déclaration d'une variable stockant l'offset de mise à jour du buffer de sortie */
   uint32_t l_outByteOffset = 0;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_parser != K_MK_NULL ) && ( p_table != K_MK_NULL ) )
   {
      /* Réinitialisation du résultat */
      mk_hid_resetResult ( ( uint8_t* ) &p_parser->usageBuf [ l_outByteOffset ], p_destinationSize );

      /* Tant que l'intégralité de l'usage n'a pas été récupéré */
      while ( ( p_parser->usageSize != 0 ) && ( l_result == K_MK_OK ) && ( ( p_hidDevice->state & K_MK_HID_DEVICE_ERROR_STATE ) != K_MK_HID_DEVICE_ERROR_STATE ) )
      {
         /* Si des nouvelles données doivent être récupérées */
         if ( ( p_parser->bitNumber == 0 ) && ( p_parser->byteRemaining != 0 ) )
         {
            /* Déclenchement d'une nouvelle requête HID */
            l_result = mk_hid_requestUsage ( p_hidDevice, p_pipe, p_parser );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Ce parser récupére plusieurs type de données : */

            /* Dans le cas d'un usage ('Variable' | 'Bitfield'), il récupére les 'n' bits de données. Si la variable a une taille */
            /* inférieur à K_MK_HID_MAX_USAGE_SIZE, il regarde si la donnée est signée (logical minimum et logical maximum) puis */
            /* la convertie si nécessaire */

            /* Dans le cas d'une variable bufferisée ('Variable' | 'Buffered Bytes'), il récupére les 'n' octets du tableau et n'applique aucune */
            /* conversion explicite en valeur signée. La norme indique que les données sont alignées sur 8 bits. Si une conversion est nécessaire, */
            /* elle est réalisée automatiquement par le jeu de cast. */

            /* Dans le cas d'un tableau ('Array' | 'Bitfield'), il récupére les 'n' bits de l'index puis détermine la valeur à appliquer à partir */
            /* d'une adresse statique. Il n'y a pas de conversion explicite en valeur signée. Si une conversion est nécessaire, elle est dictée par la */
            /* valeur présente à l'index de la table. */

            /* L'adresse de destination est déterminée à partir des attributs 'Usage Minimum', 'Usage Maximum' et 'Usage'. */

            /* Dans le cas d'une définition avec 'Usage', le parser s'exécute une seule fois. Une unique adresse est alors dédiée à la réception de la donnée. */
            /* Lorsque la donnée à une taille supérieure à K_MK_HID_MAX_USAGE_SIZE, les adresses successives sont utilisées pour stocker l'intégralité du message. */

            /* Dans le cas d'une définition avec 'Usage Minimum' et 'Usage Maximum', le parser s'exécute 'n' fois. Plusieurs adresses sont dédiées à la réception */
            /* des données. Une nouvelle adresse peut être spécifiée à l'entrée de la fonction pour modifier l'emplaçement de stockage des données à chaque itération. */

            /* Si l'usage peut être partiellement ou entièrement récupéré */
            if ( p_parser->usageSize >= p_parser->bitAvailable )
            {
               /* Récupération d'un segment de données d'un usage HID */
               l_chunk = mk_hid_setUsageBuffer ( p_parser, p_parser->bitAvailable, l_outByteOffset, l_bitOffset ) ;

               /* Gestion du cas où la longueur de l'usage est supérieure à 32 bits */
               /* L'usage est un champ de bit */

               /* Si le morceau ne peut pas être copier intégralement dans le buffer de sortie */
               if ( ( p_parser->bitAvailable + l_bitOffset ) > K_MK_HID_MAX_USAGE_SIZE )
               {
                  /* Le processus de conversion en nombre signé n'est pas appliqué pour les variables dont la taille */
                  /* est supérieure à K_MK_HID_MAX_USAGE_SIZE bits. */

                  /* Actualisation de l'offset du buffer */
                  l_outByteOffset++;

                  /* Actualisation de la valeur de l'usage */
                  /* On applique la conversion en entier après la condition suivante uniquement si la donnée a été entièrement récupérée. */
                  mk_hid_setResult ( &p_parser->usageBuf [ l_outByteOffset ], ( l_chunk >> ( K_MK_HID_MAX_USAGE_SIZE - l_bitOffset ) ) );

                  /* Actualisation de l'offset de l'octet courant */
                  l_bitOffset += ( K_MK_HID_MAX_USAGE_SIZE - l_bitOffset );
               }

               /* Sinon */
               else
               {
                  /* Actualisation de l'offset de l'octet courant */
                  l_bitOffset += p_parser->bitAvailable;
               }

               /* Si la donnée a été entièrement récupérée */
               if ( p_parser->usageSize == p_parser->bitAvailable )
               {
                  /* Analyse puis conversion du format de la donnée */
                  /* Cette fonction n'a aucun effet si la données n'est pas signé ou si la longueur de la donnée est supérieure à K_MK_HID_MAX_USAGE_SIZE */
                  mk_hid_convertResult ( p_table, &p_parser->usageBuf [ l_outByteOffset ], p_parser->usageSize );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Actualisation des variables */
               p_parser->bitNumber -= p_parser->bitAvailable;
               p_parser->usageSize -= p_parser->bitAvailable;
               p_parser->bitAvailable = 8;
               p_parser->byteOffset++ ;
            }

            /* Sinon */
            else
            {
               /* Récupération du dernier segment de données HID */
               /* Après cette fonction tous les bits de l'usage HID ont été récupérés. */
               l_chunk = mk_hid_setUsageBuffer ( p_parser, p_parser->usageSize, l_outByteOffset, l_bitOffset ) ;

               /* Gestion du cas où la longueur de l'usage est supérieure à 32 bits */
               /* L'usage peut être un champ de bits ou un tableau */

               /* Si le morceau ne peut pas être copier intégralement dans le buffer de sortie */
               if ( ( p_parser->bitAvailable + l_bitOffset ) > K_MK_HID_MAX_USAGE_SIZE )
               {
                  /* Actualisation de l'offset du buffer */
                  l_outByteOffset++;

                  /* Actualisation de la valeur de l'usage */
                  mk_hid_setResult ( &p_parser->usageBuf [ l_outByteOffset ], ( l_chunk >> ( K_MK_HID_MAX_USAGE_SIZE - l_bitOffset ) ) );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Analyse puis conversion du format de la donnée */
               /* Cette fonction n'a aucun effet si la données n'est pas signé ou si la longueur de la donnée est supérieure à K_MK_HID_MAX_USAGE_SIZE */
               mk_hid_convertResult ( p_table, &p_parser->usageBuf [ l_outByteOffset ], p_parser->usageSize );

               /* Actualisation des variables */
               p_parser->bitAvailable -= p_parser->usageSize;
               p_parser->bitNumber -= p_parser->usageSize;
               p_parser->usageSize = 0;
            }
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}

