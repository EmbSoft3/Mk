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
* @file mk_display_console.h
* @brief Déclaration des fonctions publiques dédiées à l'objet 'Console'.
* @date 5 févr. 2023
*
*/

#ifndef MK_DISPLAY_CONSOLE_H
#define MK_DISPLAY_CONSOLE_H

/**
 * @fn void mk_console_init ( T_mkConsole* p_console, T_mkAddr p_promptBuf, uint32_t p_promptSize, T_mkAddr p_windowBuf, uint32_t p_windowSize );
 * @brief Cette fonction initialise une console.
 *
 * @param[out] p_console    Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_promptBuf  Ce paramètre contient l'adresse du buffer stockant les données de la boite d'édition de type 'Prompt'.
 * @param[in]  p_promptSize Ce paramètre contient la taille du buffer stockant les données de la boite d'édition de type 'Prompt'.
 * @param[in]  p_windowBuf  Ce paramètre contient l'adresse du buffer stockant les données de la boite d'édition de type 'Window'.
 * @param[in]  p_windowSize Ce paramètre contient la taille du buffer stockant les données de la boite d'édition de type 'Window'.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK          : la console a été initialisée.
 *         \li \ref K_MK_ERROR_PARAM : la console n'a pas été initialisée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : la console n'a pas été initialisée car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 * @note Les boites de texte et d'édition sont initialisées de manière à supporter l'encodage UTF8. L'encodage ne doit pas être modifié.
 *
 */

T_mkCode mk_console_init ( T_mkConsole* p_console, T_mkAddr p_promptBuf, uint32_t p_promptSize, T_mkAddr p_windowBuf, uint32_t p_windowSize );

/**
 * @fn void mk_console_setChild ( T_mkConsole* p_console, T_mkAddr p_child );
 * @brief Cette fonction configure le descendant d'une console.
 *
 * @param[out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_child   Ce paramètre contient l'adresse du descendant de la console (cf. nota).
 *
 * @return Sans objet.
 *
 * @note Dans l'héritage, chaque structure configure son pointeur 'child' pour pointer sur son descendant direct.
 *       Une chaine est ainsi formée. Il est alors possible de récupérer l'adresse d'un objet de plus haut niveau
 *       dans les fonctions d'écoutes et de peintures n'ayant accès qu'à une structure \ref T_mkField.
 *
 */

void mk_console_setChild ( T_mkConsole* p_console, T_mkAddr p_child );

/**
 * @fn void mk_console_setPosition ( T_mkConsole* p_console, uint32_t p_field, real32_t p_x, real32_t p_y );
 * @brief Cette fonction configure la position d'un des champs de la console.
 *
 * @param[out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_field   Ce paramètre contient l'identifiant du champ à configurer. Un des constants suivantes peut être utilisées :
 *                       \ref K_MK_CONSOLE_WINDOW, \ref K_MK_CONSOLE_PROMPT ou \ref K_MK_CONSOLE_SCREEN.
 * @param[in]  p_x       Ce paramètre contient la coordonnée x du champ [en pixel].
 *                       Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH - 1].
 * @param[in]  p_y       Ce paramètre contient la coordonnée y du champ [en pixel].
 *                       Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT - 1].
 *
 * @return Sans objet.
 *
 */

void mk_console_setPosition ( T_mkConsole* p_console, uint32_t p_field, real32_t p_x, real32_t p_y );

/**
 * @fn void mk_console_setDimension ( T_mkConsole* p_console, uint32_t p_field, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure la hauteur et la largeur d'un des champs de la console.
 *
 * @param[out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_field   Ce paramètre contient l'identifiant du champ à configurer. Un des constants suivantes peut être utilisées :
 *                       \ref K_MK_CONSOLE_WINDOW, \ref K_MK_CONSOLE_PROMPT ou \ref K_MK_CONSOLE_SCREEN.
 * @param[in]  p_width   Ce paramètre contient la largeur du champ [en pixel]. Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH].
 * @param[in]  p_height  Ce paramètre contient la hauteur du champ [en pixel]. Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT].
 *
 * @return Sans objet.
 *
 */

void mk_console_setDimension ( T_mkConsole* p_console, uint32_t p_field, uint32_t p_width, uint32_t p_height );

/**
 * @fn void mk_console_setBackgroundColor ( T_mkConsole* p_console, uint32_t p_field, uint32_t p_color );
 * @brief Cette fonction configure la couleur d'un des champs de la console.
 *
 * @param[out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_field   Ce paramètre contient l'identifiant du champ à configurer. Un des constants suivantes peut être utilisées :
 *                       \ref K_MK_CONSOLE_WINDOW, \ref K_MK_CONSOLE_PROMPT ou \ref K_MK_CONSOLE_SCREEN.
 * @param[in]  p_color   Ce paramètre contient la couleur du champ au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_console_setBackgroundColor ( T_mkConsole* p_console, uint32_t p_field, uint32_t p_color );

/**
 * @fn void mk_console_setVisibility ( T_mkConsole* p_console, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité d'une console.
 *
 * @param[out] p_console    Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_visibility Ce paramètre contient l'état de la console.
 *                          Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_console_setVisibility ( T_mkConsole* p_console, uint32_t p_visibility );

/**
 * @fn void mk_console_setTextColor ( T_mkConsole* p_console, uint32_t p_color );
 * @brief Cette fonction configure la couleur du texte d'une console.
 *
 * @param[out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_color   Ce paramètre contient la couleur du texte au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_console_setTextColor ( T_mkConsole* p_console, uint32_t p_color );

/**
 * @fn void mk_console_setActivity ( T_mkConsole* p_console, uint32_t p_activity );
 * @brief Cette fonction configure l'activité d'une console.
 *
 * @param[out] p_console  Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_activity Ce paramètre contient l'état de la console.
 *                        Il peut prendre les valeurs \ref K_MK_FIELD_ACTIF ou \ref K_MK_FIELD_INACTIF.
 *
 * @return Sans objet.
 *
 */

void mk_console_setActivity ( T_mkConsole* p_console, uint32_t p_activity );

/**
 * @fn void mk_console_setLocalEcho ( T_mkConsole* p_console, uint32_t p_localEcho );
 * @brief Cette fonction configure l'echo local de la sortie standard d'une console.
 *
 * @param[out] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_localEcho Ce paramètre contient l'état de l'echo local.
 *                         Il peut prendre les valeurs \ref K_MK_CONSOLE_LOCALECHO_ENABLED ou \ref K_MK_CONSOLE_LOCALECHO_DISABLED.
 *
 * @return Sans objet.
 *
 */

void mk_console_setLocalEcho ( T_mkConsole* p_console, uint32_t p_localEcho );

/**
 * @fn void mk_console_setCache ( T_mkConsole* p_console, uint32_t p_field, T_mkAddr p_addr );
 * @brief Cette fonction configure l'adresse d'un des caches d'une console. Le cache est un buffer stockant les pixels d'un ou
 *        plusieurs objets de la console. Son utilisation peut réduire le temps de traitement des fonctions de peintures.
 *        En effet, si les données contenues dans la console n'ont pas été modifiées, une copie de pixels
 *        est réalisée du cache vers le buffer graphique. Les traitements longs des boites de texte et d'édition ne sont pas
 *        réalisés.
 *
 * @param[out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_field   Ce paramètre contient l'identifiant du cache à configurer. Un des constants suivantes peut être
 *                       utilisées : \ref K_MK_CONSOLE_WINDOW ou \ref K_MK_CONSOLE_PROMPT.
 * @param[in]  p_addr    Ce paramètre contient l'adresse du cache de l'objet graphique à configurer.
 *                       Sa taille est définie de la manière suivante : width * height * 32 [BitsPerPixel].
 *
 * @return Sans objet.
 *
 */

void mk_console_setCache ( T_mkConsole* p_console, uint32_t p_field, T_mkAddr p_addr );

/**
 * @fn void mk_console_setListener ( T_mkConsole* p_console, T_mkListener p_listener );
 * @brief Cette fonction configure la fonction d'écoute du prompt.
 *
 * @param[out] p_console  Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_listener Ce paramètre contient l'adresse d'une fonction d'écoute possédant le prototype suivant :
 *                        T_mkCode listener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );
 *
 * @return Sans objet.
 *
 */

void mk_console_setListener ( T_mkConsole* p_console, T_mkListener p_listener );

/**
 * @fn void mk_console_setRefresh ( T_mkConsole* p_console, uint32_t p_refresh );
 * @brief Cette fonction active ou désactive le rafraichissement d'une console.
 *
 * @param[in,out] p_console  Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]     p_refresh  Ce paramètre contient l'état de rafraichissement de la console.
 *                           Les valeurs suivantes peuvent être utilisées :
 *                           \li \ref K_MK_FIELD_REFRESH_ENABLED : active le rafraichissement de la console pendant au moins 'n'
 *                           frames. La valeur 'n' est le nombre de buffers graphiques utilisés par le moteur.
 *                           \li \ref K_MK_FIELD_REFRESH_DISABLED : désactive le rafraichissement de la console. Le compteur de
 *                           rafraichissement est décrémenté d'une unité à chaque appel de la fonction. Lorsque
 *                           le compteur atteint la valeur nulle, la désactivation est effective.
 *
 * @return Sans objet.
 *
 */

void mk_console_setRefresh ( T_mkConsole* p_console, uint32_t p_refresh );

/**
 * @fn void mk_console_setFocus ( T_mkConsole* p_console, uint32_t p_state );
 * @brief Cette fonction configure l'état de l'attribut 'focus' du prompt d'une console.
 *
 * @param[out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_state   Ce paramètre contient la valeur de l'attribut 'focus'. Un des constantes suivantes peut être utilisée :
 *                       \ref K_MK_FIELD_STATE_IDLE ou \ref K_MK_FIELD_STATE_FOCUS.
 *
 * @return Sans objet.
 *
 */

void mk_console_setFocus ( T_mkConsole* p_console, uint32_t p_state );

/**
 * @fn T_mkCode mk_console_addContainer ( T_mkConsole* p_console, T_mkContainer* p_container );
 * @brief Cette fonction ajoute une console dans le container présent en paramètre.
 *
 * @param[in,out] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in,out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la console a été ajoutée dans le container.
 *         \li \ref K_MK_ERROR_PARAM   : la console n'a pas été ajoutée dans le container car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la console n'a pas été ajoutée dans le container car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la console n'a pas été ajoutée dans le container car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la console n'a pas été dans le container ajoutée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_console_addContainer ( T_mkConsole* p_console, T_mkContainer* p_container );

/**
 * @fn T_mkCode mk_console_removeContainer ( T_mkConsole* p_console, T_mkContainer* p_container );
 * @brief Cette fonction retire une console du container présent en paramètre.
 *
 * @param[in,out] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in,out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la console a été retirée dans le container.
 *         \li \ref K_MK_ERROR_PARAM   : la console n'a pas été retirée du container car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la console n'a pas été retirée du container car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la console n'a pas été retirée du container car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la console n'a pas été retirée du container car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_console_removeContainer ( T_mkConsole* p_console, T_mkContainer* p_container );

/**
 * @fn T_mkCode mk_console_open ( T_mkConsole* p_console, T_mkVolume* p_volume, T_str8 p_stdinPath, T_str8 p_stdoutPath );
 * @brief Cette fonction ouvre les fichiers d'entrée et de sortie standard d'une console de type \ref T_mkConsole.
 *        Si les fichiers existent alors ceux-ci sont réinitialisés, sinon ils sont créés. Suite à l'ouverture des fichiers, les données présentes
 *        dans le buffer de sortie sont automatiquement écrites dans le fichier de sortie.
 *
 * @param[in,out] p_console    Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]     p_volume     Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume.
 * @param[in]     p_stdinPath  Ce paramètre contient l'adresse d'une chaine de caractères stockant le chemin et le nom du fichier d'entrée standard.
 *                             La chaine de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 * @param[in]     p_stdoutPath Ce paramètre contient l'adresse d'une chaine de caractères stockant le chemin et le nom du fichier de sorite standard.
 *                             La chaine de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : les fichiers ont été ouverts correctement.
 *         \li \ref K_MK_ERROR_PARAM         : les fichiers n'ont pas été ouverts / créés car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC        : les fichiers n'ont pas été ouverts / créés car l'espace mémoire est insuffiant pour allouer un fichier.
 *         \li \ref K_MK_ERROR_ISR           : les fichiers n'ont pas été ouverts / créés car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : les fichiers n'ont pas été ouverts / créés car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : les fichiers n'ont pas été ouverts / créés car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : les fichiers n'ont pas été ouverts / créés car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_FULL          : les fichiers n'ont pas été ouverts / créés car l'espace sur le disque est insuffisant.
 *         \li \ref K_MK_ERROR_CORRUPTED     : les fichiers n'ont pas été ouverts / créés car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_COLLISION     : les fichiers n'ont pas été ouverts / créés car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : les fichiers n'ont pas été ouverts / créés car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_DENIED        : les fichiers n'ont pas été ouverts / créés car les fichiers n'ont pas été ouvert avec les droits adéquates (écriture ou lecture).
 *         \li \ref K_MK_ERROR_RIGHT         : les fichiers n'ont pas été ouverts / créés car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_console_open ( T_mkConsole* p_console, T_mkVolume* p_volume, T_str8 p_stdinPath, T_str8 p_stdoutPath );

/**
 * @fn T_mkCode mk_console_close ( T_mkConsole* p_console );
 * @brief Cette fonction ferme les fichiers d'entrée et de sortie standard d'une console.
 * @param[in,out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : les fichiers ont été fermés.
 *         \li \ref K_MK_ERROR_PARAM      : les fichiers n'ont pas été fermés car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : les fichiers n'ont pas été fermés car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : les fichiers n'ont pas été fermés car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : les fichiers n'ont pas été fermés car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED : les fichiers n'ont pas été fermés car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT      : les fichiers n'ont pas été fermés car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_console_close ( T_mkConsole* p_console );

/**
 * @fn T_mkCode mk_console_delete ( T_mkConsole* p_console );
 * @brief Cette fonction détruit les ressources allouées par une console (fermeture des fichiers d'entrée et de sortie standard de désallocation du sémaphore).
 * @param[in,out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : les ressources de la console ont été détruites.
 *         \li \ref K_MK_ERROR_PARAM      : les ressources de la console n'ont pas été détruites car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : les ressources de la console n'ont pas été détruites car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : les ressources de la console n'ont pas été détruites car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : les ressources de la console n'ont pas été détruites car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED : les ressources de la console n'ont pas été détruites car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT      : les ressources de la console n'ont pas été détruites car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_console_delete ( T_mkConsole* p_console );

/**
 * @fn T_mkCode mk_console_clear ( T_mkConsole* p_console );
 * @brief Cette fonction efface le fichier de sortie standard d'une console.
 * @param[in,out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le fichier de sortie a été effacé.
 *         \li \ref K_MK_ERROR_PARAM      : le fichier n'a pas été effacé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : le fichier n'a pas été effacé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le fichier n'a pas été effacé car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le fichier n'a pas été effacé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : le fichier n'a pas été effacé car le fichier est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED : le fichier n'a pas été effacé car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_DENIED     : le fichier n'a pas été effacé car le fichier de sortie n'a pas été ouvert avec les droits d'écriture.
 *         \li \ref K_MK_ERROR_RIGHT      : le fichier n'a pas été effacé car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_console_clear ( T_mkConsole* p_console );

/**
 * @fn T_mkCode mk_console_clean ( T_mkConsole* p_console );
 * @brief Cette fonction efface les caractères affichés dans la fenêtre d'une console. Le pointeur de fichier est positionné à la fin du fichier de sortie standard.
 * @param[in,out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : la console a été effacé.
 *         \li \ref K_MK_ERROR_PARAM      : la console n'a pas été effacée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : la console n'a pas été effacée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : la console n'a pas été effacée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : la console n'a pas été effacée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : la console n'a pas été effacée car le fichier est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED : la console n'a pas été effacée car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_DENIED     : la console n'a pas été effacée car le fichier de sortie n'a pas été ouvert avec les droits d'écriture.
 *         \li \ref K_MK_ERROR_RIGHT      : la console n'a pas été effacée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_console_clean ( T_mkConsole* p_console );

/**
 * @fn T_mkCode mk_console_print ( T_mkConsole* p_console, T_str8 p_str );
 * @brief Cette fonction enregistre un message dans le fichier de sortie standard d'une console. Un rafraichissement graphique est déclenché suite à l'appel de cette fonction.
 *
 * @param[in,out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]     p_str     Ce paramètre contient l'adresse d'une chaine de caractères au format UTF8.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le message a été enregistré dans le fichier de sortie standard.
 *         \li \ref K_MK_ERROR_PARAM      : le message n'a pas été enregistré dans le fichier de sortie standard car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : le message n'a pas été enregistré dans le fichier de sortie standard car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le message n'a pas été enregistré dans le fichier de sortie standard car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le message n'a pas été enregistré dans le fichier de sortie standard car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : le message n'a pas été enregistré dans le fichier de sortie standard car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_DENIED     : le message n'a pas été enregistré dans le fichier de sortie standard car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL       : le message n'a pas été enregistré dans le fichier de sortie standard car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *         \li \ref K_MK_ERROR_RIGHT      : le message n'a pas été enregistré dans le fichier de sortie standard car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_UNEXPECTED : le message n'a pas été enregistré dans le fichier de sortie standard car une erreur inattendue s'est produite.
 *
 */

T_mkCode mk_console_print ( T_mkConsole* p_console, T_str8 p_str );

/**
 * @fn T_mkCode mk_console_log ( T_mkConsole* p_console, T_str8 p_str );
 * @brief Cette fonction enregistre un message dans le fichier de sortie standard d'une console. L'entête suivante est ajoutée en préambule de chaque
 *        message : TID({valeur_TID}h) > {yy-mm-ddThh:mm:ss,000} > avec
 *        \li {valeur_TID} : l'identifiant de la tâche qui a posté le message,
 *        \li {yy-mm-ddThh:mm:ss,000} : la valeur du calendrier RTC.
 *        Un rafraichissement graphique est déclenché suite à l'appel de cette fonction.
 *
 * @param[in,out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]     p_str     Ce paramètre contient l'adresse d'une chaine de caractères au format UTF8.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le message a été enregistré dans le fichier de sortie standard.
 *         \li \ref K_MK_ERROR_PARAM      : le message n'a pas été enregistré dans le fichier de sortie standard car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : le message n'a pas été enregistré dans le fichier de sortie standard car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le message n'a pas été enregistré dans le fichier de sortie standard car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le message n'a pas été enregistré dans le fichier de sortie standard car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : le message n'a pas été enregistré dans le fichier de sortie standard car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_DENIED     : le message n'a pas été enregistré dans le fichier de sortie standard car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL       : le message n'a pas été enregistré dans le fichier de sortie standard car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *         \li \ref K_MK_ERROR_RIGHT      : le message n'a pas été enregistré dans le fichier de sortie standard car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_UNEXPECTED : le message n'a pas été enregistré dans le fichier de sortie standard car une erreur inattendue s'est produite.
 *
 */

T_mkCode mk_console_log ( T_mkConsole* p_console, T_str8 p_str );

/**
 * @fn T_mkCode mk_console_puts ( T_mkConsole* p_console, T_str8 p_str );
 * @brief Cette fonction enregistre un message dans le fichier de sortie standard d'une console. Elle ne déclenche pas de rafraichissement graphique.
 *
 * @param[in,out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]     p_str     Ce paramètre contient l'adresse d'une chaine de caractères au format UTF8.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le message a été enregistré dans le fichier de sortie standard.
 *         \li \ref K_MK_ERROR_PARAM      : le message n'a pas été enregistré dans le fichier de sortie standard car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : le message n'a pas été enregistré dans le fichier de sortie standard car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le message n'a pas été enregistré dans le fichier de sortie standard car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le message n'a pas été enregistré dans le fichier de sortie standard car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : le message n'a pas été enregistré dans le fichier de sortie standard car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_DENIED     : le message n'a pas été enregistré dans le fichier de sortie standard car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL       : le message n'a pas été enregistré dans le fichier de sortie standard car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *         \li \ref K_MK_ERROR_RIGHT      : le message n'a pas été enregistré dans le fichier de sortie standard car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_UNEXPECTED : le message n'a pas été enregistré dans le fichier de sortie standard car une erreur inattendue s'est produite.
 *
 */

T_mkCode mk_console_puts ( T_mkConsole* p_console, T_str8 p_str );

/**
 * @fn T_mkCode mk_console_gets ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_length );
 * @brief Cette fonction récupére la chaine de caractères présente dans le prompt de la console.
 *
 * @param[in,out] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[out]    p_str     Ce paramètre contient l'adresse du buffer où doit être enregistré le contenu du prompt.
 * @param[in]     p_length  Ce paramètre contient la taille du buffer fourni [en octet]. Le caractère de fin doit être inclu dans le compte.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : le prompt a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM     : le prompt n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : le prompt n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : le prompt n'a pas été récupéré car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : le prompt n'a pas été récupéré car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : le prompt n'a pas été récupéré car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_DENIED    : le prompt n'a pas été récupéré car le fichier d'entrée n'a pas été ouvert avec les droits en lecture.
 *         \li \ref K_MK_ERROR_RIGHT     : le prompt n'a pas été récupéré car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_console_gets ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_length );

/**
 * @fn void mk_console_setTextEncoding ( T_mkConsole* p_console, T_mkFontUnicode p_encoding );
 * @brief Cette fonction configure l'encodage des caractères de la console.
 *
 * @param[out] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in]  p_encoding  Ce paramètre contient l'encodage des caractères de la console.
 *                         Il peut prendre les valeurs \ref K_MK_FONT_ASCII, \ref K_MK_FONT_UTF8 à \ref K_MK_FONT_UTF32
 *
 * @return Sans objet.
 *
 */

void mk_console_setTextEncoding ( T_mkConsole* p_console, T_mkFontUnicode p_encoding );

/**
 * @fn T_mkCode mk_console_defaultListener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );
 * @brief Cette fonction est la fonction d'écoute par défaut du prompt d'une console de type \ref T_mkConsole. Elle est exécutée par le moteur graphique lorsqu'un événement se produit.\n
 *        En plus des contrôles standard d'une boite d'édition, cette fonction redirige le contenu du prompt vers le fichier d'entrée standard lors de l'appui sur la touche
 *        entrée.
 *
 * @param[in] p_mkContainer Ce paramètre contient l'adresse du container propriétaire du champ p_mkField.
 * @param[in] p_mkField     Ce paramètre contient l'adresse du champ \ref T_mkField présent dans le prompt de la console.
 *                          L'adresse de la console peut être récupérée en utilisant les attributs child.
 * @param[in] p_mkAppCtrlId Ce paramètre contient l'identifiant du contrôle applicatif ayant déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_mkAppCtrl   Ce paramètre contient l'adresse du contrôle applicatif ayant déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...). Celui-ci peut être nul.
 * @param[in] p_mkEvtCtrl   Ce paramètre contient le type de l'événement (\ref T_mkCtrlEvent).
 * @param[in] p_mkCtrlId    Ce paramètre contient l'identifiant de l'événement.
 *
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : l'exécution de la fonction d'écoute a réussi.
 *         \li \ref K_MK_ERROR_PARAM      : l'exécution de la fonction d'écoute a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : l'exécution de la fonction d'écoute a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : l'exécution de la fonction d'écoute a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : l'exécution de la fonction d'écoute a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : l'exécution de la fonction d'écoute a échoué car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_DENIED     : l'exécution de la fonction d'écoute a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL       : l'exécution de la fonction d'écoute a échoué car l'espace disponible sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_UNEXPECTED : l'exécution de la fonction d'écoute a échoué car une erreur inattendue s'est produite.
 *
 */

T_mkCode mk_console_defaultListener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );

/**
 *
 */

#endif
