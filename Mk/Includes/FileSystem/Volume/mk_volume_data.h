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
* @file mk_volume_data.h
* @brief Déclaration des données dédiées aux partitions.
* @date 16 juin 2020
*
*/

#ifndef MK_VOLUME_DATA_H
#define MK_VOLUME_DATA_H

/**
 * @fn T_mkVolumePool g_mkVolumePool;
 * @brief Déclaration du gestionnaire d'allocation dynamique des partition de type \ref T_mkVolume.
 *
 */

extern T_mkVolumePool g_mkVolumePool;

/**
 * @fn T_mkVolume* g_mkSystemVolume;
 * @brief Déclaration d'un pointeur contenant l'adresse de la partition système.
 *
 */

extern T_mkVolume* volatile g_mkSystemVolume;

/**
 *
 */

#endif

