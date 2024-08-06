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
* @file mk_hid_button_create.c
* @brief Définition de la fonction mk_hid_button_create.
* @date 10 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_button_create ( T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_buttonNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de bouton */
   T_mkButton** l_button = K_MK_NULL;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Si les paramètres sont valides */
   if ( ( p_table != K_MK_NULL ) && ( p_usage != K_MK_NULL ) )
   {
      /* Si les 'n' boutons peuvent être alloués */
      if ( ( p_buttonNumber <= K_MK_BUTTON_NUMBER ) )
      {
         /* Récupération de l'adresse d'allocation de l'objet */
         l_button = ( T_mkButton** ) &p_usage->first->addr;

         /* Configuration de la taille de destination */
         p_usage->first->head.field.destinationSize = 16;

         /* Pour le nombre de boutons à allouer */
         for ( l_counter = 0 ; ( l_counter < p_buttonNumber ) && ( l_result == K_MK_OK ) ; l_counter++ )
         {
            /* Allocation d'un bouton */
            l_result = mk_pool_allocSafe ( g_mkButtonPool.pool, ( T_mkAddr* ) l_button, K_MK_POOL_CLEAR, 0 );

            /* Si aucune erreur ne s'est produite */
            if ( ( l_result == K_MK_OK ) && ( ( *l_button ) != K_MK_NULL ) )
            {
               /* Si plusieurs boutons doivent être alloués */
               if ( p_buttonNumber != 1 )
               {
                  /* L'allocation a été provoqué par la détection des balises 'Usage Minimum' et 'Usage Maximum' */
                  /* L'identifiant de départ est donc égale à 'Usage Minimum' */

                  /* Configuration de l'identifiant du bouton */
                  ( *l_button )->layer.id = ( uint16_t ) ( ( uint16_t ) ( p_table->local->usageMinimum ) + ( uint16_t ) l_counter );
               }

               /* Sinon */
               else
               {
                  /* L'allocation a été provoqué par la détection d'une balise 'Usage' */
                  /* L'identifiant est donc contenu dans la valeur de la structure p_usage */

                  /* Configuration de l'identifiant du bouton */
                  ( *l_button )->layer.id = ( uint16_t ) ( p_usage->first->value & 0xFFFF );
               }

               /* Configuration du type du bouton */
               l_result = mk_hid_button_setType ( *l_button, p_table, p_usage );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du pointeur de bouton */
            l_button = &( *l_button )->nextButton;
         }

         /* Si l'allocation de 'n' boutons a échoué */
         if ( l_result != K_MK_OK )
         {
            /* Récupération de l'adresse d'allocation du premier objet */
            l_button = ( T_mkButton** ) &p_usage->first->addr;

            /* Pour l'ensemble des boutons à désallouer */
            while ( ( l_counter != 0 ) && ( ( *l_button ) != K_MK_NULL ) )
            {
               /* Désallocation du bouton courant */
               l_result |= mk_pool_freeSafe ( g_mkButtonPool.pool, ( *l_button ) );

               /* Actualisation du pointeur de bouton */
               l_button = &( *l_button )->nextButton;

               /* Actualisation du compteur de bouton */
               l_counter = l_counter - 1;
            }

            /* L'intégralité des boutons ne peuvent pas être alloués */
            /* Il est nécessaire d'actualiser l'adresse de l'usage */
            p_usage->first->addr = K_MK_NULL;
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
         /* L'intégralité des boutons ne peuvent pas être alloués */
         /* Ceci n'est pas une erreur, on actualise donc le champ 'addr' pour ignorer l'usage */
         p_usage->first->addr = K_MK_NULL;
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



