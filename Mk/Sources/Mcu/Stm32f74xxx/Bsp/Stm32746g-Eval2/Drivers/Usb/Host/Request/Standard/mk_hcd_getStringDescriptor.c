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
* @file mk_hcd_getStringDescriptor.c
* @brief Définition de la fonction mk_hcd_getStringDescriptor.
* @date 26 avr. 2020
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_getLanguage ( uint8_t* p_string, uint16_t p_langid, uint16_t* p_index )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_NOT_AVAILABLE;

   /* Déclaration d'un compteur */
   uint16_t l_counter;

   /* Déclaration d'une variable contenant la longueur des données du descripteur (en multiple de 16 bits ) */
   uint8_t l_length = ( uint8_t )  ( ( p_string [ 0 ] - K_MK_HCD_STRING_DESCRIPTOR_SIZE ) >> 1 );

   /* Déclaration d'un pointeur de langage */
   uint16_t* l_lang = ( T_mkAddr ) ( &p_string [ K_MK_HCD_STRING_DESCRIPTOR_SIZE ] );

   /* Pour le nombre de langages supportés */
   for ( l_counter = 0 ; ( l_counter < l_length ) && ( l_result == K_MK_ERROR_NOT_AVAILABLE ) ; l_counter++ )
   {
      /* Si le langage recherché par l'utilisateur a été trouvé */
      if ( l_lang [ l_counter ] == p_langid )
      {
         /* Actualisation de l'index */
         *p_index = ( uint16_t ) ( l_counter + 1 );

         /* Actualisation de la variable de retour */
         l_result = K_MK_OK;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result );
}

static void mk_hcd_shiftStringDescriptor ( uint8_t* p_string )
{
   /* Déclaration d'un compteur */
   uint8_t l_counter;

   /* Récupération de la longueur de la chaine */
   uint8_t l_length = ( uint8_t ) ( p_string [ 0 ] - K_MK_HCD_STRING_DESCRIPTOR_SIZE );

   /* Pour chaque octet de la chaine */
   for ( l_counter = 0 ; l_counter < l_length ; l_counter++ )
   {
      /* Décalage progressif de la chaine */
      p_string [ l_counter ] = p_string [ l_counter + K_MK_HCD_STRING_DESCRIPTOR_SIZE ];
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_getString ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint8_t* p_string, uint32_t p_index, uint16_t p_length )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une requête */
   T_mkHCDRequest l_request;

   /* Création de la requête d'identification du périphérique */
   l_result = mk_hcd_createRequest ( &l_request, K_MK_HCD_GET_DESCRIPTOR, K_MK_HCD_DEVICE_TO_HOST | K_MK_HCD_STANDARD | K_MK_HCD_DEVICE, K_MK_HCD_DESC_STRING | ( uint16_t ) ( ( p_index >> 16 ) & 0xFFFF ), ( uint16_t ) ( p_index & 0xFFFF ), p_length );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Transmission de la requête */
      l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_SETUP, 8 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Récupération du descripteur */
         l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) p_string, K_MK_HCD_ENDPOINT_IN | K_MK_HCD_PID_DATA1, ( uint32_t ) p_length );

         /* Si la transaction est terminée */
         if ( l_result == K_MK_OK )
         {
            /* Transmission du paquet d'acquittement (ZLP) */
            l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_DATA1, 0 );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_getStringDescriptorByIndex ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint8_t* p_string, uint32_t p_index, uint16_t p_length )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération des deux premier octets du descripteur contenant le langage utilisateur */
   l_result = mk_hcd_getString ( p_device, p_pipe, p_string, p_index, K_MK_HCD_STRING_DESCRIPTOR_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si la longueur du buffer utilisateur est suffisante pour récupérer l'intégralité du descripteur */
      if ( p_length >= p_string [ 0 ] )
      {
         /* Récupération du descripteur contenant le langage utilisateur */
         l_result = mk_hcd_getString ( p_device, p_pipe, p_string, p_index, p_string [ 0 ] );
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
      }
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

T_mkCode mk_hcd_getStringDescriptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint8_t* p_string, uint16_t* p_length, uint16_t p_langid )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint16_t* l_langid = ( T_mkAddr ) ( &p_string [ 0 ] );

   /* Déclaration d'une variable stockant l'index recherché */
   uint16_t l_index = 0;

   /* Si les paramètres sont valides */
   if ( ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_string != K_MK_NULL ) && ( p_length != K_MK_NULL ) && ( ( *p_length ) >= K_MK_HCD_STRING_DESCRIPTOR_SIZE ) )
   {
      /* Récupération de l'index des descripteurs */
      l_result = mk_hcd_getStringDescriptorByIndex ( p_device, p_pipe, p_string, K_MK_HCD_LANGID_INDEX, ( *p_length ) );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si au moins un langage est compris dans l'index */
         if ( p_string [ 0 ] >= ( K_MK_HCD_STRING_DESCRIPTOR_SIZE + K_MK_HCD_LANGID_SIZE ) )
         {
            /* Si l'utilisateur ne recherche pas un descripteur particulier */
            if ( p_langid == K_MK_HCD_LANGID_INDEX )
            {
               /* Récupération du contenu du premier descripteur (index 1) */
               l_result = mk_hcd_getStringDescriptorByIndex ( p_device, p_pipe, p_string, ( uint32_t ) ( l_langid [ 1 ] ) | 0x10000, ( *p_length ) );
            }

            /* Sinon */
            else
            {
               /* Si le langage recherché est contenu dans la table */
               l_result = mk_hcd_getLanguage ( p_string, p_langid, &l_index );

               /* Si le langage recherché par l'utilisateur a été trouvé */
               if ( l_result == K_MK_OK )
               {
                  /* Récupération du contenu du descripteur choisi par l'utilisateur */
                   l_result = mk_hcd_getStringDescriptorByIndex ( p_device, p_pipe, p_string, ( uint32_t ) p_langid | ( ( ( uint32_t ) l_index ) << 16 ), ( *p_length ) );
               }

               /* Sinon */
               else
               {
                  /* Actualisation de la longueur du descripteur */
                  *p_length = 0;
               }
            }

            /* Si le descripteur a été récupéré */
            if ( l_result == K_MK_OK )
            {
               /* Enregistrement de la longueur du descripteur */
               ( *p_length ) = p_string [ 0 ];

               /* Suppression de l'entête du descripteur */
               mk_hcd_shiftStringDescriptor ( p_string );
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



