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
* @file mk_peripheral_usb_constants.h
* @brief Déclaration des constantes dédiées au périphérique USB.
* @date 18 mai 2019
*
*/

#ifndef MK_PERIPHERAL_USB_CONSTANTS_H
#define MK_PERIPHERAL_USB_CONSTANTS_H

/**
 * @def K_USB_OTGFS
 * @brief Adresse de base du périphérique OTG_FS.
 */

#define K_USB_OTGFS ( addr_t ) 0x50000000

/**
 * @def K_USB_OTGHS
 * @brief Adresse de base du périphérique OTG_HS.
 */

#define K_USB_OTGHS ( addr_t ) 0x40040000

/**
 *
 */

/**
 * @def K_USB_GOTGCTL
 * @brief Offset du registre K_USB_GOTGCTL.
 */

#define K_USB_GOTGCTL 0x00000000

/**
 * @def K_USB_GOTGINT
 * @brief Offset du registre K_USB_GOTGINT.
 */

#define K_USB_GOTGINT 0x00000001

/**
 * @def K_USB_GAHBCFG
 * @brief Offset du registre K_USB_GAHBCFG.
 */

#define K_USB_GAHBCFG 0x00000002

/**
 * @def K_USB_GUSBCFG
 * @brief Offset du registre K_USB_GUSBCFG.
 */

#define K_USB_GUSBCFG 0x00000003

/**
 * @def K_USB_GRSTCTL
 * @brief Offset du registre K_USB_GRSTCTL.
 */

#define K_USB_GRSTCTL 0x00000004

/**
 * @def K_USB_GINTSTS
 * @brief Offset du registre K_USB_GINTSTS.
 */

#define K_USB_GINTSTS 0x00000005

/**
 * @def K_USB_GINTMSK
 * @brief Offset du registre K_USB_GINTMSK.
 */

#define K_USB_GINTMSK 0x00000006

/**
 * @def K_USB_GRXSTSR
 * @brief Offset du registre K_USB_GRXSTSR.
 */

#define K_USB_GRXSTSR 0x00000007

/**
 * @def K_USB_GRXSTSP
 * @brief Offset du registre K_USB_GRXSTSP.
 */

#define K_USB_GRXSTSP 0x00000008

/**
 * @def K_USB_GRXFSIZ
 * @brief Offset du registre K_USB_GRXFSIZ.
 */

#define K_USB_GRXFSIZ 0x00000009

/**
 * @def K_USB_HNPTXFSIZ
 * @brief Offset du registre K_USB_HNPTXFSIZ.
 */

#define K_USB_HNPTXFSIZ 0x0000000A

/**
 * @def K_USB_DIEPTXF0
 * @brief Offset du registre K_USB_DIEPTXF0.
 */

#define K_USB_DIEPTXF0 0x0000000A

/**
 * @def K_USB_HNPTXSTS
 * @brief Offset du registre K_USB_HNPTXSTS.
 */

#define K_USB_HNPTXSTS 0x0000000B

/**
 * @def K_USB_GI2CCTL
 * @brief Offset du registre K_USB_GI2CCTL.
 */

#define K_USB_GI2CCTL 0x0000000C

/**
 * @def K_USB_GCCFG
 * @brief Offset du registre K_USB_GCCFG.
 */

#define K_USB_GCCFG 0x0000000E

/**
 * @def K_USB_CID
 * @brief Offset du registre K_USB_CID.
 */

#define K_USB_CID 0x0000000F

/**
 * @def K_USB_GLPMCFG
 * @brief Offset du registre K_USB_GLPMCFG.
 */

#define K_USB_GLPMCFG 0x00000015

/**
 * @def K_USB_HPTXFSIZ
 * @brief Offset du registre K_USB_HPTXFSIZ.
 */

#define K_USB_HPTXFSIZ 0x00000040

/**
 * @def K_USB_DIEPTXF1
 * @brief Offset du registre K_USB_DIEPTXF1.
 */

#define K_USB_DIEPTXF1 0x00000041

/**
 * @def K_USB_PCGCCTL
 * @brief Offset du registre K_USB_PCGCCTL.
 */

#define K_USB_PCGCCTL 0x000000380

/**
 *
 */

/**
 * @def K_USB_HCFG
 * @brief Offset du registre K_USB_HCFG.
 */

#define K_USB_HCFG 0x00000100

/**
 * @def K_USB_HFIR
 * @brief Offset du registre K_USB_HFIR.
 */

#define K_USB_HFIR 0x00000101

/**
 * @def K_USB_HFNUM
 * @brief Offset du registre K_USB_HFNUM.
 */

#define K_USB_HFNUM 0x00000102

/**
 * @def K_USB_HPTXSTS
 * @brief Offset du registre K_USB_HPTXSTS.
 */

#define K_USB_HPTXSTS 0x00000104

/**
 * @def K_USB_HAINT
 * @brief Offset du registre K_USB_HAINT.
 */

#define K_USB_HAINT 0x00000105

/**
 * @def K_USB_HAINTMSK
 * @brief Offset du registre K_USB_HAINTMSK.
 */

#define K_USB_HAINTMSK 0x00000106

/**
 * @def K_USB_HPRT
 * @brief Offset du registre K_USB_HPRT.
 */

#define K_USB_HPRT 0x00000110

/**
 * @def K_USB_HCCHAR0
 * @brief Offset du registre K_USB_HCCHAR0.
 */

#define K_USB_HCCHAR0 0x00000140

/**
 * @def K_USB_HCSPLT0
 * @brief Offset du registre K_USB_HCSPLT0.
 */

#define K_USB_HCSPLT0 0x00000141

/**
 * @def K_USB_HCINT0
 * @brief Offset du registre K_USB_HCINT0.
 */

#define K_USB_HCINT0 0x00000142

/**
 * @def K_USB_HCINTMSK0
 * @brief Offset du registre K_USB_HCINTMSK0.
 */

#define K_USB_HCINTMSK0 0x00000143

/**
 * @def K_USB_HCTSIZ0
 * @brief Offset du registre K_USB_HCTSIZ0.
 */

#define K_USB_HCTSIZ0 0x00000144

/**
 * @def K_USB_HCDMA0
 * @brief Offset du registre K_USB_HCDMA0.
 */

#define K_USB_HCDMA0 0x00000145

/**
 *
 */

/**
 * @def K_USB_DCFG
 * @brief Offset du registre K_USB_DCFG.
 */

#define K_USB_DCFG 0x00000200

/**
 * @def K_USB_DCTL
 * @brief Offset du registre K_USB_DCTL.
 */

#define K_USB_DCTL 0x00000201

/**
 * @def K_USB_DSTS
 * @brief Offset du registre K_USB_DSTS.
 */

#define K_USB_DSTS 0x00000202

/**
 * @def K_USB_DIEPMSK
 * @brief Offset du registre K_USB_DIEPMSK.
 */

#define K_USB_DIEPMSK 0x00000204

/**
 * @def K_USB_DOEPMSK
 * @brief Offset du registre K_USB_DOEPMSK.
 */

#define K_USB_DOEPMSK 0x00000205

/**
 * @def K_USB_DAINT
 * @brief Offset du registre K_USB_DAINT.
 */

#define K_USB_DAINT 0x00000206

/**
 * @def K_USB_DAINTMSK
 * @brief Offset du registre K_USB_DAINTMSK.
 */

#define K_USB_DAINTMSK 0x00000207

/**
 * @def K_USB_DVBUSDIS
 * @brief Offset du registre K_USB_DVBUSDIS.
 */

#define K_USB_DVBUSDIS 0x0000020A

/**
 * @def K_USB_DVBUSPULSE
 * @brief Offset du registre K_USB_DVBUSPULSE.
 */

#define K_USB_DVBUSPULSE 0x0000020B

/**
 * @def K_USB_DTHRCTL
 * @brief Offset du registre K_USB_DTHRCTL.
 */

#define K_USB_DTHRCTL 0x0000020C

/**
 * @def K_USB_DIEPEMPMSK
 * @brief Offset du registre K_USB_DIEPEMPMSK.
 */

#define K_USB_DIEPEMPMSK 0x0000020D

/**
 * @def K_USB_DEACHINT
 * @brief Offset du registre K_USB_DEACHINT.
 */

#define K_USB_DEACHINT 0x0000020E

/**
 * @def K_USB_DEACHINTMSK
 * @brief Offset du registre K_USB_DEACHINTMSK.
 */

#define K_USB_DEACHINTMSK 0x0000020F

/**
 * @def K_USB_DIEPCTL0
 * @brief Offset du registre K_USB_DIEPCTL0.
 */

#define K_USB_DIEPCTL0 0x00000240

/**
 * @def K_USB_DIEPINT0
 * @brief Offset du registre K_USB_DIEPINT0.
 */

#define K_USB_DIEPINT0 0x00000242

/**
 * @def K_USB_DIEPTSIZ0
 * @brief Offset du registre K_USB_DIEPTSIZ0.
 */

#define K_USB_DIEPTSIZ0 0x00000244

/**
 * @def K_USB_DIEPDMA0
 * @brief Offset du registre K_USB_DIEPDMA0.
 */

#define K_USB_DIEPDMA0 0x00000245

/**
 * @def K_USB_DTXFSTS0
 * @brief Offset du registre K_USB_DTXFSTS0.
 */

#define K_USB_DTXFSTS0 0x00000246

/**
 * @def K_USB_DIEPCTL1
 * @brief Offset du registre K_USB_DIEPCTL1.
 */

#define K_USB_DIEPCTL1 0x00000248

/**
 * @def K_USB_DIEPTSIZ1
 * @brief Offset du registre K_USB_DIEPTSIZ1.
 */

#define K_USB_DIEPTSIZ1 0x0000024C

/**
 * @def K_USB_DOEPCTL0
 * @brief Offset du registre K_USB_DOEPCTL0.
 */

#define K_USB_DOEPCTL0 0x000002C0

/**
 * @def K_USB_DOEPINT0
 * @brief Offset du registre K_USB_DOEPINT0.
 */

#define K_USB_DOEPINT0 0x000002C2

/**
 * @def K_USB_DOEPTSIZ0
 * @brief Offset du registre K_USB_DOEPTSIZ0.
 */

#define K_USB_DOEPTSIZ0 0x000002C4

/**
 * @def K_USB_DOEPDMA0
 * @brief Offset du registre K_USB_DOEPDMA0.
 */

#define K_USB_DOEPDMA0 0x000002C5

/**
 * @def K_USB_DOEPCTL1
 * @brief Offset du registre K_USB_DOEPCTL1.
 */

#define K_USB_DOEPCTL1 0x000002C8

/**
 * @def K_USB_DOEPTSIZ1
 * @brief Offset du registre K_USB_DOEPTSIZ1.
 */

#define K_USB_DOEPTSIZ1 0x000002CC

/**
 *
 */

/**
 * @def K_USB_CHANNEL_SIZE
 * @brief Définition de la taille d'un canal en mulitple de mot 32 bits.
 */

#define K_USB_CHANNEL_SIZE 4

/**
 *
 */

/**
 * @def K_USB_FLUSH_KO
 * @brief Définition d'une constante indiquant la réussite d'une opération
 *        flush dans le timeout imparti.
 */

#define K_USB_FLUSH_OK 0

/**
 * @def K_USB_FLUSH_KO
 * @brief Définition d'une constante indiquant l'échec d'une opération
 *        flush dans le timeout imparti.
 */

#define K_USB_FLUSH_KO 1

/**
 *
 */

/**
 * @def K_USB_RESET_OK
 * @brief Définition d'une constante indiquant la réussite d'une opération
 *        reset dans le timeout imparti.
 */

#define K_USB_RESET_OK 0

/**
 * @def K_USB_RESET_KO
 * @brief Définition d'une constante indiquant l'échec d'une opération
 *        reset dans le timeout imparti.
 */

#define K_USB_RESET_KO 1

/**
 *
 */

/**
 * @def K_USB_SPECIFICATION_1DOT3
 * @brief Constante dédiée à la fonction usb_setRevision().\n
 *        Définition de la révision 1.3 (FS) du protocole USB.
 */

#define K_USB_SPECIFICATION_1DOT3 0x00000000

/**
 * @def K_USB_SPECIFICATION_2DOT0
 * @brief Constante dédiée à la fonction usb_setRevision().\n
 *        Définition de la révision 2.0 (HS) du protocole USB.
 */

#define K_USB_SPECIFICATION_2DOT0 0x00100000

/**
 *
 */

/**
 * @def K_USB_OTG_HOST
 * @brief Constante dédiée à la fonction usb_setClass().\n
 *        Définition du type du coeur USB (OTG - [ A ] or [ B ] Device).
 */

#define K_USB_OTG_HOST 0x00000000

/**
 * @def K_USB_EMBEDDED_HOST
 * @brief Constante dédiée à la fonction usb_setClass().\n
 *        Définition du type du coeur USB (Embedded Host [ A ] or Peripheral [ B ]).
 */

#define K_USB_EMBEDDED_HOST 0x00001000

/**
 *
 */

/**
 * @def K_USB_ID_CLASS_A
 * @brief Constante dédiée à la fonction usb_getConnectorID().\n
 *        Définition du status 'A' du signal ID présent sur le connecteur USB.
 */

#define K_USB_ID_CLASS_A 0x00000000

/**
 * @def K_USB_ID_CLASS_B
 * @brief Constante dédiée à la fonction usb_getConnectorID().\n
 *        Définition du status 'B' du signal ID présent sur le connecteur USB.
 */

#define K_USB_ID_CLASS_B 0x00000001

/**
 * @def K_USB_PHYSICAL_CONNECTION
 * @brief Constante dédiée à la fonction usb_getConnectorID().\n
 *        Définition du type de connection 'physique' ( 100ms + 2.5µs ).
 */

#define K_USB_PHYSICAL_CONNECTION 0x00000000

/**
 * @def K_USB_SOFT_CONNECTION
 * @brief Constante dédiée à la fonction usb_getConnectorID().\n
 *        Définition du type de connection 'logicielle' ( 2.5µs ).
 */

#define K_USB_SOFT_CONNECTION 0x00000001

/**
 *
 */

/**
 * @def K_USB_HNP_SUCCESS
 * @brief Constante dédiée à la fonction usb_getHNPStatus().\n
 *        Définition du résultat d'une requête HNP.
 */

#define K_USB_HNP_SUCCESS 0x00000001

/**
 * @def K_USB_HNP_FAILURE
 * @brief Constante dédiée à la fonction usb_getHNPStatus().\n
 *        Définition du résultat d'une requête HNP.
 */

#define K_USB_HNP_FAILURE 0x00000000

/**
 *
 */

/**
 * @def K_USB_SRP_SUCCESS
 * @brief Constante dédiée à la fonction usb_getSRPStatus().\n
 *        Définition du résultat d'une requête SRP.
 */

#define K_USB_SRP_SUCCESS 0x00000001

/**
 * @def K_USB_SRP_FAILURE
 * @brief Constante dédiée à la fonction usb_getSRPStatus().\n
 *        Définition du résultat d'une requête SRP.
 */

#define K_USB_SRP_FAILURE 0x00000000

/**
 *
 */

/**
 * @def K_USB_SRP_FAILURE
 * @brief Constante dédiée aux fonctions usb_enableOverride(), usb_disableOverride(),
 *        usb_setOverride() et usb_clearOverride().\n
 *        Définition d'une constante permettant le bypass du signal
 *        A_VALID renvoyé par le PHY.
 */

#define K_USB_OVERRIDE_AVALID_SIGNAL 0x00000010

/**
 * @def K_USB_OVERRIDE_BVALID_SIGNAL
 * @brief Constante dédiée aux fonctions usb_enableOverride(), usb_disableOverride(),
 *        usb_setOverride() et usb_clearOverride().\n
 *        Définition d'une constante permettant le bypass du signal
 *        B_VALID renvoyé par le PHY.
 */

#define K_USB_OVERRIDE_BVALID_SIGNAL 0x00000040

/**
 * @def K_USB_OVERRIDE_VBUSVALID_SIGNAL
 * @brief Constante dédiée aux fonctions usb_enableOverride(), usb_disableOverride(),
 *        usb_setOverride() et usb_clearOverride().\n
 *        Définition d'une constante permettant le bypass du signal
 *        VBUS_VALID renvoyé par le PHY.
 */

#define K_USB_OVERRIDE_VBUSVALID_SIGNAL 0x00000004

/**
 *
 */

/**
 * @def K_USB_OVERRIDE_VBUSVALID_SIGNAL
 * @brief Constante dédiée aux fonctions usb_clearInterruptFlag() et usb_getInterruptFlag().\n
 *        Définition de l'interruption ID_PIN.
 */

#define K_USB_ID_PIN_INTERRUPT 0x00100000

/**
 * @def K_USB_DEBOUNCE_DONE_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearInterruptFlag() et usb_getInterruptFlag().\n
 *        Définition de l'interruption DEBOUNCE_DONE.
 */

#define K_USB_DEBOUNCE_DONE_INTERRUPT 0x00080000

/**
 * @def K_USB_HOST_TIMEOUT_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearInterruptFlag() et usb_getInterruptFlag().\n
 *        Définition de l'interruption A_DEVICE_TIMEOUT.
 */

#define K_USB_HOST_TIMEOUT_INTERRUPT 0x00040000

/**
 * @def K_USB_HNP_DETECTED_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearInterruptFlag() et usb_getInterruptFlag().\n
 *        Définition de l'interruption HNP_DETECTED.
 */

#define K_USB_HNP_DETECTED_INTERRUPT 0x00020000

/**
 * @def K_USB_HNP_STATUS_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearInterruptFlag() et usb_getInterruptFlag().\n
 *        Définition de l'interruption HNP_STATUS.
 */

#define K_USB_HNP_STATUS_INTERRUPT 0x00000200

/**
 * @def K_USB_SRP_STATUS_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearInterruptFlag() et usb_getInterruptFlag().\n
 *        Définition de l'interruption SRP_STATUS.
 */

#define K_USB_SRP_STATUS_INTERRUPT 0x00000100

/**
 * @def K_USB_END_OF_SESSION_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearInterruptFlag() et usb_getInterruptFlag().\n
 *        Définition de l'interruption END_OF_SESSION.
 */

#define K_USB_END_OF_SESSION_INTERRUPT 0x00000004

/**
 * @def K_USB_OTG_ALL_INTERRUPTS
 * @brief Constante dédiée aux fonctions usb_clearInterruptFlag() et usb_getInterruptFlag().\n
 *        Définition d'une constante permettant d'adresser toutes les interruptions.
 */

#define K_USB_OTG_ALL_INTERRUPTS 0x001E0304

/**
 *
 */

/**
 * @def K_USB_BURST_1WORD_DO_NOT_USED
 * @brief Constante dédiée à la fonction usb_setBurstLength().\n
 *        Définition des accès 1x32bits.
 */

#define K_USB_BURST_1WORD_DO_NOT_USED 0x00000000

/**
 * @def K_USB_BURST_NOT_SPECIFIED_DO_NOT_USED
 * @brief Constante dédiée à la fonction usb_setBurstLength().\n
 *        Définition des accès non spécifié.
 */

#define K_USB_BURST_NOT_SPECIFIED_DO_NOT_USED 0x00000002

/**
 * @def K_USB_BURST_4WORDS
 * @brief Constante dédiée à la fonction usb_setBurstLength().\n
 *        Définition des accès 4x32bits.
 */

#define K_USB_BURST_4WORDS 0x00000006

/**
 * @def K_USB_BURST_8WORDS
 * @brief Constante dédiée à la fonction usb_setBurstLength().\n
 *        Définition des accès 8x32bits.
 */

#define K_USB_BURST_8WORDS 0x0000000A

/**
 * @def K_USB_BURST_16WORDS
 * @brief Constante dédiée à la fonction usb_setBurstLength().\n
 *        Définition des accès 8x32bits.
 */

#define K_USB_BURST_16WORDS 0x0000000E

/**
 *
 */

/**
 * @def K_USB_TXFIFO_HALF_EMPTY
 * @brief Constante dédiée aux fonctions usb_setDeviceTxFifoEmptyLevel()
 *        et usb_setHostTxFifoEmptyLevel().\n
 *        Définition du niveau de déclenchement de l'interruption relative
 *        au FIFO de transmission (périodique et non périodique).
 */

#define K_USB_TXFIFO_HALF_EMPTY 0x00000000

/**
 * @def K_USB_TXFIFO_EMPTY
 * @brief Constante dédiée aux fonctions usb_setDeviceTxFifoEmptyLevel()
 *        et usb_setHostTxFifoEmptyLevel().\n
 *        Définition du niveau de déclenchement de l'interruption relative
 *        au FIFO de transmission (périodique et non périodique).
 */

#define K_USB_TXFIFO_EMPTY 0x00000080

/**
 *
 */

/**
 * @def K_USB_PERIODIC_TXFIFO
 * @brief Constante dédiée à la fonction usb_setHostTxFifoEmptyLevel().\n
 *        Définition du type de FIFO de transmission.
 */

#define K_USB_PERIODIC_TXFIFO 0x00000001

/**
 * @def K_USB_NONPERIODIC_TXFIFO
 * @brief Constante dédiée à la fonction usb_setHostTxFifoEmptyLevel().\n
 *        Définition du type de FIFO de transmission.
 */

#define K_USB_NONPERIODIC_TXFIFO 0x00000000

/**
 *
 */

/**
 * @def K_USB_ULPI_PROTECTION_ENABLED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant d'activer le mécanisme de protection
 *        de l'interface ULPI.
 */

#define K_USB_ULPI_PROTECTION_ENABLED 0x00000000

/**
 * @def K_USB_ULPI_PROTECTION_ENABLED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de désactiver le mécanisme de protection
 *        de l'interface ULPI.
 */

#define K_USB_ULPI_PROTECTION_DISABLED 0x02000000

/**
 * @def K_USB_ULPI_COMPLEMENT_OUTPUT_QUALIFIED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de qualifier les signals de sortie avec
 *        le comparateur interne VBUS_VALID.
 */

#define K_USB_ULPI_COMPLEMENT_OUTPUT_QUALIFIED 0x00000000

/**
 * @def K_USB_ULPI_COMPLEMENT_OUTPUT_NOT_QUALIFIED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de ne pas qualifier les signals de sortie avec
 *        le comparateur interne VBUS_VALID.
 */

#define K_USB_ULPI_COMPLEMENT_OUTPUT_NOT_QUALIFIED 0x01000000

/**
 * @def K_USB_ULPI_VBUS_INVERT_DISABLED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de désactiver l'inversion du signal
 *        EXTVBUS.
 */

#define K_USB_ULPI_VBUS_INVERT_DISABLED 0x00000000

/**
 * @def K_USB_ULPI_VBUS_INVERT_ENABLED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant d'activer l'inversion du signal
 *        EXTVBUS.
 */

#define K_USB_ULPI_VBUS_INVERT_ENABLED 0x00800000

/**
 * @def K_USB_ULPI_TX_VALID
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de sélectionner le type d'impulsion sur
 *        la ligne de données durant une requête SRP.
 */

#define K_USB_ULPI_TX_VALID 0x00000000

/**
 * @def K_USB_ULPI_TERMSEL
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de sélectionner le type d'impulsion sur
 *        la ligne de données durant une requête SRP.
 */

#define K_USB_ULPI_TERMSEL 0x00400000

/**
 * @def K_USB_ULPI_INTERNAL_VBUS_COMPARATOR
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de sélectionner le circuit de comparaison
 *        interne du signal VBUS.
 */

#define K_USB_ULPI_INTERNAL_VBUS_COMPARATOR 0x00000000

/**
 * @def K_USB_ULPI_EXTERNAL_VBUS_COMPARATOR
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de sélectionner un circuit de comparaison
 *        externe du signal VBUS.
 */

#define K_USB_ULPI_EXTERNAL_VBUS_COMPARATOR 0x00200000

/**
 * @def K_USB_ULPI_CHARGE_PUMP
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de sélectionner le circuit interne pour
 *        l'alimentation de la ligne VBUS.
 */

#define K_USB_ULPI_CHARGE_PUMP 0x00000000

/**
 * @def K_USB_ULPI_EXTERNAL_SUPPLY
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de sélectionner un circuit externe pour
 *        l'alimentation de la ligne VBUS.
 */

#define K_USB_ULPI_EXTERNAL_SUPPLY 0x00100000

/**
 * @def K_USB_ULPI_CLOCK_POWERDOWN_DISABLED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de ne pas désactiver l'horloge interne durant
 *        le mode 'Suspend'.
 */

#define K_USB_ULPI_CLOCK_POWERDOWN_ENABLED 0x00000000

/**
 * @def K_USB_ULPI_CLOCK_POWERDOWN_ENABLED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de désactiver l'horloge interne durant
 *        le mode 'Suspend'.
 */

#define K_USB_ULPI_CLOCK_POWERDOWN_DISABLED 0x00080000

/**
 * @def K_USB_ULPI_AUTORESUME_ENABLED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant d'activer le mode 'AutoResume' en interne
 *        du PHY ULPI.
 */

#define K_USB_ULPI_AUTORESUME_ENABLED 0x00040000

/**
 * @def K_USB_ULPI_AUTORESUME_DISABLED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de désactiver le mode 'AutoResume' en interne
 *        du PHY ULPI.
 */

#define K_USB_ULPI_AUTORESUME_DISABLED 0x00000000

/**
 * @def K_USB_ULPI_INTERFACE_DEFAULT
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de sélectionner le type d'interface en interne
 *        du PHY ULPI (HIGHSPEED).
 */

#define K_USB_ULPI_INTERFACE_DEFAULT 0x00000000

/**
 * @def K_USB_ULPI_INTERFACE_FULLSPEED
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de sélectionner le type d'interface en interne
 *        du PHY ULPI.
 */

#define K_USB_ULPI_INTERFACE_FULLSPEED 0x00020000

/**
 * @def K_USB_ULPI_INTERNAL_PLL
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de sélectionner une vitesse de cadencement de
 *        480MHz en interne PHY ULPI.
 */

#define K_USB_ULPI_INTERNAL_PLL 0x00000000

/**
 * @def K_USB_ULPI_INTERNAL_PLL
 * @brief Constante dédiée à la fonction usb_setULPI().\n
 *        Définition d'une constante permettant de sélectionner une vitesse de cadencement de
 *        48MHz en interne PHY ULPI.
 */

#define K_USB_ULPI_EXTERNAL_CLOCK 0x00008000

/**
 *
 */

/**
 * @def K_USB_PHY_FULLSPEED
 * @brief Constante dédiée à la fonction usb_selectPHY().\n
 *        Définition d'une constante permettant de sélectionner un PHY de type FULLSPEED.
 */

#define K_USB_PHY_FULLSPEED 0x00000040

/**
 * @def K_USB_PHY_HIGHSPEED_UTMI
 * @brief Constante dédiée à la fonction usb_selectPHY().\n
 *        Définition d'une constante permettant de sélectionner un PHY de type UTMI.
 */

#define K_USB_PHY_HIGHSPEED_UTMI 0x00000000

/**
 * @def K_USB_PHY_HIGHSPEED_ULPI
 * @brief Constante dédiée à la fonction usb_selectPHY().\n
 *        Définition d'une constante permettant de sélectionner un PHY de type ULPI.
 */

#define K_USB_PHY_HIGHSPEED_ULPI 0x00000010

/**
 *
 */

/**
 * @def K_USB_GATE_HCLK
 * @brief Constante dédiée à la fonction usb_gate().\n
 *        Définition d'une constante permettant de stopper l'horloge de tous les modules
 *        à l'exception du bus AHB ('MASTER' et 'SLAVE') quand la session n'est pas valide
 *        ou que le bus USB est dans l'état suspendu.
 */

#define K_USB_GATE_HCLK 0x00000002

/**
 * @def K_USB_GATE_PHY
 * @brief Constante dédiée à la fonction usb_gate().\n
 *        Définition d'une constante permettant de stopper l'horloge du PHY lorsque la session
 *        n'est pas valide, lorsque le bus USB est suspendu ou lorsqu'aucun dispositif
 *        n'est connecté sur le bus.
 */

#define K_USB_GATE_PHY 0x00000001

/**
 * @def K_USB_GATE_CORE
 * @brief Constante dédiée à la fonction usb_gate().\n
 *        Définition d'une constante permettant de stopper l'horloge du coeur en mode sommeil.
 */

#define K_USB_GATE_CORE 0x00000020

/**
 * @def K_USB_GATE_NONE
 * @brief Constante dédiée à la fonction usb_gate().\n
 *        Définition d'une constante indiquant qu'aucune horloge ne doit être stoppée.
 */

#define K_USB_GATE_NONE 0x00000000

/**
 *
 */

/**
 * @def K_USB_PHY_DEEP_SLEEP_STATUS
 * @brief Constante dédiée à la fonction usb_getPHYState().\n
 *        Définition d'une constante indiquant que le PHY est en sommeil profond.
 */

#define K_USB_PHY_DEEP_SLEEP_STATUS 0x00000080

/**
 * @def K_USB_PHY_SLEEP_STATUS
 * @brief Constante dédiée à la fonction usb_getPHYState().\n
 *        Définition d'une constante indiquant que le PHY est en sommeil.
 */

#define K_USB_PHY_SLEEP_STATUS 0x00000040

/**
 * @def K_USB_PHY_SUSPENDED_STATUS
 * @brief Constante dédiée à la fonction usb_getPHYState().\n
 *        Définition d'une constante indiquant que le PHY est suspendu.
 */

#define K_USB_PHY_SUSPENDED_STATUS 0x00000010

/**
 *
 */

/**
 * @def K_USB_FS_TRDT_AHB_14DOT2_TO_15DOT0_MHZ
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_FS_TRDT_AHB_14DOT2_TO_15DOT0_MHZ 0x00003C00

/**
 * @def K_USB_FS_TRDT_AHB_15DOT0_TO_16DOT0_MHZ
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_FS_TRDT_AHB_15DOT0_TO_16DOT0_MHZ 0x00003800

/**
 * @def K_USB_FS_TRDT_AHB_16DOT0_TO_17DOT2_MHZ
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_FS_TRDT_AHB_16DOT0_TO_17DOT2_MHZ 0x00003400

/**
 * @def K_USB_FS_TRDT_AHB_17DOT2_TO_18DOT5_MHZ
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_FS_TRDT_AHB_17DOT2_TO_18DOT5_MHZ 0x00003000

/**
 * @def K_USB_FS_TRDT_AHB_18DOT5_TO_20DOT0_MHZ
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_FS_TRDT_AHB_18DOT5_TO_20DOT0_MHZ 0x00002C00

/**
 * @def K_USB_FS_TRDT_AHB_20DOT0_TO_21DOT8_MHZ
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_FS_TRDT_AHB_20DOT0_TO_21DOT8_MHZ 0x00002800

/**
 * @def K_USB_FS_TRDT_AHB_21DOT8_TO_24DOT0_MHZ
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_FS_TRDT_AHB_21DOT8_TO_24DOT0_MHZ 0x00002400

/**
 * @def K_USB_FS_TRDT_AHB_24DOT0_TO_27DOT5_MHZ
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_FS_TRDT_AHB_24DOT0_TO_27DOT5_MHZ 0x00002000

/**
 * @def K_USB_FS_TRDT_AHB_27DOT5_TO_32DOT0_MHZ
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_FS_TRDT_AHB_27DOT5_TO_32DOT0_MHZ 0x00001C00

/**
 * @def K_USB_FS_TRDT_AHB_32_MHZ_MIN
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_FS_TRDT_AHB_32_MHZ_MIN 0x00001800

/**
 * @def K_USB_HS_TRDT_AHB_30_MHZ_MIN
 * @brief Constante dédiée à la fonction usb_setTurnaroundTime().\n
 *        Définition d'une constante permettant la configuration du 'Turnaround Time'.
 *        Ce temps est fonction de la fréquence AHB.
 */

#define K_USB_HS_TRDT_AHB_30_MHZ_MIN 0x00002400

/**
 *
 */

/**
 * @def K_USB_TXFIFO_0
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 0 (Non-Periodique - Host Mode).
 */

#define K_USB_TXFIFO_0 0x00000000

/**
 * @def K_USB_TXFIFO_1
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 1 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_1 0x00000040

/**
 * @def K_USB_TXFIFO_2
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 2 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_2 0x00000080

/**
 * @def K_USB_TXFIFO_3
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 3 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_3 0x000000C0

/**
 * @def K_USB_TXFIFO_4
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 4 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_4 0x00000100

/**
 * @def K_USB_TXFIFO_5
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 5 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_5 0x00000140

/**
 * @def K_USB_TXFIFO_6
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 6 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_6 0x00000180

/**
 * @def K_USB_TXFIFO_7
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 7 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_7 0x000001C0

/**
 * @def K_USB_TXFIFO_8
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 8 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_8 0x00000200

/**
 * @def K_USB_TXFIFO_9
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 9 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_9 0x00000240

/**
 * @def K_USB_TXFIFO_10
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 10 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_10 0x00000280

/**
 * @def K_USB_TXFIFO_11
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 11 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_11 0x000002C0

/**
 * @def K_USB_TXFIFO_12
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 12 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_12 0x00000300

/**
 * @def K_USB_TXFIFO_13
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 13 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_13 0x00000340

/**
 * @def K_USB_TXFIFO_14
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 14 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_14 0x00000380

/**
 * @def K_USB_TXFIFO_15
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser le buffer
 *        de transmission 15 (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_15 0x000003C0

/**
 * @def K_USB_TXFIFO_ALL
 * @brief Constante dédiée à la fonction usb_flushTxFifo().\n
 *        Définition d'une constante permettant de réinitialiser tous les buffers
 *        de transmission (Periodique - Host Mode).
 */

#define K_USB_TXFIFO_ALL 0x00000400

/**
 *
 */

/**
 * @def K_USB_WAKEUP_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption WAKEUP_INTERRUPT. Elle est déclenchée
 *        lors de la détection d'une commande 'Remote Wakeup' (Host) ou 'Resume' (Device).
 */

#define K_USB_WAKEUP_INTERRUPT 0x80000000

/**
 * @def K_USB_SESSION_REQUEST_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption SESSION_REQUEST_INTERRUPT. Elle est déclenchée
 *        lorsqu'un dispositif de type B (device) demande l'ouverture d'une session.
 *        Cette interruption peut être utilisée en mode 'Host'.
 */

#define K_USB_SESSION_REQUEST_INTERRUPT 0x40000000

/**
 * @def K_USB_VBUS_VALID_RANGE_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption VBUS_VALID_RANGE_INTERRUPT. Elle est déclenchée
 *        lorsque la tension VBUS est conforme au seuil d'alimentation d'un dispositif
 *        esclave.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_VBUS_VALID_RANGE_INTERRUPT 0x40000000

/**
 * @def K_USB_DISCONNECT_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption DISCONNECT_INTERRUPT. Elle est déclenchée
 *        lorsqu'un dispositif esclave a été déconnecté du bus.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_DISCONNECT_INTERRUPT 0x20000000

/**
 * @def K_USB_ID_PIN_CHANGE_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption ID_CHANGE_INTERRUPT. Elle est déclenchée
 *        lorsque la broche ID change d'état logique.
 */

#define K_USB_ID_PIN_CHANGE_INTERRUPT 0x10000000

/**
 * @def K_USB_LPM_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption LPM_INTERRUPT. Elle est déclenchée de la
 *        manière suivante :
 *        \li En mode 'Device', l'interruption est déclenché après l'envoi d'une
 *        réponse 'NON_ERROR' acquittant une transaction LPM envoyée par le maitre.
 *        \li En mode 'Host', l'interruption est déclenché après le transfert d'une
 *        transaction LPM et lors de l'acquitement de la commande (réponse 'NON_ERROR').
 *
 * @note La fonction usb_getCoreInterruptFlag() n'est disponible que pour le périphérique USBOTG_HS.
 */

#define K_USB_LPM_INTERRUPT 0x08000000

/**
 * @def K_USB_PERIODIC_TXFIFO_EMPTY_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts().\n
 *        Définition de l'interruption PERIODIC_TXFIFO_EMPTY_INTERRUPT. Elle est
 *        déclenchée lorsque le FIFO est à moitié ou entièrement vide. Le seuil
 *        se détermine selon la configuration appliquée avec la fonction
 *        usb_setHostTxFifoEmptyLevel().
 *        Cette interruption peut être utilisée en mode 'Host'.
 */

#define K_USB_PERIODIC_TXFIFO_EMPTY_INTERRUPT 0x04000000

/**
 * @def K_USB_CHANNELS_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts().\n
 *        Définition de l'interruption CHANNELS_INTERRUPT. Elle est
 *        déclenchée lorsqu'une interruption relative au canaux de communication
 *        est en attente de traitement.
 *        Cette interruption peut être utilisée en mode 'Host'.
 */

#define K_USB_CHANNELS_INTERRUPT 0x02000000

/**
 * @def K_USB_PORT_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts().\n
 *        Définition de l'interruption PORT_INTERRUPT. Elle est
 *        déclenchée lorsqu'une interruption relative au port USB est en attente
 *        de traitement.
 *        Cette interruption peut être utilisée en mode 'Host'.
 */

#define K_USB_PORT_INTERRUPT 0x01000000

/**
 * @def K_USB_RESET_SUSPENDED_STATE_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption RESET_SUSPENDED_STATE_INTERRUPT. Elle est
 *        déclenchée par un périphérique esclave lorsqu'une opération de reset est
 *        effectuée par le maitre lorsque le bus USB est dans l'état 'Partial Power Down'.
 *        Cette interruption peut être utilisée en mode 'Device'.
 *
 * @note La fonction usb_getCoreInterruptFlag() n'est disponible que pour le périphérique USBOTG_FS.
 */

#define K_USB_RESET_SUSPENDED_STATE_INTERRUPT 0x00800000

/**
 * @def K_USB_DATA_FETCH_SUSPENDED_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption RESET_DATA_FETCH_SUSPENDED_INTERRUPT. Elle est
 *        déclenchée en mode DMA lorsque les buffers de communication de type IN ne peuvent plus
 *        acceuillir de nouvelles données.
 *
 * @note La fonction usb_getCoreInterruptFlag() n'est disponible que pour le périphérique USBOTG_HS.
 */

#define K_USB_DATA_FETCH_SUSPENDED_INTERRUPT 0x00400000

/**
 * @def K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT. Elle est
 *        déclenchée lorsque dans la trame courante, une transaction périodique est toujours en
 *        attente de transfert.
 *        Cette interruption peut être utilisée en mode 'Host'.
 */

#define K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT 0x00200000

/**
 * @def K_USB_INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT. Elle est
 *        déclenchée lorsqu'à la fin de la période courante, au moins une transaction isochrone est toujours en
 *        attente de transfert.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT 0x00200000

/**
 * @def K_USB_INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT. Elle est
 *        déclenchée lorsqu'à la fin de la période courante, au moins une transaction isochrone est toujours en
 *        attente de transfert.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT 0x00100000

/**
 * @def K_USB_OUT_ENDPOINT_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts().\n
 *        Définition de l'interruption OUT_ENDPOINT_INTERRUPT. Elle est
 *        déclenchée lorsqu'une interruption relative à une terminaison de type OUT est détectée par
 *        le coeur USB.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_OUT_ENDPOINT_INTERRUPT 0x00080000

/**
 * @def K_USB_IN_ENDPOINT_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts().\n
 *        Définition de l'interruption IN_ENDPOINT_INTERRUPT. Elle est
 *        déclenchée lorsqu'une interruption relative à une terminaison de type IN est détectée par
 *        le coeur USB.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_IN_ENDPOINT_INTERRUPT 0x00040000

/**
 * @def K_USB_END_OF_PERIODIC_FRAME_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption END_OF_PERIODIC_FRAME_INTERRUPT. Elle est
 *        déclenchée lorsque la période de la trame courante est terminée.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_END_OF_PERIODIC_FRAME_INTERRUPT 0x00008000

/**
 * @def K_USB_ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT. Elle est
 *        déclenchée lorsque le coeur ne peut pas écrire le paquet isochrone entrant dans
 *        le buffer de réception en raison d'une taille insuffisante.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT 0x00004000

/**
 * @def K_USB_ENUMERATION_DONE_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption ENUMERATION_DONE_INTERRUPT. Elle est
 *        déclenchée lorsque la phase d'énumération est terminée.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_ENUMERATION_DONE_INTERRUPT 0x00002000

/**
 * @def K_USB_RESET_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption RESET_INTERRUPT. Elle est déclenchée lorqu'un
 *        reset est détecté sur le bus.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_RESET_INTERRUPT 0x00001000

/**
 * @def K_USB_SUSPENDED_STATE_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption SUSPENDED_STATE_INTERRUPT. Elle est déclenchée lorsque le bus
 *        passe dans l'état suspendu en raison d'un période d'inactivité prolongée.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_SUSPENDED_STATE_INTERRUPT 0x00000800

/**
 * @def K_USB_EARLY_SUSPENDED_STATE_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption IDLE_STATE_INTERRUPT. Elle est déclenchée lorsque le bus
 *        passe dans l'état de repos en raison d'un période d'inactivité de 3ms.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_EARLY_SUSPENDED_STATE_INTERRUPT 0x00000400

/**
 * @def K_USB_GLOBAL_OUT_NACK_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts(). \n
 *        Définition de l'interruption GLOBAL_OUT_NACK_INTERRUPT. Elle est déclenchée lorsque le
 *        mécanisme de bypass des terminaisons de type OUT est actif.
 *        Cette interruption peut être utilisée en mode 'Device'.
 */

#define K_USB_GLOBAL_OUT_NACK_INTERRUPT 0x00000080

/**
 * @def K_USB_GLOBAL_NON_PERIODIC_IN_NACK_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts(). \n
 *        Définition de l'interruption GLOBAL_NON_PERIODIC_IN_NACK_INTERRUPT. Elle est déclenchée lorsque
 *        le mécanisme de bypass des terminaisons de type IN est actif.
 */

#define K_USB_GLOBAL_NON_PERIODIC_IN_NACK_INTERRUPT 0x00000040

/**
 * @def K_USB_NON_PERIODIC_TXFIFO_EMPTY_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts(). \n
 *        Définition de l'interruption NON_PERIODIC_TXFIFO_EMPTY_INTERRUPT. Elle est
 *        déclenchée lorsque le FIFO est à moitié ou entièrement vide. Le seuil
 *        se détermine selon la configuration appliquée avec la fonction
 *        usb_setHostTxFifoEmptyLevel().
 *        Cette interruption peut être utilisée en mode 'Host'.
 */

#define K_USB_NON_PERIODIC_TXFIFO_EMPTY_INTERRUPT 0x00000020

/**
 * @def K_USB_RX_FIFO_NOT_EMPTY_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts(). \n
 *        Définition de l'interruption RX_FIFO_NOT_EMPTY_INTERRUPT. Elle est déclenchée lorsqu'il y a
 *        au moins un paquet disponible dans le FIFO de réception.
 */

#define K_USB_RX_FIFO_NOT_EMPTY_INTERRUPT 0x00000010

/**
 * @def K_USB_START_OF_FRAME_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearCoreInterruptFlag().\n
 *        Définition de l'interruption START_OF_FRAME_INTERRUPT. Elle est déclenchée de la manière
 *        suivante : \n
 *        \li En mode 'Host', elle est déclenchée lorsqu'un SOF (Start Of Frame) ou un LS ( Keep Alive)
 *            est transmis sur le bus.
 *        \li En mode 'Device', elle est déclenchée lorqu'une SOF est détecté sur le bus.
 */

#define K_USB_START_OF_FRAME_INTERRUPT 0x00000008

/**
 * @def K_USB_OTG_EVENT_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts(). \n
 *        Définition de l'interruption OTG_EVENT_INTERRUPT. Elle est déclenchée lorsqu'un événement
 *        de type OTG est détecté.
 */

#define K_USB_OTG_EVENT_INTERRUPT 0x00000004

/**
 * @def K_USB_MODE_MISMATCH_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearInterrupts().\n
 *        Définition de l'interruption MODE_MISMATCH_INTERRUPT. Elle est déclenchée lorsqu'en mode
 *        'Host', un registre de type 'Device' est accédé ou lorsqu'en mode 'Device', un registre de
 *        type 'Host' est accédé.
 */

#define K_USB_MODE_MISMATCH_INTERRUPT 0x00000002

/**
 * @def K_USB_CORE_ALL_INTERRUPTS
 * @brief Constante dédiée aux fonctions usb_getCoreInterruptFlag(), usb_maskCoreInterrupts()
 *        et usb_clearInterrupts().\n
 *        Définition d'une constante permettant d'adresser toutes interruptions.
 */

#define K_USB_CORE_ALL_INTERRUPTS 0xF070FC0A

/**
 *
 */

/**
 * @def K_USB_DEVICE_MODE
 * @brief Constante dédiée à la fonction usb_getMode().\n
 *        Définition d'une constante indiquant que le mode courant est le mode 'Device'.
 */

#define K_USB_DEVICE_MODE 0x00000000

/**
 * @def K_USB_HOST_MODE
 * @brief Constante dédiée à la fonction usb_getMode().\n
 *        Définition d'une constante indiquant que le mode courant est le mode 'Host'.
 */

#define K_USB_HOST_MODE 0x00000001

/**
 *
 */

/**
 * @def K_USB_IDLE
 * @brief Constante dédiée à la fonction usb_getIdleStatus().\n
 *        Définition d'une constante indiquant que la machine à état est au repos.
 */

#define K_USB_IDLE 0x00000001

/**
 * @def K_USB_BUSY
 * @brief Constante dédiée à la fonction usb_getIdleStatus().\n
 *        Définition d'une constante indiquant que la machine à état n'est pas au repos.
 */

#define K_USB_BUSY 0x00000000

/**
 *
 */

/**
 * @def K_USB_DEBUG_READ
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        Définition de l'opération DEBUG_READ permettant de lire sans retirer une donnée
 *        entrée dans le FIFO de réception.
 */

#define K_USB_DEBUG_READ 0x00000000

/**
 * @def K_USB_POP
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        usb_getByteCount(), usb_getChannelNumber(), usb_getFrameNumber() et
 *        usb_getEndpointNumber().\n
 *        Définition de l'opération POP permettant de lire et de retirer une donnée
 *        entrée dans le FIFO de réception.
 */

#define K_USB_POP 0x00000001

/**
 *
 */

/**
 * @def K_USB_GLOBAL_OUT_NACK
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        Définition d'une constante indiquant que le paquet USB entré possède un statut
 *        GLOBAL_OUT_NACK.\n
 *        Cette constante peut être utilisée en mode 'Device'.
 */

#define K_USB_GLOBAL_OUT_NACK 0x00000001

/**
 * @def K_USB_IN_DATA_PACKET
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        Définition d'une constante indiquant que le paquet USB entré possède un statut
 *        IN_DATA_PACKET.\n
 *        Cette constante peut être utilisée en mode 'Host'.
 */

#define K_USB_IN_DATA_PACKET 0x00000002

/**
 * @def K_USB_OUT_DATA_PACKET
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        Définition d'une constante indiquant que le paquet USB entré possède un statut
 *        OUT_DATA_PACKET.\n
 *        Cette constante peut être utilisée en mode 'Device'.
 */

#define K_USB_OUT_DATA_PACKET 0x00000002

/**
 * @def K_USB_IN_TRANSFER_COMPLETED
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        Définition d'une constante indiquant que le paquet USB entré possède un statut
 *        IN_TRANSFER_COMPLETED.\n
 *        Cette constante peut être utilisée en mode 'Host'.
 */

#define K_USB_IN_TRANSFER_COMPLETED 0x00000003

/**
 *
 */

/**
 * @def K_USB_OUT_TRANSFER_COMPLETED
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        Définition d'une constante indiquant que le paquet USB entré possède un statut
 *        OUT_TRANSFER_COMPLETED.\n
 *        Cette constante peut être utilisée en mode 'Device'.
 */

#define K_USB_OUT_TRANSFER_COMPLETED 0x00000003

/**
 * @def K_USB_SETUP_TRANSACTION_COMPLETED
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        Définition d'une constante indiquant que le paquet USB entré possède un statut
 *        SETUP_TRANSACTION_COMPLETED.\n
 *        Cette constante peut être utilisée en mode 'Device'.
 */

#define K_USB_SETUP_TRANSACTION_COMPLETED 0x00000004

/**
 * @def K_USB_DATA_TOOGLE_ERROR
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        Définition d'une constante indiquant que le paquet USB entré possède un statut
 *        DATA_TOOGLE_ERROR.\n
 *        Cette constante peut être utilisée en mode 'Host'.
 */

#define K_USB_DATA_TOOGLE_ERROR 0x00000005

/**
 * @def K_USB_SETUP_DATA_PACKET_RECEIVED
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        Définition d'une constante indiquant que le paquet USB entré possède un statut
 *        K_USB_SETUP_DATA_PACKET_RECEIVED.\n
 *        Cette constante peut être utilisée en mode 'Device'.
 */

#define K_USB_SETUP_DATA_PACKET_RECEIVED 0x00000006

/**
 * @def K_USB_CHANNEL_HALTED
 * @brief Constante dédiée à la fonction usb_getRxStatus().\n
 *        Définition d'une constante indiquant que le paquet USB entré possède un statut
 *        CHANNEL_HALTED.\n
 *        Cette constante peut être utilisée en mode 'Host'.
 */

#define K_USB_CHANNEL_HALTED 0x00000007

/**
 *
 */

/**
 * @def K_USB_CHANNEL_IDLE
 * @brief Constante dédiée à la fonction usb_getChannelStatus().\n
 *        Définition d'une constante indiquant qu'un canal de communication est au repos.
 */

#define K_USB_CHANNEL_IDLE 0x00000000

/**
 * @def K_USB_CHANNEL_DISABLED
 * @brief Constante dédiée à la fonction usb_getChannelStatus().\n
 *        Définition d'une constante indiquant qu'un canal de communication a été explicitement
 *        suspendu par l'application ou le coeur.
 */

#define K_USB_CHANNEL_DISABLED 0x00000001

/**
 * @def K_USB_CHANNEL_ENABLED
 * @brief Constante dédiée à la fonction usb_getChannelStatus().\n
 *        Définition d'une constante indiquant qu'un canal de communication est en cours de
 *        fonctionnement.
 */

#define K_USB_CHANNEL_ENABLED 0x00000002

/**
 *
 */

/**
 * @def K_USB_SPLIT_TRANSACTION
 * @brief Constante dédiée à la fonction usb_getSplit().\n
 *        Définition d'une constante indiquant que la transaction en cours est de type SPLIT.
 */

#define K_USB_SPLIT_TRANSACTION 0x00000001

/**
 * @def K_USB_DEFAULT_TRANSACTION
 * @brief Constante dédiée à la fonction usb_getSplit().\n
 *        Définition d'une constante indiquant que la transaction en cours est de type classique.
 */

#define K_USB_DEFAULT_TRANSACTION 0x00000000

/**
 *
 */

/**
 * @def K_USB_TOKEN_SSPLIT
 * @brief Constante dédiée à la fonction usb_getSplitToken().\n
 *        Définition d'une constante indiquant que la transaction en cours est de type SSPLIT.
 */

#define K_USB_TOKEN_SSPLIT 0x00000000

/**
 * @def K_USB_TOKEN_CSPLIT
 * @brief Constante dédiée à la fonction usb_getSplitToken().\n
 *        Définition d'une constante indiquant que la transaction en cours est de type CSPLIT.
 */

#define K_USB_TOKEN_CSPLIT 0x00000000

/**
 *
 */

/**
 * @def K_USB_PID_DATA0
 * @brief Constante dédiée aux fonctions usb_getRxStatus() et usb_setChannel().\n
 *        Définition du PID DATA0.
 */

#define K_USB_PID_DATA0 0x00000000

/**
 * @def K_USB_PID_DATA1
 * @brief Constante dédiée aux fonctions usb_getRxStatus() et usb_setChannel().\n
 *        Définition du PID DATA1.
 */

#define K_USB_PID_DATA1 0x00000002

/**
 * @def K_USB_PID_DATA2
 * @brief Constante dédiée aux fonctions usb_getRxStatus() et usb_setChannel().\n
 *        Définition du PID DATA2.
 */

#define K_USB_PID_DATA2 0x00000001

/**
 * @def K_USB_PID_MDATA
 * @brief Constante dédiée aux fonctions usb_getRxStatus() et usb_setChannel().\n
 *        Définition du PID MDATA.
 */

#define K_USB_PID_MDATA 0x00000003

/**
 * @def K_USB_PID_MDATA
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition du PID SETUP.
 */

#define K_USB_PID_SETUP 0x00000003

/**
 * @def K_USB_PID_TOOGLE
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition d'un identifiant permettant de permuter les PIDs.
 */

#define K_USB_PID_TOOGLE 0x00000004

/**
 *
 */

/**
 * @def K_USB_ENTRY_IN_OUT_TOKEN
 * @brief Constante dédiée aux fonctions usb_getNonPeriodicTxStatus() et .
 *        usb_getPeriodicTxStatus().\n
 *        Définition d'une constante décrivant une entrée de type IN/OUT_TOKEN.
 */

#define K_USB_ENTRY_IN_OUT_TOKEN 0x00000000

/**
 * @def K_USB_ENTRY_ZERO_LENGTH_PACKET
 * @brief Constante dédiée aux fonctions usb_getNonPeriodicTxStatus() et .
 *        usb_getPeriodicTxStatus().\n
 *        Définition d'une constante décrivant une entrée de type ZERO_LENGTH_DATA_PACKET.
 */

#define K_USB_ENTRY_ZERO_LENGTH_PACKET 0x00000001

/**
 * @def K_USB_ENTRY_CHANNEL_HALT
 * @brief Constante dédiée à la fonction usb_getNonPeriodicTxStatus().\n
 *        Définition d'une constante décrivant une entrée de type CHANNEL_HALT_COMMAND.
 */

#define K_USB_ENTRY_CHANNEL_HALT 0x00000002

/**
 * @def K_USB_DISABLE_CHANNEL_CMD
 * @brief Constante dédiée à la fonction usb_getPeriodicTxStatus().\n
 *        Définition d'une constante décrivant une entrée de type DISABLE_CHANNEL_CMD.
 */

#define K_USB_DISABLE_CHANNEL_CMD 0x00000003

/**
 *
 */

/**
 * @def K_USB_EVEN_FRAME
 * @brief Constante dédiée aux fonctions usb_getPeriodicTxStatus() et
 *        usb_setChannel().\n
 *        Définition d'une constante décrivant une trame de type paire.
 */

#define K_USB_EVEN_FRAME 0x00000000

/**
 * @def K_USB_ODD_FRAME
 * @brief Constante dédiée aux fonctions usb_getPeriodicTxStatus() et
 *        usb_setChannel().\n
 *        Définition d'une constante décrivant une trame de type impaire.
 */

#define K_USB_ODD_FRAME 0x00000001

/**
 *
 */

/**
 * @def K_USB_ENDPOINT0
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition de l'identifiant de la terminaison 0.
 */

#define K_USB_ENDPOINT0 0x00000000

/**
 * @def K_USB_ENDPOINT1
 * @brief Constante dédiée aux fonctions usb_setEPnTxFifoSize(), usb_setEPnTxFifoAddr().
 *        et usb_setChannel().\n
 *        Définition de l'identifiant de la terminaison 1.
 */

#define K_USB_ENDPOINT1 0x00000001

/**
 * @def K_USB_ENDPOINT2
 * @brief Constante dédiée aux fonctions usb_setEPnTxFifoSize(), usb_setEPnTxFifoAddr().
 *        et usb_setChannel().\n
 *        Définition de l'identifiant de la terminaison 2.
 */

#define K_USB_ENDPOINT2 0x00000002

/**
 * @def K_USB_ENDPOINT3
 * @brief Constante dédiée aux fonctions usb_setEPnTxFifoSize(), usb_setEPnTxFifoAddr().
 *        et usb_setChannel().\n
 *        Définition de l'identifiant de la terminaison 3.
 */

#define K_USB_ENDPOINT3 0x00000003

/**
 * @def K_USB_ENDPOINT4
 * @brief Constante dédiée aux fonctions usb_setEPnTxFifoSize(), usb_setEPnTxFifoAddr().
 *        et usb_setChannel().\n
 *        Définition de l'identifiant de la terminaison 4.
 */

#define K_USB_ENDPOINT4 0x00000004

/**
 * @def K_USB_ENDPOINT5
 * @brief Constante dédiée aux fonctions usb_setEPnTxFifoSize(), usb_setEPnTxFifoAddr().
 *        et usb_setChannel().\n
 *        Définition de l'identifiant de la terminaison 5.
 */

#define K_USB_ENDPOINT5 0x00000005

/**
 * @def K_USB_ENDPOINT6
 * @brief Constante dédiée aux fonctions usb_setEPnTxFifoSize(), usb_setEPnTxFifoAddr().
 *        et usb_setChannel().\n
 *        Définition de l'identifiant de la terminaison 6.
 */

#define K_USB_ENDPOINT6 0x00000006

/**
 * @def K_USB_ENDPOINT7
 * @brief Constante dédiée aux fonctions usb_setEPnTxFifoSize(), usb_setEPnTxFifoAddr().
 *        et usb_setChannel().\n
 *        Définition de l'identifiant de la terminaison 7.
 */

#define K_USB_ENDPOINT7 0x00000007

/**
 * @def K_USB_ENDPOINT8
 * @brief Constante dédiée aux fonctions usb_setEPnTxFifoSize(), usb_setEPnTxFifoAddr().
 *        et usb_setChannel().\n
 *        Définition de l'identifiant de la terminaison 8.
 */

#define K_USB_ENDPOINT8 0x00000008

/**
 *
 */

/**
 * @def K_USB_I2C_VP_VM_MODE
 * @brief Constante dédiée à la fonction usb_setI2CInterface().\n
 *        Définition du mode de fonctionnement du PHY USB I2C. Le PHY se pilote en utilisant
 *        l'interface VP_VM.
 */

#define K_USB_I2C_VP_VM_MODE 0x00000000

/**
 * @def K_USB_I2C_DAT_SE0_MODE
 * @brief Constante dédiée à la fonction usb_setI2CInterface().\n
 *        Définition du mode de fonctionnement du PHY USB I2C. Le PHY se pilote en utilisant
 *        l'interface DAT_SE0.
 */

#define K_USB_I2C_DAT_SE0_MODE 0x10000000

/**
 * @def K_USB_I2C_IDLE
 * @brief Constante dédiée à la fonction usb_getI2CStatus().\n
 *        Définition de l'état du bus I2C du périphérique USB (occupé).
 */

#define K_USB_I2C_IDLE 0x00000000

/**
 * @def K_USB_I2C_BUSY
 * @brief Constante dédiée à la fonction usb_getI2CStatus().\n
 *        Définition de l'état du bus I2C du périphérique USB (repos).
 */

#define K_USB_I2C_BUSY 0x00000001

/**
 * @def K_USB_I2C_ACK
 * @brief Constante dédiée à la fonction usb_getI2CData().\n
 *        Définition de la valeur indiquant la réception d'un ACK.
 */

#define K_USB_I2C_ACK 0x00000001

/**
 * @def K_USB_I2C_NACK
 * @brief Constante dédiée à la fonction usb_getI2CStatus().\n
 *        Définition de la valeur indiquant la réception d'un NACK.
 */

#define K_USB_I2C_NACK 0x00000000


/**
 *
 */

/**
 * @def K_USB_LPM_CHANNEL0
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 0.
 */

#define K_USB_LPM_CHANNEL0 0x00000000

/**
 * @def K_USB_LPM_CHANNEL1
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 1.
 */

#define K_USB_LPM_CHANNEL1 0x00000001

/**
 * @def K_USB_LPM_CHANNEL2
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 2.
 */

#define K_USB_LPM_CHANNEL2 0x00000002

/**
 * @def K_USB_LPM_CHANNEL3
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 3.
 */

#define K_USB_LPM_CHANNEL3 0x00000003

/**
 * @def K_USB_LPM_CHANNEL4
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 4.
 */

#define K_USB_LPM_CHANNEL4 0x00000004

/**
 * @def K_USB_LPM_CHANNEL5
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 5.
 */

#define K_USB_LPM_CHANNEL5 0x00000005

/**
 * @def K_USB_LPM_CHANNEL6
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 6.
 */

#define K_USB_LPM_CHANNEL6 0x00000006

/**
 * @def K_USB_LPM_CHANNEL7
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 7.
 */

#define K_USB_LPM_CHANNEL7 0x00000007

/**
 * @def K_USB_LPM_CHANNEL8
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 8.
 */

#define K_USB_LPM_CHANNEL8 0x00000008

/**
 * @def K_USB_LPM_CHANNEL9
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 9.
 */

#define K_USB_LPM_CHANNEL9 0x00000009

/**
 * @def K_USB_LPM_CHANNEL10
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 10.
 */

#define K_USB_LPM_CHANNEL10 0x0000000A

/**
 * @def K_USB_LPM_CHANNEL11
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 11.
 */

#define K_USB_LPM_CHANNEL11 0x0000000B

/**
 * @def K_USB_LPM_CHANNEL12
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 12. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_LPM_CHANNEL12 0x0000000C

/**
 * @def K_USB_LPM_CHANNEL13
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 13. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_LPM_CHANNEL13 0x0000000D

/**
 * @def K_USB_LPM_CHANNEL14
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 14. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_LPM_CHANNEL14 0x0000000E

/**
 * @def K_USB_LPM_CHANNEL15
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du numéro de canal 15. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_LPM_CHANNEL15 0x0000000F

/**
 *
 */

/**
 * @def K_USB_LPM_ACK
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition des réponses d'une requête LPM.
 */

#define K_USB_LPM_ACK 0x00000003

/**
 * @def K_USB_LPM_NYET
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition des réponses d'une requête LPM.
 */

#define K_USB_LPM_NYET 0x00000002

/**
 * @def K_USB_LPM_STALL
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition des réponses d'une requête LPM.
 */

#define K_USB_LPM_STALL 0x00000001

/**
 * @def K_USB_LPM_ERROR
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition des réponses d'une requête LPM.
 */

#define K_USB_LPM_ERROR 0x00000000

/**
 *
 */

/**
 * @def K_USB_BESL_125_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_125_US 0x00000000

/**
 * @def K_USB_BESL_150_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_150_US 0x00000001

/**
 * @def K_USB_BESL_200_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_200_US 0x00000002

/**
 * @def K_USB_BESL_300_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_300_US 0x00000003

/**
 * @def K_USB_BESL_400_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_400_US 0x00000004

/**
 * @def K_USB_BESL_500_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_500_US 0x00000005

/**
 * @def K_USB_BESL_1000_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_1000_US 0x00000006

/**
 * @def K_USB_BESL_2000_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_2000_US 0x00000007

/**
 * @def K_USB_BESL_3000_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_3000_US 0x00000008

/**
 * @def K_USB_BESL_4000_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_4000_US 0x00000009

/**
 * @def K_USB_BESL_5000_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_5000_US 0x0000000A

/**
 * @def K_USB_BESL_6000_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_6000_US 0x0000000B

/**
 * @def K_USB_BESL_7000_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_7000_US 0x0000000C

/**
 * @def K_USB_BESL_8000_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_8000_US 0x0000000D

/**
 * @def K_USB_BESL_9000_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_9000_US 0x0000000E

/**
 * @def K_USB_BESL_10000_US
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition de la durée T_L1_HubDrvResume1 en µs d'une
 *        transaction LPM.
 */

#define K_USB_BESL_10000_US 0x0000000F

/**
 *
 */

/**
 * @def K_USB_BESL_THRESHOLD_75_US
 * @brief Constante dédiée à la fonction usb_setBESLBehavior().\n
 *        Définition de la durée T_L1_HubDrvResume2 en µs.
 */

#define K_USB_BESL_THRESHOLD_75_US 0x00000000

/**
 * @def K_USB_BESL_THRESHOLD_100_US
 * @brief Constante dédiée à la fonction usb_setBESLBehavior().\n
 *        Définition de la durée T_L1_HubDrvResume2 en µs.
 */

#define K_USB_BESL_THRESHOLD_100_US 0x00000001

/**
 * @def K_USB_BESL_THRESHOLD_150_US
 * @brief Constante dédiée à la fonction usb_setBESLBehavior().\n
 *        Définition de la durée T_L1_HubDrvResume2 en µs.
 */

#define K_USB_BESL_THRESHOLD_150_US 0x00000002

/**
 * @def K_USB_BESL_THRESHOLD_250_US
 * @brief Constante dédiée à la fonction usb_setBESLBehavior().\n
 *        Définition de la durée T_L1_HubDrvResume2 en µs.
 */

#define K_USB_BESL_THRESHOLD_250_US 0x00000003

/**
 * @def K_USB_BESL_THRESHOLD_350_US
 * @brief Constante dédiée à la fonction usb_setBESLBehavior().\n
 *        Définition de la durée T_L1_HubDrvResume2 en µs.
 */

#define K_USB_BESL_THRESHOLD_350_US 0x00000004

/**
 * @def K_USB_BESL_THRESHOLD_450_US
 * @brief Constante dédiée à la fonction usb_setBESLBehavior().\n
 *        Définition de la durée T_L1_HubDrvResume2 en µs.
 */

#define K_USB_BESL_THRESHOLD_450_US 0x00000005

/**
 * @def K_USB_BESL_THRESHOLD_950_US
 * @brief Constante dédiée à la fonction usb_setBESLBehavior().\n
 *        Définition de la durée T_L1_HubDrvResume2 en µs.
 */

#define K_USB_BESL_THRESHOLD_950_US 0x00000006

/**
 *
 */

/**
 * @def K_USB_REMOTE_WAKEUP_ENABLED
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du paramètre REMOTE_WAKEUP d'une transaction LPM autorisant
 *        un device à réveiller le maitre du bus.
 */

#define K_USB_REMOTE_WAKEUP_ENABLED 0x00000040

/**
 * @def K_USB_REMOTE_WAKEUP_DISABLED
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 *        Définition du paramètre REMOTE_WAKEUP d'une transaction LPM interdisant
 *        un device à réveiller le maitre du bus.
 */

#define K_USB_REMOTE_WAKEUP_DISABLED 0x00000000

/**
 *
 */

/**
 * @def K_USB_REMOTE_WAKEUP_DISABLED
 * @brief Constante dédiée à la fonction usb_getLPMSleepStatus().\n
 *        Définition du constante indiquant que le coeur est dans l'état L1 (sommeil).
 */

#define K_USB_L1_MODE_ENABLED 0x00000001

/**
 * @def K_USB_L1_MODE_DISABLED
 * @brief Constante dédiée à la fonction usb_getLPMSleepStatus().\n
 *        Définition du constante indiquant que le coeur n'est pas dans l'état L1 (sommeil).
 */

#define K_USB_L1_MODE_DISABLED 0x00000000

/**
 *
 */

/**
 * @def K_USB_READY_TO_WAKE
 * @brief Constante dédiée à la fonction usb_getLPMReadyToWakeStatus().\n
 *        Définition du constante indiquant que le coeur peut sortir du mode L1 (sommeil).
 */

#define K_USB_READY_TO_WAKE 0x00000001

/**
 * @def K_USB_READY_TO_WAKE
 * @brief Constante dédiée à la fonction usb_getLPMReadyToWakeStatus().\n
 *        Définition du constante indiquant que le coeur ne peut pas sortir du mode
 *        L1 (sommeil).
 */

#define K_USB_NOT_READY_TO_WAKE 0x00000001

/**
 *
 */

/**
 * @def K_USB_PHY_CLOCK_6MHZ
 * @brief Constante dédiée à la fonction usb_setPHYClock().\n
 *        Définition de la fréquence de fonctionnement d'un PHY USB de type LS.
 */

#define K_USB_PHY_CLOCK_6MHZ 0x00000002

/**
 * @def K_USB_PHY_CLOCK_48MHZ
 * @brief Constante dédiée à la fonction usb_setPHYClock().\n
 *        Définition de la fréquence de fonctionnement d'un PHY USB de type LS ou FS.
 */

#define K_USB_PHY_CLOCK_48MHZ 0x00000001

/**
 *
 */

/**
 * @def K_USB_CHANNEL0
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 0.
 */

#define K_USB_MASK_CHANNEL0 0x00000001

/**
 * @def K_USB_CHANNEL1
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 1.
 */

#define K_USB_MASK_CHANNEL1 0x00000002

/**
 * @def K_USB_MASK_CHANNEL2
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 2.
 */

#define K_USB_MASK_CHANNEL2 0x00000004

/**
 * @def K_USB_MASK_CHANNEL3
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 3.
 */

#define K_USB_MASK_CHANNEL3 0x00000008

/**
 * @def K_USB_MASK_CHANNEL4
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 4.
 */

#define K_USB_MASK_CHANNEL4 0x00000010

/**
 * @def K_USB_MASK_CHANNEL5
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 5.
 */

#define K_USB_MASK_CHANNEL5 0x00000020

/**
 * @def K_USB_MASK_CHANNEL6
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 6.
 */

#define K_USB_MASK_CHANNEL6 0x00000040

/**
 * @def K_USB_MASK_CHANNEL7
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 7.
 */

#define K_USB_MASK_CHANNEL7 0x00000080

/**
 * @def K_USB_MASK_CHANNEL8
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 8.
 */

#define K_USB_MASK_CHANNEL8 0x00000100

/**
 * @def K_USB_MASK_CHANNEL9
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 9.
 */

#define K_USB_MASK_CHANNEL9 0x00000200

/**
 * @def K_USB_MASK_CHANNEL10
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 10.
 */

#define K_USB_MASK_CHANNEL10 0x00000400

/**
 * @def K_USB_MASK_CHANNEL11
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 11.
 */

#define K_USB_MASK_CHANNEL11 0x00000800

/**
 * @def K_USB_MASK_CHANNEL12
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 12. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_MASK_CHANNEL12 0x00001000

/**
 * @def K_USB_MASK_CHANNEL13
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 13. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_MASK_CHANNEL13 0x00002000

/**
 * @def K_USB_MASK_CHANNEL14
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 14. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_MASK_CHANNEL14 0x00004000

/**
 * @def K_USB_MASK_CHANNEL15
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 15. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_MASK_CHANNEL15 0x00008000

/**
 * @def K_USB_MASK_CHANNEL_ALL
 * @brief Constante dédiée aux fonctions usb_maskGlobalChannelInterrupt(),
 *        usb_unmaskGlobalChannelInterrupt() et usb_getGlobalChannelInterrupt().\n
 *        Définition du numéro de canal 1 à 15. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_MASK_CHANNEL_ALL 0x0000FFFF

/**
 *
 */

/**
 * @def K_USB_FULL_SPEED
 * @brief Constante dédiée aux fonctions usb_getPortSpeed() et usb_setDeviceSpeed().\n
 *        Définition de la vitesse du périphérique connecté sur le bus. En mode 'Device',
 *        cette constante indique que le coeur doit utiliser le PHY ULPI.
 */

#define K_USB_FULL_SPEED 0x00000001

/**
 * @def K_USB_LOW_SPEED
 * @brief Constante dédiée à la fonction usb_getPortSpeed().\n
 *        Définition de la vitesse du périphérique connecté sur le bus.
 */

#define K_USB_LOW_SPEED 0x00000002

/**
 * @def K_USB_HIGH_SPEED
 * @brief Constante dédiée aux fonctions usb_getPortSpeed() et usb_setDeviceSpeed().\n
 *        Définition de la vitesse du périphérique connecté sur le bus.
 */

#define K_USB_HIGH_SPEED 0x00000000

/**
 * @def K_USB_FULL_SPEED
 * @brief Constante dédiée à la fonction usb_setDeviceSpeed().\n
 *        Définition de la vitesse du périphérique connecté sur le bus. En mode 'Device',
 *        cette constante indique que le coeur doit utiliser le PHY interne.
 */

#define K_USB_FULL_SPEED_INTERNAL 0x00000003

/**
 *
 */

/**
 * @def K_USB_TEST_MODE_DISABLE
 * @brief Constante dédiée à la fonction usb_setTestMode().\n
 *        Définition d'une constante permettant de désactiver le mode test.
 */

#define K_USB_TEST_MODE_DISABLE 0x00000000

/**
 * @def K_USB_TEST_MODE_J
 * @brief Constante dédiée à la fonction usb_setTestMode().\n
 *        Définition d'une constante permettant le déclenchement d'une 'pattern' de
 *        type J sur le bus.
 */

#define K_USB_TEST_MODE_J 0x00000001

/**
 * @def K_USB_TEST_MODE_K
 * @brief Constante dédiée à la fonction usb_setTestMode().\n
 *        Définition d'une constante permettant le déclenchement d'une 'pattern' de
 *        type K sur le bus.
 */

#define K_USB_TEST_MODE_K 0x00000002

/**
 * @def K_USB_TEST_MODE_SE0_NAK
 * @brief Constante dédiée à la fonction usb_setTestMode().\n
 *        Définition d'une constante permettant le déclenchement d'une 'pattern' de
 *        type SE0_NAK sur le bus.
 */

#define K_USB_TEST_MODE_SE0_NAK 0x00000003

/**
 * @def K_USB_TEST_MODE_PACKET
 * @brief Constante dédiée à la fonction usb_setTestMode().\n
 *        Définition d'une constante permettant le déclenchement d'une 'pattern' de
 *        type PACKET sur le bus.
 */

#define K_USB_TEST_MODE_PACKET 0x00000004

/**
 * @def K_USB_TEST_FORCE_ENABLE
 * @brief Constante dédiée à la fonction usb_setTestMode().\n
 *        Définition d'une constante permettant le déclenchement d'une 'pattern' de
 *        type FORCE sur le bus.
 */

#define K_USB_TEST_FORCE_ENABLE 0x00000005

/**
 *
 */

/**
 * @def K_USB_OTGDP_PIN_FLAG
 * @brief Constante dédiée aux fonctions usb_getPortStatus() et usb_getSignalStatus().\n
 *        Définition d'une constante permettant de lire l'état de la broche OTG_DP.
 */

#define K_USB_OTGDP_PIN_FLAG 0x00000400

/**
 * @def K_USB_OTGDM_PIN_FLAG
 * @brief Constante dédiée aux fonctions usb_getPortStatus() et usb_getSignalStatus().\n
 *        Définition d'une constante permettant de lire l'état de la broche OTG_DM.
 */

#define K_USB_OTGDM_PIN_FLAG 0x00000800

/**
 * @def K_USB_SUSPENDED_FLAG
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante permettant de savoir si le coeur est en mode
 *        suspendu.
 */

#define K_USB_SUSPENDED_FLAG 0x00000080

/**
 * @def K_USB_OVERCURRENT_CHANGE_FLAG
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante permettant de savoir si une surcharge est
 *        apparue ou a disparu sur le bus.
 */

#define K_USB_OVERCURRENT_CHANGE_FLAG 0x00000020

/**
 * @def K_USB_OVERCURRENT_FLAG
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante permettant de savoir si une surcharge est
 *        présente sur le bus.
 */

#define K_USB_OVERCURRENT_FLAG 0x00000010

/**
 * @def K_USB_PORT_ENABLED_CHANGE_FLAG
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante permettant de savoir si le statut du port
 *        a changé (activé à désactivé ou inversement).
 */

#define K_USB_PORT_ENABLED_CHANGE_FLAG 0x00000008

/**
 * @def K_USB_PORT_ENABLED_FLAG
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante permettant de savoir le port est activé ou
 *        désactivé.
 */

#define K_USB_PORT_ENABLED_FLAG 0x00000004

/**
 * @def K_USB_PORT_DEVICE_CONNECTED_FLAG
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante permettant de savoir si un périphérique a
 *        été connecté sur le bus.
 */

#define K_USB_PORT_DEVICE_CONNECTED_FLAG 0x00000002

/**
 * @def K_USB_PORT_DEVICE_ATTACHED_FLAG
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante permettant de savoir si un périphérique est
 *        présent sur le bus.
 */

#define K_USB_PORT_DEVICE_ATTACHED_FLAG 0x00000001

/**
 *
 */

/**
 * @def K_USB_RESET_ENABLE
 * @brief Constante dédiée à la fonction usb_resetPort().\n
 *        Définition d'une constante permettant d'activer la réinitialisation
 *        du port.
 */

#define K_USB_RESET_ENABLE 0x00000100

/**
 * @def K_USB_RESET_DISABLE
 * @brief Constante dédiée à la fonction usb_resetPort().\n
 *        Définition d'une constante permettant désactiver la réinitialisation
 *        du port.
 */

#define K_USB_RESET_DISABLE 0x00000000

/**
 *
 */

/**
 * @def K_USB_SUSPEND_MODE_ENABLED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant l'état du port USB.
 */

#define K_USB_SUSPEND_MODE_ENABLED 0x00000080

/**
 * @def K_USB_SUSPEND_MODE_DISABLED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant l'état du port USB.
 */

#define K_USB_SUSPEND_MODE_DISABLED 0x00000000

/**
 *
 */

/**
 * @def K_USB_OVERCURRENT_DETECTED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant qu'une surcharge est présente sur
 *        le bus.
 */

#define K_USB_OVERCURRENT_DETECTED 0x00000010

/**
 * @def K_USB_OVERCURRENT_NOT_DETECTED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant qu'aucune surcharge n'est présente sur
 *        le bus.
 */

#define K_USB_OVERCURRENT_NOT_DETECTED 0x00000000

/**
 *
 */

/**
 * @def K_USB_OVERCURRENT_CHANGED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant que l'état du bus a changé.
 */

#define K_USB_OVERCURRENT_CHANGED 0x00000020

/**
 * @def K_USB_OVERCURRENT_CHANGED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant que l'état du bus n'a pas changé.
 */

#define K_USB_OVERCURRENT_NOT_CHANGED 0x00000000

/**
 *
 */

/**
 * @def K_USB_PORT_ENABLED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant que le port USB est activé.
 */

#define K_USB_PORT_ENABLED 0x00000004

/**
 * @def K_USB_OVERCURRENT_CHANGED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant que le port USB est désactivé.
 */

#define K_USB_PORT_DISABLED 0x00000000

/**
 *
 */

/**
 * @def K_USB_PORT_ENABLED_STATUS_CHANGED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant que le statut du port USB a
 *        changé.
 */

#define K_USB_PORT_ENABLED_STATUS_CHANGED 0x00000008

/**
 * @def K_USB_PORT_ENABLED_STATUS_NOT_CHANGED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant que le statut du port USB a
 *        changé.
 */

#define K_USB_PORT_ENABLED_STATUS_NOT_CHANGED 0x00000000

/**
 *
 */

/**
 * @def K_USB_DEVICE_CONNECTED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant qu'un périphérique s'est connecté
 *        sur le bus.
 */

#define K_USB_DEVICE_CONNECTED 0x00000002

/**
 * @def K_USB_DEVICE_NOT_CONNECTED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant qu'aucun périphérique ne s'est connecté
 *        sur le bus.
 */

#define K_USB_DEVICE_NOT_CONNECTED 0x00000000

/**
 * @def K_USB_DEVICE_ATTACHED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant qu'au périphérique est connecté sur
 *        le bus.
 */

#define K_USB_DEVICE_ATTACHED 0x00000001

/**
 * @def K_USB_DEVICE_NOT_ATTACHED
 * @brief Constante dédiée à la fonction usb_getPortStatus().\n
 *        Définition d'une constante indiquant qu'aucun périphérique n'est présent
 *        sur le bus.
 */

#define K_USB_DEVICE_NOT_ATTACHED 0x00000000

/**
 *
 */

/**
 *
 */

/**
 * @def K_USB_CHANNEL0
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 0.
 */

#define K_USB_CHANNEL0 0x00000000

/**
 * @def K_USB_CHANNEL1
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 1.
 */

#define K_USB_CHANNEL1 0x00000001

/**
 * @def K_USB_CHANNEL2
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 2.
 */

#define K_USB_CHANNEL2 0x00000002

/**
 * @def K_USB_CHANNEL3
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 3.
 */

#define K_USB_CHANNEL3 0x00000003

/**
 * @def K_USB_CHANNEL4
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 4.
 */

#define K_USB_CHANNEL4 0x00000004

/**
 * @def K_USB_CHANNEL5
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 5.
 */

#define K_USB_CHANNEL5 0x00000005

/**
 * @def K_USB_CHANNEL6
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 6.
 */

#define K_USB_CHANNEL6 0x00000006

/**
 * @def K_USB_CHANNEL7
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 7.
 */

#define K_USB_CHANNEL7 0x00000007

/**
 * @def K_USB_CHANNEL8
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 8.
 */

#define K_USB_CHANNEL8 0x00000008

/**
 * @def K_USB_CHANNEL9
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 9.
 */

#define K_USB_CHANNEL9 0x00000009

/**
 * @def K_USB_CHANNEL10
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 10.
 */

#define K_USB_CHANNEL10 0x0000000A

/**
 * @def K_USB_CHANNEL11
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 11.
 */

#define K_USB_CHANNEL11 0x0000000B

/**
 * @def K_USB_CHANNEL12
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 12. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_CHANNEL12 0x0000000C

/**
 * @def K_USB_CHANNEL13
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 13. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_CHANNEL13 0x0000000D

/**
 * @def K_USB_CHANNEL14
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 14. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_CHANNEL14 0x0000000E

/**
 * @def K_USB_CHANNEL15
 * @brief Constante dédiée à la fonction usb_sendLPMRequest().\n
 * @brief Constante dédiée aux fonction usb_enableChannel(), usb_disableChannel()
 *        et usb_setChannel().\n
 *        Définition de l'identifiant du canal 15. Cette constante est
 *        dédiée au périphérique USBOTG_HS.
 */

#define K_USB_CHANNEL15 0x0000000F

/**
 *
 */

/**
 * @def K_USB_CONTROL_ENDPOINT
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition du type de terminaison.
 */

#define K_USB_CONTROL_ENDPOINT 0x00000000

/**
 * @def K_USB_CONTROL_ENDPOINT
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition du type de terminaison.
 */

#define K_USB_ISOCHRONOUS_ENDPOINT 0x00000001

/**
 * @def K_USB_CONTROL_ENDPOINT
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition du type de terminaison.
 */

#define K_USB_BULK_ENDPOINT 0x00000002

/**
 * @def K_USB_CONTROL_ENDPOINT
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition du type de terminaison.
 */

#define K_USB_INTERRUPT_ENDPOINT 0x00000003

/**
 *
 */

/**
 * @def K_USB_FSHS_CHANNEL
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition de la vitesse de fonctionnement d'un canal.
 */

#define K_USB_FSHS_CHANNEL 0x00000000

/**
 * @def K_USB_LS_CHANNEL
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition de la vitesse de fonctionnement d'un canal.
 */

#define K_USB_LS_CHANNEL 0x00000001

/**
 *
 */

/**
 * @def K_USB_OUT_ENDPOINT
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition de la direction de la terminaison.
 */

#define K_USB_OUT_ENDPOINT 0x00000000

/**
 * @def K_USB_IN_ENDPOINT
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition de la direction de la terminaison.
 */

#define K_USB_IN_ENDPOINT 0x00000001

/**
 *
 */

/**
 * @def K_USB_SPLIT_MODE_DISABLE
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition d'une constante permettant la désactivation du mode SPLIT.
 */

#define K_USB_SPLIT_MODE_DISABLE 0x00000000

/**
 * @def K_USB_SPLIT_MODE_ENABLE
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition d'une constante permettant l'activation du mode SPLIT.
 */

#define K_USB_SPLIT_MODE_ENABLE 0x00000001

/**
 *
 */

/**
 * @def K_USB_START_SPLIT
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition d'une transaction de type START_SPLIT.
 */

#define K_USB_START_SPLIT 0x00000000

/**
 * @def K_USB_START_SPLIT
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition d'une transaction de type K_USB_COMPLETE_SPLIT.
 */

#define K_USB_COMPLETE_SPLIT 0x00000001

/**
 *
 */

/**
 * @def K_USB_ALL_PAYLOADS
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition d'une constante identifiant tous les paquets de données d'une
 *        transaction.
 */

#define K_USB_ALL_PAYLOADS 0x00000003

/**
 * @def K_USB_FIRST_PAYLOAD
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition d'une constante identifiant le premier paquets de données d'une
 *        transaction.
 */

#define K_USB_FIRST_PAYLOAD 0x00000002

/**
 * @def K_USB_MIDDLE_PAYLOAD
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition d'une constante identifiant le deuxième paquets de données d'une
 *        transaction.
 */

#define K_USB_MIDDLE_PAYLOAD 0x00000000

/**
 * @def K_USB_LAST_PAYLOAD
 * @brief Constante dédiée à la fonction usb_setChannel().\n
 *        Définition d'une constante identifiant le dernier (troisième) paquets de données
 *        d'une transaction.
 */

#define K_USB_LAST_PAYLOAD 0x00000001

/**
 *
 */

/**
 * @def K_USB_DATA_TOGGLE_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption TOGGLE_INTERRUPT.
 */

#define K_USB_DATA_TOGGLE_INTERRUPT 0x00000400

/**
 * @def K_USB_FRAME_OVERRUN_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption FRAME_INTERRUPT.
 */

#define K_USB_FRAME_OVERRUN_INTERRUPT 0x00000200

/**
 * @def K_USB_BABBLE_ERROR_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption BABBLE_INTERRUPT.
 */

#define K_USB_BABBLE_ERROR_INTERRUPT 0x00000100

/**
 * @def K_USB_TRANSACTION_ERROR_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption TRANSACTION_ERROR_INTERRUPT.\n
 *        Une erreur de transaction est définie comme un erreur de CRC, un timeout, un erreur de stuff,
 *        ou un mauvais 'EOP'.
 */

#define K_USB_TRANSACTION_ERROR_INTERRUPT 0x00000080

/**
 * @def K_USB_NYET_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption NYET_INTERRUPT.
 * @note Cette constante est dédiée au périphérique OTG_HS.
 */

#define K_USB_NYET_INTERRUPT 0x00000040

/**
 * @def K_USB_ACK_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption ACK_INTERRUPT.
 */

#define K_USB_ACK_INTERRUPT 0x00000020

/**
 * @def K_USB_NAK_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption NAK_INTERRUPT.
 */

#define K_USB_NAK_INTERRUPT 0x00000010

/**
 * @def K_USB_STALL_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption STALL_INTERRUPT.
 */

#define K_USB_STALL_INTERRUPT 0x00000008

/**
 * @def K_USB_AHB_ERROR_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption AHB_ERROR_INTERRUPT.
 * @note Cette constante est dédiée au périphérique OTG_HS. Elle est déclenchée en mode DMA uniquement.
 */

#define K_USB_AHB_ERROR_INTERRUPT 0x00000004

/**
 * @def K_USB_CHANNEL_HALTED_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption CHANNEL_HALTED_INTERRUPT.
 */

#define K_USB_CHANNEL_HALTED_INTERRUPT 0x00000002

/**
 * @def K_USB_TRANSFER_COMPLETED_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition de l'interruption TRANSFER_COMPLETED_INTERRUPT.
 */

#define K_USB_TRANSFER_COMPLETED_INTERRUPT 0x00000001

/**
 * @def K_USB_CHANNEL_ALL_INTERRUPTS
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition d'une constante permettant d'adresser toutes les interruptions.
 */

#define K_USB_CHANNEL_ALL_INTERRUPTS 0x000007FF

/**
 * @def K_USB_CHANNEL_GROUP_INTERRUPTS
 * @brief Constante dédiée aux fonctions usb_clearChannelInterruptFlag(), usb_getChannelInterruptMask(),
 *        usb_getChannelInterruptFlag(), usb_maskChannelInterrupt() et usb_unmaskChannelInterrupt().\n
 *        Définition d'une constante permettant d'adresser un groupe d'interruption.
 */

#define K_USB_CHANNEL_GROUP_INTERRUPTS 0x000007CE

/**
 *
 */

/**
 * @def K_USB_DMA_ALLOCATE_25_PERCENT_TO_FETCH_PERIODIC_ENDPOINT
 * @brief Constante dédiée à la fonction usb_setDMAPeriodicFetchingTime(). \n
 *        Définition de la durée allouée au moteur DMA pour traiter les terminaisons périodique de
 *        type IN (25%).
 */

#define K_USB_DMA_ALLOCATE_25_PERCENT_TO_FETCH_PERIODIC_ENDPOINT 0x00000000

/**
 * @def K_USB_DMA_ALLOCATE_50_PERCENT_TO_FETCH_PERIODIC_ENDPOINT
 * @brief Constante dédiée à la fonction usb_setDMAPeriodicFetchingTime(). \n
 *        Définition de la durée allouée au moteur DMA pour traiter les terminaisons périodique de
 *        type IN (25%).
 */

#define K_USB_DMA_ALLOCATE_50_PERCENT_TO_FETCH_PERIODIC_ENDPOINT 0x01000000

/**
 * @def K_USB_DMA_ALLOCATE_75_PERCENT_TO_FETCH_PERIODIC_ENDPOINT
 * @brief Constante dédiée à la fonction usb_setDMAPeriodicFetchingTime(). \n
 *        Définition de la durée allouée au moteur DMA pour traiter les terminaisons périodique de
 *        type IN (25%).
 */

#define K_USB_DMA_ALLOCATE_75_PERCENT_TO_FETCH_PERIODIC_ENDPOINT 0x02000000

/**
 *
 */

/**
 * @def K_USB_80_PERCENTS_OF_FRAME_INTERVAL
 * @brief Constante dédiée à la fonction usb_setEOFInterruptThreshold(). \n
 *        Définition du seuil de déclenchement de l'interruption 'End Of Frame Interrupt'.
 */

#define K_USB_80_PERCENTS_OF_FRAME_INTERVAL 0x00000000

/**
 * @def K_USB_85_PERCENTS_OF_FRAME_INTERVAL
 * @brief Constante dédiée à la fonction usb_setEOFInterruptThreshold(). \n
 *        Définition du seuil de déclenchement de l'interruption 'End Of Frame Interrupt'.
 */

#define K_USB_85_PERCENTS_OF_FRAME_INTERVAL 0x00000800

/**
 * @def K_USB_90_PERCENTS_OF_FRAME_INTERVAL
 * @brief Constante dédiée à la fonction usb_setEOFInterruptThreshold(). \n
 *        Définition du seuil de déclenchement de l'interruption 'End Of Frame Interrupt'.
 */

#define K_USB_90_PERCENTS_OF_FRAME_INTERVAL 0x00001000

/**
 * @def K_USB_95_PERCENTS_OF_FRAME_INTERVAL
 * @brief Constante dédiée à la fonction usb_setEOFInterruptThreshold(). \n
 *        Définition du seuil de déclenchement de l'interruption 'End Of Frame Interrupt'.
 */

#define K_USB_95_PERCENTS_OF_FRAME_INTERVAL 0x00001800

/**
 *
 */

/**
 * @def K_USB_NZL_RESPONSE_IS_STALL
 * @brief Constante dédiée à la fonction usb_overwriteNZLPacketHandshake(). \n
 *        Définition du comportement du coeur à la réception d'un paquet de type
 *        'NonZeroLength'. Le coeur envoie un STALL à l'hote et ne transmet pas le
 *        paquet reçu à l'application.
 */

#define K_USB_NZL_RESPONSE_IS_STALL 0x00000004

/**
 * @def K_USB_NZL_RESPONSE_IS_DEFAULT
 * @brief Constante dédiée à la fonction usb_overwriteNZLPacketHandshake(). \n
 *        Définition du comportement du coeur à la réception d'un paquet de type
 *        'NonZeroLength'. Le coeur envoie un statut fonction de l'état de la terminaison
 *        et transmet le paquet reçu à l'application.
 */

#define K_USB_NZL_RESPONSE_IS_DEFAULT 0x00000000

/**
 *
 */

/**
 * @def K_USB_GLOBAL_OUT_NAK
 * @brief Constante dédiée aux fonctions usb_getGlobalOverwriteStatus(), usb_enableGlobalOverwriteStatus()
 *        et usb_disableGlobalOverwriteStatus. \n
 *        Définition du statut GLOBAL_OUT_NAK.
 */

#define K_USB_GLOBAL_OUT_NAK 0x00000003

/**
 * @def K_USB_GLOBAL_IN_NAK
 * @brief Constante dédiée aux fonctions usb_getGlobalOverwriteStatus(), usb_enableGlobalOverwriteStatus()
 *        et usb_disableGlobalOverwriteStatus. \n
 *        Définition du statut GLOBAL_IN_NAK.
 */

#define K_USB_GLOBAL_IN_NAK 0x00000002

/**
 * @def K_HANDSHAKE_OVERWRITE
 * @brief Constante dédiée à la fonction usb_getGlobalOverwriteStatus(). \n
 *        Définition du comportement des FIFO de type IN/OUT.
 *        Pour une terminaison de type OUT, aucune donnée n'est écrite dans le FIFO de réception,
 *        le statut NAK est envoyé pour tous les paquets à l'exception des paquets de type SETUP.
 *        Les paquets ISOCHRONES font exception à la régles précédente.
 *        Pour une terminaison de type IN, le statut NAK est envoyé pour chaque entrée non périodique.
 */

#define K_HANDSHAKE_OVERWRITE 0x00000001

/**
 * @def K_HANDSHAKE_OVERWRITE
 * @brief Constante dédiée à la fonction usb_getGlobalOverwriteStatus(). \n
 *        Définition du comportement des FIFO de type IN/OUT. Les statuts envoyés répondent
 *        à un fonctionnement normal.
 */

#define K_HANDSHAKE_DEFAULT 0x00000000

/**
 *
 */

/**
 * @def K_USB_ERRATIC_ERROR_DETECTED
 * @brief Constante dédiée à la fonction usb_getErraticErrorStatus(). \n
 *        Définition d'une constante indiquant qu'une erreur erratique a été détectée.
 */

#define K_USB_ERRATIC_ERROR_DETECTED 0x00000001

/**
 * @def K_USB_ERRATIC_ERROR_NOT_DETECTED
 * @brief Constante dédiée à la fonction usb_getErraticErrorStatus(). \n
 *        Définition d'une constante indiquant qu'aucune erreur erratique n'a été détectée.
 */

#define K_USB_ERRATIC_ERROR_NOT_DETECTED 0x00000000

/**
 *
 */

/**
 * @def K_USB_SUSPENDED_STATE
 * @brief Constante dédiée à la fonction usb_getSuspendStatus(). \n
 *        Définition d'une constante indiquant que le bus est dans l'état suspendu.
 */

#define K_USB_SUSPENDED_STATE 0x00000001

/**
 * @def K_USB_NOT_SUSPENDED_STATE
 * @brief Constante dédiée à la fonction usb_getSuspendStatus(). \n
 *        Définition d'une constante indiquant que le bus n'est pas dans l'état suspendu.
 */

#define K_USB_NOT_SUSPENDED_STATE 0x00000000

/**
 *
 */

/**
 * @def K_USB_IN_ENDPOINT_NAK_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskINEndpointInterrupt(),
 *        usb_unmaskINEndpointInterrupt(), usb_clearINEndpointInterrupt()
 *        et usb_getINEndpointInterrupt(). \n
 *        Définition de l'interruption NAK_INTERRUPT. L'utilisation des fonctions
 *        usb_clearINEndpointInterrupt() et usb_getINEndpointInterrupt() avec
 *        cette interruption peut être effectuée uniquement pour le
 *        périphérique USB_OTGHS.
 */

#define K_USB_IN_ENDPOINT_NAK_INTERRUPT 0x00002000

/**
 * @def K_USB_IN_ENDPOINT_BABBLE_ERROR_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_clearINEndpointInterrupt()
 *        et usb_getINEndpointInterrupt(). \n
 *        Définition de l'interruption BABBLE_ERROR_INTERRUPT. Elle est dédiée au
 *        périphérique USB_OTGHS.
 */

#define K_USB_IN_ENDPOINT_BABBLE_ERROR_INTERRUPT 0x00001000

/**
 * @def K_USB_IN_ENDPOINT_PACKET_DROPPED_STATUS
 * @brief Constante dédiée aux fonctions usb_clearINEndpointInterrupt()
 *        et usb_getINEndpointInterrupt(). \n
 *        Définition du statut PACKET_DROPPED. Il est dédiée au périphérique USB_OTGHS.
 */

#define K_USB_IN_ENDPOINT_PACKET_DROPPED_STATUS 0x00000800

/**
 * @def K_USB_IN_ENDPOINT_BNA_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskINEndpointInterrupt(),
 *        usb_unmaskINEndpointInterrupt(), usb_clearINEndpointInterrupt()
 *        et usb_getINEndpointInterrupt(). \n
 *        Définition de l'interruption BNA_INTERRUPT ('Buffer Not Available'). Elle est
 *        dédiée au périphérique USB_OTGHS.
 */

#define K_USB_IN_ENDPOINT_BNA_INTERRUPT 0x00000200

/**
 * @def K_USB_IN_ENDPOINT_TXFIFO_UNDERRUN_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskINEndpointInterrupt(),
 *        usb_unmaskINEndpointInterrupt(), usb_clearINEndpointInterrupt()
 *        et usb_getINEndpointInterrupt(). \n
 *        Définition de l'interruption FIFO_TX_FIFO_UNDERRUN_INTERRUPT. Elle est dédiée au
 *        périphérique USB_OTGHS.
 */

#define K_USB_IN_ENDPOINT_TXFIFO_UNDERRUN_INTERRUPT 0x00000100

/**
 * @def K_USB_IN_ENDPOINT_TXFIFO_EMPTY_INTERRUPT
 * @brief Constante dédiée à la fonction usb_getINEndpointInterrupt(). \n
 *        Définition de l'interruption TXFIFO_EMPTY.
 */

#define K_USB_IN_ENDPOINT_TXFIFO_EMPTY_INTERRUPT 0x00000080

/**
 * @def K_USB_IN_ENDPOINT_NAK_EFFECTIVE_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskINEndpointInterrupt() et
 *        usb_unmaskINEndpointInterrupt() et usb_getINEndpointInterrupt(). \n
 *        Définition de l'interruption NAK_EFFECTIVE_INTERRUPT.
 */

#define K_USB_IN_ENDPOINT_NAK_EFFECTIVE_INTERRUPT 0x00000040

/**
 * @def K_USB_IN_ENDPOINT_MISMATCH_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskINEndpointInterrupt() et
 *        usb_unmaskINEndpointInterrupt(). \n
 *        Définition de l'interruption ENDPOINT_MISMATCH_INTERRUPT.
 */

#define K_USB_IN_ENDPOINT_MISMATCH_INTERRUPT 0x00000020

/**
 * @def K_USB_IN_ENDPOINT_TOKEN_RECEIVED_WHEN_TXFIFO_EMPTY_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskINEndpointInterrupt() et
 *        usb_unmaskINEndpointInterrupt(), usb_clearINEndpointInterrupt()
 *        et usb_getINEndpointInterrupt(). \n
 *        Définition de l'interruption INTOKEN_RECEIVED_WHEN_TXFIFO_EMPTY_INTERRUPT.
 */

#define K_USB_IN_ENDPOINT_TOKEN_RECEIVED_WHEN_TXFIFO_EMPTY_INTERRUPT 0x00000010

/**
 * @def K_USB_IN_ENDPOINT_TIMEOUT_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskINEndpointInterrupt(),
 *        usb_unmaskINEndpointInterrupt(), usb_clearINEndpointInterrupt()
 *        et usb_getINEndpointInterrupt(). \n
 *        Définition de l'interruption TIMEOUT_INTERRUPT.
 */

#define K_USB_IN_ENDPOINT_TIMEOUT_INTERRUPT 0x00000008

/**
 * @def K_USB_IN_ENDPOINT_DISABLED_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskINEndpointInterrupt(),
 *        usb_unmaskINEndpointInterrupt(), usb_clearINEndpointInterrupt()
 *        et usb_getINEndpointInterrupt(). \n
 *        Définition de l'interruption ENDPOINT_DISABLE_INTERRUPT.
 */

#define K_USB_IN_ENDPOINT_DISABLED_INTERRUPT 0x00000002

/**
 * @def K_USB_IN_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskINEndpointInterrupt(),
 *        usb_unmaskINEndpointInterrupt(), usb_clearINEndpointInterrupt(),
 *        usb_getINEndpointInterrupt(). \n
 *        Définition de l'interruption TRANSFER_COMPLETED_INTERRUPT.
 */

#define K_USB_IN_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT 0x00000001

/**
 *
 */

/**
 * @def K_USB_OUT_ENDPOINT_NYET_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskOUTEndpointInterrupt() et
 *        usb_unmaskOUTEndpointInterrupt(). \n
 *        Définition de l'interruption NYET_INTERRUPT. Elle est dédiée au
 *        périphérique USB_OTGHS.
 */

#define K_USB_OUT_ENDPOINT_NYET_INTERRUPT 0x00004000

/**
 * @def K_USB_OUT_ENDPOINT_BNA_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskOUTEndpointInterrupt() et
 *        usb_unmaskOUTEndpointInterrupt(). \n
 *        Définition de l'interruption BNA_INTERRUPT. Elle est dédiée au
 *        périphérique USB_OTGHS.
 * @note Bit non implémenté sur la plateforme STM32F746.
 */

#define K_USB_OUT_ENDPOINT_BNA_INTERRUPT 0x00000200

/**
 * @def K_USB_OUT_ENDPOINT_FIFO_UNDERRUN_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskOUTEndpointInterrupt() et
 *        usb_unmaskOUTEndpointInterrupt(). \n
 *        Définition de l'interruption FIFO_UNDERRUN_INTERRUPT. Elle est dédiée au
 *        périphérique USB_OTGHS.
 */

#define K_USB_OUT_ENDPOINT_FIFO_UNDERRUN_INTERRUPT 0x00000100

/**
 * @def K_USB_OUT_ENDPOINT_B2B_SETUP_PACKETS_RECEIVED_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskOUTEndpointInterrupt() et
 *        usb_unmaskOUTEndpointInterrupt(), usb_getOUTEndpointInterrupt()
 *        et usb_clearOUTEndpointInterrupt(). \n
 *        Définition de l'interruption BACK_TO_BACK_SETUP_PACKETS_RECEIVED_INTERRUPT.
 *        L'utilisation des fonctions usb_maskOUTEndpointInterrupt() et
 *        usb_unmaskOUTEndpointInterrupt() avec cette interruption peut être effectuée
 *        uniquement avec le périphérique USB_OTGHS.
 */

#define K_USB_OUT_ENDPOINT_B2B_SETUP_PACKETS_RECEIVED_INTERRUPT 0x00000040

/**
 * @def K_USB_OUT_ENDPOINT_MISMATCH_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskOUTEndpointInterrupt() et
 *        usb_unmaskOUTEndpointInterrupt(), usb_getOUTEndpointInterrupt()
 *        et usb_clearOUTEndpointInterrupt(). \n
 *        Définition de l'interruption MISMATCH_INTERRUPT.
 */

#define K_USB_OUT_ENDPOINT_MISMATCH_INTERRUPT 0x00000010

/**
 * @def K_USB_OUT_ENDPOINT_SETUP_PHASE_DONE_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskOUTEndpointInterrupt() et
 *        usb_unmaskOUTEndpointInterrupt(), usb_getOUTEndpointInterrupt()
 *        et usb_clearOUTEndpointInterrupt(). \n
 *        Définition de l'interruption SETUP_PHASE_DONE_INTERRUPT.
 */

#define K_USB_OUT_ENDPOINT_SETUP_PHASE_DONE_INTERRUPT 0x00000008

/**
 * @def K_USB_OUT_ENDPOINT_DISABLED_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskOUTEndpointInterrupt() et
 *        usb_unmaskOUTEndpointInterrupt(), usb_getOUTEndpointInterrupt()
 *        et usb_clearOUTEndpointInterrupt(). \n
 *        Définition de l'interruption ENDPOINT_DISABLED_INTERRUPT.
 */

#define K_USB_OUT_ENDPOINT_DISABLED_INTERRUPT 0x00000002

/**
 * @def K_USB_OUT_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT
 * @brief Constante dédiée aux fonctions usb_maskOUTEndpointInterrupt(),
 *        usb_unmaskOUTEndpointInterrupt(), usb_getOUTEndpointInterrupt()
 *        et usb_clearOUTEndpointInterrupt(). \n
 *        Définition de l'interruption TRANSFER_COMPLETED_INTERRUPT.
 */

#define K_USB_OUT_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT 0x00000001

/**
 *
 */

/**
 * @def K_USB_MASK_IN_ENDPOINT0
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison IN0.
 * @note La terminaison 0 est bidirectionnelle.
 */

#define K_USB_MASK_IN_ENDPOINT0 0x00000001

/**
 * @def K_USB_MASK_IN_ENDPOINT1
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison IN1.
 */

#define K_USB_MASK_IN_ENDPOINT1 0x00000002

/**
 * @def K_USB_MASK_IN_ENDPOINT2
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison IN2.
 */

#define K_USB_MASK_IN_ENDPOINT2 0x00000004

/**
 * @def K_USB_MASK_IN_ENDPOINT3
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison IN3.
 */

#define K_USB_MASK_IN_ENDPOINT3 0x00000008

/**
 * @def K_USB_MASK_IN_ENDPOINT4
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison IN4.
 */

#define K_USB_MASK_IN_ENDPOINT4 0x00000010

/**
 * @def K_USB_MASK_IN_ENDPOINT5
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison IN5.
 */

#define K_USB_MASK_IN_ENDPOINT5 0x00000020

/**
 * @def K_USB_MASK_IN_ENDPOINT6
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison IN6.
 *        Cette constante est dédiées au périphérique USB_OTGHS.
 */

#define K_USB_MASK_IN_ENDPOINT6 0x00000040

/**
 * @def K_USB_MASK_IN_ENDPOINT7
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison IN7.
 *        Cette constante est dédiées au périphérique USB_OTGHS.
 */

#define K_USB_MASK_IN_ENDPOINT7 0x00000080

/**
 * @def K_USB_MASK_IN_ENDPOINT8
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison IN8.
 *        Cette constante est dédiées au périphérique USB_OTGHS.
 */

#define K_USB_MASK_IN_ENDPOINT8 0x00000100

/**
 * @def K_USB_MASK_ALL_IN_ENDPOINT
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de toutes les terminaisons de type IN.
 */

#define K_USB_MASK_ALL_IN_ENDPOINT 0x0000FFFF

/**
 *
 */

/**
 * @def K_USB_MASK_OUT_ENDPOINT0
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison OUT0.
 * @note La terminaison 0 est bidirectionnelle.
 */

#define K_USB_MASK_OUT_ENDPOINT0 0x00010000

/**
 * @def K_USB_MASK_OUT_ENDPOINT1
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison OUT1.
 */

#define K_USB_MASK_OUT_ENDPOINT1 0x00020000

/**
 * @def K_USB_MASK_OUT_ENDPOINT2
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison OUT2.
 */

#define K_USB_MASK_OUT_ENDPOINT2 0x00040000

/**
 * @def K_USB_MASK_OUT_ENDPOINT3
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison OUT3.
 */

#define K_USB_MASK_OUT_ENDPOINT3 0x00080000

/**
 * @def K_USB_MASK_OUT_ENDPOINT4
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison OUT4.
 */

#define K_USB_MASK_OUT_ENDPOINT4 0x00100000

/**
 * @def K_USB_MASK_OUT_ENDPOINT5
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison OUT5.
 */

#define K_USB_MASK_OUT_ENDPOINT5 0x00200000

/**
 * @def K_USB_MASK_OUT_ENDPOINT6
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison OUT6.
 *        Cette constante est dédiées au périphérique USB_OTGHS.
 */

#define K_USB_MASK_OUT_ENDPOINT6 0x00400000

/**
 * @def K_USB_MASK_OUT_ENDPOINT7
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison OUT7.
 *        Cette constante est dédiées au périphérique USB_OTGHS.
 */

#define K_USB_MASK_OUT_ENDPOINT7 0x00800000

/**
 * @def K_USB_MASK_OUT_ENDPOINT7
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de la terminaison OUT8.
 *        Cette constante est dédiées au périphérique USB_OTGHS.
 */

#define K_USB_MASK_OUT_ENDPOINT8 0x01000000

/**
 * @def K_USB_MASK_ALL_IN_ENDPOINT
 * @brief Constante dédiée aux fonctions usb_maskGlobalEndpointInterrupt()
 *        usb_unmaskGlobalEndpointInterrupt() et usb_getGlobalEndpointInterrupt(). \n
 *        Définition de l'identifiant de toutes les terminaisons de type OUT.
 */

#define K_USB_MASK_ALL_OUT_ENDPOINT 0xFFFF0000

/**
 *
 */

/**
 * @def K_USB_THRESHOLD_RECEIVE_DIRECTION
 * @brief Constante dédiée aux fonctions usb_enableThreshold() et usb_disableThreshold(). \n
 *        Définition de l'identifiant permettant d'activer ou de désactiver les transferts
 *        par seuil lors d'une réception.
 */

#define K_USB_THRESHOLD_RECEIVE_DIRECTION 0x00010000

/**
 * @def K_USB_THRESHOLD_NON_ISOCHRONOUS_IN_ENDPOINT
 * @brief Constante dédiée aux fonctions usb_enableThreshold() et usb_disableThreshold(). \n
 *        Définition de l'identifiant permettant d'activer ou de désactiver les transferts
 *        par seuil pour les terminaisons de type non isochrones.
 */

#define K_USB_THRESHOLD_NON_ISOCHRONOUS_IN_ENDPOINT 0x00000001

/**
 * @def K_USB_THRESHOLD_ISOCHRONOUS_IN_ENDPOINT
 * @brief Constante dédiée aux fonctions usb_enableThreshold() et usb_disableThreshold(). \n
 *        Définition de l'identifiant permettant d'activer ou de désactiver les transferts
 *        par seuil pour les terminaisons de type isochrones.
 */

#define K_USB_THRESHOLD_ISOCHRONOUS_IN_ENDPOINT 0x00000002

/**
 *
 */

/**
 * @def K_USB_RECEIVE_DIRECTION
 * @brief Constante dédiée à la fonction \ref usb_setThreshold. \n
 *        Définition de l'identifiant permettant de configurer le seuil de déclenchement
 *        des transferts du bus AHB vers le bus USB ou inversement.
 */

#define K_USB_RECEIVE_DIRECTION 0x00000011

/**
 * @def K_USB_TRANSMIT_DIRECTION
 * @brief Constante dédiée à la fonction \ref usb_setThreshold. \n
 *        Définition de l'identifiant permettant de configurer le seuil de déclenchement
 *        des transferts du bus AHB vers le bus USB ou inversement.
 */

#define K_USB_TRANSMIT_DIRECTION 0x00000002

/**
 *
 */

/**
 * @def K_USB_IN_ENDPOINT0
 * @brief Constante dédiée aux fonctions \ref usb_enableINEndpoint() et usb_disableINEndpoint().
 *        usb_setINEndpoint(), usb_setINEndpointFlag(), usb_clearINEndpointFlag(),
 *        usb_getINEndpointPacketCount() et usb_getINEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 0 de type IN.
 */

#define K_USB_IN_ENDPOINT0 0x00000000

/**
 * @def K_USB_IN_ENDPOINT1
 * @brief Constante dédiée aux fonctions \ref usb_enableINEndpoint() et usb_disableINEndpoint().
 *        usb_setINEndpoint(), usb_setINEndpointFlag(), usb_clearINEndpointFlag(),
 *        usb_getINEndpointPacketCount() et usb_getINEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 1 de type IN.
 */

#define K_USB_IN_ENDPOINT1 0x00000001

/**
 * @def K_USB_IN_ENDPOINT2
 * @brief Constante dédiée aux fonctions \ref usb_enableINEndpoint() et usb_disableINEndpoint().
 *        usb_setINEndpoint(), usb_setINEndpointFlag(), usb_clearINEndpointFlag(),
 *        usb_getINEndpointPacketCount() et usb_getINEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 2 de type IN.
 */

#define K_USB_IN_ENDPOINT2 0x00000002

/**
 * @def K_USB_IN_ENDPOINT3
 * @brief Constante dédiée aux fonctions \ref usb_enableINEndpoint() et usb_disableINEndpoint().
 *        usb_setINEndpoint(), usb_setINEndpointFlag(), usb_clearINEndpointFlag(),
 *        usb_getINEndpointPacketCount() et usb_getINEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 3 de type IN.
 */

#define K_USB_IN_ENDPOINT3 0x00000003

/**
 * @def K_USB_IN_ENDPOINT4
 * @brief Constante dédiée aux fonctions \ref usb_enableINEndpoint() et usb_disableINEndpoint().
 *        usb_setINEndpoint(), usb_setINEndpointFlag(), usb_clearINEndpointFlag(),
 *        usb_getINEndpointPacketCount() et usb_getINEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 4 de type IN.
 */

#define K_USB_IN_ENDPOINT4 0x00000004

/**
 * @def K_USB_IN_ENDPOINT5
 * @brief Constante dédiée aux fonctions \ref usb_enableINEndpoint() et usb_disableINEndpoint().
 *        usb_setINEndpoint(), usb_setINEndpointFlag(), usb_clearINEndpointFlag(),
 *        usb_getINEndpointPacketCount() et usb_getINEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 5 de type IN.
 */

#define K_USB_IN_ENDPOINT5 0x00000005

/**
 * @def K_USB_IN_ENDPOINT6
 * @brief Constante dédiée aux fonctions \ref usb_enableINEndpoint() et usb_disableINEndpoint().
 *        usb_setINEndpoint(), usb_setINEndpointFlag(), usb_clearINEndpointFlag(),
 *        usb_getINEndpointPacketCount() et usb_getINEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 6 de type IN. Elle est dédiée au périphérique USB_OTGHS.
 */

#define K_USB_IN_ENDPOINT6 0x00000006

/**
 * @def K_USB_IN_ENDPOINT7
 * @brief Constante dédiée aux fonctions \ref usb_enableINEndpoint() et usb_disableINEndpoint().
 *        usb_setINEndpoint(), usb_setINEndpointFlag(), usb_clearINEndpointFlag(),
 *        usb_getINEndpointPacketCount() et usb_getINEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 7 de type IN. Elle est dédiée au périphérique USB_OTGHS.
 */

#define K_USB_IN_ENDPOINT7 0x00000007

/**
 * @def K_USB_IN_ENDPOINT8
 * @brief Constante dédiée aux fonctions \ref usb_enableINEndpoint() et usb_disableINEndpoint().
 *        usb_setINEndpoint(), usb_setINEndpointFlag(), usb_clearINEndpointFlag(),
 *        usb_getINEndpointPacketCount() et usb_getINEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 8 de type IN. Elle est dédiée au périphérique USB_OTGHS.
 */

#define K_USB_IN_ENDPOINT8 0x00000008

/**
 *
 */

/**
 * @def K_USB_OUT_ENDPOINT0
 * @brief Constante dédiée aux fonctions \ref usb_enableOUTEndpoint() et usb_disableOUTEndpoint().
 *        usb_setOUTEndpoint(), usb_setOUTEndpointFlag(), usb_setOUTEndpointFlag(),
 *        usb_getOUTEndpointPacketCount() et usb_getOUTEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 0 de type OUT.
 */

#define K_USB_OUT_ENDPOINT0 0x00000000

/**
 * @def K_USB_OUT_ENDPOINT1
 * @brief Constante dédiée aux fonctions \ref usb_enableOUTEndpoint() et usb_disableOUTEndpoint().
 *        usb_setOUTEndpoint(), usb_setOUTEndpointFlag(), usb_setOUTEndpointFlag(),
 *        usb_getOUTEndpointPacketCount() et usb_getOUTEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 1 de type OUT.
 */

#define K_USB_OUT_ENDPOINT1 0x00000001

/**
 * @def K_USB_OUT_ENDPOINT2
 * @brief Constante dédiée aux fonctions \ref usb_enableOUTEndpoint() et usb_disableOUTEndpoint().
 *        usb_setOUTEndpoint(), usb_setOUTEndpointFlag(), usb_setOUTEndpointFlag(),
 *        usb_getOUTEndpointPacketCount() et usb_getOUTEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 2 de type OUT.
 */

#define K_USB_OUT_ENDPOINT2 0x00000002

/**
 * @def K_USB_OUT_ENDPOINT3
 * @brief Constante dédiée aux fonctions \ref usb_enableOUTEndpoint() et usb_disableOUTEndpoint().
 *        usb_setOUTEndpoint(), usb_setOUTEndpointFlag(), usb_setOUTEndpointFlag(),
 *        usb_getOUTEndpointPacketCount() et usb_getOUTEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 3 de type OUT.
 */

#define K_USB_OUT_ENDPOINT3 0x00000003

/**
 * @def K_USB_OUT_ENDPOINT4
 * @brief Constante dédiée aux fonctions \ref usb_enableOUTEndpoint() et usb_disableOUTEndpoint().
 *        usb_setOUTEndpoint(), usb_setOUTEndpointFlag(), usb_setOUTEndpointFlag(),
 *        usb_getOUTEndpointPacketCount() et usb_getOUTEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 4 de type OUT.
 */

#define K_USB_OUT_ENDPOINT4 0x00000004

/**
 * @def K_USB_OUT_ENDPOINT5
 * @brief Constante dédiée aux fonctions \ref usb_enableOUTEndpoint() et usb_disableOUTEndpoint().
 *        usb_setOUTEndpoint(), usb_setOUTEndpointFlag(), usb_setOUTEndpointFlag(),
 *        usb_getOUTEndpointPacketCount() et usb_getOUTEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 5 de type OUT.
 */

#define K_USB_OUT_ENDPOINT5 0x00000005

/**
 * @def K_USB_OUT_ENDPOINT6
 * @brief Constante dédiée aux fonctions \ref usb_enableOUTEndpoint() et usb_disableOUTEndpoint().
 *        usb_setOUTEndpoint(), usb_setOUTEndpointFlag(), usb_setOUTEndpointFlag(),
 *        usb_getOUTEndpointPacketCount() et usb_getOUTEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 6 de type OUT.
 *        Elle est dédiée au périphérique USB_OTGHS.
 */

#define K_USB_OUT_ENDPOINT6 0x00000006

/**
 * @def K_USB_OUT_ENDPOINT7
 * @brief Constante dédiée aux fonctions \ref usb_enableOUTEndpoint() et usb_disableOUTEndpoint().
 *        usb_setOUTEndpoint(), usb_setOUTEndpointFlag(), usb_setOUTEndpointFlag(),
 *        usb_getOUTEndpointPacketCount() et usb_getOUTEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 7 de type OUT.
 *        Elle est dédiée au périphérique USB_OTGHS.
 */

#define K_USB_OUT_ENDPOINT7 0x00000007

/**
 * @def K_USB_OUT_ENDPOINT8
 * @brief Constante dédiée aux fonctions \ref usb_enableOUTEndpoint() et usb_disableOUTEndpoint().
 *        usb_setOUTEndpoint(), usb_setOUTEndpointFlag(), usb_setOUTEndpointFlag(),
 *        usb_getOUTEndpointPacketCount() et usb_getOUTEndpointTransfertSize(). \n
 *        Identifiant de la terminaison 8 de type OUT.
 *        Elle est dédiée au périphérique USB_OTGHS.
 */

#define K_USB_OUT_ENDPOINT8 0x00000008

/**
 *
 */

/**
 * @def K_USB_CONTROL_ENDPOINT
 * @brief Constante dédiée aux fonctions usb_setINEndpoint() et usb_setOUTEndpoint(). \n
 *        Identifiant du type d'une terminaison (CTRL).
 */

#define K_USB_CONTROL_ENDPOINT 0x00000000

/**
 * @def K_USB_ISOCHRONOUS_ENDPOINT
 * @brief Constante dédiée aux fonctions usb_setINEndpoint() et usb_setOUTEndpoint(). \n
 *        Identifiant du type d'une terminaison (ISOCHRONOUS).
 */

#define K_USB_ISOCHRONOUS_ENDPOINT 0x00000001

/**
 * @def K_USB_BULK_ENDPOINT
 * @brief Constante dédiée aux fonctions usb_setINEndpoint() et usb_setOUTEndpoint(). \n
 *        Identifiant du type d'une terminaison (BULK).
 */

#define K_USB_BULK_ENDPOINT 0x00000002

/**
 * @def K_USB_INTERRUPT_ENDPOINT
 * @brief Constante dédiée aux fonctions usb_setINEndpoint() et usb_setOUTEndpoint(). \n
 *        Identifiant du type d'une terminaison (INTERRUPT).
 */

#define K_USB_INTERRUPT_ENDPOINT 0x00000003

/**
 *
 */

/**
 * @def K_USB_ENDPOINT_ACTIVE
 * @brief Constante dédiée aux fonctions usb_setINEndpoint() et usb_setOUTEndpoint(). \n
 *        Elle permet d'indiquer au coeur que la terminaison est active dans
 *        la configuration courante.
 */

#define K_USB_ENDPOINT_ACTIVE 0x00000001

/**
 * @def K_USB_ENDPOINT_NOT_ACTIVE
 * @brief Constante dédiée aux fonctions usb_setINEndpoint() et usb_setOUTEndpoint(). \n
 *        Elle permet d'indiquer au coeur que la terminaison n'est pas active dans
 *        la configuration courante.
 */

#define K_USB_ENDPOINT_NOT_ACTIVE 0x00000000

/**
 *
 */

/**
 * @def K_USB_FLAG_EVEN_FRAME
 * @brief Constante dédiée aux fonctions usb_setINEndpointFlag() et usb_setOUTEndpointFlag(). \n
 *        Définition du drapeau EVEN_FRAME dédié aux terminaisons isochrones.
 *        Configuration du champ EONUM à la valeur EVEN_FRAME.
 */

#define K_USB_FLAG_EVEN_FRAME 0x10000000

/**
 * @def K_USB_FLAG_PID_DATA0
 * @brief Constante dédiée aux fonctions usb_setINEndpointFlag() et usb_setOUTEndpointFlag(). \n
 *        Définition du drapeau PID_DATA0 dédié aux terminaisons 'BULK' ou 'INTERRUPT'.
 *        Configuration du champ DPID à la valeur DATA0.
 */

#define K_USB_FLAG_PID_DATA0 0x10000000

/**
 * @def K_USB_FLAG_ODD_FRAME
 * @brief Constante dédiée aux fonctions usb_setINEndpointFlag() et usb_setOUTEndpointFlag(). \n
 *        Définition du drapeau ODD_FRAME dédié aux terminaisons isochrones de
 *        type IN et OUT. Configuration du champ EONUM à la valeur ODD_FRAME.
 */

#define K_USB_FLAG_ODD_FRAME 0x20000000

/**
 * @def K_USB_FLAG_PID_DATA0
 * @brief Constante dédiée à la fonction usb_setOUTEndpointFlag(). \n
 *        Définition du drapeau PID_DATA1 dédié aux terminaisons 'BULK' ou 'INTERRUPT'.
 *        Configuration du champ DPID à la valeur DATA0.
 */

#define K_USB_FLAG_PID_DATA1 0x20000000

/**
 * @def K_USB_FLAG_NAK
 * @brief Constante dédiée aux fonctions usb_setINEndpointFlag() et usb_setOUTEndpointFlag(). \n
 *        Définition du drapeau NAK autorisant la terminaison à transférer un
 *        NAK.
 */

#define K_USB_FLAG_NAK 0x08000000

/**
 * @def K_USB_FLAG_STALL
 * @brief Constante dédiée aux fonctions usb_setINEndpointFlag() et usb_setOUTEndpointFlag(). \n
 *        Définition du drapeau STALL autorisant la terminaison à transférer un
 *        STALL. Un STALL est toujours prioritaire sur un NAK (global ou non).
 *        Pour les terminaisons de type 'CONTROL' et lors de la réception
 *        d'un paquet SETUP, le coeur répond toujours avec un ACK peut importe
 *        l'état de ce drapeau.\n
 *        La fonction usb_clearINEndpointFlag() peut être utilisée pour
 *        réinitialiser ce drapeau uniquement si la terminaison n'est pas de
 *        type 'CONTROL'.
 */

#define K_USB_FLAG_STALL 0x00200000

/**
 *
 */

/**
 * @def K_USB_FLAG_CLEAR_NAK
 * @brief Constante dédiée aux fonctions usb_clearINEndpointFlag() et usb_clearOUTEndpointFlag(). \n
 *        Définition du drapeau permettant de réinitialiser le drapeau NAK.
 *        NAK.
 */

#define K_USB_FLAG_CLEAR_NAK 0x04000000

/**
 * @def K_USB_FLAG_CLEAR_STALL
 * @brief Constante dédiée aux fonctions usb_clearINEndpointFlag() et usb_clearOUTEndpointFlag(). \n
 *        Définition du drapeau permettant de réinitialiser le drapeau STALL.
 *        Le drapeau peut être remise à zéro par l'application uniquement si la terminaison
 *        n'est pas de type 'CONTROL'.
 */

#define K_USB_FLAG_CLEAR_STALL 0x00200000

/**
 *
 */

/**
 * @def K_USB_STATUS_NAK
 * @brief Constante dédiée aux fonctions usb_getINEndpointStatus() et usb_getOUTEndpointStatus(). \n
 *        Définition de l'identifiant NAK indiquant que le coeur est en train de transférer
 *        un statut NAK dans le FIFO. Lorsqu'un NAK est en train d'être transmis : \n
 *        \li Pour une terminaison de type IN non isochrone, le coeur USB stoppe la transimission de
 *            données,
 *        \li Pour une terminaison de type IN isochrone, le coeur transmet un paquet de type
 *            'Zero Length Packet',
 *        \li Pour une terminaison de type OUT, le coeur stoppe la transmission de données,
 *        \li Lors de la réception d'un paquet 'SETUP', le coeur USB répond toujours avec un statut ACK.
 */

#define K_USB_STATUS_NAK 0x00000011

/**
 * @def K_USB_STATUS_EVEN_ODD_FRAME
 * @brief Constante dédiée aux fonctions usb_getINEndpointStatus() et usb_getOUTEndpointStatus(). \n
 *        Définition de l'identifiant 'EVEN_ODD' indiquant les numéros de trames où une terminaison
 *        isochrone doit transférer ou recevoir des données.
 */

#define K_USB_STATUS_EVEN_ODD_FRAME 0x00000010

/**
 * @def K_USB_STATUS_DATA_PID
 * @brief Constante dédiée aux fonctions usb_getINEndpointStatus() et usb_getOUTEndpointStatus(). \n
 *        Définition de l'identifiant 'DATA_PID' indiquant le PID du premier paquet transmis ou reçu par une
 *        terminaison de type 'BULK' ou 'INTERRUPT'.
 */

#define K_USB_STATUS_DATA_PID 0x00000010

/**
 * @def K_USB_STATUS_ACTIVE
 * @brief Constante dédiée aux fonctions usb_getINEndpointStatus() et usb_getOUTEndpointStatus(). \n
 *        Définition de l'identifiant 'ACTIVE' indiquant le statut de la terminaison (active ou non).
 */

#define K_USB_STATUS_ACTIVE 0x0000000F

/**
 *
 */

#endif

