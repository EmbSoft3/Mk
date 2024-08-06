/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_display_container_private.h
* @brief Déclaration des fonctions privées dédiées au module 'Container'.
* @date 5 mai 2019
*
*/

#ifndef MK_DISPLAY_CONTAINER_PRIVATE_H
#define MK_DISPLAY_CONTAINER_PRIVATE_H

/**
 * @fn void mk_container_init ( T_mkContainer* p_container, uint32_t p_type );
 * @brief Cette fonction initialise un container de type \ref T_mkContainer.
 *
 * @param[out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[in]  p_type      Ce paramètre contient le type du container (\ref K_MK_TYPE_PRIVILEGED ou \ref K_MK_TYPE_DEFAULT).
 *
 * @return Sans objet.
 *
 */

void mk_container_init ( T_mkContainer* p_container, uint32_t p_type );

/**
 * @fn T_mkCode mk_container_add ( T_mkSemaphore* p_semaphore, T_mkContainer* p_container, T_mkField* p_field );
 * @brief Cette fonction ajoute un champ dans un container de type \ref T_mkContainer. Le champ est ajouté en fin de liste.
 *
 * @param[in]     p_semaphore Ce paramètre contient l'adresse du sémaphore gérant les accès concurrent sur les containers.
 * @param[in,out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[in]     p_field     Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le champ a été ajouté dans le container.
 *         \li \ref K_MK_ERROR_ISR   : le champ n'a pas été ajouté dans le container car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : le champ n'a pas été ajouté dans le container car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_container_add ( T_mkSemaphore* p_semaphore, T_mkContainer* p_container, T_mkField* p_field );

/**
 * @fn T_mkCode mk_container_remove ( T_mkSemaphore* p_semaphore, T_mkContainer* p_container, T_mkField* p_field );
 * @brief Cette fonction retire un champ d'un container de type \ref T_mkContainer.
 *
 * @param[in]     p_semaphore Ce paramètre contient l'adresse du sémaphore gérant les accès concurrent sur les containers.
 * @param[in,out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[in]     p_field     Ce paramètre contient l'adresse d'un champ de type \ref T_mkField. Le champ doit être présent dans le container.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le champ a été retiré du container.
 *         \li \ref K_MK_ERROR_ISR   : le champ n'a pas été retiré du container car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : le champ n'a pas été ajouté dans le container car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_container_remove ( T_mkSemaphore* p_semaphore, T_mkContainer* p_container, T_mkField* p_field );

/**
 * @fn T_mkCode mk_container_handleRequest ( T_mkTask* p_task, T_mkContainerRequest* p_request );
 * @brief Cette fonction traite les requêtes permettant d'ajouter ou supprimer un champ d'un container.
 *
 * @param[in] p_task    Ce paramètre contient l'adresse de la tâche qui a posté la requête.
 * @param[in] p_request Ce paramètre contient l'adresse d'une requête de type \ref T_mkApplicationRequest.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la requête a été exécutée.
 *         \li \ref K_MK_ERROR_PARAM   : la requête n'a pas été exécutée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : la requête n'a pas été exécutée car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : la requête n'a pas été exécutée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la requête n'a pas été exécutée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_container_handleRequest ( T_mkTask* p_task, T_mkContainerRequest* p_request );

/**
 * @fn T_mkCode mk_container_paint ( T_mkContainer* p_container, T_mkField** p_field, uint32_t p_frameNumber );
 * @brief Cette fonction exécute les fonctions de peintures des champs présents dans un container de type \ref T_mkContainer.
 *
 * @param[in]  p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[out] p_field     Ce paramètre contient l'adresse du dernier champ de type \ref T_mkField traité par la fonction.
 *
 * @return Cette fonction retourne la valeur \ref K_MK_OK si aucune erreur ne s'est produite. Sinon elle retourne le code erreur (\ref T_mkCode)
 *         de la dernière fonction de peinture exécutée.
 *
 */

T_mkCode mk_container_paint ( T_mkContainer* p_container, T_mkField** p_field );

/**
 *
 */

#endif

