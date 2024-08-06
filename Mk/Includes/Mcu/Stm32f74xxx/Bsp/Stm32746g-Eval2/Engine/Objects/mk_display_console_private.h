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
* @file mk_display_console_private.h
* @brief Déclaration des fonctions privées dédiées à l'objet 'Console'.
* @date 12 mars 2023
*
*/

#ifndef MK_DISPLAY_CONSOLE_PRIVATE_H
#define MK_DISPLAY_CONSOLE_PRIVATE_H

/**
 * @fn T_mkCode mk_console_writeFile ( T_mkFile* p_file, T_str8 p_str, uint32_t p_length );
 * @brief Cette fonction écrit le buffer 'p_str' de taille 'p_length' dans le fichier 'p_file'.
 *
 * @param[in] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_file    Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in] p_str     Ce paramètre contient l'adresse du buffer de données à écrire.
 * @param[in] p_length  Ce paramètre contient la longueur du buffer de données.

 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le fichier a été écrit.
 *         \li \ref K_MK_ERROR_PARAM      : le fichier n'a pas été écrit car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : le fichier n'a pas été écrit car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le fichier n'a pas été écrit car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le fichier n'a pas été écrit car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : le fichier n'a pas été écrit car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_DENIED     : le fichier n'a pas été écrit car il n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL       : le fichier n'a pas été écrit car l'espace disponible sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_RIGHT      : le fichier n'a pas été écrit car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_UNEXPECTED : le fichier n'a pas été écrit car une erreur inattendue s'est produite. Le nombre de données à écrire est différent du nombre de données écrits.
 *
 */

T_mkCode mk_console_writeFile ( T_mkConsole* p_console, T_mkFile* p_file, T_str8 p_str, uint32_t p_length );

/**
 * @fn T_mkCode mk_console_strcat ( T_mkConsole* p_console, T_str8 p_str );
 * @brief Cette fonction ajoute la chaine de caractères présente en paramètre dans le buffer de données de la console.
 *
 * @param[in] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_str     Ce paramètre contient l'adresse du buffer de données à concaténer.

 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la chaine de caractères a été concaténée.
 *         \li \ref K_MK_ERROR_PARAM   : la chaine de caractères n'a pas été concaténée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la chaine de caractères n'a pas été concaténée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la chaine de caractères n'a pas été concaténée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_FULL    : la chaine de caractères n'a pas été concaténée car la place disponible dans le buffer de la console est insuffisante.
 *         \li \ref K_MK_ERROR_RIGHT   : la chaine de caractères n'a pas été concaténée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_console_strcat ( T_mkConsole* p_console, T_str8 p_str );

/**
 * @fn T_mkCode mk_console_refresh ( T_mkConsole* p_console );
 * @brief Cette fonction rafraichie le contenu de la console suite à une mise à jour du buffer.
 * @param[in] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le contenu de la console a été rafraichi.
 *         \li \ref K_MK_ERROR_PARAM      : le contenu de la console n'a pas été rafraichi car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : le contenu de la console n'a pas été rafraichi car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le contenu de la console n'a pas été rafraichi car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le contenu de la console n'a pas été rafraichi car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : le contenu de la console n'a pas été rafraichi car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_DENIED     : le contenu de la console n'a pas été rafraichi car il n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_RIGHT      : le contenu de la console n'a pas été rafraichi car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_console_refresh ( T_mkConsole* p_console );

/**
 *
 */

#endif
