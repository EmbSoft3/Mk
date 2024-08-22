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
* @file mk_hid_parseError.c
* @brief Définition de la fonction mk_hid_parseError.
* @date 13 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_parseError ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_error != K_MK_NULL ) )
   {
      /* Vérification qu'aucune déclaration inconnue ne soit présente */
      l_result = mk_hid_checkUnkwnownDeclaration ( p_hidDevice, p_error );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
      {
         /* Vérification qu'aucune valeur invalide ne soit présente */
         l_result = mk_hid_checkInvalidValue ( p_hidDevice, p_error );

         /* Si aucune erreur ne s'est produite */
         if ( ( l_result == K_MK_OK ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
         {
            /* Vérification que l'ensemble des déclarations obligatoires soient présentes */
            l_result = mk_hid_checkMissingDeclaration ( p_hidDevice, p_error );

            /* Si aucune erreur ne s'est produite */
            if ( ( l_result == K_MK_OK ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
            {
               /* Vérification qu'aucune déclaration invalide ne soit présente */
               l_result = mk_hid_checkInvalidDeclaration ( p_hidDevice, p_error );

               /* Si aucune erreur ne s'est produite */
               if ( ( l_result == K_MK_OK ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
               {
                  /* Vérification qu'aucun couplage de déclaration invalide ne soit présent */
                  l_result = mk_hid_checkCouplingDeclaration ( p_hidDevice, p_error );

                  /* Si aucune erreur ne s'est produite */
                  if ( ( l_result == K_MK_OK ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
                  {
                     /* Vérification que l'ensemble des déclarations soient imbriquées correctement */
                     l_result = mk_hid_checkNestingDeclaration ( p_hidDevice, p_error );

                     /* Si aucune erreur ne s'est produite */
                     if ( ( l_result == K_MK_OK ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
                     {
                        /* Vérification de la présence des déclarations applicatives */
                        l_result = mk_hid_checkApplicationDeclaration ( p_hidDevice, p_error );

                        /* Si aucune erreur ne s'est produite */
                        if ( ( l_result == K_MK_OK ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
                        {
                           /* Vérification de la validé des gammes de valeurs */
                           l_result = mk_hid_checkOutOfRange ( p_hidDevice, p_error );
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
