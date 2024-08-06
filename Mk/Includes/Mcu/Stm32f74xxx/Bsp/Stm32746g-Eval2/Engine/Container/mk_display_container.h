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
* @file mk_display_container.h
* @brief Déclaration des fonctions publiques dédiées au module 'Container'.
* @todo Mettre à jour la documentation.
* @date 4 mai 2019
*
*/

#ifndef MK_DISPLAY_CONTAINER_H
#define MK_DISPLAY_CONTAINER_H

/**
 * @fn T_mkCode mk_container_create ( T_mkContainer** p_container, T_mkListener p_listener, T_mkCallback* p_callback );
 * @brief Cette fonction alloue un nouveau container de type \ref T_mkContainer.
 *
 * @param[in,out] p_container Ce paramètre contient l'adresse du container alloué.
 * @param[in]     p_listener  Ce paramètre contient l'adresse de la fonction d'écoute du container.
 *                            Il peut prendre la valeur \ref K_MK_NULL lorsqu'aucune fonction d'écoute n'est nécessaire.
 * @param[in]     p_callback  Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la création du container a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la création du container a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la création du container a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_MALLOC  : la création du container a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : la création du container a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la création du container a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_callback ( T_mkCode l_result, T_mkContainer* p_container );
 *
 */

T_mkCode mk_container_create ( T_mkContainer** p_container, T_mkListener p_listener, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_container_delete ( T_mkContainer* p_container, T_mkCallback* p_callback );
 * @brief Cette fonction supprime un container de type \ref T_mkContainer.
 *
 * @param[in,out] p_container Ce paramètre contient l'adresse du container à supprimer.
 * @param[in]     p_callback  Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la suppression du container a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la suppression du container a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la suppression du container a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la suppression du container a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la suppression du container a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_callback ( T_mkCode l_result, T_mkContainer* p_container );
 *       Le paramètre p_container prend la valeur \ref K_MK_NULL si la désinstallation a réussi.
 *
 */

T_mkCode mk_container_delete ( T_mkContainer* p_container, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_container_addField ( T_mkContainer* p_container, T_mkField* p_field, T_mkCallback* p_callback );
 * @brief Cette fonction ajoute un champ dans un container. Le champ est ajouté en fin de liste.
 *
 * @param[in,out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[in]     p_field     Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]     p_callback  Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'ajout du champ dans le container a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'ajout du champ dans le container a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'ajout du champ dans le container a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : l'ajout du champ dans le container a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : l'ajout du champ dans le container a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_callback ( T_mkCode p_result, T_mkContainer* p_container, T_mkField* p_field );
 *
 */

T_mkCode mk_container_addField ( T_mkContainer* p_container, T_mkField* p_field, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_container_removeField ( T_mkContainer* p_container, T_mkField* p_field, T_mkCallback* p_callback );
 * @brief Cette fonction retire un champ présent dans un container. Le champ à retirer doit être présent dans le container.
 *
 * @param[in,out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[in]     p_field     Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]     p_callback  Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la suppression du champ du container a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la suppression du champ du container a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la suppression du champ du container a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la suppression du champ du container a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la suppression du champ du container a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_callback ( T_mkCode p_result, T_mkContainer* p_container, T_mkField* p_field );
 *
 */

T_mkCode mk_container_removeField ( T_mkContainer* p_container, T_mkField* p_field, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_container_setListener ( T_mkContainer* p_container, T_mkListener p_listener, T_mkCallback* p_callback );
 * @brief Cette fonction configure la fonction d'écoute d'un container.
 *
 * @param[in,out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[in]     p_listener  Ce paramètre contient l'adresse d'une fonction d'écoute de type \ref T_mkListener
 * @param[in]     p_callback  Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la configuration de la fonction d'écoute a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la configuration de la fonction d'écoute a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la configuration de la fonction d'écoute a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la configuration de la fonction d'écoute a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la configuration de la fonction d'écoute a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_callback ( T_mkCode p_result, T_mkContainer* p_container );
 *
 */

T_mkCode mk_container_setListener ( T_mkContainer* p_container, T_mkListener p_listener, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_container_setVisibility ( T_mkContainer* p_container, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité de tous les champ présents dans un container.
 *
 * @param[in,out] p_container  Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[in]     p_visibility Ce paramètre contient la nouvelle valeur de visibilité des champs présents dans le container.
 *                             Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction a été exécutée correctement.
 *         \li \ref K_MK_ERROR_PARAM : la fonction n'a pas été exécutée car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_container_setVisibility ( T_mkContainer* p_container, uint32_t p_visibility );

/**
 * @fn T_mkCode mk_container_setActivity ( T_mkContainer* p_container, uint32_t p_activity );
 * @brief Cette fonction configure l'activité de tous les champ présents dans un container.
 *
 * @param[in,out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[in]     p_activity  Ce paramètre contient la nouvelle valeur d'activité des champs présents dans le container.
 *                            Il peut prendre les valeurs \ref K_MK_FIELD_ACTIF ou \ref K_MK_FIELD_INACTIF.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction a été exécutée correctement.
 *         \li \ref K_MK_ERROR_PARAM : la fonction n'a pas été exécutée car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_container_setActivity ( T_mkContainer* p_container, uint32_t p_activity );

/**
 * @fn T_mkAddr mk_container_getOwner ( T_mkContainer* p_container );
 * @brief Cette fonction retourne l'adresse du propriétaire du container (habituellement une application de type \ref T_mkApplication).
 * @return Cette fonction retourne :
 *         \li l'adresse du propriétaire du container,
 *         \li la valeur \ref K_MK_NULL si le paramètre p_container est invalide.
 *
 */

T_mkAddr mk_container_getOwner ( T_mkContainer* p_container );

/**
 *
 */

#endif

