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
#include "stm32f0xx_hal_gpio.h"

typedef enum {
    JAGUAR_BUTTON_STATE_UP = 0,
    JAGUAR_BUTTON_STATE_DOWN
} jaguar_button_state_t;

typedef enum {
    JAGUAR_DB15_PIN1  = GPIO_PIN_0,  /* Address 1 */
    JAGUAR_DB15_PIN2  = GPIO_PIN_1,  /* Address 2 */
    JAGUAR_DB15_PIN3  = GPIO_PIN_2,  /* Address 3 */
    JAGUAR_DB15_PIN4  = GPIO_PIN_3,  /* Address 4 */
    JAGUAR_DB15_PIN6  = GPIO_PIN_4,  /* Row 1 */
    JAGUAR_DB15_PIN10 = GPIO_PIN_5,  /* Row 2 */
    JAGUAR_DB15_PIN11 = GPIO_PIN_6,  /* Row 3 */
    JAGUAR_DB15_PIN12 = GPIO_PIN_7,  /* Row 4 */
    JAGUAR_DB15_PIN13 = GPIO_PIN_8, /* Row 5 */
    JAGUAR_DB15_PIN14 = GPIO_PIN_9  /* Row 6 */
} jaguar_db15_pin_t;

typedef enum {
    JAGUAR_BUTTON_NORTH = 0,
    JAGUAR_BUTTON_SOUTH,
    JAGUAR_BUTTON_EAST,
    JAGUAR_BUTTON_WEST,
    JAGUAR_BUTTON_A,
    JAGUAR_BUTTON_B,
    JAGUAR_BUTTON_C,
    JAGUAR_BUTTON_OPTION,
    JAGUAR_BUTTON_PAUSE,
    JAGUAR_BUTTON_ZERO,
    JAGUAR_BUTTON_ONE,
    JAGUAR_BUTTON_TWO,
    JAGUAR_BUTTON_THREE,
    JAGUAR_BUTTON_FOUR,
    JAGUAR_BUTTON_FIVE,
    JAGUAR_BUTTON_SIX,
    JAGUAR_BUTTON_SEVEN,
    JAGUAR_BUTTON_EIGHT,
    JAGUAR_BUTTON_NINE,
    JAGUAR_BUTTON_STAR,
    JAGUAR_BUTTON_POUND,
    JAGUAR_BUTTON_LENGTH
} jaguar_button_t;

typedef struct {
    uint16_t address_pin;
    uint16_t row_pin;
    jaguar_button_state_t state;
} jaguar_button_info_t;

void jaguar_update_inputs();
void jaguar_get_pending_transition();
const char* jaguar_get_button_str(jaguar_button_t button);

#endif /* _JAGUAR_CONTROLLER_H */

