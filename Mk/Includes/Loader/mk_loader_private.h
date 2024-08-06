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
* @file mk_loader_private.h
* @brief Déclaration des fonctions privées dédiées aux chargements des fichiers de programmation et des bibliothèques externes.
* @date 14 janv. 2024
*
*/

#ifndef MK_LOADER_PRIVATE_H
#define MK_LOADER_PRIVATE_H

/**
 * @fn T_mkCode mk_loader_init ( void );
 * @brief Cette fonction initialise le gestionnaire de programme externe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le gestionnaire de programme a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM   : le gestionnaire de programme n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le gestionnaire de programme n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le gestionnaire de programme n'a pas été initialisé en raison d'une erreur d'allocation dynamique.
 */

T_mkCode mk_loader_init ( void );

/**
 * @fn T_mkCode mk_loader_addLibrary ( T_mkExternalLibrariesList* p_list, T_mkExternalLibraryItem* p_library );
 * @brief Cette fonction ajoute un nouvelle bibliothèque dans une liste de bibliothèques externes.
 *
 * @param[in, out] p_list    Ce paramètre contient l'adresse d'une liste de bibliothèques externes.
 * @param[in]      p_library Ce paramètre contient l'adresse d'une bibliothèque externe de type \ref T_mkExternalLibraryItem.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la nouvelle bibliothèque a été ajoutée dans la liste des bibliothèques.
 *         \li \ref K_MK_ERROR_PARAM : la nouvelle bibliothèque n'a pas été ajoutée dans la liste des bibliothèques car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_loader_addLibrary ( T_mkExternalLibrariesList* p_list, T_mkExternalLibraryItem* p_library );

/**
 * @fn T_mkCode mk_loader_searchLibrary ( T_mkExternalLibrariesList* p_list, T_mkExternalLibraryItem** p_item, T_str8 p_libraryName );
 * @brief Cette fonction recherche une bibliothèque dans une liste de bibliothèques externes.
 *
 * @param[in]  p_list        Ce paramètre contient l'adresse d'une liste de bibliothèques externes.
 * @param[out] p_item        Ce paramètre contient l'adresse d'une bibliothèque externe de type \ref T_mkExternalLibraryItem.
 * @param[in]  p_libraryName Ce paramètre contient l'adresse de la chaine de caractères stockant le nom de la bibliothèque externe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la bibliothèque recherchée a été trouvée.
 *         \li \ref K_MK_ERROR_PARAM         : la bibliothèque recherchée n'a été trouvée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : la bibliothèque recherchée n'a été trouvée.
 *
 */

T_mkCode mk_loader_searchLibrary ( T_mkExternalLibrariesList* p_list, T_mkExternalLibraryItem** p_item, T_str8 p_libraryName );

/**
 * @fn T_mkCode mk_loader_flushLibraries ( T_mkExternalLibrariesList* p_list );
 * @brief Cette fonction désalloue l'ensemble des bibliothèques présente dans une liste de bibliothèques externes.
 * @param[in]  p_list        Ce paramètre contient l'adresse d'une liste de bibliothèques externes.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : les bibliothèques de la liste ont été désallouées.
 *         \li \ref K_MK_ERROR_PARAM : les bibliothèques de la liste n'ont pas été désallouées car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : les bibliothèques de la liste n'ont pas été désallouées car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : les bibliothèques de la liste n'ont pas été désallouées car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_loader_flushLibraries ( T_mkExternalLibrariesList* p_list );

/**
 *
 */

#endif

