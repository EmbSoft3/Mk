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
* @file mk_hcd_request_private.h
* @brief Déclaration des fonctions privées dédiées aux requêtes USB.
* @date 10 oct. 2019
*
*/

#ifndef MK_HCD_REQUEST_PRIVATE_H
#define MK_HCD_REQUEST_PRIVATE_H

/**
 * @fn T_mkCode mk_hcd_createRequest ( T_mkHCDRequest* p_request, T_mkHCDRequestCode p_code, uint8_t p_requestType, uint16_t p_value, uint16_t p_index, uint16_t p_length );
 * @brief Cette fonction configure une requête USB de type \ref T_mkHCDRequest.
 *
 * @param[out] p_request     Ce paramètre contient l'adresse d'une structure de type \ref T_mkHCDRequest.
 * @param[in]  p_code        Ce paramètre contient l'identifiant de la requête (\ref T_mkHCDRequestCode).
 * @param[in]  p_requestType Ce paramètre contient les attributs de la requête (\ref T_mkHCDEnumRequestDirection, \ref T_mkHCDEnumRequestType, et \ref T_mkHCDEnumRequestRecipient).
 * @param[in]  p_value       Ce paramètre contient la valeur de la requête à configurer.
 * @param[in]  p_index       Ce paramètre contient l'index de la requête à configurer.
 * @param[in]  p_length      Ce paramètre contient la taille de la requête [en octets].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la requête a été configurée.
 *         \li \ref K_MK_ERROR_PARAM : la requête n'a pas été configurée car au moins un paramètre est invalide.
 *
 * @note La spécification USB2.0 peut être utilisée pour configurer la requête correctement.
 *
 */

T_mkCode mk_hcd_createRequest ( T_mkHCDRequest* p_request, T_mkHCDRequestCode p_code, uint8_t p_requestType, uint16_t p_value, uint16_t p_index, uint16_t p_length );


/**
 *
 */

#endif


