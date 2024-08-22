/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_chromart_handleRequest.c
* @brief Définition de la fonction mk_chromart_handleRequest.
* @date 1 nov. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_chromart_handleRequest ( T_mkTask* p_task, T_mkChromartRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si la requête est de type FILL */
   if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_FILL )
   {
      l_result = mk_chromart_fill ( p_request );
   }

   /* Sinon si la requête est de type COPY */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_COPY )
   {
      l_result = mk_chromart_copy ( p_task, p_request );
   }

   /* Sinon si la requête est de type INVCOPY */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_INVCOPY )
   {
      l_result = mk_chromart_invcopy ( p_task, p_request );
   }

   /* Sinon si la requête est de type BLEND */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_BLEND )
   {
      l_result = mk_chromart_blend ( p_request );
   }

   /* Sinon si la requête est de type WRITE */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_WRITE )
   {
      l_result = mk_chromart_write ( p_request );
   }

   /* Sinon si la requête est de type STRING */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_STRING )
   {
      l_result = mk_chromart_drawString ( p_request );
   }

   /* Sinon si la requête est de type CIRCLE */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_CIRCLE )
   {
      l_result = mk_chromart_drawCircle ( p_request );
   }

   /* Sinon si la requête est de type LINE */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_LINE )
   {
      l_result = mk_chromart_drawLine ( p_request );
   }

   /* Sinon si la requête est de type TRIANGLE */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_TRIANGLE )
   {
      l_result = mk_chromart_drawTriangle ( p_request );
   }

   /* Sinon si la requête est de type ROUNDRECT */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_ROUNDRECT )
   {
      l_result = mk_chromart_drawRoundRect ( p_request );
   }

   /* Sinon si la requête est de type PLOT */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_PLOT )
   {
      l_result = mk_chromart_plot ( p_request );
   }

   /* Sinon si la requête est de type LOAD */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_LOAD )
   {
      l_result = mk_chromart_load ( p_task, p_request );
   }

   /* Sinon si la requête est de type ALPHA */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_ALPHA )
   {
      mk_chromart_alpha ( p_request );
   }

   /* Sinon si la requête est de type SCREENSHOT */
   else if ( p_request->id == K_MK_DISPLAY_REQUEST_CHROMART_SCREENSHOT )
   {
      l_result = mk_chromart_screenshot ( );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


