/*
 * File: gpio.c
 * Author: dgrubb
 * Date: 30/11/2017
 *
 * Handle digital I/O.
 */

#include "gpio.h"
#include "stm32f0xx_hal_rcc.h"

void gpio_init()
{
     GPIO_InitTypeDef GPIO_InitStructure;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStructure.Pin = GPIO_PIN_All;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStructure.Pin = GPIO_PIN_1;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void gpio_get_pin(gpio_port_t port, uint16_t pin, GPIO_PinState *value)
{
    GPIO_TypeDef *periph_port = gpio_get_periph_address(port);
    *value = HAL_GPIO_ReadPin(periph_port, pin);
}

void gpio_set_pin(gpio_port_t port, uint16_t pin, GPIO_PinState value)
{
    GPIO_TypeDef *periph_port = gpio_get_periph_address(port);
    HAL_GPIO_WritePin(periph_port, pin, value);
}

GPIO_TypeDef* gpio_get_periph_address(gpio_port_t port)
{
    switch (port) {
        case GPIO_PORT_A: return GPIOA;
        case GPIO_PORT_B: return GPIOB;
        default:          return GPIOA;
    }
}

