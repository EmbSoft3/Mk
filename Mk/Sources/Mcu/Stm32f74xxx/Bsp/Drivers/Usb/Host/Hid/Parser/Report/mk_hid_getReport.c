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
* @file mk_hid_getReport.c
* @brief Définition de la fonction mk_hid_getReport.
* @date 2 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_initReport ( T_mkHIDReport* p_report, T_mkHIDItem* p_item )
{
   /* Enregistrement de l'adresse de l'item  */
   p_report->first = p_item;

   /* Réinitialisation de la taille du 'Report' */
   p_report->inputSize = 0;
   p_report->outputSize = 0;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_hid_setReportSize ( uint32_t* p_size, uint32_t p_reportID )
{
   /* Récupération de la taille du report */
   uint32_t l_size = *p_size;

   /* Si des champs de type 'INPUT' sont présents */
   if ( l_size != 0 )
   {
      /* Si un identifiant est associé au 'Report' */
      if ( p_reportID != 0 )
      {
         /* Actualisation de la taille du 'Report' */
         /* Le 'ReportID' a une taille fixe de 8bits */
         l_size = ( uint32_t ) ( l_size + 8 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Conversion du nombre de bits en octets */
      /* Le 'Report' doit être aligné sur 8bits */
      l_size = l_size >> 3;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_size );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_setReportAttribute ( T_mkHIDReport* p_report, T_mkHIDItem* p_item, uint32_t p_reportID )
{
   /* Enregistrement de l'adresse de l'item  */
   p_report->last = p_item;

   /* Enregistrement de l'identifiant du 'ReportID' */
   p_report->id = p_reportID;

   /* Configuration de la taille des champs 'Input' */
   p_report->inputSize = mk_hid_setReportSize ( &p_report->inputSize, p_reportID );

   /* Configuration de la taille des champs 'Output' */
   p_report->outputSize = mk_hid_setReportSize ( &p_report->outputSize, p_reportID );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_getReportAttribute ( T_mkHIDReport* p_report, T_mkHIDItem* p_item, uint32_t* p_reportID, uint32_t* p_reportSize, uint32_t* p_reportCount )
{
   /* Si l'item courant contient l'identification d'un REPORT_ID */
   if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_REPORT_ID )
   {
      /* Basculement d'un verrou afin d'inclure la taille du 'ReportID' dans la taille du 'Report' */
      *p_reportID = p_item->value;
   }

   /* Sinon si l'item courant contient la définition d'un REPORT_SIZE */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_REPORT_SIZE )
   {
      /* Enregistrement de la taille du champ */
      *p_reportSize = p_item->value;
   }

   /* Sinon si l'item courant contient la définition d'un REPORT_COUNT */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_REPORT_COUNT )
   {
      /* Enregistrement du nombre de champs */
      *p_reportCount = p_item->value;
   }

   /* Sinon si l'item courant contient la définition d'un champ de type INPUT */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_INPUT )
   {
      /* Actualisation de la taille du 'Report' */
      p_report->inputSize = ( uint32_t ) ( p_report->inputSize + ( ( *p_reportSize ) * ( *p_reportCount ) ) );
   }

   /* Sinon si l'item courant contient la définition d'un champ de type OUTPUT */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_OUTPUT )
   {
      /* Actualisation de la taille du 'Report' */
      p_report->outputSize = ( uint32_t ) ( p_report->outputSize + ( ( *p_reportSize ) * ( *p_reportCount ) ) );
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

T_mkCode mk_hid_getReport ( T_mkHIDDevice* p_hidDevice, T_mkHIDReport* p_report, uint32_t p_index )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un item */
   T_mkHIDItem* l_item;

   /* Déclaration d'une variable stockant le niveau d'imbrication recherché */
   uint32_t l_nestedLevel = 0;

   /* Déclaration du compteur d'imbrication, du compteur d'offset et d'un verrou */
   uint32_t l_nestedCounter = 0, l_offset = 0, l_lock = 0;

   /* Déclaration des variables stockant la valeur des attributs 'ReportSize', 'ReportCount' et 'ReportID' */
   uint32_t l_reportSize = 0, l_reportCount = 0, l_reportID = 0;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_report != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du premier item contenu dans le 'ReportDescriptor' */
      l_item = p_hidDevice->reportDescriptor.item;

      /* Tant que tout les items n'ont pas été analysés ou tant que */
      /* le 'report' n'a pas été récupéré */
      while ( ( l_item != K_MK_NULL ) && ( l_lock != 2 ) )
      {
         /* Si le report rencontrée doit être récupérée */
         if ( ( l_nestedCounter == l_nestedLevel ) && ( l_offset == p_index ) && ( l_lock == 0 ) )
         {
            /* Initialisation des attributs du 'Report' */
            mk_hid_initReport ( p_report, l_item );

            /* Bascullement du verrou */
            l_lock = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si l'item courant délimite le début d'une collection */
         if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_COLLECTION )
         {
            /* Actualisation du compteur d'imbrication */
            l_nestedCounter++;
         }

         /* Sinon si l'item courant délimite la fin d'une collection */
         else if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_END_COLLECTION )
         {
            /* Actualisation du compteur d'imbrication */
            l_nestedCounter--;

            /* Si le report a été entièrement récupérée */
            if ( ( l_nestedCounter == l_nestedLevel ) && ( l_offset == p_index ) && ( l_lock == 1 ) )
            {
               /* Configuration des attributs du Report */
               mk_hid_setReportAttribute ( p_report, l_item, l_reportID );

               /* Basculement du verrou */
               l_lock = 2;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Si le niveau d'imbrication de la collection courante est le niveau recherché */
            if ( l_nestedCounter == l_nestedLevel )
            {
               /* Actualisation de l'offset */
               l_offset++;
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

         /* Actualisation de la valeur des attributs intermédiaires du report */
         mk_hid_getReportAttribute ( p_report, l_item, &l_reportID, &l_reportSize, &l_reportCount );

         /* Actualisation de l'adresse de l'item courant */
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



