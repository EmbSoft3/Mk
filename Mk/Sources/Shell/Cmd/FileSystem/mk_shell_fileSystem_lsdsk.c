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
* @file mk_shell_fileSystem_lsdsk.c
* @brief Définition de la fonction mk_shell_fileSystem_lsdsk.
* @date 15 avr. 2024
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_shell_fileSystem_lsdskGetSize ( uint64_t p_size, T_str8 p_str, uint32_t p_length )
{
   /* Déclaration d'une variable stockant la taille du disque en chaine de caractères */
   char8_t l_strSize [ 12 ] = { 0 };

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'une variable stockant la longueur de la chaine de caractères */
   uint32_t l_length = 0;

   /* Si la taille du disque est supérieur 1TiB */
   if ( p_size > 0x10000000000 )
   {
      /* Division par 1GiB */
      p_size = p_size >> 30 ;

      /* Conversion en chaine de caractères */
      mk_utils_itoa ( ( uint32_t ) p_size, ( T_str8 ) l_strSize, 10, 0 );
      l_length = mk_utils_strlen ( ( T_str8 ) l_strSize );
      mk_utils_strcat ( &p_str [ p_length - l_length - 5 ], ( T_str8 ) l_strSize, ( T_str8 ) " TiB" );
   }

   /* Sinon si la taille du disque est supérieur 1MB */
   else if ( p_size > 0x100000 )
   {
      /* Division par 1MiB */
      p_size = p_size >> 20 ;

      /* Conversion en chaine de caractères */
      mk_utils_itoa ( ( uint32_t ) p_size, ( T_str8 ) l_strSize, 10, 0 );
      l_length = mk_utils_strlen ( ( T_str8 ) l_strSize );
      mk_utils_strcat ( &p_str [ p_length - l_length - 5 ], ( T_str8 ) l_strSize, ( T_str8 ) " MiB" );
   }

   /* Sinon si la taille du disque est supérieur 1KB */
   else if ( p_size > 0x400 )
   {
      /* Division par 1KB */
      p_size = p_size >> 10 ;

      /* Conversion en chaine de caractères */
      mk_utils_itoa ( ( uint32_t ) p_size, ( T_str8 ) l_strSize, 10, 0 );
      l_length = mk_utils_strlen ( ( T_str8 ) l_strSize );
      mk_utils_strcat ( &p_str [ p_length - l_length - 5 ], ( T_str8 ) l_strSize, ( T_str8 ) " KiB" );
   }

   /* Sinon */
   else
   {
      /* Conversion en chaine de caractères */
      mk_utils_itoa ( ( uint32_t ) ( p_size ), ( T_str8 ) l_strSize, 10, 0 );
      l_length = mk_utils_strlen ( ( T_str8 ) l_strSize );
      mk_utils_strcat ( &p_str [ p_length - l_length - 5 ], ( T_str8 ) l_strSize, ( T_str8 ) " Byt" );
   }

   for ( l_counter = 0 ; l_counter < ( p_length - l_length - 5 ) ; l_counter++ ) p_str [ l_counter ] = ' ';

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shell_fileSystem_lsdskPrint ( T_mkConsole* p_console, T_mkDisk* p_disk, T_str8 p_prompt, uint8_t p_char )
{
   /* Déclaration des variables de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des buffers stockant les chaines de caractères */
   char8_t l_currentStr  [ 96 ], l_strSize [ 12 ];
   char8_t l_baseStr     [ 96 ] = "\n\r\t> vol   \t     \t           \t                   \t                                             ";

   /* Déclaration des variables de travail */
   uint32_t l_length = 0, l_index = 0, l_counter = 0, l_utfValue = 0;

   /* Déclaration d'un pointeur de partitions */
   T_mkVolume* l_volume = K_MK_NULL;

   /* Ecriture de l'identifiant du disque dans la chaine de caractères */
   mk_utils_strcat ( ( T_str8 ) l_currentStr, ( T_str8 ) p_prompt, ( T_str8 ) p_disk->name.id );

   /* Si le disque est initialisé */
   if ( ( ( p_disk->status.main & K_MK_DISK_READY ) == K_MK_DISK_READY ) && ( ( p_disk->status.main & K_MK_DISK_USED ) != K_MK_DISK_USED ) && ( p_char == 'o' ) )
   {
      /* Si le disque est protégé en écriture */
      if ( ( p_disk->status.main & K_MK_DISK_WRITE_PROTECT ) == K_MK_DISK_WRITE_PROTECT )
      {
         /* Ecriture du statut "online:wp" dans la chaine de caractères */
         mk_utils_strcat ( ( T_str8 ) l_currentStr, ( T_str8 ) l_currentStr, ( T_str8 ) "\t(online:wp)" );
      }

      /* Sinon */
      else
      {
         /* Ecriture du statut "online" dans la chaine de caractères */
         mk_utils_strcat ( ( T_str8 ) l_currentStr, ( T_str8 ) l_currentStr, ( T_str8 ) "\t(online)" );
      }

      /* Affichage des informations relatives au disque dans la console */
      l_result = mk_console_puts ( p_console, ( T_str8 ) l_currentStr );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Copie du modèle de chaine de caractères dans la variable de travail  */
         _copy ( l_currentStr, l_baseStr, 96 );

         /* Récupération de la longueur de l'identifiant de la partition */
         l_length = mk_utils_strlen ( ( T_str8 ) p_disk->name.id );

         /* Récupération de la taille du disque */
         mk_shell_fileSystem_lsdskGetSize ( ( uint64_t ) p_disk->attribute.numberOfBlocks* ( uint64_t ) p_disk->attribute.blockLength, ( T_str8 ) l_strSize, 12 );

         /* Ecriture de l'identifiant de la partition dans la chaine de caractères */
         _copy ( ( T_str8 ) &l_currentStr [ 5 ], ( T_str8 ) p_disk->name.id, l_length );

         /* Ecriture de la taille du disque dans la chaine de caractères */
         _copy ( ( T_str8 ) &l_currentStr [ 18 ], ( T_str8 ) l_strSize, 11 );

         /* Ecriture du caractère de fin de chaine */
         l_currentStr [ 29 ] = '\0';

         /* Affichage des informations relatives au disque dans la console */
         l_result = mk_console_puts ( p_console, ( T_str8 ) l_currentStr );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Pour le nombre de partitions présentes sur le disque */
      for ( l_result |= mk_disk_getFirstVolume ( p_disk, &l_volume ) ; ( l_volume != K_MK_NULL ) && ( l_result == K_MK_OK ) ; l_volume = l_volume->nextVolume )
      {
         /* Copie du modèle de chaine de caractères dans la variable de travail  */
         _copy ( l_currentStr, l_baseStr, 96 );

         /* Récupération de la longueur de l'identifiant de la partition */
         l_length = mk_utils_strlen ( ( T_str8 ) l_volume->name.str );

         /* Ecriture de l'identifiant de la partition dans la chaine de caractères */
         _copy ( ( T_str8 ) &l_currentStr [ 5 ], ( T_str8 ) l_volume->name.str, l_length );

         /* Si la partition est non reconnue */
         if ( l_volume->type == K_MK_VOLUME_TYPE_UNKNOWN )
         {
            /* Ecriture de la fin de la chaine */
            _copy ( ( T_str8 ) &l_currentStr [ 5 + l_length ], ( T_str8 ) &l_baseStr [ 5 + l_length ], ( uint32_t ) ( 96 - l_length ) );
         }

         /* Sinon si la partition est de type FAT16 ou FAT32 */
         else if ( ( l_volume->type == K_MK_VOLUME_TYPE_FAT16 ) || ( l_volume->type == K_MK_VOLUME_TYPE_FAT32 ) )
         {
            /* Si la partition est de type 'FAT16' */
            if ( l_volume->type == K_MK_VOLUME_TYPE_FAT16 )
            {
               /* Ecriture du type de la partition dans la chaine de caractères */
               _copy ( ( T_str8 ) &l_currentStr [ 12 ], ( T_str8 ) "FAT16", 5 );
            }

            /* Sinon */
            else
            {
               /* Ecriture du type de la partition dans la chaine de caractères */
               _copy ( ( T_str8 ) &l_currentStr [ 12 ], ( T_str8 ) "FAT32", 5 );
            }

            /* Récupération de la taille du disque */
            mk_shell_fileSystem_lsdskGetSize ( ( uint64_t ) l_volume->partition.fat.totalNumberOfSectors * ( uint64_t ) l_volume->partition.fat.bytesPerSector,
                                          ( T_str8 ) l_strSize, 12 );

            /* Ecriture de la taille de la partition dans la chaine de caractères */
            _copy ( ( T_str8 ) &l_currentStr [ 18 ], ( T_str8 ) l_strSize, 11 );

            /* Récupération de la taille utilisée sur la partition */
            mk_shell_fileSystem_lsdskGetSize ( ( uint64_t ) ( l_volume->partition.fat.totalNumberOfSectors - ( l_volume->partition.fat.numberOfFreeCluster * l_volume->partition.fat.sectorsPerCluster ) ) *
                                          ( uint64_t ) l_volume->partition.fat.bytesPerSector, ( T_str8 ) l_strSize, 12 );

            /* Ecriture de la taille utilisée dans la chaine de caractères */
            _copy ( ( T_str8 ) &l_currentStr [ 30 ], ( T_str8 ) l_strSize, 11 );
            _copy ( ( T_str8 ) &l_currentStr [ 42 ], ( T_str8 ) "(used)", 6 );

            /* Ecriture du nom de la partition dans la chaine de caractères */
            _copy ( ( T_str8 ) &l_currentStr [ 50 ], ( T_str8 ) l_volume->partition.fat.label, 11 );

            /* Ecriture du caractère de fin de chaine */
            l_currentStr [ 61 ] = '\0';

         }

         /* Sinon si la partition est de type NTFS */
         else if ( l_volume->type == K_MK_VOLUME_TYPE_NTFS )
         {
            /* Ecriture du type de la partition dans la chaine de caractères */
            _copy ( ( T_str8 ) &l_currentStr [ 12 ], ( T_str8 ) "NTFS", 4 );

            /* Récupération de la taille du disque */
            mk_shell_fileSystem_lsdskGetSize ( ( ( uint64_t ) l_volume->partition.ntfs.highTotalNumberOfSectors | ( uint64_t ) l_volume->partition.ntfs.lowTotalNumberOfSectors ) *
                                            ( uint64_t ) l_volume->partition.ntfs.bytesPerSector, ( T_str8 ) l_strSize, 12 );

            /* Ecriture de la taille de la partition dans la chaine de caractères */
            _copy ( ( T_str8 ) &l_currentStr [ 18 ], ( T_str8 ) l_strSize, 11 );

            /* Configuration de l'offset initiale du nom de la partition dans la chaine */
            l_index = 50;

            /* Si la console est encodée en UTF8 */
            if ( p_console->foreground.window.style.fontEncoding == K_MK_FONT_UTF8 )
            {
               /* Ecriture du nom de la partition dans la chaine de caractères */
               for ( l_counter = 0 ; l_counter < K_MK_VOLUME_NTFS_MAX_VOLUME_NAME_LENGTH ; l_counter++ )
               {
                  /* Le caractère est sur 16bits, la conversion en codepoint est directe */
                  l_utfValue = mk_utils_utf16ToUtf32 ( l_volume->partition.ntfs.label [ l_counter ] );
                  l_utfValue = mk_utils_codeToUtf8 ( l_utfValue );

                  /* Ecriture du caractère UTF-8 dans la chaine */
                  mk_utils_codeToString ( l_utfValue, ( T_str8 ) &l_currentStr [ l_index ], p_console->foreground.window.style.fontEncoding );

                  /* Récupération de la longueur du caractère écrit dans la chaine */
                  mk_utils_utfget ( ( T_str8 ) &l_currentStr [ l_index ], 0, p_console->foreground.window.style.fontEncoding, &l_length );

                  /* Actualisation de l'offset du prochain caractère */
                  l_index = ( uint32_t ) ( l_index + l_length );
               }
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Ecriture du caractère de fin de chaine */
            l_currentStr [ l_index ] = '\0';
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Affichage des informations relatives à la partition dans la console */
         l_result = mk_console_puts ( p_console, ( T_str8 ) l_currentStr );

         /* Si la partition est la dernière du disque */
         if ( ( l_result == K_MK_OK ) && ( l_volume->nextVolume == K_MK_NULL ) )
         {
            /* Ajout d'un saut de ligne */
            l_result = mk_console_puts ( p_console, ( T_str8 ) "\r\n" );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Si la partition est la dernière du disque */
      if ( ( l_result == K_MK_OK ) && ( l_volume != K_MK_NULL ) && ( l_volume->nextVolume == K_MK_NULL ) )
      {
         /* Affichage des informations relatives à la partition dans la console */
         l_result = mk_console_puts ( p_console, ( T_str8 ) "\r\n" );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon si les disques 'offline' doivent être affiché */
   else if ( ( ( p_disk->status.main & K_MK_DISK_READY ) != K_MK_DISK_READY ) && ( p_char == 'f' ) )
   {
      /* Ecriture du statut ("offline") dans la chaine de caractères */
      mk_utils_strcat ( ( T_str8 ) l_currentStr, ( T_str8 ) l_currentStr, ( T_str8 ) "\t(offline)" );

      /* Affichage des informations relatives au disque dans la console */
      l_result = mk_console_puts ( p_console, ( T_str8 ) l_currentStr );

      /* Si le disque est le dernier de la liste */
      if ( ( l_result == K_MK_OK ) && ( p_disk->nextDisk == K_MK_NULL ) )
      {
         /* Ajout d'un saut de ligne */
         l_result = mk_console_puts ( p_console, ( T_str8 ) "\r\n" );
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

T_mkCode mk_shell_fileSystem_lsdsk ( T_mkConsole* p_console )
{
   /* Prototype de la commande */
   /* lsdsk */

   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de disque */
   T_mkDisk* l_disk = K_MK_NULL;

   /* Déclaration d'un pointeur de périphériques MSC */
   T_mkMSCDevice* l_mscDevice = K_MK_NULL;

   /* Déclaration d'un pointeur de périphérique sMMC */
   T_mkMMCDevice* l_mmcDevice = K_MK_NULL;

   /* Récupération de l'adresse du premier périphérique MMC */
   l_result = mk_mmc_getFirstDevice ( &l_mmcDevice );

   /* Pour le nombre de périphérique MMC montés par le système */
   for ( ; ( l_mmcDevice != K_MK_NULL ) && ( l_result == K_MK_OK ) ; l_mmcDevice = l_mmcDevice->next )
   {
      /* Pour le nombre de disques présents sur le périphérique MMC */
      for ( l_result = mk_mmc_getFirstDisk ( l_mmcDevice, &l_disk ) ; ( l_disk != K_MK_NULL ) && ( l_result == K_MK_OK ) ; l_disk = l_disk->nextDisk )
      {
         /* Affichage du statut des disques en ligne */
         l_result = mk_shell_fileSystem_lsdskPrint ( p_console, l_disk, ( T_str8 ) "\n\rmmc:", 'o' );
      }
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Récupération de l'adresse du premier périphérique MSC */
      l_result = mk_msc_getFirstDevice ( &l_mscDevice );

      /* Pour le nombre de périphérique MSC montés par le système */
      for ( ; ( l_mscDevice != K_MK_NULL ) && ( l_result == K_MK_OK ) ; l_mscDevice = l_mscDevice->next )
      {
         /* Pour le nombre de disques présents sur le périphérique MSC */
         for ( l_result = mk_msc_getFirstDisk ( l_mscDevice, &l_disk ) ; ( l_disk != K_MK_NULL ) && ( l_result == K_MK_OK ) ; l_disk = l_disk->nextDisk )
         {
            /* Affichage du statut des disques en ligne */
            l_result = mk_shell_fileSystem_lsdskPrint ( p_console, l_disk, ( T_str8 ) "\n\rusb:", 'o' );
         }
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
      /* Récupération de l'adresse du premier périphérique MSC */
      l_result |= mk_msc_getFirstDevice ( &l_mscDevice );

      /* Pour le nombre de périphérique MSC montés par le système */
      for ( ; ( l_mscDevice != K_MK_NULL ) && ( l_result == K_MK_OK ) ; l_mscDevice = l_mscDevice->next )
      {
         /* Pour le nombre de disques présents sur le périphérique MSC */
         for ( l_result = mk_msc_getFirstDisk ( l_mscDevice, &l_disk ) ; ( l_disk != K_MK_NULL ) && ( l_result == K_MK_OK ) ; l_disk = l_disk->nextDisk )
         {
            /* Affichage du statut des disques hors ligne */
            l_result = mk_shell_fileSystem_lsdskPrint ( p_console, l_disk, ( T_str8 ) "\n\rusb:", 'f' );
         }
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Ajout d'un saut de ligne et déclenchement du rafraichissement graphique */
   l_result |= mk_console_print ( p_console, ( T_str8 ) "\r\n" );

   /* Retour */
   return ( l_result );
}



