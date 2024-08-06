/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_file_handle.c
* @brief Définition de la fonction mk_file_handle.
* @date 26 juin 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleAlloc ( T_mkFileMessage* p_message, uint8_t* p_buf )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de fichier */
   T_mkFile** l_file = ( T_mkFile** ) p_message->argument2;

   /* Allocation d'un nouveau fichier */
   l_result = mk_pool_allocSafe ( g_mkFileArea.pool, ( T_mkAddr* ) l_file, K_MK_POOL_CLEAR, 0 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration du cache */
      (*l_file)->cacheBaseAddress = p_buf;
      (*l_file)->cacheCurrentAddress = 0;
      (*l_file)->cacheFlushFlag = 0;
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

static T_mkCode mk_file_handleFileInstance ( T_mkFile* p_file, uint8_t* p_buf )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'une variable de travail */
   uint32_t l_modulo = 0;

   /* Si l'instance du fichier est valide */
   if ( ( p_file >=  &g_mkFileArea.heap[0] ) &&
        ( p_file < ( &g_mkFileArea.heap[0] + K_MK_FILE_NUMBER ) ) )
   {
      /* Vérification de l'alignement de l'adresse */
      l_modulo = _math_mod ( ( uint32_t ) p_file - ( uint32_t ) &g_mkFileArea.heap[0], sizeof ( T_mkFile ) );

      /* Si l'adresse est alignée et si un volume a été assigné */
      if ( ( l_modulo == 0 ) && ( p_file->volume != K_MK_NULL ) )
      {
         /* Actualisation de la variable de retour */
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
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration du cache */
      p_file->cacheBaseAddress = p_buf;
      p_file->cacheCurrentAddress = 0;
      p_file->cacheFlushFlag = 0;
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

static T_mkCode mk_file_searchVolume ( T_mkFileMessage* p_message, T_mkDisk* p_disk )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération d'un pointeur de volume */
   T_mkVolume* l_volume = K_MK_NULL;

   /* Récupération de l'adresse de la chaine de caractère stockant le chemin du fichier */
   T_str8 l_filePath = ( T_str8 ) p_message->argument3;

   /* Déclaration d'un buffer de données */
   char8_t l_strBuf [ 28 ] = { '/', '\0' };

   /* Déclaration des variables de travail */
   uint32_t l_length = 0, l_ret = 0;

   /* Le but est de récupérer l'instance de la partition spécifiée par l'utilisateur */
   /* Pour le nombre de disques connectés au système */
   for ( ; ( l_result == K_MK_OK ) && ( p_disk != K_MK_NULL ) && ( p_message->argument1 == K_MK_NULL ) ; )
   {
      /* Concaténation du nom du disque dans la variable de travail */
      mk_utils_strcat ( ( T_str8 ) &l_strBuf [ 1 ], ( T_str8 ) p_disk->name.id, ( T_str8 ) "/" );

      /* Récupération de la longueur de la chaine de caractères */
      l_length = mk_utils_strlen ( ( T_str8 ) l_strBuf );

      /* Récupération de l'adresse de la première partition du disque */
      l_result = mk_disk_getFirstVolume ( p_disk, &l_volume );

      /* Pour le nombre de partitions présentes sur le disque */
      for ( ; ( l_result == K_MK_OK ) && ( l_volume != K_MK_NULL ) ; )
      {
         /* Concaténation du nom de la partition dans la variable de travail */
         mk_utils_strcat ( ( T_str8 ) &l_strBuf [ l_length ], ( T_str8 ) l_volume->name.str, ( T_str8 ) "/" );

         /* Récupération de la longueur de la chaine de caractères */
         l_length = mk_utils_strlen ( ( T_str8 ) l_strBuf );

         /* Réalisation d'une comparaison entre le nom de la partition et */
         /* la chaine de caractères utilisateur */
         l_ret = mk_utils_strcomp ( ( T_str8 ) l_strBuf, l_filePath, 0, l_length );

         /* Si la partition est la partition recherchée */
         if ( l_ret == 1 )
         {
            /* Actualisation de la valeur des paramètres de la requête */
            p_message->argument3 = &l_filePath [ l_length ];
            p_message->argument1 = l_volume;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Récupération de l'adresse de la prochaine partition */
         l_result = mk_disk_getNextVolume ( &l_volume, l_volume );
      }

      /* Récupération de l'adresse du prochain disque */
      p_disk = p_disk->nextDisk;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_searchVolumeByDevices ( T_mkFileMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de disque */
   T_mkDisk* l_disk = K_MK_NULL;

   /* Déclaration d'un pointeur de périphérique MMC */
   T_mkMMCDevice* l_mmcDevice = K_MK_NULL;

   /* Déclaration d'un pointeur de périphérique MSC */
   T_mkMSCDevice* l_mscDevice = K_MK_NULL;

   /* Récupération de l'adresse du premier périphérique MMC */
   l_result = mk_mmc_getFirstDevice ( &l_mmcDevice );

   /* Pour le nombre de périphériques MMC connectés au système */
   for ( ; ( l_result == K_MK_OK ) && ( l_mmcDevice != K_MK_NULL ) && ( p_message->argument1 == K_MK_NULL ) ; )
   {
      /* Récupération de l'adresse du premier disque enregistré */
      /* Les périphériques MMC ne possède qu'un disque */
      l_result = mk_mmc_getFirstDisk ( l_mmcDevice, &l_disk );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Recherche de la partition demandée par l'utilisateur */
         l_result = mk_file_searchVolume ( p_message, l_disk );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Récupération de l'adresse du prochain périphérique MMC */
      l_result = mk_mmc_getNextDevice ( &l_mmcDevice, l_mmcDevice );
   }

   /* Récupération de l'adresse du premier périphérique MSC */
   l_result = mk_msc_getFirstDevice ( &l_mscDevice );

   /* Pour le nombre de périphérique MSC connectés au système */
   for ( ; ( l_result == K_MK_OK ) && ( l_mscDevice != K_MK_NULL ) && ( p_message->argument1 == K_MK_NULL ) ; )
   {
      /* Récupération de l'adresse du premier disque enregistré */
      l_result = mk_msc_getFirstDisk ( l_mscDevice, &l_disk );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Recherche de la partition demandée par l'utilisateur sur tous les disques */
         l_result = mk_file_searchVolume ( p_message, l_disk );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Récupération de l'adresse du prochain périphérique MSC */
      l_result = mk_msc_getNextDevice ( &l_mscDevice, l_mscDevice );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleFilePath ( T_mkFileMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de la chaine de caractère stockant le chemin du fichier */
   T_str8 l_filePath = ( T_str8 ) p_message->argument3;

   /* Récupération de l'adresse de la partition spécifiée par l'utilisateur */
   T_mkVolume* l_volume = ( T_mkVolume* ) p_message->argument1;

   /* Si l'instance de la partition est nulle */
   if ( l_volume == K_MK_NULL )
   {
      /* Si le caractère spécial '/' n'est pas présent en début de chaine, */
      /* on utilise le disque système par défaut. */
      if ( l_filePath [ 0 ] != '/' )
      {
         /* Configuration de l'argument de la requête */
         p_message->argument1 = g_mkSystemVolume;
      }

      /* Sinon */
      else
      {
         /* Recherche de la partition demandée par l'utilisateur */
         l_result = mk_file_searchVolumeByDevices ( p_message );

         /* Si la partition n'a pas été trouvée */
         if ( p_message->argument1 == K_MK_NULL )
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
   }

   /* Sinon */
   else
   {
      /* L'instance du volume est non nulle, l'accès disque sera réalisé sur */
      /* le volume spécifié par l'utilisateur. */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkDisk* mk_file_getDiskHandle ( T_mkFileMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkDisk* l_result = K_MK_NULL;

   /* Déclaration d'un pointeur de partition */
   T_mkVolume* l_volume = p_message->argument1;

   /* Déclaration d'un pointeur de fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Si l'adresse du disque est contenue dans la partition (requête d'ouverture de fichier) */
   if ( ( p_message->requestIdentifier == K_MK_FS_OPEN ) ||
        ( p_message->requestIdentifier == K_MK_FS_OPEN_DIRECTORY ) || ( p_message->requestIdentifier == K_MK_FS_OPEN_RELATIVE ) ||
        ( p_message->requestIdentifier == K_MK_FS_STAT ) )
   {
      /* Actualisation de l'adresse du disque */
      l_result = ( T_mkDisk* ) l_volume->disk;
   }

   /* Sinon */
   else
   {
      /* L'adresse du disque est contenue dans l'instance du fichier */
      /* Actualisation de l'adresse du disque */
      l_result = l_file->volume->disk;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleOpenRequest ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   T_mkFileMode l_fileMode = ( T_mkFileMode ) ( ( ( uint32_t* ) p_message->argument5 ) );

   /* Récupération de l'instance de la partition */
   T_mkVolume* l_volume = p_message->argument1;

   /* Récupération de l'instance du fichier */
   T_mkFile** l_file = p_message->argument2;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_open ( l_volume, *l_file, p_message->argument3,
                               l_volume->partition.fat.firstRootDirectoryCluster, l_fileMode );

      /* Si une fonction de rappel a été référencée */
      if ( ( l_result == K_MK_OK ) && ( p_message->callback != K_MK_NULL ) )
      {
         /* Enregistrement de l'instance du fichier dans la structure de rappel */
         /* Cet argument est transmis peut importe le résultat de la fonction */
         p_callbackParam->param2 = ( T_mkAddr ) ( *l_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleOpenDirectoryRequest ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance de la partition */
   T_mkVolume* l_volume = p_message->argument1;

   /* Récupération de l'instance du fichier */
   T_mkFile** l_file = p_message->argument2;

   /* Récupération de l'instance du répertoire */
   T_mkFile* l_directory = p_message->argument3;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_openDirectory ( l_volume, *l_file, ( uint32_t ) l_directory->descriptor.fat.firstCluster,
                                      ( uint16_t ) ( uint32_t ) p_message->argument4, ( uint32_t ) p_message->argument5 );

      /* Si une fonction de rappel a été référencée */
      if ( ( l_result == K_MK_OK ) && ( p_message->callback != K_MK_NULL ) )
      {
         /* Enregistrement de l'instance du fichier dans la structure de rappel */
         /* Cet argument est transmis peut importe le résultat de la fonction */
         p_callbackParam->param2 = ( T_mkAddr ) ( *l_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleOpenRelativeRequest ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance de la partition */
   T_mkVolume* l_volume = p_message->argument1;

   /* Récupération de l'instance du fichier */
   T_mkFile** l_file = p_message->argument2;

   /* Récupération de l'instance du répertoire */
   T_mkFile* l_directory = p_message->argument3;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_open ( l_volume, *l_file, ( T_str8 ) p_message->argument4,
                               ( uint32_t ) l_directory->descriptor.fat.firstCluster,
                               ( uint32_t ) p_message->argument5 );

      /* Si une fonction de rappel a été référencée */
      if ( ( l_result == K_MK_OK ) && ( p_message->callback != K_MK_NULL ) )
      {
         /* Enregistrement de l'instance du fichier dans la structure de rappel */
         /* Cet argument est transmis peut importe le résultat de la fonction */
         p_callbackParam->param2 = ( T_mkAddr ) ( *l_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleChmodRequest ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_chmod ( l_file, ( uint8_t ) ( uint32_t ) ( p_message->argument4 ) );

      /* Si une fonction de rappel a été référencée */
      if ( p_message->callback != K_MK_NULL )
      {
         /* Enregistrement de l'instance du fichier dans la structure de rappel */
         /* Cet argument est transmis peut importe le résultat de la fonction */
         p_callbackParam->param2 = ( T_mkAddr ) ( l_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleCloseRequest ( T_mkFileMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_close ( l_file );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Désallocation du fichier */
         l_result = mk_pool_freeSafe ( g_mkFileArea.pool, ( T_mkAddr ) ( l_file ) );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleEofRequest ( T_mkFileMessage* p_message, T_mkTask* p_task, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Vérification de la validité du paramètre de retour */
   uint32_t l_area = _mk_memory_isPrivilegedArea ( p_message->argument5 );

   /* Si l'argument de retour est situé en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le fichier est stocké dans une partition FAT32 */
      if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
      {
         /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
         l_result = mk_fat_eof ( l_file, ( uint32_t* ) p_message->argument5 );

         /* Si une fonction de rappel a été référencée */
         if ( p_message->callback != K_MK_NULL )
         {
            /* Enregistrement de l'instance du fichier dans la structure de rappel */
            /* Cet argument est transmis peut importe le résultat de la fonction */
            p_callbackParam->param2 = ( T_mkAddr ) ( l_file );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Ecriture du résultat de la fonction dans la structure de rappel */
               p_callbackParam->param3 = ( T_mkAddr ) ( p_message->argument5 );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleExpandRequest ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_expand ( l_file, ( uint32_t ) p_message->argument4 );

      /* Si une fonction de rappel a été référencée */
      if ( p_message->callback != K_MK_NULL )
      {
         /* Enregistrement de l'instance du fichier dans la structure de rappel */
         /* Cet argument est transmis peut importe le résultat de la fonction */
         p_callbackParam->param2 = ( T_mkAddr ) ( l_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleGetNameRequest ( T_mkFileMessage* p_message, T_mkTask* p_task, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Vérification de la validité des paramètres de la requête */
   l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument3 ) );
   l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument3 ) + K_MK_FILE_MAX_NAME_LENGTH );

   /* Si le buffer de retour est situé en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le fichier est stocké dans une partition FAT32 */
      if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
      {
         /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
         l_result = mk_fat_getName ( l_file, ( T_str8 ) p_message->argument3 );

         /* Si une fonction de rappel a été référencée */
         if ( p_message->callback != K_MK_NULL )
         {
            /* Enregistrement de l'instance du fichier dans la structure de rappel */
            /* Cet argument est transmis peut importe le résultat de la fonction */
            p_callbackParam->param2 = ( T_mkAddr ) ( l_file );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Ecriture de l'adresse de la chaine de caractères dans la structure de rappel */
               p_callbackParam->param3 = ( T_mkAddr ) p_message->argument3;
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleLinkRequest ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_link ( l_file, ( T_str8 ) p_message->argument3, l_file->volume->partition.fat.firstRootDirectoryCluster );

      /* Si une fonction de rappel a été référencée */
      if ( p_message->callback != K_MK_NULL )
      {
         /* Enregistrement de l'instance du fichier dans la structure de rappel */
         /* Cet argument est transmis peut importe le résultat de la fonction */
         p_callbackParam->param2 = ( T_mkAddr ) ( l_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleReadRequest ( T_mkFileMessage* p_message, T_mkTask* p_task, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Déclaration de la table des clusters */
   uint32_t l_clusterMap [ K_MK_FAT_CLUSTER_MAP_LENGTH ];

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Vérification de la validité des paramètres de la requête */
   l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument3 ) );
   l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument3 ) + ( uint32_t ) p_message->argument4 );
   l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument5 ) );

   /* Si les arguments de retour sont situés en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le fichier est stocké dans une partition FAT32 */
      if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
      {
         /* Analyse du type de la mémoire */
         l_area  = _mk_memory_isDmaArea ( ( uint8_t* ) ( p_message->argument3 ) );
         l_area |= _mk_memory_isDmaArea ( ( uint8_t* ) ( p_message->argument3 ) + ( uint32_t ) p_message->argument4 );

         /* Si la mémoire n'est pas de la mémoire DMA */
         if ( l_area == K_MK_AREA_CACHEABLE )
         {
            /* Il est nécessaire d'actualiser le cache */
            _cortex_cleanEntireDataCache ( );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Configuration de la table des clusters */
         l_file->descriptor.fat.clusterMap = l_clusterMap;

         /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
         l_result = mk_fat_read ( l_file, p_message->argument3, ( uint32_t ) p_message->argument4, ( uint32_t* ) p_message->argument5 );

         /* Si une fonction de rappel a été référencée */
         if ( p_message->callback != K_MK_NULL )
         {
            /* Enregistrement de l'instance du fichier dans la structure de rappel */
            /* Cet argument est transmis peut importe le résultat de la fonction */
            p_callbackParam->param2 = ( T_mkAddr ) ( l_file );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Configuration des arguments de la structure de rappel */
               p_callbackParam->param3 = ( T_mkAddr ) ( p_message->argument3 );
               p_callbackParam->param4 = ( T_mkAddr ) ( p_message->argument4 );
               p_callbackParam->param5 = ( T_mkAddr ) ( p_message->argument5 );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleRenameRequest ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_rename ( l_file, ( T_str8 ) p_message->argument3, l_file->volume->partition.fat.firstRootDirectoryCluster );

      /* Si une fonction de rappel a été référencée */
      if ( p_message->callback != K_MK_NULL )
      {
         /* Enregistrement de l'instance du fichier dans la structure de rappel */
         /* Cet argument est transmis peut importe le résultat de la fonction */
         p_callbackParam->param2 = ( T_mkAddr ) ( l_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleSeekRequest ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_seek ( l_file, ( uint32_t ) p_message->argument4 );

      /* Si une fonction de rappel a été référencée */
      if ( p_message->callback != K_MK_NULL )
      {
         /* Enregistrement de l'instance du fichier dans la structure de rappel */
         /* Cet argument est transmis peut importe le résultat de la fonction */
         p_callbackParam->param2 = ( T_mkAddr ) ( l_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleStatRequest ( T_mkFileMessage* p_message, uint8_t* p_buf )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de répertoire */
   T_mkFile l_directory;

   /* Récupération de l'instance de la partition */
   T_mkVolume* l_volume = p_message->argument1;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Si la requête doit être effectuée de manière relative */
      if ( p_message->argument4 != K_MK_NULL )
      {
         /* Réinitialisation de l'instance du fichier */
         _writeWords ( &l_directory, 0, sizeof ( T_mkFile ) >> 2 );

         /* Configuration de l'adresse du cache */
         l_directory.cacheBaseAddress = p_buf;

         /* Ouverture du répertoire */
         l_result = mk_fat_open ( l_volume, &l_directory, ( T_str8 ) p_message->argument3,
                                  ( uint32_t ) l_volume->partition.fat.firstRootDirectoryCluster,
                                  ( uint32_t ) ( K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ ) );

         /* Si l'ouverture du répertoire a réussi */
         if ( l_result == K_MK_OK )
         {
            /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
            l_result = mk_fat_stat ( l_volume, ( T_str8 ) p_message->argument4, l_directory.descriptor.fat.firstCluster, p_buf );

            /* Fermeture du répertoire */
            l_result |= mk_fat_close ( &l_directory );
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
         /* La requête est effectuée de manière absolue. */
         /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
         l_result = mk_fat_stat ( l_volume, ( T_str8 ) p_message->argument3, l_volume->partition.fat.firstRootDirectoryCluster, p_buf );
      }

      /* Le cache ne doit pas être invalidé car le buffer 'p_buf' pointe vers la donnée */
      /* mk_file_handle qui n'est pas cachable. */
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleTellRequest ( T_mkFileMessage* p_message, T_mkTask* p_task, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Vérification de la validité du paramètre de retour */
   uint32_t l_area = _mk_memory_isPrivilegedArea ( p_message->argument5 );

   /* Si l'argumnet de retour est situé en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le fichier est stocké dans une partition FAT32 */
      if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
      {
         /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
         l_result = mk_fat_tell ( l_file, ( uint32_t* ) p_message->argument4 );

         /* Si une fonction de rappel a été référencée */
         if ( p_message->callback != K_MK_NULL )
         {
            /* Enregistrement de l'instance du fichier dans la structure de rappel */
            /* Cet argument est transmis peut importe le résultat de la fonction */
            p_callbackParam->param2 = ( T_mkAddr ) ( l_file );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Ecriture du résultat de la fonction */
               p_callbackParam->param3 = ( T_mkAddr ) ( p_message->argument4 );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleTruncateRequest ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_truncate ( l_file );

      /* Si une fonction de rappel a été référencée */
      if ( p_message->callback != K_MK_NULL )
      {
         /* Enregistrement de l'instance du fichier dans la structure de rappel */
         /* Cet argument est transmis peut importe le résultat de la fonction */
         p_callbackParam->param2 = ( T_mkAddr ) ( l_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleUnlinkRequest ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
      l_result = mk_fat_unlink ( l_file );

      /* Si une fonction de rappel a été référencée */
      if ( p_message->callback != K_MK_NULL )
      {
         /* Enregistrement de l'instance du fichier dans la structure de rappel */
         /* Cet argument est transmis peut importe le résultat de la fonction */
         p_callbackParam->param2 = ( T_mkAddr ) ( l_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleWriteRequest ( T_mkFileMessage* p_message, T_mkTask* p_task, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Déclaration de la table des clusters */
   uint32_t l_clusterMap [ K_MK_FAT_CLUSTER_MAP_LENGTH ];

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Vérification de la validité du paramètre de retour */
   l_area = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument5 ) );

   /* Si l'argument de retour est situé en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le fichier est stocké dans une partition FAT32 */
      if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
      {
         /* Analyse du type de la mémoire */
         l_area  = _mk_memory_isDmaArea ( ( uint8_t* ) ( p_message->argument3 ) );
         l_area |= _mk_memory_isDmaArea ( ( uint8_t* ) ( p_message->argument3 ) + ( uint32_t ) p_message->argument4 );

         /* Si la mémoire n'est pas de la mémoire DMA */
         if ( l_area == K_MK_AREA_CACHEABLE )
         {
            /* Nettoyage du cache */
            _cortex_cleanEntireDataCache ( );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Configuration de la table des clusters */
         l_file->descriptor.fat.clusterMap = l_clusterMap;

         /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
         l_result = mk_fat_write ( l_file, p_message->argument3, ( uint32_t ) p_message->argument4, ( uint32_t* ) p_message->argument5 );

         /* Si une fonction de rappel a été référencée */
         if ( p_message->callback != K_MK_NULL )
         {
            /* Enregistrement de l'instance du fichier dans la structure de rappel */
            /* Cet argument est transmis peut importe le résultat de la fonction */
            p_callbackParam->param2 = ( T_mkAddr ) ( l_file );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Configuration des arguments de la structure de rappel */
               p_callbackParam->param3 = ( T_mkAddr ) ( p_message->argument4 );
               p_callbackParam->param4 = ( T_mkAddr ) ( p_message->argument5 );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleFileInfoRequest ( T_mkFileMessage* p_message, T_mkTask* p_task, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Vérification de la validité de l'instance de retour */
   l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument3 ) );
   l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument3 ) + ( uint32_t ) sizeof ( T_mkFileInfo ) );

   /* Si l'argument de retour est située en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le fichier est stocké dans une partition FAT32 */
      if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
      {
         /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
         l_result = mk_fat_getInfo ( l_file, p_message->argument3 );

         /* Si une fonction de rappel a été référencée */
         if ( p_message->callback != K_MK_NULL )
         {
            /* Enregistrement de l'instance du fichier dans la structure de rappel */
            /* Cet argument est transmis peut importe le résultat de la fonction */
            p_callbackParam->param2 = ( T_mkAddr ) ( l_file );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Configuration de l'argument de la structure de rappel */
               p_callbackParam->param3 = ( T_mkAddr ) ( p_message->argument3 );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleSizeRequest ( T_mkFileMessage* p_message, T_mkTask* p_task, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une structure d'information */
   T_mkFileInfo l_info;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Récupération de l'adresse des variables stockant la taille du fichier */
   uint32_t* l_lowFileSize = p_message->argument3;
   uint32_t* l_highFileSize = p_message->argument4;

   /* Vérification de la validité des arguments de retour */
   l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument3 ) );
   l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument4 ) );

   /* Si les arguments de retour situés en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le fichier est stocké dans une partition FAT32 */
      if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
      {
         /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
         l_result = mk_fat_getInfo ( l_file, &l_info );

         /* Si une fonction de rappel a été référencée */
         if ( p_message->callback != K_MK_NULL )
         {
            /* Enregistrement de l'instance du fichier dans la structure de rappel */
            /* Cet argument est transmis peut importe le résultat de la fonction */
            p_callbackParam->param2 = ( T_mkAddr ) ( l_file );
            p_callbackParam->param3 = ( T_mkAddr ) 0;
            p_callbackParam->param4 = ( T_mkAddr ) 0;

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Configuration des arguments de la structure de rappel */
               p_callbackParam->param3 = ( T_mkAddr ) l_info.fat.fileSize;
               p_callbackParam->param4 = ( T_mkAddr ) 0;
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
            /* Configuration des paramètres de retour */
            /* La taille des fichiers est sur 32bits en FAT32 */
            *l_lowFileSize = l_info.fat.fileSize;
            *l_highFileSize = 0;
         }
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
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

static T_mkCode mk_file_handleTypeRequest ( T_mkFileMessage* p_message, T_mkTask* p_task, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une structure d'information */
   T_mkFileInfo l_info;

   /* Déclaration des variables de travail */
   uint32_t l_area = 0, l_localType = 0;

   /* Récupération de l'instance du fichier */
   T_mkFile* l_file = p_message->argument2;

   /* Récupération de l'adresse de la variable stockant le type du fichier */
   uint32_t* l_type = p_message->argument3;

   /* Vérification de la validité de l'argument de retour */
   l_area = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_message->argument3 ) );

   /* Si l'argument de retour est situé en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le fichier est stocké dans une partition FAT32 */
      if ( l_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
      {
         /* Exécution de la requête demandée par l'utilisateur en utilisant le driver FAT */
         l_result = mk_fat_getInfo ( l_file, &l_info );

         /* Si le fichier est un répertoire */
         if ( ( l_info.fat.attribute & K_MK_FS_ATTRIBUTE_DIRECTORY ) == K_MK_FS_ATTRIBUTE_DIRECTORY )
         {
            l_localType = K_MK_FS_TYPE_DIRECTORY;
         }

         /* Sinon */
         else
         {
            l_localType = K_MK_FS_TYPE_FILE;
         }

         /* Si une fonction de rappel a été référencée */
         if ( p_message->callback != K_MK_NULL )
         {
            /* Configuration des arguments de la structure de rappel */
            /* L'argument est transmis peut importe le résultat de la fonction */
            /* Les fichiers FAT sont forcément sur 32 bits */
            p_callbackParam->param2 = ( T_mkAddr ) ( l_file );
            p_callbackParam->param3 = ( T_mkAddr ) 0;

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Ecriture du type du fichier dans la structure de rappel */
               p_callbackParam->param3 = ( T_mkAddr ) l_localType;
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
            /* Ecriture du type du fichier dans le paramètre de retour */
            *l_type = l_localType;
         }
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
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

static T_mkCode mk_file_synchroniseShared ( T_mkFile* p_file )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si le fichier est stocké dans une partition FAT32 */
   if ( p_file->volume->type == K_MK_VOLUME_TYPE_FAT32 )
   {
      /* Si le fichier est partagé, il faut récupérer son descripteur de fichier entre */
      /* chaque requête. */
      /* Récupération du descripteur de fichier */
      l_result = mk_fat_utils_synchFileEntryDescriptor ( p_file );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleRequest ( T_mkFileMessage* p_message, T_mkTask* p_task, T_mkCallbackParam* p_callbackParam, uint8_t* p_buf )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si une requêtre de type K_MK_FS_CHMOD a été reçue */
   if ( p_message->requestIdentifier == K_MK_FS_CHMOD )
   {
      /* Exécution de la requête de type K_MK_FS_CHMOD */
      l_result = mk_file_handleChmodRequest ( p_message, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_CLOSE a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_CLOSE )
   {
      /* Exécution de la requête de type K_MK_FS_CLOSE */
      l_result = mk_file_handleCloseRequest ( p_message );
   }

   /* Sinon si une requête de type K_MK_FS_EOF a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_EOF )
   {
      /* Exécution de la requête de type K_MK_FS_EOF */
      l_result = mk_file_handleEofRequest ( p_message, p_task, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_EXPAND a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_EXPAND )
   {
      /* Exécution de la requête de type K_MK_FS_EXPAND */
      l_result = mk_file_handleExpandRequest ( p_message, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_GETNAME a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_GETNAME )
   {
      /* Exécution de la requête de type K_MK_FS_GETNAME */
      l_result = mk_file_handleGetNameRequest ( p_message, p_task, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_LINK a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_LINK )
   {
      /* Exécution de la requête de type K_MK_FS_LINK */
      l_result = mk_file_handleLinkRequest ( p_message, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_OPEN a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_OPEN )
   {
      /* Exécution de la requête de type K_MK_FS_OPEN */
      l_result = mk_file_handleOpenRequest ( p_message, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_OPEN_DIRECTORY a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_OPEN_DIRECTORY )
   {
      /* Exécution de la requête de type K_MK_FS_OPEN_DIRECTORY */
      l_result = mk_file_handleOpenDirectoryRequest ( p_message, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_OPEN_RELATIVE a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_OPEN_RELATIVE )
   {
      /* Exécution de la requête de type K_MK_FS_OPEN_RELATIVE */
      l_result = mk_file_handleOpenRelativeRequest ( p_message, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_READ a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_READ )
   {
      /* Exécution de la requête de type K_MK_FS_READ */
      l_result = mk_file_handleReadRequest ( p_message, p_task, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_RENAME a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_RENAME )
   {
      /* Exécution de la requête de type K_MK_FS_RENAME */
      l_result = mk_file_handleRenameRequest ( p_message, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_SEEK a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_SEEK )
   {
      /* Exécution de la requête de type K_MK_FS_SEEK */
      l_result = mk_file_handleSeekRequest ( p_message, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_STAT a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_STAT )
   {
      /* Exécution de la requête de type K_MK_FS_STAT */
      l_result = mk_file_handleStatRequest ( p_message, p_buf );
   }

   /* Sinon si une requête de type K_MK_FS_TELL a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_TELL )
   {
      /* Exécution de la requête de type K_MK_FS_TELL */
      l_result = mk_file_handleTellRequest ( p_message, p_task, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_TRUNCATE a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_TRUNCATE )
   {
      /* Exécution de la requête de type K_MK_FS_TRUNCATE */
      l_result = mk_file_handleTruncateRequest ( p_message, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_UNLINK a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_UNLINK )
   {
      /* Exécution de la requête de type K_MK_FS_UNLINK */
      l_result = mk_file_handleUnlinkRequest ( p_message, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_WRITE a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_WRITE )
   {
      /* Exécution de la requête de type K_MK_FS_WRITE */
      l_result = mk_file_handleWriteRequest ( p_message, p_task, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_FILEINFO a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_FILEINFO )
   {
      /* Exécution de la requête de type K_MK_FS_FILEINFO */
      l_result = mk_file_handleFileInfoRequest ( p_message, p_task, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_SIZE a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_SIZE )
   {
      /* Exécution de la requête de type K_MK_FS_SIZE */
      l_result = mk_file_handleSizeRequest ( p_message, p_task, p_callbackParam );
   }

   /* Sinon si une requête de type K_MK_FS_TYPE a été reçue */
   else if ( p_message->requestIdentifier == K_MK_FS_TYPE )
   {
      /* Exécution de la requête de type K_MK_FS_TYPE */
      l_result = mk_file_handleTypeRequest ( p_message, p_task, p_callbackParam );
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

T_mkCode mk_file_handle ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam, T_mkTask* p_task, uint8_t* p_buf, uint32_t p_sharedTermio )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de disque */
   T_mkDisk* l_disk = K_MK_NULL;

   /* Déclaration d'un pointeur de fichier */
   T_mkFile** l_file = ( T_mkFile** ) p_message->argument2;

   /* Si une requête de type K_MK_FS_OPEN, K_MK_FS_OPEN_RELATIVE ou K_MK_FS_OPEN_DIRECTORY a été reçue */
   if ( ( p_message->requestIdentifier == K_MK_FS_OPEN ) || ( p_message->requestIdentifier == K_MK_FS_OPEN_RELATIVE ) ||
        ( p_message->requestIdentifier == K_MK_FS_OPEN_DIRECTORY ) )
   {
      /* Allocation d'un nouveau fichier */
      l_result = mk_file_handleAlloc ( p_message, p_buf );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si une requête différente des types K_MK_FS_OPEN, OPEN_DIRECTORY, K_MK_FS_OPEN_RELATIVE ou FS_STAT a été reçue */
      if ( ( p_message->requestIdentifier != K_MK_FS_OPEN ) && ( p_message->requestIdentifier != K_MK_FS_OPEN_DIRECTORY ) &&
           ( p_message->requestIdentifier != K_MK_FS_OPEN_RELATIVE ) && ( p_message->requestIdentifier != K_MK_FS_STAT ) )
      {
         /* Contrôle de la validité de l'instance du fichier et configuration de l'adresse du cache */
         l_result = mk_file_handleFileInstance ( p_message->argument2, p_buf );
      }

      /* Sinon si une requête de type K_MK_FS_OPEN_DIRECTORY ou K_MK_FS_OPEN_RELATIVE a été reçue */
      else if ( ( p_message->requestIdentifier == K_MK_FS_OPEN_DIRECTORY ) || ( p_message->requestIdentifier == K_MK_FS_OPEN_RELATIVE ) )
      {
         /* Contrôle de la validité de l'instance du fichier et configuration de l'adresse du cache */
         l_result = mk_file_handleFileInstance ( p_message->argument3, p_buf );
      }

      /* Si une requête de type K_MK_FS_OPEN ou FS_STAT a été reçue */
      else if ( ( p_message->requestIdentifier == K_MK_FS_OPEN ) || ( p_message->requestIdentifier == K_MK_FS_STAT ) )
      {
         /* Analyse du chemin du fichier */
         l_result = mk_file_handleFilePath ( p_message );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Récupération de l'adresse du disque propriétaire du fichier */
         l_disk = mk_file_getDiskHandle ( p_message );

         /* Si le disque est valide */
         if ( ( l_disk != K_MK_NULL ) && ( l_disk->status.main != K_MK_DISK_NOT_ENUMERATED ) )
         {
            /* Acquisition du sémaphore */
            l_result = mk_semaphore_take ( l_disk->semaphore, K_MK_TASK_WAIT_FOREVER );

            /* Actualisation du registre de statut du disque afin d'indiquer qu'il va être utilisé */
            l_disk->status.main |= K_MK_DISK_USED;

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Si le terminal est le terminal de gestion des fichiers partagés et si */
               /* le descripteur de fichiers doit être rechargé */
               if ( ( p_sharedTermio == 1 ) &&
                  ( p_message->requestIdentifier != K_MK_FS_OPEN ) && ( p_message->requestIdentifier != K_MK_FS_CLOSE ) &&
                  ( p_message->requestIdentifier != K_MK_FS_OPEN_DIRECTORY ) && ( p_message->requestIdentifier != K_MK_FS_OPEN_RELATIVE )  &&
                  ( p_message->requestIdentifier != K_MK_FS_STAT ) )
               {
                  /* Chargement du descripteur de fichiers */
                  l_result = mk_file_synchroniseShared ( p_message->argument2 );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Exécution de la requête utilisateur */
               l_result = mk_file_handleRequest ( p_message, p_task, p_callbackParam, p_buf );

               /* Actualisation du registre de statut du disque afin d'indiquer qu'il n'est plus utilisé */
               l_disk->status.main &= ( uint32_t ) ( ~K_MK_DISK_USED );

               /* Libération du sémaphore sans condition */
               l_result |= mk_semaphore_release ( l_disk->semaphore );
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
            /* Si une requête de type K_MK_FS_CLOSE a été transmise */
            if ( p_message->requestIdentifier == K_MK_FS_CLOSE )
            {
               /* Désallocation du fichier (sans condition) */
               l_result = mk_pool_freeSafe ( g_mkFileArea.pool, ( T_mkAddr ) ( p_message->argument2 ) );
            }

            /* Sinon */
            else
            {
               /* Actualisation de la variable de retour */
               l_result = K_MK_ERROR_PARAM;
            }
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si une erreur s'est produite et si une requête de type K_MK_FS_OPEN, K_MK_FS_OPEN_DIRECTORY */
      /* ou K_MK_FS_OPEN_RELATIVE a été demandée */
      if ( ( l_result != K_MK_OK ) &&
         ( ( p_message->requestIdentifier == K_MK_FS_OPEN ) || ( p_message->requestIdentifier == K_MK_FS_OPEN_DIRECTORY ) ||
           ( p_message->requestIdentifier == K_MK_FS_OPEN_RELATIVE ) ) )
      {
         /* Désallocation du fichier */
         l_result |= mk_pool_freeSafe ( g_mkFileArea.pool, ( T_mkAddr ) ( *l_file ) );

         /* Ecriture de la valeur nulle */
         *l_file = K_MK_NULL;
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

