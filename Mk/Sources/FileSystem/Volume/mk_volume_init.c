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
* @file mk_volume_init.c
* @brief Définition de la fonction mk_volume_init.
* @date 24 mai 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_volume_dispatchList ( T_mkVolume* p_list )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de volume */
   T_mkVolume* l_volume;

   /* Pour chaque partition dans la liste des partitions */
   for ( l_volume = p_list; l_volume != K_MK_NULL; l_volume = l_volume->nextVolume )
   {
      /* Transmission d'un événement au 'Dispatcher' pour prévenir l'applicatif qu'une partition a été montée */
      l_result |= mk_volume_dispatch ( l_volume, K_MK_EVENT_MOUNT );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_volume_decode ( T_mkDisk* p_disk, T_mkVolume** p_list, uint8_t* p_buf, uint32_t p_baseSectorNumber, uint32_t p_firstPartitionSector, uint32_t p_ebrSectorNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de buffer */
   uint16_t* l_mbr16 = ( T_mkAddr ) p_buf;

   /* Déclaration des variables stockant le résultat de la comparaison entre deux chaines de caractères */
   uint32_t l_fatResult, l_ntfsResult;

   /* Déclaration d'une variable stockant le nombre d'octets lus */
   uint64_t p_numberOfBytesRead = 0;

   /* Déclaration d'une variable stockant l'adresse du premier secteur de la partition */
   uint32_t l_firstPartitionSector = p_baseSectorNumber + p_firstPartitionSector;

   /* Si la partition est définie dans le MBR */
   if ( p_ebrSectorNumber == K_MK_VOLUME_MBR_SECTOR )
   {
      /* Aucune offset ne doit être ajoutée à l'adresse de la partition */
      l_firstPartitionSector = p_firstPartitionSector;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Lecture du premier secteur de la partition. */
   l_result = mk_disk_readSector ( p_disk, ( uint64_t ) l_firstPartitionSector, p_buf, 1, &p_numberOfBytesRead );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( p_numberOfBytesRead == p_disk->attribute.blockLength ) )
   {
      /* Si le secteur de boot n'est pas corrompu */
      if ( l_mbr16 [ ( K_MK_VOLUME_MBR_SIZE >> 1 ) - 1 ] == K_MK_VOLUME_MBR_SIGNATURE )
      {
         /* Analyse du nom de la partition */
         l_fatResult = mk_utils_strcomp ( ( T_str8 ) &p_buf [ K_MK_VOLUME_FAT32_PARTITION_LABEL_OFFSET ], ( T_str8 ) "FAT32", 0, 5 );

         /* Si une partition de type 'FAT32' est présente */
         if ( l_fatResult == 1 )
         {
            /* Récupération des informations de la partition */
            l_result = mk_volume_decodeFAT32 ( p_disk, p_list, p_buf, l_firstPartitionSector );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Analyse du nom de la partition */
         l_ntfsResult = mk_utils_strcomp ( ( T_str8 ) &p_buf [ K_MK_VOLUME_NTFS_PARTITION_LABEL_OFFSET ], ( T_str8 ) "NTFS", 0, 4 );

         /* Si une partition de type 'NTFS' est présente */
         if ( ( l_fatResult == 0 ) && ( l_ntfsResult == 1 ) )
         {
            /* Récupération des informations de la partition */
            l_result = mk_volume_decodeNTFS ( p_disk, p_list, p_buf, l_firstPartitionSector );
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
      l_result = K_MK_ERROR_COMM;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_volume_explore ( T_mkDisk* p_disk, T_mkVolume** p_list, uint8_t* p_buf, uint32_t p_baseSectorNumber, uint32_t p_ebrSectorNumber, uint32_t p_level )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'une variable stockant le nombre d'octets lus */
   uint64_t l_numberOfBytesRead = 0;

   /* Déclaration d'un pointeur de buffer */
   uint16_t* l_mbr16 = ( T_mkAddr ) p_buf;

   /* Déclaration d'un tableau stockant la valeur des entrées de la partition */
   T_mkVolumeEntry l_entry [ 4 ];

   /* Lecture d'un secteur MBR ou EBR */
   /* Les secteurs MBR ou EBR sont adressés sur 32 bits */
   l_result = mk_disk_readSector ( p_disk, ( uint64_t ) p_baseSectorNumber, p_buf, 1, &l_numberOfBytesRead );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead == p_disk->attribute.blockLength ) )
   {
      /* Si le secteur de boot n'est pas corrompu */
      if ( l_mbr16 [ ( K_MK_VOLUME_MBR_SIZE >> 1 ) - 1 ] == K_MK_VOLUME_MBR_SIGNATURE )
      {
         /* Copie des 4 entrées dans le tableau */
         /* Un pointeur n'est pas utilisée car cette fonction s'exécute récursivement. */
         /* Il vaut donc créer une copie des entrées après la lecture du secteur */
         _copy ( l_entry, &p_buf [ K_MK_VOLUME_MBR_FIRST_ENTRY_OFFSET ], K_MK_VOLUME_MBR_NUMBER_OF_ENTRIES * K_MK_VOLUME_MBR_ENTRY_SIZE );

         /* Pour le nombre d'entrées contenues dans le MBR */
         for ( l_counter = 0 ; ( l_counter < K_MK_VOLUME_MBR_NUMBER_OF_ENTRIES ) ; l_counter++ )
         {
            /* Si container étendue adressée en CHS */
            if ( l_entry [ l_counter ].type == K_MK_VOLUME_ENTRY_IBM_CHS_CONTAINER )
            {
               /* Si le taux maximal de récursivité n'a pas été atteint */
               if ( p_level < K_MK_VOLUME_RECURSIVITY_LEVEL )
               {
                  /* Ré-exécution de la fonction afin d'analyser le prochain EBR */
                  l_result |= mk_volume_explore ( p_disk, p_list, p_buf, p_ebrSectorNumber + l_entry [ l_counter ].firstLBA, p_ebrSectorNumber, p_level + 1 );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }
            }

            /* Sinon si container étendue adressée en LBA */
            else if ( l_entry [ l_counter ].type == K_MK_VOLUME_ENTRY_MICROSOFT_LBA_CONTAINER )
            {
               /* Si le taux maximal de récursivité n'a pas été atteint */
               if ( p_level < K_MK_VOLUME_RECURSIVITY_LEVEL )
               {
                  /* Enregistrement de l'adresse de base de l'EBR */
                  p_ebrSectorNumber = l_entry [ l_counter ].firstLBA;

                  /* Ré-exécution de la fonction afin d'analyser le prochain EBR */
                  l_result |= mk_volume_explore ( p_disk, p_list, p_buf, l_entry [ l_counter ].firstLBA, p_ebrSectorNumber, p_level + 1 );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }
            }

            /* Sinon si partition de type 'FAT32' adressée en CHS */
            else if ( l_entry [ l_counter ].type != K_MK_VOLUME_ENTRY_EMPTY )
            {
               /* Décodage du volume courant */
               l_result |= mk_volume_decode ( p_disk, p_list, p_buf, p_baseSectorNumber, l_entry [ l_counter ].firstLBA, p_ebrSectorNumber );
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
      l_result = K_MK_ERROR_COMM;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_volume_openPipe ( T_mkDiskType* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le périphérique est de type 'MSC' */
   if  ( *p_device == K_MK_DISK_TYPE_MSC_DEVICE )
   {
      /* Ouverture des 'Pipe' de communication */
      l_result = mk_msc_openPipe ( ( T_mkMSCDevice* ) p_device );
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

static T_mkCode mk_volume_closePipe ( T_mkDiskType* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le périphérique est de type 'MSC' */
   if  ( *p_device == K_MK_DISK_TYPE_MSC_DEVICE )
   {
      /* Fermeture des 'Pipe' de communication */
      l_result = mk_msc_closePipe ( ( T_mkMSCDevice* ) p_device );
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

T_mkCode mk_volume_init ( T_mkDisk* p_disk, uint8_t* p_buf )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de disque */
   T_mkDisk* l_disk = p_disk;

   /* Déclaration d'un volume */
   T_mkVolume* l_volumeList =  K_MK_NULL;

   /* Si les paramètre sont valides */
   if ( ( p_disk != K_MK_NULL ) && ( p_buf != K_MK_NULL ) )
   {
      /* Pour le nombre de disques à initialiser */
      /* Un média peut contenir plusieurs disques. On rencontre parfois cette situation avec un hub possédant un lecture MMC, CF, SD, ... */
      for (  ; ( l_disk != K_MK_NULL ) && ( l_result == K_MK_OK ) ; l_disk = l_disk->nextDisk )
      {
         /* Si le disque n'est pas intialisé */
         if ( ( l_disk->status.main & ( K_MK_DISK_READY | K_MK_DISK_VOLUME_MOUNTED ) ) == K_MK_DISK_READY )
         {
            /* Ouverture d'un pipe de communication */
            l_result = mk_volume_openPipe ( l_disk->device );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Recherche des volumes présents dans le disque */
               l_result = mk_volume_explore ( l_disk, &l_volumeList, p_buf, K_MK_VOLUME_MBR_SECTOR, K_MK_VOLUME_MBR_SECTOR, 0 );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Enregistrement de la liste dans le disque */
                  l_disk->volume = l_volumeList;

                  /* Actualisation de l'état du disque */
                  l_disk->status.main |= K_MK_DISK_VOLUME_MOUNTED;

                  /* Transmission de l'adresse des 'n' volumes à l'applicatif */
                  l_result = mk_volume_dispatchList ( l_disk->volume );
               }

               /* Sinon */
               else
               {
                  /* Si un volume a été alloué */
                  if ( l_volumeList != K_MK_NULL )
                  {
                     /* Suppression de la liste allouée */
                     l_result |= mk_volume_delete ( l_volumeList, 0 );
                  }

                  /* Sinon */
                  else
                  {
                     /* Ne rien faire */
                  }
               }

               /* Fermeture des pipe de communication */
               l_result |= mk_volume_closePipe ( l_disk->device );
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



