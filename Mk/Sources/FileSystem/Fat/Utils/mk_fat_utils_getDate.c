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
* @file mk_fat_utils_getDate.c
* @brief Définition de la fonction mk_fat_getDate.
* @date 26 déc. 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_getCalendar ( T_str8 p_calendar )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_counter = K_MK_FAT_CALENDAR_NUMBER, l_weekDay = 0;

   /* Tant que le calendrier système n'a pas été acquis */
   while ( ( l_counter != 0 ) && ( l_weekDay == 0 ) )
   {
      /* Récupération de la date au format yy-mm-ddThh:mm:ss,000 */
      l_weekDay = rtc_getCalendar ( p_calendar );

      /* Actualisation du compteur */
      l_counter++;
   }

   /* Si une erreur s'est produite */
   if ( l_weekDay == 0 )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_UNEXPECTED;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_encode ( T_str8 p_calendar, uint16_t* p_date, uint16_t* p_time )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_year, l_month, l_date;
   uint32_t l_hour, l_minute, l_second;

   /* Champs "CreationTime" et "LastModifiedTime" */
   l_hour   = ( uint32_t ) (   ( uint32_t ) ( p_calendar [ 10 ] - 0x30 ) + ( ( uint32_t ) ( p_calendar [ 9 ]  - 0x30 ) * 10 ) );
   l_minute = ( uint32_t ) (   ( uint32_t ) ( p_calendar [ 13 ] - 0x30 ) + ( ( uint32_t ) ( p_calendar [ 12 ] - 0x30 ) * 10 ) );
   l_second = ( uint32_t ) ( ( ( uint32_t ) ( p_calendar [ 16 ] - 0x30 ) + ( ( uint32_t ) ( p_calendar [ 15 ] - 0x30 ) * 10 ) ) >> 1 );

   /* Champs "CreationDate", "LastModifiedDate" et "LastAccessDate" */
   l_year   = ( uint32_t ) ( 20 + ( ( uint32_t ) ( p_calendar [ 1 ] - 0x30 ) + ( ( uint32_t ) ( p_calendar [ 0 ] - 0x30 ) * 10 ) ) ); /* calendrier commence en 1980) */
   l_month  = ( uint32_t ) (        ( uint32_t ) ( p_calendar [ 4 ] - 0x30 ) + ( ( uint32_t ) ( p_calendar [ 3 ] - 0x30 ) * 10 ) );
   l_date   = ( uint32_t ) (        ( uint32_t ) ( p_calendar [ 7 ] - 0x30 ) + ( ( uint32_t ) ( p_calendar [ 6 ] - 0x30 ) * 10 ) );

   /* Actualisation de la valeur des paramètres de retour */
   *p_time = ( uint16_t ) ( ( ( l_hour & 0x1F ) << 11 ) | ( ( l_minute & 0x3F ) << 5 ) | ( l_second & 0x1F ) );
   *p_date = ( uint16_t ) ( ( ( l_year & 0x7F ) << 9  ) | ( ( l_month  & 0x0F ) << 5 ) | ( l_date   & 0x1F ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_getDate ( uint16_t* p_date, uint16_t* p_time )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   char8_t l_calendar [ 22 ];

   /* Si le paramètre est valide */
   if ( ( p_date != K_MK_NULL ) && ( p_time != K_MK_NULL ) )
   {
      /* Récupération du calendrier système */
      l_result = mk_fat_utils_getCalendar ( ( T_str8 ) l_calendar );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Encodage du calendrier au format FAT */
         l_result = mk_fat_utils_encode ( ( T_str8 ) l_calendar, p_date, p_time );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}
