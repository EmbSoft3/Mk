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
* @file mk_api.h
* @brief Ce fichier contient les directives 'include' utilisées.
* @date 21 mars 2024
*
*/

#ifndef MK_API_H
#define MK_API_H

/**
 *
 */

#include "mk_types.h"
#include "mk_peripheral_api.h"

/**
 *
 */

#include "mk_id.h"
#include "mk_constants.h"
#include "mk_sync_types.h"
#include "mk_pool_constants.h"
#include "mk_pool_types.h"
#include "mk_task_constants.h"
#include "mk_task_types.h"
#include "mk_task_data.h"
#include "mk_task.h"
#include "mk_pool_private.h"
#include "mk_pool.h"
#include "mk_list_types.h"
#include "mk_list_private.h"
#include "mk_stack_constants.h"
#include "mk_stack.h"
#include "mk_svc_constants.h"
#include "mk_svc_types.h"
#include "mk_svc_data.h"
#include "mk_svc_private.h"
#include "mk_event_constants.h"
#include "mk_event_types.h"
#include "mk_event.h"
#include "mk_event_private.h"
#include "mk_mutex_types.h"
#include "mk_mutex_private.h"
#include "mk_mutex.h"
#include "mk_semaphore_types.h"
#include "mk_semaphore_private.h"
#include "mk_semaphore.h"
#include "mk_mail_constants.h"
#include "mk_mail_types.h"
#include "mk_mail_private.h"
#include "mk_mail.h"
#include "mk_handler_types.h"
#include "mk_handler_data.h"
#include "mk_handler_private.h"
#include "mk_callback_constants.h"
#include "mk_callback_types.h"
#include "mk_callback_data.h"
#include "mk_callback_private.h"
#include "mk_callback.h"
#include "mk_scheduler_constants.h"
#include "mk_scheduler_types.h"
#include "mk_scheduler_data.h"
#include "mk_scheduler_private.h"
#include "mk_memory_constants.h"
#include "mk_memory_private.h"
#include "mk_memory_task_types.h"
#include "mk_memory_task_data.h"
#include "mk_memory_task_private.h"
#include "mk_call_private.h"
#include "mk_kernel.h"

/**
 *
 */

#include "mk_dma_constants.h"
#include "mk_dma_types.h"
#include "mk_dma_data.h"
#include "mk_dma_isr_private.h"
#include "mk_dma_pipe_private.h"
#include "mk_dma_private.h"

/**
 *
 */

#include "mk_volume_constants.h"
#include "mk_volume_types.h"
#include "mk_disk_constants.h"
#include "mk_disk_types.h"
#include "mk_disk_pool_constants.h"
#include "mk_disk_pool_types.h"
#include "mk_disk_data.h"
#include "mk_disk_private.h"
#include "mk_disk_request_constants.h"
#include "mk_disk_request_types.h"
#include "mk_disk.h"
#include "mk_volume_pool_constants.h"
#include "mk_volume_pool_types.h"
#include "mk_volume_data.h"
#include "mk_volume_list_private.h"
#include "mk_volume_private.h"
#include "mk_fat_constants.h"
#include "mk_fat_types.h"
#include "mk_file_constants.h"
#include "mk_file_types.h"
#include "mk_file_pool_constants.h"
#include "mk_file_pool_types.h"
#include "mk_file_data.h"
#include "mk_file_private.h"
#include "mk_file.h"
#include "mk_fat_private.h"
#include "mk_fat_utils_private.h"

/**
 *
 */

#include "mk_page_constants.h"
#include "mk_page_types.h"
#include "mk_page_data.h"
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

#include "mk_loader_elf_constants.h"
#include "mk_loader_elf_types.h"
#include "mk_loader_srec_constants.h"
#include "mk_loader_srec_types.h"
#include "mk_loader_constants.h"
#include "mk_loader_types.h"
#include "mk_loader_data.h"
#include "mk_loader_srec.h"
#include "mk_loader_elf.h"
#include "mk_loader_private.h"

/**
 *
 */

#include "mk_display_events_constants.h"
#include "mk_display_events_types.h"
#include "mk_display_vect2d_types.h"
#include "mk_display_field_constants.h"
#include "mk_display_field_types.h"
#include "mk_display_field_private.h"
#include "mk_display_field.h"
#include "mk_display_container_constants.h"
#include "mk_display_container_types.h"
#include "mk_display_container_data.h"
#include "mk_display_container_private.h"
#include "mk_display_container.h"
#include "mk_display_factory_types.h"
#include "mk_display_factory_private.h"
#include "mk_display_factory.h"
#include "mk_display_font_constants.h"
#include "mk_display_font_types.h"
#include "mk_display_font_data.h"
#include "mk_display_font_private.h"
#include "mk_display_font.h"
#include "mk_display_color_constants.h"
#include "mk_display_color_types.h"
#include "mk_display_color.h"
#include "mk_display_application_constants.h"
#include "mk_display_application_types.h"
#include "mk_display_application_data.h"
#include "mk_display_application_private.h"
#include "mk_display_application.h"
#include "mk_display_chromart_types.h"
#include "mk_display_chromart_private.h"
#include "mk_display_chromart.h"
#include "mk_display_graphics_constants.h"
#include "mk_display_graphics_types.h"
#include "mk_display_graphics_private.h"
#include "mk_display_graphics.h"
#include "mk_display_bmp_constants.h"
#include "mk_display_bmp_types.h"
#include "mk_display_bmp.h"
#include "mk_display_plane2d_types.h"
#include "mk_display_vect2d_types.h"
#include "mk_display_vect2d.h"
#include "mk_display_parser_types.h"
#include "mk_display_parser_private.h"
#include "mk_display_request_constants.h"
#include "mk_display_constants.h"
#include "mk_display_peripherals_constants.h"
#include "mk_display_tasks_constants.h"
#include "mk_display_types.h"
#include "mk_display_request_types.h"
#include "mk_display_request_private.h"
#include "mk_display_data.h"
#include "mk_display_utils_private.h"
#include "mk_display_private.h"
#include "mk_display.h"

#include "mk_display_cursor_constants.h"
#include "mk_display_cursor_types.h"
#include "mk_display_cursor_data.h"
#include "mk_display_cursor.h"
#include "mk_display_screen_types.h"
#include "mk_display_screen.h"
#include "mk_display_layer_constants.h"
#include "mk_display_layer_types.h"
#include "mk_display_layer.h"
#include "mk_display_buttonImage_constants.h"
#include "mk_display_buttonImage_types.h"
#include "mk_display_buttonImage.h"
#include "mk_display_textField_constants.h"
#include "mk_display_textField_types.h"
#include "mk_display_textField.h"
#include "mk_display_editField_constants.h"
#include "mk_display_editField_types.h"
#include "mk_display_editField_private.h"
#include "mk_display_editField.h"
#include "mk_display_figure_types.h"
#include "mk_display_figure.h"
#include "mk_display_graph2D_constants.h"
#include "mk_display_graph2D_types.h"
#include "mk_display_graph2D.h"
#include "mk_display_progressBar_constants.h"
#include "mk_display_progressBar_types.h"
#include "mk_display_progressBar.h"
#include "mk_display_console_constants.h"
#include "mk_display_console_types.h"
#include "mk_display_console_private.h"
#include "mk_display_console.h"

/**
 *
 */

#include "mk_i2c_constants.h"
#include "mk_i2c_right_constants.h"
#include "mk_i2c_gpio_constants.h"
#include "mk_i2c_device_constants.h"
#include "mk_i2c_device_types.h"
#include "mk_i2c_list_types.h"
#include "mk_i2c_list_private.h"
#include "mk_i2c_pool_constants.h"
#include "mk_i2c_pool_types.h"
#include "mk_i2c_port_constants.h"
#include "mk_i2c_types.h"
#include "mk_i2c_dma_private.h"
#include "mk_i2c_isr_private.h"
#include "mk_i2c_port_types.h"
#include "mk_i2c_port_private.h"
#include "mk_i2c_device_private.h"
#include "mk_i2c_data.h"
#include "mk_i2c_private.h"
#include "mk_i2c.h"

/**
 *
 */

#include "mk_gpio_constants.h"
#include "mk_gpio_pool_types.h"
#include "mk_gpio_types.h"
#include "mk_gpio_data.h"
#include "mk_gpio_isr_private.h"
#include "mk_gpio_private.h"
#include "mk_gpio_port_private.h"
#include "mk_gpio_expander_constants.h"
#include "mk_gpio_expander_types.h"
#include "mk_gpio_expander_data.h"
#include "mk_gpio_expander_private.h"
#include "mk_gpio.h"

/**
 *
 */

#include "mk_usb_constants.h"
#include "mk_usb_data.h"
#include "mk_usb_private.h"
#include "mk_usb_isr_private.h"
#include "mk_hcd_class_types.h"
#include "mk_hcd_constants.h"
#include "mk_hcd_hub_constants.h"
#include "mk_hcd_hub_types.h"
#include "mk_hcd_device_constants.h"
#include "mk_hcd_device_types.h"
#include "mk_hcd_langid_types.h"
#include "mk_hcd_list_constants.h"
#include "mk_hcd_list_types.h"
#include "mk_hcd_list_private.h"
#include "mk_hcd_pipe_constants.h"
#include "mk_hcd_pipe_types.h"
#include "mk_hcd_pool_constants.h"
#include "mk_hcd_pool_types.h"
#include "mk_hcd_request_types.h"
#include "mk_hcd_request_private.h"
#include "mk_hcd_types.h"
#include "mk_hcd_pipe_private.h"
#include "mk_hcd_hub_private.h"
#include "mk_hcd_device_private.h"
#include "mk_hcd_isr_private.h"
#include "mk_hcd_data.h"
#include "mk_hcd_utils_private.h"
#include "mk_hcd_private.h"

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
#include "mk_hid_consumer_events_types.h"
#include "mk_hid_consumer_private.h"
#include "mk_hid_wheel_types.h"
#include "mk_hid_axis_types.h"
#include "mk_hid_hatswitch_types.h"
#include "mk_hid_throttle_types.h"
#include "mk_hid_stick_constants.h"
#include "mk_hid_stick_types.h"
#include "mk_hid_pointer_constants.h"
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
#include "mk_hid_keyboard_events_types.h"
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

#include "mk_dispatcher_keyboard_private.h"
#include "mk_dispatcher_private.h"

/**
 *
 */

#include "mk_msc_constants.h"
#include "mk_msc_class_types.h"
#include "mk_msc_device_types.h"
#include "mk_msc_list_types.h"
#include "mk_msc_pool_constants.h"
#include "mk_msc_pool_types.h"
#include "mk_msc_types.h"
#include "mk_msc_request_types.h"
#include "mk_msc_wrapper_constants.h"
#include "mk_msc_wrapper_types.h"
#include "mk_msc_wrapper_private.h"
#include "mk_msc_scsi_types.h"
#include "mk_msc_scsi_private.h"
#include "mk_msc_device_private.h"
#include "mk_msc_utils_types.h"
#include "mk_msc_utils_private.h"
#include "mk_msc_data.h"
#include "mk_msc_request_private.h"
#include "mk_msc_list_private.h"
#include "mk_msc_disk_constants.h"
#include "mk_msc_disk_private.h"
#include "mk_msc_private.h"
#include "mk_msc.h"

/**
 *
 */

#include "mk_mmc_constants.h"
#include "mk_mmc_cmd_constants.h"
#include "mk_mmc_cmd_types.h"
#include "mk_mmc_port_types.h"
#include "mk_mmc_device_constants.h"
#include "mk_mmc_device_types.h"
#include "mk_mmc_pool_constants.h"
#include "mk_mmc_pool_types.h"
#include "mk_mmc_port_types.h"
#include "mk_mmc_port_private.h"
#include "mk_mmc_list_types.h"
#include "mk_mmc_list_private.h"
#include "mk_mmc_types.h"
#include "mk_mmc_data.h"
#include "mk_mmc_cmd_private.h"
#include "mk_mmc_dma_private.h"
#include "mk_mmc_isr_private.h"
#include "mk_mmc_disk_private.h"
#include "mk_mmc_device_private.h"
#include "mk_mmc_private.h"
#include "mk_mmc.h"

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

#include "mk_system_api.h"

/**
 *
 */

#include "mk_micron_n25q512a_constants.h"
#include "mk_micron_n25q512a_types.h"

/**
 *
 */

#include "mk_utils_constants.h"
#include "mk_utils_parser_ini_constants.h"
#include "mk_utils_parser_ini_types.h"
#include "mk_utils_parser_ini.h"
#include "mk_utils_string.h"
#include "mk_utils_utf.h"
#include "mk_utils.h"

/**
 *
 */

#include "mk_supervisor_fault_types.h"
#include "mk_supervisor_constants.h"
#include "mk_supervisor_types.h"
#include "mk_supervisor_data.h"
#include "mk_supervisor_private.h"
#include "mk_supervisor.h"
#include "mk_shell_constants.h"
#include "mk_shell_message_constants.h"
#include "mk_shell_types.h"
#include "mk_shell_data.h"
#include "mk_shell_private.h"

/**
 *
 */

#include "mk_home_constants.h"
#include "mk_home_main_constants.h"
#include "mk_home_main_types.h"
#include "mk_home_manager_constants.h"
#include "mk_home_manager_types.h"
#include "mk_home_types.h"
#include "mk_home_data.h"
#include "mk_home.h"

/**
 *
 */

#include "mk_main.h"

/**
 *
 */

#endif
