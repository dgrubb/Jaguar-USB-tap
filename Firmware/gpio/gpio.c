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
}

void gpio_get_pin(uint16_t pin, GPIO_PinState *value)
{
    *value = HAL_GPIO_ReadPin(GPIOA, pin);
}

void gpio_set_pin(uint16_t pin, GPIO_PinState value)
{
    HAL_GPIO_WritePin(GPIOB, pin, value);
}

