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
* @file mk_hid_getReportNumber.c
* @brief Définition de la fonction mk_hid_getReportNumber.
* @date 2 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_getReportNumber ( T_mkHIDDevice* p_hidDevice, uint32_t* p_reportNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un item */
   T_mkHIDItem* l_item;

   /* Déclaration des compteurs */
   uint32_t l_nestedCounter = 0, l_counter = 0;

   /* Déclaration d'une variable stockant le niveau d'imbrication recherché */
   uint32_t l_nestedLevel = 0;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_reportNumber != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du premier item contenu dans le 'ReportDescriptor' */
      l_item = p_hidDevice->reportDescriptor.item;

      /* Tant que tout les items n'ont pas été analysés */
      while ( l_item != K_MK_NULL )
      {
         /* Si l'item courant marque le début d'une collection */
         if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_COLLECTION )
         {
            /* Si la collection est de niveau égale à 'p_nestedLevel' */
            if ( l_nestedCounter == l_nestedLevel )
            {
               /* Actualisation du compteur de 'Report' */
               l_counter++;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du compteur d'imbrication */
            l_nestedCounter++;
         }

         /* Sinon si l'item courant marque la fin d'une collection */
         else if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_END_COLLECTION )
         {
            /* Actualisation du compteur d'imbrication */
            l_nestedCounter--;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation de l'adresse de l'item courant */
         l_item = l_item->nextItem;
      }

      /* Initialisation du compteur de 'report' */
      *p_reportNumber = l_counter;
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


