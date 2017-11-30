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
#include "stm32f0xx_hal_gpio.h"

void gpio_init();
void gpio_get_pin(uint16_t pin, GPIO_PinState *value);
void gpio_set_pin(uint16_t pin, GPIO_PinState value);

#endif /* _GPIO_H */

