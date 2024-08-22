/**
*
* @copyright Copyright (C) 2018 RENARD Mathieu. All rights reserved.
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
* @file mk_hcd_add.c
* @brief Définition de la fonction mk_hcd_add.
* @date 15 septembre 2018
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_add ( T_mkHCDList* p_list, T_mkHCDDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_list != K_MK_NULL ) && ( p_device != K_MK_NULL ) )
   {
      /* Si la liste est vide */
      if ( p_list->current == K_MK_NULL )
      {
         /* Initialisation du pointeur de périphérique courant */
         /* Le premier périphérique inséré dans la liste doit configurer ces */
         /* attributs "next" et "previous" de manière à ce qu'il pointe sur */
         /* lui même. */
         p_list->current = p_device;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Mise à jour des pointeurs "next" et "previous" du périphérique */
      /* Le nouveau périphérique est placé avant le pointeur p_list->current. */
      p_device->previous = p_list->current->previous;
      p_device->next = p_list->current;

      /* Mise à jour des pointeurs "next" et "previous" du périphérique */
      /* pointé par la liste */
      p_list->current->previous->next = p_device;
      p_list->current->previous = p_device;
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


