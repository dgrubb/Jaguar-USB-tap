/*
 * File: jaguar-controller.h
 * Author: dgrubb
 * Date: 30/11/2017
 *
 * Interpret digital I/O in context of Jaguar controller.
 */

#ifndef _JAGUAR_CONTROLLER_H
#define _JAGUAR_CONTROLLER_H

#include <stdint.h>
#include "stm32f0xx.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_uart.h"

#define JAGUAR_DEBUG_MSG_LENGTH 100
#define JAGUAR_USB_REPORT_LENGTH    5

#define JAGUAR_USB_BUTTON_OPTION 0x00000001
#define JAGUAR_USB_BUTTON_THREE  0x00000002
#define JAGUAR_USB_BUTTON_SIX    0x00000004
#define JAGUAR_USB_BUTTON_NINE   0x00000008
#define JAGUAR_USB_BUTTON_POUND  0x00000010
#define JAGUAR_USB_BUTTON_C      0x00000020
#define JAGUAR_USB_BUTTON_TWO    0x00000040
#define JAGUAR_USB_BUTTON_FIVE   0x00000080
#define JAGUAR_USB_BUTTON_EIGHT  0x00000100
#define JAGUAR_USB_BUTTON_ZERO   0x00000200
#define JAGUAR_USB_BUTTON_B      0x00000400
#define JAGUAR_USB_BUTTON_ONE    0x00000800
#define JAGUAR_USB_BUTTON_FOUR   0x00001000
#define JAGUAR_USB_BUTTON_SEVEN  0x00002000
#define JAGUAR_USB_BUTTON_STAR   0x00004000
#define JAGUAR_USB_BUTTON_PAUSE  0x00008000
#define JAGUAR_USB_BUTTON_A      0x00010000
#define JAGUAR_USB_BUTTON_NONE   0x00000000

typedef enum {
    JAGUAR_BUTTON_STATE_UP = 0,
    JAGUAR_BUTTON_STATE_DOWN
} jaguar_button_state_t;

typedef enum {
    JAGUAR_DB15_PIN_UNKNOWN = 0,
    JAGUAR_DB15_PIN1        = GPIO_PIN_0, /* Address 1 */
    JAGUAR_DB15_PIN2        = GPIO_PIN_1, /* Address 2 */
    JAGUAR_DB15_PIN3        = GPIO_PIN_2, /* Address 3 */
    JAGUAR_DB15_PIN4        = GPIO_PIN_3, /* Address 4 */
    JAGUAR_DB15_PIN6        = GPIO_PIN_4, /* Row 1 */
    JAGUAR_DB15_PIN10       = GPIO_PIN_5, /* Row 2 */
    JAGUAR_DB15_PIN11       = GPIO_PIN_6, /* Row 3 */
    JAGUAR_DB15_PIN12       = GPIO_PIN_7, /* Row 4 */
    JAGUAR_DB15_PIN13       = GPIO_PIN_8, /* Row 5 */
    JAGUAR_DB15_PIN14       = GPIO_PIN_9  /* Row 6 */
} jaguar_db15_pin_t;

typedef enum {
    JAGUAR_BUTTON_OPTION = 0,
    JAGUAR_BUTTON_THREE,
    JAGUAR_BUTTON_SIX,
    JAGUAR_BUTTON_NINE,
    JAGUAR_BUTTON_POUND,
    JAGUAR_BUTTON_C,
    JAGUAR_BUTTON_TWO,
    JAGUAR_BUTTON_FIVE,
    JAGUAR_BUTTON_EIGHT,
    JAGUAR_BUTTON_ZERO,
    JAGUAR_BUTTON_B,
    JAGUAR_BUTTON_ONE,
    JAGUAR_BUTTON_FOUR,
    JAGUAR_BUTTON_SEVEN,
    JAGUAR_BUTTON_STAR,
    JAGUAR_BUTTON_PAUSE,
    JAGUAR_BUTTON_A,
    JAGUAR_BUTTON_EAST,
    JAGUAR_BUTTON_WEST,
    JAGUAR_BUTTON_SOUTH,
    JAGUAR_BUTTON_NORTH,
    JAGUAR_BUTTON_LENGTH
} jaguar_button_t;

typedef struct {
    jaguar_button_t button;
    jaguar_db15_pin_t address_pin;
    jaguar_db15_pin_t row_pin;
    jaguar_button_state_t state;
    uint32_t usb_mask;
} jaguar_button_info_t;

typedef struct {
    int8_t x;
    int8_t y;
    uint32_t buttons;
} jaguar_usb_report_t;

void jaguar_update_inputs(UART_HandleTypeDef *uart);
void jaguar_get_pending_transition();
void jaguar_select_address(jaguar_db15_pin_t address_pin);
void jaguar_send_USB_report();
const char* jaguar_get_button_str(jaguar_button_t button);
const char* jaguar_get_button_state_str(jaguar_button_state_t state);

#endif /* _JAGUAR_CONTROLLER_H */

