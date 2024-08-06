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
* @file mk_termio_create.c
* @brief Définition de la fonction mk_termio_create.
* @date 9 juin 2019
*
*/

#include "mk_termio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_termio_initEvent ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation du champ d'événement permettant la synchronisation entre les terminaux et le dispatcher */
   l_result = mk_event_create ( &g_mkTermioSync.event, K_MK_ID_EVENT_SIGNAL, K_MK_AREA_PROTECTED, 0 );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_termio_createSystemTermio ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Création du dispatcher */
   l_result = mk_termio_create ( K_MK_NULL, K_MK_TERMIO_DISPATCHER_ID, K_MK_TERMIO_DISPATCHER_PRIORITY,
                                  mk_dispatcher_task, g_mkDispatcherStack, K_MK_DISPATCHER_STACK_SIZE );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_termio_createDriverTermio ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Création du terminal MMC */
   l_result = mk_termio_create ( K_MK_NULL, K_MK_TERMIO_MMC_ID, K_MK_TERMIO_TASK_PRIORITY,
                                 mk_mmc_task, g_mkMMCStackAddr, K_MK_MMC_STACK_SIZE );

   /* Si l'initialisation du terminal a réussi */
   if ( l_result == K_MK_OK )
   {
      /* Création du terminal I2C */
      l_result = mk_termio_create ( K_MK_NULL, K_MK_TERMIO_I2C1_ID, K_MK_TERMIO_TASK_PRIORITY,
                                    mk_i2c_task, g_mkI2CStackAddr, K_MK_I2C_STACK_SIZE );

      /* Si l'initialisation du terminal a réussi */
      if ( l_result == K_MK_OK )
      {
         /* Création du terminal GPIO */
         l_result = mk_termio_create ( K_MK_NULL, K_MK_TERMIO_GPIO_ID, K_MK_TERMIO_TASK_PRIORITY,
                                        mk_gpio_task, g_mkGPIOStackAddr, K_MK_GPIO_STACK_SIZE );
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

static T_mkCode mk_termio_createUSBTermio ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Création du terminal USB_OTGHS */
   l_result = mk_termio_create ( K_MK_NULL, K_MK_TERMIO_HCD_OTGHS_ID, K_MK_TERMIO_TASK_PRIORITY,
                                  mk_usbhs_taskDeviceMode, g_mkUSBHSDeviceStackAddr, K_MK_USBHS_DEVICE_STACK_SIZE );

   /* Si l'initialisation du terminal a réussi */
   if ( l_result == K_MK_OK )
   {
      /* Création du terminal USB_OTGFS */
      l_result = mk_termio_create ( K_MK_NULL, K_MK_TERMIO_HCD_OTGFS_ID, K_MK_TERMIO_TASK_PRIORITY,
                                     mk_usbfs_taskDeviceMode, g_mkUSBFSDeviceStackAddr, K_MK_USBFS_DEVICE_STACK_SIZE );

      /* Si l'initialisation du terminal a réussi */
      if ( l_result == K_MK_OK )
      {
         /* Création du terminal HID */
         l_result = mk_termio_create ( K_MK_NULL, K_MK_TERMIO_HID_ID, K_MK_TERMIO_TASK_PRIORITY,
                                        mk_hid_task, g_mkHIDStackAddr, K_MK_HID_STACK_SIZE );

         /* Si l'initialisation du terminal a réussi */
         if ( l_result == K_MK_OK )
         {
            /* Création du terminal MSC */
            l_result = mk_termio_create ( K_MK_NULL, K_MK_TERMIO_MSC_ID, K_MK_TERMIO_TASK_PRIORITY,
                                           mk_msc_task, g_mkMSCStackAddr, K_MK_MSC_STACK_SIZE );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_termio_createFileSystemTermio ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Pour le nombre de terminal à initialiser */
   for ( l_counter = 0 ; ( l_counter < ( K_MK_FILE_NUMBER_OF_TASKS - 1 ) ) && ( l_result == K_MK_OK ) ; l_counter++ )
   {
      /* Création des terminaux en relation avec le système de fichiers */
      l_result = mk_termio_create ( K_MK_NULL, K_MK_TERMIO_FILESYSTEM_ID + ( l_counter), K_MK_TERMIO_TASK_PRIORITY,
                                     mk_file_task, ( uint32_t* ) &g_mkFileStackAddr [ l_counter ] [ 0 ], K_MK_FILE_STACK_SIZE  );
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Création du terminal du système de fichiers partagés */
      l_result = mk_termio_create ( K_MK_NULL, K_MK_TERMIO_FILESYSTEM_ID + ( l_counter), K_MK_TERMIO_TASK_PRIORITY,
                                     mk_file_taskShared, ( uint32_t* ) &g_mkFileStackAddr [ l_counter ] [ 0 ], K_MK_FILE_STACK_SIZE );
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

T_mkCode mk_termio_init ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation du gestionnaire de référencement des terminaux. */
   mk_termio_initHandler ( );

   /* Initialisation du gestionnaire d'allocation dynamique des terminaux */
   l_result = mk_termio_createHeap ( );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de l'événement permettant la synchronisation des */
      /* terminaux au démarrage. */
      l_result = mk_termio_initEvent ( );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Création des terminaux système (dispatcher) */
         l_result = mk_termio_createSystemTermio ( );

         /* Si l'initialisation a réussi */
         if ( l_result == K_MK_OK )
         {
            /* Création des terminaux USB */
            l_result = mk_termio_createUSBTermio ( );

            /* Si l'initialisation a réussi */
            if ( l_result == K_MK_OK )
            {
               /* Création des terminaux I2C, MMC, ...  */
               l_result = mk_termio_createDriverTermio ( );

               /* Si l'initialisation a réussi */
               if ( l_result == K_MK_OK )
               {
                  /* Création des terminaux dédiés au système de fichiers */
                  l_result = mk_termio_createFileSystemTermio ( );
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

   /* Retour */
   return ( l_result );
}




