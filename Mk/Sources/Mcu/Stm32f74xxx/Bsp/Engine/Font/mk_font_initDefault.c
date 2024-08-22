/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_font_initDefault.c
* @brief Définition de la fonction mk_font_initDefault.
* @date 2 juil. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_font_initDefaultFixedLength ( void )
{
   /* Configuration des attributs de la police de taille fixe */
   mk_font_init ( &g_mkDisplay.defaultFixedFont.handle );
   mk_font_setHeight ( &g_mkDisplay.defaultFixedFont.handle, K_MK_FONT_DEFAULT_FIXED_HEIGHT );
   mk_font_setNumberOfPixelsBetweenChars ( &g_mkDisplay.defaultFixedFont.handle, 0 );
   mk_font_setNumberOfPixelsBetweenRows ( &g_mkDisplay.defaultFixedFont.handle, K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_ROWS );
   mk_font_setTabulationNumberOfPixels ( &g_mkDisplay.defaultFixedFont.handle, K_MK_FONT_DEFAULT_TABULATION_PIXELS_NUMBER );

   /* Configuration de la page BASIC_LATIN */
   mk_font_setPage ( &g_mkDisplay.defaultFixedFont.page [ 0 ], K_MK_FONT_PAGE_BASIC_LATIN, ( uint32_t ) ( K_MK_FONT_PAGE_LATIN_1_SUPPLEMENT - 1 ),
                     &g_mkFontConsolasFixed11ptBasicLatinPageDescriptor [ 0 ] [ 0 ], g_mkFontConsolasFixed11ptBasicLatinPage );
   mk_font_addPage ( &g_mkDisplay.defaultFixedFont.handle, &g_mkDisplay.defaultFixedFont.page [ 0 ] );

   /* Configuration de la page LATIN_1_SUPPLEMENT */
   mk_font_setPage ( &g_mkDisplay.defaultFixedFont.page [ 1 ], K_MK_FONT_PAGE_LATIN_1_SUPPLEMENT, ( uint32_t ) ( K_MK_FONT_PAGE_LATIN_EXTENDED_A - 1 ),
                     &g_mkFontConsolasFixed11ptLatin1SupplementPageDescriptor [ 0 ] [ 0 ], g_mkFontConsolasFixed11ptLatin1SupplementPage );
   mk_font_addPage ( &g_mkDisplay.defaultFixedFont.handle, &g_mkDisplay.defaultFixedFont.page [ 1 ] );

   /* Configuration de la page LATIN_EXTENDED_A */
   mk_font_setPage ( &g_mkDisplay.defaultFixedFont.page [ 2 ], K_MK_FONT_PAGE_LATIN_EXTENDED_A, ( uint32_t ) ( K_MK_FONT_PAGE_LATIN_EXTENDED_B - 1 ),
                     &g_mkFontConsolasFixed11ptLatinExtendedAPageDescriptor [ 0 ] [ 0 ], g_mkFontConsolasFixed11ptLatinExtendedAPage );
   mk_font_addPage ( &g_mkDisplay.defaultFixedFont.handle, &g_mkDisplay.defaultFixedFont.page [ 2 ] );

   /* Configuration de la page LATIN_EXTENDED_B */
   mk_font_setPage ( &g_mkDisplay.defaultFixedFont.page [ 3 ], K_MK_FONT_PAGE_LATIN_EXTENDED_B, ( uint32_t ) ( K_MK_FONT_PAGE_IPA_EXTENSIONS - 1 ),
                     &g_mkFontConsolasFixed11ptLatinExtendedBPageDescriptor [ 0 ] [ 0 ], g_mkFontConsolasFixed11ptLatinExtendedBPage );
   mk_font_addPage ( &g_mkDisplay.defaultFixedFont.handle, &g_mkDisplay.defaultFixedFont.page [ 3 ] );

   /* Configuration de la page MODIFIER_LETTERS */
   mk_font_setPage ( &g_mkDisplay.defaultFixedFont.page [ 4 ], K_MK_FONT_PAGE_SPACING_MODIFIER_LETTERS, ( uint32_t ) ( K_MK_FONT_PAGE_COMBINING_DIACRITICAL_MARKS - 1 ),
                     &g_mkFontConsolasFixed11ptSpacingModifierLetterPageDescriptor [ 0 ] [ 0 ], g_mkFontConsolasFixed11ptSpacingModifierLetterPage );
   mk_font_addPage ( &g_mkDisplay.defaultFixedFont.handle, &g_mkDisplay.defaultFixedFont.page [ 4 ] );

   /* Configuration de la page COMBINING_DIACRITICAL_MARKS */
   mk_font_setPage ( &g_mkDisplay.defaultFixedFont.page [ 5 ], K_MK_FONT_PAGE_COMBINING_DIACRITICAL_MARKS, ( uint32_t ) ( K_MK_FONT_PAGE_GREEK_AND_COPTIC - 1 ),
                     &g_mkFontConsolasFixed11ptCombiningDiacriticalMarksPageDescriptor [ 0 ] [ 0 ], g_mkFontConsolasFixed11ptCombiningDiacriticalMarksPage );
   mk_font_addPage ( &g_mkDisplay.defaultFixedFont.handle, &g_mkDisplay.defaultFixedFont.page [ 5 ] );

   /* Configuration de la page GENERAL_PUNCTUATION */
   mk_font_setPage ( &g_mkDisplay.defaultFixedFont.page [ 6 ], K_MK_FONT_PAGE_GENERAL_PUNCTUATION, ( uint32_t ) ( K_MK_FONT_PAGE_SUPERSCRIPTS_AND_SUBSCRIPTS - 1 ),
                     &g_mkFontConsolasFixed11ptGeneralPonctuationPageDescriptor [ 0 ] [ 0 ], g_mkFontConsolasFixed11ptGeneralPonctuationPage );
   mk_font_addPage ( &g_mkDisplay.defaultFixedFont.handle, &g_mkDisplay.defaultFixedFont.page [ 6 ] );

   /* Configuration de la page CURRENCY_SYMBOLS */
   mk_font_setPage ( &g_mkDisplay.defaultFixedFont.page [ 7 ], K_MK_FONT_PAGE_CURRENCY_SYMBOLS, ( uint32_t ) ( K_MK_FONT_PAGE_COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS - 1 ),
                     &g_mkFontConsolasFixed11ptCurrencySymbolPageDescriptor [ 0 ] [ 0 ], g_mkFontConsolasFixed11ptCurrencySymbolPage );
   mk_font_addPage ( &g_mkDisplay.defaultFixedFont.handle, &g_mkDisplay.defaultFixedFont.page [ 7 ] );

   /* Configuration de la page ARROWS */
   mk_font_setPage ( &g_mkDisplay.defaultFixedFont.page [ 8 ], K_MK_FONT_PAGE_ARROWS, ( uint32_t ) ( K_MK_FONT_PAGE_MATHEMATICAL_OPERATORS - 1 ),
                     &g_mkFontConsolasFixed11ptArrowPageDescriptor [ 0 ] [ 0 ], g_mkFontConsolasFixed11ptArrowPage );
   mk_font_addPage ( &g_mkDisplay.defaultFixedFont.handle, &g_mkDisplay.defaultFixedFont.page [ 8 ] );

   /* Configuration de la page MATHEMATICAL_OPERATORS */
   mk_font_setPage ( &g_mkDisplay.defaultFixedFont.page [ 9 ], K_MK_FONT_PAGE_MATHEMATICAL_OPERATORS, ( uint32_t ) ( K_MK_FONT_PAGE_MISCELLANEOUS_TECHNICAL - 1 ),
                     &g_mkFontConsolasFixed11ptMathematicalOperatorPageDescriptor [ 0 ] [ 0 ], g_mkFontConsolasFixed11ptMathematicalOperatorPage );
   mk_font_addPage ( &g_mkDisplay.defaultFixedFont.handle, &g_mkDisplay.defaultFixedFont.page [ 9 ] );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_font_initDefaultVariableLength ( void )
{
   /* Configuration des attributs de la police de taille variable */
   mk_font_init ( &g_mkDisplay.defaultFont.handle );
   mk_font_setHeight ( &g_mkDisplay.defaultFont.handle, K_MK_FONT_DEFAULT_HEIGHT );
   mk_font_setNumberOfPixelsBetweenChars ( &g_mkDisplay.defaultFont.handle, K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_CHARS );
   mk_font_setNumberOfPixelsBetweenRows ( &g_mkDisplay.defaultFont.handle, K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_ROWS );
   mk_font_setTabulationNumberOfPixels ( &g_mkDisplay.defaultFont.handle, K_MK_FONT_DEFAULT_TABULATION_PIXELS_NUMBER );

   /* Configuration de la page BASIC_LATIN */
   mk_font_setPage ( &g_mkDisplay.defaultFont.page [ 0 ], K_MK_FONT_PAGE_BASIC_LATIN, ( uint32_t ) ( K_MK_FONT_PAGE_LATIN_1_SUPPLEMENT - 1 ),
                     &g_mkFontArialUnicodeMS12ptBasicLatinPageDescriptor [ 0 ] [ 0 ], g_mkFontArialUnicodeMS12ptBasicLatinPage );
   mk_font_addPage ( &g_mkDisplay.defaultFont.handle, &g_mkDisplay.defaultFont.page [ 0 ] );

   /* Configuration de la page LATIN_1_SUPPLEMENT */
   mk_font_setPage ( &g_mkDisplay.defaultFont.page [ 1 ], K_MK_FONT_PAGE_LATIN_1_SUPPLEMENT, ( uint32_t ) ( K_MK_FONT_PAGE_LATIN_EXTENDED_A - 1 ),
                     &g_mkFontArialUnicodeMS12ptLatin1SupplementPageDescriptor [ 0 ] [ 0 ], g_mkFontArialUnicodeMS12ptLatin1SupplementPage );
   mk_font_addPage ( &g_mkDisplay.defaultFont.handle, &g_mkDisplay.defaultFont.page [ 1 ] );

   /* Configuration de la page LATIN_EXTENDED_A */
   mk_font_setPage ( &g_mkDisplay.defaultFont.page [ 2 ], K_MK_FONT_PAGE_LATIN_EXTENDED_A, ( uint32_t ) ( K_MK_FONT_PAGE_LATIN_EXTENDED_B - 1 ),
                     &g_mkFontArialUnicodeMS12ptLatinExtendedAPageDescriptor [ 0 ] [ 0 ], g_mkFontArialUnicodeMS12ptLatinExtendedAPage );
   mk_font_addPage ( &g_mkDisplay.defaultFont.handle, &g_mkDisplay.defaultFont.page [ 2 ] );

   /* Configuration de la page LATIN_EXTENDED_B */
   mk_font_setPage ( &g_mkDisplay.defaultFont.page [ 3 ], K_MK_FONT_PAGE_LATIN_EXTENDED_B, ( uint32_t ) ( K_MK_FONT_PAGE_IPA_EXTENSIONS - 1 ),
                     &g_mkFontArialUnicodeMS12ptLatinExtendedBPageDescriptor [ 0 ] [ 0 ], g_mkFontArialUnicodeMS12ptLatinExtendedBPage );
   mk_font_addPage ( &g_mkDisplay.defaultFont.handle, &g_mkDisplay.defaultFont.page [ 3 ] );

   /* Configuration de la page MODIFIER_LETTERS */
   mk_font_setPage ( &g_mkDisplay.defaultFont.page [ 4 ], K_MK_FONT_PAGE_SPACING_MODIFIER_LETTERS, ( uint32_t ) ( K_MK_FONT_PAGE_COMBINING_DIACRITICAL_MARKS - 1 ),
                     &g_mkFontArialUnicodeMS12ptSpacingModifierLetterPageDescriptor [ 0 ] [ 0 ], g_mkFontArialUnicodeMS12ptSpacingModifierLetterPage );
   mk_font_addPage ( &g_mkDisplay.defaultFont.handle, &g_mkDisplay.defaultFont.page [ 4 ] );

   /* Configuration de la page COMBINING_DIACRITICAL_MARKS */
   mk_font_setPage ( &g_mkDisplay.defaultFont.page [ 5 ], K_MK_FONT_PAGE_COMBINING_DIACRITICAL_MARKS, ( uint32_t ) ( K_MK_FONT_PAGE_GREEK_AND_COPTIC - 1 ),
                     &g_mkFontArialUnicodeMS12ptCombiningDiacriticalMarksPageDescriptor [ 0 ] [ 0 ], g_mkFontArialUnicodeMS12ptCombiningDiacriticalMarksPage );
   mk_font_addPage ( &g_mkDisplay.defaultFont.handle, &g_mkDisplay.defaultFont.page [ 5 ] );

   /* Configuration de la page GENERAL_PUNCTUATION */
   mk_font_setPage ( &g_mkDisplay.defaultFont.page [ 6 ], K_MK_FONT_PAGE_GENERAL_PUNCTUATION, ( uint32_t ) ( K_MK_FONT_PAGE_SUPERSCRIPTS_AND_SUBSCRIPTS - 1 ),
                     &g_mkFontArialUnicodeMS12ptGeneralPonctuationPageDescriptor [ 0 ] [ 0 ], g_mkFontArialUnicodeMS12ptGeneralPonctuationPage );
   mk_font_addPage ( &g_mkDisplay.defaultFont.handle, &g_mkDisplay.defaultFont.page [ 6 ] );

   /* Configuration de la page CURRENCY_SYMBOLS */
   mk_font_setPage ( &g_mkDisplay.defaultFont.page [ 7 ], K_MK_FONT_PAGE_CURRENCY_SYMBOLS, ( uint32_t ) ( K_MK_FONT_PAGE_COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS - 1 ),
                     &g_mkFontArialUnicodeMS12ptCurrencySymbolPageDescriptor [ 0 ] [ 0 ], g_mkFontArialUnicodeMS12ptCurrencySymbolPage );
   mk_font_addPage ( &g_mkDisplay.defaultFont.handle, &g_mkDisplay.defaultFont.page [ 7 ] );

   /* Configuration de la page ARROWS */
   mk_font_setPage ( &g_mkDisplay.defaultFont.page [ 8 ], K_MK_FONT_PAGE_ARROWS, ( uint32_t ) ( K_MK_FONT_PAGE_MATHEMATICAL_OPERATORS - 1 ),
                     &g_mkFontArialUnicodeMS12ptArrowPageDescriptor [ 0 ] [ 0 ], g_mkFontArialUnicodeMS12ptArrowPage );
   mk_font_addPage ( &g_mkDisplay.defaultFont.handle, &g_mkDisplay.defaultFont.page [ 8 ] );

   /* Configuration de la page MATHEMATICAL_OPERATORS */
   mk_font_setPage ( &g_mkDisplay.defaultFont.page [ 9 ], K_MK_FONT_PAGE_MATHEMATICAL_OPERATORS, ( uint32_t ) ( K_MK_FONT_PAGE_MISCELLANEOUS_TECHNICAL - 1 ),
                     &g_mkFontArialUnicodeMS12ptMathematicalOperatorPageDescriptor [ 0 ] [ 0 ], g_mkFontArialUnicodeMS12ptMathematicalOperatorPage );
   mk_font_addPage ( &g_mkDisplay.defaultFont.handle, &g_mkDisplay.defaultFont.page [ 9 ] );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_font_initDefault ( void )
{
   /* Initialisation de la police de taille fixe */
   mk_font_initDefaultFixedLength ( );

   /* Initialisation de la police de taille variable */
   mk_font_initDefaultVariableLength ( );

   /* Retour */
   return;
}


