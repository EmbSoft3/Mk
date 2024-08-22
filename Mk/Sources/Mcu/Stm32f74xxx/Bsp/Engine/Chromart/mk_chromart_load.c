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
* @file mk_chromart_load.c
* @brief Définition de la fonction mk_chromart_load.
* @date 24 juin 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_loadAll ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_numberOfBytesRead = 0;

   /* Configuration du pointeur de fichier au début de la table de pixel */
   l_result = mk_file_seek ( p_bitmap->file, p_bitmap->pixelArray, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Chargement du fichier en mémoire (lecture complète) */
      l_result = mk_file_read ( p_bitmap->file, ( T_mkAddr* ) p_addr, p_bitmap->imageSize, &l_numberOfBytesRead, K_MK_NULL );

      /* Si le fichier n'a pas été lu intégralement */
      if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead != p_bitmap->imageSize ) )
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

static T_mkCode mk_chromart_loadBottomToTop ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr, uint32_t p_byteCount, uint32_t p_bytesPerPixel )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_numberOfBytesRead = 0, l_counter = 0;

   /* Déclaration d'une variable stockant l'adresse courante d'une ligne de données */
   uint8_t* l_addr = ( uint8_t* ) p_addr + ( p_bytesPerPixel * ( ( p_bitmap->height - 1 ) * p_bitmap->width ) );

   /* Configuration du pointeur de fichier au début du fichier (en bas à gauche de l'image) */
   l_result = mk_file_seek ( p_bitmap->file, p_bitmap->pixelArray, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Pour le nombre de ligne de l'image */
      for ( l_counter = 0 ; ( l_counter < ( uint32_t ) p_bitmap->height ) && ( l_result == K_MK_OK ) ; l_counter++ )
      {
         /* Lecture de la ligne courante */
         l_result = mk_file_read ( p_bitmap->file, ( uint8_t* ) l_addr, p_byteCount, &l_numberOfBytesRead, K_MK_NULL );

         /* Actualisation de l'adresse de la prochaine ligne de données */
         l_addr = ( uint8_t* ) ( l_addr - ( p_bytesPerPixel * p_bitmap->width ) );

         /* Si une erreur s'est produite */
         if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead != p_byteCount ) )
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

static uint8_t* mk_chromart_convert24To32BPP ( uint8_t* p_pixelTable, uint8_t* p_addr, uint32_t p_numberOfBytes, uint32_t* p_modulo, uint8_t p_alpha )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_pixelTableCounter = 0;

   /* Cette fonction convertit les données 24 bits du bitmap en résolution 32 bits. */
   /* Un compteur variant de [0 à 3] est actualisé pour savoir quand écrire la composante alpha. */

   /* Pour le nombre d'octets à traiter */
   for ( l_counter = 0 ; l_pixelTableCounter < p_numberOfBytes ; l_counter++ )
   {
      /* Si il est temps d'actualiser la composante alpha */
      if ( ( *p_modulo ) == 0x3 )
      {
         /* Ecriture de la composante alpha */
         p_addr [ l_counter ] = p_alpha;

         /* Réinitialisation du compteur d'écriture de la composante alpha */
         ( *p_modulo ) = 0;
      }

      /* Sinon */
      else
      {
         /* Ecriture de l'octet courant (R, G ou B) */
         p_addr [ l_counter ] = p_pixelTable [ l_pixelTableCounter + 0 ];

         /* Réinitialisation du compteur d'écriture de la composante alpha */
         ( *p_modulo ) = ( *p_modulo ) + 1;

         /* Actualisation du compteur d'octets */
         l_pixelTableCounter = ( uint32_t ) ( l_pixelTableCounter + 1 );
      }
   }

   /* On ajoute un contrôle supplémentaire pour la fin du fichier */
   /* S'il est temps d'actualiser la composante alpha */
   if ( ( *p_modulo ) == 0x3 )
   {
      /* Ecriture de la composante alpha */
      p_addr [ l_counter ] = p_alpha;

      /* Réinitialisation du compteur d'écriture de la composante alpha */
      ( *p_modulo ) = 0;

      /* Actualisation du compteur d'adresse */
      l_counter = ( uint32_t ) ( l_counter + 1 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( ( uint8_t* ) ( &p_addr [ l_counter ] ) );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint8_t* mk_chromart_convert32To24BPP ( uint8_t* p_pixelTable, uint8_t* p_addr, uint32_t p_numberOfBytes, uint32_t* p_modulo )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_offset = 0;

   /* Cette fonction convertit les données 32 bits du bitmap en résolution 24 bits. */
   /* Un compteur variant de [0 à 3] est actualisé pour savoir quand écrire la composante alpha. */

   /* Pour le nombre d'octets à traiter */
   for ( l_counter = 0 ; l_counter < p_numberOfBytes ; l_counter++ )
   {
      /* On bypass la composante alpha de p_pixelTable */
      if ( ( *p_modulo ) == 0x3 )
      {
         /* Réinitialisation du compteur de la composante alpha */
         ( *p_modulo ) = 0;
      }

      /* Sinon */
      else
      {
         /* Ecriture de l'octet courant (R, G ou B) */
         p_addr [ l_offset ] = p_pixelTable [ l_counter ];

         /* Actualisation de l'offset */
         l_offset = ( uint32_t ) ( l_offset + 1 );

         /* Réinitialisation du compteur d'écriture de la composante alpha */
         ( *p_modulo ) = ( *p_modulo ) + 1;
      }


   }

   /* On ajoute un contrôle supplémentaire pour la fin du fichier */
   /* S'il est temps d'actualiser la composante alpha */
   if ( ( *p_modulo ) == 0x3 )
   {
      /* Réinitialisation du compteur d'écriture de la composante alpha */
      ( *p_modulo ) = 0;

      /* Actualisation de l'offset */
      l_offset = ( uint32_t ) ( l_offset + 1 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( ( uint8_t* ) ( &p_addr [ l_offset ] ) );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_load24To32BPPBuffer ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr, uint32_t p_numberOfPaddingBytes, uint8_t p_alpha )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_indexOfPixelTable = 0, l_modulo = 0;

   /* Déclaration d'une variable stockant les pixels 24bits de la mémoire */
   uint8_t l_pixelTable [ 3 * K_MK_BMP_PIXEL_TABLE_SIZE ];

   /* Déclaration d'une variable stockant le sens de lecture du bitmap (haut vers bas = 0 ; bas vers haut = -2) */
   int32_t l_upsideDown = ( -2 );

   /* Déclaration d'une variable stockant le nombre d'octets de padding restant à traiter */
   uint32_t l_currentPaddingCount = 0;

   /* Déclaration d'une variable stockant le nombre de données en cours de traitement */
   uint32_t l_numberOfBytesRead = 0;

   /* Déclaration d'une variable stockant le nombre de données à lire lors de la prochaine requête */
   uint32_t l_numberOfBytesToRead = ( uint32_t ) ( 3 * K_MK_BMP_PIXEL_TABLE_SIZE );

   /* Déclaration d'une variable stockant le nombre de données restant à traiter pour terminer le dessin d'une ligne */
   uint32_t l_numberOfRemainingBytesPerRow = ( uint32_t ) ( 3 * p_bitmap->width );

   /* Déclaration d'une variable stockant le nombre d'octets total à traiter dans le bitmap */
   uint32_t l_imageSize = p_bitmap->imageSize;

   /* Déclaration d'une variable stockant l'adresse courante où doit être enregistré le prochain pixel */
   uint8_t* l_addr = ( uint8_t* ) p_addr + ( 4 * ( ( ( uint32_t ) p_bitmap->height - 1 ) * ( uint32_t ) p_bitmap->width ) );

   /* Si l'image doit être chargéee du haut vers le bas */
   if ( p_bitmap->topDownRowOrder == 0 )
   {
      /* Actualisation du sens de lecture */
      l_upsideDown = 0;

      /* Actualisation de l'adresse où doit être enregistrée le prochain pixel (en haut à gauche) */
      l_addr = ( uint8_t* ) p_addr;
   }

   /* Sinon (dessin de bas en haut) */
   else
   {
      /* Ne rien faire */
   }

   /* Configuration du pointeur de fichier au début du fichier */
   l_result = mk_file_seek ( p_bitmap->file, p_bitmap->pixelArray, K_MK_NULL );

   /* Tant que des lignes reste à dessiner */
   while ( ( l_result == K_MK_OK ) && ( l_counter < p_bitmap->height ) )
   {
      /* Si plus aucune donnée n'est disponible */
      if ( l_numberOfBytesRead == 0 )
      {
         /* S'il est temps d'effectuer la dernière requête de lecture */
         if ( l_numberOfBytesToRead > l_imageSize )
         {
            /* Actualisation du nombre de données à lire */
            l_numberOfBytesToRead = l_imageSize;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Lecture d'un morceau du fichier */
         l_result = mk_file_read ( p_bitmap->file, l_pixelTable, l_numberOfBytesToRead, &l_numberOfBytesRead, K_MK_NULL );

         /* Si une erreur s'est produite */
         if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead != l_numberOfBytesToRead ) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_UNEXPECTED;
         }

         /* Sinon */
         else
         {
            /* Actualisation du nombre de données à lire */
            l_imageSize = ( uint32_t ) ( l_imageSize - l_numberOfBytesToRead );

            /* Actualisation du nombre de données disponibles */
            /* On retranche directement le nombre d'octets de padding non traité */
            l_numberOfBytesRead = ( uint32_t ) ( l_numberOfBytesRead - l_currentPaddingCount );

            /* Réinitialisation de l'index du buffer de donnée */
            l_indexOfPixelTable = 0;

            /* Actualisation du nombre d'octets de padding restant à traiter */
            l_currentPaddingCount = 0;
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
         /* Si le nombre de données disponibles est supérieur à la taille d'une ligne */
         if ( l_numberOfBytesRead >= l_numberOfRemainingBytesPerRow )
         {
            /* Copie de toute la ligne ("l_numberOfRemainingBytesPerRow" octets) dans la mémoire */
            l_addr = ( uint8_t* ) mk_chromart_convert24To32BPP ( &l_pixelTable [ l_indexOfPixelTable ], ( uint8_t* ) l_addr, l_numberOfRemainingBytesPerRow, &l_modulo, p_alpha );

            /* Actualisation du nombre d'octets disponibles */
            l_numberOfBytesRead = ( uint32_t ) ( l_numberOfBytesRead - l_numberOfRemainingBytesPerRow );

            /* Actualisation de l'index de la table de pixel */
            l_indexOfPixelTable = ( uint32_t ) ( l_indexOfPixelTable + l_numberOfRemainingBytesPerRow );

            /* Si un ou plusieurs octets de padding sont présents */
            if ( p_numberOfPaddingBytes != 0 )
            {
               /* Si le nombre de données disponibles est supérieur ou égal au nombre d'octets de padding alors on ne réalise qu'un incrément */
               if ( p_numberOfPaddingBytes <= l_numberOfBytesRead )
               {
                  /* Actualisation du nombre d'octets de padding restant à traiter */
                  l_currentPaddingCount = 0;

                  /* Actualisation du nombre d'octets disponibles */
                  l_numberOfBytesRead = ( uint32_t ) ( l_numberOfBytesRead - p_numberOfPaddingBytes );

                  /* Actualisation de l'index de la table de pixel */
                  l_indexOfPixelTable = ( uint32_t ) ( l_indexOfPixelTable + p_numberOfPaddingBytes );
               }

               /* Sinon, le nombre d'octets de padding n'est pas suffisant, on fait un traitement en 2 temps sur cette lecture et la prochaine */
               else
               {
                  /* Actualisation du nombre d'octets de padding restant à traiter */
                  l_currentPaddingCount = ( uint32_t ) ( p_numberOfPaddingBytes - l_numberOfBytesRead );

                  /* Actualisation de l'index de la table de pixel */
                  l_indexOfPixelTable = 0;

                  /* Actualisation du nombre d'octet disponible */
                  l_numberOfBytesRead = 0;
               }
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du compteur de ligne (passage à la prochaine ligne) */
            l_counter = ( uint32_t ) ( l_counter + 1 );

            /* Actualisation du nombre d'octets restant à traiter sur une ligne */
            l_numberOfRemainingBytesPerRow = ( uint32_t ) ( 3 * p_bitmap->width );

            /* Actualisation de l'adresse de la prochaine ligne à traiter */
            l_addr = ( uint8_t* ) ( l_addr + 4 * ( ( int32_t ) ( l_upsideDown * ( int32_t ) p_bitmap->width ) ) );
         }

         /* Sinon (le nombre de données n'est pas suffisant pour terminer le traitement d'une ligne */
         else
         {
            /* Copie d'une portion de la ligne ("l_numberOfBytesRead" octets) dans la mémoire */
            l_addr = ( uint8_t* ) mk_chromart_convert24To32BPP ( &l_pixelTable [ l_indexOfPixelTable ], ( uint8_t* ) l_addr, l_numberOfBytesRead, &l_modulo, p_alpha );

            /* Actualisation du nombre d'octets restant à traiter sur une ligne */
            l_numberOfRemainingBytesPerRow = ( uint32_t ) ( l_numberOfRemainingBytesPerRow - l_numberOfBytesRead );

            /* Réinitialisation du nombre d'octets disponibles */
            l_numberOfBytesRead = 0;
         }
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

static T_mkCode mk_chromart_load32To24BPPBuffer ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_indexOfPixelTable = 0, l_modulo = 0;

   /* Déclaration d'une variable stockant les pixels 24bits de la mémoire */
   uint8_t l_pixelTable [ 4 * K_MK_BMP_PIXEL_TABLE_SIZE ];

   /* Déclaration d'une variable stockant le sens de lecture du bitmap (haut vers bas = 0 ; bas vers haut = -2) */
   int32_t l_upsideDown = ( -2 );

   /* Déclaration d'une variable stockant le nombre de données en cours de traitement */
   uint32_t l_numberOfBytesRead = 0;

   /* Déclaration d'une variable stockant le nombre de données à lire lors de la prochaine requête */
   uint32_t l_numberOfBytesToRead = ( uint32_t ) ( 4 * K_MK_BMP_PIXEL_TABLE_SIZE );

   /* Déclaration d'une variable stockant le nombre de données restant à traiter pour terminer le dessin d'une ligne */
   uint32_t l_numberOfRemainingBytesPerRow = ( uint32_t ) ( 4 * p_bitmap->width );

   /* Déclaration d'une variable stockant le nombre d'octets total à traiter dans le bitmap */
   uint32_t l_imageSize = p_bitmap->imageSize;

   /* Déclaration d'une variable stockant l'adresse courante où doit être enregistré le prochain pixel */
   uint8_t* l_addr = ( uint8_t* ) p_addr + ( 3 * ( ( ( uint32_t ) p_bitmap->height - 1 ) * ( uint32_t ) p_bitmap->width ) );

   /* Si l'image doit être chargéee du haut vers le bas */
   if ( p_bitmap->topDownRowOrder == 0 )
   {
      /* Actualisation du sens de lecture */
      l_upsideDown = 0;

      /* Actualisation de l'adresse où doit être enregistrée le prochain pixel (en haut à gauche) */
      l_addr = ( uint8_t* ) p_addr;
   }

   /* Sinon (dessin de bas en haut) */
   else
   {
      /* Ne rien faire */
   }

   /* Configuration du pointeur de fichier au début du fichier */
   l_result = mk_file_seek ( p_bitmap->file, p_bitmap->pixelArray, K_MK_NULL );

   /* Tant que des lignes reste à dessiner */
   while ( ( l_result == K_MK_OK ) && ( l_counter < p_bitmap->height ) )
   {
      /* Si plus aucune donnée n'est disponible */
      if ( l_numberOfBytesRead == 0 )
      {
         /* S'il est temps d'effectuer la dernière requête de lecture */
         if ( l_numberOfBytesToRead > l_imageSize )
         {
            /* Actualisation du nombre de données à lire */
            l_numberOfBytesToRead = l_imageSize;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Lecture d'un morceau du fichier */
         l_result = mk_file_read ( p_bitmap->file, l_pixelTable, l_numberOfBytesToRead, &l_numberOfBytesRead, K_MK_NULL );

         /* Si une erreur s'est produite */
         if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead != l_numberOfBytesToRead ) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_UNEXPECTED;
         }

         /* Sinon */
         else
         {
            /* Actualisation du nombre de données à lire */
            l_imageSize = ( uint32_t ) ( l_imageSize - l_numberOfBytesToRead );

            /* Réinitialisation de l'index du buffer de donnée */
            l_indexOfPixelTable = 0;
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
         /* Si le nombre de données disponibles est supérieur à la taille d'une ligne */
         if ( l_numberOfBytesRead >= l_numberOfRemainingBytesPerRow )
         {
            /* Copie de toute la ligne ("l_numberOfRemainingBytesPerRow" octets) dans la mémoire */
            l_addr = ( uint8_t* ) mk_chromart_convert32To24BPP ( &l_pixelTable [ l_indexOfPixelTable ], ( uint8_t* ) l_addr, l_numberOfRemainingBytesPerRow, &l_modulo );

            /* Actualisation du nombre d'octets disponibles */
            l_numberOfBytesRead = ( uint32_t ) ( l_numberOfBytesRead - l_numberOfRemainingBytesPerRow );

            /* Actualisation de l'index de la table de pixel */
            l_indexOfPixelTable = ( uint32_t ) ( l_indexOfPixelTable + l_numberOfRemainingBytesPerRow );

            /* Actualisation du compteur de ligne (passage à la prochaine ligne) */
            l_counter = ( uint32_t ) ( l_counter + 1 );

            /* Actualisation du nombre d'octets restant à traiter sur une ligne */
            l_numberOfRemainingBytesPerRow = ( uint32_t ) ( 4 * p_bitmap->width );

            /* Actualisation de l'adresse de la prochaine ligne à traiter */
            l_addr = ( uint8_t* ) ( l_addr + 3 * ( ( int32_t ) ( l_upsideDown * ( int32_t ) p_bitmap->width ) ) );
         }

         /* Sinon (le nombre de données n'est pas suffisant pour terminer le traitement d'une ligne */
         else
         {
            /* Copie d'une portion de la ligne ("l_numberOfBytesRead" octets) dans la mémoire */
            l_addr = ( uint8_t* ) mk_chromart_convert32To24BPP ( &l_pixelTable [ l_indexOfPixelTable ], ( uint8_t* ) l_addr, l_numberOfBytesRead, &l_modulo );

            /* Actualisation du nombre d'octets restant à traiter sur une ligne */
            l_numberOfRemainingBytesPerRow = ( uint32_t ) ( l_numberOfRemainingBytesPerRow - l_numberOfBytesRead );

            /* Réinitialisation du nombre d'octets disponibles */
            l_numberOfBytesRead = 0;
         }
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

static T_mkCode mk_chromart_load24To24BPPBuffer ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr, uint32_t p_numberOfPaddingBytes )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_indexOfPixelTable = 0;

   /* Déclaration d'une variable stockant les pixels 24bits de la mémoire */
   uint8_t l_pixelTable [ 3 * K_MK_BMP_PIXEL_TABLE_SIZE ];

   /* Déclaration d'une variable stockant le sens de lecture du bitmap (haut vers bas = 0 ; bas vers haut = -2) */
   int32_t l_upsideDown = ( -2 );

   /* Déclaration d'une variable stockant le nombre d'octets de padding restant à traiter */
   uint32_t l_currentPaddingCount = 0;

   /* Déclaration d'une variable stockant le nombre de données en cours de traitement */
   uint32_t l_numberOfBytesRead = 0;

   /* Déclaration d'une variable stockant le nombre de données à lire lors de la prochaine requête */
   uint32_t l_numberOfBytesToRead = ( uint32_t ) ( 3 * K_MK_BMP_PIXEL_TABLE_SIZE );

   /* Déclaration d'une variable stockant le nombre de données restant à traiter pour terminer le dessin d'une ligne */
   uint32_t l_numberOfRemainingBytesPerRow = ( uint32_t ) ( 3 * p_bitmap->width );

   /* Déclaration d'une variable stockant le nombre d'octets total à traiter dans le bitmap */
   uint32_t l_imageSize = p_bitmap->imageSize;

   /* Déclaration d'une variable stockant l'adresse courante où doit être enregistré le prochain pixel */
   uint8_t* l_addr = ( uint8_t* ) p_addr + ( 3 * ( ( ( uint32_t ) p_bitmap->height - 1 ) * ( uint32_t ) p_bitmap->width ) );

   /* Si l'image doit être chargéee du haut vers le bas */
   if ( p_bitmap->topDownRowOrder == 0 )
   {
      /* Actualisation du sens de lecture */
      l_upsideDown = 0;

      /* Actualisation de l'adresse où doit être enregistrée le prochain pixel (en haut à gauche) */
      l_addr = ( uint8_t* ) p_addr;
   }

   /* Sinon (dessin de bas en haut) */
   else
   {
      /* Ne rien faire */
   }

   /* Configuration du pointeur de fichier au début du fichier */
   l_result = mk_file_seek ( p_bitmap->file, p_bitmap->pixelArray, K_MK_NULL );

   /* Tant que des lignes reste à dessiner */
   while ( ( l_result == K_MK_OK ) && ( l_counter < p_bitmap->height ) )
   {
      /* Si plus aucune donnée n'est disponible */
      if ( l_numberOfBytesRead == 0 )
      {
         /* S'il est temps d'effectuer la dernière requête de lecture */
         if ( l_numberOfBytesToRead > l_imageSize )
         {
            /* Actualisation du nombre de données à lire */
            l_numberOfBytesToRead = l_imageSize;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Lecture d'un morceau du fichier */
         l_result = mk_file_read ( p_bitmap->file, l_pixelTable, l_numberOfBytesToRead, &l_numberOfBytesRead, K_MK_NULL );

         /* Si une erreur s'est produite */
         if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead != l_numberOfBytesToRead ) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_UNEXPECTED;
         }

         /* Sinon */
         else
         {
            /* Actualisation du nombre de données à lire */
            l_imageSize = ( uint32_t ) ( l_imageSize - l_numberOfBytesToRead );

            /* Actualisation du nombre de données disponibles */
            /* On retranche directement le nombre d'octets de padding non traité */
            l_numberOfBytesRead = ( uint32_t ) ( l_numberOfBytesRead - l_currentPaddingCount );

            /* Réinitialisation de l'index du buffer de donnée */
            l_indexOfPixelTable = 0;

            /* Actualisation du nombre d'octets de padding restant à traiter */
            l_currentPaddingCount = 0;
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
         /* Si le nombre de données disponibles est supérieur à la taille d'une ligne */
         if ( l_numberOfBytesRead >= l_numberOfRemainingBytesPerRow )
         {
            /* Copie de toute la ligne ("l_numberOfRemainingBytesPerRow" octets) dans la mémoire */
            _copy ( ( uint8_t* ) l_addr, &l_pixelTable [ l_indexOfPixelTable ], l_numberOfRemainingBytesPerRow );

            /* Actualisation de l'adresse de destination */
            l_addr = ( uint8_t* ) ( l_addr + l_numberOfRemainingBytesPerRow );

            /* Actualisation du nombre d'octets disponibles */
            l_numberOfBytesRead = ( uint32_t ) ( l_numberOfBytesRead - l_numberOfRemainingBytesPerRow );

            /* Actualisation de l'index de la table de pixel */
            l_indexOfPixelTable = ( uint32_t ) ( l_indexOfPixelTable + l_numberOfRemainingBytesPerRow );

            /* Si un ou plusieurs octets de padding sont présents */
            if ( p_numberOfPaddingBytes != 0 )
            {
               /* Si le nombre de données disponibles est supérieur ou égal au nombre d'octets de padding alors on ne réalise qu'un incrément */
               if ( p_numberOfPaddingBytes <= l_numberOfBytesRead )
               {
                  /* Actualisation du nombre d'octets de padding restant à traiter */
                  l_currentPaddingCount = 0;

                  /* Actualisation du nombre d'octets disponibles */
                  l_numberOfBytesRead = ( uint32_t ) ( l_numberOfBytesRead - p_numberOfPaddingBytes );

                  /* Actualisation de l'index de la table de pixel */
                  l_indexOfPixelTable = ( uint32_t ) ( l_indexOfPixelTable + p_numberOfPaddingBytes );
               }

               /* Sinon, le nombre d'octets de padding n'est pas suffisant, on fait un traitement en 2 temps sur cette lecture et la prochaine */
               else
               {
                  /* Actualisation du nombre d'octets de padding restant à traiter */
                  l_currentPaddingCount = ( uint32_t ) ( p_numberOfPaddingBytes - l_numberOfBytesRead );

                  /* Actualisation de l'index de la table de pixel */
                  l_indexOfPixelTable = 0;

                  /* Actualisation du nombre d'octet disponible */
                  l_numberOfBytesRead = 0;
               }
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du compteur de ligne (passage à la prochaine ligne) */
            l_counter = ( uint32_t ) ( l_counter + 1 );

            /* Actualisation du nombre d'octets restant à traiter sur une ligne */
            l_numberOfRemainingBytesPerRow = ( uint32_t ) ( 3 * p_bitmap->width );

            /* Actualisation de l'adresse de la prochaine ligne à traiter */
            l_addr = ( uint8_t* ) ( l_addr + 3 * ( ( int32_t ) ( l_upsideDown * ( int32_t ) p_bitmap->width ) ) );
         }

         /* Sinon (le nombre de données n'est pas suffisant pour terminer le traitement d'une ligne */
         else
         {
            /* Copie d'une portion de la ligne ("l_numberOfBytesRead" octets) dans la mémoire */
            _copy ( ( uint8_t* ) l_addr, &l_pixelTable [ l_indexOfPixelTable ], l_numberOfBytesRead );

            /* Actualisation de l'adresse de destination */
            l_addr = ( uint8_t* ) ( l_addr + l_numberOfBytesRead );

            /* Actualisation du nombre d'octets restant à traiter sur une ligne */
            l_numberOfRemainingBytesPerRow = ( uint32_t ) ( l_numberOfRemainingBytesPerRow - l_numberOfBytesRead );

            /* Réinitialisation du nombre d'octets disponibles */
            l_numberOfBytesRead = 0;
         }
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

static T_mkCode mk_chromart_load32BPP ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr, uint32_t p_bytesPerPixel )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail stockant le nombre d'octets sur une ligne*/
   uint32_t l_byteCount = ( uint32_t ) ( 4 * ( uint32_t ) p_bitmap->width );

   /* Si la résolution du buffer est de 4 octets par pixel */
   if ( p_bytesPerPixel == K_MK_DISPLAY_ARGB8888 )
   {
      /* Si le bitmap se dessine de bas en haut */
      if ( p_bitmap->topDownRowOrder == 1 )
      {
         /* Réorganisation des données du bitmap pour obtenir un dessin de haut en bas */
         l_result = mk_chromart_loadBottomToTop ( p_bitmap, p_addr, l_byteCount, K_MK_DISPLAY_ARGB8888 );
      }

      /* Sinon */
      else
      {
         /* Chargement direct du bitmap en mémoire */
         l_result = mk_chromart_loadAll ( p_bitmap, p_addr );
      }
   }

   /* Sinon, la résolution du buffer est de 3 octets par pixel (K_MK_DISPLAY_RGB888) */
   else
   {
      /* Conversion du bitmap 32 bits en 24 bits */
      /* Les bitmap en topologie bottomToTop seront réorganisé en topToBottom */
      l_result = mk_chromart_load32To24BPPBuffer ( p_bitmap, p_addr );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_load24BPP ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr, uint32_t p_bytesPerPixel, uint8_t p_alpha )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variable de travail */
   uint32_t l_byteCount, l_paddingBytes;

   /* Détermination du nombre d'octets sur une ligne */
   l_byteCount = ( uint32_t ) ( 3 * ( uint32_t ) p_bitmap->width );

   /* Détermination préliminaire du nombre d'octets de padding */
   l_paddingBytes = _math_mod ( ( 3 * ( uint32_t ) p_bitmap->width ), 4 );

   /* Si la taille d'une ligne n'est pas alignée sur 4 octets */
   if ( l_paddingBytes != 0 )
   {
      /* Détermination du nombre d'octets de padding */
      l_paddingBytes = ( 4 - l_paddingBytes );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si la résolution du buffer est de 4 octets par pixel */
   if ( p_bytesPerPixel == K_MK_DISPLAY_ARGB8888 )
   {
      /* Conversion du bitmap 24 bits en 32 bits */
      /* Les bitmap en topologie bottomToTop seront réorganisé en topToBottom */
      l_result = mk_chromart_load24To32BPPBuffer ( p_bitmap, p_addr, l_paddingBytes, p_alpha );
   }

   /* Sinon, la résolution du buffer est de 3 octets par pixel (K_MK_DISPLAY_RGB888) */
   else
   {
      /* Si le bitmap se dessine de bas en haut */
      if ( p_bitmap->topDownRowOrder == 1 )
      {
         /* Si pas d'octets de padding, on peut déployer l'image directement */
         if ( l_paddingBytes == 0 )
         {
            /* Réorganisation des données du bitmap pour obtenir un dessin de haut en bas */
            l_result = mk_chromart_loadBottomToTop ( p_bitmap, p_addr, l_byteCount, K_MK_DISPLAY_RGB888 );
         }

         /* Sinon */
         else
         {
            /* Déploiement du bitmap 24 bits */
            /* Les bitmap en topologie bottomToTop seront réorganisé en topToBottom */
            l_result = mk_chromart_load24To24BPPBuffer ( p_bitmap, p_addr, l_paddingBytes );
         }
      }

      /* Sinon, le bitmap se dessine de haut en bas */
      else
      {
         /* Si pas d'octets de padding, on peut déployer l'image directement */
         if ( l_paddingBytes == 0 )
         {
            /* Chargement direct du bitmap en mémoire */
            l_result = mk_chromart_loadAll ( p_bitmap, p_addr );
         }

         /* Sinon */
         else
         {
            /* Déploiement du bitmap 24 bits */
            /* Les bitmap en topologie bottomToTop seront réorganisé en topToBottom */
            l_result = mk_chromart_load24To24BPPBuffer ( p_bitmap, p_addr, l_paddingBytes );
         }
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

static T_mkCode mk_chromart_loadContent ( T_mkBMPFile* p_bitmap, T_mkAddr p_addr, uint32_t p_bytesPerPixel, uint8_t p_alpha )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si la résolution de l'image est 32 BPP et si l'image n'est pas compressée */
   if ( ( p_bitmap->bitsPerPixel == 32 ) && ( p_bitmap->compression == K_MK_BMP_COMPRESSION_RGB ) )
   {
      /* Dessin du bitmap 32BPP */
      l_result = mk_chromart_load32BPP ( p_bitmap, p_addr, p_bytesPerPixel );
   }

   /* Sinon si la résolution de l'image est 24 BPP et si l'image n'est pas compressée */
   else if ( ( p_bitmap->bitsPerPixel == 24 ) && ( p_bitmap->compression == K_MK_BMP_COMPRESSION_RGB ) )
   {
      /* Dessin du bitmap 24BPP */
      l_result = mk_chromart_load24BPP ( p_bitmap, p_addr, p_bytesPerPixel, p_alpha );
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_NOT_SUPPORTED;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_checkRight ( T_mkTask* p_task, T_mkBMPFile* p_bitmap, T_mkAddr p_addr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_area = 0;

   /* Vérification de la validité de la zone mémoire écrite */
   l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_addr ) );
   l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( ( uint8_t* ) p_addr + ( K_MK_DISPLAY_BYTE_PER_PIXEL * p_bitmap->width * p_bitmap->height ) - 1 ) );

   /* Si l'adresse de destination de l'image est en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
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

T_mkCode mk_chromart_load ( T_mkTask* p_task, T_mkChromartRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'un pointeur de bitmap */
   T_mkBMPFile* l_bitmap = p_request->content.load.bitmapAddr;

   /* Si les paramètres sont valides */
   if ( ( l_bitmap != K_MK_NULL ) && ( l_bitmap->file != K_MK_NULL ) &&
        ( l_bitmap->width != 0 ) && ( l_bitmap->height != 0 ) && ( l_bitmap->imageSize != 0 ) )
   {
      /* Vérification des droits de la tâche ayant réalisé la requête */
      l_result = mk_chromart_checkRight ( p_task, p_request->content.load.bitmapAddr, p_request->content.load.destinationAddr );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si le bitmap est du type K_MK_BMP_HEADER_WIN3V1, K_MK_BMP_HEADER_WIN3V2 ou K_MK_BM_HEADER_WIN3V3 */
         if ( l_bitmap->type == K_MK_BMP_HEADER_WIN3V1 || l_bitmap->type == K_MK_BMP_HEADER_WIN3V2 || l_bitmap->type == K_MK_BMP_HEADER_WIN3V3 )
         {
            /* Lancement de la fonction de dessin */
            l_result = mk_chromart_loadContent ( p_request->content.load.bitmapAddr, p_request->content.load.destinationAddr, ( uint32_t ) p_request->content.load.bytesPerPixel, p_request->content.load.alpha );
         }

         /* Sinon si le bitmap est du type K_MK_BMP_HEADER_WIN4 */
         else if ( l_bitmap->type == K_MK_BMP_HEADER_WIN4 )
         {
            /* Lancement de la fonction de dessin */
            l_result = mk_chromart_loadContent ( p_request->content.load.bitmapAddr, p_request->content.load.destinationAddr, ( uint32_t ) p_request->content.load.bytesPerPixel, p_request->content.load.alpha );
         }

         /* Sinon si le bitmap est du type K_MK_BMP_HEADER_WIN5 */
         else if ( l_bitmap->type == K_MK_BMP_HEADER_WIN5 )
         {
            /* Lancement de la fonction de dessin */
            l_result = mk_chromart_loadContent ( p_request->content.load.bitmapAddr, p_request->content.load.destinationAddr, ( uint32_t ) p_request->content.load.bytesPerPixel, p_request->content.load.alpha );
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
         /* Enregistrement de l'adresse du bitmap */
         l_bitmap->baseAddr = p_request->content.load.destinationAddr;
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

