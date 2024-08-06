/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_display_request_private.h
* @brief Déclaration des fonctions privées dédiées au module 'Reqest'.
* @date 30 oct. 2022
*
*/

#ifndef MK_DISPLAY_REQUEST_PRIVATE_H
#define MK_DISPLAY_REQUEST_PRIVATE_H

/**
 * @fn T_mkCode mk_display_postRequest ( T_mkDisplayRequest* p_request );
 * @brief Cette fonction envoie une requête au moteur graphique.
 * @param[in] p_request Ce paramètre contient l'adresse d'une requête de type \ref T_mkDisplayRequest configurée.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la requête a été envoyée à la tâche de gestion.
 *         \li \ref K_MK_ERROR_PARAM   : la requête n'a pas été envoyée à la tâche de gestion car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête n'a pas été envoyée à la tâche de gestion car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la requête n'a pas été envoyée à la tâche de gestion car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la requête n'a pas été envoyée à la tâche de gestion car une tâche non privilégiée ne possède pas suffisamment de droits.
 *                                       une ressource protégée.
 *
 */

T_mkCode mk_display_postRequest ( T_mkDisplayRequest* p_request );

/**
 *
 */

#endif

