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
* @file mk_hid_keyboard_lookupTableByType.c
* @brief Définition de la fonction mk_hid_keyboard_lookupTableByType.
*        La disposition des claviers peut être retrouvée à partir du lien suivant :
*        https://fr.wikipedia.org/wiki/Disposition_des_touches_d%27un_clavier_de_saisie
* @date 23 déc. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @fn uint32_t g_mkHidFrExtendedAzertyLookupTable;
 * @brief Déclaration de la table de correspondance des caractères AZERTY(FR) étendue.
 *
 */

const uint32_t g_mkHidFrExtendedAzertyLookupTable [ 256 ] =
{
      /* 0x0000 */ ( uint32_t ) 0x00,
      /* 0x0001 */ ( uint32_t ) 'q',
      /* 0x0002 */ ( uint32_t ) 'b',
      /* 0x0003 */ ( uint32_t ) 'c',
      /* 0x0004 */ ( uint32_t ) 'd',
      /* 0x0005 */ ( uint32_t ) 'e',
      /* 0x0006 */ ( uint32_t ) 'f',
      /* 0x0007 */ ( uint32_t ) 'g',
      /* 0x0008 */ ( uint32_t ) 'h',
      /* 0x0009 */ ( uint32_t ) 'i',
      /* 0x000A */ ( uint32_t ) 'j',
      /* 0x000B */ ( uint32_t ) 'k',
      /* 0x000C */ ( uint32_t ) 'l',
      /* 0x000D */ ( uint32_t ) ',',
      /* 0x000E */ ( uint32_t ) 'n',
      /* 0x000F */ ( uint32_t ) 'o',

      /* 0x0010 */ ( uint32_t ) 'p',
      /* 0x0011 */ ( uint32_t ) 'a',
      /* 0x0012 */ ( uint32_t ) 'r',
      /* 0x0013 */ ( uint32_t ) 's',
      /* 0x0014 */ ( uint32_t ) 't',
      /* 0x0015 */ ( uint32_t ) 'u',
      /* 0x0016 */ ( uint32_t ) 'v',
      /* 0x0017 */ ( uint32_t ) 'z',
      /* 0x0018 */ ( uint32_t ) 'x',
      /* 0x0019 */ ( uint32_t ) 'y',
      /* 0x001A */ ( uint32_t ) 'w',
      /* 0x001B */ ( uint32_t ) '&',
      /* 0x001C */ ( uint32_t ) 0x00E9, /* 'é' */
      /* 0x001D */ ( uint32_t ) '"',
      /* 0x001E */ ( uint32_t ) '\'',
      /* 0x001F */ ( uint32_t ) '(',

      /* 0x0020 */ ( uint32_t ) '-',
      /* 0x0021 */ ( uint32_t ) 0x00E8, /* 'è' */
      /* 0x0022 */ ( uint32_t ) '_',
      /* 0x0023 */ ( uint32_t ) 0x00E7, /* 'ç' */
      /* 0x0024 */ ( uint32_t ) 0x00E0, /* 'à' */
      /* 0x0025 */ ( uint32_t ) ' ',
      /* 0x0026 */ ( uint32_t ) ')',
      /* 0x0027 */ ( uint32_t ) '=',
      /* 0x0028 */ ( uint32_t ) 0x0302, /* '^' */
      /* 0x0029 */ ( uint32_t ) '$',
      /* 0x002A */ ( uint32_t ) '*',
      /* 0x002B */ ( uint32_t ) 'm',
      /* 0x002C */ ( uint32_t ) 0x00F9, /* ù */
      /* 0x002D */ ( uint32_t ) 0x00B2, /* ² */
      /* 0x002E */ ( uint32_t ) ';',
      /* 0x002F */ ( uint32_t ) ':',

      /* 0x0030 */ ( uint32_t ) '!',
      /* 0x0031 */ ( uint32_t ) '/',
      /* 0x0032 */ ( uint32_t ) '*',
      /* 0x0033 */ ( uint32_t ) '-',
      /* 0x0034 */ ( uint32_t ) '+',
      /* 0x0035 */ ( uint32_t ) '1',
      /* 0x0036 */ ( uint32_t ) '2',
      /* 0x0037 */ ( uint32_t ) '3',
      /* 0x0038 */ ( uint32_t ) '4',
      /* 0x0039 */ ( uint32_t ) '5',
      /* 0x003A */ ( uint32_t ) '6',
      /* 0x003B */ ( uint32_t ) '7',
      /* 0x003C */ ( uint32_t ) '8',
      /* 0x003D */ ( uint32_t ) '9',
      /* 0x003E */ ( uint32_t ) '0',
      /* 0x003F */ ( uint32_t ) '.',

      /* 0x0040 */ ( uint32_t ) '<',
      /* 0x0041 */ ( uint32_t ) ',',
      /* 0x0042 */ ( uint32_t ) '=',
      /* 0x0043 */ ( uint32_t ) '(',
      /* 0x0044 */ ( uint32_t ) ')',
      /* 0x0045 */ ( uint32_t ) '[',
      /* 0x0046 */ ( uint32_t ) ']',
      /* 0x0047 */ ( uint32_t ) 'A',
      /* 0x0048 */ ( uint32_t ) 'B',
      /* 0x0049 */ ( uint32_t ) 'C',
      /* 0x004A */ ( uint32_t ) 'D',
      /* 0x004B */ ( uint32_t ) 'E',
      /* 0x004C */ ( uint32_t ) 'F',
      /* 0x004D */ ( uint32_t ) 0x22BB, /* '⊻ ' */
      /* 0x004E */ ( uint32_t ) '^',
      /* 0x004F */ ( uint32_t ) '&',

      /* 0x0050 */ ( uint32_t ) '<',
      /* 0x0051 */ ( uint32_t ) '>',
      /* 0x0052 */ ( uint32_t ) 0x2227, /* '∧' */
      /* 0x0053 */ ( uint32_t ) 0x00,
      /* 0x0054 */ ( uint32_t ) 0x2228, /* '∨ ' */
      /* 0x0055 */ ( uint32_t ) 0x00,
      /* 0x0056 */ ( uint32_t ) ':',
      /* 0x0057 */ ( uint32_t ) '#',
      /* 0x0058 */ ( uint32_t ) ' ',
      /* 0x0059 */ ( uint32_t ) '@',
      /* 0x005A */ ( uint32_t ) '!',
      /* 0x005B */ ( uint32_t ) 0x00B1, /* '±' */
      /* 0x005C */ ( uint32_t ) 'Q',
      /* 0x005D */ ( uint32_t ) 'B',
      /* 0x005E */ ( uint32_t ) 'C',
      /* 0x005F */ ( uint32_t ) 'D',

      /* 0x0060 */ ( uint32_t ) 'E',
      /* 0x0061 */ ( uint32_t ) 'F',
      /* 0x0062 */ ( uint32_t ) 'G',
      /* 0x0063 */ ( uint32_t ) 'H',
      /* 0x0064 */ ( uint32_t ) 'I',
      /* 0x0065 */ ( uint32_t ) 'J',
      /* 0x0066 */ ( uint32_t ) 'K',
      /* 0x0067 */ ( uint32_t ) 'L',
      /* 0x0068 */ ( uint32_t ) '?',
      /* 0x0069 */ ( uint32_t ) 'N',
      /* 0x006A */ ( uint32_t ) 'O',
      /* 0x006B */ ( uint32_t ) 'P',
      /* 0x006C */ ( uint32_t ) 'A',
      /* 0x006D */ ( uint32_t ) 'R',
      /* 0x006E */ ( uint32_t ) 'S',
      /* 0x006F */ ( uint32_t ) 'T',

      /* 0x0070 */ ( uint32_t ) 'U',
      /* 0x0071 */ ( uint32_t ) 'V',
      /* 0x0072 */ ( uint32_t ) 'Z',
      /* 0x0073 */ ( uint32_t ) 'X',
      /* 0x0074 */ ( uint32_t ) 'Y',
      /* 0x0075 */ ( uint32_t ) 'W',
      /* 0x0076 */ ( uint32_t ) '1',
      /* 0x0077 */ ( uint32_t ) '2',
      /* 0x0078 */ ( uint32_t ) '3',
      /* 0x0079 */ ( uint32_t ) '4',
      /* 0x007A */ ( uint32_t ) '5',
      /* 0x007B */ ( uint32_t ) '6',
      /* 0x007C */ ( uint32_t ) '7',
      /* 0x007D */ ( uint32_t ) '8',
      /* 0x007E */ ( uint32_t ) '9',
      /* 0x007F */ ( uint32_t ) '0',

      /* 0x0080 */ ( uint32_t ) 0x00B0, /* '°' */
      /* 0x0081 */ ( uint32_t ) '+',
      /* 0x0082 */ ( uint32_t ) 0x0308, /* '¨' */
      /* 0x0083 */ ( uint32_t ) 0x00A3, /* '£' */
      /* 0x0084 */ ( uint32_t ) 0x00B5, /* 'µ' */
      /* 0x0085 */ ( uint32_t ) 'M',
      /* 0x0086 */ ( uint32_t ) '%',
      /* 0x0087 */ ( uint32_t ) '.',
      /* 0x0088 */ ( uint32_t ) '/',
      /* 0x0089 */ ( uint32_t ) 0x00A7, /* '§' */
      /* 0x008A */ ( uint32_t ) '>',
      /* 0x008B */ ( uint32_t ) ',',
      /* 0x008C */ ( uint32_t ) '=',
      /* 0x008D */ ( uint32_t ) 0x00E4, /* 'ä' */
      /* 0x008E */ ( uint32_t ) 0x2193, /* '↓' */
      /* 0x008F */ ( uint32_t ) 0x00A9, /* '©' */

      /* 0x0090 */ ( uint32_t ) 0x00EB, /* 'ë' */
      /* 0x0091 */ ( uint32_t ) 0x20AC, /* '€' */
      /* 0x0092 */ ( uint32_t ) 0x02BB, /* '‘' */
      /* 0x0093 */ ( uint32_t ) 0x02BC, /* '’' */
      /* 0x0094 */ ( uint32_t ) 0x00F0, /* 'ð' */
      /* 0x0095 */ ( uint32_t ) 0x00EE, /* 'î' */
      /* 0x0096 */ ( uint32_t ) 0x00FC, /* 'ü' */
      /* 0x0097 */ ( uint32_t ) 0x00EF, /* 'ï' */
      /* 0x0098 */ ( uint32_t ) 0x0140, /* 'ŀ' */
      /* 0x0099 */ ( uint32_t ) 0x00BF, /* '¿' */
      /* 0x009A */ ( uint32_t ) 0x00AC, /* '¬' */
      /* 0x009B */ ( uint32_t ) 0x0153, /* 'œ' */
      /* 0x009C */ ( uint32_t ) 0x00F4, /* 'ô' */
      /* 0x009D */ ( uint32_t ) 0x00E6, /* 'æ' */
      /* 0x009E */ ( uint32_t ) 0x00EA, /* 'ê' */
      /* 0x009F */ ( uint32_t ) 0x00DF, /* 'ß' */

      /* 0x00A0 */ ( uint32_t ) 0x00FE, /* 'þ' */
      /* 0x00A1 */ ( uint32_t ) 0x00FB, /* 'û' */
      /* 0x00A2 */ ( uint32_t ) 0x202F, /* ' ' */
      /* 0x00A3 */ ( uint32_t ) 0x00E2, /* 'â' */
      /* 0x00A4 */ ( uint32_t ) 0x00BB, /* '»' */
      /* 0x00A5 */ ( uint32_t ) 0x00FF, /* 'ÿ' */
      /* 0x00A6 */ ( uint32_t ) 0x00AB, /* '«' */
      /* 0x00A7 */ ( uint32_t ) 0x030C, /* '˅' */
      /* 0x00A8 */ ( uint32_t ) '~',
      /* 0x00A9 */ ( uint32_t ) '#',
      /* 0x00AA */ ( uint32_t ) '{',
      /* 0x00AB */ ( uint32_t ) '[',
      /* 0x00AC */ ( uint32_t ) '|',
      /* 0x00AD */ ( uint32_t ) '`',
      /* 0x00AE */ ( uint32_t ) '\\',
      /* 0x00AF */ ( uint32_t ) '^',

      /* 0x00B0 */ ( uint32_t ) '@',
      /* 0x00B1 */ ( uint32_t ) 0x00A0, /* ' ' */
      /* 0x00B2 */ ( uint32_t ) ']',
      /* 0x00B3 */ ( uint32_t ) '}',
      /* 0x00B4 */ ( uint32_t ) 0x0303, /* '~' */
      /* 0x00B5 */ ( uint32_t ) 0x00F8, /* 'ø' */
      /* 0x00B6 */ ( uint32_t ) 0x0300, /* 'ˋ' */
      /* 0x00B7 */ ( uint32_t ) 0x00F6, /* 'ö' */
      /* 0x00B8 */ ( uint32_t ) 0x0301, /* 'ˊ' */
      /* 0x00B9 */ ( uint32_t ) 0x00B9, /* '¹' */
      /* 0x00BA */ ( uint32_t ) 0x00D7, /* '×' */
      /* 0x00BB */ ( uint32_t ) 0x00F7, /* '÷' */
      /* 0x00BC */ ( uint32_t ) 0x00A1, /* '¡' */
      /* 0x00BD */ ( uint32_t ) 0x2264, /* '≤' */
      /* 0x00BE */ ( uint32_t ) ',',
      /* 0x00BF */ ( uint32_t ) '=',

      /* 0x00C0 */ ( uint32_t ) 0x00C4, /* 'Ä' */
      /* 0x00C1 */ ( uint32_t ) 0x2191, /* '↑' */
      /* 0x00C2 */ ( uint32_t ) 0x00AE, /* '®' */
      /* 0x00C3 */ ( uint32_t ) 0x00CB, /* 'Ë' */
      /* 0x00C4 */ ( uint32_t ) 0x00A2, /* '¢' */
      /* 0x00C5 */ ( uint32_t ) 0x201A, /* '‚' */
      /* 0x00C6 */ ( uint32_t ) 0x00A5, /* '¥' */
      /* 0x00C7 */ ( uint32_t ) 0x00D0, /* 'Ð' */
      /* 0x00C8 */ ( uint32_t ) 0x00CE, /* 'Î' */
      /* 0x00C9 */ ( uint32_t ) 0x00DC, /* 'Ü' */
      /* 0x00CA */ ( uint32_t ) 0x00CF, /* 'Ï' */
      /* 0x00CB */ ( uint32_t ) 0x013F, /* 'Ŀ' */
      /* 0x00CC */ ( uint32_t ) 0x2026, /* '…' */
      /* 0x00CD */ ( uint32_t ) 0x2192, /* '→' */
      /* 0x00CE */ ( uint32_t ) 0x0152, /* 'Œ' */
      /* 0x00CF */ ( uint32_t ) 0x00D4, /* 'Ô' */

      /* 0x00D0 */ ( uint32_t ) 0x00C6, /* 'Æ' */
      /* 0x00D1 */ ( uint32_t ) 0x00CA, /* 'Ê' */
      /* 0x00D2 */ ( uint32_t ) 0x201E, /* '„' */
      /* 0x00D3 */ ( uint32_t ) 0x00DE, /* 'Þ' */
      /* 0x00D4 */ ( uint32_t ) 0x00DB, /* 'Û' */
      /* 0x00D5 */ ( uint32_t ) 0x2190, /* '←' */
      /* 0x00D6 */ ( uint32_t ) 0x00C2, /* 'Â' */
      /* 0x00D7 */ ( uint32_t ) 0x201D, /* '”' */
      /* 0x00D8 */ ( uint32_t ) 0x0178, /* 'Ÿ' */
      /* 0x00D9 */ ( uint32_t ) 0x201C, /* '“' */
      /* 0x00DA */ ( uint32_t ) 0x0328, /* '¸' */
      /* 0x00DB */ ( uint32_t ) 0x00C9, /* 'É' */
      /* 0x00DC */ ( uint32_t ) 0x0306, /* '˘' */
      /* 0x00DD */ ( uint32_t ) 0x2014, /* '—' */
      /* 0x00DE */ ( uint32_t ) 0x2013, /* '–' */
      /* 0x00DF */ ( uint32_t ) '-',

      /* 0x00E0 */ ( uint32_t ) 0x00C8, /* 'È' */
      /* 0x00E1 */ ( uint32_t ) 0x2122, /* '™' */
      /* 0x00E2 */ ( uint32_t ) 0x00C7, /* 'Ç' */
      /* 0x00E3 */ ( uint32_t ) 0x00C0, /* 'À' */
      /* 0x00E4 */ ( uint32_t ) 0x00A0, /* ' ' */
      /* 0x00E5 */ ( uint32_t ) 0x2260, /* '≠' */
      /* 0x00E6 */ ( uint32_t ) 0x00B1, /* '±' */
      /* 0x00E7 */ ( uint32_t ) 0x030A, /* '°' */
      /* 0x00E8 */ ( uint32_t ) 0x00D8, /* 'Ø' */
      /* 0x00E9 */ ( uint32_t ) 0x0304, /* 'ˉ' */
      /* 0x00EA */ ( uint32_t ) 0x00D6, /* 'Ö' */
      /* 0x00EB */ ( uint32_t ) 0x00D9, /* 'Ù' */
      /* 0x00EC */ ( uint32_t ) 0x0327, /* '¸' */
      /* 0x00ED */ ( uint32_t ) 0x00B7, /* '·' */
      /* 0x00EE */ ( uint32_t ) 0x2215, /* '∕' */
      /* 0x00EF */ ( uint32_t ) 0x2212, /* '−' */

      /* 0x00F0 */ ( uint32_t ) 0x2265, /* '≥' */
      /* 0x00F1 */ ( uint32_t ) ',',
      /* 0x00F2 */ ( uint32_t ) '=',
      /* 0x00F3 */ ( uint32_t ) 0x00,
      /* 0x00F4 */ ( uint32_t ) 0x00,
      /* 0x00F5 */ ( uint32_t ) 0x00,
      /* 0x00F6 */ ( uint32_t ) 0x00B3, /* '³' */
      /* 0x00F7 */ ( uint32_t ) 0x00,
      /* 0x00F8 */ ( uint32_t ) 0x00,
      /* 0x00F9 */ ( uint32_t ) 0x00,
      /* 0x00FA */ ( uint32_t ) 0x00,
      /* 0x00FB */ ( uint32_t ) 0x00,
      /* 0x00FC */ ( uint32_t ) 0x00,
      /* 0x00FD */ ( uint32_t ) 0x00,
      /* 0x00FE */ ( uint32_t ) 0x00,
      /* 0x00FF */ ( uint32_t ) 0x00,
};




