/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_termio_api.h
* @brief Ce fichier contient les directives 'include' utilisées.
* @date 24 mars 2024
*
*/

#ifndef MK_TERMIO_API_H
#define MK_TERMIO_API_H

/**
 *
 */

#include "mk_types.h"
#include "mk_binary.h"
#include "mk_peripheral_nvic_constants.h"
#include "mk_peripheral_nvic.h"

/**
 *
 */

#include "mk_constants.h"
#include "mk_sync_types.h"
#include "mk_pool_constants.h"
#include "mk_pool_types.h"
#include "mk_task_constants.h"
#include "mk_task_types.h"
#include "mk_task.h"
#include "mk_pool.h"
#include "mk_list_types.h"
#include "mk_stack.h"
#include "mk_event_types.h"
#include "mk_event.h"
#include "mk_semaphore_types.h"
#include "mk_mail_constants.h"
#include "mk_mail_types.h"
#include "mk_callback_constants.h"
#include "mk_callback_types.h"
#include "mk_scheduler_constants.h"
#include "mk_scheduler_types.h"
#include "mk_scheduler_private.h"
#include "mk_memory_constants.h"

/**
 *
 */


#include "mk_dma_types.h"
#include "mk_volume_constants.h"
#include "mk_volume_types.h"
#include "mk_disk_types.h"
#include "mk_disk_request_constants.h"
#include "mk_fat_types.h"
#include "mk_file_constants.h"
#include "mk_file_types.h"
#include "mk_file_pool_constants.h"
#include "mk_file_pool_types.h"
#include "mk_file_data.h"
#include "mk_file_private.h"

/**
 *
 */

#include "mk_i2c_constants.h"
#include "mk_i2c_device_constants.h"
#include "mk_i2c_device_types.h"
#include "mk_i2c_list_types.h"
#include "mk_i2c_pool_constants.h"
#include "mk_i2c_pool_types.h"
#include "mk_i2c_types.h"
#include "mk_i2c_port_types.h"
#include "mk_i2c_data.h"
#include "mk_i2c_private.h"

/**
 *
 */

#include "mk_gpio_constants.h"
#include "mk_gpio_pool_types.h"
#include "mk_gpio_types.h"
#include "mk_gpio_data.h"
#include "mk_gpio_private.h"

/**
 *
 */

#include "mk_usb_constants.h"
#include "mk_usb_data.h"
#include "mk_usb_private.h"
#include "mk_hcd_constants.h"
#include "mk_hcd_hub_types.h"
#include "mk_hcd_device_types.h"
#include "mk_hcd_pipe_types.h"

/**
 *
 */

#include "mk_hid_table_types.h"
#include "mk_hid_item_types.h"
#include "mk_hid_report_types.h"
#include "mk_hid_constants.h"
#include "mk_hid_device_types.h"
#include "mk_hid_list_types.h"
#include "mk_hid_pool_constants.h"
#include "mk_hid_pool_types.h"
#include "mk_hid_types.h"
#include "mk_hid_data.h"
#include "mk_hid_private.h"

/**
 *
 */

#include "mk_msc_constants.h"
#include "mk_msc_device_types.h"
#include "mk_msc_list_types.h"
#include "mk_msc_pool_constants.h"
#include "mk_msc_pool_types.h"
#include "mk_msc_types.h"
#include "mk_msc_wrapper_constants.h"
#include "mk_msc_data.h"
#include "mk_msc_private.h"

/**
 *
 */

#include "mk_mmc_constants.h"
#include "mk_mmc_cmd_types.h"
#include "mk_mmc_port_types.h"
#include "mk_mmc_device_constants.h"
#include "mk_mmc_device_types.h"
#include "mk_mmc_pool_constants.h"
#include "mk_mmc_pool_types.h"
#include "mk_mmc_list_types.h"
#include "mk_mmc_types.h"
#include "mk_mmc_data.h"
#include "mk_mmc_private.h"

/**
 *
 */

#include "mk_dispatcher_constants.h"
#include "mk_dispatcher_pool_types.h"
#include "mk_dispatcher_types.h"
#include "mk_dispatcher_data.h"
#include "mk_dispatcher_private.h"

/**
 *
 */

#include "mk_termio_constants.h"
#include "mk_termio_types.h"
#include "mk_termio_data.h"
#include "mk_termio_private.h"
#include "mk_termio.h"

/**
 *
 */

#endif


