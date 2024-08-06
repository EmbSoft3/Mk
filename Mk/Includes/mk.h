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
* @file mk.h
* @brief Ce fichier contient les directives 'include' de l'API.
* @date 11 févr. 2024
*
*/

#ifndef MK_H
#define MK_H

/**
 *
 */

#include "mk_types.h"
#include "mk_peripheral_api.h"

/**
 *
 */

#include "mk_constants.h"
#include "mk_sync_types.h"
#include "mk_memory_constants.h"
#include "mk_pool_constants.h"
#include "mk_pool_types.h"
#include "mk_pool.h"
#include "mk_task_constants.h"
#include "mk_task_types.h"
#include "mk_task.h"
#include "mk_stack.h"
#include "mk_list_types.h"
#include "mk_event_constants.h"
#include "mk_event_types.h"
#include "mk_event.h"
#include "mk_semaphore_types.h"
#include "mk_semaphore.h"
#include "mk_mutex_types.h"
#include "mk_mutex.h"
#include "mk_mail_constants.h"
#include "mk_mail_types.h"
#include "mk_mail.h"
#include "mk_callback_constants.h"
#include "mk_callback_types.h"
#include "mk_callback.h"
#include "mk_kernel.h"

/**
 *
 */

#include "mk_volume_constants.h"
#include "mk_volume_types.h"
#include "mk_disk_types.h"
#include "mk_disk.h"
#include "mk_fat_types.h"
#include "mk_file_constants.h"
#include "mk_file_types.h"
#include "mk_file.h"

/**
 *
 */

#include "mk_page_types.h"
#include "mk_page.h"

/**
 *
 */

#include "mk_dispatcher_constants.h"
#include "mk_dispatcher_pool_types.h"
#include "mk_dispatcher_types.h"
#include "mk_dispatcher_data.h"

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
#include "mk_display_field.h"
#include "mk_display_container_types.h"
#include "mk_display_container.h"
#include "mk_display_factory_types.h"
#include "mk_display_factory.h"
#include "mk_display_font_constants.h"
#include "mk_display_font_types.h"
#include "mk_display_font_data.h"
#include "mk_display_font.h"
#include "mk_display_color_constants.h"
#include "mk_display_color_types.h"
#include "mk_display_color.h"
#include "mk_display_application_constants.h"
#include "mk_display_application_types.h"
#include "mk_display_application.h"
#include "mk_display_chromart_types.h"
#include "mk_display_chromart.h"
#include "mk_display_graphics_constants.h"
#include "mk_display_graphics_types.h"
#include "mk_display_graphics.h"
#include "mk_display_bmp_types.h"
#include "mk_display_bmp.h"
#include "mk_display_plane2d_types.h"
#include "mk_display_vect2d_types.h"
#include "mk_display_vect2d.h"
#include "mk_display.h"

#include "mk_display_cursor_types.h"
#include "mk_display_cursor.h"
#include "mk_display_screen_types.h"
#include "mk_display_screen.h"
#include "mk_display_layer_constants.h"
#include "mk_display_layer_types.h"
#include "mk_display_layer.h"
#include "mk_display_buttonImage_types.h"
#include "mk_display_buttonImage.h"
#include "mk_display_textField_types.h"
#include "mk_display_textField.h"
#include "mk_display_editField_types.h"
#include "mk_display_editField.h"
#include "mk_display_figure_types.h"
#include "mk_display_figure.h"
#include "mk_display_graph2D_types.h"
#include "mk_display_graph2D.h"
#include "mk_display_progressBar_types.h"
#include "mk_display_progressBar.h"
#include "mk_display_console_constants.h"
#include "mk_display_console_types.h"
#include "mk_display_console.h"

/**
 *
 */

#include "mk_dma_types.h"
#include "mk_i2c_constants.h"
#include "mk_i2c_device_constants.h"
#include "mk_i2c_device_types.h"
#include "mk_i2c_list_types.h"
#include "mk_i2c_pool_constants.h"
#include "mk_i2c_pool_types.h"
#include "mk_i2c_port_types.h"
#include "mk_i2c_types.h"
#include "mk_i2c.h"

#include "mk_gpio_constants.h"
#include "mk_gpio_pool_types.h"
#include "mk_gpio_types.h"
#include "mk_gpio.h"

#include "mk_mmc_cmd_types.h"
#include "mk_mmc_port_types.h"
#include "mk_mmc_device_constants.h"
#include "mk_mmc_device_types.h"
#include "mk_mmc.h"

/**
 *
 */

#include "mk_hcd_hub_types.h"
#include "mk_hcd_device_types.h"
#include "mk_hcd_pipe_types.h"
#include "mk_msc_device_types.h"
#include "mk_msc.h"

/**
 *
 */

#include "mk_hid_button_constants.h"
#include "mk_hid_button_types.h"
#include "mk_hid_wheel_types.h"
#include "mk_hid_axis_types.h"
#include "mk_hid_hatswitch_types.h"
#include "mk_hid_throttle_types.h"
#include "mk_hid_stick_constants.h"
#include "mk_hid_stick_types.h"
#include "mk_hid_pointer_constants.h"

#include "mk_hid_led_constants.h"
#include "mk_hid_led_types.h"
#include "mk_hid_led.h"

#include "mk_hid_joystick_constants.h"
#include "mk_hid_joystick_types.h"
#include "mk_hid_joystick.h"

#include "mk_hid_key_constants.h"
#include "mk_hid_key_types.h"
#include "mk_hid_keyboard_events_types.h"
#include "mk_hid_keyboard_constants.h"
#include "mk_hid_keyboard_types.h"
#include "mk_hid_keyboard.h"

#include "mk_hid_mouse_constants.h"
#include "mk_hid_mouse_types.h"
#include "mk_hid_mouse.h"

/**
 *
 */

#include "mk_utils_string.h"
#include "mk_utils_utf.h"
#include "mk_utils.h"

/**
 *
 */

#endif
