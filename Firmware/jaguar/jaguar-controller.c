/*
 * File: jaguar-controller.c
 * Author: dgrubb
 * Date: 30/11/2017
 *
 * Interpret digital I/O in context of Jaguar controller.
 */

#include "jaguar-controller.h"


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
        case JAGUAR_BUTTON_START:  return "Start";
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
