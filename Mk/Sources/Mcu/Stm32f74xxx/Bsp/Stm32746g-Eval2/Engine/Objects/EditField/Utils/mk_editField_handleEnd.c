/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_editField_handleEnd.c
* @brief Définition de la fonction mk_editField_handleEnd.
* @date 7 févr. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_editField_handleEnd ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_numberOfRow = 0;

   /* Déclaration d'une variable stockant le vecteur de travail DOWN_RIGHT */
   T_mkVect2D l_vectDownRight = { 0, 0 };

   /* Déclaration des variables stockant les vecteurs de travail TOP_LEFT et DOWN_RIGHT */
   T_mkVect2Di l_2DiTopLeft = { 0, 0 }, l_2DiBottomRight = { 0, 0 };

   /* Configuration du vecteur DOWN_RIGHT */
   mk_vect2d_setCoord ( &l_vectDownRight, p_editField->field.position.x + ( real32_t ) p_editField->field.dimension.width, p_editField->field.position.y + ( real32_t ) p_editField->field.dimension.height );

   /* Détermination des attributs de la boite d'édition */
   l_result = mk_editField_setAttribute ( p_editField, p_editField->field.position, l_vectDownRight, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Récupération du nombre de lignes à dessiner en fonction de la taille de la fenêtre */
      l_numberOfRow =
            mk_display_utils_getWindowCurrentNumberOfLines ( p_editField->style.font, p_editField->strAddr, 0xFFFFFFFF, ( uint32_t ) p_editField->style.fontEncoding, ( uint32_t ) ( l_2DiBottomRight.x - l_2DiTopLeft.x ) );

      /* Si la taille de la fenêtre est inférieure au nombre total de lignes */
      if ( p_editField->windowNumberOfRow < l_numberOfRow )
      {
         /* Actualisation de l'offset de la prochaine ligne */
         p_editField->windowFirstRowIndex = ( l_numberOfRow - p_editField->windowNumberOfRow );

         /* Actualisation de l'adresse de base de la fenêtre */
         p_editField->windowBaseAddr = mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex, &p_editField->cursorBaseOffset );

         /* Actualisation de l'offset de base de la fenêtre */
         p_editField->windowBaseOffset = ( uint32_t ) ( ( T_str8 ) p_editField->windowBaseAddr - ( T_str8 ) p_editField->strAddr );
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


