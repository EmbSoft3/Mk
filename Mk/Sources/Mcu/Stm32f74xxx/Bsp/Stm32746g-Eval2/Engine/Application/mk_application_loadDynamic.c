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
* @file mk_application_loadDynamic.c
* @brief Définition de la fonction mk_application_loadDynamic.
* @date 3 janv. 2024
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_application_checkDynamic ( T_mkApplicationDynamicHeader* p_header )
{
   /* Actualisation de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le paramètre est valide */
   if ( p_header != K_MK_NULL )
   {
      /* Si au moins un paramètre du descripteur de l'application est invalide */
      if ( ( p_header->header.magicNumber != K_MK_DISPLAY_APPLICATION_DYNAMICHEADER_MAGICNUMBER ) || ( p_header->header.version == 0 ) ||
           ( p_header->header.headerSize < sizeof ( T_mkApplicationHeader ) ) ||
           ( p_header->header.descriptorSize < sizeof ( T_mkApplicationDescriptor ) ) ||
           ( p_header->header.metadataSize < sizeof ( T_mkApplicationMetadata ) ) ||
           ( ( p_header->descriptor.type & K_MK_APPLICATION_TYPE_DYNAMIC ) != K_MK_APPLICATION_TYPE_DYNAMIC ) ||
           ( p_header->descriptor.stackSize == 0 ) || ( p_header->descriptor.stackAddr == K_MK_NULL ) ||
           ( p_header->descriptor.entryPoint == K_MK_NULL ) )
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

T_mkCode mk_application_loadDynamic ( T_mkApplication* p_application, T_mkApplicationRequest* p_request, uint32_t p_identifier )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_count = 0, l_length = 0;

   /* Déclaration d'un pointeur de fichier */
   T_mkFile* l_file = K_MK_NULL;

   /* Déclaration d'un pointeur de page mémoire */
   T_mkAddr l_page = K_MK_NULL;

   /* Déclaration d'un pointeur de bibliothèques */
   T_mkExternalLibrariesList l_list = { K_MK_NULL };

   /* Déclaration du pointeur d'entête de l'application dynamique */
   T_mkApplicationDynamicHeader* l_header = K_MK_NULL;

   /* Ouverture du fichier de programmation */
   l_result = mk_loader_elf_open ( p_request->content.volume, &l_file, p_request->content.path, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Allocation d'une nouvelle page mémoire */
      /* Cette page est dédiée au déploiement du fichier de programmation */
      l_result = mk_application_alloc ( ( T_mkAddr* ) &l_page, 0 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Le but des lignes ci-dessous est de stocker le nom et le chemin de l'application dans la structure de l'application */
         /* Comptage du nombre de caractères '/' dans la chaine */
         l_count = mk_utils_utfcount ( ( T_str8 ) p_request->content.path, ( uint32_t ) '/', K_MK_FONT_UTF8 );
         /* Comptage du nombre total de caractères dans la chaine */
         l_length = mk_utils_utfsize ( p_request->content.path, K_MK_FONT_UTF8 );

         /* Copie du chemin de l'application */
         /* Le nombre de caractères est inférieur à K_MK_FILE_MAX_NAME_LENGTH car l'ouverture du fichier a réussi */
         _copy ( p_application->dynamic.fileBuf, p_request->content.path, l_length );

         /* Si au moins un caractère '/' est présent */
         if ( l_count > 0 )
         {
            /* Configuration du pointeur de chemin */
            p_application->dynamic.filePath = ( T_str8 ) &p_application->dynamic.fileBuf [ 0 ];

            /* Configuration du nom de l'application */
            while ( p_application->dynamic.fileBuf [ l_length - 1 ] != '/' )
            {
               /* Décrémentation de la longueur */
               l_length = ( uint32_t ) ( l_length - 1 );
            }

            /* Suppression du caractère '/' */
            p_application->dynamic.fileBuf [ l_length - 1 ] = '\0';

            /* Configuration du pointeur de nom */
            p_application->dynamic.fileName = ( T_str8 ) &p_application->dynamic.fileBuf [ l_length ];
         }

         /* Sinon */
         else
         {
            /* Configuration des pointeurs */
            p_application->dynamic.fileName = ( T_str8 ) &p_application->dynamic.fileBuf [ 0 ];
            p_application->dynamic.filePath = ( T_str8 ) &p_application->dynamic.fileBuf [ l_length ];
         }

         /* Déploiement du programme dans la page mémoire */
         /* Cette fonction est récursive. Une ou plusieurs bibliothèques supplémentaires peuvent être chargées. */
         l_result = mk_loader_elf_loadRAM ( l_file, p_application->dynamic.filePath, l_page, &l_list, K_MK_NULL );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Récupération de l'adresse où est localisé l'entête de l'application */
            l_header = ( T_mkApplicationDynamicHeader* ) l_page;

            /* Vérification de la validité de l'application */
            l_result = mk_application_checkDynamic ( l_header );
         }

         /* Sinon */
         else
         {
            /* Une erreur s'est produite */
            /* Désallocation de toutes les bibliothèques allouées. */
            l_result |= mk_loader_flushLibraries ( &l_list );
         }

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Initialisation des attributs de l'application */
            l_result = mk_application_init ( p_application, &l_header->descriptor, p_identifier, K_MK_DISPLAY_APPLICATION_DEFAULT_PRIORITY );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Configuration de l'argument de l'application dynamique */
               p_application->descriptor.arg = p_application;

               /* Enregistrement de la page mémoire où a été allouée l'application */
               p_application->page.deploymentAddr = l_page;

               /* Enregistrement de l'adresse des ressources externes allouées */
               p_application->dynamic.libraries.first = l_list.first;

               /* Si l'application possède des arguments */
               /* Les arguments d'une application dynamique sont saisi en ligne de commande */
               if ( p_request->content.descriptor.arg != K_MK_NULL )
               {
                  /* Copie de la chaine de caractères contenant les arguments de l'application */
                  _copy ( l_header->args.chain, p_request->content.descriptor.arg, K_MK_DISPLAY_APPLICATION_ARGV_SIZE );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Copie des métadonnées de l'application */
               _copy ( &p_application->metadata, &l_header->metadata, sizeof ( T_mkApplicationMetadata ) );
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

         /* Si une erreur s'est produite */
         if ( l_result != K_MK_OK )
         {
            /* Désallocation de la page mémoire */
            l_result |= mk_application_free ( l_page );
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

      /* Fermeture du fichier de programmation */
      l_result |= mk_loader_elf_close ( l_file, K_MK_NULL );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}



