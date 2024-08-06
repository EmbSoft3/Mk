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
* @file mk_hid_checkOutOfRange.c
* @brief Définition de la fonction mk_hid_checkOutOfRange.
* @date 14 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkOutOfRangeStringMinMax ( T_mkHIDReportTable* p_table, T_mkHIDReportError* p_error )
{
   /* Si la valeur minimale est supérieure à la valeur maximale */
   if ( p_table->local->stringMinimum > p_table->local->stringMaximum )
   {
      /* Actualisation du registre d'erreur */
      ( *p_error ) = K_MK_HID_ERROR_INVALID_VALUE_STRING_MIN_MAX;
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

static void mk_hid_checkOutOfRangeDesignatorMinMax ( T_mkHIDReportTable* p_table, T_mkHIDReportError* p_error )
{
   /* Si la valeur minimale est supérieure à la valeur maximale */
   if ( p_table->local->designatorMinimum > p_table->local->designatorMaximum )
   {
      /* Actualisation du registre d'erreur */
      ( *p_error ) = K_MK_HID_ERROR_INVALID_VALUE_DESIGNATOR_MIN_MAX;
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

static void mk_hid_checkOutOfRangeUsageMinMax ( T_mkHIDReportTable* p_table, T_mkHIDReportError* p_error )
{
   /* Déclaration des variables de travail */
   uint32_t l_minimalPage = 0, l_maximalPage = 0;

   /* Si la valeur minimale est supérieure à la valeur maximale */
   if ( p_table->local->usageMinimum > p_table->local->usageMaximum )
   {
      /* Actualisation du registre d'erreur */
      ( *p_error ) = K_MK_HID_ERROR_INVALID_VALUE_USAGE_MIN_MAX;
   }

   /* Sinon */
   else
   {
      /* Vérification de la page de l'usage */
      /* Les 16 bits de poids fort contienne le numéro de page. */
      /* Si la valeur est nulle, l'usage n'est pas étendue */
      l_minimalPage = ( uint32_t ) ( p_table->local->usageMinimum >> 16 );
      l_maximalPage = ( uint32_t ) ( p_table->local->usageMaximum >> 16 );

      /* Si les numéros de page sont différents */
      if ( l_minimalPage != l_maximalPage )
      {
         /* Actualisation du registre d'erreur */
         ( *p_error ) = K_MK_HID_ERROR_INVALID_VALUE_USAGE_PAGE_MIN_MAX;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_checkOutOfRangePhysicalMinMax ( T_mkHIDReportTable* p_table, T_mkHIDReportError* p_error )
{
   /* Si au moins une balise physical est présente et si la valeur minimale est supérieure ou égale à la valeur maximale */
   if ( ( p_table->global.physical == 1 ) && ( p_table->global.physicalMinimum >= p_table->global.physicalMaximum ) )
   {
      /* Actualisation du registre d'erreur */
      ( *p_error ) = K_MK_HID_ERROR_INVALID_VALUE_PHYSICAL_MIN_MAX;
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

static void mk_hid_checkOutOfRangeLogicalMinMax ( T_mkHIDReportTable* p_table, T_mkHIDItem* p_item, T_mkHIDReportError* p_error )
{
   /* Déclaration des variables de travail */
   uint32_t l_size = 0, l_range = 0, l_mask = 0;

   /* Si la valeur minimale est supérieure ou égale à la valeur maximale */
   if ( p_table->global.logicalMinimum >= p_table->global.logicalMaximum )
   {
      /* Ces items sont obligatoires, le parser vérifie la présence des balises avant l'exécution de cette fonction */
      /* La valeur de défaut est donc sans importance. */

      /* Actualisation du registre d'erreur */
      ( *p_error ) = K_MK_HID_ERROR_INVALID_VALUE_LOGICAL_MIN_MAX;
   }

   /* Sinon */
   else
   {
      /* Détermination de la valeur du masque */
      l_mask = ( uint32_t ) ( ~ ( K_MK_HID_MAX_USAGE_RANGE << p_table->global.reportSize ) );

      /* Vérification de la valeur minimale */
      l_range = ( uint32_t ) ( ( uint32_t ) ( ( uint32_t ) p_table->global.logicalMaximum & l_mask ) >> p_table->global.reportSize );

      /* Si la valeur maximale est en dehors de la limite définie par la taille */
      if ( l_range > 0 )
      {
         /* Actualisation du registre d'erreur */
         ( *p_error ) = K_MK_HID_ERROR_INVALID_RANGE_LOGICAL_MAXIMUM;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Vérification de la valeur minimale */
      l_range = ( uint32_t ) ( ( uint32_t ) ( ( uint32_t ) p_table->global.logicalMinimum & l_mask ) >> p_table->global.reportSize );

      /* Si la valeur minimale est en dehors de la limite définie par la taille */
      if ( l_range > 0 )
      {
         /* Actualisation du registre d'erreur */
         ( *p_error ) = K_MK_HID_ERROR_INVALID_RANGE_LOGICAL_MINIMUM;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si l'usage principal n'est pas de type 'Variable' ou 'Constant' */
      if ( ( p_item->value & ( K_MK_HID_ITEM_VARIABLE | K_MK_HID_ITEM_CONSTANT ) ) == 0 )
      {
         /* Détermination du nombre d'usages */
         /* Les fonctions précédentes ont vérifié que 'Usage Maximum' est supérieur à 'Usage Minimum' */
         l_size = p_table->local->usageMaximum - p_table->local->usageMinimum;

         /* Si la valeur logique maximale est inférieure ou égale au nombre maximum d'usages ou négative */
         if ( (p_table->global.logicalMaximum <= ( int32_t ) l_size ) || ( p_table->global.logicalMaximum < 0 ) )
         {
            /* Actualisation du registre d'erreur */
            ( *p_error ) = K_MK_HID_ERROR_INVALID_VALUE_LOGICAL_MAXIMUM;
         }

         /* Sinon si la valeur logique minimale est négative */
         else if ( p_table->global.logicalMinimum < 0 )
         {
            /* Actualisation du registre d'erreur */
            ( *p_error ) = K_MK_HID_ERROR_INVALID_VALUE_LOGICAL_MINIMUM;
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

      /* Si l'usage principal posséde l'attribut 'NULL' */
      if ( ( p_item->value & K_MK_HID_ITEM_NULL_STATE ) == K_MK_HID_ITEM_NULL_STATE )
      {
         /* La valeur nulle doit être en dehors de l'espace logique min-max */
         /* Il est nécessaire d'ajouter un emplaçement mémoire supplémentaire */
         l_range = ( uint32_t ) ( ( p_table->global.logicalMaximum - p_table->global.logicalMinimum ) + 1 );

         /* Détermination de la taille de l'usage */
         l_size = ( uint32_t ) ( 1 << p_table->global.reportSize );

         /* Si l'intervalle min-max est supérieur à la taille de l'usage */
         if ( l_range > l_size )
         {
            /* Actualisation du registre d'erreur */
            ( *p_error ) = K_MK_HID_ERROR_INVALID_RANGE_NULL;
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

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_checkOutOfRange ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'item */
   T_mkHIDItem* l_item;

   /* Déclaration d'une table d'item */
   T_mkHIDReportTable l_itemTable = { { 0 }, K_MK_NULL };

   /* Déclaration d'un stack stockant les items locaux */
   T_mkHIDReportStack l_itemStack;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_error != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du premier item du 'Report Descriptor' */
      l_item = p_hidDevice->reportDescriptor.item;

      /* Initialisation de la stack */
      l_itemStack.top = K_MK_NULL;

      /* Allocation d'une table d'item local */
      l_result = mk_pool_allocSafe ( g_mkHIDPool.itemStatePool, ( T_mkAddr* ) &l_itemTable.local, K_MK_POOL_CLEAR, 0 );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_itemTable.local != K_MK_NULL ) )
      {
         /* Réinitialisation de la table d'item local */
         _writeWords ( l_itemTable.local, 0, sizeof ( T_mkHIDLocalTable ) >> 2 );

         /* Tant que le 'Report Descriptor' n'a pas été analysé et tant qu'aucune erreur n'est détectée */
         while ( ( l_item != K_MK_NULL ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
         {
            /* Actualisation de la table d'item */
            l_result = mk_hid_setItemStateTable ( &l_itemStack, &l_itemTable, l_item );

            /* Si l'item est de type 'Input', 'Output' et 'Feature' */
            if ( ( l_item->head.value & 0xC ) == 0 )
            {
               /* Analyse des balises 'Usage Minimal' et 'Usage Maximal' */
               mk_hid_checkOutOfRangeUsageMinMax ( &l_itemTable, p_error );

               /* Si aucune erreur ne s'est produite */
               if ( p_error == K_MK_HID_NO_ERROR )
               {
                  /* Analyse des balises 'Physical Minimal' et 'Physical Maximal' */
                  mk_hid_checkOutOfRangeStringMinMax ( &l_itemTable, p_error );

                  /* Si aucune erreur ne s'est produite */
                  if ( p_error == K_MK_HID_NO_ERROR )
                  {
                     /* Analyse des balises 'String Minimal' et 'String Maximal' */
                     mk_hid_checkOutOfRangeDesignatorMinMax ( &l_itemTable, p_error );
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

               /* Si aucune erreur ne s'est produite */
               if ( p_error == K_MK_HID_NO_ERROR )
               {
                  /* Si l'item est de type 'Input', 'Output' et 'Feature' */
                  if ( ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_INPUT ) || ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_OUTPUT ) ||
                            ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_FEATURE ) )
                  {
                     /* Analyse des balises 'Physical Minimal' et 'Physical Maximal' */
                     mk_hid_checkOutOfRangePhysicalMinMax ( &l_itemTable, p_error );

                     /* Si aucune erreur ne s'est produite */
                     if ( p_error == K_MK_HID_NO_ERROR )
                     {
                        /* Analyse des balises 'Logical Min' et 'Logical Max' */
                        mk_hid_checkOutOfRangeLogicalMinMax ( &l_itemTable, l_item, p_error );
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

               /* Réinitialisation de la table d'item local */
               _writeWords ( l_itemTable.local, 0, sizeof ( T_mkHIDLocalTable ) >> 2 );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du pointeur d'item */
            l_item = l_item->nextItem;
         }

         /* Désallocation de la table d'item local */
         l_result |= mk_pool_freeSafe ( g_mkHIDPool.itemStatePool, ( T_mkAddr ) l_itemTable.local );
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

