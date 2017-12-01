/*
 * File: jaguar-controller.c
 * Author: dgrubb
 * Date: 30/11/2017
 *
 * Interpret digital I/O in context of Jaguar controller.
 */

#include "jaguar-controller.h"
#include "gpio/gpio.h"

static uint32_t jaguar_port = GPIOA;

static jaguar_button_info_t jaguar_button_mapping[] = {
    /* North: */
    { JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN14, JAGUAR_BUTTON_STATE_UP },
    /* South: */
    { JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN13, JAGUAR_BUTTON_STATE_UP },
    /* East: */
    { JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP },
    /* West: */
    { JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN12, JAGUAR_BUTTON_STATE_UP },
    /* A: */
    { JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN10, JAGUAR_BUTTON_STATE_UP },
    /* B: */
    { JAGUAR_DB15_PIN3, JAGUAR_DB15_PIN10, JAGUAR_BUTTON_STATE_UP },
    /* C: */
    { JAGUAR_DB15_PIN2, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP },
    /* Option: */
    { JAGUAR_DB15_PIN1, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP },
    /* Pause: */
    { JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP },
    /* Zero: */
    { JAGUAR_DB15_PIN2, JAGUAR_DB15_PIN14, JAGUAR_BUTTON_STATE_UP },
    /* One: */
    { JAGUAR_DB15_PIN3, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP },
    /* Two: */
    { JAGUAR_DB15_PIN2, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP },
    /* Three: */
    { JAGUAR_DB15_PIN1, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP },
    /* Four: */
    { JAGUAR_DB15_PIN3, JAGUAR_DB15_PIN12, JAGUAR_BUTTON_STATE_UP },
    /* Five: */
    { JAGUAR_DB15_PIN2, JAGUAR_DB15_PIN12, JAGUAR_BUTTON_STATE_UP },
    /* Six: */
    { JAGUAR_DB15_PIN1, JAGUAR_DB15_PIN12, JAGUAR_BUTTON_STATE_UP },
    /* Seven: */
    { JAGUAR_DB15_PIN3, JAGUAR_DB15_PIN13, JAGUAR_BUTTON_STATE_UP },
    /* Eight: */
    { JAGUAR_DB15_PIN2, JAGUAR_DB15_PIN13, JAGUAR_BUTTON_STATE_UP },
    /* Nine: */
    { JAGUAR_DB15_PIN1, JAGUAR_DB15_PIN13, JAGUAR_BUTTON_STATE_UP },
    /* Star: */
    { JAGUAR_DB15_PIN3, JAGUAR_DB15_PIN14, JAGUAR_BUTTON_STATE_UP },
    /* Pound: */
    { JAGUAR_DB15_PIN1, JAGUAR_DB15_PIN14, JAGUAR_BUTTON_STATE_UP }
};

void jaguar_update_inputs()
{
    uint32_t i;
    GPIO_PinState address, row = GPIO_PIN_RESET;
    jaguar_button_state_t button_state;

    for (i=0; i<JAGUAR_BUTTON_LENGTH; i++) {
        gpio_get_pin(jaguar_port, jaguar_button_mapping[i].address_pin, &address);
        gpio_get_pin(jaguar_port, jaguar_button_mapping[i].row_pin, &row);
        if ((address == GPIO_PIN_SET) && (row == GPIO_PIN_SET)) {
            button_state = JAGUAR_BUTTON_STATE_DOWN;
        } else {
            button_state = JAGUAR_BUTTON_STATE_UP;
        }
        if (button_state != jaguar_button_mapping[i].state) {
            jaguar_button_mapping[i].state = button_state;
            // TODO: send USB message here
        }
    }
}

const char* jaguar_get_button_str(jaguar_button_t button)
{
    switch (button) {
        case JAGUAR_BUTTON_NORTH:  return "North";
        case JAGUAR_BUTTON_SOUTH:  return "South";
        case JAGUAR_BUTTON_EAST:   return "East";
        case JAGUAR_BUTTON_WEST:   return "West";
        case JAGUAR_BUTTON_A:      return "A";
        case JAGUAR_BUTTON_B:      return "B";
        case JAGUAR_BUTTON_C:      return "C";
        case JAGUAR_BUTTON_OPTION: return "Option";
        case JAGUAR_BUTTON_PAUSE:  return "Pause";
        case JAGUAR_BUTTON_ZERO:   return "Zero";
        case JAGUAR_BUTTON_ONE:    return "One";
        case JAGUAR_BUTTON_TWO:    return "Two";
        case JAGUAR_BUTTON_THREE:  return "Three";
        case JAGUAR_BUTTON_FOUR:   return "Four";
        case JAGUAR_BUTTON_FIVE:   return "Five";
        case JAGUAR_BUTTON_SIX:    return "Six";
        case JAGUAR_BUTTON_SEVEN:  return "Seven";
        case JAGUAR_BUTTON_EIGHT:  return "Eight";
        case JAGUAR_BUTTON_NINE:   return "Nine";
        case JAGUAR_BUTTON_STAR:   return "Star";
        case JAGUAR_BUTTON_POUND:  return "Pound";
        default:                   return "Unknown";
    }
}
