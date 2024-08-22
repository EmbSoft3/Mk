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
* @file mk_micron_n25q512a_types.h
* @brief Déclaration des types dédiés à la mémoire MICRON N25Q512A.
* @date 5 mai 2020
*
* @todo Ecrire la documentation.
*
*/

#ifndef MK_MICRON_N25Q512A_H
#define MK_MICRON_N25Q512A_H

/**
 * @struct T_MicronN25Q512A_StatusField
 * @brief Déclaration de la structure T_MicronN25Q512A_StatusField.
 *
 */

typedef struct T_MicronN25Q512A_StatusField T_MicronN25Q512A_StatusField;
struct T_MicronN25Q512A_StatusField
{
   unsigned_t writeInProgress:1;
   unsigned_t writeEnableLatch:1;
   unsigned_t blockProtectLSB:3;
   unsigned_t topBottom:1;
   unsigned_t blockProtectMSB:1;
   unsigned_t statWriteEnableLatch:1;
   unsigned_t padding:24;
};

/**
 * @struct T_MicronN25Q512AStatusRegister
 * @brief Déclaration de la structure T_MicronN25Q512AStatusRegister.
 *
 */

typedef union T_MicronN25Q512A_StatusRegister T_MicronN25Q512A_StatusRegister;
union T_MicronN25Q512A_StatusRegister
{
   T_MicronN25Q512A_StatusField field;
   uint32_t word;
};

/**
 *
 */

/**
 * @struct T_MicronN25Q512A_NVConfigurationField
 * @brief Déclaration de la structure T_MicronN25Q512A_NVConfigurationField.
 *
 */

typedef struct T_MicronN25Q512A_NVConfigurationField T_MicronN25Q512A_NVConfigurationField;
struct T_MicronN25Q512A_NVConfigurationField
{
   unsigned_t addressBytes:1;
   unsigned_t segmentSelect:1;
   unsigned_t dualIO:1;
   unsigned_t quadIO:1;
   unsigned_t resetHold:1;
   unsigned_t reserved:1;
   unsigned_t outputDriverStrength:3;
   unsigned_t xipModeAtPor:3;
   unsigned_t dummyClockCycle:4;
   unsigned_t padding:16;
};

/**
 * @struct T_MicronN25Q512A_NVConfigurationRegister
 * @brief Déclaration de la structure T_MicronN25Q512A_NVConfigurationRegister.
 * @note Ce registre est de type 'Non Volatile'.
 *
 */

typedef union T_MicronN25Q512A_NVConfigurationRegister T_MicronN25Q512A_NVConfigurationRegister;
union T_MicronN25Q512A_NVConfigurationRegister
{
   T_MicronN25Q512A_NVConfigurationField field;
   uint32_t word;
};

/**
 *
 */

/**
 * @struct T_MicronN25Q512ANVConfigurationField
 * @brief Déclaration de la structure T_MicronN25Q512ANVConfigurationField.
 *
 */

typedef struct T_MicronN25Q512A_ConfigurationField T_MicronN25Q512A_ConfigurationField;
struct T_MicronN25Q512A_ConfigurationField
{
   unsigned_t wrap:2;
   unsigned_t reserved:1;
   unsigned_t xip:1;
   unsigned_t dummyClockCycle:4;
   unsigned_t padding:24;
};

/**
 * @struct T_MicronN25Q512A_ConfigurationRegister
 * @brief Déclaration de la structure T_MicronN25Q512A_ConfigurationRegister.
 * @note Ce registre est de type 'Volatile'.
 *
 */

typedef union T_MicronN25Q512A_ConfigurationRegister T_MicronN25Q512A_ConfigurationRegister;
union T_MicronN25Q512A_ConfigurationRegister
{
   T_MicronN25Q512A_ConfigurationField field;
   uint32_t word;
};

/**
 *
 */

/**
 * @struct T_MicronN25Q512ANVConfigurationField
 * @brief Déclaration de la structure T_MicronN25Q512ANVConfigurationField.
 *
 */

typedef struct T_MicronN25Q512A_EnhancedConfigurationField T_MicronN25Q512A_EnhancedConfigurationField;
struct T_MicronN25Q512A_EnhancedConfigurationField
{
   unsigned_t outputDriverStrength:3;
   unsigned_t vppAccelerator:1;
   unsigned_t resetHold:1;
   unsigned_t reserved:1;
   unsigned_t dualIO:1;
   unsigned_t quadIO:1;
   unsigned_t padding:24;
};

/**
 * @struct T_MicronN25Q512A_EnhancedConfigurationRegister
 * @brief Déclaration de la structure T_MicronN25Q512A_EnhancedConfigurationRegister.
 * @note Ce registre est de type 'Volatile'.
 *
 */

typedef union T_MicronN25Q512A_EnhancedConfigurationRegister T_MicronN25Q512A_EnhancedConfigurationRegister;
union T_MicronN25Q512A_EnhancedConfigurationRegister
{
   T_MicronN25Q512A_EnhancedConfigurationField field;
   uint32_t word;
};

/**
 *
 */

#endif

