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
* @file mk_utils_srec_loadRAM.c
* @brief Définition de la fonction mk_utils_srec_loadRAM.
* @date 20 déc. 2023
*
*/

#include "mk_loader_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_loader_srec_hexatoi ( T_str8 p_buf, uint32_t p_numberOfDigits )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Déclaration des variables de travail */
   uint32_t l_byte, l_counter;

   /* Pour le nombre de digits à traiter */
   for ( l_counter = 0 ; l_counter < p_numberOfDigits ; l_counter++ )
   {
      /* Décalage de la variable de retour */
      l_result = ( uint32_t ) ( l_result << 4 );

      /* Conversion du caractère courant en entier */
      if ( ( p_buf [ l_counter ] >= '0' ) && ( p_buf [ l_counter ] <= '9' ) )
      {
         l_byte = ( p_buf [ l_counter ] - '0' ) & 0xF;
      }

      else
      {
         l_byte = ( 10 + ( p_buf [ l_counter ] - 'A' ) ) & 0xF;
      }

      /* Actualisation de la variable de retour */
      l_result |= l_byte;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_srec_verifyChecksum ( T_mkSRECParser* p_parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_counter, l_computeChecksum = 0, l_storageChecksum = 0;

   /* Récupération de la valeur du checksum stocké */
   l_storageChecksum = mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD + ( 2 * ( p_parser->recordBytesCount - 1 ) ) ], 2 );

   /* Pour le nombre de digits à traiter */
   for ( l_counter = 0 ; l_counter < p_parser->recordBytesCount ; l_counter++ )
   {
      l_computeChecksum += mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_BYTECOUNT_FIELD + ( 2 * l_counter ) ], 2 );
   }

   /* Finalisation du calcul du CRC */
   l_computeChecksum = 0xFF - ( l_computeChecksum & 0xFF );

   /* Si les CRC sont différents */
   if ( l_computeChecksum != l_storageChecksum )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_CORRUPTED;
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

static T_mkCode mk_loader_srec_getFileChunk ( T_mkFile* p_file, T_mkSRECParser* p_parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_size = p_parser->remainingSize;

   /* Si la taille restante à analyser dans le fichier est supérieure à la taille du buffer */
   if ( p_parser->remainingSize > K_MK_LOADER_SREC_FILEBUFSIZE )
   {
      /* Configuration de la taille de la requête de lecture */
      l_size = K_MK_LOADER_SREC_FILEBUFSIZE;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le fichier n'a pas été entièrement analysé */
   if ( p_parser->remainingSize != 0 )
   {
      /* Lecture d'une portion du fichier */
      l_result = mk_file_read ( p_file, p_parser->buf, l_size, &p_parser->numberOfBytesRead, K_MK_NULL );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_size == p_parser->numberOfBytesRead ) )
      {
         /* Réinitialisation de l'offset du buffer */
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

static void mk_loader_srec_parseStart ( T_mkSRECParser* p_parser )
{
   /* Mise à jour de la variable de statut */
   p_parser->recordValidity = 0;

   /* Si la ligne du record est une ligne de données */
   if ( p_parser->buf [ p_parser->bytePointer ] == 'S' )
   {
      /* Réinitialisation des attributs du record */
      p_parser->recordPointer = 0;

      /* Enregistrement du caractère dans le record */
      p_parser->record [ p_parser->recordPointer ] = 'S';
      p_parser->recordPointer = ( uint32_t ) ( p_parser->recordPointer + 1 );

      /* Passage à la prochaine étape */
      p_parser->state = K_MK_LOADER_SREC_STATE_TYPE;
   }

   /* Sinon */
   else
   {
      /* On considére la ligne comme une ligne de commentaires. */
      /* On bascule dans l'état de bypass */
      p_parser->state = K_MK_LOADER_SREC_STATE_BYPASS;
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_loader_srec_parseBypass ( T_mkSRECParser* p_parser )
{
   /* Dans cet état, on ignore les données présentes sur la ligne */
   /* La fin de celle-ci est marquée par la succession des caractères : \r\n */
   if ( p_parser->buf [ p_parser->bytePointer ] == '\n' )
   {
      /* Passage à la prochaine étape */
      p_parser->state = K_MK_LOADER_SREC_STATE_START;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_srec_parseType ( T_mkSRECParser* p_parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le type du record est valide  */
   if ( ( p_parser->buf [ p_parser->bytePointer ] >= '0' ) && ( p_parser->buf [ p_parser->bytePointer ] <= '9' ) )
   {
      /* Enregistrement du caractère dans le record */
      p_parser->record [ p_parser->recordPointer ] = p_parser->buf [ p_parser->bytePointer ];
      p_parser->recordPointer = ( uint32_t ) ( p_parser->recordPointer + 1 );

      /* Si le record est de type '4' */
      if ( p_parser->buf [ p_parser->bytePointer ] == '4' )
      {
         /* On ne traite pas le record car celui-ci n'est pas défini */
         p_parser->state = K_MK_LOADER_SREC_STATE_BYPASS;
      }

      /* Sinon */
      else
      {
         /* Passage à la prochaine étape */
         p_parser->state = K_MK_LOADER_SREC_STATE_BYTECOUNT;
      }
   }

   /* Sinon */
   else
   {
      /* Arrêt du traitement, le fichier est corrompu */
      l_result = K_MK_ERROR_CORRUPTED;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_srec_parseByteCount ( T_mkSRECParser* p_parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le caractère est valide  */
   if ( ( ( p_parser->buf [ p_parser->bytePointer ] >= '0' ) && ( p_parser->buf [ p_parser->bytePointer ] <= '9' ) ) ||
        ( ( p_parser->buf [ p_parser->bytePointer ] >= 'A' ) && ( p_parser->buf [ p_parser->bytePointer ] <= 'F' ) ) )
   {
      /* Enregistrement du caractère dans le record */
      p_parser->record [ p_parser->recordPointer ] = p_parser->buf [ p_parser->bytePointer ];
      p_parser->recordPointer = ( uint32_t ) ( p_parser->recordPointer + 1 );

      /* Si les 2 caractères constituant le champ 'ByteCount' ont été récupérés */
      if ( p_parser->recordPointer == 4 )
      {
         /* Conversion du nombre d'octets en entier */
         p_parser->recordBytesCount = mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_BYTECOUNT_FIELD ], 2 );

         /* Si le nombre d'octets est valide */
         if ( p_parser->recordBytesCount >= K_MK_LOADER_SREC_MINIMAL_BYTE_COUNT )
         {
            /* Passage à la prochaine étape */
            p_parser->state = K_MK_LOADER_SREC_STATE_COPY;
         }

         /* Sinon */
         else
         {
            /* Arrêt du traitement, le fichier est corrompu */
            l_result = K_MK_ERROR_CORRUPTED;
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
      /* Arrêt du traitement, le fichier est corrompu */
      l_result = K_MK_ERROR_CORRUPTED;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_srec_parseCopy ( T_mkSRECParser* p_parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le caractère est valide  */
   if ( ( ( p_parser->buf [ p_parser->bytePointer ] >= '0' ) && ( p_parser->buf [ p_parser->bytePointer ] <= '9' ) ) ||
        ( ( p_parser->buf [ p_parser->bytePointer ] >= 'A' ) && ( p_parser->buf [ p_parser->bytePointer ] <= 'F' ) ) )
   {
      /* Si la taille maximale du record n'a pas été dépassée */
      if ( ( p_parser->recordPointer < K_MK_LOADER_SREC_RECORD_MAX_SIZE ) )
      {
         /* Enregistrement du caractère dans le record */
         p_parser->record [ p_parser->recordPointer ] = p_parser->buf [ p_parser->bytePointer ];
         p_parser->recordPointer = ( uint32_t ) ( p_parser->recordPointer + 1 );

         /* Si les caractères constituant les champs 'Address', 'Data' et 'Checksum' ont été récupérés */
         if ( p_parser->recordPointer == ( K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD + 2*p_parser->recordBytesCount ) )
         {
            /* Ajout du caractère de terminaison */
            p_parser->record [ p_parser->recordPointer ] = '\n';

            /* Mise à jour de la variable de statut */
            p_parser->recordValidity = 1;

            /* Passage à la prochaine étape */
            p_parser->state = K_MK_LOADER_SREC_STATE_BYPASS;
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
         /* Arrêt du traitement, le fichier est corrompu */
         l_result = K_MK_ERROR_CORRUPTED;
      }
   }

   /* Sinon */
   else
   {
      /* Arrêt du traitement, le fichier est corrompu */
      l_result = K_MK_ERROR_CORRUPTED;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_srec_parse ( T_mkSRECParser* p_parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le parser est dans l'état 'COPY' */
   if ( p_parser->state == K_MK_LOADER_SREC_STATE_COPY )
   {
      l_result = mk_loader_srec_parseCopy ( p_parser );
   }

   /* Sinon si le parser est dans l'état 'START' */
   else if ( p_parser->state == K_MK_LOADER_SREC_STATE_START )
   {
      mk_loader_srec_parseStart ( p_parser );
   }

   /* Sinon si le parser est dans l'état 'BYPASS' */
   else if ( p_parser->state == K_MK_LOADER_SREC_STATE_BYPASS )
   {
      mk_loader_srec_parseBypass ( p_parser );
   }

   /* Sinon si le parser est dans l'état 'TYPE' */
   else if ( p_parser->state == K_MK_LOADER_SREC_STATE_TYPE )
   {
      l_result = mk_loader_srec_parseType ( p_parser );
   }

   /* Sinon si le parser est dans l'état 'BYTECOUNT' */
   else if ( p_parser->state == K_MK_LOADER_SREC_STATE_BYTECOUNT )
   {
      l_result = mk_loader_srec_parseByteCount ( p_parser );
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

static T_mkCode mk_loader_srec_getRecord ( T_mkFile* p_file, T_mkSRECParser* p_parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Tant qu'un nouveau record n'a pas été récupéré */
   do
   {
      /* Si aucune donnée n'est disponible pour traitement */
      if ( p_parser->numberOfBytesRead == 0 )
      {
         /* Lecture d'une portion du fichier */
         l_result = mk_loader_srec_getFileChunk ( p_file, p_parser );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Récupération des informations du record */
         l_result = mk_loader_srec_parse ( p_parser );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation des données du parser */
      p_parser->bytePointer = ( uint32_t ) ( p_parser->bytePointer + 1 );
      p_parser->remainingSize = ( uint32_t ) ( p_parser->remainingSize - 1 );
      p_parser->numberOfBytesRead = ( uint32_t ) ( p_parser->numberOfBytesRead - 1 );
   }
   while ( ( l_result == K_MK_OK ) && ( p_parser->remainingSize != 0 ) && ( p_parser->state != K_MK_LOADER_SREC_STATE_START ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_srec_loadRecord ( T_mkSRECParser* p_parser, T_mkAddr p_offsetAddr, T_mkAddr* p_startAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable permettant de réaliser les accès mémoire sur 8bits */
   uint8_t* l_addr = ( uint8_t* ) p_offsetAddr;

   /* Déclaration d'une variable stockant l'adresse du record */
   uint32_t l_recordAddr = 0;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Vérification du checksum du record */
   l_result = mk_loader_srec_verifyChecksum ( p_parser );

   /* Si le record est valide */
   if ( l_result == K_MK_OK )
   {
      /* Si le record est de type 'S1' (Data 16bits Address) */
      if ( p_parser->record [ K_MK_LOADER_SREC_OFFSET_TYPE_FIELD ] == '1' )
      {
         /* Récupération de l'adresse (format 16bits) */
         l_recordAddr = mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD ], 4 );

         /* Ecriture des données du record en mémoire */
         for ( l_counter = 0 ; l_counter < ( p_parser->recordBytesCount - 3 ) ; l_counter++ )
         {
            * ( l_addr + l_recordAddr + l_counter ) = ( uint8_t ) mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD + 4 + ( 2 * l_counter ) ], 2 );
         }
      }

      /* Sinon si le record est de type 'S2' (Data 24bits Address) */
      else if ( p_parser->record [ K_MK_LOADER_SREC_OFFSET_TYPE_FIELD ] == '2' )
      {
         /* Récupération de l'adresse (format 24bits) */
         l_recordAddr = mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD ], 6 );

         /* Ecriture des données du record en mémoire */
         for ( l_counter = 0 ; l_counter < ( p_parser->recordBytesCount - 4 ) ; l_counter++ )
         {
            * ( l_addr + l_recordAddr + l_counter ) = ( uint8_t ) mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD + 6 + ( 2 * l_counter ) ], 2 );
         }
      }

      /* Sinon si le record est de type 'S3' (Data 32bits Address) */
      else if ( p_parser->record [ K_MK_LOADER_SREC_OFFSET_TYPE_FIELD ] == '3' )
      {
         /* Récupération de l'adresse (format 32bits) */
         l_recordAddr = mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD ], 8 );

         /* Ecriture des données du record en mémoire */
         for ( l_counter = 0 ; l_counter < ( p_parser->recordBytesCount - 5 ) ; l_counter++ )
         {
            * ( l_addr + l_recordAddr + l_counter ) = ( uint8_t ) mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD + 8 + ( 2 * l_counter ) ], 2 );
         }
      }

      /* Sinon si le record est de type 'S7' (Start Address 32bits) */
      else if ( p_parser->record [ K_MK_LOADER_SREC_OFFSET_TYPE_FIELD ] == '7' )
      {
         /* Si l'adresse de démarrage doit être récupérée */
         if ( p_startAddr != K_MK_NULL )
         {
            /* Récupération de l'adresse de démarrage (format 32bits) */
            *p_startAddr = ( T_mkAddr ) ( ( uint32_t ) p_offsetAddr + mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD ], 8 ) );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si le record est de type 'S8' (Start Address 24bits) */
      else if ( p_parser->record [ K_MK_LOADER_SREC_OFFSET_TYPE_FIELD ] == '8' )
      {
         /* Si l'adresse de démarrage doit être récupérée */
         if ( p_startAddr != K_MK_NULL )
         {
            /* Récupération de l'adresse de démarrage (format 24bits) */
            *p_startAddr = ( T_mkAddr ) ( ( uint32_t ) p_offsetAddr + mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD ], 6 ) );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si le record est de type 'S9' (Start Address 16bits) */
      else if ( p_parser->record [ K_MK_LOADER_SREC_OFFSET_TYPE_FIELD ] == '9' )
      {
         /* Si l'adresse de démarrage doit être récupérée */
         if ( p_startAddr != K_MK_NULL )
         {
            /* Récupération de l'adresse de démarrage (format 16bits) */
            *p_startAddr = ( T_mkAddr ) ( ( uint32_t ) p_offsetAddr + mk_loader_srec_hexatoi ( ( T_str8 ) &p_parser->record [ K_MK_LOADER_SREC_OFFSET_ADDRESS_FIELD ], 4 ) );
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
      /* Arrêt du traitement, le fichier est corrompu */
      l_result = K_MK_ERROR_CORRUPTED;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_loader_srec_loadRAM ( T_mkFile* p_file, T_mkAddr p_baseAddr, T_mkAddr* p_startAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_notUsedParam = 0;

   /* Déclaration du parser de fichier */
   T_mkSRECParser l_parser = { 0 };

   /* Si le paramètre est valide (les adresses peuvent être nulle) */
   if ( p_file != K_MK_NULL )
   {
      /* Récupération de la taille du fichier */
      l_result = mk_file_getSize ( p_file, &l_parser.remainingSize, &l_notUsedParam, K_MK_NULL );

      /* Si la taille du fichier est valide */
      if ( l_parser.remainingSize != 0 )
      {
         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Configuration du pointeur de fichier au début de celui-ci */
            l_result = mk_file_seek ( p_file, 0, K_MK_NULL );

            /* Tant que le fichier n'a pas été écrit dans la mémoire et tant qu'aucune erreur ne s'est produite */
            while ( ( l_result == K_MK_OK ) && ( l_parser.remainingSize != 0 ) )
            {
               /* Récupération du prochain record du fichier */
               l_result = mk_loader_srec_getRecord ( p_file, &l_parser );

               /* Si aucune erreur ne s'est produite et si le record est valide */
               if ( ( l_result == K_MK_OK ) && ( l_parser.recordValidity == 1 ) )
               {
                  /* Chargement du record en mémoire */
                  l_result = mk_loader_srec_loadRecord ( &l_parser, p_baseAddr, p_startAddr );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}




