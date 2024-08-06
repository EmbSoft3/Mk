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
* @file mk_bmp_open.c
* @brief Définition de la fonction mk_bmp_open.
* @date 26 mai 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_bmp_checkW3Header ( T_mkBMPFile* p_bitmap, T_mkBMPHeader* p_header )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les caractéristiques de l'image sont invalides */
   if ( ( p_header->w3.imageHeader.width <= 0 ) || ( p_header->w3.imageHeader.height == 0 ) || ( p_header->w3.imageHeader.planes != 1 ) || ( p_header->w3.imageHeader.imageSize == 0 ) ||
      ( ( p_header->w3.imageHeader.bitsPerPixel != 1 ) && ( p_header->w3.imageHeader.bitsPerPixel != 2 ) && ( p_header->w3.imageHeader.bitsPerPixel != 4 ) &&
        ( p_header->w3.imageHeader.bitsPerPixel != 8 ) && ( p_header->w3.imageHeader.bitsPerPixel != 16 ) && ( p_header->w3.imageHeader.bitsPerPixel != 24 ) && ( p_header->w3.imageHeader.bitsPerPixel != 32 ) )
      )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Sinon */
   else
   {
      /* Enregistrement de la largeur du bitmap */
      p_bitmap->width = ( uint32_t ) p_header->w3.imageHeader.width;

      /* Si l'image doit être chargée du haut vers le bas */
      if ( p_header->w3.imageHeader.height < 0 )
      {
         /* Conversion de la hauteur en valeur positive */
         p_bitmap->height = ( uint32_t ) ( ( -1 ) * p_header->w3.imageHeader.height );
         p_bitmap->topDownRowOrder = 0;
      }

      /* Sinon (dessin de bas en haut) */
      else
      {
         /* Enregistrement de la hauteur du bitmap */
         p_bitmap->height = ( uint32_t ) p_header->w3.imageHeader.height;
         p_bitmap->topDownRowOrder = 1;
      }

      /* Enregistrement de la méthode de compression, du nombre de bits par pixel */
      /* et de la taille de l'image. */
      p_bitmap->compression = p_header->w3.imageHeader.compression;
      p_bitmap->bitsPerPixel = p_header->w3.imageHeader.bitsPerPixel;
      p_bitmap->imageSize = p_header->w3.imageHeader.imageSize;

      /* Si le format de l'image n'est pas supporté */
      if ( ( ( p_header->w3.imageHeader.bitsPerPixel != 32 ) && ( p_header->w3.imageHeader.bitsPerPixel != 24 ) ) ||
             ( p_header->w3.imageHeader.compression != K_MK_BMP_COMPRESSION_RGB ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_NOT_SUPPORTED;
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

static T_mkCode mk_bmp_checkW4Header ( T_mkBMPFile* p_bitmap, T_mkBMPHeader* p_header )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les caractéristiques de l'image sont invalides */
   if ( ( p_header->w4.imageHeader.width <= 0 ) || ( p_header->w4.imageHeader.height == 0 ) || ( p_header->w4.imageHeader.planes != 1 ) || ( p_header->w4.csType != K_MK_BMP_LCS_CALIBRATED_RGB ) || ( p_header->w3.imageHeader.imageSize == 0 ) ||
      ( ( p_header->w4.imageHeader.bitsPerPixel != 1 ) && ( p_header->w4.imageHeader.bitsPerPixel != 2 ) && ( p_header->w4.imageHeader.bitsPerPixel != 4 ) &&
        ( p_header->w4.imageHeader.bitsPerPixel != 8 ) && ( p_header->w4.imageHeader.bitsPerPixel != 16 ) && ( p_header->w4.imageHeader.bitsPerPixel != 24 ) && ( p_header->w4.imageHeader.bitsPerPixel != 32 ) )
      )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Sinon */
   else
   {
      /* Enregistrement de la largeur du bitmap */
      p_bitmap->width = ( uint32_t ) p_header->w4.imageHeader.width;

      /* Si l'image doit être chargée du haut vers le bas */
      if ( p_header->w4.imageHeader.height < 0 )
      {
         /* Conversion de la hauteur en valeur positive */
         p_bitmap->height = ( uint32_t ) ( ( -1 ) * p_header->w4.imageHeader.height );
         p_bitmap->topDownRowOrder = 0;
      }

      /* Sinon (dessin de bas en haut) */
      else
      {
         /* Enregistrement de la hauteur du bitmap */
         p_bitmap->height = ( uint32_t ) p_header->w4.imageHeader.height;
         p_bitmap->topDownRowOrder = 1;
      }

      /* Enregistrement de la méthode de compression, du nombre de bits par pixel */
      /* et de la taille de l'image. */
      p_bitmap->compression = p_header->w4.imageHeader.compression;
      p_bitmap->bitsPerPixel = p_header->w4.imageHeader.bitsPerPixel;
      p_bitmap->imageSize = p_header->w4.imageHeader.imageSize;

      /* Si le format de l'image n'est pas supporté */
      if ( ( ( p_header->w4.imageHeader.bitsPerPixel != 32 ) && ( p_header->w4.imageHeader.bitsPerPixel != 24 ) ) ||
             ( p_header->w4.imageHeader.compression != K_MK_BMP_COMPRESSION_RGB ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_NOT_SUPPORTED;
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

static T_mkCode mk_bmp_checkW5Header ( T_mkBMPFile* p_bitmap, T_mkBMPHeader* p_header )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les caractéristiques de l'image sont invalides */
   if ( ( p_header->w5.imageHeader.width <= 0 ) || ( p_header->w5.imageHeader.height == 0 ) || ( p_header->w5.imageHeader.planes != 1 ) || ( p_header->w3.imageHeader.imageSize == 0 ) ||
      ( ( p_header->w5.imageHeader.bitsPerPixel != 1 ) && ( p_header->w5.imageHeader.bitsPerPixel != 2 ) && ( p_header->w5.imageHeader.bitsPerPixel != 4 ) &&
        ( p_header->w5.imageHeader.bitsPerPixel != 8 ) && ( p_header->w5.imageHeader.bitsPerPixel != 16 ) && ( p_header->w5.imageHeader.bitsPerPixel != 24 ) && ( p_header->w5.imageHeader.bitsPerPixel != 32 ) )
      )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Sinon */
   else
   {
      /* Enregistrement de la largeur du bitmap */
      p_bitmap->width = ( uint32_t ) p_header->w5.imageHeader.width;

      /* Si l'image doit être chargée du haut vers le bas */
      if ( p_header->w5.imageHeader.height < 0 )
      {
         /* Conversion de la hauteur en valeur positive */
         p_bitmap->height = ( uint32_t ) ( ( -1 ) * p_header->w5.imageHeader.height );
         p_bitmap->topDownRowOrder = 0;
      }

      /* Sinon (dessin de bas en haut) */
      else
      {
         /* Enregistrement de la hauteur du bitmap */
         p_bitmap->height = ( uint32_t ) p_header->w5.imageHeader.height;
         p_bitmap->topDownRowOrder = 1;
      }

      /* Enregistrement de la méthode de compression, du nombre de bits par pixel */
      /* et de la taille de l'image. */
      p_bitmap->compression = p_header->w5.imageHeader.compression;
      p_bitmap->bitsPerPixel = p_header->w5.imageHeader.bitsPerPixel;
      p_bitmap->imageSize = p_header->w5.imageHeader.imageSize;

      /* Si le format de l'image n'est pas supporté */
      if ( ( ( p_header->w5.imageHeader.bitsPerPixel != 32 ) && ( p_header->w5.imageHeader.bitsPerPixel != 24 ) ) ||
             ( p_header->w5.imageHeader.compression != K_MK_BMP_COMPRESSION_RGB ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_NOT_SUPPORTED;
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

static T_mkCode mk_bmp_getImageHeader (T_mkBMPFile* p_bitmap, T_mkBMPHeader* p_header, uint32_t p_numberOfBytesToRead )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_numberOfBytesRead = 0;

   /* Configuration du pointeur de fichier au début de celui-ci */
   l_result = mk_file_seek ( p_bitmap->file, K_MK_BMP_HEADER_SIZE, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Lecture de l'entête du fichier */
      l_result = mk_file_read ( p_bitmap->file, ( T_mkBMPHeader* ) p_header, p_numberOfBytesToRead, &l_numberOfBytesRead, K_MK_NULL );

      /* Si l'entête n'a pas été lue intégralement */
      if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead != p_numberOfBytesToRead ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_UNEXPECTED;
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

static T_mkCode mk_bmp_checkImageHeader ( T_mkBMPFile* p_bitmap )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'une entête d'un fichier bitmap */
   T_mkBMPHeader l_header;

   /* Si les paramètres sont valides */
   if ( ( p_bitmap != K_MK_NULL ) && ( p_bitmap->file != K_MK_NULL ) )
   {
      /* Si le bitmap est du type K_MK_BMP_HEADER_WIN3V1, K_MK_BMP_HEADER_WIN3V2 ou K_MK_BM_HEADER_WIN3V3 */
      if ( p_bitmap->type == K_MK_BMP_HEADER_WIN3V1 || p_bitmap->type == K_MK_BMP_HEADER_WIN3V2 || p_bitmap->type == K_MK_BMP_HEADER_WIN3V3 )
      {
         /* Récupération des informations de l'entête */
         l_result = mk_bmp_getImageHeader ( p_bitmap, &l_header, ( uint32_t ) ( sizeof ( T_mkBMPW3Header ) ) );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Enregistrement et vérification des attributs du bitmap */
            l_result = mk_bmp_checkW3Header ( p_bitmap, &l_header );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si le bitmap est du type K_MK_BMP_HEADER_WIN4 */
      else if ( p_bitmap->type == K_MK_BMP_HEADER_WIN4 )
      {
         /* Récupération des informations de l'entête */
         l_result = mk_bmp_getImageHeader ( p_bitmap, &l_header, ( uint32_t ) ( sizeof ( T_mkBMPW4Header ) ) );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Enregistrement et vérification des attributs du bitmap */
            l_result = mk_bmp_checkW4Header ( p_bitmap, &l_header );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si le bitmap est du type K_MK_BMP_HEADER_WIN5 */
      else if ( p_bitmap->type == K_MK_BMP_HEADER_WIN5 )
      {
         /* Récupération des informations de l'entête */
         l_result = mk_bmp_getImageHeader ( p_bitmap, &l_header, ( uint32_t ) ( sizeof ( T_mkBMPW5Header ) ) );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Enregistrement et vérification des attributs du bitmap */
            l_result = mk_bmp_checkW5Header ( p_bitmap, &l_header );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_bmp_open ( T_mkBMPFile* p_bitmap, T_mkVolume* p_volume, T_str8 p_directoryPath, T_str8 p_filePath )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de fichier */
   T_mkFile* l_directory;

   /* Déclaration d'une entête de fichier bitmap */
   T_mkBMPFileHeader l_header;

   /* Déclaration des variables de travail */
   uint32_t l_numberOfBytesRead = 0;

   /* Si les paramètres sont valides */
   if ( ( p_bitmap != K_MK_NULL ) && ( p_filePath != K_MK_NULL ) )
   {
      /* Initialisation des données du bitmap */
      _writeWords ( p_bitmap, 0, sizeof ( T_mkBMPFile ) >> 2 );

      /* Si l'ouverture du fichier doit s'effectuer de manière relative */
      if ( p_directoryPath [ 0 ] != '\0' )
      {
         /* Ouverture du répertoire */
         l_result = mk_file_open ( p_volume, &l_directory, p_directoryPath, K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Ouverture du fichier */
            l_result = mk_file_openRelative ( &p_bitmap->file, l_directory, p_filePath, K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL );
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
         /* Ouverture du fichier BMP (absolu) */
         /* Le pointeur de fichier est automatiquement placé au début */
         l_result = mk_file_open ( p_volume, &p_bitmap->file, p_filePath, K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL );
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Lecture de l'entête du fichier */
         l_result = mk_file_read ( p_bitmap->file, &l_header, ( uint32_t ) sizeof ( T_mkBMPFileHeader ), &l_numberOfBytesRead, K_MK_NULL );

         /* Si l'entête n'a pas été lue intégralement */
         if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead != ( ( uint32_t ) sizeof ( T_mkBMPFileHeader ) ) ) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_UNEXPECTED;
         }

         /* Sinon */
         else
         {
            /* Si le fichier est de type BMP ('BM') */
            if ( l_header.fileType == K_MK_BMP_SIGNATURE )
            {
               /* Récupération du type du bitmap */
               p_bitmap->type = ( uint32_t ) ( l_header.lowHeaderSize ) | ( uint32_t ) ( ( uint32_t ) (l_header.highHeaderSize ) << 16 );

               /* Récupération de l'adresse du pixelArray */
               p_bitmap->pixelArray = ( uint32_t ) ( l_header.lowBitmapArrayOffset ) | ( uint32_t ) ( ( uint32_t ) (l_header.highBitmapArrayOffset ) << 16 );

               /* Si le type du bitmap est invalide */
               if ( ( p_bitmap->type != K_MK_BMP_HEADER_WIN1 ) && ( p_bitmap->type != K_MK_BMP_HEADER_WIN2_OS2V1 ) && ( p_bitmap->type != K_MK_BMP_HEADER_OS2V2_TINY ) &&
                    ( p_bitmap->type != K_MK_BMP_HEADER_OS2V2 ) && ( p_bitmap->type != K_MK_BMP_HEADER_WIN3V1 ) && ( p_bitmap->type != K_MK_BMP_HEADER_WIN3V2 ) &&
                    ( p_bitmap->type != K_MK_BMP_HEADER_WIN3V3 ) && ( p_bitmap->type != K_MK_BMP_HEADER_WIN4 ) && ( p_bitmap->type != K_MK_BMP_HEADER_WIN5 ) )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_MK_ERROR_PARAM;
               }

               /* Sinon */
               else
               {
                  /* Récupération et vérification de la conformité du bitmap */
                  l_result = mk_bmp_checkImageHeader ( p_bitmap );
               }
            }

            /* Sinon */
            else
            {
               /* Actualisation de la variable de retour */
               l_result = K_MK_ERROR_PARAM;
            }
         }

         /* Si une erreur s'est produite */
         if ( l_result != K_MK_OK )
         {
            /* Fermeture du fichier image */
            l_result |= mk_file_close ( p_bitmap->file, K_MK_NULL );

            /* Réinitialisation du pointeur de fichier */
            p_bitmap->file = K_MK_NULL;
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

   /* Retour */
   return ( l_result );
}


