/*
 * File: jaguar-controller.c
 * Author: dgrubb
 * Date: 30/11/2017
 *
 * Interpret digital I/O in context of Jaguar controller.
 */

#include <string.h>
#include "usb_device.h"
#include "jaguar-controller.h"

static GPIO_TypeDef *jaguar_port = GPIOB;

uint8_t jaguar_usb_data[JAGUAR_USB_REPORT_LENGTH];

static jaguar_button_info_t jaguar_button_mapping[] = {
    /* Column 1 */
    { JAGUAR_BUTTON_OPTION, JAGUAR_DB15_PIN1, JAGUAR_DB15_PIN10, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_OPTION },
    { JAGUAR_BUTTON_THREE,  JAGUAR_DB15_PIN1, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_THREE },
    { JAGUAR_BUTTON_SIX,    JAGUAR_DB15_PIN1, JAGUAR_DB15_PIN12, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_SIX },
    { JAGUAR_BUTTON_NINE,   JAGUAR_DB15_PIN1, JAGUAR_DB15_PIN13, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_NINE },
    { JAGUAR_BUTTON_POUND,  JAGUAR_DB15_PIN1, JAGUAR_DB15_PIN14, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_POUND },
    /* Column 2 */
    { JAGUAR_BUTTON_C,      JAGUAR_DB15_PIN2, JAGUAR_DB15_PIN10, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_C },
    { JAGUAR_BUTTON_TWO,    JAGUAR_DB15_PIN2, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_TWO },
    { JAGUAR_BUTTON_FIVE,   JAGUAR_DB15_PIN2, JAGUAR_DB15_PIN12, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_FIVE },
    { JAGUAR_BUTTON_EIGHT,  JAGUAR_DB15_PIN2, JAGUAR_DB15_PIN13, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_EIGHT },
    { JAGUAR_BUTTON_ZERO,   JAGUAR_DB15_PIN2, JAGUAR_DB15_PIN14, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_ZERO },
    /* Column 3 */
    { JAGUAR_BUTTON_B,      JAGUAR_DB15_PIN3, JAGUAR_DB15_PIN10, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_B },
    { JAGUAR_BUTTON_ONE,    JAGUAR_DB15_PIN3, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_ONE },
    { JAGUAR_BUTTON_FOUR,   JAGUAR_DB15_PIN3, JAGUAR_DB15_PIN12, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_FOUR },
    { JAGUAR_BUTTON_SEVEN,  JAGUAR_DB15_PIN3, JAGUAR_DB15_PIN13, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_SEVEN },
    { JAGUAR_BUTTON_STAR,   JAGUAR_DB15_PIN3, JAGUAR_DB15_PIN14, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_STAR },
    /* Column 4 */
    { JAGUAR_BUTTON_PAUSE,  JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN6,  JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_PAUSE },
    { JAGUAR_BUTTON_A,      JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN10, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_A },
    { JAGUAR_BUTTON_EAST,   JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN11, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_NONE },
    { JAGUAR_BUTTON_WEST,   JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN12, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_NONE },
    { JAGUAR_BUTTON_SOUTH,  JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN13, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_NONE },
    { JAGUAR_BUTTON_NORTH,  JAGUAR_DB15_PIN4, JAGUAR_DB15_PIN14, JAGUAR_BUTTON_STATE_UP, JAGUAR_USB_BUTTON_NONE }
};

void jaguar_update_inputs(UART_HandleTypeDef *uart)
{
    char debug_msg[JAGUAR_DEBUG_MSG_LENGTH];
    jaguar_db15_pin_t address_pin = JAGUAR_DB15_PIN_UNKNOWN;
    uint32_t i=0;
    jaguar_button_state_t button_state;

    for (i=0; i<JAGUAR_BUTTON_LENGTH; i++) {
        if (address_pin != jaguar_button_mapping[i].address_pin) {
            /* Only switch the address pins if a new address is required. Buttons
             * are ordered in the button mapping table so that addresses are
             * grouped together and should only need switching four times for a 
             * complete sweep of all the buttons.
             * */
            jaguar_select_address(jaguar_button_mapping[i].address_pin);
           // HAL_Delay(10);
        }
        /* N.B: data pins are active low (RESET) when pressed.
         */
        if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(jaguar_port, jaguar_button_mapping[i].row_pin)) {
            button_state = JAGUAR_BUTTON_STATE_DOWN;
        } else {
            button_state = JAGUAR_BUTTON_STATE_UP;
        }
        /* Update the new button state and send messages on UART (for debug)
         * and USB (for fun).
         */
        if (button_state != jaguar_button_mapping[i].state) {
            jaguar_button_mapping[i].state = button_state;
            memset(debug_msg, 0, JAGUAR_DEBUG_MSG_LENGTH);
            sprintf(
                debug_msg,
                "Button: %s - %s\n\r",
                jaguar_get_button_str(jaguar_button_mapping[i].button),
                jaguar_get_button_state_str(jaguar_button_mapping[i].state)
            );
            jaguar_send_USB_report();
            HAL_UART_Transmit(uart, (uint8_t *)debug_msg, JAGUAR_DEBUG_MSG_LENGTH, HAL_MAX_DELAY);
        }
    }
}

void jaguar_select_address(jaguar_db15_pin_t address_pin)
{
    /* Reset all address pins */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
    /* Now enable our desired address line */
    HAL_GPIO_WritePin(GPIOB, address_pin, GPIO_PIN_RESET);
}

void jaguar_send_USB_report()
{
    jaguar_usb_report_t report;
    uint8_t i = 0;
    memset(&report, 0, sizeof(jaguar_usb_report_t));
    memset(&jaguar_usb_data, 0, JAGUAR_USB_REPORT_LENGTH);

    /* Scan the keymap to build a complete report of current button state */
    while (jaguar_button_mapping[i].button != JAGUAR_BUTTON_EAST) {
        if (jaguar_button_mapping[i].state == JAGUAR_BUTTON_STATE_DOWN) {
            report.buttons |= jaguar_button_mapping[i].usb_mask;
        } else {
            report.buttons &= ~jaguar_button_mapping[i].usb_mask;
        }
        /* Check the next button in sequence*/
        i++;
    }

    /* Handle D-pad as a special case */
    if (jaguar_button_mapping[JAGUAR_BUTTON_NORTH].state == JAGUAR_BUTTON_STATE_DOWN) report.y = 127;
    if (jaguar_button_mapping[JAGUAR_BUTTON_SOUTH].state == JAGUAR_BUTTON_STATE_DOWN) report.y = -127;
    if (jaguar_button_mapping[JAGUAR_BUTTON_EAST].state == JAGUAR_BUTTON_STATE_DOWN) report.x = 127;
    if (jaguar_button_mapping[JAGUAR_BUTTON_WEST].state == JAGUAR_BUTTON_STATE_DOWN) report.x = -127;

    /* Package report data into a flat array */
    jaguar_usb_data[0] = (uint8_t)report.buttons;
    jaguar_usb_data[1] = (uint8_t)(report.buttons >> 8);
    jaguar_usb_data[2] = (uint8_t)(report.buttons >> 16);
    jaguar_usb_data[3] = report.x;
    jaguar_usb_data[4] = report.y;

    MX_USB_DEVICE_Send(&jaguar_usb_data, JAGUAR_USB_REPORT_LENGTH);
}

const char* jaguar_get_button_state_str(jaguar_button_state_t state)
{
    switch (state) {
        case JAGUAR_BUTTON_STATE_UP:   return "Up";
        case JAGUAR_BUTTON_STATE_DOWN: return "Down";
        default:                       return "Unknown";
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
