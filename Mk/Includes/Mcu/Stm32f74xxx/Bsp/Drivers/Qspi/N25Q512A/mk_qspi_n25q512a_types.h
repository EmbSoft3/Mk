/**
*
* @copyright Copyright (C) 2020-2026 RENARD Mathieu. All rights reserved.
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
* @file mk_qspi_n25q512a_types.h
* @brief Déclaration des types dédiés à la mémoire QSPI N25Q512A.
* @date 5 mai 2020
*
* @todo Ecrire la documentation.
*
*/

#ifndef MK_MICRON_N25Q512A_TYPES_H
#define MK_MICRON_N25Q512A_TYPES_H

/**
 * @struct T_mkN25Q512AStatusField
 * @brief Déclaration de la structure T_mkN25Q512AStatusField.
 *
 */

typedef struct T_mkN25Q512AStatusField T_mkN25Q512AStatusField;
struct T_mkN25Q512AStatusField
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

typedef union T_mkN25Q512AStatusRegister T_mkN25Q512AStatusRegister;
union T_mkN25Q512AStatusRegister
{
   T_mkN25Q512AStatusField field;
   uint32_t word;
};

/**
 *
 */

/**
 * @struct T_mkN25Q512ANonVolatileConfigurationField
 * @brief Déclaration de la structure T_mkN25Q512ANonVolatileConfigurationField.
 *
 */

typedef struct T_mkN25Q512ANonVolatileConfigurationField T_mkN25Q512ANonVolatileConfigurationField;
struct T_mkN25Q512ANonVolatileConfigurationField
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
 * @struct T_mkN25Q512ANonVolatileConfigurationRegister
 * @brief Déclaration de la structure T_mkN25Q512ANonVolatileConfigurationRegister.
 * @note Ce registre est de type 'Non Volatile'.
 *
 */

typedef union T_mkN25Q512ANonVolatileConfigurationRegister T_mkN25Q512ANonVolatileConfigurationRegister;
union T_mkN25Q512ANonVolatileConfigurationRegister
{
   T_mkN25Q512ANonVolatileConfigurationField field;
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

typedef struct T_mkN25Q512AConfigurationField T_mkN25Q512AConfigurationField;
struct T_mkN25Q512AConfigurationField
{
   unsigned_t wrap:2;
   unsigned_t reserved:1;
   unsigned_t xip:1;
   unsigned_t dummyClockCycle:4;
   unsigned_t padding:24;
};

/**
 * @struct T_mkN25Q512AConfigurationRegister
 * @brief Déclaration de la structure T_mkN25Q512AConfigurationRegister.
 * @note Ce registre est de type 'Volatile'.
 *
 */

typedef union T_mkN25Q512AConfigurationRegister T_mkN25Q512AConfigurationRegister;
union T_mkN25Q512AConfigurationRegister
{
   T_mkN25Q512AConfigurationField field;
   uint32_t word;
};

/**
 *
 */

/**
 * @struct T_mkN25Q512AEnhancedConfigurationField
 * @brief Déclaration de la structure T_mkN25Q512AEnhancedConfigurationField.
 *
 */

typedef struct T_mkN25Q512AEnhancedConfigurationField T_mkN25Q512AEnhancedConfigurationField;
struct T_mkN25Q512AEnhancedConfigurationField
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
 * @struct T_mkN25Q512AEnhancedConfigurationRegister
 * @brief Déclaration de la structure T_mkN25Q512AEnhancedConfigurationRegister.
 * @note Ce registre est de type 'Volatile'.
 *
 */

typedef union T_mkN25Q512AEnhancedConfigurationRegister T_mkN25Q512AEnhancedConfigurationRegister;
union T_mkN25Q512AEnhancedConfigurationRegister
{
   T_mkN25Q512AEnhancedConfigurationField field;
   uint32_t word;
};

/**
 *
 */

#endif

