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
* @file mk_home.h
* @brief Déclaration des fonctions publiques dédiées à l'applicaiton home.
* @date 6 mai 2019
*
*/

#ifndef MK_HOME_H
#define MK_HOME_H

/**
 * @fn void mk_home_main ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage de l'application home.
 * @param[in] p_param Ce paramètre contient l'adresse d'une application de type \ref T_mkHomeApplication.
 *
 * @return Sans objet.
 *
 */

void mk_home_main ( T_mkAddr p_param );

/**
 * @fn T_mkCode mk_home_init ( T_mkHomeApplication* p_home );
 * @brief Cette fonction initialise une application de type \ref T_mkHomeApplication.
 * @param[in] p_home Ce paramètre contient l'adresse d'une application de type \ref T_mkHomeApplication.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'initialisation de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'initialisation de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC        : l'initialisation de l'application a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : l'initialisation de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT         : l'initialisation de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'initialisation de l'application a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'initialisation de l'application a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'initialisation de l'application a échoué car une ressource est corrompue (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'initialisation de l'application a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_NOT_SUPPORTED : l'initialisation de l'application a échoué car un format de fichier n'est pas supporté.
 *
 */

T_mkCode mk_home_init ( T_mkHomeApplication* p_home );

/**
 * @fn T_mkCode mk_home_install ( void );
 * @brief Cette fonction installe les applications par défaut au démarrage du système.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK               : l'installation des applications a réussi.
 *         \li \ref K_MK_ERROR_PARAM      : l'installation des applications a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC     : l'installation des applications a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR        : l'installation des applications a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT      : l'installation des applications a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT    : l'installation des applications a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : l'installation des applications a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : l'installation des applications a échoué car une ressource est corrompue (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED : l'installation des applications a échoué car une erreur inattendue s'est produite.
 *
 *
 */

T_mkCode mk_home_install ( void );

/**
 * @fn T_mkCode mk_home_loadRessources ( T_mkHomeApplication* p_home );
 * @brief Cette fonction initialise les ressources d'une application de type \ref T_mkHomeApplication.
 * @param[in] p_home Ce paramètre contient l'adresse d'une application de type \ref T_mkHomeApplication.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : le chargement des ressources de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : le chargement des ressources de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC        : le chargement des ressources de l'application a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : le chargement des ressources de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT         : le chargement des ressources de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le chargement des ressources de l'application a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : le chargement des ressources de l'application a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : le chargement des ressources de l'application a échoué car une ressource est corrompue (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : le chargement des ressources de l'application a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_NOT_SUPPORTED : le chargement des ressources de l'application a échoué car un format de fichier n'est pas supporté.
 *
 */

T_mkCode mk_home_loadRessources ( T_mkHomeApplication* p_home );

/**
 *
 */

/**
 * @fn void mk_home_main_setVisibility ( T_mkHomeApplication* p_home );
 * @brief Cette fonction configure la visibilité et la position des boutons images de la barre applicative de la vue principale.
 * @param[in] p_home Ce paramètre contient l'adresse d'une application de type \ref T_mkHomeApplication.
 *
 * @return Sans objet.
 *
 */

void mk_home_main_setVisibility ( T_mkHomeApplication* p_home );

/**
 * @fn T_mkCode mk_home_main_paintApplicationButton ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture des boutons image de la barre applicative.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkButtonImage.
 *                          L'adresse de la figure peut être récupérée en utilisant l'attribut 'child'.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_main_paintApplicationButton ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_home_main_paintBackground ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture de l'arrière plan de l'application home.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkButtonImage.
 *                          L'adresse de la figure peut être récupérée en utilisant l'attribut 'child'.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_main_paintBackground ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_home_main_paintForeground ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture du premier plan de l'application home.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkScreen.
 *                          L'adresse de la figure peut être récupérée en utilisant l'attribut 'child'.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_main_paintForeground ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_home_main_listenApplication ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );
 * @brief Cette fonction est la fonction d'écoute applicative du container de la vue principale. Elle s'occupe des événements en relation avec les applications et le clavier.
 *
 * @param[in] p_container Ce paramètre contient l'adresse du container propriétaire du champ p_mkField.
 * @param[in] p_field     Ce paramètre contient la valeur \ref K_MK_NULL.
 * @param[in] p_appCtrlId Ce paramètre contient l'identifiant du contrôle applicatif ayant déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl   Ce paramètre contient l'adresse du contrôle applicatif ayant déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...). Celui-ci peut être nul.
 * @param[in] p_evtCtrl   Ce paramètre contient le type de l'événement (\ref T_mkCtrlEvent).
 * @param[in] p_ctrlId    Ce paramètre contient l'identifiant de l'événement.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction d'écoute a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction d'écoute a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction d'écoute a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : l'exécution de la fonction d'écoute a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction d'écoute a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_main_listenApplication ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );

/**
 * @fn T_mkCode mk_home_main_listenScreen ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );
 * @brief Cette fonction est la fonction d'écoute de l'arrière plan de la vue principale. Elle s'occupe des événements en relation avec le clavier et la souris.
 *
 * @param[in] p_container Ce paramètre contient l'adresse du container propriétaire du champ p_mkField.
 * @param[in] p_field     Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkScreen.
 * @param[in] p_appCtrlId Ce paramètre contient l'identifiant du contrôle applicatif ayant déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl   Ce paramètre contient l'adresse du contrôle applicatif ayant déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...). Celui-ci peut être nul.
 * @param[in] p_evtCtrl   Ce paramètre contient le type de l'événement (\ref T_mkCtrlEvent).
 * @param[in] p_ctrlId    Ce paramètre contient l'identifiant de l'événement.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK : l'exécution de la fonction d'écoute a réussi.
 *
 */

T_mkCode mk_home_main_listenScreen ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );

/**
 * @fn T_mkCode mk_home_main_listenApplicationButton ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );
 * @brief Cette fonction est la fonction d'écoute des boutons image de la vue principale. Elle s'occupe des événements en relation avec la souris et le clavier.
 *
 * @param[in] p_container Ce paramètre contient l'adresse du container propriétaire du champ p_mkField.
 * @param[in] p_field     Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkButtonImage.
 * @param[in] p_appCtrlId Ce paramètre contient l'identifiant du contrôle applicatif ayant déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl   Ce paramètre contient l'adresse du contrôle applicatif ayant déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...). Celui-ci peut être nul.
 * @param[in] p_evtCtrl   Ce paramètre contient le type de l'événement (\ref T_mkCtrlEvent).
 * @param[in] p_ctrlId    Ce paramètre contient l'identifiant de l'événement.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction d'écoute a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction d'écoute a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction d'écoute a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : l'exécution de la fonction d'écoute a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction d'écoute a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_main_listenApplicationButton ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );

/**
 *
 */

/**
 * @fn void mk_home_manager_setVisibility ( T_mkHomeApplication* p_home );
 * @brief Cette fonction configure la visibilité de la barre applicative du manager.
 * @param[in] p_home Ce paramètre contient l'adresse d'une application de type \ref T_mkHomeApplication.
 *
 * @return Sans objet.
 *
 */

void mk_home_manager_setVisibility ( T_mkHomeApplication* p_home );

/**
 * @fn T_mkCode mk_home_manager_paintScreen ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture de l'arrière plan du manager.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkScreen.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_manager_paintScreen ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_home_manager_paintScreen ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture des boutons image du manager.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkButtonImage.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_manager_paintButtonImage ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_home_manager_paintBackground ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture de l'arrière plan du manager.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkScreen.
 *                          L'adresse de la figure peut être récupérée en utilisant l'attribut 'child'.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_manager_paintBackground ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_home_manager_paintGraphics ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture des graphiques du manager.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkGraph2D.
 *                          L'adresse de la figure peut être récupérée en utilisant l'attribut 'child'.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_manager_paintGraphics ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_home_manager_paintApplicationListBackground ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture de l'arrière plan de la liste d'application.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkFigure.
 *                          L'adresse de la figure peut être récupérée en utilisant l'attribut 'child'.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_manager_paintApplicationListBackground ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_home_manager_paintStatus ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture de la zone de statut du manager.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkButtonImage.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_manager_paintStatus ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_home_main_listenScreen ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );
 * @brief Cette fonction est la fonction d'écoute de l'arrière plan du manager. Elle s'occupe des événements en relation avec le clavier.
 *
 * @param[in] p_container Ce paramètre contient l'adresse du container propriétaire du champ p_mkField.
 * @param[in] p_field     Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkScreen.
 * @param[in] p_appCtrlId Ce paramètre contient l'identifiant du contrôle applicatif ayant déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl   Ce paramètre contient l'adresse du contrôle applicatif ayant déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...). Celui-ci peut être nul.
 * @param[in] p_evtCtrl   Ce paramètre contient le type de l'événement (\ref T_mkCtrlEvent).
 * @param[in] p_ctrlId    Ce paramètre contient l'identifiant de l'événement.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction d'écoute a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction d'écoute a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction d'écoute a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : l'exécution de la fonction d'écoute a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction d'écoute a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_home_manager_listenScreen ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );

/**
 *
 */

#endif
