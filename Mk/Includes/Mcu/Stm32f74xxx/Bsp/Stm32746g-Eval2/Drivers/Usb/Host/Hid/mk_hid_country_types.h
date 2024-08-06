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
* @file mk_hid_country_types.h
* @brief Déclaration des constantes dédiées aux localisation des périphériques HID.
* @date 19 déc. 2019
*
*/

#ifndef MK_HID_COUNTRY_TYPES_H
#define MK_HID_COUNTRY_TYPES_H

/**
 * @enum T_mkHIDCountryCode
 * @brief Déclaration de l'énumération T_mkHIDCountryCode.
 *
 */

typedef enum T_mkHIDCountryCode
{
   K_MK_HID_COUNTRY_NOT_SUPPORTED = 0,          /*!< Définition de l'identifiant de la langue 'NOT_SUPPORTED' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_ARABIC = 1,                 /*!< Définition de l'identifiant de la langue 'ARABIC' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_BELGIAN = 2,                /*!< Définition de l'identifiant de la langue 'BELGIAN' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_CANADIAN_BILINGUAL = 3,     /*!< Définition de l'identifiant de la langue 'CANADIAN_BILINGUAL' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_CANADIAN_FRENCH = 4,        /*!< Définition de l'identifiant de la langue 'CANADIAN_FRENCH' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_CZECH_REPUBLIC = 5,         /*!< Définition de l'identifiant de la langue 'CZECH_REPUBLIC' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_DANISH = 6,                 /*!< Définition de l'identifiant de la langue 'DANISH' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_FINNISH = 7,                /*!< Définition de l'identifiant de la langue 'FINNISH' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_FRENCH = 8,                 /*!< Définition de l'identifiant de la langue 'FRENCH' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_GERMAN = 9,                 /*!< Définition de l'identifiant de la langue 'GERMAN' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_GREEK = 10,                 /*!< Définition de l'identifiant de la langue 'GREEK' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_HEBREW = 11,                /*!< Définition de l'identifiant de la langue 'HEBREW' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_HUNGARY = 12,               /*!< Définition de l'identifiant de la langue 'HUNGARY' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_INTERNATIONAL_ISO = 13,     /*!< Définition de l'identifiant de la langue 'INTERNATIONAL_ISO' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_ITALIAN = 14,               /*!< Définition de l'identifiant de la langue 'ITALIAN' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_JAPAN = 15,                 /*!< Définition de l'identifiant de la langue 'JAPAN' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_KOREAN = 16,                /*!< Définition de l'identifiant de la langue 'KOREAN' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_LATIN_AMERICAN = 17,        /*!< Définition de l'identifiant de la langue 'LATIN_AMERICAN' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_NETHERLANDS_DUTCH = 18,     /*!< Définition de l'identifiant de la langue 'NETHERLANDS_DUTCH' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_NORWEGIAN = 19,             /*!< Définition de l'identifiant de la langue 'NORWEGIAN' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_PERSIAN = 20,               /*!< Définition de l'identifiant de la langue 'PERSIAN' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_POLAND = 21,                /*!< Définition de l'identifiant de la langue 'POLAND' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_PORTUGUESE = 22,            /*!< Définition de l'identifiant de la langue 'PORTUGUESE' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_RUSSIA = 23,                /*!< Définition de l'identifiant de la langue 'RUSSIA' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_SLOVAKIA = 24,              /*!< Définition de l'identifiant de la langue 'SLOVAKIA' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_SPANISH = 25,               /*!< Définition de l'identifiant de la langue 'SPANISH' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_SWEDISH = 26,               /*!< Définition de l'identifiant de la langue 'SWEDISH' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_SWISS_FRENCH = 27,          /*!< Définition de l'identifiant de la langue 'SWISS_FRENCH' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_SWISS_GERMAN = 28,          /*!< Définition de l'identifiant de la langue 'SWISS_GERMAN' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_SWITZERLAND = 29,           /*!< Définition de l'identifiant de la langue 'SWITZELAND' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_TAIWAN = 30,                /*!< Définition de l'identifiant de la langue 'TAIWAN' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_TURKISH_Q = 31,             /*!< Définition de l'identifiant de la langue 'TURKISH_Q' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_UK = 32,                    /*!< Définition de l'identifiant de la langue 'UK' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_US = 33,                    /*!< Définition de l'identifiant de la langue 'US' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_YUGOSLAVIA = 34,            /*!< Définition de l'identifiant de la langue 'YUGOSLAVIA' selon la spécification HID 1.11. */
   K_MK_HID_COUNTRY_TURKISH_F = 35              /*!< Définition de l'identifiant de la langue 'TURKISH_F' selon la spécification HID 1.11. */
} T_mkHIDCountryCode;


/**
 *
 */

#endif


