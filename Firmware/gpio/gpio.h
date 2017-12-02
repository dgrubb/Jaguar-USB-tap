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

typedef enum {
    GPIO_PORT_A = 0,
    GPIO_PORT_B
} gpio_port_t;

void gpio_init();
void gpio_get_pin(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState *value);
void gpio_set_pin(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState value);
GPIO_TypeDef* gpio_get_periph_address(gpio_port_t port);

#endif /* _GPIO_H */

