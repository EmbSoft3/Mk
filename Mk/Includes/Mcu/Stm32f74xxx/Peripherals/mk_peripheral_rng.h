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
* @file mk_peripheral_rng.h
* @brief Déclaration des fonctions dédiées au périphérique RNG.
* @date 30 mai 2020
*
*/

#ifndef MK_PERIPHERAL_RNG_H
#define MK_PERIPHERAL_RNG_H

/**
 * @fn void rng_enable ( void );
 * @brief Cette fonction active le périphérique RNG.
 * @return Sans objet.
 *
 */

void rng_enable ( void );

/**
 * @fn void rng_disable ( void );
 * @brief Cette fonction désactive le périphérique RNG.
 * @return Sans objet.
 *
 */

void rng_disable ( void );

/**
 * @fn void rng_enableInterrupt ( void );
 * @brief Cette fonction active les interruptions RNG.
 * @return Sans objet.
 *
 */

void rng_enableInterrupt ( void );

/**
 * @fn void rng_disableInterrupt ( void );
 * @brief Cette fonction désactive les interruptions RNG.
 * @return Sans objet.
 *
 */

void rng_disableInterrupt ( void );

/**
 * @fn void rng_getStatus ( uint32_t p_status );
 * @brief Cette fonction retourne un ou plusieurs statuts du périphérique RNG.
 *
 * @param[in] p_status Ce paramètre est un masque contenant l'identifiant des statuts à
 *                     retourner. Une combinaison des constantes suivantes peut être
 *                     utilisées : \ref K_RNG_SEED_ERROR_INTERRUPT_STATUS, \ref K_RNG_CLOCK_ERROR_INTERRUPT_STATUS,
 *                     \ref K_RNG_SEED_ERROR_CURRENT_STATUS, \ref K_RNG_CLOCK_ERROR_CURRENT_STATUS et
 *                     \ref K_RNG_READY_STATUS
 *
 * @return La valeur d'un ou plusieurs statuts du périphérique RNG.
 *
 */

uint32_t rng_getStatus ( uint32_t p_status );

/**
 * @fn void rng_clearStatus ( uint32_t p_status );
 * @brief Cette fonction réinitialise un ou plusieurs statuts du périphérique RNG.
 *
 * @param[in] p_status Ce paramètre est un masque contenant l'identifiant des statuts à
 *                     retourner. Une combinaison des constantes suivantes peut être
 *                     utilisées : \ref K_RNG_SEED_ERROR_INTERRUPT_STATUS et \ref K_RNG_CLOCK_ERROR_INTERRUPT_STATUS
 *
 * @return Sans objet.
 *
 */

void rng_clearStatus ( uint32_t p_status );

/**
 * @fn uint32_t rng_get ( void );
 * @brief Cette fonction retourne un mot 32 bits aléatoire.
 * @return La valeur d'un mot aléatoire 32 bits.
 *
 */

uint32_t rng_get ( void );

/**
 *
 */

#endif

