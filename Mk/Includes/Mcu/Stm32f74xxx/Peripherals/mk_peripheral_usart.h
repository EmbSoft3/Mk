/**
*
* @copyright Copyright (C) 2018 RENARD Mathieu. All rights reserved.
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
* @file mk_peripheral_usart.h
* @brief Déclaration des fonctions dédiées au périphérique USART.
* @date 1 avr. 2018
* @todo Implémenter et écrire la documentation du périphérique USART.
*
*/

#ifndef MK_PERIPHERAL_USART_H
#define MK_PERIPHERAL_USART_H

void usart_disable ( void_t p_addr );
void usart_disableParity ( void_t p_addr );
void usart_disableRx ( void_t p_addr );
void usart_disableTx ( void_t p_addr );
void usart_disableRxInterrupt ( void_t p_addr );

void usart_enable ( void_t p_addr );
void usart_enableParity ( void_t p_addr );
void usart_enableRx ( void_t p_addr );
void usart_enableTx ( void_t p_addr );
void usart_enableRxInterrupt ( void_t p_addr );

void usart_setBaudRate ( void_t p_addr, uint32_t p_baud );
void usart_setFlow ( void_t p_addr, uint32_t p_flow );
void usart_setFrame ( void_t p_addr, uint32_t p_frame );
void usart_setParity ( void_t p_addr, uint32_t p_parity );
void usart_swap ( void_t p_addr );
void usart_write ( void_t p_addr, uint32_t p_data );
void usart_clearFlag ( void_t p_addr, uint32_t p_flag );

uint32_t usart_getRxFullFlag ( void_t p_addr );
uint32_t usart_getTxEmptyFlag ( void_t p_addr );
uint32_t usart_read ( void_t p_addr );


/**
 *
 */

#endif

