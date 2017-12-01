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
    JAGUAR_BUTTON_NORTH = 0,
    JAGUAR_BUTTON_SOUTH,
    JAGUAR_BUTTON_EAST,
    JAGUAR_BUTTON_WEST,
    JAGUAR_BUTTON_A,
    JAGUAR_BUTTON_B,
    JAGUAR_BUTTON_C,
    JAGUAR_BUTTON_OPTION,
    JAGUAR_BUTTON_START,
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
    JAGUAR_BUTTON_POUND
} jaguar_button_t;

typedef struct {
    uint16_t address_pin;
    uint16_t data_pin;
    GPIO_PinState state;
} jaguar_button_state_t;

void jaguar_update_inputs();
void jaguar_get_pending_transition();
const char* jaguar_get_button_str(jaguar_button_t button);

#endif /* _JAGUAR_CONTROLLER_H */

