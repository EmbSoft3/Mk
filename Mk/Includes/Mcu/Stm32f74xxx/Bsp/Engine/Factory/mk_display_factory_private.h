/**
*
* @copyright Copyright (C) 2019-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_display_factory_private.h
* @brief Déclaration des fonctions privées dédiées au module 'Factory'.
* @todo Mettre à jour la documentation.
* @date 5 mai 2019
*
*/

#ifndef MK_DISPLAY_FACTORY_PRIVATE_H
#define MK_DISPLAY_FACTORY_PRIVATE_H

/**
 * @fn void mk_factory_init ( T_mkFactory* p_factory );
 * @brief Cette fonction initialise une factory de type \ref T_mkFactory.
 *
 * @param[in,out] p_factory Ce paramètre contient l'adresse d'une factory de type \ref T_mkFactory.
 *
 * @return Sans objet.
 *
 */

void mk_factory_init ( T_mkFactory* p_factory );

/**
 * @fn T_mkCode mk_factory_add ( T_mkSemaphore* p_semaphore, T_mkFactory* p_factory, T_mkContainer* p_container );
 * @brief Cette fonction ajoute un container dans une factory de type \ref T_mkFactory. La position du container dans la factory est déterminée
 *        par son indice de profondeur (zIndex).
 *
 * @param[in]     p_semaphore Ce paramètre contient l'adresse du sémaphore gérant les accès concurrent sur les containers.
 * @param[in,out] p_factory   Ce paramètre contient l'adresse d'une factory de type \ref T_mkFactory.
 * @param[in]     p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le container a été ajouté dans le container.
 *         \li \ref K_MK_ERROR_ISR   : le container n'a pas été ajouté dans la factory car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : le container n'a pas été ajouté dans la factory car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_factory_add ( T_mkSemaphore* p_semaphore, T_mkFactory* p_factory, T_mkContainer* p_container );

/**
 * @fn T_mkCode mk_factory_remove ( T_mkSemaphore* p_semaphore, T_mkFactory* p_factory, T_mkContainer* p_container );
 * @brief Cette fonction retire un container d'une factory de type \ref T_mkFactory.
 *
 * @param[in]     p_semaphore Ce paramètre contient l'adresse du sémaphore gérant les accès concurrent sur les containers.
 * @param[in,out] p_factory   Ce paramètre contient l'adresse d'une factory de type \ref T_mkFactory.
 * @param[in]     p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le container a été retiré de la factory.
 *         \li \ref K_MK_ERROR_ISR   : le container n'a pas été retiré de la factory car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : le container n'a pas été retiré de la factory car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_factory_remove ( T_mkSemaphore* p_semaphore, T_mkFactory* p_factory, T_mkContainer* p_container );

/**
 * @fn T_mkCode mk_factory_paint ( T_mkFactory* p_factory, T_mkField** p_field );
 * @brief Cette fonction exécute les fonctions de peinture des containers présents dans une factory de type \ref T_mkContainer.
 *
 * @param[in]  p_factory     Ce paramètre contient l'adresse d'une factory de type \ref T_mkFactory.
 * @param[out] p_field       Ce paramètre contient l'adresse du dernier champ de type \ref T_mkField traité par la fonction.
 *
 * @return Cette fonction retourne la valeur \ref K_MK_OK si aucune erreur ne s'est produite. Sinon elle retourne le code erreur (\ref T_mkCode)
 *         de la dernière fonction de peinture exécutée.
 *
 */

T_mkCode mk_factory_paint ( T_mkFactory* p_factory, T_mkField** p_field );

/**
 *
 */

#endif

