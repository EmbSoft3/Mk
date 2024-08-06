/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_msc_request_types.h
* @brief Déclaration des types dédiés aux requêtes des périphériques de stockage.
* @date 18 mai 2020
*
*/

#ifndef MK_MSC_REQUEST_TYPES_H
#define MK_MSC_REQUEST_TYPES_H

/**
 * @struct T_mkStorageBulkOnlyRequestCode
 * @brief Déclaration de la structure T_mkStorageBulkOnlyRequestCode.
 *
 */

typedef enum T_mkMSBulkOnlyRequestCode
{
   K_MK_MSC_BULK_ONLY_GET_MAX_LUN = 0xFE,             /*!< Définition du code de la requête GET_MAX_LUN du protocole "BulkOnly". */
   K_MK_MSC_BULK_ONLY_RESET = 0xFF                    /*!< Définition du code de la requête RESET du protocole "BulkOnly". */
} T_mkMSBulkOnlyRequestCode;

/**
 *
 */

#endif

