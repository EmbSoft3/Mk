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
* @file mk_system_memory_initQSPI.c
* @brief Définition de la fonction mk_system_memory_initQSPI.
* @date 3 mai 2020
*
*/

#include "mk_system_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_wait ( void )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Effectue */
   do
   {
      /* Récupération du statut du FIFO */
      l_result = qspi_getStatus ( K_QSPI_TRANSFER_COMPLETE_STATUS );

      /* Actualisation du compteur */
      l_counter++;

   /* Tant que le nombre d'octets demandés n'a pas été reçu */
   } while ( ( l_result != K_QSPI_TRANSFER_COMPLETE ) && ( l_counter < K_MICRON_N25Q512A_TIMEOUT ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_abort ( void )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Arrêt du transfert */
   qspi_abort ( );

   /* Effectue */
   do
   {
      /* Récupération du statut de l'opération */
      l_result = qspi_getAbortStatus ( );

      /* Actualisation du compteur */
      l_counter++;

   /* Tant que l'arrêt du transfert n'est pas terminé */
   } while ( ( l_result == K_QSPI_ABORT_IN_PROGRESS ) && ( l_counter < K_MICRON_N25Q512A_TIMEOUT ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_writeInstruction ( uint32_t p_instruction, uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Récupération du statut du périphérique */
   l_result = qspi_getStatus ( K_QSPI_BUSY_STATUS );

   /* Si aucune opération n'est en cours */
   if ( l_result == K_QSPI_IDLE )
   {
      /* Configuration du nombre de données à récupérer */
      qspi_setTransferSize ( 0 );

      /* Si la transmission de l'instruction est en mode 'SINGLE' */
      if ( p_mode == K_QSPI_INSTRUCTION_SINGLE_MODE )
      {
         /* Transmission de l'instruction 'WriteEnable' */
         qspi_write ( K_QSPI_SDR_MODE, MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                      K_QSPI_INSTRUCTION_SINGLE_MODE, K_QSPI_ADDRESS_NO_LINE_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                      K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_NO_LINE_MODE );
      }

      /* Sinon si la transmission de l'instruction est en mode 'DUAL' */
      else if ( p_mode == K_QSPI_INSTRUCTION_DUAL_MODE )
      {
         /* Transmission de l'instruction 'WriteEnable' */
         qspi_write ( K_QSPI_SDR_MODE, MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                      K_QSPI_INSTRUCTION_DUAL_MODE, K_QSPI_ADDRESS_NO_LINE_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                      K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_NO_LINE_MODE );
      }

      /* Sinon (mode QUAD) */
      else
      {
         /* Transmission de l'instruction 'WriteEnable' */
         qspi_write ( K_QSPI_SDR_MODE, MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                      K_QSPI_INSTRUCTION_QUAD_MODE, K_QSPI_ADDRESS_NO_LINE_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                      K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_NO_LINE_MODE );
      }

      /* Attendre tant que le nombre d'octets demandés n'a pas été reçu */
      l_result = mk_system_memory_wait ( );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si l'opération a échoué */
   if ( l_result != K_QSPI_TRANSFER_COMPLETE )
   {
      /* Arrêt du transfert */
      l_result = mk_system_memory_abort ( );
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_QSPI_OK;
   }

   /* Réinitialisation du drapeau indiquant la fin du transfert */
   qspi_clearStatus ( K_QSPI_TRANSFER_COMPLETE_STATUS );

   /* Réinitialisation du drapeau indiquant une erreur de transfert */
   qspi_clearStatus ( K_QSPI_TRANSFER_ERROR_STATUS );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_readRegister ( T_mkAddr p_register, uint32_t p_instruction, uint32_t p_mode, uint32_t p_size )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Déclaration d'une variable de travail */
   uint8_t* l_register = p_register;

   /* Récupération du statut du périphérique */
   l_result = qspi_getStatus ( K_QSPI_BUSY_STATUS );

   /* Si aucune opération n'est en cours */
   if ( l_result == K_QSPI_IDLE )
   {
      /* Configuration du nombre de données à récupérer */
      qspi_setTransferSize ( p_size - 1 );

      /* Si la transmission de l'instruction est en mode 'SINGLE' */
      if ( p_mode == K_QSPI_INSTRUCTION_SINGLE_MODE )
      {
         /* Transmission de l'instruction demandée */
         qspi_read ( K_QSPI_SDR_MODE, MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                     K_QSPI_INSTRUCTION_SINGLE_MODE, K_QSPI_ADDRESS_NO_LINE_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                     K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_SINGLE_MODE );
      }

      /* Sinon si la transmission de l'instruction est en mode 'DUAL' */
      else if ( p_mode == K_QSPI_INSTRUCTION_DUAL_MODE )
      {
         /* Transmission de l'instruction demandée */
         qspi_read ( K_QSPI_SDR_MODE, MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                     K_QSPI_INSTRUCTION_DUAL_MODE, K_QSPI_ADDRESS_NO_LINE_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                     K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_DUAL_MODE );
      }

      /* Sinon (mode QUAD) */
      else
      {
         /* Transmission de l'instruction demandée */
         qspi_read ( K_QSPI_SDR_MODE, MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                     K_QSPI_INSTRUCTION_QUAD_MODE, K_QSPI_ADDRESS_NO_LINE_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                     K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_QUAD_MODE );
      }

      /* Attendre tant que le nombre d'octets demandés n'a pas été reçu */
      l_result = mk_system_memory_wait ( );

      /* Si l'opération a échoué */
      if ( l_result != K_QSPI_TRANSFER_COMPLETE )
      {
         /* Arrêt du transfert */
         l_result = mk_system_memory_abort ( );
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_QSPI_OK;

         /* Pour le nombre de données à lire */
         for ( l_counter = 0 ; l_counter < p_size ; l_counter++ )
         {
            /* Lecture de la donnée courante */
            *l_register = qspi_readByte ( );

            /* Actualisation du pointeur */
            l_register++;
         }
      }

      /* Réinitialisation du drapeau indiquant la fin du transfert */
      qspi_clearStatus ( K_QSPI_TRANSFER_COMPLETE_STATUS );

      /* Réinitialisation du drapeau indiquant une erreur de transfert */
      qspi_clearStatus ( K_QSPI_TRANSFER_ERROR_STATUS );
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

static uint32_t mk_system_memory_writeRegister ( T_mkAddr p_register, uint32_t p_instruction, uint32_t p_mode, uint32_t p_size )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'une variable de travail */
   uint8_t* l_register = p_register;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Récupération du statut du périphérique */
   l_result = qspi_getStatus ( K_QSPI_BUSY_STATUS );

   /* Si aucune opération n'est en cours */
   if ( l_result == K_QSPI_IDLE )
   {
      /* Configuration du nombre de données à transmettre */
      qspi_setTransferSize ( p_size - 1 );

      /* Si la transmission de l'instruction est en mode 'SINGLE' */
      if ( p_mode == K_QSPI_INSTRUCTION_SINGLE_MODE )
      {
         /* Transmission de l'instruction demandée */
         qspi_write ( K_QSPI_SDR_MODE, MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                      K_QSPI_INSTRUCTION_SINGLE_MODE, K_QSPI_ADDRESS_NO_LINE_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                      K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_SINGLE_MODE );
      }

      /* Sinon si la transmission de l'instruction est en mode 'DUAL' */
      else if ( p_mode == K_QSPI_INSTRUCTION_DUAL_MODE )
      {
         /* Transmission de l'instruction demandée */
         qspi_write ( K_QSPI_SDR_MODE, MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                      K_QSPI_INSTRUCTION_DUAL_MODE, K_QSPI_ADDRESS_NO_LINE_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                      K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_DUAL_MODE );
      }

      /* Sinon (QUADMODE) */
      else
      {
         /* Transmission de l'instruction demandée */
         qspi_write ( K_QSPI_SDR_MODE, MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                      K_QSPI_INSTRUCTION_QUAD_MODE, K_QSPI_ADDRESS_NO_LINE_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                      K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_QUAD_MODE );
      }

      /* Pour le nombre de données à écrire */
      for ( l_counter = 0 ; l_counter < p_size ; l_counter++ )
      {
         /* Ecriture d'un octet sur le bus QSPI */
         qspi_writeByte ( *l_register );

         /* Actualisation du pointeur */
         l_register++;
      }

      /* Attendre tant que le nombre d'octets demandés n'a pas été transmis */
      l_result = mk_system_memory_wait ( );

      /* Si l'opération a échoué */
      if ( l_result != K_QSPI_TRANSFER_COMPLETE )
      {
         /* Arrêt du transfert */
         l_result = mk_system_memory_abort ( );
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_QSPI_OK;
      }

      /* Réinitialisation du drapeau indiquant la fin du transfert */
      qspi_clearStatus ( K_QSPI_TRANSFER_COMPLETE_STATUS );

      /* Réinitialisation du drapeau indiquant une erreur de transfert */
      qspi_clearStatus ( K_QSPI_TRANSFER_ERROR_STATUS );
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

static uint32_t mk_system_memory_setDummyCycle ( uint32_t p_mode, uint32_t p_numberOfDummyClockCycles )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'un registre de configuration de type volatile */
   T_MicronN25Q512A_ConfigurationRegister l_configurationRegister = { 0 };

   /* Lecture du registre de configuration */
   l_result = mk_system_memory_readRegister ( &l_configurationRegister, MK_MICRON_N25Q512A_OPCODE_READ_CONFIGURATION, p_mode, 1 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Si le nombre de dummyCycle doit être configuré */
      if ( l_configurationRegister.field.dummyClockCycle != p_numberOfDummyClockCycles )
      {
         /* Autorisation d'une écriture */
         l_result = mk_system_memory_writeInstruction ( MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE, p_mode );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_QSPI_OK )
         {
            /* Actualisation de la valeur du registre de configuration */
            l_configurationRegister.field.dummyClockCycle = ( uint8_t ) ( p_numberOfDummyClockCycles & 0xF ); ;

            /* Ecriture du registre de configuration */
            l_result = mk_system_memory_writeRegister ( &l_configurationRegister, MK_MICRON_N25Q512A_OPCODE_WRITE_CONFIGURATION, p_mode, 1 );

            /* Si l'opération a réussi */
            if ( l_result == K_QSPI_OK )
            {
               /* Vérification de la nouvelle valeur du registre */
               /* Si la commande a correctement été exécutée, la lecture doit être réalisée en QUADMODE */
               l_result = mk_system_memory_readRegister ( &l_configurationRegister, MK_MICRON_N25Q512A_OPCODE_READ_CONFIGURATION, p_mode, 1 );

               /* Si le mode 4 fils n'est pas actif */
               if ( l_configurationRegister.field.dummyClockCycle != p_numberOfDummyClockCycles )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_QSPI_KO;
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_enableExtendedMode ( uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Autorisation d'une écriture */
   l_result = mk_system_memory_writeInstruction ( MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE, p_mode );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Activation de l'adressage 32 bits */
      l_result = mk_system_memory_writeInstruction ( MK_MICRON_N25Q512A_OPCODE_ENTER_4BYTE_ADDRESS_MODE, p_mode );
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

static uint32_t mk_system_memory_disableExtendedMode ( uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Autorisation d'une écriture */
   l_result = mk_system_memory_writeInstruction ( MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE, p_mode );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Désactivation de l'adressage 32 bits */
      l_result = mk_system_memory_writeInstruction ( MK_MICRON_N25Q512A_OPCODE_EXIT_4BYTE_ADDRESS_MODE, p_mode );
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

static uint32_t mk_system_memory_getMode ( uint32_t* p_mode )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'une variable de travail */
   uint8_t l_id = 0;

   /* La mémoire QSPI possède un registre de type non volatile définissant le mode de fonctionnement au démarrage de la mémoire. */
   /* Le but de cette fonction est de déterminer la valeur du mode initial (SINGLE, DUAL, QUAD). */
   /* Pour ce faire, on récupére l'identifiant fabricant de la mémoire et on le compare à une valeur prédéfinie. */

   /* Initialisation de la variable de retour */
   *p_mode = K_QSPI_INSTRUCTION_SINGLE_MODE;

   /* Lecture de l'identifiant fabricant en mode 'SINGLE' */
   l_result = mk_system_memory_readRegister ( &l_id, MK_MICRON_N25Q512A_OPCODE_READ_ID, K_QSPI_INSTRUCTION_SINGLE_MODE, 1 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Si le mode 'SINGLE' n'est pas le mode recherché */
      if ( l_id != MK_MICRON_N25Q512A_MANUFACTURER_ID )
      {
         /* Initialisation de la variable de retour */
         *p_mode = K_QSPI_INSTRUCTION_DUAL_MODE;

         /* Lecture de l'identifiant fabricant en mode 'DUAL' */
         l_result = mk_system_memory_readRegister ( &l_id, MK_MICRON_N25Q512A_OPCODE_READ_ID, K_QSPI_INSTRUCTION_DUAL_MODE, 1 );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_QSPI_OK )
         {
            /* Si le mode 'DUAL' n'est pas le mode recherché */
            if ( l_id != MK_MICRON_N25Q512A_MANUFACTURER_ID )
            {
               /* Initialisation de la variable de retour */
               *p_mode = K_QSPI_INSTRUCTION_QUAD_MODE;

               /* Lecture de l'identifiant fabricant en mode 'QUAD' */
               l_result = mk_system_memory_readRegister ( &l_id, MK_MICRON_N25Q512A_OPCODE_READ_ID, K_QSPI_INSTRUCTION_QUAD_MODE, 1 );

               /* Si le mode 'QUAD' n'est pas le mode recherché */
               if ( l_id != MK_MICRON_N25Q512A_MANUFACTURER_ID )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_QSPI_KO;
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_enableSingleModeNV ( uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'un registre de statut */
   T_MicronN25Q512A_StatusRegister l_statusRegister = { 0 };

   /* Déclaration d'un registre de configuration de type 'Enhanced' */
   T_MicronN25Q512A_NVConfigurationRegister l_nvConfigurationRegister = { 0 };

   /* Lecture du registre de configuration non volatile */
   l_result = mk_system_memory_readRegister ( &l_nvConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_READ_NV_CONFIGURATION, p_mode, 2 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Si le mode 1 fils est désactivé, il faut l'activer */
      if ( ( l_nvConfigurationRegister.field.quadIO == 0 ) || ( l_nvConfigurationRegister.field.dualIO == 0 ) )
      {
         /* Autorisation d'une écriture */
         l_result = mk_system_memory_writeInstruction ( MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE, p_mode );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_QSPI_OK )
         {
            /* Actualisation de la valeur du registre de configuration */
            l_nvConfigurationRegister.field.quadIO = 1;
            l_nvConfigurationRegister.field.dualIO = 1;

            /* Ecriture du registre de configuration */
            l_result = mk_system_memory_writeRegister ( &l_nvConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_WRITE_NV_CONFIGURATION, p_mode, 2 );

            /* Si l'opération a réussi */
            if ( l_result == K_QSPI_OK )
            {
               /* Effectue */
               do
               {
                  /* Lecture du registre de statut pour savoir si l'écriture est terminée */
                  l_result = mk_system_memory_readRegister ( &l_statusRegister, MK_MICRON_N25Q512A_OPCODE_READ_STATUS, p_mode, 1 );

                  /* Attente 1ms */
                  mk_utils_waitus ( 1000 );

                  /* Actualisation d'un compteur */
                  l_counter = ( uint32_t ) ( l_counter + 1 );

               /* Tant que le registre de configuration non volatile est en cours d'écriture */
               } while ( ( l_statusRegister.field.writeInProgress == 1 ) && ( l_counter < 25 ) );

               /* Vérification de la nouvelle valeur du registre */
               l_result = mk_system_memory_readRegister ( &l_nvConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_READ_NV_CONFIGURATION, p_mode, 2 );

               /* Si le mode 1 fils n'est pas actif */
               if ( ( l_nvConfigurationRegister.field.quadIO != 1 ) || ( l_nvConfigurationRegister.field.dualIO != 1 ) )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_QSPI_KO;
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_enableQuadModeNV ( uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'un registre de statut */
   T_MicronN25Q512A_StatusRegister l_statusRegister = { 0 };

   /* Déclaration d'un registre de configuration de type 'Enhanced' */
   T_MicronN25Q512A_NVConfigurationRegister l_nvConfigurationRegister = { 0 };

   /* Lecture du registre de configuration non volatile */
   l_result = mk_system_memory_readRegister ( &l_nvConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_READ_NV_CONFIGURATION, p_mode, 2 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Si le mode 4 fils est désactivé, alors il faut l'activer */
      if ( ( l_nvConfigurationRegister.field.quadIO == 1 ) || ( l_nvConfigurationRegister.field.dualIO == 0 ) )
      {
         /* Autorisation d'une écriture */
         l_result = mk_system_memory_writeInstruction ( MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE, p_mode );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_QSPI_OK )
         {
            /* Actualisation de la valeur du registre de configuration */
            l_nvConfigurationRegister.field.quadIO = 0;
            l_nvConfigurationRegister.field.dualIO = 1;

            /* Ecriture du registre de configuration */
            l_result = mk_system_memory_writeRegister ( &l_nvConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_WRITE_NV_CONFIGURATION, p_mode, 2 );

            /* Si l'opération a réussi */
            if ( l_result == K_QSPI_OK )
            {
               /* Effectue */
               do
               {
                  /* Lecture du registre de statut pour savoir si l'écriture est terminée */
                  l_result = mk_system_memory_readRegister ( &l_statusRegister, MK_MICRON_N25Q512A_OPCODE_READ_STATUS, p_mode, 1 );

                  /* Attente 1ms (100 µs min) */
                  mk_utils_waitus ( 1000 );

                  /* Actualisation d'un compteur */
                  l_counter = ( uint32_t ) ( l_counter + 1 );

               /* Tant que le registre de configuration non volatile est en cours d'écriture */
               } while ( ( l_statusRegister.field.writeInProgress == 1 ) && ( l_counter < 25 ) );

               /* Vérification de la nouvelle valeur du registre */
               l_result = mk_system_memory_readRegister ( &l_nvConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_READ_NV_CONFIGURATION, p_mode, 2 );

               /* Si le mode 4 fils n'est pas actif */
               if ( ( l_nvConfigurationRegister.field.quadIO != 0 ) || ( l_nvConfigurationRegister.field.dualIO != 1 ) )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_QSPI_KO;
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_enableSingleMode ( uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'un registre de configuration de type 'Enhanced' */
   T_MicronN25Q512A_EnhancedConfigurationRegister l_enhancedConfigurationRegister = { 0 };

   /* Lecture du registre de configuration non volatile */
   l_result = mk_system_memory_readRegister ( &l_enhancedConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_READ_ENHANCED_CONFIGURATION, p_mode, 1 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Si le mode 1 fil est désactivé, alors il faut l'activer */
      if ( ( l_enhancedConfigurationRegister.field.quadIO == 0 ) || ( l_enhancedConfigurationRegister.field.dualIO == 0 ) )
      {
         /* Autorisation d'une écriture */
         l_result = mk_system_memory_writeInstruction ( MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE, p_mode );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_QSPI_OK )
         {
            /* Actualisation de la valeur du registre de configuration */
            l_enhancedConfigurationRegister.field.quadIO = 1;
            l_enhancedConfigurationRegister.field.dualIO = 1;

            /* Ecriture du registre de configuration */
            l_result = mk_system_memory_writeRegister ( &l_enhancedConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_WRITE_ENHANCED_CONFIGURATION, p_mode, 1 );

            /* Si l'opération a réussi */
            if ( l_result == K_QSPI_OK )
            {
               /* Vérification de la nouvelle valeur du registre */
               /* Si la commande a correctement été exécutée, la lecture doit être réalisée en mode 1 fil */
               l_result = mk_system_memory_readRegister ( &l_enhancedConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_READ_ENHANCED_CONFIGURATION, K_QSPI_INSTRUCTION_SINGLE_MODE, 1 );

               /* Si le mode 1 fils n'est pas actif */
               if ( ( l_enhancedConfigurationRegister.field.quadIO != 1 ) || ( l_enhancedConfigurationRegister.field.dualIO != 1 ) )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_QSPI_KO;
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_enableQuadMode ( uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'un registre de configuration de type 'Enhanced' */
   T_MicronN25Q512A_EnhancedConfigurationRegister l_enhancedConfigurationRegister = { 0 };

   /* Lecture du registre de configuration non volatile */
   l_result = mk_system_memory_readRegister ( &l_enhancedConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_READ_ENHANCED_CONFIGURATION, p_mode, 1 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Si le mode 4 fils est désactivé, alors il faut l'activer */
      if ( ( l_enhancedConfigurationRegister.field.quadIO == 1 ) || ( l_enhancedConfigurationRegister.field.dualIO == 0 ) )
      {
         /* Autorisation d'une écriture */
         l_result = mk_system_memory_writeInstruction ( MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE, p_mode );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_QSPI_OK )
         {
            /* Actualisation de la valeur du registre de configuration */
            l_enhancedConfigurationRegister.field.quadIO = 0;
            l_enhancedConfigurationRegister.field.dualIO = 1;

            /* Ecriture du registre de configuration */
            l_result = mk_system_memory_writeRegister ( &l_enhancedConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_WRITE_ENHANCED_CONFIGURATION, p_mode, 1 );

            /* Si l'opération a réussi */
            if ( l_result == K_QSPI_OK )
            {
               /* Vérification de la nouvelle valeur du registre */
               /* Si la commande a correctement été exécutée, la lecture doit être réalisée en mode 4 fils */
               l_result = mk_system_memory_readRegister ( &l_enhancedConfigurationRegister, MK_MICRON_N25Q512A_OPCODE_READ_ENHANCED_CONFIGURATION, K_QSPI_INSTRUCTION_QUAD_MODE, 1 );

               /* Si le mode 4 fils n'est pas actif */
               if ( ( l_enhancedConfigurationRegister.field.quadIO != 0 ) || ( l_enhancedConfigurationRegister.field.dualIO != 1 ) )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_QSPI_KO;
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_singleModeInitializationSequence ( void )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'une variable stockant le mode de fonctionnement de la mémoire */
   uint32_t l_mode = K_QSPI_INSTRUCTION_SINGLE_MODE;

   /* Récupération du mode de fonctionnement de la mémoire */
   l_result = mk_system_memory_getMode ( &l_mode );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Configuration du nombre de 'DummyCycle' */
      l_result = mk_system_memory_setDummyCycle ( l_mode, 0 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Configuration de la mémoire de manière à la faire fonctionner en mode 1 fil */
      /* à chaque démarrage */
      l_result = mk_system_memory_enableSingleModeNV ( l_mode );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Activation du mode 1 fil */
      l_result = mk_system_memory_enableSingleMode ( l_mode );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Activation de l'adressage étendu */
      l_result = mk_system_memory_disableExtendedMode ( l_mode );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Le mode 1 fil a été activé et configuré dans les séquences précédentes */
      /* On vérifie la prise en compte de celui-ci en lisant l'identifiant du fabricant */
      l_result = mk_system_memory_getMode ( &l_mode );

      /* Si le mode 1 fil n'est pas actif */
      if ( l_mode != K_QSPI_INSTRUCTION_SINGLE_MODE )
      {
         /* Actualisation de la variable de retour */
         l_result = K_QSPI_KO;
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

   /* Si le mode 1 fil est actif */
   if ( l_result == K_QSPI_OK )
   {
      /* Activation du mode 'MemoryMap' */
      qspi_map ( K_QSPI_SDR_MODE, 0, MK_MICRON_N25Q512A_OPCODE_READ |
                 K_QSPI_INSTRUCTION_SINGLE_MODE, K_QSPI_ADDRESS_SINGLE_MODE | K_QSPI_ADDRESS_SIZE_24BITS,
                 K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_SINGLE_MODE );

      /* Activation des interruptions */
      qspi_enableInterrupt ( K_QSPI_TRANSFER_COMPLETE_INTERRUPT | K_QSPI_TRANSFER_ERROR_INTERRUPT );
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_QSPI_KO;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_quadModeInitializationSequence ( void )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'une variable stockant le mode de fonctionnement de la mémoire */
   uint32_t l_mode = K_QSPI_INSTRUCTION_QUAD_MODE;

   /* Récupération du mode de fonctionnement de la mémoire */
   l_result = mk_system_memory_getMode ( &l_mode );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Configuration du nombre de 'DummyCycle' */
      l_result = mk_system_memory_setDummyCycle ( l_mode, 0 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Configuration de la mémoire de manière à la faire fonctionner en mode 4 fils */
      /* à chaque démarrage */
      l_result = mk_system_memory_enableQuadModeNV ( l_mode );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Configuration du nombre de 'DummyCycle' */
      l_result = mk_system_memory_setDummyCycle ( l_mode, MK_MICRON_N25Q512A_DUMMY_CYCLE );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Activation du mode 4 fils (si non configuré) */
      l_result = mk_system_memory_enableQuadMode ( l_mode );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Activation de l'adressage étendu */
      l_result = mk_system_memory_enableExtendedMode ( l_mode );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Le mode 4 fils a été activé et configuré dans les séquences précédentes */
      /* On vérifie la prise en compte de celui-ci en lisant l'identifiant du fabricant */
      l_result = mk_system_memory_getMode ( &l_mode );

      /* Si le mode 4 fils n'est pas actif */
      if ( l_mode != K_QSPI_INSTRUCTION_QUAD_MODE )
      {
         /* Actualisation de la variable de retour */
         l_result = K_QSPI_KO;
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

   /* Si le mode 4 fils n'est pas actif */
   if ( l_result == K_QSPI_OK )
   {
      /* Activation du mode 'MemoryMap' */
      qspi_map ( K_QSPI_SDR_MODE, MK_MICRON_N25Q512A_DUMMY_CYCLE, MK_MICRON_N25Q512A_OPCODE_4BYTE_FAST_READ |
                 K_QSPI_INSTRUCTION_QUAD_MODE, K_QSPI_ADDRESS_QUAD_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                 K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_QUAD_MODE );

      /* Activation des interruptions */
      qspi_enableInterrupt ( K_QSPI_TRANSFER_COMPLETE_INTERRUPT | K_QSPI_TRANSFER_ERROR_INTERRUPT );
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_QSPI_KO;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_singleModeProgrammingSequence ( void )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'une variable stockant le mode de fonctionnement de la mémoire */
   uint32_t l_mode = K_QSPI_INSTRUCTION_SINGLE_MODE;

   /* Récupération du mode de fonctionnement de la mémoire */
   l_result = mk_system_memory_getMode ( &l_mode );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Configuration du nombre de 'DummyCycle' */
      l_result = mk_system_memory_setDummyCycle ( l_mode, MK_MICRON_N25Q512A_DUMMY_CYCLE );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Activation du mode 1 fil */
      l_result = mk_system_memory_enableSingleMode ( l_mode );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_QSPI_OK )
   {
      /* Le mode 1 fil a été activé et configuré dans les séquences précédentes */
      /* On vérifie la prise en compte de celui-ci en lisant l'identifiant du fabricant */
      l_result = mk_system_memory_getMode ( &l_mode );

      /* Si le mode 4 fils n'est pas actif */
      if ( l_mode != K_QSPI_INSTRUCTION_SINGLE_MODE )
      {
         /* Actualisation de la variable de retour */
         l_result = K_QSPI_KO;
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

static void mk_system_memory_enableQSPI ( void )
{
   /* Désactivation du périphérique QUADSPI */
   qspi_disable ( );

   /* Désactivation de la DMA */
   qspi_disableDma ( );

   /* Désactivation de toutes les interruptions */
   qspi_disableInterrupt ( K_QSPI_ALL_INTERRUPT );

   /* Configuration de la fréquence de l'horloge QUADSPI */
   /* Une fréquence supérieure entraine des erreurs de lecture ponctuelle. */
   /* F_CLOCK = F_AHB / 4 */
   qspi_setClock ( 5 );

   /* Activation du mode 'SingleFlash' */
   /* Adressage de la FLASH numéro 1 */
   qspi_enableSingleFlashMode ( K_QSPI_FLASH1 );

   /* Configuration du nombre de cycles d'horloge entre deux commandes */
   qspi_setChipSelectHighTime ( 1 );

   /* Configuration du niveau de repos de l'horloge */
   qspi_setIdleClockState ( K_QSPI_IDLE_CLOCK_HIGH );

   /* Configuration du point d'acquisation des données */
   qspi_setSampleEdge ( K_QSPI_DEFAULT_EDGE );

   /* Configuration du seuil de déclenchement de l'interruption FIFO */
   qspi_setFifoThresholdLevel ( 1 );

   /* Configuration de la taille de la FLASH */
   /* Mémoire de 64 MB */
   qspi_setFlashSize ( 25 );

   /* Activation du périphérique QUADSPI */
   qspi_enable ( );

   /* Attente 10ms */
   mk_utils_waitus ( 10000 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_system_memory_initQSPI ( uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Activation du périphérique QSPI */
   mk_system_memory_enableQSPI ( );

   /* Si le mode 1 fil doit être activé (obligatoire pour la programmation de la QSPI) */
   if ( p_mode == K_QSPI_INSTRUCTION_SINGLE_MODE )
   {
      /* Initialisation de la mémoire QSPI en mode 1 fil */
      l_result = mk_system_memory_singleModeInitializationSequence ( );
   }

   /* Sinon */
   else if ( p_mode == K_QSPI_INSTRUCTION_QUAD_MODE )
   {
      /* Initialisation de la mémoire QSPI en mode 4 fils */
      l_result = mk_system_memory_quadModeInitializationSequence ( );
   }

   /* Sinon */
   else
   {
      /* La programmation de la mémoire QSPI est réalisée directement par la sonde de programmation */
      /* Le script Startup.JLinkScript doit être exécuté au démarrage. */
      /* La méthodologie pour exécuter ce script est décrite à l'intérieur du fichier Startup.JLinkScript. */
      /* Si le message ERROR: Failed to erase sectors 0 @ address 0x90000000 (erase error) apparait alors la mémoire */
      /* n'est pas en mode 1 fil ou le script n'a pas été exécuté (2 options nécessaires -jlinkscriptfile et -JLinkDevicesXMLPath). */
      /* Le fichier exécutable contenant le code RAM déployé lors de la programmation est STM32F746G_QSPI.elf */

      /* Le code ci-dessous doit être exécutée 1 fois pour configurer la mémoire QSPI. Deux programmation sont donc nécessaires. */

      /* Initialisation de la mémoire QSPI en mode 1 fils */
      l_result = mk_system_memory_singleModeProgrammingSequence ( );

      /* Ne pas retirer cette instruction (sinon la programmation échoue) */
      /* On retourne un KO explicite car la fenêtre QSPI n'est pas initialisée. */
      l_result = K_QSPI_KO;
   }

   /* Retour */
   return ( l_result );
}


