/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_file_private.h
* @brief Déclaration des fonctions privées dédiées au système de fichiers.
* @date 6 juin 2021
*
*/

#ifndef MK_FILE_PRIVATE_H
#define MK_FILE_PRIVATE_H

/**
 * @fn void mk_file_task ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage des tâches concurrentes du système de fichiers.
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_file_task ( T_mkAddr p_param );

/**
 * @fn void mk_file_taskShared ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage des tâches partagées du système de fichiers.
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_file_taskShared ( T_mkAddr p_param );

/**
 * @fn T_mkCode mk_file_handle ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam, T_mkTask* p_task, uint8_t* p_buf, uint32_t p_sharedTermio );
 * @brief Cette fonction exécute une requête envoyée aux tâches de gestion du système de fichiers.
 *
 * @param[in]  p_message       Ce paramètre contient l'adresse d'un message de type \ref T_mkFileMessage. Le message contient les paramètres de la requêtre.
 * @param[out] p_callbackParam Ce paramètre contient l'adresse d'une structure de type \ref T_mkCallbackParam.
 * @param[in]  p_task          Ce paramètre contient l'adresse de la tâche ayant réalisée l'appel système.
 * @param[in]  p_buf           Ce paramètre contient l'adresse du cache de la tâche de gestion.
 * @param[in]  p_sharedTermio  Ce paramètre contient une valeur indiquant si le terminal est de type partagé (1) ou non (0).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la requête a été exécutée sans renconter d'erreur.
 *         \li \ref K_MK_ERROR_NOT_FOUND     : la requête a été exécutée est son résultat indique que le fichier recherché n'a pas été trouvé.
 *         \li \ref K_MK_ERROR_PARAM         : la requête n'a pas été éxécutée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC        : la requête n'a pas été exécutée car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : la requête n'a pas été éxécutée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la requête n'a pas été éxécutée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : la requête n'a pas été éxécutée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_FULL          : la requête n'a pas été éxécutée car l'espace sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_ALREADY_EXIST : la requête n'a pas été éxécutée car un fichier avec le même nom existe déjà.
 *         \li \ref K_MK_ERROR_CORRUPTED     : la requête n'a pas été éxécutée car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_COLLISION     : la requête n'a pas été éxécutée car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : la requête n'a pas été éxécutée car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_RIGHT         : la requête n'a pas été éxécutée car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_file_handle ( T_mkFileMessage* p_message, T_mkCallbackParam* p_callbackParam, T_mkTask* p_task, uint8_t* p_buf, uint32_t p_sharedTermio );

/**
 *
 */

#endif


