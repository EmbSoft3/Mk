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
* @file mk_hid_parseAlternate.c
* @brief Définition de la fonction mk_hid_parseAlternate.
* @date 11 nov. 2019
*
*/

#include "mk_hid_api.h"


/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_parseAlternate ( T_mkHIDDevice* p_hidDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'item */
   T_mkHIDItem* l_item;

   /* Déclaration d'un pointeur d'item stockant l'adresse d'un usage principal */
   T_mkHIDItem* l_mainAlternateItem = K_MK_NULL;

   /* Si le paramètre est valide */
   if ( p_hidDevice != K_MK_NULL )
   {
      /* Récupération de l'adresse du premier item contenu dans le 'Report Descriptor' */
      l_item = p_hidDevice->reportDescriptor.item;

      /* Tant que l'analyse du 'Report Descriptor' n'est pas terminée */
      while ( l_item != K_MK_NULL )
      {
         /* Si l'item courant est un item de type DELIMITER */
         if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_DELIMITER )
         {
            /* Si ouverture d'une page d'usage alternatif */
            if ( l_item->value == 1 )
            {
               /* Une page d'usage alternatif vient de s'ouvrir. */
               /* Le but est d'enlever de la liste principal l'intégralité des usages alternatifs. */
               /* Afin de ne pas perdre d'information, ils sont mappés sur le pointeur 'nextAlternate' de */
               /* l'usage principal */

               /* Enregistrement de l'adresse de l'usage principal */
               l_mainAlternateItem = l_item->nextItem;

               /* Mapping de l'adresse du premier usage alternatif dans l'usage principale */
               /* L'usage principal est l'usage qui suit directement la balise. Le premier usage alternatif */
               /* est l'usage qui suit directement l'usage principal. */
               l_mainAlternateItem->nextAlternate = l_mainAlternateItem->nextItem;
            }

            /* Sinon */
            else
            {
               /* A ce stade la chaine est constituée d'un item OPEN_DELIMITER et de l'usage principal */
               /* Il est temps d'actualiser le pointeur 'nextItem' de l'usage principal pour qu'il pointe */
               /* sur l'item CLOSE_DELIMITER. */

               /* Si une page d'usage alternatif a été ouverte */
               if ( l_mainAlternateItem != K_MK_NULL )
               {
                  /* Réinitialisation du pointeur d'usage principal */
                  l_mainAlternateItem->nextItem = l_item;

                  /* On actualise le pointeur d'item afin qu'il pointe sur le premier usage alternatif */
                  l_mainAlternateItem = l_mainAlternateItem->nextAlternate;

                  /* La valeur nulle doit aussi être ajoutée à la fin des usages alternatifs afin de terminer */
                  /* la chaine. */
                  /* On parcourt donc la chaine tant que la valeur du prochain item est différente de */
                  /* CLOSE_DELIMITER */
                  while ( l_mainAlternateItem->nextItem != l_item )
                  {
                     /* Actualisation de la valeur de l'item */
                     l_mainAlternateItem = l_mainAlternateItem->nextItem;
                  }

                  /* Finalisation de la chaine */
                  l_mainAlternateItem->nextItem = K_MK_NULL;
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


