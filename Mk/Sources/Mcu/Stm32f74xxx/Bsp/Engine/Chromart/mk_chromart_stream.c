/**
*
* @copyright Copyright (C) 2026 RENARD Mathieu. All rights reserved.
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
* @file mk_chromart_stream.c
* @brief Définition de la fonction mk_chromart_stream.
* @date 15 avril 2026
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_chromart_createFilePath ( T_str8 p_path )
{
   /* Déclaration des chaines de caractères permettant de coder le nom du fichier */
   char8_t l_screenshotString [ 12 ] = { 0 };
   char8_t l_randString [ 4 ] [ 9 ] = { { 0 } };
   
   /* Conversion du numéro du screenshot en chaine de caractères */
   ( void ) mk_utils_itoa ( g_mkDisplay.stream.counter, l_screenshotString, 10, 0 );
   
   /* Conversion des nombres aléatoires en chaine de caractères */
   ( void ) mk_utils_itoa ( g_mkDisplay.stream.randomNumber [ 0 ], ( T_str8 ) &l_randString [ 0 ] [ 0 ], 16, 8 );
   ( void ) mk_utils_itoa ( g_mkDisplay.stream.randomNumber [ 1 ], ( T_str8 ) &l_randString [ 1 ] [ 0 ], 16, 8 );
   ( void ) mk_utils_itoa ( g_mkDisplay.stream.randomNumber [ 2 ], ( T_str8 ) &l_randString [ 2 ] [ 0 ], 16, 8 );
   ( void ) mk_utils_itoa ( g_mkDisplay.stream.randomNumber [ 3 ], ( T_str8 ) &l_randString [ 3 ] [ 0 ], 16, 8 );

   /* Concaténéation de la chaine de caractère */
   ( void ) mk_utils_strcat ( p_path, ( T_str8 ) "mk/stream/stream_", ( T_str8 ) &l_randString [ 0 ] [ 0 ] );
   ( void ) mk_utils_strcat ( p_path, p_path, ( T_str8 ) &l_randString [ 1 ] [ 0 ] );
   ( void ) mk_utils_strcat ( p_path, p_path, ( T_str8 ) &l_randString [ 2 ] [ 0 ] );
   ( void ) mk_utils_strcat ( p_path, p_path, ( T_str8 ) &l_randString [ 3 ] [ 0 ] );
   ( void ) mk_utils_strcat ( p_path, p_path, ( T_str8 ) "/screenshot_" );
   ( void ) mk_utils_strcat ( p_path, p_path, ( T_str8 ) l_screenshotString );
   ( void ) mk_utils_strcat ( p_path, p_path, ( T_str8 ) ".bmp");

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_createBitmapPath ( T_str8 p_path )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de retour locale */
   int32_t l_ret = 0;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Si un nombre aléatoire doit être généré (premier enregistrement) */
   if ( g_mkDisplay.stream.counter == 0 )
   {
      /* Effectue */
      do
      {
         /* Génération d'un nombre aléatoire */
         l_ret = mk_utils_rand ( g_mkDisplay.stream.randomNumber );

         /* Si aucune erreur ne s'est produite */
         if ( l_ret == 0 )
         {
            /* Création du chemin où sera enregistré le fichier */
            mk_chromart_createFilePath ( p_path );
            
            /* Test de l'existance du fichier à créer */
            l_result = mk_file_stat ( K_MK_NULL, ( T_str8 ) p_path, K_MK_NULL );
         }

         /* Sinon */
         else
         {
            /* Actualisation du compteur */
            l_counter = ( uint32_t ) ( l_counter + 1 );
         }

         /* Si le nombre aléatoire n'arrive pas à être généré */
         if ( l_counter >= 100 )
         {
            /* Positionnement de la variable de retour à K_MK_ERROR_UNEXPECTED */
            l_result = K_MK_ERROR_UNEXPECTED;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

      /* Tant que le fichier existe et tant qu'aucune erreur ne s'est produite */
      } while ( ( l_result == K_MK_OK ) );

      /* Si le fichier n'a pas été trouvé */
      if ( l_result == K_MK_ERROR_NOT_FOUND )
      {
         /* Un nom de fichier unique a été trouvé, on positionne la variable de retour à K_MK_OK */
         l_result = K_MK_OK;
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
      /* Création du chemin où sera enregistré le fichier */
      mk_chromart_createFilePath ( p_path );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_chromart_stream ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une chaine de caractères */
   char8_t l_filePath [ 80 ] = { 0 };

   /* Génération d'un nom de fichier aléatoire */
   /* "mk/stream/stream_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx/screenshot_yyyyyyyyyy.bmp" */
   l_result = mk_chromart_createBitmapPath ( l_filePath );

   /* Si le nom de fichier a été généré correctement */
   if ( l_result == K_MK_OK )
   {
      /* Si une trame doit être enregistrée */
      if ( g_mkDisplay.stream.currentValue == ( g_mkDisplay.stream.rate - 1 ) )
      {
         /* Déclenchement du screenshot */
         l_result = mk_chromart_screenshot ( l_filePath );

         /* Actualisation du compteur de screenshot*/
         g_mkDisplay.stream.counter = ( uint32_t ) ( g_mkDisplay.stream.counter + 1 );

         /* Si le compteur a fait un rollback, on stoppe l'enregistrement */
         if ( g_mkDisplay.stream.counter == 0 )
         {
            /* Arrêt du flux d'enregistrement */
            g_mkDisplay.status.stream = 0;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
         
         /* Réinitialisation de la valeur du compteur de frames */
         g_mkDisplay.stream.currentValue = 0;
      }

      /* Sinon */
      else
      {
         /* Incrémentation de la valeur du compteur de frames */
         g_mkDisplay.stream.currentValue = ( uint32_t ) ( g_mkDisplay.stream.currentValue + 1 );
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