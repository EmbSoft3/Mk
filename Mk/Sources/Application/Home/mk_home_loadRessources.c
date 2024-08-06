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
* @file mk_home_loadRessources.c
* @brief Définition de la fonction mk_home_loadRessources.
* @date 23 sept. 2023
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_loadRessource ( T_mkBMPFile* p_bmp, T_str8 p_directoryPath, T_str8 p_filePath, T_mkAddr p_bitmapAddr, uint32_t p_bytesPerPixel, uint32_t p_width, uint32_t p_height )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_width = 0, l_height = 0;

   /* Récupération de l'adresse de la partition système */
   T_mkVolume* l_volume = mk_supervisor_getVolume ( );

   /* Si le fichier n'a pas été ouvert */
   if ( p_bmp->file == K_MK_NULL )
   {
      /* Ouverture du fichier image */
      l_result = mk_bmp_open ( p_bmp, l_volume, p_directoryPath, p_filePath );
   }

   /* Sinon */
   else
   {
      /* Il est nécessaire de réouvrir l'instance des fichiers car un bouton image ne contient */
      /* pas systématiquement la même image. */

      /* Fermeture d'un fichier image */
      l_result = mk_bmp_close ( p_bmp );

      /* Réouverture du fichier */
      if ( l_result == K_MK_OK )
      {
         /* Ouverture d'un fichier image */
         l_result = mk_bmp_open ( p_bmp, l_volume, p_directoryPath, p_filePath );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Récupération de la taille de l'image */
      l_result = mk_bmp_getSize ( p_bmp, &l_width, &l_height );

      /* Si la taille de l'image est valide */
      if ( ( l_result == K_MK_OK ) &&
           ( l_width == p_width ) && ( l_height == p_height ) )
      {
         /* Chargement de l'image en mémoire */
         l_result = mk_bmp_load2D ( p_bmp, ( uint8_t* ) p_bitmapAddr, p_bytesPerPixel, 0xFF );
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

static T_mkCode mk_home_loadIcons ( T_mkHomeApplication* p_home, uint32_t* p_ressourceAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le fichier image du manager n'a pas été chargé */
   if ( p_home->view.manager.status.addr == K_MK_NULL )
   {
      /* Chargement de la ressource en mémoire */
      l_result = mk_home_loadRessource ( &p_home->view.ressources.managerSystemStatusLogo, ( T_str8 ) "",
                                         K_MK_HOME_MANAGERVIEW_STATUS_ICON_PATH, p_ressourceAddr, K_MK_DISPLAY_RGB888,
                                         K_MK_HOME_MANAGERVIEW_STATUS_ICON_WIDTH, K_MK_HOME_MANAGERVIEW_STATUS_ICON_HEIGHT );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Enregistrement de l'adresse de la ressource */
         p_home->view.manager.status.addr = ( T_mkAddr ) p_ressourceAddr;
      }

      /* Sinon */
      else
      {
         /* Une erreur s'est produite lors du chargement de la ressource. */
         /* On configure donc la valeur par défaut */
         p_home->view.manager.status.addr = K_MK_NULL;
      }
   }

   /* Si l'arrière plan de la vue principale n'a pas été chargée */
   if (  p_home->page.background == K_MK_NULL )
   {
      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Allocation de la page mémoire dédiée à l'affichage de l'arrière plan de l'application home */
         l_result = mk_page_alloc ( K_MK_PAGE_ID_SDRAM, ( T_mkAddr* ) &p_home->page.background, 0 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Chargement de la ressource en mémoire */
         l_result = mk_home_loadRessource ( &p_home->view.ressources.background, ( T_str8 ) "",
                                            K_MK_HOME_MAINVIEW_BACKGROUND_PATH,
                                            p_home->page.background, K_MK_DISPLAY_RGB888,
                                            K_MK_HOME_MAINVIEW_BACKGROUND_WIDTH, K_MK_HOME_MAINVIEW_BACKGROUND_HEIGHT );
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

T_mkCode mk_home_loadRessources ( T_mkHomeApplication* p_home )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'adresse */
   uint32_t* l_ressourceAddr = K_MK_NULL;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = mk_application_getFirst ( );

   /* Parcours de la liste d'applications */
   while ( ( l_result == K_MK_OK ) && ( l_application != K_MK_NULL ) )
   {
      /* Si l'application possède un logo et si il n'a pas déjà été chargé */
      if ( ( l_application->metadata.iconPath != K_MK_NULL ) && ( l_application->metadata.iconPath [ 0 ] != '\0' ) &&
           ( l_application->metadata.iconAddr == K_MK_NULL ) )
      {
         /* Allocation d'un nouvel espace mémoire pour charger le logo */
         l_result = mk_pool_allocSafe ( p_home->view.ressources.pool, ( T_mkAddr* ) &l_ressourceAddr, K_MK_POOL_NO_CLEAR, 0 );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Enregistrement de l'adresse de la ressource */
            l_application->metadata.iconAddr = l_ressourceAddr;

            /* Si l'application est de type dynamique */
            if ( ( l_application->descriptor.type & K_MK_APPLICATION_TYPE_DYNAMIC ) == K_MK_APPLICATION_TYPE_DYNAMIC )
            {
               /* Chargement de la ressource en mémoire en utilisant les attributs dynamique */
               l_result = mk_home_loadRessource ( &p_home->view.ressources.applicationLogo [ l_application->layer.id ],
                                                  ( T_str8 ) l_application->dynamic.filePath,
                                                  ( T_str8 ) l_application->metadata.iconPath, l_ressourceAddr,
                                                  K_MK_DISPLAY_ARGB8888,
                                                  K_MK_APPLICATION_LOGO_WIDTH, K_MK_APPLICATION_LOGO_HEIGHT );
            }

            /* Sinon */
            else
            {
               /* Chargement de la ressource en mémoire en utilisant les attributs statiques */
               l_result = mk_home_loadRessource ( &p_home->view.ressources.applicationLogo [ l_application->layer.id ],
                                                  ( T_str8 ) "", ( T_str8 ) l_application->metadata.iconPath, l_ressourceAddr,
                                                  K_MK_DISPLAY_ARGB8888,
                                                  K_MK_APPLICATION_LOGO_WIDTH, K_MK_APPLICATION_LOGO_HEIGHT );
            }
         }

         /* Sinon */
         else
         {
            /* Il n'y a plus de mémoire pour charger le logo */
            /* On configure donc la valeur par défaut */
            l_application->metadata.iconAddr = K_MK_NULL;
         }

         /* Si la ressource n'a pas été trouvé sur le système de fichiers */
         if ( l_result == K_MK_ERROR_NOT_FOUND )
         {
            /* Bypass de l'erreur */
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
         /* @todo : Charger l'icone par défaut */
      }

      /* Passage à la prochaine application */
      l_application = l_application->next;
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Chargement des icônes utilisées par la vue principale et le manager */
      l_result = mk_home_loadIcons ( p_home, p_home->page.pointer );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


