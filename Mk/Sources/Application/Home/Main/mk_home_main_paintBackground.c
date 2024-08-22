/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_home_main_paintBackground.c
* @brief Définition de la fonction mk_home_main_paintBackground.c.
* @date 19 juil. 2024
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_home_main_paintBackground ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'adresse du bouton */
   T_mkButtonImage* l_buttonImage = p_field->child;

   /* Exécution de la fonction de peinture par défaut */
   l_result = mk_buttonImage_defaultPainter ( p_container, p_field, p_frameNumber );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_buttonImage->bitmap != K_MK_NULL ) && ( l_buttonImage->bitmap->file != K_MK_NULL ) && ( l_buttonImage->bitmap->baseAddr != K_MK_NULL ) )
   {
      /* Désactivation du rafraichissement */
      mk_field_setRefresh ( p_field, K_MK_FIELD_REFRESH_DISABLED );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result);
}



