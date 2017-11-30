/*
 * File: gpio.h
 * Author: dgrubb
 * Date: 30/11/2017
 *
 * Handle digital I/O.
 */

#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>

typedef enum {
    GPIO_CLOCK_PIN_IN,
    GPIO_CLOCK_PIN_OUT
} gpio_clock_pin_t;

void gpio_init();
void gpio_set_pin(gpio_clock_pin_t pin, uint8_t value);

#endif /* _GPIO_H */

