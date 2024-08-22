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
* @file mk_page.h
* @brief Déclaration des fonctions publiques dédiées au module 'Page'.
* @date 10 avr. 2023
*
*/

#ifndef MK_PAGE_H
#define MK_PAGE_H

/**
 * @fn T_mkCode mk_page_initHandler ( void );
 * @brief Cette fonction initialise les gestionnaires permettant d'allouer dynamiquement des pages mémoire.
 *
 * @return Cette fonction retourne un des codes suivants :
 *
 *         \li \ref K_MK_OK           : les gestionnaires d'allocation ont été initialisées correctement.
 *         \li \ref K_MK_ERROR_PARAM  : les gestionnaires d'allocation n'ont pas été initialisées car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : les gestionnaires d'allocation n'ont pas été initialisées car la taille de la zone mémoire définie dans la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : les gestionnaires d'allocation n'ont pas été initialisées car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_page_initHandler ( void );

/**
 * @fn T_mkCode mk_page_alloc ( T_mkPageIdentifier p_mkIdentifier, T_mkAddr* p_mkAddr, uint32_t p_mkTick );
 * @brief Cette fonction alloue une page mémoire dans la mémoire identifiée par le paramètre 'p_mkIdentifier'.
 *
 * @param[in]  p_mkIdentifier Ce paramètre contient l'identifiant de la mémoire où l'allocation doit être réalisée (\ref K_MK_PAGE_ID_SRAM ou \ref K_MK_PAGE_ID_SDRAM).
 * @param[out] p_mkAddr       Ce paramètre contient l'adresse de la page allouée.
 * @param[in]  p_mkTick       Ce paramètre contient la valeur du timeout. Il peut prendre les valeurs suivantes :
 *                            \li 0x0 - la fonction retourne immédiatement,
 *                            \li 0x1 à 0xFFFFFFFE - la fonction est bloquée pendant la durée spécifiée tant qu'auncune page n'est disponible,
 *                            \li 0xFFFFFFFF (\ref K_MK_TASK_WAIT_FOREVER) - la fonction est bloquée tant qu'aucune page n'est disponible.
 *                            Si la valeur "p_mkTick" est nulle et qu'aucune page mémoire n'est disponible, la fonction retourne immédiatement.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK           : la page mémoire a été allouée.
 *         \li \ref K_MK_ERROR_PARAM  : la page mémoire n'a pas été allouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : la page mémoire n'a pas été allouée car aucun bloc n'était disponible dans le timeout imparti.
 *         \li \ref K_MK_ERROR_ISR    : la page mémoire n'a pas été allouée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT  : la page mémoire n'a pas été allouée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_page_alloc ( T_mkPageIdentifier p_mkIdentifier, T_mkAddr* p_mkAddr, uint32_t p_mkTick );

/**
 * @fn T_mkCode mk_page_free ( T_mkPageIdentifier p_mkIdentifier, T_mkAddr* p_mkAddr );
 * @brief Cette fonction désalloue une page mémoire dans la mémoire identifiée par le paramètre 'p_mkIdentifier'. La page doit obligatoirement avoir été allouée avec
 *        la fonction \ref mk_page_alloc.
 *
 * @param[in] p_mkIdentifier Ce paramètre contient l'identifiant de la mémoire où l'allocation doit être réalisée (\ref K_MK_PAGE_ID_SRAM ou \ref K_MK_PAGE_ID_SDRAM).
 * @param[in] p_mkAddr       Ce paramètre contient l'adresse du bloc de mémoire alloué.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK          : la page mémoire a été désallouée.
 *         \li \ref K_MK_ERROR_PARAM : la page mémoire n'a pas été désallouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : la page mémoire n'a pas été désallouée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : la page mémoire n'a pas été désallouée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_page_free ( T_mkPageIdentifier p_mkIdentifier, T_mkAddr p_mkAddr );

/**
 *
 */

#endif


