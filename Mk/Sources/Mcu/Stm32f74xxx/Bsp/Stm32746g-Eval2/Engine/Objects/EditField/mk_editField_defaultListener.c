/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_editField_defaultListener.c
* @brief Définition de la fonction mk_editField_defaultListener.
* @date 2 déc. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleRightArrow ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant la longueur de la chaine de caractères */
   uint32_t l_length = 0;

   /* Déclaration d'une variable indiquant si le curseur est dans la fenêtre affichable ou non */
   uint32_t l_inside = 0;

   /* Déclaration d'une variable stockant le vecteur de travail DOWN_RIGHT */
   T_mkVect2D l_vectDownRight = { 0, 0 };

   /* Déclaration des variables stockant les vecteurs de travail TOP_LEFT et DOWN_RIGHT */
   T_mkVect2Di l_2DiTopLeft = { 0, 0 }, l_2DiBottomRight = { 0, 0 };

   /* Récupération de la longueur de la chaine de caractères */
   l_length = mk_utils_utflen ( ( T_str8 ) p_editField->strAddr, p_editField->style.fontEncoding );

   /* Si le curseur n'est pas sur le dernier caractère de la chaine */
   if ( p_editField->cursorBaseOffset < l_length )
   {
      /* Actualisation de la position du curseur */
      p_editField->cursorBaseOffset = ( uint32_t ) ( p_editField->cursorBaseOffset + 1 );

      /* Configuration de la valeur du vecteur DOWN_RIGHT */
      mk_vect2d_setCoord ( &l_vectDownRight, p_editField->field.position.x + ( real32_t ) p_editField->field.dimension.width, p_editField->field.position.y + ( real32_t ) p_editField->field.dimension.height );

      /* Récupération des attributs de la boite d'édition */
      l_result = mk_editField_setAttribute ( p_editField, p_editField->field.position, l_vectDownRight, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Inhibition du clignotement du curseur pendant 60 trames */
         p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;

         /* Détermination de la position du curseur dans la fenêtre */
         l_inside = mk_editField_inside ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->windowBaseAddr, p_editField->cursorBaseOffset );

         /* Si le curseur est situé à l'extérieur de la fenêtre */
         if ( ( l_inside == 0 ) && ( p_editField->windowCurrentNumberOfRow == p_editField->windowNumberOfRow ) )
         {
            /* Actualisation de l'index de la prochaine ligne */
            p_editField->windowFirstRowIndex = ( p_editField->windowFirstRowIndex + 1 );

            /* Actualisation de l'adresse et de l'offset de la fenêtre */
            p_editField->windowBaseAddr = mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex, &p_editField->windowBaseOffset );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleLeftArrow ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable indiquant si le curseur est dans la fenêtre affichable ou non */
   uint32_t l_inside = 0;

   /* Déclaration d'une variable stockant le vecteur de travail DOWN_RIGHT */
   T_mkVect2D l_vectDownRight = { 0, 0 };

   /* Déclaration des variables stockant les vecteurs de travail TOP_LEFT et DOWN_RIGHT */
   T_mkVect2Di l_2DiTopLeft = { 0, 0 }, l_2DiBottomRight = { 0, 0 };

   /* Si le curseur n'est pas sur le premier caractère de la chaine */
   if ( p_editField->cursorBaseOffset > 0 )
   {
      /* Actualisation de la position du curseur */
      p_editField->cursorBaseOffset = ( uint32_t ) ( p_editField->cursorBaseOffset - 1 );

      /* Configuration de la valeur du vecteur DOWN_RIGHT */
      mk_vect2d_setCoord ( &l_vectDownRight, p_editField->field.position.x + ( real32_t ) p_editField->field.dimension.width, p_editField->field.position.y + ( real32_t ) p_editField->field.dimension.height );

      /* Récupération des attributs de la boite d'édition */
      l_result = mk_editField_setAttribute ( p_editField, p_editField->field.position, l_vectDownRight, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Inhibition du clignotement du curseur pendant 60 trames */
         p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;

         /* Détermination de la position du curseur dans la fenêtre */
         l_inside = mk_editField_inside ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->windowBaseAddr, p_editField->cursorBaseOffset );

         /* Si le curseur est situé à l'extérieur de la fenêtre */
         if ( l_inside == 0 )
         {
            /* Actualisation de l'offset de la prochaine ligne */
            p_editField->windowFirstRowIndex = ( p_editField->windowFirstRowIndex - 1 );

            /* Actualisation de l'adresse et de l'offset de la fenêtre */
            p_editField->windowBaseAddr = mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex, &p_editField->windowBaseOffset );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleDownArrow ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable indiquant si le curseur est dans la fenêtre affichable ou non */
   uint32_t l_inside = 0;

   /* Déclaration d'une variable contenant la taille de la chaine de caractères */
   uint32_t l_length = 0;

   /* Déclaration d'une variable stockant le vecteur de travail DOWN_RIGHT */
   T_mkVect2D l_vectDownRight = { 0, 0 };

   /* Déclaration des variables stockant les vecteurs TOP_LEFT, DOWN_RIGHT et la position du curseur. */
   T_mkVect2Di l_2DiTopLeft = { 0, 0 }, l_2DiBottomRight = { 0, 0 }, l_cursorVector = { 0, 0 };

   /* Récupération de la longueur de la chaine de caractères */
   l_length = mk_utils_utflen ( ( T_str8 ) p_editField->strAddr, p_editField->style.fontEncoding );

   /* Si le curseur n'est pas sur le dernier caractère de la chaine */
   if ( p_editField->cursorBaseOffset < l_length )
   {
      /* Configuration du vecteur DOWN_RIGHT */
      mk_vect2d_setCoord ( &l_vectDownRight, p_editField->field.position.x + ( real32_t ) p_editField->field.dimension.width, p_editField->field.position.y + ( real32_t ) p_editField->field.dimension.height );

      /* Récupération des attributs de la boite d'édition */
      l_result = mk_editField_setAttribute ( p_editField, p_editField->field.position, l_vectDownRight, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Inhibition du clignotement du curseur pendant 60 trames */
         p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;

         /* Mise à jour de la position du curseur */
         mk_editField_setCursorVector ( p_editField, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

         /* Configuration du vecteur stockant les coordonnées du curseur sur la prochaine ligne */
         mk_vect2d_setCoord2Di ( &l_cursorVector, p_editField->cursorVect.x, p_editField->cursorVect.y + ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) );

         /* Détermination de la prochaine position du curseur */
         p_editField->cursorBaseOffset = mk_editField_getCursorOffsetDown ( p_editField, l_2DiTopLeft, l_2DiBottomRight, l_cursorVector, p_editField->windowBaseAddr );

         /* Détermination de la position du curseur dans la fenêtre */
         l_inside = mk_editField_inside ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->windowBaseAddr, p_editField->cursorBaseOffset );

         /* Si le curseur est situé à l'extérieur de la fenêtre */
         if ( ( l_inside == 0 ) && ( p_editField->windowCurrentNumberOfRow == p_editField->windowNumberOfRow ) )
         {
            /* Actualisation de l'offset de la prochaine ligne */
            p_editField->windowFirstRowIndex = ( p_editField->windowFirstRowIndex + 1 );

            /* Actualisation de l'adresse et de l'offset de la fenêtre */
            p_editField->windowBaseAddr = mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex, &p_editField->windowBaseOffset );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleUpArrow ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable indiquant si le curseur est dans la fenêtre affichable ou non */
   uint32_t l_inside = 0;

   /* Déclaration d'une variable stockant le vecteur de travail DOWN_RIGHT */
   T_mkVect2D l_vectDownRight = { 0, 0 };

   /* Déclaration des variables stockant les vecteurs TOP_LEFT, DOWN_RIGHT et la position du curseur. */
   T_mkVect2Di l_2DiTopLeft = { 0, 0 }, l_2DiBottomRight = { 0, 0 }, l_cursorVector = { 0, 0 };

   /* Configuration du vecteur DOWN_RIGHT */
   mk_vect2d_setCoord ( &l_vectDownRight, p_editField->field.position.x + ( real32_t ) p_editField->field.dimension.width, p_editField->field.position.y + ( real32_t ) p_editField->field.dimension.height );

   /* Récupération des attributs de la boite d'édition */
   l_result = mk_editField_setAttribute ( p_editField, p_editField->field.position, l_vectDownRight, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Inhibition du clignotement du curseur pendant 60 trames */
      p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;

      /* Mise à jour de la position du curseur */
      mk_editField_setCursorVector ( p_editField, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

      /* Configuration du vecteur stockant les coordonnées du curseur */
      mk_vect2d_setCoord2Di ( &l_cursorVector, p_editField->cursorVect.x, p_editField->cursorVect.y );

      /* Détermination de la prochaine position du curseur */
      p_editField->cursorBaseOffset = mk_editField_getCursorOffsetUp ( p_editField, l_2DiTopLeft, l_2DiBottomRight, l_cursorVector, p_editField->strAddr, p_editField->windowFirstRowIndex );

      /* Détermination de la position du curseur dans la fenêtre */
      l_inside = mk_editField_inside ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->windowBaseAddr, p_editField->cursorBaseOffset );

      /* Si le curseur est situé à l'extérieur de la fenêtre */
      if ( ( l_inside == 0 ) && ( p_editField->windowFirstRowIndex != 0 ) )
      {
         /* Actualisation de l'offset de la prochaine ligne */
         p_editField->windowFirstRowIndex = ( p_editField->windowFirstRowIndex - 1 );

         /* Actualisation de l'adresse de base de la fenêtre */
         p_editField->windowBaseAddr = mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex, &p_editField->windowBaseOffset );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_editField_handleStart ( T_mkEditField* p_editField )
{
   /* Actualisation de la position du curseur */
   p_editField->cursorBaseOffset = 0;

   /* Actualisation de l'offset de la prochaine ligne */
   p_editField->windowFirstRowIndex = 0;

   /* Actualisation de l'adresse de base de la fenêtre */
   p_editField->windowBaseAddr = p_editField->strAddr;

   /* Actualisation de l'offset de base de la fenêtre */
   p_editField->windowBaseOffset = 0;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleWheelDown ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable indiquant si le curseur est dans la fenêtre affichable ou non */
   uint32_t l_inside = 0;

   /* Déclaration d'une variable stockant le vecteur de travail DOWN_RIGHT */
   T_mkVect2D l_vectDownRight = { 0, 0 };

   /* Déclaration des variables stockant les vecteurs de travail TOP_LEFT et DOWN_RIGHT */
   T_mkVect2Di l_2DiTopLeft = { 0, 0 }, l_2DiBottomRight = { 0, 0 }, l_cursorVector = { 0, 0 };

   /* Configuration du vecteur DOWN_RIGHT */
   mk_vect2d_setCoord ( &l_vectDownRight, p_editField->field.position.x + ( real32_t ) p_editField->field.dimension.width, p_editField->field.position.y + ( real32_t ) p_editField->field.dimension.height );

   /* Détermination des attributs de la boite d'édition */
   l_result = mk_editField_setAttribute ( p_editField, p_editField->field.position, l_vectDownRight, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Inhibition du clignotement du curseur pendant 60 trames */
      p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;

      /* Mise à jour de la position du curseur */
      mk_editField_setCursorVector ( p_editField, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

      /* Configuration du vecteur stockant les coordonnées du curseur sur la prochaine ligne */
      mk_vect2d_setCoord2Di ( &l_cursorVector, p_editField->cursorVect.x, p_editField->cursorVect.y + ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) );

      /* Détermination de la prochaine position du curseur */
      p_editField->cursorBaseOffset = mk_editField_getCursorOffsetDown ( p_editField, l_2DiTopLeft, l_2DiBottomRight, l_cursorVector, p_editField->windowBaseAddr );

      /* Détermination de la position du curseur dans la fenêtre */
      l_inside = mk_editField_inside ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->windowBaseAddr, p_editField->cursorBaseOffset );

      /* Si le curseur est situé à l'extérieur de la fenêtre */
      if ( ( l_inside == 0 ) && ( p_editField->windowCurrentNumberOfRow == p_editField->windowNumberOfRow ) )
      {
         /* Actualisation de l'offset de la prochaine ligne */
         p_editField->windowFirstRowIndex = ( p_editField->windowFirstRowIndex + 1 );

         /* Actualisation de l'adresse et de l'offset de la fenêtre */
         p_editField->windowBaseAddr = mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex, &p_editField->windowBaseOffset );
      }

      /* Sinon */
      else
      {
         /* Actualisation de l'adresse de base de la fenêtre */
         ( void ) mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex + p_editField->windowNumberOfRow - 1, &p_editField->cursorBaseOffset );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleWheelUp ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable indiquant si le curseur est dans la fenêtre affichable ou non */
   uint32_t l_inside = 0;

   /* Déclaration d'une variable stockant le vecteur de travail DOWN_RIGHT */
   T_mkVect2D l_vectDownRight = { 0, 0 };

   /* Déclaration des variables stockant les vecteurs de travail TOP_LEFT et DOWN_RIGHT */
   T_mkVect2Di l_2DiTopLeft = { 0, 0 }, l_2DiBottomRight = { 0, 0 }, l_cursorVector = { 0, 0 };

   /* Configuration du vecteur DOWN_RIGHT */
   mk_vect2d_setCoord ( &l_vectDownRight, p_editField->field.position.x + ( real32_t ) p_editField->field.dimension.width, p_editField->field.position.y + ( real32_t ) p_editField->field.dimension.height );

   /* Détermination des attributs de la boite d'édition */
   l_result = mk_editField_setAttribute ( p_editField, p_editField->field.position, l_vectDownRight, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Inhibition du clignotement du curseur pendant 60 trames */
      p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;

      /* Mise à jour de la position du curseur */
      mk_editField_setCursorVector ( p_editField, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

      /* Configuration du vecteur stockant les coordonnées du curseur */
      mk_vect2d_setCoord2Di ( &l_cursorVector, p_editField->cursorVect.x, p_editField->cursorVect.y );

      /* Détermination de la prochaine position du curseur */
      p_editField->cursorBaseOffset = mk_editField_getCursorOffsetUp ( p_editField, l_2DiTopLeft, l_2DiBottomRight, l_cursorVector, p_editField->strAddr, p_editField->windowFirstRowIndex );

      /* Détermination de la position du curseur dans la fenêtre */
      l_inside = mk_editField_inside ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->windowBaseAddr, p_editField->cursorBaseOffset );

      /* Si le curseur est situé sur la première ligne de la fenêtre */
      if ( ( l_inside == 0 ) && ( p_editField->windowFirstRowIndex != 0 ) )
      {
         /* Actualisation de l'offset de la prochaine ligne */
         p_editField->windowFirstRowIndex = ( p_editField->windowFirstRowIndex - 1 );

         /* Actualisation de l'adresse et de l'offset de la fenêtre */
         p_editField->windowBaseAddr = mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex, &p_editField->windowBaseOffset );
      }

      /* Sinon */
      else
      {
         /* Actualisation de l'adresse de base de la fenêtre */
         p_editField->windowBaseAddr = mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex, &p_editField->cursorBaseOffset );

         /* Actualisation de l'offset de base de la fenêtre */
         p_editField->windowBaseOffset = ( uint32_t ) p_editField->cursorBaseOffset;
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handlePageUp ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

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
      /* Inhibition du clignotement du curseur pendant 60 trames */
      p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;

      /* Si la taille de la fenêtre est inférieure au nombre total de lignes */
      if ( p_editField->windowFirstRowIndex > p_editField->windowNumberOfRow )
      {
         /* Actualisation de l'offset de la prochaine ligne */
         p_editField->windowFirstRowIndex = ( p_editField->windowFirstRowIndex - p_editField->windowNumberOfRow );
      }

      /* Sinon */
      else
      {
         /* Actualisation de l'offset de la prochaine ligne */
         p_editField->windowFirstRowIndex = 0;
      }

      /* Actualisation de l'adresse de base de la fenêtre */
      p_editField->windowBaseAddr = mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex, &p_editField->cursorBaseOffset );

      /* Actualisation de l'offset de base de la fenêtre */
      p_editField->windowBaseOffset = ( uint32_t ) p_editField->cursorBaseOffset;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handlePageDown ( T_mkEditField* p_editField )
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
      /* Inhibition du clignotement du curseur pendant 60 trames */
      p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;

      /* Récupération du nombre de lignes à dessiner en fonction de la taille de la fenêtre */
      l_numberOfRow =
            mk_display_utils_getWindowCurrentNumberOfLines ( p_editField->style.font, p_editField->strAddr, 0xFFFFFFFF, ( uint32_t ) p_editField->style.fontEncoding, ( uint32_t ) ( l_2DiBottomRight.x - l_2DiTopLeft.x ) );

      /* Si la taille de la fenêtre est inférieure au nombre total de lignes */
      if ( ( uint32_t ) ( p_editField->windowFirstRowIndex + p_editField->windowNumberOfRow + 1 ) <= l_numberOfRow )
      {
         /* Actualisation de l'offset de la prochaine ligne */
         p_editField->windowFirstRowIndex = ( uint32_t ) ( p_editField->windowFirstRowIndex + p_editField->windowNumberOfRow );

         /* Actualisation de l'adresse de base de la fenêtre */
         p_editField->windowBaseAddr = mk_editField_getWindowAddr ( p_editField, l_2DiTopLeft, l_2DiBottomRight, p_editField->strAddr, p_editField->windowFirstRowIndex, &p_editField->cursorBaseOffset );

         /* Actualisation de l'offset de base de la fenêtre */
         p_editField->windowBaseOffset = ( uint32_t ) p_editField->cursorBaseOffset;
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleMousePress ( T_mkEditField* p_editField, T_mkAxis2* p_mouseAxis )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable contenant la taille de la chaine de caractères */
   uint32_t l_length = 0;

   /* Déclaration d'une variable contenant la valeur de la coordonnée y fonction de l'alignement */
   uint32_t l_y = 0;

   /* Déclaration d'une variable contenant la valeur de la coordonnée y de la souris */
   uint32_t l_mouseY = ( uint32_t ) p_mouseAxis->y;

   /* Déclaration d'une variable stockant le vecteur de travail DOWN_RIGHT */
   T_mkVect2D l_vectDownRight = { 0, 0 };

   /* Déclaration des variables stockant les vecteurs TOP_LEFT, DOWN_RIGHT et la position du curseur. */
   T_mkVect2Di l_2DiTopLeft = { 0, 0 }, l_2DiBottomRight = { 0, 0 }, l_cursorVector = { 0, 0 };

   /* Récupération de la longueur de la chaine de caractères */
   l_length = mk_utils_utflen ( ( T_str8 ) p_editField->strAddr, p_editField->style.fontEncoding );

   /* Si le curseur n'est pas sur le dernier caractère de la chaine */
   if ( p_editField->cursorBaseOffset <= l_length )
   {
      /* Configuration du vecteur DOWN_RIGHT */
      mk_vect2d_setCoord ( &l_vectDownRight, p_editField->field.position.x + ( real32_t ) p_editField->field.dimension.width, p_editField->field.position.y + ( real32_t ) p_editField->field.dimension.height );

      /* Récupération des attributs de la boite d'édition */
      l_result = mk_editField_setAttribute ( p_editField, p_editField->field.position, l_vectDownRight, &l_2DiTopLeft, &l_2DiBottomRight, p_editField->windowBaseAddr );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si la chaine de caractères doit être centrée sur l'axe verticale */
         if ( p_editField->style.verticalAlignment == K_MK_TEXT_CENTER_JUSTIFIED )
         {
            /* Détermination de la valeur de la coordonnée y */
            l_y = ( uint32_t ) ( l_2DiTopLeft.y + ( ( ( l_2DiBottomRight.y - l_2DiTopLeft.y ) -
                  ( p_editField->windowCurrentNumberOfRow * ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) ) - ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) >> 1 ) );
         }

         /* Sinon si la chaine de caractères doit être justifiée à droite sur l'axe vertical */
         else if ( p_editField->style.verticalAlignment == K_MK_TEXT_DOWN_JUSTIFIED )
         {
            /* Détermination de la valeur de la coordonnée y */
            l_y = ( uint32_t ) ( l_2DiBottomRight.y -
                  ( p_editField->windowCurrentNumberOfRow * ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) ) + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows );
         }

         /* Sinon (équivalent K_MK_TEXT_TOP_JUSTIFIED) */
         else
         {
            /* Détermination de la valeur de la coordonnée y */
            l_y = ( uint32_t ) ( l_2DiTopLeft.y );
         }

         /* Si la coordonnée du clic est sur une zone affichable */
         if ( l_mouseY < l_y )
         {
            /* Le curseur sera positionné sur la première ligne */
            l_mouseY = l_y;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Configuration du vecteur stockant les coordonnées du curseur sur la prochaine ligne */
         mk_vect2d_setCoord2Di ( &l_cursorVector, ( uint32_t ) p_mouseAxis->x, l_y +
                                 ( uint32_t ) ( ( ( ( uint32_t ) l_mouseY - l_y ) / ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) ) * ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) ) );

         /* Si la coordonnée du clic est sur une zone affichable */
         if ( ( p_editField->windowCurrentNumberOfRow != 0 ) && ( l_cursorVector.y == ( l_y + ( ( uint32_t ) p_editField->windowCurrentNumberOfRow * ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) ) ) ) )
         {
            /* Décrémentation d'une ligne */
            l_cursorVector.y = ( uint32_t ) ( l_cursorVector.y - ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Détermination de la prochaine position du curseur */
         p_editField->cursorBaseOffset = mk_editField_getCursorOffsetDown ( p_editField, l_2DiTopLeft, l_2DiBottomRight, l_cursorVector, p_editField->windowBaseAddr );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleInsert ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le mode courant est le mode INSERT */
   if ( p_editField->cursor == &p_editField->secondaryCursor )
   {
      /* Actualisation de l'adresse du pointeur de curseur */
      p_editField->cursor = &p_editField->primaryCursor;
   }

   /* Sinon */
   else
   {
      /* Actualisation de l'adresse du pointeur de curseur */
      p_editField->cursor = &p_editField->secondaryCursor;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleInput ( T_mkEditField* p_editField, T_mkKeyboard* p_keyboard, int8_t p_key )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de retour locale */
   uint32_t l_ret = 0;

   /* Déclaration d'une variable stockant la longueur du caractère UTF */
   uint32_t l_length = 0;

   /* Déclaration d'une variable stockant les digits du caractère UTF */
   char8_t l_utf [ 4 ] = { 0 };

   /* Récupération de l'adresse de la chaine de caractères */
   T_str8 l_baseAddr = p_editField->strAddr;

   /* Inhibition du clignotement du curseur pendant 60 trames */
   p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;

   /* Si le caractère '\n' a été saisi */
   if ( p_key == '\n' )
   {
      /* Concaténation de l'entrée dans la chaine de caractères */
      l_length = mk_utils_codeToString ( ( uint32_t ) '\n', ( T_str8 ) l_utf, p_editField->style.fontEncoding );
   }

   /* Sinon si le caractère '\t' a été saisi */
   else if ( p_key == '\t' )
   {
      /* Concaténation de l'entrée dans la chaine de caractères */
      l_length = mk_utils_codeToString ( ( uint32_t ) '\t', ( T_str8 ) l_utf, p_editField->style.fontEncoding );
   }

   /* Si la chaine de caractères est encodée en ASCII */
   else if ( p_editField->style.fontEncoding == K_MK_FONT_ASCII )
   {
      /* Concaténation de l'entrée dans la chaine de caractères */
      l_length = mk_utils_codeToString ( p_keyboard->output->ascii, ( T_str8 ) l_utf, p_editField->style.fontEncoding );
   }

   /* Sinon si la chaine de caractères est encodée en UTF-8 */
   else if ( p_editField->style.fontEncoding == K_MK_FONT_UTF8 )
   {
      /* Concaténation de l'entrée dans la chaine de caractères */
      l_length = mk_utils_codeToString ( p_keyboard->output->utf8, ( T_str8 ) l_utf, p_editField->style.fontEncoding );
   }

   /* Sinon si la chaine de caractères est encodée en UTF-16 */
   else if ( p_editField->style.fontEncoding == K_MK_FONT_UTF16 )
   {
      /* Concaténation de l'entrée dans la chaine de caractères */
      l_length = mk_utils_codeToString ( p_keyboard->output->utf16, ( T_str8 ) l_utf, p_editField->style.fontEncoding );
   }

   /* Sinon si la chaine de caractères est encodée en UTF-32 */
   else if ( p_editField->style.fontEncoding == K_MK_FONT_UTF32 )
   {
      /* Concaténation de l'entrée dans la chaine de caractères */
      l_length = mk_utils_codeToString ( p_keyboard->output->utf32, ( T_str8 ) l_utf, p_editField->style.fontEncoding );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le curseur n'est pas sur le dernier caractère de la chaine */
   if ( ( p_editField->cursorBaseOffset + l_length ) < p_editField->maxStrSize )
   {
      /* Si le mode de saisi est le mode secondaire */
      if ( p_editField->cursor == &p_editField->secondaryCursor )
      {
         /* Copie du caractère UTF dans la chaine */
         _copy ( &l_baseAddr [ p_editField->cursorBaseOffset ], l_utf, l_length );
      }

      /* Sinon */
      else
      {
         /* Insertion du caractère UTF dans la chaine */
         l_ret = mk_utils_utfinsert ( l_baseAddr, p_editField->cursorBaseOffset, ( T_str8 ) l_utf, l_length, p_editField->style.fontEncoding );

         /* Si une erreur s'est produite */
         if ( l_ret == 0 )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_PARAM;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Actualisation de la position du curseur et de la fenêtre courante */
      l_result = mk_editField_handleRightArrow ( p_editField );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleBackspace ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de retour locale */
   uint32_t l_ret = 0;

   /* Récupération de l'adresse de la chaine de caractères */
   T_str8 l_baseAddr = p_editField->strAddr;

   /* Si le curseur ne pointe pas sur le début de la chaine */
   if ( p_editField->cursorBaseOffset != 0 )
   {
      /* Insertion du caractère UTF dans la chaine */
      l_ret = mk_utils_utfdel ( l_baseAddr, p_editField->cursorBaseOffset - 1, p_editField->style.fontEncoding );

      /* Si une erreur s'est produite */
      if ( l_ret == 0 )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
      }

      /* Sinon */
      else
      {
         /* Si le dernier caractère a été supprimé */
         if ( p_editField->cursorBaseOffset == p_editField->maxStrSize )
         {
            /* Ajout du caractère de fin de chaine */
            l_baseAddr [ p_editField->cursorBaseOffset ] = '\0';
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Inhibition du clignotement du curseur pendant 60 trames */
         p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;

         /* Actualisation de la position du curseur et de la fenêtre courante */
         l_result = mk_editField_handleLeftArrow ( p_editField );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_editField_handleSuppr ( T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de retour locale */
   uint32_t l_ret = 0;

   /* Récupération de l'adresse de la chaine de caractères */
   T_str8 l_baseAddr = p_editField->strAddr;

   /* Insertion du caractère UTF dans la chaine */
   l_ret = mk_utils_utfdel ( l_baseAddr, p_editField->cursorBaseOffset, p_editField->style.fontEncoding );

   /* Si une erreur s'est produite */
   if ( l_ret == 0 )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Sinon */
   else
   {
      /* Si le dernier caractère a été supprimé */
      if ( p_editField->cursorBaseOffset == ( p_editField->maxStrSize - 1 ) )
      {
         /* Ajout du caractère de fin de chaine */
         l_baseAddr [ p_editField->cursorBaseOffset + 1 ] = '\0';
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du champ */
      p_editField->cursorPainterOffset = K_MK_EDITFIELD_REFRESH;

      /* Inhibition du clignotement du curseur pendant 60 trames */
      p_editField->cursorInhibitionCounter = K_MK_EDITFIELD_INHIBITION_TIME;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_editField_defaultListener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de la boite d'édition */
   T_mkEditField* l_editField = ( T_mkEditField* ) p_mkField->child;

   /* Déclaration d'un pointeur de clavier */
   T_mkKeyboard* l_keyboard = K_MK_NULL;

   /* Déclaration d'un pointeur de souris */
   T_mkMouse* l_mouse = K_MK_NULL;

   /* Suppression warning */
   ( void ) p_mkContainer;

   /* Si le champ est sélectionné */
   if ( p_mkField->focus == K_MK_FIELD_STATE_FOCUS )
   {
      /* Si un événement en relation avec le clavier s'est produit */
      if ( p_mkAppCtrlId == K_MK_CONTROL_KEYBOARD )
      {
         /* Configuration du pointeur de clavier */
         l_keyboard = ( T_mkKeyboard* ) p_mkAppCtrl;

         /* Si l'utilisateur a saisi un caractère non affichable */
         if ( ( p_mkEvtCtrl == K_MK_EVENT_KEY_DOWN ) || ( p_mkEvtCtrl == K_MK_EVENT_KEY_HOLD ) )
         {
            /* Si la touche RIGHT_ARROW a été appuyée */
            if ( ( p_mkCtrlId == K_MK_KEYBOARD_RIGHTARROW ) )
            {
               /* Actualisation de la position du curseur et de la fenêtre courante */
               l_result = mk_editField_handleRightArrow ( l_editField );
            }

            /* Sinon si la touche LEFT_ARROW a été appuyée */
            else if ( ( p_mkCtrlId == K_MK_KEYBOARD_LEFTARROW ) )
            {
               /* Actualisation de la position du curseur et de la fenêtre courante */
               l_result = mk_editField_handleLeftArrow ( l_editField );
            }

            /* Sinon si la touche DOWN_ARROW a été appuyée */
            else if ( ( p_mkCtrlId == K_MK_KEYBOARD_DOWNARROW ) )
            {
               /* Actualisation de la position du curseur et de la fenêtre courante */
               l_result = mk_editField_handleDownArrow ( l_editField );
            }

            /* Sinon si la touche UP_ARROW a été appuyée */
            else if ( ( p_mkCtrlId == K_MK_KEYBOARD_UPARROW ) )
            {
               /* Actualisation de la position du curseur et de la fenêtre courante */
               l_result = mk_editField_handleUpArrow ( l_editField );
            }

            /* Sinon si la touche START a été appuyée */
            else if ( p_mkCtrlId == K_MK_KEYBOARD_START )
            {
               /* Actualisation de la position du curseur et de la fenêtre courante */
               mk_editField_handleStart ( l_editField );
            }

            /* Sinon si la touche END a été appuyée */
            else if ( p_mkCtrlId == K_MK_KEYBOARD_END )
            {
               /* Actualisation de la position du curseur et de la fenêtre courante */
               l_result = mk_editField_handleEnd ( l_editField );
            }

            /* Sinon si la touche PAGE_UP a été appuyée */
            else if ( p_mkCtrlId == K_MK_KEYBOARD_PAGEUP )
            {
               /* Actualisation de la position du curseur et de la fenêtre courante */
               l_result = mk_editField_handlePageUp ( l_editField );
            }

            /* Sinon si la touche PAGE_DOWN a été appuyée */
            else if ( p_mkCtrlId == K_MK_KEYBOARD_PAGEDOWN )
            {
               /* Actualisation de la position du curseur et de la fenêtre courante */
               l_result = mk_editField_handlePageDown ( l_editField );
            }

            /* Sinon si la touche INSERT a été appuyée */
            else if ( p_mkCtrlId == K_MK_KEYBOARD_INSERT )
            {
               /* Modification du mode de saisi */
               l_result = mk_editField_handleInsert ( l_editField );
            }

            /* Sinon si la touche ENTER a été appuyée */
            else if ( ( l_editField->writeProtect == K_MK_EDITFIELD_WRITE_PROTECT_DISABLED ) && ( p_mkCtrlId == K_MK_KEYBOARD_ENTER ) )
            {
               /* Ajout d'un caractère '\n' dans la chaine de caractères */
               l_result = mk_editField_handleInput ( l_editField, l_keyboard, '\n' );
            }

            /* Sinon si la touche TABULATION a été appuyée */
            else if ( ( l_editField->writeProtect == K_MK_EDITFIELD_WRITE_PROTECT_DISABLED ) && ( p_mkCtrlId == K_MK_KEYBOARD_TABULATION ) )
            {
               /* Ajout d'un caractère '\t' dans la chaine de caractères */
               l_result = mk_editField_handleInput ( l_editField, l_keyboard, '\t' );
            }

            /* Sinon si la touche SUPPR a été appuyée */
            else if ( ( l_editField->writeProtect == K_MK_EDITFIELD_WRITE_PROTECT_DISABLED ) && ( p_mkCtrlId == K_MK_KEYBOARD_DELETE ) )
            {
               /* Suppression d'un caractère de la chaine de caractères */
               l_result = mk_editField_handleSuppr ( l_editField );
            }

            /* Sinon si la touche BACKSPACE a été appuyée */
            else if ( ( l_editField->writeProtect == K_MK_EDITFIELD_WRITE_PROTECT_DISABLED ) && ( p_mkCtrlId == K_MK_KEYBOARD_BACKSPACE ) )
            {
               /* Suppression d'un caractère de la chaine de caractères */
               l_result = mk_editField_handleBackspace ( l_editField );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Si l'utilisateur a saisi un caractère affichable */
         if ( ( p_mkEvtCtrl == K_MK_EVENT_CHAR_DOWN ) || ( p_mkEvtCtrl == K_MK_EVENT_CHAR_HOLD ) )
         {
            /* Si la protection en écriture est désactivée */
            if ( l_editField->writeProtect == K_MK_EDITFIELD_WRITE_PROTECT_DISABLED )
            {
               /* Si le défilement automatique est activé */
               if ( l_editField->scrolling == K_MK_EDITFIELD_SCROLLING_ENABLED )
               {
                  /* Actualisation de la position du curseur et de la fenêtre courante */
                  l_result = mk_editField_handleScrolling ( l_editField );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Modification de la chaine de caractères en fonction de l'entrée saisie */
               l_result = mk_editField_handleInput ( l_editField, l_keyboard, 0 );
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

      /* Sinon si un événement en relation avec la souris s'est produit */
      else if ( p_mkAppCtrlId == K_MK_CONTROL_MOUSE )
      {
         /* Configuration du pointeur de souris */
         l_mouse = ( T_mkMouse* ) p_mkAppCtrl;

         /* Si l'utilisateur a réalisé un clic droit */
         if ( ( p_mkEvtCtrl == K_MK_EVENT_PRESS ) && ( p_mkCtrlId == 1 ) )
         {
            /* Actualisation de la position du curseur et de la fenêtre courante */
            l_result = mk_editField_handleMousePress ( l_editField, &l_mouse->axis );
         }

         /* Sinon si un scrolling vertical s'est produit */
         else if ( p_mkEvtCtrl == K_MK_EVENT_VSCROLL )
         {
            /* Si le curseur est désactivé */
            if ( l_editField->cursor->visibility == K_MK_GRAPHICS_VISIBLE )
            {
               /* Si le mouvement de la molette était vers le haut */
               if ( l_mouse->wheel.delta > 0 )
               {
                  /* Actualisation de la position du curseur et de la fenêtre courante */
                  l_result = mk_editField_handleUpArrow ( l_editField );
               }

               /* Sinon (mouvement vers le bas) */
               else
               {
                  /* Actualisation de la position du curseur et de la fenêtre courante */
                  l_result = mk_editField_handleDownArrow ( l_editField );
               }
            }

            /* Sinon */
            else
            {
               /* Si le mouvement de la molette était vers le haut */
               if ( l_mouse->wheel.delta > 0 )
               {
                  /* Actualisation de la position du curseur et de la fenêtre courante */
                  l_result = mk_editField_handleWheelUp ( l_editField );
               }

               /* Sinon (mouvement vers le bas) */
               else
               {
                  /* Actualisation de la position du curseur et de la fenêtre courante */
                  l_result = mk_editField_handleWheelDown ( l_editField );
               }
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

   /* Retour */
   return ( l_result );
}



