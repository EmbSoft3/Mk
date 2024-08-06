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
* @file mk_console_refresh.c
* @brief Définition de la fonction mk_console_refresh.
* @date 7 nov. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_console_clearBuffer ( T_mkConsole* p_console )
{
   /* Entrée en section critique */
   T_mkCode l_result = mk_display_enterCritical ( );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation des chaines de caractères */
      _writeBytes ( p_console->window.buf, 0, p_console->window.bufSize );

      /* Réinitialisation du buffer de la boite d'édition */
      mk_editField_setTextBuffer ( &p_console->foreground.window, p_console->window.buf, p_console->window.bufSize );

      /* Sortie de la section crique */
      l_result |= mk_display_exitCritical ( );
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

static uint32_t mk_console_setFilePointer ( T_mkConsole* p_console )
{
   /* Le buffer de la boite d'édition est plein. Il est nécessaire d'actualiser la valeur du pointeur filePointer */
   /* pour faire de la place dans celui-ci. */
   /* La console est encodée en UTF-8 donc c'est galère. */

   /* Déclaration des variables de travail */
   uint32_t l_pointer = 0, l_currentChar = 0;

   /* Déclaration des pointeurs de chaine de caractères */
   T_str8 l_str = ( T_str8 ) p_console->foreground.window.strAddr;
   T_str8 l_nextStr = K_MK_NULL;

   /* Déclaration d'une variable stockant la taille à éliminer dans le buffer de la boite d'édition */
   uint32_t l_shiftSize = ( 3 * p_console->foreground.window.maxStrSize / 4 );

   /* Effectue */
   do
   {
      /* Récupération de la valeur du premier caractère de la chaine */
      l_nextStr = mk_font_parseString ( l_str, &l_currentChar, ( uint32_t ) p_console->foreground.window.style.fontEncoding );

      /* Actualisation de la valeur du pointeur */
      l_pointer = l_pointer + ( uint32_t ) ( l_nextStr - l_str );

      /* Actualisation des variables */
      l_str = l_nextStr;

   /* Tant que l'offset recherchée n'a pas été atteinte */
   } while ( ( l_currentChar != 0 ) && ( l_pointer < l_shiftSize ) );

   /* Retour */
   return ( p_console->window.filePointer + l_pointer );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_console_refresh ( T_mkConsole* p_console )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_lFileSize = 0, l_hFileSize = 0, l_numberOfBytesToRead = 0, l_numberOfBytesRead;

   /* Récupération de la taille du fichier */
   l_result = mk_file_getSize ( p_console->window.file, &l_lFileSize, &l_hFileSize, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si la taille du fichier est supérieure à la taille du buffer */
      if ( ( l_lFileSize - p_console->window.filePointer ) > p_console->foreground.window.maxStrSize )
      {
         /* L'intégralité du fichier ne peut pas être affiché dans la boite d'édition. */
         /* Actualisation de la valeur du pointeur de fichier */
         p_console->window.filePointer = mk_console_setFilePointer ( p_console );

         /* Réinitialisation du buffer */
         l_result = mk_console_clearBuffer ( p_console );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
         /* L'intégralité du fichier peut être affiché dans la boite d'édition. */
      }

      /* Configuration de la taille de la requête de lecture */
      l_numberOfBytesToRead = ( l_lFileSize - p_console->window.filePointer );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Configuration du pointeur de fichier */
         l_result = mk_file_seek ( p_console->window.file, ( uint32_t ) p_console->window.filePointer, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Lecture du fichier */
         l_result = mk_file_read ( p_console->window.file, p_console->foreground.window.strAddr, l_numberOfBytesToRead, &l_numberOfBytesRead, K_MK_NULL );

         /* Si une erreur de lecture s'est produite */
         if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesToRead != l_numberOfBytesRead) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_UNEXPECTED;
         }

         /* Sinon */
         else
         {
            /* Déclenchement d'un rafraichissement graphique */
            mk_console_setRefresh ( p_console, K_MK_FIELD_REFRESH_ENABLED );

            /* Actualisation du pointeur de scrolling */
            /* Cette fonction peut être exécutée en parallèle du painter (pas besoin d'allouer une section critique) */
            l_result = mk_editField_handleScrolling ( &p_console->foreground.window );
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


