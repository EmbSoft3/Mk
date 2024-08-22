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
* @file mk_hid_checkCouplingDeclaration.c
* @brief Définition de la fonction mk_hid_checkCouplingDeclaration.
* @date 13 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkUsageMinMaxCouplingDeclaration ( T_mkHIDItem* p_item, uint32_t* p_usageMinimumCounter, uint32_t* p_usageMaximumCounter, T_mkHIDReportError* p_error )
{
   /* Déclaration des compteurs d'item */
   uint32_t l_usageMinimum = *p_usageMinimumCounter, l_usageMaximum = *p_usageMaximumCounter;

   /* Si l'item est de type 'Usage Minimum' */
   if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MINIMUM )
   {
      /* Actualisation de la variable d'état */
      l_usageMinimum++;
   }

   /* Sinon si l'item est de type 'Usage Maximum' */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MAXIMUM )
   {
      /* Actualisation de la variable d'état */
      l_usageMaximum++;
   }

   /* Sinon si l'item est de type main ('Input', 'Output', 'Feature' ou 'Collection' ) */
   else if ( ( p_item->head.value & 0xC ) == 0x0 )
   {
      /* Si les compteurs 'Usage Minimum' et 'Usage Maximum' sont différents */
      if ( l_usageMinimum != l_usageMaximum )
      {
         /* Actualisation du registre d'erreur */
         ( *p_error ) = K_MK_HID_ERROR_CORRESPONDING_DECLARATION_USAGE_MIN_MAX;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Actualisation des pointeurs */
   *p_usageMinimumCounter = l_usageMinimum;
   *p_usageMaximumCounter = l_usageMaximum;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkDesignatorMinMaxCouplingDeclaration ( T_mkHIDItem* p_item, uint32_t* p_designatorMinimumCounter, uint32_t* p_designatorMaximumCounter, T_mkHIDReportError* p_error )
{
   /* Déclaration des compteurs d'item */
   uint32_t l_designatorMinimum = *p_designatorMinimumCounter, l_designatorMaximum = *p_designatorMaximumCounter;

   /* Si l'item est de type 'Designator Minimum' */
   if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_DESIGNATOR_MINIMUM )
   {
      /* Actualisation de la variable d'état */
      l_designatorMinimum++;
   }

   /* Sinon si l'item est de type 'Designator Maximum' */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_DESIGNATOR_MAXIMUM )
   {
      /* Actualisation de la variable d'état */
      l_designatorMaximum++;
   }

   /* Sinon si l'item est de type main ('Input', 'Output', 'Feature' ou 'Collection' ) */
   else if ( ( p_item->head.value & 0xC ) == 0x0 )
   {
      /* Si les compteurs 'Designator Minimum' et 'Designator Maximum' sont différents */
      if ( l_designatorMinimum != l_designatorMaximum )
      {
         /* Actualisation du registre d'erreur */
         ( *p_error ) = K_MK_HID_ERROR_CORRESPONDING_DECLARATION_DESIGNATOR_MIN_MAX;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Actualisation des pointeurs */
   *p_designatorMinimumCounter = l_designatorMinimum;
   *p_designatorMaximumCounter = l_designatorMaximum;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkStringMinMaxCouplingDeclaration ( T_mkHIDItem* p_item, uint32_t* p_stringMinimumCounter, uint32_t* p_stringMaximumCounter, T_mkHIDReportError* p_error )
{
   /* Déclaration des compteurs d'item */
   uint32_t l_stringMinimum = *p_stringMinimumCounter, l_stringMaximum = *p_stringMaximumCounter;

   /* Si l'item est de type 'String Minimum' */
   if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_STRING_MINIMUM )
   {
      /* Actualisation de la variable d'état */
      l_stringMinimum++;
   }

   /* Sinon si l'item est de type 'String Maximum' */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_STRING_MAXIMUM )
   {
      /* Actualisation de la variable d'état */
      l_stringMaximum++;
   }

   /* Sinon si l'item est de type main ('Input', 'Output', 'Feature' ou 'Collection' ) */
   else if ( ( p_item->head.value & 0xC ) == 0x0 )
   {
      /* Si les compteurs 'String Minimum' et 'String Maximum' sont différents */
      if ( l_stringMinimum != l_stringMaximum )
      {
         /* Actualisation du registre d'erreur */
         ( *p_error ) = K_MK_HID_ERROR_CORRESPONDING_DECLARATION_STRING_MIN_MAX;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Actualisation des pointeurs */
   *p_stringMinimumCounter = l_stringMinimum;
   *p_stringMaximumCounter = l_stringMaximum;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkPopPushCouplingDeclaration ( T_mkHIDItem* p_item, uint32_t* p_popCounter, uint32_t* p_pushCounter, T_mkHIDReportError* p_error )
{
   /* Déclaration des compteurs d'item */
   uint32_t l_pop = *p_popCounter, l_push = *p_pushCounter;

   /* Si l'item est de type 'Pop' */
   if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_POP )
   {
      /* Actualisation de la variable d'état */
      l_pop++;
   }

   /* Sinon si l'item est de type 'Push' */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_PUSH )
   {
      /* Actualisation de la variable d'état */
      l_push++;
   }

   /* Sinon si l'item est de type main ('Input', 'Output', 'Feature' ou 'Collection' ) */
   else if ( ( p_item->head.value & 0xC ) == 0x0 )
   {
      /* Si les compteurs 'Push' et 'Pop' sont différents */
      if ( l_push != l_pop )
      {
         /* Actualisation du registre d'erreur */
         ( *p_error ) = K_MK_HID_ERROR_CORRESPONDING_DECLARATION_PUSH_POP;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Actualisation des pointeurs */
   *p_popCounter = l_pop;
   *p_pushCounter = l_push;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkDelimiterCouplingDeclaration ( T_mkHIDItem* p_item, uint32_t* p_delimiterOpenCounter, uint32_t* p_delimiterCloseCounter, T_mkHIDReportError* p_error )
{
   /* Déclaration des compteurs d'item */
   uint32_t l_delimiterOpen = *p_delimiterOpenCounter, l_delimiterClose = *p_delimiterCloseCounter;

   /* Si l'item est de type 'Delimiter' */
   if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_DELIMITER )
   {
      /* Si ouverture */
      if ( p_item->value == 0 )
      {
         /* Actualisation de la variable d'état */
         l_delimiterOpen++;
      }

      /* Si fermeture */
      else if ( p_item->value == 1 )
      {
         /* Actualisation de la variable d'état */
         l_delimiterClose++;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
         /* L'erreur est remontée dans la fonction mk_hid_checkInvalidValue */
      }
   }

   /* Sinon si l'item est de type main ('Input', 'Output', 'Feature' ou 'Collection' ) */
   else if ( ( p_item->head.value & 0xC ) == 0x0 )
   {
      /* Si les compteurs 'Delimiter Open' et 'Delimiter Close' sont différents */
      if ( l_delimiterOpen != l_delimiterClose )
      {
         /* Actualisation du registre d'erreur */
         ( *p_error ) = K_MK_HID_ERROR_CORRESPONDING_DECLARATION_DELIMITER;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Actualisation des pointeurs */
   *p_delimiterOpenCounter = l_delimiterOpen;
   *p_delimiterCloseCounter = l_delimiterClose;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkCollectionCouplingDeclaration ( T_mkHIDItem* p_item, uint32_t* p_collectionCounter, uint32_t* p_endCollectionCounter, T_mkHIDReportError* p_error )
{
   /* Déclaration des compteurs d'item */
   uint32_t l_collection = *p_collectionCounter, l_endCollection = *p_endCollectionCounter;

   /* Sinon si l'item est de type main ('Input', 'Output', 'Feature', 'Collection' ) */
   if ( ( p_item->head.value & 0xC ) == 0x0 )
   {
      /* Si l'item est de type 'Collection' */
      if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_COLLECTION )
      {
         /* Actualisation de la variable d'état */
         l_collection++;
      }

      /* Sinon si l'item est de type 'End Collection' */
      else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_END_COLLECTION )
      {
         /* Actualisation de la variable d'état */
         l_endCollection++;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* On ne vérifie pas si les compteurs de collection sont identiques car certains */
      /* périphériques omettent la fermeture de la dernière collection */

      /* Si une erreur d'imbrication est présente */
      if ( l_collection < l_endCollection )
      {
         /* Actualisation du registre d'erreur */
         ( *p_error ) = K_MK_HID_ERROR_CORRESPONDING_DECLARATION_COLLECTION;
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

   /* Actualisation des pointeurs */
   *p_collectionCounter = l_collection;
   *p_endCollectionCounter = l_endCollection;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_checkCouplingDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'item */
   T_mkHIDItem* l_item;

   /* Déclaration des compteurs d'item */
   uint32_t l_usageMinimumCounter = 0, l_usageMaximumCounter = 0;
   uint32_t l_designatorMinimumCounter = 0, l_designatorMaximumCounter = 0;
   uint32_t l_stringMinimumCounter = 0, l_stringMaximumCounter = 0;
   uint32_t l_popCounter = 0, l_pushCounter = 0;
   uint32_t l_delimiterCloseCounter = 0, l_delimiterOpenCounter = 0;
   uint32_t l_collectionCounter = 0, l_endCollectionCounter = 0;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_error != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du premier item du 'Report Descriptor' */
      l_item = p_hidDevice->reportDescriptor.item;

      /* Tant que le 'Report Descriptor' n'a pas été analysé et tant qu'aucune erreur n'est détectée */
      while ( ( l_item != K_MK_NULL ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
      {
         /* La déclaration des items 'Physical maximum' et 'Physical minimum' n'est pas vérifiée */
         /* car certain périphérique ne déclare qu'un item et laisse la deuxième à la valeur de défaut qui */
         /* est définie par les déclarations 'Logical Minimum' ou 'Logical Maximum'. */

         /* Vérification de la cohérence des items 'UsageMinimum' et 'UsageMaximum' */
         mk_hid_checkUsageMinMaxCouplingDeclaration ( l_item, &l_usageMinimumCounter, &l_usageMaximumCounter, p_error );

         /* Si aucune erreur n'a été détectée */
         if ( ( *p_error ) == K_MK_HID_NO_ERROR )
         {
            /* Vérification de la cohérence des items 'DesignatorMinimum' et 'DesignatorMaximum' */
            mk_hid_checkDesignatorMinMaxCouplingDeclaration ( l_item, &l_designatorMinimumCounter, &l_designatorMaximumCounter, p_error );

            /* Si aucune erreur n'a été détectée */
            if ( ( *p_error ) == K_MK_HID_NO_ERROR )
            {
               /* Vérification de la cohérence des items 'StringMinimum' et 'StringMaximum' */
               mk_hid_checkStringMinMaxCouplingDeclaration ( l_item, &l_stringMinimumCounter, &l_stringMaximumCounter, p_error );

               /* Si aucune erreur n'a été détectée */
               if ( ( *p_error ) == K_MK_HID_NO_ERROR )
               {
                  /* Vérification de la cohérence des items 'Pop' et 'Push' */
                  mk_hid_checkPopPushCouplingDeclaration ( l_item, &l_popCounter, &l_pushCounter, p_error );

                  /* Si aucune erreur n'a été détectée */
                  if ( ( *p_error ) == K_MK_HID_NO_ERROR )
                  {
                     /* Vérification de la cohérence des items 'Delimiter' */
                     mk_hid_checkDelimiterCouplingDeclaration ( l_item, &l_delimiterOpenCounter, &l_delimiterCloseCounter, p_error );

                     /* Si aucune erreur n'a été détectée */
                     if ( ( *p_error ) == K_MK_HID_NO_ERROR )
                     {
                        /* Vérification de la cohérence des items 'Collection' et 'EndCollection' */
                        mk_hid_checkCollectionCouplingDeclaration ( l_item, &l_collectionCounter, &l_endCollectionCounter, p_error );
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

         /* Actualisation du pointeur d'item */
         l_item = l_item->nextItem;
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
