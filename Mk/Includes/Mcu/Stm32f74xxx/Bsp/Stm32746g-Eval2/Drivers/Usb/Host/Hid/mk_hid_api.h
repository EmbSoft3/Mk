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
* @file mk_hid_api.h
* @brief Ce fichier contient les directives 'include' utilisées.
* @date 23 mars 2024
*
*/

#ifndef MK_HID_API_H
#define MK_HID_API_H

/**
 *
 */

#include "mk_types.h"
#include "mk_binary.h"
#include "mk_peripheral_usb_constants.h"

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
#include "mk_event_constants.h"
#include "mk_event_types.h"
#include "mk_event.h"
#include "mk_mutex_types.h"
#include "mk_semaphore_types.h"
#include "mk_mail_constants.h"
#include "mk_mail_types.h"
#include "mk_mail.h"
#include "mk_callback_constants.h"
#include "mk_callback_types.h"
#include "mk_memory_constants.h"
#include "mk_kernel.h"

/**
 *
 */

#include "mk_volume_constants.h"
#include "mk_volume_types.h"
#include "mk_file_constants.h"

/**
 *
 */

#include "mk_dispatcher_constants.h"
#include "mk_dispatcher_pool_types.h"
#include "mk_dispatcher_types.h"

/**
 *
 */

#include "mk_loader_elf_types.h"
#include "mk_loader_constants.h"
#include "mk_loader_types.h"

/**
 *
 */

#include "mk_display_events_types.h"
#include "mk_display_vect2d_types.h"
#include "mk_display_field_constants.h"
#include "mk_display_field_types.h"
#include "mk_display_field_private.h"
#include "mk_display_field.h"
#include "mk_display_container_types.h"
#include "mk_display_container_private.h"
#include "mk_display_factory_types.h"
#include "mk_display_font_constants.h"
#include "mk_display_font_types.h"
#include "mk_display_color_types.h"
#include "mk_display_application_constants.h"
#include "mk_display_application_types.h"
#include "mk_display_graphics_constants.h"
#include "mk_display_graphics_types.h"
#include "mk_display_graphics.h"
#include "mk_display_request_constants.h"
#include "mk_display_constants.h"
#include "mk_display_tasks_constants.h"
#include "mk_display_types.h"
#include "mk_display_data.h"
#include "mk_display_cursor_types.h"
#include "mk_display_cursor.h"

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

#include "mk_usb_constants.h"
#include "mk_hcd_class_types.h"
#include "mk_hcd_constants.h"
#include "mk_hcd_hub_types.h"
#include "mk_hcd_device_types.h"
#include "mk_hcd_list_types.h"
#include "mk_hcd_list_private.h"
#include "mk_hcd_pipe_constants.h"
#include "mk_hcd_pipe_types.h"
#include "mk_hcd_request_types.h"
#include "mk_hcd_request_private.h"
#include "mk_hcd_types.h"
#include "mk_hcd_pipe_private.h"
#include "mk_hcd_device_private.h"
#include "mk_hcd_utils_private.h"

/**
 *
 */

#include "mk_hid_table_types.h"
#include "mk_hid_item_types.h"
#include "mk_hid_usage_constants.h"
#include "mk_hid_usage_types.h"
#include "mk_hid_report_types.h"
#include "mk_hid_constants.h"
#include "mk_hid_country_types.h"
#include "mk_hid_collection_types.h"
#include "mk_hid_device_types.h"
#include "mk_hid_list_types.h"
#include "mk_hid_request_types.h"
#include "mk_hid_pool_constants.h"
#include "mk_hid_pool_types.h"
#include "mk_hid_types.h"
#include "mk_hid_device_private.h"
#include "mk_hid_dispatcher_private.h"
#include "mk_hid_error_private.h"
#include "mk_hid_list_private.h"
#include "mk_hid_page_types.h"
#include "mk_hid_parser_private.h"
#include "mk_hid_data.h"
#include "mk_hid_private.h"
#include "mk_hid_report_private.h"
#include "mk_hid_request_private.h"
#include "mk_hid_router_private.h"
#include "mk_hid_table_private.h"
#include "mk_hid_usage_private.h"
#include "mk_hid_button_constants.h"
#include "mk_hid_button_types.h"
#include "mk_hid_button_data.h"
#include "mk_hid_button_private.h"
#include "mk_hid_consumer_constants.h"
#include "mk_hid_consumer_types.h"
#include "mk_hid_consumer_data.h"
#include "mk_hid_consumer_private.h"
#include "mk_hid_wheel_types.h"
#include "mk_hid_axis_types.h"
#include "mk_hid_hatswitch_types.h"
#include "mk_hid_throttle_types.h"
#include "mk_hid_stick_types.h"
#include "mk_hid_led_constants.h"
#include "mk_hid_led_types.h"
#include "mk_hid_led_data.h"
#include "mk_hid_led_private.h"
#include "mk_hid_led.h"
#include "mk_hid_joystick_constants.h"
#include "mk_hid_joystick_types.h"
#include "mk_hid_joystick_data.h"
#include "mk_hid_joystick_private.h"
#include "mk_hid_joystick.h"
#include "mk_hid_key_constants.h"
#include "mk_hid_key_types.h"
#include "mk_hid_key_data.h"
#include "mk_hid_key_private.h"
#include "mk_hid_keyboard_constants.h"
#include "mk_hid_keyboard_types.h"
#include "mk_hid_keyboard_data.h"
#include "mk_hid_keyboard_private.h"
#include "mk_hid_keyboard.h"
#include "mk_hid_mouse_constants.h"
#include "mk_hid_mouse_types.h"
#include "mk_hid_mouse_data.h"
#include "mk_hid_mouse_private.h"
#include "mk_hid_mouse.h"

/**
 *
 */

#endif


