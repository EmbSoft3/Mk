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
* @file mk_supervisor_report.c
* @brief Définition de la fonction mk_supervisor_report.
* @date 30 mars 2023
*
*/

#include "mk_supervisor_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_supervisor_getFileName ( T_str8 p_str, T_str8 p_suffix )
{
   /* Déclaration d'une variable contenant le nom du fichier */
   char8_t l_tid [ 11 ] = { 0 };

   /* Conversion du TID de la tâche en ASCII */
   ( void ) mk_utils_itoa ( g_mkScheduler.currentTask->attribute.identifier, ( T_str8 ) l_tid, 16, 0 );

   /* Création de la chaine de caractères TID_<l_tid><suffix> */
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, ( T_str8 ) K_MK_SUPERVISOR_PATH, ( T_str8 ) "TID_" );
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, ( T_str8 ) p_str, ( T_str8 ) l_tid );
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, ( T_str8 ) p_str, ( T_str8 ) p_suffix );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_getRamdomFileName ( T_str8 p_randomFileName )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de retour locale */
   int32_t l_ret = 0;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'un ensemble de variables contenant les nombres aléatoires brutes */
   /* et leurs conversions en ASCII */
   char8_t l_randString [ 4 ] [ 9 ] = { { 0 } };
   uint32_t l_randNumber [ 4 ] = { 0, 0, 0, 0 };

   /* Création de la base de la chaine de caractères */
   mk_supervisor_getFileName ( ( T_str8 ) p_randomFileName, ( T_str8 ) "h_error_" );

   /* Pour le nombre de données aléatoires à générer */
   for ( l_counter = 0 ; ( l_counter < 4 ) && ( l_ret != ( -2 ) ) ; l_counter++ )
   {
      /* Effectue */
      do
      {
         /* Récupération d'un nombre aléatoire */
         l_ret = mk_utils_rand ( &l_randNumber [ l_counter ] );

      /* Tant que la conversion n'est pas terminée et tant qu'aucune erreur ne s'est produite */
      } while ( l_ret == ( -3 ) );
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_ret == 0 )
   {
      /* Conversion des nombres aléatoires en chaine de caractères */
      ( void ) mk_utils_itoa ( ( uint32_t ) l_randNumber [ 0 ], ( T_str8 ) &l_randString [ 0 ] [ 0 ], 16, 8 );
      ( void ) mk_utils_itoa ( l_randNumber [ 1 ], ( T_str8 ) &l_randString [ 1 ] [ 0 ], 16, 8 );
      ( void ) mk_utils_itoa ( l_randNumber [ 2 ], ( T_str8 ) &l_randString [ 2 ] [ 0 ], 16, 8 );
      ( void ) mk_utils_itoa ( l_randNumber [ 3 ], ( T_str8 ) &l_randString [ 3 ] [ 0 ], 16, 8 );

      /* Concaténéation des nombres aléatoires dans la chaine TID_<l_tid>h_error_<p_randomFileName>.md */
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomFileName, ( T_str8 ) p_randomFileName, ( T_str8 ) &l_randString [ 0 ] [ 0 ] );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomFileName, ( T_str8 ) p_randomFileName, ( T_str8 ) &l_randString [ 1 ] [ 0 ] );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomFileName, ( T_str8 ) p_randomFileName, ( T_str8 ) &l_randString [ 2 ] [ 0 ] );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomFileName, ( T_str8 ) p_randomFileName, ( T_str8 ) &l_randString [ 3 ] [ 0 ] );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomFileName, ( T_str8 ) p_randomFileName, ( T_str8 ) ".md" );
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_UNEXPECTED;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_logErr ( T_mkSupervisor* p_supervisor, T_mkSupervisorMessage* p_message, T_str8 p_str )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une chaine de caractères */
   char8_t l_str [ 196 ] = { 0 };

   /* Déclaration des variables de travail */
   char8_t l_tid [ 11 ] = { 0 }, l_err [ 11 ] = { 0 };

   /* Conversion du TID de la tâche en ASCII */
   ( void ) mk_utils_itoa ( p_message->task->attribute.identifier, ( T_str8 ) l_tid, 16, 0 );

   /* Conversion du code erreur de la tâche en ASCII */
   ( void ) mk_utils_itoa ( p_message->returnValue, ( T_str8 ) l_err, 16, 0 );

   /* Si l'erreur est de type TimeoutFault */
   if ( p_message->fault == K_MK_SUPERVISOR_TIMEOUTFAULT )
   {
      /* Création de la chaine de caractères */
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) p_str, ( T_str8 ) " catched.\n\nThe task (TID_" );
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) l_str, ( T_str8 ) l_tid );
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) l_str, ( T_str8 ) "h) suspended the non-privileged task. Creating report ...\n" );
   }

   /* Sinon si l'erreur est de type "TaskFault" */
   else if ( p_message->fault == K_MK_SUPERVISOR_TASKFAULT )
   {
      /* Création de la chaine de caractères */
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) p_str, ( T_str8 ) " catched.\n\nThe task (TID_" );
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) l_str, ( T_str8 ) l_tid );
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) l_str, ( T_str8 ) "h) has been suspended (error " );
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) l_str, ( T_str8 ) l_err );
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) l_str, ( T_str8 ) "h). Creating report ...\n" );
   }

   /* Sinon */
   else
   {
      /* Création de la chaine de caractères */
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) p_str, ( T_str8 ) " catched.\n\nThe task (TID_" );
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) l_str, ( T_str8 ) l_tid );
      ( void ) mk_utils_strcat ( ( T_str8 ) l_str, ( T_str8 ) l_str, ( T_str8 ) "h) has been suspended.\nSaving report ...\n\n" );
   }

   /* Affichage du message */
   l_result = mk_console_log ( &p_supervisor->console, ( T_str8 ) l_str );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_cat ( T_str8 p_str, T_str8 p_prefix, uint32_t p_registre, T_str8 p_suffix, uint8_t p_base, uint8_t p_digit )
{
   /* Déclaration des variables stockant la longueur des chaines de caractères */
   uint32_t l_length1 = 0, l_length2 = 0, l_length3 = 0;

   /* Déclaration d'un buffer */
   char8_t l_str [ 9 ] =  { 0 };

   /* Conversion du registre dans la base choisie */
   ( void ) mk_utils_itoa ( p_registre, ( T_str8 ) l_str, p_base, p_digit );

   /* Récupération de la longueur des chaines de caractères */
   l_length1 = mk_utils_strlen ( ( T_str8 ) p_prefix );
   l_length2 = mk_utils_strlen ( ( T_str8 ) l_str );
   l_length3 = mk_utils_strlen ( ( T_str8 ) p_suffix );

   /* Concaténation des chaines de caractères dans le buffer */
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, p_prefix, ( T_str8 ) l_str );
   ( void ) mk_utils_strcat ( ( T_str8 ) &p_str [ l_length1 + l_length2 ], p_suffix, ( T_str8 ) "" );

   /* Retour */
   return ( &p_str [ l_length1 + l_length2 + l_length3 ] );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_catString ( T_str8 p_str, T_str8 p_prefix, T_str8 p_suffix )
{
   /* Déclaration des variables stockant la longueur des chaines de caractères */
   uint32_t l_length1 = 0, l_length2 = 0;

   /* Récupération de la longueur des chaines de caractères */
   l_length1 = mk_utils_strlen ( ( T_str8 ) p_prefix );
   l_length2 = mk_utils_strlen ( ( T_str8 ) p_suffix );

   /* Concaténation des chaines de caractères dans le buffer */
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, p_prefix, ( T_str8 ) p_suffix );

   /* Retour */
   return ( &p_str [ l_length1 + l_length2 ] );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportDescription ( T_mkSupervisorFault p_fault, T_str8 p_str )
{
   /* Déclaration d'une variable stockant la date de création du rapport */
   char8_t l_time [ 22 ] = { 0 };

   /* Récupération du calendrier (format yy-mm-ddThh:mm:ss,000) */
   ( void ) rtc_getCalendar ( ( T_str8 ) l_time );

   /* Ecriture du titre dans le raport */
   p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "# Report\n\n", ( T_str8 ) "## Description\n\n" );

   /* Si l'erreur est de type NMI */
   if ( p_fault == K_MK_SUPERVISOR_NMIFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[NMI]\n" );
   }

   /* Sinon si l'erreur est de type HARDFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_HARDFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[HardFault]\n" );
   }

   /* Sinon si l'erreur est de type MEMFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_MEMFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[MemFault]\n" );
   }

   /* Sinon si l'erreur est de type BUSFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_BUSFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[BusFault]\n" );
   }

   /* Sinon si l'erreur est de type USAGEFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_USAGEFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[UsageFault]\n" );
   }

   /* Sinon si l'erreur est de type FPUFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_FPUFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[FPUFault]\n" );
   }

   /* Sinon si l'erreur est de type HANDLEFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_HANDLEFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[HandleFault]\n" );
   }

   /* Sinon si l'erreur est de type KERNELFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_SVCFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[KernelFault]\n" );
   }

   /* Sinon si l'erreur est de type RIGHTFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_RIGHTFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[RightFault]\n" );
   }

   /* Sinon si l'erreur est de type STACKFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_STACKFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[StackFault]\n" );
   }

   /* Sinon si l'erreur est de type TASKFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_TASKFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[TaskFault]\n" );
   }

   /* Sinon si l'erreur est de type TIMEOUTFAULT */
   else if ( p_fault == K_MK_SUPERVISOR_TIMEOUTFAULT )
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[TimeoutFault]\n" );
   }

   /* Sinon */
   else
   {
      p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Type : ", ( T_str8 ) "[UnknownFault]\n" );
   }

   /* Ecriture de la date de création du fichier */
   p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "Creation : ", ( T_str8 ) l_time );
   p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "\n\n", ( T_str8 ) "" );

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportStack ( T_mkTask* p_task, T_str8 p_str, T_str8 p_header )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'une variable de travail */
   uint32_t* l_base = p_task->stack.base;

   /* Ecriture de l'adresse de la tâche dans le rapport */
   p_str = mk_supervisor_cat ( p_str, p_header, ( uint32_t ) p_task, ( T_str8 ) ";\n\n", 16, 8 );

   /* Ecriture du contenu de la stack dans le rapport */
   /* Pour le nombre de mots dans la stack */
   for ( l_counter = 0 ; l_counter < p_task->stack.size ; l_counter++ )
   {
      /* Adresse */
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "0x", ( uint32_t ) ( l_base - l_counter ), ( T_str8 ) "  ", 16, 8 );

      /* Contenu */
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base - l_counter ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base - ( l_counter + 1 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base - ( l_counter + 2 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base - ( l_counter + 3 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base - ( l_counter + 4 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base - ( l_counter + 5 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base - ( l_counter + 6 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base - ( l_counter + 7 ) ), ( T_str8 ) "\n", 16, 8 );

      /* Actualisation du compteur */
      l_counter = ( uint32_t ) ( l_counter + 8 );
   }

   p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "\n", ( T_str8 ) "" );

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportTask ( T_mkTask* p_task, T_str8 p_str, T_str8 p_header )
{
   /* Ecriture des attributs de la tâche dans le rapport */
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) p_header, ( uint32_t ) p_task, ( T_str8 ) ";\n\n", 16u, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.stack.top : 0x", ( uint32_t ) p_task->stack.top, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.stack.base : 0x", ( uint32_t ) p_task->stack.base, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.stack.end : 0x", ( uint32_t ) p_task->stack.end, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.stack.size : 0x", ( uint32_t ) p_task->stack.size, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.function.address : 0x", ( uint32_t ) p_task->function.address, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.function.argument : 0x", ( uint32_t ) p_task->function.argument, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.attribute.identifier : 0x", ( uint32_t ) p_task->attribute.identifier, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.attribute.type : 0x", ( uint32_t ) p_task->attribute.type, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.attribute.state : 0x", ( uint32_t ) p_task->attribute.state, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.attribute.priority : 0x", ( uint32_t ) p_task->attribute.priority, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.attribute.currentPriority : 0x", ( uint32_t ) p_task->attribute.currentPriority, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.next[0] : 0x", ( uint32_t ) p_task->next[0], ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.next[1] : 0x", ( uint32_t ) p_task->next[1], ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.previous[0] : 0x", ( uint32_t ) p_task->previous[0], ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.previous[1] : 0x", ( uint32_t ) p_task->previous[1], ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.load.lastValue : 0x", ( uint32_t ) p_task->load.lastValue, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.load.value : 0x", ( uint32_t ) p_task->load.value, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.tick.timeout : 0x", ( uint32_t ) p_task->tick.timeout, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.tick.count : 0x", ( uint32_t ) p_task->tick.count, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.tick.refTime : 0x", ( uint32_t ) p_task->tick.refTime, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.synchro.object : 0x", ( uint32_t ) p_task->synchro.object, ( T_str8 ) ";\n", 16, 8  );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.synchro.mutex : 0x", ( uint32_t ) p_task->synchro.mutex, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.synchro.message : 0x", ( uint32_t ) p_task->synchro.message, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.synchro.event : 0x", ( uint32_t ) p_task->synchro.event, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.pool : 0x", ( uint32_t ) p_task->pool, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Task.svc : 0x", ( uint32_t ) p_task->svc, ( T_str8 ) ";\n\n", 16, 8 );

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportTasks ( T_mkScheduler* p_scheduler, T_mkTask* p_task, T_str8 p_str )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Ecriture des registres de la tâche de repos dans le rapport */
   p_str = mk_supervisor_reportTask ( &p_scheduler->idle, p_str, ( T_str8 ) "## IdleTask : 0x" );

   /* Ecriture du contenu de la stack de repos dans le rapport */
   p_str = mk_supervisor_reportStack ( &p_scheduler->idle, p_str, ( T_str8 ) "## IdleStack : 0x" );

   /* Ecriture des registres de la tâche en erreur dans le buffer */
   p_str = mk_supervisor_reportTask ( p_task, p_str, ( T_str8 ) "## FaultTask : 0x" );

   /* Ecriture du contenu de la stack en erreur dans le rapport */
   p_str = mk_supervisor_reportStack ( p_task, p_str, ( T_str8 ) "## FaultStack : 0x" );

   /* Pour le nombre de tâches pouvant être allouée */
   for ( l_counter = 0 ; l_counter < K_MK_SCHEDULER_MAX_NUMBER_OF_TASKS ; l_counter++ )
   {
      /* Si la tâche a été allouée */
      if ( g_mkTaskPool.task [ l_counter ].attribute.state != K_MK_STATE_DELETED )
      {
         /* Ecriture des registres de la tâche dans le buffer */
         p_str = mk_supervisor_reportTask ( &g_mkTaskPool.task [ l_counter ], p_str, ( T_str8 ) "## Task : 0x" );

         /* Ecriture de la stack de la tâche dans le buffer */
         p_str = mk_supervisor_reportStack ( &g_mkTaskPool.task [ l_counter ], p_str, ( T_str8 ) "## Stack : 0x" );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportPools ( T_str8 p_str )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_itemUnused = 0;

   /* Déclaration d'un pointeur de pool */
   T_mkPool* l_unused = K_MK_NULL;

   /* Pour le nombre de pools disponibles */
   for ( l_counter = 0 ; l_counter < K_MK_SCHEDULER_MAX_NUMBER_OF_POOLS ; l_counter++ )
   {
      /* Tant que l'analyse des pools non utilisés n'est pas terminée */
      for ( l_unused = g_mkAreaPool.pool.current ; ( l_unused != K_MK_NULL ) && ( l_itemUnused == 0 ) ; )
      {
         /* Si la pool n'est pas utilisée */
         if ( l_unused == &g_mkAreaPool.poolArea [ l_counter ] )
         {
            /* Arrêt de la boucle */
            l_itemUnused = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage à la prochaine pool */
         l_unused = ( T_mkPool* ) ( * ( uint32_t* ) l_unused );
      }

      /* Si la pool est utilisée */
      if ( l_itemUnused == 0 )
      {
         /* Ecriture des attributs de la pool dans le rapport */
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## Pool : 0x", ( uint32_t ) &g_mkAreaPool.poolArea [ l_counter ], ( T_str8 ) ";\n\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Pool.type : 0x", ( uint32_t ) g_mkAreaPool.poolArea [ l_counter ].type, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Pool.current : 0x", ( uint32_t ) g_mkAreaPool.poolArea [ l_counter ].current, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Pool.size : 0x", ( uint32_t ) g_mkAreaPool.poolArea [ l_counter ].size, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Pool.count : 0x", ( uint32_t ) g_mkAreaPool.poolArea [ l_counter ].count, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Pool.pendingList : 0x", ( uint32_t ) g_mkAreaPool.poolArea [ l_counter ].pendingList, ( T_str8 ) ";\n\n", 16, 8 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Réinitialisation de la variable de travail */
      l_itemUnused = 0;
   }

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportEvents ( T_str8 p_str )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_itemUnused = 0;

   /* Déclaration d'un pointeur d'événement */
   T_mkEvent* l_unused = K_MK_NULL;

   /* Pour le nombre d'événements disponibles */
   for ( l_counter = 0 ; l_counter < K_MK_SCHEDULER_MAX_NUMBER_OF_EVENTS ; l_counter++ )
   {
      /* Tant que l'analyse des événements non utilisés n'est pas terminée */
      for ( l_unused = g_mkEventPool.pool.current ; ( l_unused != K_MK_NULL ) && ( l_itemUnused == 0 ) ; )
      {
         /* Si l'événement n'est pas utilisé */
         if ( l_unused == &g_mkEventPool.event [ l_counter ] )
         {
            /* Arrêt de la boucle */
            l_itemUnused = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage au prochain événement */
         l_unused = ( T_mkEvent* ) ( * ( uint32_t* ) l_unused );
      }

      /* Si l'événement est utilisé */
      if ( l_itemUnused == 0 )
      {
         /* Ecriture des attributs de l'événement dans le rapport */
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## Event : 0x", ( uint32_t ) &g_mkEventPool.event [ l_counter ], ( T_str8 ) ";\n\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Event.type : 0x", ( uint32_t ) g_mkEventPool.event [ l_counter ].type, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Event.bypass : 0x", ( uint32_t ) g_mkEventPool.event [ l_counter ].bypass, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Event.flag : 0x", ( uint32_t ) g_mkEventPool.event [ l_counter ].flag, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Event.pendingList : 0x", ( uint32_t ) g_mkEventPool.event [ l_counter ].pendingList.current, ( T_str8 ) ";\n\n", 16, 8 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Réinitialisation de la variable de travail */
      l_itemUnused = 0;
   }

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportMutex ( T_str8 p_str )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_itemUnused = 0;

   /* Déclaration d'un pointeur de mutex */
   T_mkMutex* l_unused = K_MK_NULL;

   /* Pour le nombre de mutex disponibles */
   for ( l_counter = 0 ; l_counter < K_MK_SCHEDULER_MAX_NUMBER_OF_MUTEX ; l_counter++ )
   {
      /* Tant que l'analyse des mutex non utilisés n'est pas terminée */
      for ( l_unused = g_mkMutexPool.pool.current ; ( l_unused != K_MK_NULL ) && ( l_itemUnused == 0 ) ; )
      {
         /* Si le mutex n'est pas utilisé */
         if ( l_unused == &g_mkMutexPool.mutex [ l_counter ] )
         {
            /* Arrêt de la boucle */
            l_itemUnused = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage au prochain mutex */
         l_unused = ( T_mkMutex* ) ( * ( uint32_t* ) l_unused );
      }

      /* Si le mutex est utilisé */
      if ( l_itemUnused == 0 )
      {
         /* Ecriture des attributs du mutex dans le rapport */
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## Mutex : 0x", ( uint32_t ) &g_mkMutexPool.mutex [ l_counter ], ( T_str8 ) ";\n\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mutex.type : 0x", ( uint32_t ) g_mkMutexPool.mutex [ l_counter ].type, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mutex.lock : 0x", ( uint32_t ) g_mkMutexPool.mutex [ l_counter ].lock, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mutex.owner : 0x", ( uint32_t ) g_mkMutexPool.mutex [ l_counter ].owner, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mutex.pendingList : 0x", ( uint32_t ) g_mkMutexPool.mutex [ l_counter ].pendingList.current, ( T_str8 ) ";\n\n", 16, 8 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Réinitialisation de la variable de travail */
      l_itemUnused = 0;
   }

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportSemaphores ( T_str8 p_str )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_itemUnused = 0;

   /* Déclaration d'un pointeur de sémaphore */
   T_mkSemaphore* l_unused = K_MK_NULL;

   /* Pour le nombre de sémaphores disponibles */
   for ( l_counter = 0 ; l_counter < K_MK_SCHEDULER_MAX_NUMBER_OF_SEMAPHORES ; l_counter++ )
   {
      /* Tant que l'analyse des sémaphores non utilisés n'est pas terminée */
      for ( l_unused = g_mkSemaphorePool.pool.current ; ( l_unused != K_MK_NULL ) && ( l_itemUnused == 0 ) ; )
      {
         /* Si le sémaphore n'est pas utilisé */
         if ( l_unused == &g_mkSemaphorePool.semaphore [ l_counter ] )
         {
            /* Arrêt de la boucle */
            l_itemUnused = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage au prochain sémaphore */
         l_unused = ( T_mkSemaphore* ) ( * ( uint32_t* ) l_unused );
      }

      /* Si le sémaphore est utilisé */
      if ( l_itemUnused == 0 )
      {
         /* Ecriture des attributs du sémaphore dans le rapport */
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## Semaphore : 0x", ( uint32_t ) &g_mkSemaphorePool.semaphore [ l_counter ], ( T_str8 ) ";\n\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Semaphore.type : 0x", ( uint32_t ) g_mkSemaphorePool.semaphore [ l_counter ].type, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Semaphore.token : 0x", ( uint32_t ) g_mkSemaphorePool.semaphore [ l_counter ].token, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Semaphore.tokenNumber : 0x", ( uint32_t ) g_mkSemaphorePool.semaphore [ l_counter ].tokenNumber, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Semaphore.pendingList : 0x", ( uint32_t ) g_mkSemaphorePool.semaphore [ l_counter ].pendingList.current, ( T_str8 ) ";\n\n", 16, 8 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Réinitialisation de la variable de travail */
      l_itemUnused = 0;
   }

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportMailItem ( T_mkMailItem* p_item, T_str8 p_str, uint32_t p_size )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'un pointeur */
   uint32_t* l_base = ( uint32_t* ) p_item->pnt;

   /* Ecriture des attributs d'un item de la boite dans le rapport */
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## Item : 0x", ( uint32_t ) p_item, ( T_str8 ) ";\n\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Item.next : 0x", ( uint32_t ) p_item->next, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Item.task : 0x", ( uint32_t ) p_item->task, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Item.pnt : 0x", ( uint32_t ) p_item->pnt, ( T_str8 ) ";\n\n", 16, 8 );

   /* Ecriture des attributs du message de la boite dans le rapport */
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## Pnt : 0x", ( uint32_t ) p_item->pnt, ( T_str8 ) ";\n\n", 16, 8 );

   /* Ecriture du contenu du message */
   for ( l_counter = 0 ; l_counter < p_size ; l_counter++ )
   {
      /* Adresse */
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "0x", ( uint32_t ) ( p_item->pnt ), ( T_str8 ) "  ", 16, 8 );
      /* Contenu */
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base + l_counter ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base + ( l_counter + 1 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base + ( l_counter + 2 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base + ( l_counter + 3 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base + ( l_counter + 4 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base + ( l_counter + 5 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base + ( l_counter + 6 ) ), ( T_str8 ) " ", 16, 8 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) * ( l_base + ( l_counter + 7 ) ), ( T_str8 ) "\n", 16, 8 );
      /* Actualisation du compteur */
      l_counter = ( uint32_t ) ( l_counter + 8 );
   }

   p_str = mk_supervisor_catString ( ( T_str8 ) p_str, ( T_str8 ) "\n", ( T_str8 ) "" );

   /* Retour */
   return ( p_str );

}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportMail ( T_str8 p_str )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_itemUnused = 0;

   /* Déclaration d'un pointeur de boite de messages */
   T_mkMail* l_unused = K_MK_NULL;

   /* Déclaration d'un pointeur d'item */
   T_mkMailItem* l_item = K_MK_NULL;

   /* Pour le nombre de boite de messages disponibles */
   for ( l_counter = 0 ; l_counter < K_MK_SCHEDULER_MAX_NUMBER_OF_MAILS ; l_counter++ )
   {
      /* Tant que l'analyse des boites de messages non utilisées n'est pas terminée */
      for ( l_unused = g_mkMailPool.pool.current ; ( l_unused != K_MK_NULL ) && ( l_itemUnused == 0 ) ; )
      {
         /* Si la boite n'est pas utilisée */
         if ( l_unused == &g_mkMailPool.mail [ l_counter ] )
         {
            /* Arrêt de la boucle */
            l_itemUnused = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage à la prochaine boite */
         l_unused = ( T_mkMail* ) ( * ( uint32_t* ) l_unused );
      }

      /* Si la boite est utilisée */
      if ( l_itemUnused == 0 )
      {
         /* Ecriture des attributs de la boite dans le rapport */
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## Mail : 0x", ( uint32_t ) &g_mkMailPool.mail [ l_counter ], ( T_str8 ) ";\n\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mail.size : 0x", ( uint32_t ) g_mkMailPool.mail [ l_counter ].size, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mail.unused.item : 0x", ( uint32_t ) g_mkMailPool.mail [ l_counter ].unused.item, ( T_str8 ) ";\n\n", 16, 8 );

         /* Poster */
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mail.poster.type : 0x", ( uint32_t ) g_mkMailPool.mail [ l_counter ].poster.type, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mail.poster.item : 0x", ( uint32_t ) g_mkMailPool.mail [ l_counter ].poster.item, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mail.poster.reserved : 0x", ( uint32_t ) g_mkMailPool.mail [ l_counter ].poster.reserved, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mail.poster.pendingList.task : 0x", ( uint32_t ) g_mkMailPool.mail [ l_counter ].poster.pendingList.current, ( T_str8 ) ";\n\n", 16, 8 );

         /* Pender */
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mail.pender.type : 0x", ( uint32_t ) g_mkMailPool.mail [ l_counter ].pender.type, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mail.pender.item : 0x", ( uint32_t ) g_mkMailPool.mail [ l_counter ].pender.item, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mail.pender.reserved : 0x", ( uint32_t ) g_mkMailPool.mail [ l_counter ].pender.reserved, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Mail.pender.pendingList.task : 0x", ( uint32_t ) g_mkMailPool.mail [ l_counter ].pender.pendingList.current, ( T_str8 ) ";\n\n", 16, 8 );

         /* Configuration du pointeur d'item */
         l_item = g_mkMailPool.mail [ l_counter ].poster.item;

         /* Tant que tous les items de la chaine n'ont pas été enregistré */
         while ( l_item != K_MK_NULL )
         {
            p_str = mk_supervisor_reportMailItem ( l_item, p_str, g_mkMailPool.mail [ l_counter ].size );
            l_item = l_item->next;
         }

         /* Configuration du pointeur d'item */
         l_item = g_mkMailPool.mail [ l_counter ].pender.item;

         /* Tant que tous les items de la chaine n'ont pas été enregistré */
         while ( l_item != K_MK_NULL )
         {
            p_str = mk_supervisor_reportMailItem ( l_item, p_str, g_mkMailPool.mail [ l_counter ].size );
            l_item = l_item->next;
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Réinitialisation de la variable de travail */
      l_itemUnused = 0;
   }

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportCallbackFunction ( T_str8 p_str )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_itemUnused = 0;

   /* Déclaration d'un pointeur de fonction de rappel */
   T_mkCallback* l_unused = K_MK_NULL;

   /* Pour le nombre de fonctions de rappel disponibles */
   for ( l_counter = 0 ; l_counter < K_MK_SCHEDULER_MAX_NUMBER_OF_CALLBACK_FUNCTION ; l_counter++ )
   {
      /* Tant que l'analyse des fonctions de rappel non utilisées n'est pas terminée */
      for ( l_unused = g_mkCallbackFunctionPool.pool.current ; ( l_unused != K_MK_NULL ) && ( l_itemUnused == 0 ) ; )
      {
         /* Si la fonction de rappel n'est pas utilisée */
         if ( l_unused == &g_mkCallbackFunctionPool.callback [ l_counter ] )
         {
            /* Arrêt de la boucle */
            l_itemUnused = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage à la prochaine fonction */
         l_unused = ( T_mkCallback* ) ( * ( uint32_t* ) l_unused );
      }

      /* Si la fonction de rappel est utilisée */
      if ( l_itemUnused == 0 )
      {
         /* Ecriture des attributs de la fonction de rappel dans le rapport */
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## CallbackFunction : 0x", ( uint32_t ) &g_mkCallbackFunctionPool.callback [ l_counter ], ( T_str8 ) ";\n\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CallbackFunction.type : 0x", ( uint32_t ) g_mkCallbackFunctionPool.callback [ l_counter ].type, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CallbackFunction.identifier : 0x", ( uint32_t ) g_mkCallbackFunctionPool.callback [ l_counter ].identifier, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CallbackFunction.addr : 0x", ( uint32_t ) g_mkCallbackFunctionPool.callback [ l_counter ].addr, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CallbackFunction.handler : 0x", ( uint32_t ) g_mkCallbackFunctionPool.callback [ l_counter ].handler, ( T_str8 ) ";\n\n", 16, 8 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Réinitialisation de la variable de travail */
      l_itemUnused = 0;
   }

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportCallbackHandler ( T_str8 p_str )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_itemUnused = 0;

   /* Déclaration d'un pointeur de gestionnaire de rappel */
   T_mkCallbackHandler* l_unused = K_MK_NULL;

   /* Pour le nombre de gestionnaires de rappel disponibles */
   for ( l_counter = 0 ; l_counter < K_MK_SCHEDULER_MAX_NUMBER_OF_CALLBACK_HANDLER ; l_counter++ )
   {
      /* Tant que l'analyse des gestionnaires de rappel non utilisés n'est pas terminée */
      for ( l_unused = g_mkCallbackHandlerPool.pool.current ; ( l_unused != K_MK_NULL ) && ( l_itemUnused == 0 ) ; )
      {
         /* Si le gestionnaire de rappel n'est pas utilisé */
         if ( l_unused == &g_mkCallbackHandlerPool.handler [ l_counter ] )
         {
            /* Arrêt de la boucle */
            l_itemUnused = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage au prochain gestionnaire */
         l_unused = ( T_mkCallbackHandler* ) ( * ( uint32_t* ) l_unused );
      }

      /* Si le gestionnaire de rappel est utilisé */
      if ( l_itemUnused == 0 )
      {
         /* Ecriture des attributs du gestionnaire de rappel dans le rapport */
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## CallbackHandler : 0x", ( uint32_t ) &g_mkCallbackHandlerPool.handler [ l_counter ], ( T_str8 ) ";\n\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CallbackHandler.type : 0x", ( uint32_t ) g_mkCallbackHandlerPool.handler [ l_counter ].type, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CallbackHandler.identifier : 0x", ( uint32_t ) g_mkCallbackHandlerPool.handler [ l_counter ].identifier, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CallbackHandler.event : 0x", ( uint32_t ) g_mkCallbackHandlerPool.handler [ l_counter ].event, ( T_str8 ) ";\n", 16, 8 );
         p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CallbackHandler.mail : 0x", ( uint32_t ) g_mkCallbackHandlerPool.handler [ l_counter ].mail, ( T_str8 ) ";\n\n", 16, 8 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Réinitialisation de la variable de travail */
      l_itemUnused = 0;
   }

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportScheduler ( T_mkScheduler* p_scheduler, T_str8 p_str )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Ecriture des attributs de l'ordonnanceur dans le rapport */
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## Scheduler : 0x", ( uint32_t ) p_scheduler, ( T_str8 ) ";\n\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.currentTask : 0x", ( uint32_t ) p_scheduler->currentTask, ( T_str8 ) ";\n", 16, 8 );

   /* Pour le nombre de listes dans l'ordonnanceur */
   for ( l_counter = 0 ; l_counter < ( K_MK_SCHEDULER_PRIORITY_NUMBER + 1 ) ; l_counter++ )
   {
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.readyList[", l_counter, ( T_str8 ) "] : 0x", 10, 0 );
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "", ( uint32_t ) p_scheduler->readyList [ l_counter].current, ( T_str8 ) ";\n", 16, 8 );
   }

   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.delayList : 0x", ( uint32_t ) p_scheduler->delayList.current, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.suspendList : 0x", ( uint32_t ) p_scheduler->suspendList.current, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.statusRegister.initialized : 0x", ( uint32_t ) p_scheduler->statusRegister.initialized, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.statusRegister.started : 0x", ( uint32_t ) p_scheduler->statusRegister.started, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.statusRegister.idle : 0x", ( uint32_t ) p_scheduler->statusRegister.idle, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.statusRegister.type : 0x", ( uint32_t ) p_scheduler->statusRegister.type, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.statusRegister.locked : 0x", ( uint32_t ) p_scheduler->statusRegister.locked, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.statusRegister.isr : 0x", ( uint32_t ) p_scheduler->statusRegister.isr, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.priorityRegister : 0x", ( uint32_t ) p_scheduler->priorityRegister, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.tickRegister : 0x", ( uint32_t ) p_scheduler->tickRegister, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.taskCounter : 0x", ( uint32_t ) p_scheduler->taskCounter, ( T_str8 ) ";\n", 16, 0 );

   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.load.tickRegister : 0x", ( uint32_t ) p_scheduler->load.tickRegister, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.load.timerRegister : 0x", ( uint32_t ) p_scheduler->load.timerRegister, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.load.usTickRegister : 0x", ( uint32_t ) p_scheduler->load.usTickRegister, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.load.usTickRegisterSum : 0x", ( uint32_t ) p_scheduler->load.usTickRegisterSum, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.load.usTickRegisterLastSum : 0x", ( uint32_t ) p_scheduler->load.usTickRegisterLastSum, ( T_str8 ) ";\n", 16, 0 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "Scheduler.load.cycleRegister : 0x", ( uint32_t ) p_scheduler->load.cycleRegister, ( T_str8 ) ";\n\n", 16, 0 );

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportRegister ( T_mkSupervisorDumpRegister* p_reg, T_str8 p_str )
{
   /* Ecriture de la valeur des registres du CPU dans le rapport */
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "## Core Registers :\n\nMSP : 0x", p_reg->msp, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "PSP : 0x", p_reg->psp, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SP : 0x", p_reg->sp, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "PSR : 0x", p_reg->psr, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "PRIMASK : 0x", p_reg->primask, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "FAULTMASK : 0x", p_reg->faultmask, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "BASEPRI : 0x", p_reg->basepri, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CONTROL : 0x", p_reg->control, ( T_str8 ) ";\n", 16, 8 );

   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "ACTLR : 0x", p_reg->actlr, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CPUID : 0x", p_reg->cpuid, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "ICSR : 0x", p_reg->icsr, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "VTOR : 0x", p_reg->vtor, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "AIRCR : 0x", p_reg->aircr, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SCR : 0x", p_reg->scr, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CCR : 0x", p_reg->ccr, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SHPR1 : 0x", p_reg->shpr1, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SHPR2 : 0x", p_reg->shpr2, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SHPR3 : 0x", p_reg->shpr3, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SHCRS : 0x", p_reg->shcrs, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "CFSR : 0x", p_reg->cfsr, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "HFSR : 0x", p_reg->hfsr, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "MMAR : 0x", p_reg->mmar, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "BFAR : 0x", p_reg->bfar, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "AFSR : 0x", p_reg->afsr, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "FPSCR : 0x", p_reg->fpscr, ( T_str8 ) ";\n", 16, 8 );

   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "R4 : 0x", p_reg->r4, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "R5 : 0x", p_reg->r5, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "R6 : 0x", p_reg->r6, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "R7 : 0x", p_reg->r7, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "R8 : 0x", p_reg->r8, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "R9 : 0x", p_reg->r9, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "R10 : 0x", p_reg->r10, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "R11 : 0x", p_reg->r11, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "R12 : 0x", p_reg->r12, ( T_str8 ) ";\n", 16, 8 );

   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S16 : 0x", ( uint32_t ) p_reg->s16, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S17 : 0x", ( uint32_t ) p_reg->s17, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S18 : 0x", ( uint32_t ) p_reg->s18, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S19 : 0x", ( uint32_t ) p_reg->s19, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S20 : 0x", ( uint32_t ) p_reg->s20, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S21 : 0x", ( uint32_t ) p_reg->s21, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S22 : 0x", ( uint32_t ) p_reg->s22, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S23 : 0x", ( uint32_t ) p_reg->s23, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S24 : 0x", ( uint32_t ) p_reg->s24, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S25 : 0x", ( uint32_t ) p_reg->s25, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S26 : 0x", ( uint32_t ) p_reg->s26, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S27 : 0x", ( uint32_t ) p_reg->s27, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S28 : 0x", ( uint32_t ) p_reg->s28, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S29 : 0x", ( uint32_t ) p_reg->s29, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S30 : 0x", ( uint32_t ) p_reg->s30, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "S31 : 0x", ( uint32_t ) p_reg->s31, ( T_str8 ) ";\n\n", 16, 8 );

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportSVC ( T_mkSVCError p_error, T_mkSVCObject* p_svc, uint32_t p_isr, T_str8 p_str )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Ecriture des attributs de l'objet SVC dans le rapport */
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "KernelFault : 0x", ( uint32_t ) p_error, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "ISRStatus : 0x", ( uint32_t ) p_isr, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SVCType : 0x", ( uint32_t ) p_svc->type, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SVCStatus : 0x", ( uint32_t ) p_svc->status, ( T_str8 ) ";\n", 16, 8 );
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SVCHandle : 0x", ( uint32_t ) p_svc->handle, ( T_str8 ) ";\n", 16, 8 );

   for ( l_counter = 0 ; l_counter < K_MK_SVC_OBJECT_SIZE ; l_counter++ )
   {
      p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SVCData : 0x", ( uint32_t ) p_svc->data [ l_counter ], ( T_str8 ) ";\n", 16, 8 );
   }

   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "SVCResult : 0x", ( uint32_t ) p_svc->result, ( T_str8 ) ";\n\n", 16, 8 );

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportTaskResult ( T_mkCode p_returnValue, T_str8 p_str )
{
   /* Ecriture de la valeur de retour dans le rapport */
   p_str = mk_supervisor_cat ( p_str, ( T_str8 ) "ReturnValue : 0x", ( uint32_t ) p_returnValue, ( T_str8 ) ";\n\n", 16, 8 );

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_supervisor_reportObjects ( T_str8 p_str )
{
   /* Ecriture des pools dans le rapport */
   p_str = mk_supervisor_reportPools ( p_str );

   /* Ecriture des champs d'événements dans le rapport */
   p_str = mk_supervisor_reportEvents ( p_str );

   /* Ecriture des mutex dans le rapport */
   p_str = mk_supervisor_reportMutex ( p_str );

   /* Ecriture des sémaphores dans le rapport */
   p_str = mk_supervisor_reportSemaphores ( p_str );

   /* Ecriture des boites de messages dans le rapport */
   p_str = mk_supervisor_reportMail ( p_str );

   /* Ecriture des gestionnaires de rappel dans le rapport */
   p_str = mk_supervisor_reportCallbackHandler ( p_str );

   /* Ecriture des fonctions de rappel dans le rapport */
   p_str = mk_supervisor_reportCallbackFunction ( p_str );

   /* Retour */
   return ( p_str );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_writeFile ( T_mkFile* p_file, T_str8 p_str )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_totalNumberOfBytes = 0, l_numberOfBytesToWrite = 0, l_numberOfBytesWrite = 0;

   /* Récupération de la longueur de la chaine de caractères */
   l_totalNumberOfBytes = mk_utils_strlen ( ( T_str8 ) p_str );

   /* Ecriture du fichier par morceaux de K_MK_SUPERVISOR_REPORT_NUMBEROFBYTES_TO_WRITE octets */
   /* Le buffer est stocké dans la mémoire SDRAM, il faut enregistrer le buffer petit à petit pour */
   /* ne pas provoquer d'artefact graphique "FifoUnderrunInterrupt". */
   while ( ( l_result == K_MK_OK ) && ( l_totalNumberOfBytes != 0 ) )
   {
      /* Si un morceau complet de NUMBEROFBYTES octets peut être écrit */
      if ( l_totalNumberOfBytes > K_MK_SUPERVISOR_REPORT_NUMBEROFBYTES_TO_WRITE )
      {
         /* Configuration de la taille du transfert à NUMBEROFBYTES octets */
         l_numberOfBytesToWrite = K_MK_SUPERVISOR_REPORT_NUMBEROFBYTES_TO_WRITE;

      }

      /* Sinon */
      else
      {
         /* Configuration de la taille du transfert avec le nombre d'octets restants */
         l_numberOfBytesToWrite = l_totalNumberOfBytes;
      }

      /* Ecriture du buffer dans le fichier */
      l_result = mk_file_write ( p_file, p_str, l_numberOfBytesToWrite, &l_numberOfBytesWrite, K_MK_NULL );

      /* Si une erreur d'écriture s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesToWrite != l_numberOfBytesWrite ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_UNEXPECTED;
      }

      /* Sinon */
      else
      {
         /* Attente 20 ms (> 1 frame) */
         l_result = mk_task_sleep ( 20 );
      }

      /* Actualisation des variables */
      l_totalNumberOfBytes = ( uint32_t ) ( l_totalNumberOfBytes - l_numberOfBytesToWrite );
      p_str += l_numberOfBytesToWrite;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_rename ( T_mkSupervisor* p_supervisor, T_str8 p_str )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de fichier */
   T_mkFile* l_file = K_MK_NULL;

   /* Déclaration d'une chaine de caractères */
   char8_t l_randomFileName [ 96 ] = { 0 };

   /* Ouverture du fichier à renommer */
   l_result = mk_file_open ( p_supervisor->volume, &l_file, p_str, K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ | K_MK_FS_OPEN_WRITE, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Effectue */
      do
      {
         /* Récupération d'un nom de fichier aléatoire */
         mk_supervisor_getRamdomFileName ( ( T_str8 ) l_randomFileName );

         /* Test de l'existance du fichier à créer */
         l_result = mk_file_stat ( p_supervisor->volume, ( T_str8 ) l_randomFileName, K_MK_NULL );

      /* Tant que le fichier existe et tant qu'aucune erreur ne s'est produite */
      } while ( ( l_result == K_MK_OK ) );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_ERROR_NOT_FOUND )
      {
         /* Renommage du fichier */
         l_result = mk_file_rename ( l_file, ( T_str8 ) l_randomFileName, K_MK_NULL );

         /* Fermeture du fichier */
         l_result |= mk_file_close ( l_file, K_MK_NULL );
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

static T_mkCode mk_supervisor_editReport ( T_mkSupervisorMessage* p_message, T_str8 p_fileName, T_str8 p_str )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un fichier */
   T_mkFile* l_file = K_MK_NULL;

   /* Déclaration d'un ponteur de chaine */
   T_str8 l_str = K_MK_NULL;

   /* Si les paramètres sont valides */
   if ( ( p_message != K_MK_NULL ) && ( p_fileName != K_MK_NULL ) && ( p_str != K_MK_NULL ) )
   {
      /* Ouverture du fichier */
      l_result = mk_file_open ( g_mkSupervisor.volume, &l_file, p_fileName, K_MK_FS_OPEN_APPEND | K_MK_FS_OPEN_READ | K_MK_FS_OPEN_WRITE, K_MK_NULL );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Ecriture de l'entête du rapport dans le fichier */
         l_str = mk_supervisor_reportDescription ( p_message->fault, p_str );

         /* Ecriture des registres de processeur dans le rapport */
         l_str = mk_supervisor_reportRegister ( &p_message->dump, l_str );

         /* Ecriture des registres de l'ordonanceur dans le rapport */
         l_str = mk_supervisor_reportScheduler ( &p_message->scheduler, l_str );

         /* Si l'erreur détectée est de type KERNEL_FAULT */
         if ( p_message->fault == K_MK_SUPERVISOR_SVCFAULT )
         {
            /* Ecriture des registres du gestionnaire SVC dans le rapport */
            l_str = mk_supervisor_reportSVC ( p_message->svc.fault, &p_message->svc.object, p_message->svc.isr, l_str );
         }

         /* Sinon si l'erreur détectée est de type TASK_FAULT */
         else if ( p_message->fault == K_MK_SUPERVISOR_TASKFAULT )
         {
            /* Ecriture des attributs de la tâche en erreur dans le rapport */
            l_str = mk_supervisor_reportTaskResult ( p_message->returnValue, l_str );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Ecriture des attributs de toutes les tâches dans le rapport */
         l_str = mk_supervisor_reportTasks ( &p_message->scheduler, p_message->task, l_str );

         /* Ecriture des attributs des objets du noyau dans le buffer */
         l_str = mk_supervisor_reportObjects ( l_str );

         /* Ecriture du fichier */
         l_result = mk_supervisor_writeFile ( l_file, p_str );

         /* Fermeture du fichier (sans condition) */
         l_result |= mk_file_close ( l_file, K_MK_NULL );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_supervisor_report ( T_mkSupervisor* p_supervisor, T_mkSupervisorMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable contenant le nom du rapport */
   char8_t l_str [ 44 ] = { 0 };

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Une erreur grave vient de se produire */
   /* Peu importe le résultat des fonctions ci-dessous, on tente de créer un log pour l'utilisateur */
   /* L'état du système étant dégradé, on utilise un buffer de taille importante pour ne réaliser */
   /* qu'une seule requête. */

   /* Pour le nombre de terminaux dédiés au système de fichier */
   for ( ( l_counter = 0 ) ; l_counter < ( K_MK_FILE_NUMBER_OF_TASKS - 1 ) ; l_counter++ )
   {
      /* Si la tâche en erreur participe à la gestion du système de fichier */
      if ( ( p_message->task == g_mkTermioHandler.mmc->task ) ||
         ( ( K_MK_FILE_NUMBER_OF_TASKS == 2 ) && ( p_message->task == g_mkTermioHandler.fileManager [ l_counter]->task ) ) )
      {
         /* Réinitialisation du pointeur de console */
         p_supervisor->console.window.file = K_MK_NULL;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Récupération d'un nom de fichier */
   mk_supervisor_getFileName ( ( T_str8 ) l_str, ( T_str8 ) "h_error.md" );

   /* Effacement de la console */
   l_result = mk_console_clean ( &p_supervisor->console );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si l'erreur est de type NMI */
      if ( p_message->fault == K_MK_SUPERVISOR_NMIFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[NMIFault]" );
      }

      /* Sinon si l'erreur est de type HardFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_HARDFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[HardFault]" );
      }

      /* Sinon si l'erreur est de type MemFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_MEMFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[MemFault]" );
      }

      /* Sinon si l'erreur est de type BusFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_BUSFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[BusFault]" );
      }

      /* Sinon si l'erreur est de type UsageFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_USAGEFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[UsageFault]" );
      }

      /* Sinon si l'erreur est de type FPUFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_FPUFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[FpuFault]" );
      }

      /* Sinon si l'erreur est de type HandleFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_HANDLEFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[HandleFault]" );
      }

      /* Sinon si l'erreur est de type SVCFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_SVCFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[KernelFault]" );
      }

      /* Sinon si l'erreur de type RightFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_RIGHTFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[RightFault]" );
      }

      /* Sinon si l'erreur de type StackFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_STACKFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[StackFault]" );
      }

      /* Sinon si l'erreur de type TaskFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_TASKFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[TaskFault]" );
      }

      /* Sinon si l'erreur de type TimeoutFault */
      else if ( p_message->fault == K_MK_SUPERVISOR_TIMEOUTFAULT )
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[TimeoutFault]" );
      }

      /* Sinon */
      else
      {
         /* Signalisation de l'erreur à l'utilisateur */
         l_result |= mk_supervisor_logErr ( p_supervisor, p_message, ( T_str8 ) "[UnknowFault]" );
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Désactivation de l'exécution des fonctions d'écoutes et de peintures de tous */
   /* les containers privilégiés et non privilégiés */
   mk_display_disableFactory ( );

   /* Réactivation de la visibilité de la console */
   mk_container_setVisibility ( g_mkDisplay.criticalContainer, K_MK_FIELD_VISIBLE );
   mk_container_setActivity ( g_mkDisplay.criticalContainer, K_MK_FIELD_ACTIF );

   /* Si un rapport peut être édité */
   if ( ( l_result == K_MK_OK ) && ( p_supervisor->console.window.file != K_MK_NULL ) )
   {
      /* Test de l'existance du fichier à créer */
      l_result = mk_file_stat ( p_supervisor->volume, ( T_str8 ) l_str, K_MK_NULL );

      /* Si le fichier existe */
      if ( l_result == K_MK_OK )
      {
         /* Renommage du fichier existant */
         l_result = mk_supervisor_rename ( p_supervisor, ( T_str8 ) l_str );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_NOT_FOUND ) )
      {
         /* Edition d'un rapport d'erreur */
         l_result = mk_supervisor_editReport ( p_message, ( T_str8 ) l_str, ( T_str8 ) p_supervisor->page.reportAddr );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Affichage d'un message de succès dans la console */
         l_result = mk_console_log ( &p_supervisor->console, ( T_str8 ) "\n\nThe report has been saved. \nUse the 'reset' command to restart the system.\n\n" );
      }

      /* Sinon */
      else
      {
         /* Affichage d'un message d'erreur dans la console */
         l_result = mk_console_log ( &p_supervisor->console, ( T_str8 ) "\n\nFailed :(\nUse the 'reset' command to restart the system.\n\n" );
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}



