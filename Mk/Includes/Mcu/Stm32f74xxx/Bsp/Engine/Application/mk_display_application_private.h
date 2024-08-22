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
* @file mk_display_application_private.h
* @brief Déclaration des fonctions privées dédiées au module 'Application'.
* @date 17 août 2023
*
*/

#ifndef MK_DISPLAY_APPLICATION_PRIVATE_H
#define MK_DISPLAY_APPLICATION_PRIVATE_H

/**
 * @fn void mk_application_init ( T_mkApplication* p_application, uint32_t p_identifier, uint32_t p_type, uint32_t p_priority );
 * @brief Cette fonction initialise une application de type \ref T_mkApplication.
 *
 * @param[out] p_application Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 * @param[in]  p_descriptor  Ce paramètre contient l'adresse d'une structure de type \ref T_mkApplicationDescriptor.
 * @param[in]  p_identifier  Ce paramètre contient l'identifiant de la tâche principale de l'application. La valeur peut évoluer de [0 à 0xFFFFFFFF].
 * @param[in]  p_type        Ce paramètre contient le type de l'application. Il peut prendre les valeurs suivantes :
 *                           \li \ref K_MK_TYPE_DEFAULT : le contexte de l'application est de type non flottant, l'application est de type non privilégié.
 *                           \li \ref K_MK_TYPE_PRIVILEGED : le contexte de l'application est de type non flottant, l'application est de type privilégié.
 *                           \li \ref K_MK_TYPE_FLOATING : le contexte de l'application est de type flottant, l'application est de type non privilégié.
 *                           \li \ref K_MK_TYPE_FLOATING_PRIVILEGED : le contexte de l'application est de type flottant, l'application est de type privilégié.
 * @param[in]  p_priority    Ce paramètre contient la priorité de l'application. Elle peut évoluer de [1 à \ref K_MK_SCHEDULER_PRIORITY_NUMBER].
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK          : l'application a été initialisée.
 *         \li \ref K_MK_ERROR_PARAM : l'application n'a pas été initialisée car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_application_init ( T_mkApplication* p_application, T_mkApplicationDescriptor* p_descriptor, uint32_t p_identifier, uint32_t p_priority );

/**
 * @fn void mk_application_add ( T_mkApplicationList* p_list, T_mkApplication* p_application );
 * @brief Cette fonction ajoute une application de type \ref T_mkApplication dans une liste d'application. L'application est ajoutée en fin de liste.
 *
 * @param[in, out] p_list        Ce paramètre contient l'adresse d'une liste de type \ref T_mkApplicationList.
 * @param[in, out] p_application Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 *
 * @return Sans objet.
 *
 */

void mk_application_add ( T_mkApplicationList* p_list, T_mkApplication* p_application );

/**
 * @fn void mk_application_remove ( T_mkApplicationList* p_list, T_mkApplication* p_application );
 * @brief Cette fonction supprime une application d'une liste.
 *
 * @param[in, out] p_list        Ce paramètre contient l'adresse d'une liste de type \ref T_mkApplicationList.
 * @param[in, out] p_application Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication. L'application doit être présente dans la liste.
 *
 * @return Sans objet.
 *
 */

void mk_application_remove ( T_mkApplicationList* p_list, T_mkApplication* p_application );

/**
 * @fn T_mkCode mk_application_delete ( void );
 * @brief Cette fonction parcours la liste des applications à détruire puis désalloue celles dont le timeout est arrivé à échéance.
 *        Le timeout des applications restantes est actualisé d'une unité.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : la désallocation des applications à détruire a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la désallocation des applications à détruire car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la désallocation des applications à détruire a échoué car aucun jeton ne s'est libéré dans le timeout imparti.
 *         \li \ref K_MK_ERROR_ISR     : la désallocation des applications à détruire a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la désallocation des applications à détruire a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_application_delete ( void );

/**
 * @fn T_mkCode mk_application_addDeletedList ( T_mkApplication* p_application, uint32_t p_elapseCounter );
 * @brief Cette fonction ajoute une application dans la liste des application à détruire.
 *
 * @param[in] p_application   Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 * @param[in] p_elapseCounter Ce paramètre contient la durée d'attente avant d'enclencher la désallocation des pages mémoires [en frame].
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK           : l'application a été ajoutée à la liste.
 *         \li \ref K_MK_ERROR_PARAM  : l'application n'a pas été ajoutée à la liste car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : l'application n'a pas été ajoutée à la liste car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR    : l'application n'a pas été ajoutée à la liste car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT  : l'application n'a pas été ajoutée à la liste car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_application_addDeletedList ( T_mkApplication* p_application, uint32_t p_elapseCounter );

/**
 * @fn T_mkCode mk_application_removeDeletedList ( T_mkApplicationGarbageItem* p_garbageItem );
 * @brief Cette fonction retire un élément de type \ref T_mkApplicationGarbageItem de la liste des applications à détruire. L'élément est ensuite désalloué.
 * @param[in] p_garbageItem Ce paramètre contient l'adresse d'une élément de type \ref T_mkApplicationGarbageItem.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK           : l'élément a été désalloué.
 *         \li \ref K_MK_ERROR_PARAM  : l'élément n'a pas été désalloué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : l'élément n'a pas été désalloué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT  : l'élément n'a pas été désalloué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_application_removeDeletedList ( T_mkApplicationGarbageItem* p_garbageItem );

/**
 * @fn T_mkCode mk_application_alloc ( T_mkAddr* p_mkAddr, uint32_t p_mkTick );
 * @brief Cette fonction alloue une page mémoire de taille \ref K_MK_DISPLAY_APPLICATION_PAGE_SIZE.
 *
 * @param[out] p_mkAddr Ce paramètre contient l'adresse de la page allouée.
 * @param[in]  p_mkTick Ce paramètre contient la valeur du timeout. Il peut prendre les valeurs suivantes :
 *                      \li 0x0 - la fonction retourne immédiatement,
 *                      \li 0x1 à 0xFFFFFFFE - la fonction est bloquée pendant la durée spécifiée tant qu'auncune page n'est disponible,
 *                      \li 0xFFFFFFFF (\ref K_MK_TASK_WAIT_FOREVER) - la fonction est bloquée tant qu'aucune page n'est disponible.
 *                      Si la valeur "p_mkTick" est nulle et qu'aucune page mémoire n'est disponible, la fonction retourne immédiatement.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK           : la page mémoire a été allouée.
 *         \li \ref K_MK_ERROR_PARAM  : la page mémoire n'a pas été allouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : la page mémoire n'a pas été allouée car aucun bloc n'était disponible dans le timeout imparti.
 *         \li \ref K_MK_ERROR_ISR    : la page mémoire n'a pas été allouée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT  : la page mémoire n'a pas été allouée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_application_alloc ( T_mkAddr* p_mkAddr, uint32_t p_mkTick );

/**
 * @fn T_mkCode mk_application_free ( T_mkAddr p_mkAddr );
 * @brief Cette fonction désalloue une page mémoire. La page doit obligatoirement avoir été allouée avec la fonction \ref mk_application_alloc.
 * @param[in] p_mkAddr       Ce paramètre contient l'adresse du bloc de mémoire alloué.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK          : la page mémoire a été désallouée.
 *         \li \ref K_MK_ERROR_PARAM : la page mémoire n'a pas été désallouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : la page mémoire n'a pas été désallouée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : la page mémoire n'a pas été désallouée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_application_free ( T_mkAddr p_mkAddr );

/**
 * @fn T_mkCode mk_application_post ( T_mkApplication* p_application, T_mkCtrlEvent p_type );
 * @brief Cette fonction transfert un événement au dispatcher.
 *
 * @param[in] p_application Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 * @param[in] p_type        Ce paramètre contient l'identifiant de l'événement à transférer (\ref T_mkCtrlEvent).
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : le transfert de l'événement a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le transfert de l'événement a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le transfert de l'événement a échoué car aucun jeton ne s'est libéré dans le timeout imparti.
 *         \li \ref K_MK_ERROR_ISR     : le transfert de l'événement a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : le transfert de l'événement a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_application_post ( T_mkApplication* p_application, T_mkCtrlEvent p_type );

/**
 * @fn T_mkCode mk_application_release ( T_mkApplication* p_application );
 * @brief Cette fonction libère l'ensemble des ressources utilisés par une application. Les containers sont retirés des factory, les pages mémoires
 *        sont désallouées et la tâche principale de l'application est arrêtée.
 * @param[in, out] p_application Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : la libération de l'ensemble des ressources a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la libération de l'ensemble des ressources a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la libération de l'ensemble des ressources a échoué car aucun jeton ne s'est libéré dans le timeout imparti.
 *         \li \ref K_MK_ERROR_ISR     : la libération de l'ensemble des ressources a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la libération de l'ensemble des ressources a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @warning L'instance p_application n'est pas désallouée par cette fonction. Les ressources supplémentaires allouées et utilisées par l'application
 *          suite à sa création ne sont pas libérées (tâches secondaires, sémaphore, ...).
 *
 */

T_mkCode mk_application_release ( T_mkApplication* p_application );

/**
 * @fn T_mkCode mk_application_loadDispatcherInputs ( T_mkApplication* p_application );
 * @brief Cette fonction charge les attributs du dispatcher (vitesse curseur souris, ...) avec les attributs d'une application.
 * @param[in, out] p_application Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK          : le chargement des attributs du dispatcher a réussi.
 *         \li \ref K_MK_ERROR_PARAM : le chargement des attributs du dispatcher a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_application_loadDispatcherInputs ( T_mkApplication* p_application );

/**
 * @fn T_mkCode mk_application_loadDynamic ( T_mkApplication* p_application, T_mkApplicationRequest* p_request, uint32_t p_identifier );
 * @brief Cette fonction charge une application dynamique en mémoire.
 *
 * @param[in, out] p_application Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 * @param[in]      p_request     Ce paramètre contient les caractéristiques de l'application à charger.
 * @param[in]      p_identifier  Ce paramètre contient l'identifiant de la tâche principale de l'application.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK               : le chargement de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM      : le chargement de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC     : le chargement de l'application a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR        : le chargement de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le chargement de l'application a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le chargement de l'application a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : le chargement de l'application a échoué car le fichier de programmation de l'application est corrompue (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED : le chargement de l'application a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT      : le chargement de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_application_loadDynamic ( T_mkApplication* p_application, T_mkApplicationRequest* p_request, uint32_t p_identifier );

/**
 * @fn T_mkCode mk_application_handleRequest ( T_mkTask* p_task, T_mkApplicationRequest* p_request );
 * @brief Cette fonction exécute les requêtes applicatives des utilisateurs.
 *
 * @param[in] p_task    Ce paramètre contient l'adresse de la tâche qui a posté la requête.
 * @param[in] p_request Ce paramètre contient l'adresse d'une requête de type \ref T_mkApplicationRequest.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK               : le traitement de la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM      : le traitement de la requête a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC     : le traitement de la requête a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR        : le traitement de la requête a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le traitement de la requête a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le traitement de la requête a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : le traitement de la requête a échoué car le fichier de programmation de l'application est corrompue (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED : le traitement de la requête a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT      : le traitement de la requête a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_application_handleRequest ( T_mkTask* p_task, T_mkApplicationRequest* p_request );

/**
 *
 */

#endif


