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
* @file mk_termio_private.h
* @brief Déclaration des fonctions privées dédiées aux terminaux d'entrées-sorties.
* @date 9 juin 2019
*
*/

#ifndef MK_TERMIO_PRIVATE_H
#define MK_TERMIO_PRIVATE_H

/**
 * @fn void mk_termio_initHandler ( void );
 * @brief Cette fonction initialise le gestionnaire de référencement des terminaux.
 * @return Sans objet.
 *
 */

void mk_termio_initHandler ( void );

/**
 * @fn T_mkCode mk_termio_report ( T_mkCode p_code );
 * @brief Cette fonction transmet un code erreur au superviseur système.
 * @param[in] p_code Ce paramètre contient un code erreur de type \ref T_mkCode.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : le code erreur a correctement été posté.
 *         \li \ref K_MK_ERROR_PARAM   : le code erreur n'a pas été posté car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le code erreur n'a pas été posté car aucun emplaçement mémoire ne s'est libéré dans le timeout imparti.
 *         \li \ref K_MK_ERROR_ISR     : le code erreur n'a pas été posté car la fonction a été exécutée depuis un vecteur d'interruption avec le paramètre p_mkTick différent de zéro.
 *         \li \ref K_MK_ERROR_RIGHT   : le code erreur n'a pas été posté car une tâche de type non privilégié ne peut pas utiliser une messagerie protégée.
 *
 */

T_mkCode mk_termio_report ( T_mkCode p_code );

/**
 *
 */

#endif


