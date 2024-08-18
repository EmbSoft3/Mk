/**
*
* @copyright Copyright (C) 2021-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_fat_close.c
* @brief Définition de la fonction mk_fat_close.
* @date 10 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_close ( T_mkFile* p_file )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un descripteur de fichiers */
   T_mkFATEntryDescriptor l_fileDescriptor;

   /* Déclaration des variables de travail */
   uint16_t l_date = 0, l_time = 0;

   /* Si le paramètre est valide */
   if ( p_file != K_MK_NULL )
   {
      /* Si le fichier n'a pas été supprimé et si le disque n'est pas protégé en écriture */
      if ( ( p_file->flag.deleted == 0 ) && ( p_file->flag.writeProtect == 0 ) )
      {
         /* Lors de la fermeture du fichier, on actualise le champ "LastAccessDate" sans condition */
         /* Les champs "LastModifiedDate" et "LastModifiedTime" sont modifiés uniquement si une opération d'écriture */
         /* a été effectuée */

         /* Récupération du descripteur de fichier */
         l_result = mk_fat_utils_getFileEntryDescriptor ( p_file, &l_fileDescriptor );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Récupération du calendrier système */
            l_result = mk_fat_utils_getDate ( &l_date, &l_time );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Configuration de la dernière date d'accès */
               l_fileDescriptor.accessDate = l_date;

               /* Si le fichier a été modifié */
               if ( p_file->flag.modified == 1 )
               {
                  /* Configuration des dates de modification */
                  l_fileDescriptor.modificationDate = l_date;
                  l_fileDescriptor.modificationTime = l_time;
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Ecriture du descripteur de fichier sur le disque */
               l_result = mk_fat_utils_setFileEntryDescriptor ( p_file, &l_fileDescriptor );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Synchronisation du cache avec le disque */
                  l_result = mk_fat_utils_sync ( p_file );
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

      /* Réinitialisation de l'instance du fichier */
      _writeWords ( p_file, 0, sizeof ( T_mkFile ) >> 2 );
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
