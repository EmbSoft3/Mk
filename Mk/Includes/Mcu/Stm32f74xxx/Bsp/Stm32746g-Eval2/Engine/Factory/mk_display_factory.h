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
* @file mk_display_factory.h
* @brief Déclaration des fonctions publiques dédiées au module 'Factory'.
* @todo Mettre à jour la documentation.
* @date 4 mai 2019
*
*/

#ifndef MK_DISPLAY_FACTORY_H
#define MK_DISPLAY_FACTORY_H

/**
 * @fn T_mkCode mk_factory_addContainer ( T_mkContainer* p_container, T_mkCallback* p_callback );
 * @brief Cette fonction ajoute un container dans une factory de type \ref T_mkFactory. Le container est ajouté en fin de liste.
 *
 * @param[in,out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[in]     p_callback  Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'ajout du container dans la factory a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'ajout du container dans la factory a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'ajout du container dans la factory a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : l'ajout du container dans la factory a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : l'ajout du container dans la factory a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_callback ( T_mkCode l_result, T_mkContainer* p_container );
 *
 */

T_mkCode mk_factory_addContainer ( T_mkContainer* p_container, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_factory_removeContainer ( T_mkContainer* p_container, T_mkCallback* p_callback );
 * @brief Cette fonction retire un container d'une factory de type \ref T_mkFactory. Le container à retirer doit être présent dans la factory.
 *
 * @param[in,out] p_container Ce paramètre contient l'adresse d'un container de type \ref T_mkContainer.
 * @param[in]     p_callback  Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la suppression du container de la factory a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la suppression du container de la factory a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la suppression du container de la factory a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la suppression du container de la factory a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la suppression du container de la factory a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_callback ( T_mkCode l_result, T_mkContainer* p_container );
 *
 */

T_mkCode mk_factory_removeContainer ( T_mkContainer* p_container, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_factory_setVisibility ( T_mkFactory* p_factory, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité de tous les containers présents dans une factory.
 *
 * @param[in,out] p_factory    Ce paramètre contient l'adresse d'une factory de type \ref T_mkFactory.
 * @param[in]     p_visibility Ce paramètre contient la nouvelle valeur de visibilité des containers présents dans la factory.
 *                             Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction a été exécutée correctement.
 *         \li \ref K_MK_ERROR_PARAM : la fonction n'a pas été exécutée car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_factory_setVisibility ( T_mkFactory* p_factory, uint32_t p_visibility );

/**
 * @fn T_mkCode mk_factory_setActivity ( T_mkFactory* p_factory, uint32_t p_activity );
 * @brief Cette fonction configure l'activité de tous les containers présents dans une factory.
 *
 * @param[in,out] p_factory   Ce paramètre contient l'adresse d'une factory de type \ref T_mkFactory.
 * @param[in]     p_activity  Ce paramètre contient l'activité des champs présents dans la factory.
 *                            Il peut prendre les valeurs \ref K_MK_FIELD_ACTIF ou \ref K_MK_FIELD_INACTIF.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction a été exécutée correctement.
 *         \li \ref K_MK_ERROR_PARAM : la fonction n'a pas été exécutée car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_factory_setActivity ( T_mkFactory* p_factory, uint32_t p_activity );

/**
 *
 */

#endif


