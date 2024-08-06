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
* @file mk_supervisor_private.h
* @brief Déclaration des fonctions privées dédiées au superviseur.
* @date 4 janv. 2023
*
*/

#ifndef MK_SUPERVISOR_PRIVATE_H
#define MK_SUPERVISOR_PRIVATE_H

/**
 * @fn T_mkCode mk_supervisor_initApplication ( void );
 * @brief Cette fonction initialise puis démarre le superviseur du système.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le superviseur a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM  : le superviseur n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : le superviseur n'a pas été initialisé car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT  : le superviseur n'a pas été initialisé car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_supervisor_initApplication ( void );

/**
 * @fn T_mkCode mk_supervisor_init ( T_mkSupervisor* p_supervisor );
 * @brief Cette fonction initialise les ressources du superviseur.
 * @param[in,out] p_supervisor Ce paramètre contient l'instance d'une structure de type \ref T_mkSupervisor.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : le superviseur a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM         : le superviseur n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC        : le superviseur n'a pas été initialisé car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : le superviseur n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le superviseur n'a pas été initialisé car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : le superviseur n'a pas été initialisé en raison d'une erreur de communication.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : le superviseur n'a pas été initialisé car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_FULL          : le superviseur n'a pas été initialisé car l'espace sur le disque est insuffisant.
 *         \li \ref K_MK_ERROR_CORRUPTED     : le superviseur n'a pas été initialisé car une corruption s'est produite (table des clusters FAT).
 *         \li \ref K_MK_ERROR_COLLISION     : le superviseur n'a pas été initialisé car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : le superviseur n'a pas été initialisé car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_RIGHT         : le superviseur n'a pas été initialisé car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_supervisor_init ( T_mkSupervisor* p_supervisor );

/**
 * @fn void mk_supervisor_main ( T_mkAddr p_addr );
 * @brief Cette fonction est la fonction de démarrage du superviseur.
 * @param[in] p_addr Ce paramètre contient l'instance d'une structure de type \ref T_mkSupervisor.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_main ( T_mkAddr p_addr );

/**
 * @fn void _mk_supervisor_dump ( T_mkSupervisorDumpRegister* p_register );
 * @brief Cette fonction enregistre la valeur des registres du CPU.
 * @param[out] p_register Ce paramètre contient l'adresse d'une structure de type \ref T_mkSupervisorDumpRegister.
 *
 * @return Sans objet.
 *
 */

void _mk_supervisor_dump ( T_mkSupervisorDumpRegister* p_register );

/**
 * @fn void mk_supervisor_recovery ( T_mkSupervisor* p_supervisor, T_mkSupervisorCode p_code, T_mkTask* p_task, T_mkSupervisorMessage* p_message );
 * @brief Cette fonction est la fonction de recouvrement. Elle estexécutée lorsqu'une erreur critique impactant la stabilité du système se produit.
 *
 * @param[in] p_supervisor Ce paramètre contient l'adresse d'une structure de type \ref T_mkSupervisor.
 * @param[in] p_code       Ce paramètre contient l'identifiant de l'erreur ayant déclenchée la fonction de récupération.
 * @param[in] p_task       Ce paramètre contient l'adresse de la tâche ayant envoyé un message au superviseur.
 * @param[in] p_message    Ce paramètre contient le contenu du message envoyé au superviseur.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_recovery ( T_mkSupervisor* p_supervisor, T_mkSupervisorCode p_code, T_mkTask* p_task, T_mkSupervisorMessage* p_message );

/**
 * @fn void mk_supervisor_mount ( T_mkSupervisor* p_supervisor );
 * @brief Cette fonction monte la partition contenant le système d'exploitation.
 * @param[in,out] p_supervisor Ce paramètre contient l'adresse d'une structure de type \ref T_mkSupervisor.
 *
 * @return Sans objet.
 *
 */

T_mkCode mk_supervisor_mount ( T_mkSupervisor* p_supervisor );

/**
 * @fn void mk_supervisor_nmiFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );
 * @brief Cette fonction est déclenchée lorsqu'une erreur de type NMI_FAULT se produit. Elle réalise un ensemble
 *        d'enregistrements puis transmet un message au superviseur.
 *
 * @param[in] p_unused1 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused2 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused3 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_nmiFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );

/**
 * @fn void mk_supervisor_hardFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );
 * @brief Cette fonction est déclenchée lorsqu'une erreur de type HARD_FAULT se produit. Elle réalise un ensemble
 *        d'enregistrements puis transmet un message au superviseur.
 *
 * @param[in] p_unused1 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused2 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused3 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_hardFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );

/**
 * @fn void mk_supervisor_memFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );
 * @brief Cette fonction est déclenchée lorsqu'une erreur de type MEM_FAULT se produit. Elle réalise un ensemble
 *        d'enregistrements puis transmet un message au superviseur.
 *
 * @param[in] p_unused1 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused2 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused3 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_memFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );

/**
 * @fn void mk_supervisor_busFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );
 * @brief Cette fonction est déclenchée lorsqu'une erreur de type BUS_FAULT se produit. Elle réalise un ensemble
 *        d'enregistrements puis transmet un message au superviseur.
 *
 * @param[in] p_unused1 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused2 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused3 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_busFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );

/**
 * @fn void mk_supervisor_usageFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );
 * @brief Cette fonction est déclenchée lorsqu'une erreur de type USAGE_FAULT se produit. Elle réalise un ensemble
 *        d'enregistrements puis transmet un message au superviseur.
 *
 * @param[in] p_unused1 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused2 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused3 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_usageFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );

/**
 * @fn void mk_supervisor_fpuFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );
 * @brief Cette fonction est déclenchée lorsqu'une erreur de type FPU_FAULT se produit. Elle réalise un ensemble
 *        d'enregistrements puis transmet un message au superviseur.
 *
 * @param[in] p_unused1 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused2 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused3 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_fpuFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );

/**
 * @fn void mk_supervisor_rightFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );
 * @brief Cette fonction est déclenchée lorsqu'une erreur de type RIGHT_FAULT se produit. Elle réalise un ensemble
 *        d'enregistrements puis transmet un message au superviseur.
 *
 * @param[in] p_unused1 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused2 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused3 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_rightFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );

/**
 * @fn void mk_supervisor_stackFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );
 * @brief Cette fonction est déclenchée lorsqu'une erreur de type STACK_FAULT se produit. Elle réalise un ensemble
 *        d'enregistrements puis transmet un message au superviseur.
 *
 * @param[in] p_unused1 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused2 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused3 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_stackFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );

/**
 * @fn void mk_supervisor_handleFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );
 * @brief Cette fonction est déclenchée lorsqu'une erreur de type HANDLE_FAULT se produit. Elle réalise un ensemble
 *        d'enregistrements puis transmet un message au superviseur.
 *
 * @param[in] p_unused1 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused2 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 * @param[in] p_unused3 Ce paramètre n'est pas utilisé pour ce type d'erreur.
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_handleFault ( T_mkAddr p_unused1, T_mkAddr p_unused2, T_mkAddr p_unused3 );

/**
 * @fn void mk_supervisor_svcFault ( T_mkAddr p_mkCode, T_mkAddr p_mkObject, T_mkAddr p_mkStatus );
 * @brief Cette fonction est déclenchée lorsqu'une erreur de type SVC_FAULT se produit. Elle réalise un ensemble
 *        d'enregistrements puis transmet un message au superviseur.
 *
 * @param[in] p_mkCode   Ce paramètre contient l'identifiant d'une erreur de type SVC (\ref T_mkSVCError).
 * @param[in] p_mkObject Ce paramètre contient les caractéristiques de la requête ayant produit
 *                       l'erreur SVC (\ref T_mkSVCObject).
 * @param[in] p_mkStatus Ce paramètre contient un registre indiquant si la requête SVC a été déclenchée par
 *                       un vecteur d'interruption (1) ou non (0).
 *
 * @return Sans objet.
 *
 */

void mk_supervisor_svcFault ( T_mkAddr p_mkCode, T_mkAddr p_mkObject, T_mkAddr p_mkStatus );

/**
 * @fn T_mkCode mk_supervisor_post ( T_mkSupervisorFault p_fault, T_mkSupervisorMessage* p_message );
 * @brief Cette fonction est exécutée par les gestionnaires d'erreurs. Elle réalise un ensemble d'enregistrements
 *        puis transmet un message au superviseur.
 *
 * @param[in]     p_fault   Ce paramètre contient l'identifiant de l'erreur (\ref T_mkSupervisorFault).
 * @param[in,out] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkSupervisorMessage).
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la fonction a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la fonction a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_RIGHT   : la fonction a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_supervisor_post ( T_mkSupervisorFault p_fault, T_mkSupervisorMessage* p_message );

/**
 * @fn T_mkCode mk_supervisor_report ( T_mkSupervisorMessage* p_message, T_str8 p_fileName, T_str8 p_str );
 * @brief Cette fonction édite un rapport suite à la détection d'une erreur critique.
 *
 * @param[in,out] p_supervisor Ce paramètre contient l'adresse d'une structure de type \ref T_mkSupervisor.
 * @param[in,out] p_message    Ce paramètre contient l'adresse d'un message de type \ref T_mkSupervisorMessage).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'édition du rapport a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'édition du rapport a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'édition du rapport a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'édition du rapport a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'édition du rapport a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : l'édition du rapport a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT         : l'édition du rapport a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'édition du rapport a échoué car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_FULL          : l'édition du rapport a échoué car l'espace disponible sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : l'édition du rapport a échoué car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_COLLISION     : l'édition du rapport a échoué car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *
 */

T_mkCode mk_supervisor_report ( T_mkSupervisor* p_supervisor, T_mkSupervisorMessage* p_message );

/**
 * @fn T_mkCode mk_supervisor_listenConsole ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );
 * @brief Cette fonction est la fonction d'écoute de la console du superviseur.
 *        Elle est exécutée par le moteur graphique lorsqu'un événement se produit.
 *
 * @param[in] p_mkContainer Ce paramètre contient l'adresse du container propriétaire du champ p_mkField.
 * @param[in] p_mkField     Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la boite d'édition du superviseur.
 *                          L'adresse de la boite peut être récupérée en utilisant les attributs child.
 * @param[in] p_mkAppCtrlId Ce paramètre contient l'identifiant du contrôle applicatif ayant déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_mkAppCtrl   Ce paramètre contient l'adresse du contrôle applicatif ayant déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...). Celui-ci peut être nul.
 * @param[in] p_mkEvtCtrl   Ce paramètre contient le type de l'événement (\ref T_mkCtrlEvent).
 * @param[in] p_mkCtrlId    Ce paramètre contient l'identifiant de l'événement.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'exécution de la fonction d'écoute a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la fonction d'écoute a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la fonction d'écoute a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la fonction d'écoute a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la fonction d'écoute a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la fonction d'écoute a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la fonction d'écoute a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la fonction d'écoute a échoué car un fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la fonction d'écoute a échoué car l'espace disponible sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : l'exécution de la fonction d'écoute a échoué car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_COLLISION     : l'exécution de la fonction d'écoute a échoué car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *
 */

T_mkCode mk_supervisor_listenConsole ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );

/**
 * @fn T_mkCode mk_supervisor_listenConsole ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );
 * @brief Cette fonction est la fonction d'écoute applicative du superviseur.
 *        Elle est exécutée par le moteur graphique lorsqu'un événement se produit.\n
 *
 * @param[in] p_mkContainer Ce paramètre contient l'adresse du container propriétaire de la fonction d'écoute.
 * @param[in] p_mkField     Ce paramètre n'est pas utilisé (valeur \ref K_MK_NULL).
 * @param[in] p_mkAppCtrlId Ce paramètre contient l'identifiant du contrôle applicatif ayant déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_mkAppCtrl   Ce paramètre contient l'adresse du contrôle applicatif ayant déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...). Celui-ci peut être nul.
 * @param[in] p_mkEvtCtrl   Ce paramètre contient le type de l'événement (\ref T_mkCtrlEvent).
 * @param[in] p_mkCtrlId    Ce paramètre contient l'identifiant de l'événement.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'exécution de la fonction d'écoute a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la fonction d'écoute a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la fonction d'écoute a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la fonction d'écoute a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la fonction d'écoute a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la fonction d'écoute a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la fonction d'écoute a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la fonction d'écoute a échoué car un fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la fonction d'écoute a échoué car l'espace disponible sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : l'exécution de la fonction d'écoute a échoué car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_COLLISION     : l'exécution de la fonction d'écoute a échoué car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *
 */

T_mkCode mk_supervisor_listenApplication ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );

/**
 * @fn T_mkCode mk_supervisor_paintCpuLoad ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture de la figure affichant la charge CPU en haut à droite de l'écran.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkFigure.
 *                          L'adresse de la boite d'édition peut être récupérée en utilisant l'attribut 'child'.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le traitement de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le traitement de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le traitement de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le traitement de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_supervisor_paintCpuLoad ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_supervisor_paintFrameRate ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture de la figure affichant le framerate en haut à droite de l'écran.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkFigure.
 *                          L'adresse de la boite d'édition peut être récupérée en utilisant l'attribut 'child'.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le traitement de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le traitement de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le traitement de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le traitement de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_supervisor_paintFrameRate ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 *
 */

#endif

