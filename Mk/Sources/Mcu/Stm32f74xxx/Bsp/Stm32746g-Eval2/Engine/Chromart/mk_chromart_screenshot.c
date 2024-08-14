/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_chromart_screenshot.c
* @brief Définition de la fonction mk_chromart_screenshot.
* @date 12 août 2024
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_writeHeader ( T_mkFile* p_file )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des structures BMP */
   T_mkBMPFileHeader l_fileHeader;
   T_mkBMPImageHeader l_imageHeader;

   /* Déclaration des variables de travail */
   int32_t l_width, l_height;
   uint32_t l_fileSize, l_numberOfByteWrite = 0;

   /* Récupération des dimensions de l'écran */
   l_width = ( int32_t ) mk_display_getWidth ( );
   l_height = ( int32_t ) mk_display_getHeight ( );

   /* Détermination de la taille du fichier BMP */
   l_fileSize = K_MK_BMP_HEADER_SIZE + K_MK_BMP_HEADER_WIN3V1 + ( 4 * ( uint32_t ) l_width * ( uint32_t ) l_height );

   /* Configuration de la structure FileHeader */
   l_fileHeader.fileType = K_MK_BMP_SIGNATURE;
   l_fileHeader.lowFileSize = ( uint16_t ) ( l_fileSize & 0xFFFF );
   l_fileHeader.highFileSize = ( uint16_t ) ( ( l_fileSize >> 16 ) & 0xFFFF );
   l_fileHeader.appsRsv1 = 0;
   l_fileHeader.appsRsv2 = 0;
   l_fileHeader.lowBitmapArrayOffset = K_MK_BMP_HEADER_SIZE + K_MK_BMP_HEADER_WIN3V1;
   l_fileHeader.highBitmapArrayOffset = 0;

   /* Configuration de la structure ImageHeader */
   l_imageHeader.headerSize = K_MK_BMP_HEADER_WIN3V1;
   l_imageHeader.width  = l_width;
   l_imageHeader.height = -l_height; /* Dessin de haut en bas */
   l_imageHeader.planes = 1;
   l_imageHeader.bitsPerPixel = 32;
   l_imageHeader.compression = K_MK_BMP_COMPRESSION_RGB;
   l_imageHeader.imageSize = ( 4 * ( uint32_t ) l_width * ( uint32_t ) l_height );
   l_imageHeader.xresolution = ( int32_t ) mk_display_getResolutionX ( );
   l_imageHeader.yresolution = ( int32_t ) mk_display_getResolutionY ( );
   l_imageHeader.coloursUsed = 0;
   l_imageHeader.coloursImportant = 0;

   /* Enregistrement de la première partie de l'entête du bitmap dans le fichier */
   /* On réalise 2 accès pour palier le défaut d'alignement du format BMP */
   l_result = mk_file_write ( p_file, &l_fileHeader.fileType, K_MK_BMP_HEADER_SIZE, &l_numberOfByteWrite, K_MK_NULL );

   /* Si une erreur s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_numberOfByteWrite != K_MK_BMP_HEADER_SIZE ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_UNEXPECTED;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Enregistrement de la seconde partie de l'entête bitmap dans le fichier */
      /* On réalise 2 accès pour palier le défaut d'alignement du format BMP */
      l_result = mk_file_write ( p_file, &l_imageHeader.headerSize, K_MK_BMP_HEADER_WIN3V1, &l_numberOfByteWrite, K_MK_NULL );

      /* Si une erreur s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_numberOfByteWrite != K_MK_BMP_HEADER_WIN3V1 ) )
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

static T_mkCode mk_chromart_blendBitmap ( uint32_t* p_page, uint32_t p_width, uint32_t p_height )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_backgroundAlpha, l_foregroundAlpha;

   /* Récupération de la valeur alpha des layers de premier et d'arrière plan */
   l_backgroundAlpha = ltdc_getConstantAlpha ( K_LTDC_LAYER1 );
   l_foregroundAlpha = ltdc_getConstantAlpha ( K_LTDC_LAYER2 );

   /* Configuration du mode de fonctionnement du moteur DMA2D */
   dma2d_setMode ( K_DMA2D_MEMORY_TO_MEMORY_WITH_PFC_AND_BLENDING );

   /* Configuration de la fenêtre */
   dma2d_setRectangle ( p_width, p_height );

   /* Configuration de la bande passante */
   dma2d_setTimer ( K_MK_DISPLAY_DMA2D_BLEND_BANDWIDTH );

   /* Configuration des composantes alpha */
   dma2d_setAlphaMode ( K_DMA2D_PFC_FOREGROUND, K_DMA2D_FPC_ALPHA_MULTIPLICATION );
   dma2d_setAlphaMode ( K_DMA2D_PFC_BACKGROUND, K_DMA2D_FPC_ALPHA_MULTIPLICATION );
   dma2d_setAlpha ( K_DMA2D_PFC_FOREGROUND, l_foregroundAlpha );
   dma2d_setAlpha ( K_DMA2D_PFC_BACKGROUND, l_backgroundAlpha );

   /* Configuration des adresses de base et de destination */
   dma2d_setAddr ( K_DMA2D_MEM_OUTPUT, ( uint32_t ) p_page );
   dma2d_setAddr ( K_DMA2D_MEM_FOREGROUND, ( uint32_t ) g_mkDisplay.pnt.currentBufferPrinted->addr [ K_MK_GRAPHICS_FOREGROUND ] );
   dma2d_setAddr ( K_DMA2D_MEM_BACKGROUND, ( uint32_t ) g_mkDisplay.pnt.currentBufferPrinted->addr [ K_MK_GRAPHICS_BACKGROUND ] );

   /* Configuration des offsets */
   dma2d_setOffset ( K_DMA2D_MEM_OUTPUT, 0 );
   dma2d_setOffset ( K_DMA2D_MEM_FOREGROUND, 0 );
   dma2d_setOffset ( K_DMA2D_MEM_BACKGROUND, 0 );

   /* Configuration du format des pixels */
   dma2d_setFormat ( K_DMA2D_PFC_OUTPUT, K_DMA2D_FORMAT_ARGB8888 );
   dma2d_setFormat ( K_DMA2D_PFC_FOREGROUND, K_DMA2D_FORMAT_ARGB8888 );
   dma2d_setFormat ( K_DMA2D_PFC_BACKGROUND, K_DMA2D_FORMAT_ARGB8888 );

   /* Si le layer de premier plan est au format RGB888 */
   if ( g_mkDisplay.screen.bytesPerPixel [ K_MK_GRAPHICS_FOREGROUND ] == K_MK_DISPLAY_RGB888 )
   {
      dma2d_setFormat ( K_DMA2D_PFC_FOREGROUND, K_DMA2D_FORMAT_RGB888 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le layer d'arrière plan est au format RGB888 */
   if ( g_mkDisplay.screen.bytesPerPixel [ K_MK_GRAPHICS_BACKGROUND ] == K_MK_DISPLAY_RGB888 )
   {
      dma2d_setFormat ( K_DMA2D_PFC_BACKGROUND, K_DMA2D_FORMAT_RGB888 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Déclenchement du transfert DMA2D */
   dma2d_start ( );

   /* Attendre jusqu'à la fin du transfert */
   l_result = mk_chromart_wait ( );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_convertBitmap ( uint32_t* p_page, uint32_t p_width, uint32_t p_height )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Configuration du mode de fonctionnement du moteur DMA2D */
   dma2d_setMode ( K_DMA2D_MEMORY_TO_MEMORY_WITH_PFC );

   /* Configuration de la fenêtre */
   dma2d_setRectangle ( p_width, p_height );

   /* Configuration de la bande passante */
   dma2d_setTimer ( K_MK_DISPLAY_DMA2D_COPY_BANDWIDTH );

   /* Configuration des adresses de base et de destination */
   dma2d_setAddr ( K_DMA2D_MEM_OUTPUT, ( uint32_t ) p_page );
   dma2d_setAddr ( K_DMA2D_MEM_FOREGROUND, ( uint32_t ) g_mkDisplay.pnt.currentBufferPrinted->addr [ K_MK_GRAPHICS_FOREGROUND ] );

   /* Si seul le layer d'arrière plan est actif et si la résolution est de 24 bits par pixel */
   if ( ( g_mkDisplay.pnt.currentBufferPrinted->status.backgroundLayer == 1 ) &&
        ( g_mkDisplay.pnt.currentBufferPrinted->status.foregroundLayer == 0 ) )
   {
      dma2d_setAddr ( K_DMA2D_MEM_FOREGROUND, ( uint32_t ) g_mkDisplay.pnt.currentBufferPrinted->addr [ K_MK_GRAPHICS_BACKGROUND ] );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Configuration des offsets */
   dma2d_setOffset ( K_DMA2D_MEM_OUTPUT, 0 );
   dma2d_setOffset ( K_DMA2D_MEM_FOREGROUND, 0 );

   /* Configuration du format des pixels */
   dma2d_setFormat ( K_DMA2D_PFC_OUTPUT, K_DMA2D_FORMAT_ARGB8888 );
   dma2d_setFormat ( K_DMA2D_PFC_FOREGROUND, K_DMA2D_FORMAT_RGB888 );

   /* Déclenchement du transfert DMA2D */
   dma2d_start ( );

   /* Attendre jusqu'à la fin du transfert */
   l_result = mk_chromart_wait ( );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_writeBitmap ( T_mkFile* p_file, uint32_t* p_page )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_width, l_height, l_size;
   uint32_t l_numberOfByteWrite = 0;

   /* Récupération des dimensions de l'écran */
   l_width  = mk_display_getWidth ( );
   l_height = mk_display_getHeight ( );

   /* Détermination de la taille de l'écran (en octets) */
   l_size = ( 4 * ( uint32_t ) l_width * ( uint32_t ) l_height );

   /* Si seul le layer d'arrière plan est actif et si la résolution est de 32 bits par pixel */
   if ( ( g_mkDisplay.pnt.currentBufferPrinted->status.backgroundLayer == 1 ) &&
        ( g_mkDisplay.pnt.currentBufferPrinted->status.foregroundLayer == 0 ) &&
        ( g_mkDisplay.screen.bytesPerPixel [ K_MK_GRAPHICS_BACKGROUND ] == K_MK_DISPLAY_ARGB8888 ) )
   {
      /* Ecriture du buffer graphique d'arrière plan dans le fichier. */
      /* On ne prend pas en compte la valeur alpha du layer car un seul calque est actif. */
      /* Aucune transformation n'est nécessaire. */
      l_result = mk_file_write ( p_file, ( uint8_t* ) g_mkDisplay.pnt.currentBufferPrinted->addr [ K_MK_GRAPHICS_BACKGROUND ], l_size, &l_numberOfByteWrite, K_MK_NULL );
   }

   /* Sinon si seul le layer de premier est actif et si la résolution est de 32 bits par pixel  */
   else if ( ( g_mkDisplay.pnt.currentBufferPrinted->status.backgroundLayer == 0 ) &&
             ( g_mkDisplay.pnt.currentBufferPrinted->status.foregroundLayer == 1 ) &&
             ( g_mkDisplay.screen.bytesPerPixel [ K_MK_GRAPHICS_FOREGROUND ] == K_MK_DISPLAY_ARGB8888 ) )
   {
      /* Ecriture du buffer graphique d'arrière plan dans le fichier. */
      /* On ne prend pas en compte la valeur alpha du layer car un seul calque est actif. */
      /* Aucune transformation n'est nécessaire. */
      l_result = mk_file_write ( p_file, ( uint8_t* ) g_mkDisplay.pnt.currentBufferPrinted->addr [ K_MK_GRAPHICS_FOREGROUND ], l_size, &l_numberOfByteWrite, K_MK_NULL );
   }

   /* Sinon */
   else
   {
      /* Si seul le layer d'arrière plan est actif et si la résolution est de 24 bits par pixel */
      if ( ( g_mkDisplay.pnt.currentBufferPrinted->status.backgroundLayer == 1 ) &&
           ( g_mkDisplay.pnt.currentBufferPrinted->status.foregroundLayer == 0 ) )
      {
         /* Il est nécessaire de convertir l'image en 32 bits par pixel */
         /* Création de l'image de destination */
         l_result = mk_chromart_convertBitmap ( p_page, l_width, l_height );
      }

      /* Sinon si seul le layer de premier est actif et si la résolution est de 24 bits par pixel  */
      else if ( ( g_mkDisplay.pnt.currentBufferPrinted->status.backgroundLayer == 0 ) &&
                ( g_mkDisplay.pnt.currentBufferPrinted->status.foregroundLayer == 1 ) )
      {
         /* Il est nécessaire de convertir l'image en 32 bits par pixel */
         /* Création de l'image de destination */
         l_result = mk_chromart_convertBitmap ( p_page, l_width, l_height );
      }

      /* Sinon */
      else
      {
         /* Il est nécessaire d'effectuer au moins une transformation */
         /* Création de l'image de destination */
         l_result = mk_chromart_blendBitmap ( p_page, l_width, l_height );
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Enregistrement du buffer dans le fichier */
         l_result = mk_file_write ( p_file, ( uint32_t* ) p_page, l_size, &l_numberOfByteWrite, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si une erreur s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_numberOfByteWrite != l_size ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_UNEXPECTED;
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

static T_mkCode mk_chromart_createBitmapFile ( T_mkFile** p_file )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de retour locale */
   int32_t l_ret = 0;

   /* Déclaration d'une chaine de caractères */
   char8_t l_randomFileName [ 62 ] = { 0 };

   /* Effectue */
   do
   {
      /* Récupération d'un nom de fichier aléatoire */
      l_ret = mk_utils_getRandomString ( ( T_str8 ) l_randomFileName, ( T_str8 ) "mk/screenshot/screenshot_", ( T_str8 ) ".bmp" );

      /* Si aucune erreur ne s'est produite */
      if ( l_ret == 0 )
      {
         /* Test de l'existance du fichier à créer */
         l_result = mk_file_stat ( K_MK_NULL, ( T_str8 ) l_randomFileName, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

   /* Tant que le fichier existe et tant qu'aucune erreur ne s'est produite */
   } while ( ( l_result == K_MK_OK ) );

   /* Si un nom de fichier unique a été trouvé */
   if ( l_result == K_MK_ERROR_NOT_FOUND )
   {
      /* Création d'un nouveau fichier */
      l_result = mk_file_open ( K_MK_NULL, p_file, l_randomFileName, K_MK_FS_OPEN_CREATE | K_MK_FS_OPEN_READ | K_MK_FS_OPEN_WRITE, K_MK_NULL );
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

T_mkCode mk_chromart_screenshot ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de fichiers */
   T_mkFile* l_file = K_MK_NULL;

   /* Déclaration d'un pointeur de page mémoire */
   uint32_t* l_page = K_MK_NULL;

   /* Allocation d'une page mémoire graphique */
   l_result = mk_page_alloc ( K_MK_PAGE_ID_SDRAM, ( T_mkAddr* ) &l_page, 0 );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_page != K_MK_NULL ) )
   {
      /* Création du nouveau fichier */
      l_result = mk_chromart_createBitmapFile ( &l_file );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Ecriture de l'entête du BMP dans le fichier */
         l_result = mk_chromart_writeHeader ( l_file );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Ecriture du bitmap dans le fichier */
            l_result = mk_chromart_writeBitmap ( l_file, l_page );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Fermeture du fichier sans condition */
         l_result |= mk_file_close ( l_file, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Désallocation de la page mémoire */
      l_result |= mk_page_free ( K_MK_PAGE_ID_SDRAM, l_page );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}
