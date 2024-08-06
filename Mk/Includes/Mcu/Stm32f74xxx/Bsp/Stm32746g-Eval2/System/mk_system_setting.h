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
* @file mk_system_setting.h
* @brief Déclaration des fonctions système dédiées au périphérique SYSCFG.
* @date 26 févr. 2019
*
*/

#ifndef MK_SYSTEM_SETTING_H
#define MK_SYSTEM_SETTING_H

/**
 * @fn T_sysCode mk_system_setting_init ( void );
 * @brief Cette fonction configure le matériel de la cible (SYSCFG). Elle active la compension de cellules
 *        pour les broches hautes vélocités ainsi que le mécanisme de  permutation de 'bank' du FMC.
 *
 * @return Cette fonction retourne la valeur \ref K_SYS_OK si la fonction a été exécutée sans erreur, sinon
 *         la valeur \ref K_SYS_ERROR_CELL_COMPENSATION si une erreur s'est produite durant l'activation de
 *         la compensation de cellules.
 *
 */

T_sysCode mk_system_setting_init ( void );

/**
 *
 */

#endif
