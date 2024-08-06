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
* @file mk_utils_ini_getValue.c
* @brief Définition de la fonction mk_utils_ini_getValue.
* @date 8 janv. 2023
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_ini_getFileChunk ( T_mkFile* p_file, T_mkINIParser* p_parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_size = p_parser->remainingSize;

   /* Si la taille restante à analyser dans le fichier est supérieure à la taille du buffer */
   if ( p_parser->remainingSize > K_MK_UTILS_PARSER_INI_FILEBUFSIZE )
   {
      /* Actualisation de la variable de travail */
      l_size = K_MK_UTILS_PARSER_INI_FILEBUFSIZE;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si l'analyse du fichier n'est pas terminée */
   if ( p_parser->remainingSize != 0 )
   {
      /* Lecture d'un morceau du fichier */
      l_result = mk_file_read ( p_file, p_parser->buf, l_size, &p_parser->numberOfBytesRead, K_MK_NULL );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_size == p_parser->numberOfBytesRead ) )
      {
         /* Réinitialisation de l'offset du pointeur dans le secteur */
         p_parser->bytePointer = 0;
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

static uint32_t mk_ini_handleSectionKey ( T_mkINIParser* p_parser, T_str8 p_str, uint32_t p_length )
{
   /* Déclaration des variables de retour */
   uint32_t l_result = 0, l_ret = 0;

   /* Si le parser est l'état 'START_OF_LINE' */
   /* Les espaces doivent être ignorés dans le décodage */
   if ( p_parser->state == K_MK_UTILS_PARSER_INI_STATE_START )
   {
      /* Si la ligne contient un commentaire */
      if ( p_parser->buf [ p_parser->bytePointer ] == ';' )
      {
         /* Passage à la prochaine étape */
         p_parser->state = K_MK_UTILS_PARSER_INI_STATE_BYPASS;
      }

      /* Sinon si l'étape de comparaison doit être activée */
      else if ( p_parser->buf [ p_parser->bytePointer ] != ' ' )
      {
         /* Passage à la prochaine étape */
         p_parser->state = K_MK_UTILS_PARSER_INI_STATE_COMPARE;
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

   /* Si l'état du parser est l'état 'COMPARE' */
   if ( p_parser->state == K_MK_UTILS_PARSER_INI_STATE_COMPARE )
   {
      /* Comparaison des caractères courant (bypass de la casse) */
      l_ret = mk_utils_strcomp ( ( T_str8 ) &p_parser->buf [ p_parser->bytePointer ],
                                 ( T_str8 ) &p_str [ p_parser->strPointer ], 1, 1 );

      /* Si le caractère courant est le caractère de fin de comparaison */
      if ( p_parser->buf [ p_parser->bytePointer ] == '\n' )
      {
         /* Si la chaine de caractères a été trouvée */
         if ( p_parser->strPointer == p_length )
         {
            /* Actualisation de la variable de retour et arrêt de la boucle */
            l_result = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Réinitialisation du pointeur de caractères */
         p_parser->strPointer = 0;

         /* Retour à la première étape */
         p_parser->state = K_MK_UTILS_PARSER_INI_STATE_START;
      }

      /* Sinon si le caractère courant est le caractère de bypass */
      else if ( p_parser->buf [ p_parser->bytePointer ] == '=' )
      {
         /* Réinitialisation du pointeur de caractères */
         p_parser->strPointer = 0;

         /* Activation du bypass jusqu'au prochain retour à la ligne */
         p_parser->state = K_MK_UTILS_PARSER_INI_STATE_BYPASS;
      }

      /* Sinon si le caractère courant est présent à l'indice recherché de la chaine de caractères */
      else if ( l_ret == 1 )
      {
         /* Actualisation du pointeur de caractères (passage au prochain) */
         p_parser->strPointer = ( uint32_t ) ( p_parser->strPointer + 1 );
      }

      /* Sinon si le caractère courant est le caractère espace */
      /* La comparaison est terminée et un ou plusieurs espaces peuvent être présents avant le caractère de fin de processus ('\n'). */
      else if ( ( p_parser->buf [ p_parser->bytePointer ] == ' ' ) || ( p_parser->buf [ p_parser->bytePointer ] == '\r' ) )
      {
         /* Ne rien faire */
      }

      /* Sinon */
      else
      {
         /* Réinitialisation du pointeur de section */
         p_parser->strPointer = 0;
      }
   }

   /* Sinon (état BYPASS) */
   else
   {
      /* Si le caractère courant est le caractère de fin de ligne */
      if ( p_parser->buf [ p_parser->bytePointer ] == '\n' )
      {
         /* Retour à la première étape, arrêt du bypass */
         p_parser->state = K_MK_UTILS_PARSER_INI_STATE_START;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_ini_handlePropertyKey ( T_mkINIParser* p_parser, T_str8 p_str, uint32_t p_length, uint8_t p_disableSection )
{
   /* Déclaration des variables de retour */
   uint32_t l_result = 0, l_ret = 0;;

   /* Si l'état du parser est l'état 'START_OF_LINE' */
   /* Les espaces doivent être ignorés dans le décodage */
   if ( p_parser->state == K_MK_UTILS_PARSER_INI_STATE_START )
   {
      /* Si la ligne contient un commentaire */
      if ( p_parser->buf [ p_parser->bytePointer ] == ';' )
      {
         /* Passage à la prochaine étape */
         p_parser->state = K_MK_UTILS_PARSER_INI_STATE_BYPASS;
      }

      /* Sinon si un début de section est détecté */
      else if ( ( p_parser->buf [ p_parser->bytePointer ] == '[' ) && ( p_disableSection != '\0' ) )
      {
         /* Actualisation de la variable de retour */
         l_result = 2;
      }

      /* Sinon si l'étape de comparaison doit être activée */
      else if ( p_parser->buf [ p_parser->bytePointer ] != ' ' )
      {
         /* Passage à la prochaine étape */
         p_parser->state = K_MK_UTILS_PARSER_INI_STATE_COMPARE;
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

   /* Si l'état du parser est l'état 'COMPARE' */
   if ( p_parser->state == K_MK_UTILS_PARSER_INI_STATE_COMPARE )
   {
      /* Comparaison des caractères (bypass de la casse) */
      l_ret = mk_utils_strcomp ( ( T_str8 ) &p_parser->buf [ p_parser->bytePointer ],
                                 ( T_str8 ) &p_str [ p_parser->strPointer ], 1, 1 );

      /* Si le caractère courant est le caractère de fin de comparaison */
      if ( p_parser->buf [ p_parser->bytePointer ] == '=' )
      {
         /* Si la chaine de caractères a été trouvée */
         if ( p_parser->strPointer == p_length )
         {
            /* Actualisation de la variable de retour et arrêt de la boucle */
            l_result = 1;

            /* Retour à la première étape */
            p_parser->state = K_MK_UTILS_PARSER_INI_STATE_START;
         }

         /* Sinon */
         else
         {
            /* Bypass des caractères jusq'au prochain retour à la ligne */
            p_parser->state = K_MK_UTILS_PARSER_INI_STATE_BYPASS;
         }

         /* Réinitialisation du pointeur de caractères */
         p_parser->strPointer = 0;
      }

      /* Sinon si le caractère courant est le caractère de fin de ligne */
      else if ( p_parser->buf [ p_parser->bytePointer ] == '\n' )
      {
         /* Retour à la première étape */
         p_parser->state = K_MK_UTILS_PARSER_INI_STATE_START;

         /* Réinitialisation du pointeur de caractères */
         p_parser->strPointer = 0;
      }

      /* Sinon si le caractère courant est présent à l'indice recherché de la chaine de caractères */
      else if ( l_ret == 1 )
      {
         /* Actualisation du pointeur de caractères (passage au prochain) */
         p_parser->strPointer = ( uint32_t ) ( p_parser->strPointer + 1 );
      }

      /* Sinon si le caractère courant est le caractère espace */
      /* La comparaison est terminée et un ou plusieurs espaces peuvent être présents avant le caractère de fin de processus ('='). */
      else if ( p_parser->buf [ p_parser->bytePointer ] == ' ' )
      {
         /* Ne rien faire */
      }

      /* Sinon */
      else
      {
         /* Réinitialisation du pointeur de section */
         p_parser->strPointer = 0;
      }
   }

   /* Sinon (état BYPASS) */
   else
   {
      /* Si le caractère courant est le caractère de fin de ligne */
      if ( p_parser->buf [ p_parser->bytePointer ] == '\n' )
      {
         /* Retour à la première étape, arrêt du bypass */
         p_parser->state = K_MK_UTILS_PARSER_INI_STATE_START;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_ini_handleValue ( T_mkINIParser* p_parser, T_str8 p_str, uint32_t p_length )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Si l'état du parser est l'état 'START_OF_LINE' */
   /* Les espaces doivent être ignorés dans le décodage */
   if ( p_parser->state == K_MK_UTILS_PARSER_INI_STATE_START )
   {
      /* Si l'étape de comparaison doit être activée */
      if ( p_parser->buf [ p_parser->bytePointer ] != ' ' )
      {
         /* Passage à la prochaine étape */
         p_parser->state = K_MK_UTILS_PARSER_INI_STATE_COPY;
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

   /* Sinon si l'état du parser est l'état 'COPY' */
   if ( p_parser->state == K_MK_UTILS_PARSER_INI_STATE_COPY )
   {
      /* Si le caractère courant est le caractère de fin de ligne */
      if ( p_parser->buf [ p_parser->bytePointer ] == '\n' )
      {
         /* Si le caractère courant peut être copié dans la chaine */
         if ( p_parser->strPointer < p_length )
         {
            /* Ecriture du caractère de fin */
            p_str [ p_parser->strPointer ] = '\0';
         }

         /* Sinon */
         else
         {
            /* Ecriture du caractère de fin */
            p_str [ p_parser->strPointer - 1 ] = '\0';
         }

         /* Actualisation de la variable de retour et arrêt de la boucle */
         l_result = 1;
      }

      /* Sinon si le caractère courant est un carriage return */
      else if ( p_parser->buf [ p_parser->bytePointer ] == '\r' )
      {
         /* Ne rien faire */
      }

      /* Sinon */
      else
      {
         /* Si le caractère courant peut être copié dans la chaine */
         if ( p_parser->strPointer < p_length )
         {
            /* Copie de l'octet courant */
            p_str [ p_parser->strPointer ] = ( int8_t ) p_parser->buf [ p_parser->bytePointer ];

            /* Actualisation du pointeur de caractères */
            p_parser->strPointer = ( uint32_t ) ( p_parser->strPointer + 1 );
         }

         /* Sinon */
         else
         {
            /* Ecriture du caractère de fin */
            p_str [ p_parser->strPointer - 1 ] = '\0';

            /* Actualisation de la variable de retour et arrêt de la boucle */
            l_result = 1;
         }
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

static T_mkCode mk_ini_moveToSection ( T_mkFile* p_file, T_mkINIParser* p_parser, T_str8 p_section )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable indiquant que la section recherchée a été trouvée */
   uint32_t l_keyFound = 0;

   /* Déclaration d'une variable stockant la longueur de la section */
   uint32_t l_length = mk_utils_strlen ( p_section );

   /* Si la section présente en paramètre n'est pas vide */
   if ( p_section [ 0 ] != '\0' )
   {
      /* Effectue */
      do
      {
         /* Si aucune donnée n'est disponible pour traitement */
         if ( p_parser->numberOfBytesRead == 0 )
         {
            /* Chargement d'un ou plusieurs secteurs du fichier */
            l_result = mk_ini_getFileChunk ( p_file, p_parser );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Analyse du fichier */
         l_keyFound = mk_ini_handleSectionKey ( p_parser, p_section, l_length );

         /* Actualisation des données du parser */
         p_parser->bytePointer = ( uint32_t ) ( p_parser->bytePointer + 1 );
         p_parser->remainingSize = ( uint32_t ) ( p_parser->remainingSize - 1 );
         p_parser->numberOfBytesRead = ( uint32_t ) ( p_parser->numberOfBytesRead - 1 );
      }

      /* Tant que le fichier n'a pas été entièrement analysé ou tant que la section */
      /* n'a pas été trouvée */
      while ( ( l_result == K_MK_OK ) && ( p_parser->remainingSize != 0 ) && ( l_keyFound == 0 ) );

      /* Si la section n'a pas été trouvée */
      if ( ( l_result == K_MK_OK ) && ( l_keyFound == 0 ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_NOT_FOUND;
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

static T_mkCode mk_ini_moveToProperty ( T_mkFile* p_file, T_mkINIParser* p_parser, T_str8 p_section, T_str8 p_property )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable indiquant que la propriété recherchée a été trouvée */
   uint32_t l_keyFound = 0;

   /* Déclaration d'une variable stockant la longueur de la section */
   uint32_t l_length = mk_utils_strlen ( p_property );

   /* Effectue */
   do
   {
      /* Si aucune donnée n'est disponible pour traitement */
      if ( p_parser->numberOfBytesRead == 0 )
      {
         /* Chargement d'un ou plusieurs secteurs du fichier */
         l_result = mk_ini_getFileChunk ( p_file, p_parser );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Analyse du fichier (le mécanisme de bypass n'est pas utilisé) */
      l_keyFound = mk_ini_handlePropertyKey ( p_parser, p_property, l_length, ( uint8_t ) p_section [ 0 ] );

      /* Actualisation des données du parser */
      p_parser->bytePointer = ( uint32_t ) ( p_parser->bytePointer + 1 );
      p_parser->remainingSize = ( uint32_t ) ( p_parser->remainingSize - 1 );
      p_parser->numberOfBytesRead = ( uint32_t ) ( p_parser->numberOfBytesRead - 1 );
   }

   /* Tant que le fichier n'a pas été entièrement analysé ou tant que la propriété */
   /* n'a pas été trouvée */
   while ( ( l_result == K_MK_OK ) && ( p_parser->remainingSize != 0 ) && ( l_keyFound == 0 ) );

   /* Si la propriété n'a pas été trouvée */
   if ( ( l_result == K_MK_OK ) && ( l_keyFound != 1 ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_NOT_FOUND;
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

static T_mkCode mk_ini_getPropertieValue ( T_mkFile* p_file, T_mkINIParser* p_parser, T_str8 p_value, uint32_t p_valueLength )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable indiquant que la propriété recherchée a été trouvée */
   uint32_t l_valueCopy = 0;

   /* Effectue */
   do
   {
      /* Si aucune donnée n'est disponible pour traitement */
      if ( p_parser->numberOfBytesRead == 0 )
      {
         /* Chargement d'un ou plusieurs secteurs du fichier */
         l_result = mk_ini_getFileChunk ( p_file, p_parser );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Analyse du fichier (le mécanisme de bypass n'est pas utilisé) */
      l_valueCopy = mk_ini_handleValue ( p_parser, p_value, p_valueLength );

      /* Actualisation des données du parser */
      p_parser->bytePointer = ( uint32_t ) ( p_parser->bytePointer + 1 );
      p_parser->remainingSize = ( uint32_t ) ( p_parser->remainingSize - 1 );
      p_parser->numberOfBytesRead = ( uint32_t ) ( p_parser->numberOfBytesRead - 1 );
   }

   /* Tant que le fichier n'a pas été entièrement analysé ou tant que la propriété */
   /* n'a pas été trouvée */
   while ( ( l_result == K_MK_OK ) && ( p_parser->remainingSize != 0 ) && ( l_valueCopy == 0 ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_utils_ini_getValue ( T_mkFile* p_file, T_str8 p_section, T_str8 p_property, T_str8 p_value, uint32_t p_valueLength )
{
   /* Caractéristiques du parser */
   /* Encodage du fichier : ascii 8 bits */
   /* Caractères réservés : '=' et ';' */
   /* Commentaires : ';' en début de ligne seulement */
   /* Autres : section et propriété non sensible à la casse */

   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de padding */
   uint32_t l_padding = 0;

   /* Déclaration d'un parser de fichier */
   T_mkINIParser l_parser = { 0 };

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_section != K_MK_NULL ) && ( p_property != K_MK_NULL ) && ( p_property [ 0 ] != '\0' ) &&
        ( p_value != K_MK_NULL ) && ( p_valueLength != 0 ) )
   {
      /* Récupération de la taille du fichier */
      l_result = mk_file_getSize ( p_file, &l_parser.remainingSize, &l_padding, K_MK_NULL );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK   )
      {
         /* Si le fichier est valide */
         if ( l_parser.remainingSize != 0 )
         {
            /* Configuration du pointeur de fichier au début de celui-ci */
            l_result = mk_file_seek ( p_file, 0, K_MK_NULL );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Recherche de la section demandée par l'utilisateur (pas d'action si aucune section n'a été spécifiée) */
               /* Si la section n'a pas été trouvée, alors la fin de fichier a été atteinte */
               l_result = mk_ini_moveToSection ( p_file, &l_parser, p_section );

               /* Si la section a été trouvée */
               if ( l_result == K_MK_OK )
               {
                  /* Recherche de la propriété demandée par l'utilisateur */
                  l_result = mk_ini_moveToProperty ( p_file, &l_parser, p_section, p_property );

                  /* Si la propriété a été trouvée */
                  if ( l_result == K_MK_OK )
                  {
                     /* Récupération de la valeur de la propriété */
                     l_result = mk_ini_getPropertieValue ( p_file, &l_parser, p_value, p_valueLength );
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
         }

         /* Sinon */
         else
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_PARAM;
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}



