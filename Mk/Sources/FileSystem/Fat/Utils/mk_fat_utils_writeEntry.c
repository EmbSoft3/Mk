/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_fat_utils_writeEntry.c
* @brief Définition de la fonction mk_fat_utils_writeEntry.
* @date 26 déc. 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_setEntry ( T_mkFATEntryDescriptor* p_entry, T_str8 p_fileName, uint32_t p_yymmdd_hhmmss, uint32_t p_cluster, uint8_t p_type, uint8_t p_fileAttribute )
{
   /* Ecriture du nom et de l'extension dans l'entrée */
   _copy ( &p_entry->name, p_fileName, 11 );

   /* Ecriture de l'attribut */
   p_entry->attribute = p_fileAttribute;

   /* Ecriture de la date de création */
   p_entry->creationTime = ( uint16_t ) ( p_yymmdd_hhmmss & 0xFFFF );
   p_entry->creationDate = ( uint16_t ) ( ( p_yymmdd_hhmmss >> 16 ) & 0xFFFF );

   /* Ecriture du type du fichier */
   p_entry->caseType = p_type;

   /* Ecriture de la date du dernier accès */
   p_entry->accessDate = ( uint16_t ) ( ( p_yymmdd_hhmmss >> 16 ) & 0xFFFF );

   /* Ecriture de la date de modification */
   p_entry->modificationTime = ( uint16_t ) ( p_yymmdd_hhmmss & 0xFFFF );
   p_entry->modificationDate = ( uint16_t ) ( ( p_yymmdd_hhmmss >> 16 ) & 0xFFFF );

   /* Ecriture de l'adresse du premier cluster */
   p_entry->firstClusterLow = ( uint16_t ) ( p_cluster & 0xFFFF );
   p_entry->firstClusterHigh = ( uint16_t ) ( ( p_cluster >> 16 ) & 0x0FFF );

   /* Ecriture de la taille du fichier */
   p_entry->fileSize = 0;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_setEntryEX ( T_str8 p_fileName, uint8_t* p_entry, uint8_t p_entryNumber, uint8_t p_mask, uint8_t p_checksum )
{
   /* Déclaration d'un tableau contenant l'offset des caractères dans l'entrée */
   uint8_t l_location [ K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY ] = { 1, 3, 5, 7, 9, 14, 16, 18, 20, 22, 24, 28, 30 };

   /* Déclaration des variables de travail */
   uint8_t l_char = 0, l_counter = 0;
   uint32_t l_currentChar = 0;

   /* Déclaration d'un pointeur d'entrée */
   T_mkFATEntryDescriptor* l_descriptor = ( T_mkAddr ) p_entry;

   /* Réinitialisation de l'entrée */
   _writeWords ( p_entry, 0, sizeof ( T_mkFATEntryDescriptor ) >> 2 );

   /* Ecriture du numéro de la séquence */
   p_entry [ 0 ] = p_entryNumber | p_mask;

   /* Tant la portion de la chaine de caractères correspondant à l'entrée n'a pas été atteinte */
   while ( p_entryNumber > 1 )
   {
      /* Effectue */
      do
      {
         /* Récupération de la valeur d'un caractère de la chaine */
         p_fileName = mk_font_parseString ( p_fileName, &l_currentChar, ( uint32_t ) K_MK_FONT_UTF8 );

         /* Actualisation du compteur */
         l_counter++;
      }

      /* Tant que les 13 caractères de la chaine n'ont pas été analysés */
      while (  l_counter < K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY );

      /* Décrémentation du nombre d'entrées */
      p_entryNumber = ( uint8_t ) ( p_entryNumber - 1 );

      /* Réinitialisation du compteur */
      l_counter = 0;
   }

   /* Récupération de la valeur du premier caractère de la chaine */
   p_fileName = mk_font_parseString ( p_fileName, &l_currentChar, ( uint32_t ) K_MK_FONT_UTF8 );

   /* Tant que les 13 caractères de la chaine n'ont pas été copié */
   while (  l_counter < K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY )
   {
      /* Si la chaine est terminée */
      if ( l_currentChar == 0 )
      {
         /* Ecriture du caractère courant (d'abord 0 puis 0xFF) */
         p_entry [ l_location [ l_counter ] ] = l_char;
         p_entry [ l_location [ l_counter ] + 1 ] = l_char;
         l_char = K_MK_FAT_EXTENDED_PADDING;
      }

      /* Sinon */
      else
      {
         /* Conversion du point de codage en UTF-16 */
         l_currentChar = mk_utils_codeToUtf16 ( l_currentChar );

         /* Ecriture du caractère courant */
         p_entry [ l_location [ l_counter ] ] = ( uint8_t ) l_currentChar;
         p_entry [ l_location [ l_counter ] + 1 ] = ( uint8_t ) ( l_currentChar >> 8 ) ;

         /* Récupération de la valeur du prochain caractère de la chaine */
         p_fileName = mk_font_parseString ( p_fileName, &l_currentChar, ( uint32_t ) K_MK_FONT_UTF8 );
      }

      /* Actualisation du compteur */
      l_counter++;
   }

   /* Ecriture des derniers attributs dans l'entrée */
   l_descriptor->attribute = K_MK_FAT_EXTENDED;
   l_descriptor->checksum = p_checksum;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_getNextBlock ( T_mkFile* p_file, uint32_t* p_currentCluster, uint32_t* p_currentBlock, uint16_t* p_blockIndex )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_currentBlock = *p_currentBlock;
   uint32_t l_currentCluster = *p_currentCluster;
   uint16_t l_blockIndex = *p_blockIndex;

   /* Si le cluster courant est complet */
   if ( l_blockIndex == ( ( uint32_t ) ( p_file->volume->partition.fat.sectorsPerCluster - 1 ) ) )
   {
      /* Actualisation de l'index du bloc de données */
      l_blockIndex = 0;

      /* Création d'un nouveau cluster */
      l_result = mk_fat_utils_appendCluster ( p_file, l_currentCluster, &l_currentCluster, 1 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Actualisation du secteur courant */
         l_currentBlock = p_file->volume->partition.fat.addressOfRootDirectory +
                  ( ( l_currentCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster );
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
      /* Actualisation de l'index du bloc de données */
      l_blockIndex = ( uint16_t ) ( l_blockIndex + 1 );

      /* Actualisation du secteur courant */
      l_currentBlock = ( uint32_t ) ( l_currentBlock + 1 );
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Lecture du nouveau secteur */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) l_currentBlock );

      /* Actualisation des variables de retour */
      *p_currentBlock = l_currentBlock;
      *p_currentCluster = l_currentCluster;
      *p_blockIndex = l_blockIndex;
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

static T_mkCode mk_fat_utils_writeEntryLA ( T_mkFile* p_file, T_mkFATHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une entrée */
   T_mkFATEntryDescriptor* l_entry;

   /* Déclaration des variables de travail */
   T_mkFATEntryAddress l_lastEntryAddr = {
         ( uint16_t ) p_handler->entryBlockIndex,
         ( uint16_t ) p_handler->blockIndex,
         ( uint32_t ) p_handler->currentBlock,
         ( uint32_t ) p_handler->currentCluster
   };

   /* Si l'entrée n'est pas localisée sur un autre secteur */
   if ( l_lastEntryAddr.entryIndex < ( p_file->volume->partition.fat.numberOfEntriesPerSector - 1 ) )
   {
      /* Actualisation de l'index de l'entrée */
      l_lastEntryAddr.entryIndex = ( uint16_t ) ( l_lastEntryAddr.entryIndex + 1 );

      /* Lecture du secteur courant */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) l_lastEntryAddr.currentBlock );
   }

   /* Sinon */
   else
   {
      /* Réinitialisation de l'offset de l'entrée */
      l_lastEntryAddr.entryIndex = K_MK_FAT_FIRST_ENTRY_OFFSET;

      /* Détermination de l'adresse puis lecture du prochain bloc de données */
      l_result = mk_fat_utils_getNextBlock ( p_file, &l_lastEntryAddr.currentCluster, &l_lastEntryAddr.currentBlock, &l_lastEntryAddr.blockIndex );
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Actualisation de l'offset de l'entrée */
      l_entry = ( T_mkAddr ) ( ( uint8_t* ) &p_file->buf [ l_lastEntryAddr.entryIndex * K_MK_FAT_ENTRY_SIZE ] );

      /* Configuration de la troisième entrées */
      mk_fat_utils_setEntry ( l_entry, ( T_str8 ) "\0          ", 0, 0, 0, 0 );

      /* Actualisation du secteur courant */
      l_result = mk_fat_utils_writeCache ( p_file, ( uint64_t ) l_lastEntryAddr.currentBlock );
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

static T_mkCode mk_fat_utils_writeEntrySP ( T_mkFile* p_file, T_mkFATHandler* p_handler, uint32_t p_yymmdd_hhmmss )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une entrée */
   T_mkFATEntryDescriptor* l_entry;

   /* Actualisation de l'adresse de la première entrée */
   l_entry = ( T_mkAddr ) ( ( uint8_t* ) &p_file->buf [ 0 ] );

   /* Lecture du secteur courant */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) p_handler->currentBlock );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration de la première entrée */
      mk_fat_utils_setEntry ( l_entry, ( T_str8 ) ".          ", p_yymmdd_hhmmss, p_handler->firstDataCluster, 0, K_MK_FAT_SUBDIRECTORY );

      /* Actualisation de l'adresse de la deuxième entrées */
      l_entry = ( T_mkAddr ) ( ( uint8_t* ) &p_file->buf [ K_MK_FAT_ENTRY_SIZE ] );

      /* Configuration de la deuxième entrées */
      mk_fat_utils_setEntry ( l_entry, ( T_str8 ) "..         ", p_yymmdd_hhmmss, p_handler->directoryCluster, 0, K_MK_FAT_SUBDIRECTORY );

      /* Actualisation de l'adresse de la troisième entrées */
      l_entry = ( T_mkAddr ) ( ( uint8_t* ) &p_file->buf [ 2 * K_MK_FAT_ENTRY_SIZE ] );

      /* Configuration de la troisième entrées */
      mk_fat_utils_setEntry ( l_entry, ( T_str8 ) "\0          ", 0, 0, 0, 0 );

      /* Actualisation du secteur courant */
      l_result = mk_fat_utils_writeCache ( p_file, ( uint64_t ) p_handler->currentBlock );
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

static T_mkCode mk_fat_utils_writeEntryST ( T_mkFile* p_file, T_mkFATHandler* p_handler, T_str8 p_fileName, uint8_t p_fileAttribute, uint32_t p_yymmdd_hhmmss )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable stockant le nom du fichier au format 8.3 + '\0' */
   int8_t l_fatEntryName [ K_MK_FAT_ENTRY_NAME_SIZE + K_MK_FAT_ENTRY_EXTENSION_SIZE + 1 ];

   /* Déclaration d'une variable stockant le type de casse */
   uint8_t l_caseType = 0;

   /* Déclaration d'une entrée */
   T_mkFATEntryDescriptor* l_entry;

   /* Ecriture d'une entrée marquant la fin du répertoire */
   l_result = mk_fat_utils_writeEntryLA ( p_file, p_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Lecture du secteur courant */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) p_handler->currentBlock );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Récupération du nom de fichier au format 8.3 + \0 */
         l_result = mk_fat_utils_setName ( p_fileName, ( T_str8 ) l_fatEntryName, &l_caseType, K_MK_NULL, K_MK_FAT_ENTRY_ST, 0 );

         /* Si aucune erreur ne s'est produtie */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation de l'offset de l'entrée */
            l_entry = ( T_mkAddr ) ( ( uint8_t* ) &p_file->buf [ p_handler->entryBlockIndex * K_MK_FAT_ENTRY_SIZE ] );

            /* Configuration de l'entrée */
            mk_fat_utils_setEntry ( l_entry, ( T_str8 ) l_fatEntryName, p_yymmdd_hhmmss, p_handler->firstDataCluster, l_caseType, p_fileAttribute );

            /* Actualisation du secteur courant */
            l_result = mk_fat_utils_writeCache ( p_file, ( uint64_t ) p_handler->currentBlock );

            /* Si aucune erreur ne s'est produtie */
            if ( l_result == K_MK_OK )
            {
               /* Détermination de l'offset de l'entrée par rapport à son cluster */
               p_handler->entryClusterIndex = ( uint16_t ) ( ( p_handler->blockIndex * p_file->volume->partition.fat.numberOfEntriesPerSector ) + p_handler->entryBlockIndex );

               /* Actualisation de l'offset de l'entrée virtuelle */
               p_handler->entryVirtualClusterIndex = K_MK_FAT_VIRTUAL_ENTRY_DEFAULT;

               /* Détermination de l'adresse du cluster de l'entrée */
               p_handler->entryCluster = p_handler->currentCluster;

               /* Actualisation de l'adresse virtuelle du cluster de l'entrée  */
               p_handler->entryVirtualCluster = K_MK_FAT_VIRTUAL_CLUSTER_DEFAULT;

               /* Initialisation des attributs du fichier */
               l_result = mk_fat_utils_setFile ( p_file, p_handler, 0 );
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

static T_mkCode mk_fat_utils_writeEntryEX ( T_mkFile* p_file, T_mkFATHandler* p_handler, T_str8 p_fileName, uint8_t p_fileAttribute, uint32_t p_yymmdd_hhmmss )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_counter, l_virtualCluster, l_virtualEntry ;

   /* Déclaration d'une variable stockant le nom du fichier au format 8.3 + '\0' */
   uint8_t l_fatEntryName [ K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY + 1 ];

   /* Déclaration d'une entrée */
   T_mkFATEntryDescriptor* l_entry;

   /* Récupération du nombre d'entrées nécessaires pour coder le nom du fichier */
   l_counter = ( uint16_t ) mk_fat_utils_getNumberOfEntries ( p_fileName );
   p_handler->entryVirtualNumber = ( uint16_t ) l_counter;

   /* Détermination de l'adresse de base du bloc où doit être écrite l'entrée */
   p_handler->entryBlock = p_file->volume->partition.fat.addressOfRootDirectory +
            ( ( p_handler->currentCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster );

   /* Enregistrement du cluster où est localisé l'entrée virtuelle */
   l_virtualCluster = p_handler->currentCluster;

   /* Détermination de l'index de l'entrée virtuelle */
   l_virtualEntry = ( uint16_t ) ( ( ( p_handler->currentBlock - p_handler->entryBlock ) * p_file->volume->partition.fat.numberOfEntriesPerSector ) + p_handler->entryBlockIndex );

   /* Génération d'un nom de fichier unique puis récupération de son CRC */
   l_result = mk_fat_utils_findName ( p_file, p_handler, p_fileName, ( T_str8 ) l_fatEntryName, &p_handler->entryChecksum );

   /* Si un nom de fichier unique a été trouvé */
   if ( l_result == K_MK_ERROR_NOT_FOUND )
   {
      /* Lecture du secteur où l'entrée doit être écrite */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) p_handler->currentBlock );

      /* Si aucune erreur ne s'est produtie */
      if ( l_result == K_MK_OK )
      {
         /* Tant que l'intégralité des entrées à écrire n'ont pas été écrites */
         while ( ( l_result == K_MK_OK ) && ( l_counter != 0 ) )
         {
            /* Actualisation de l'offset de l'entrée */
            l_entry = ( T_mkAddr ) ( ( uint8_t* ) &p_file->buf [ p_handler->entryBlockIndex * K_MK_FAT_ENTRY_SIZE ] );

            /* Si dernière entrée */
            if ( l_counter == p_handler->entryVirtualNumber )
            {
               /* Création d'une entrée particulière indiquant la fin de chaine */
               mk_fat_utils_setEntryEX ( p_fileName, ( uint8_t* ) l_entry, ( uint8_t ) l_counter, K_MK_FAT_EXTENDED_ENTRY_MASK, p_handler->entryChecksum );
            }

            /* Sinon */
            else
            {
               /* Création d'une entrée contenant les caractères étendus du nom */
               mk_fat_utils_setEntryEX ( p_fileName, ( uint8_t* ) l_entry, ( uint8_t ) l_counter, 0, p_handler->entryChecksum );
            }

            /* Si un nouveau secteur doit être lu (dernière entrée) */
            if ( p_handler->entryBlockIndex == ( p_file->volume->partition.fat.numberOfEntriesPerSector - 1 ) )
            {
               /* Actualisation du secteur courant */
               l_result = mk_fat_utils_writeCache ( p_file, ( uint64_t ) p_handler->currentBlock );

               /* Si aucune erreur ne s'est produtie */
               if ( l_result == K_MK_OK )
               {
                  /* Détermination de l'adresse puis lecture du prochain bloc de données */
                  l_result = mk_fat_utils_getNextBlock ( p_file, &p_handler->currentCluster, &p_handler->currentBlock, ( uint16_t* ) &p_handler->blockIndex );

                  /* Actualisation de l'index de la prochaine entrée */
                  p_handler->entryBlockIndex = 0;
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
               /* Actualisation de l'index de la prochaine entrée */
               p_handler->entryBlockIndex = ( uint16_t ) ( p_handler->entryBlockIndex + 1 );
            }

            /* Actualisation du nombre d'entrées restant à écrire */
            l_counter--;
         }

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation du secteur courant */
            l_result = mk_fat_utils_writeCache ( p_file, ( uint64_t ) p_handler->currentBlock );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Les entrées étendues ont été écrites, il est temps de créer l'entrée standard */
               /* Ecriture d'une entrée au format standard */
               l_result = mk_fat_utils_writeEntryST ( p_file, p_handler, ( T_str8 ) l_fatEntryName, p_fileAttribute, p_yymmdd_hhmmss );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Mise à jour des données du fichier */
                  p_file->descriptor.fat.virtualEntryIndex   = ( uint16_t ) l_virtualEntry;
                  p_file->descriptor.fat.virtualEntryCluster = ( uint32_t ) l_virtualCluster;
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
         /* Ne rien faire */
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_COLLISION;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_writeEntry ( T_mkFile* p_file, T_str8 p_fileName, uint8_t p_fileAttribute, T_mkFATEntryType p_type, T_mkFATHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_yymmdd_hhmmss = 0;
   uint16_t l_date = 0, l_time = 0;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_fileName != K_MK_NULL ) && ( p_handler != K_MK_NULL ) )
   {
      /* Récupération de la valeur du calendrier système au format FAT */
      l_result = mk_fat_utils_getDate ( &l_date, &l_time );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Concaténation du calendrier dans un variable 32 bits */
         l_yymmdd_hhmmss = ( ( ( uint32_t ) l_date << 16 ) | l_time );

         /* Si les deux entrées spéciales doivent être écrites */
         if ( p_type == K_MK_FAT_ENTRY_SP )
         {
            /* Ecriture des deux entrées spéciales ('.' et '..') */
            l_result = mk_fat_utils_writeEntrySP ( p_file, p_handler, l_yymmdd_hhmmss );
         }

         /* Sinon si une entrée standard doit être écrite */
         else if ( p_type == K_MK_FAT_ENTRY_ST )
         {
            /* Ecriture d'une entrée au format 8.3 */
            l_result = mk_fat_utils_writeEntryST ( p_file, p_handler, p_fileName, p_fileAttribute, l_yymmdd_hhmmss );
         }

         /* Sinon si une entrée étendue doit être écrite */
         else if ( p_type == K_MK_FAT_ENTRY_EX )
         {
            /* Ecriture d'une entrée au format étendu */
            l_result = mk_fat_utils_writeEntryEX ( p_file, p_handler, p_fileName, p_fileAttribute, l_yymmdd_hhmmss );
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


