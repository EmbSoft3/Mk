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
* @file mk_hid_checkMissingDeclaration.c
* @brief Définition de la fonction mk_hid_checkMissingDeclaration.
* @date 12 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkMissingLocalItemDeclaration ( T_mkHIDItem* p_item, uint32_t* p_counter, T_mkHIDShortItemTag p_tag, T_mkHIDReportError* p_errorRegister, T_mkHIDReportError p_errorFlag )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = *p_counter;

   /* Si l'item est l'item recherché */
   if ( p_item->head.field.tag == p_tag )
   {
      /* Actualisation de la variable d'état */
      l_counter = 1;
   }

   /* Sinon si l'item est de type 'Input', 'Output' et 'Feature' */
   else if ( ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_INPUT ) || ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_OUTPUT ) ||
             ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_FEATURE ) )
   {
      /* Si l'usage n'est pas de type 'constant' */
      if ( ( p_item->value & K_MK_HID_ITEM_CONSTANT ) == 0 )
      {
         /* Si une page n'a pas été déclarée */
         if ( l_counter == 0 )
         {
            /* Actualisation du registre d'erreur */
            ( *p_errorRegister ) = p_errorFlag;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
            /* On ne réinitialise pas la variable d'état car c'est un item global */
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

   /* Actualisation de la valeur du compteur */
   *p_counter = l_counter;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkMissingGlobalItemDeclaration ( T_mkHIDItem* p_item, uint32_t* p_counter, T_mkHIDShortItemTag p_tag, T_mkHIDReportError* p_errorRegister, T_mkHIDReportError p_errorFlag )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = *p_counter;

   /* Si l'item est l'item recherché */
   if ( p_item->head.field.tag == p_tag )
   {
      /* Actualisation de la variable d'état */
      l_counter = 1;
   }

   /* Sinon si l'item est de type 'Input', 'Output' et 'Feature' */
   else if ( ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_INPUT ) || ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_OUTPUT ) ||
             ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_FEATURE ) )
   {
      /* Si une page n'a pas été déclarée */
      if ( l_counter == 0 )
      {
         /* Actualisation du registre d'erreur */
         ( *p_errorRegister ) = p_errorFlag;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
         /* On ne réinitialise pas la variable d'état car c'est un item global */
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Actualisation de la valeur du compteur */
   *p_counter = l_counter;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkMissingUsageDeclaration ( T_mkHIDItem* p_item, uint32_t* p_usageCounter, uint32_t* p_usageMinMaxCounter, T_mkHIDReportError* p_errorRegister )
{
   /* Déclaration des compteurs */
   uint32_t l_usageCounter = *p_usageCounter;
   uint32_t l_usageMinMaxCounter = * p_usageMinMaxCounter;

   /* Sinon si l'item est de type 'Usage' */
   if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE )
   {
      /* Actualisation de la variable d'état */
      l_usageCounter = 1;
   }

   /* Sinon si l'item est de type 'Usage Minimum' */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MINIMUM )
   {
      /* Actualisation de la variable d'état */
      l_usageMinMaxCounter |= 1;
   }

   /* Sinon si l'item est de type 'Usage Maximum' */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MAXIMUM )
   {
      /* Actualisation de la variable d'état */
      l_usageMinMaxCounter |= 2;
   }

   /* Sinon si l'item est de type 'Input', 'Output' et 'Feature' */
   else if ( ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_INPUT ) || ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_OUTPUT ) ||
             ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_FEATURE ) )
   {
      /* Si l'usage n'est pas de type 'constant' */
      if ( ( p_item->value & K_MK_HID_ITEM_CONSTANT ) == 0 )
      {
         /* Si aucun usage n'a pas été déclarée */
         if ( ( l_usageCounter == 0 ) && ( l_usageMinMaxCounter != 3 ) )
         {
            /* Actualisation du registre d'erreur */
            ( *p_errorRegister ) = K_MK_HID_ERROR_MISSING_DECLARATION_USAGE;
         }

         /* Sinon */
         else
         {
            /* Actualisation des variables d'état */
            l_usageCounter = 0;
            l_usageMinMaxCounter = 0;
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

   /* Actualisation de la valeur des compteurs */
   *p_usageCounter = l_usageCounter;
   *p_usageMinMaxCounter = l_usageMinMaxCounter;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_countUsageDeclaration ( T_mkHIDItem* p_item, uint32_t* p_counter )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = *p_counter;

   /* Sinon si l'item est de type 'Input', 'Output' et 'Feature' */
   if ( ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_INPUT ) || ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_OUTPUT ) ||
        ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_FEATURE ) )
   {
      /* Actualisation du compteur */
      l_counter = 1;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Actualisation de la valeur du compteur */
   *p_counter = l_counter;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_checkMissingDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'item */
   T_mkHIDItem* l_item;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Déclaration des variables indiquant la présence des items rencontrés */
   uint32_t l_usagePage = 0, l_logicalMinimum = 0, l_logicalMaximum = 0, l_reportSize = 0;
   uint32_t l_reportCount = 0, l_usage = 0, l_usageRange = 0;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_error != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du premier item du 'Report Descriptor' */
      l_item = p_hidDevice->reportDescriptor.item;

      /* Tant que le 'Report Descriptor' n'a pas été analysé et tant qu'aucune erreur n'est détectée */
      while ( ( l_item != K_MK_NULL ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
      {
         /* Vérification de la déclaration de l'item 'UsagePage' */
         mk_hid_checkMissingLocalItemDeclaration ( l_item, &l_usagePage, K_MK_HID_ITEM_TAG_USAGE_PAGE, p_error, K_MK_HID_ERROR_MISSING_DECLARATION_USAGE_PAGE );

         /* Si aucune erreur ne s'est produite */
         if ( ( *p_error ) == K_MK_HID_NO_ERROR )
         {
            /* Vérification de la déclaration de l'item 'LogicalMinimum' */
            mk_hid_checkMissingLocalItemDeclaration ( l_item, &l_logicalMinimum, K_MK_HID_ITEM_TAG_LOGICAL_MINIMUM, p_error, K_MK_HID_ERROR_MISSING_DECLARATION_LOGICAL_MINIMUM );

            /* Si aucune erreur ne s'est produite */
            if ( ( *p_error ) == K_MK_HID_NO_ERROR )
            {
               /* Vérification de la déclaration de l'item 'LogicalMaximum' */
               mk_hid_checkMissingLocalItemDeclaration ( l_item, &l_logicalMaximum, K_MK_HID_ITEM_TAG_LOGICAL_MAXIMUM, p_error, K_MK_HID_ERROR_MISSING_DECLARATION_LOGICAL_MAXIMUM );

               /* Si aucune erreur ne s'est produite */
               if ( ( *p_error ) == K_MK_HID_NO_ERROR )
               {
                  /* Vérification de la déclaration de l'item 'ReportSize' */
                  mk_hid_checkMissingGlobalItemDeclaration ( l_item, &l_reportSize, K_MK_HID_ITEM_TAG_REPORT_SIZE, p_error, K_MK_HID_ERROR_MISSING_DECLARATION_REPORT_SIZE );

                  /* Si aucune erreur ne s'est produite */
                  if ( ( *p_error ) == K_MK_HID_NO_ERROR )
                  {
                     /* Vérification de la déclaration de l'item 'ReportCounter' */
                     mk_hid_checkMissingGlobalItemDeclaration ( l_item, &l_reportCount, K_MK_HID_ITEM_TAG_REPORT_COUNT, p_error, K_MK_HID_ERROR_MISSING_DECLARATION_REPORT_COUNT );

                     /* Si aucune erreur ne s'est produite */
                     if ( ( *p_error ) == K_MK_HID_NO_ERROR )
                     {
                        /* Vérification de la déclaration des item 'UsageMinimum', 'UsageMaximum' et 'Usage' */
                        mk_hid_checkMissingUsageDeclaration ( l_item, &l_usage, &l_usageRange, p_error );
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

         /* Détection de la présence d'au moins un usage dans le descripteur */
         mk_hid_countUsageDeclaration ( l_item, &l_counter );

         /* Actualisation du pointeur d'item */
         l_item = l_item->nextItem;
      }

      /* Si aucune item de type 'Input', 'Output' ou 'Feature' n'a été rencontré */
      if ( ( ( *p_error ) == K_MK_HID_NO_ERROR ) && ( l_counter == 0 ) )
      {
         /* Actualisation du registre d'erreur */
         ( *p_error ) = K_MK_HID_ERROR_MISSING_DECLARATION_ITEM;
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


