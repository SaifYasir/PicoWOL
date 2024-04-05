#pragma once

#include "hardware/gpio.h"

/**
 * \file configuration.h
 * \brief Defines hard set variables used for Physical button communication
*/

/**
 * \def LEFT_BTN_GPIO
 * GPIO pin for button to move left for the current profile selected on the display menu
 */
#define LEFT_BTN_GPIO       14
/**
 * \def RIGHT_BTN_GPIO
 * GPIO pin for button to move right for the current profile selected on the display menu
 */
#define RIGHT_BTN_GPIO      15
/**
 * \def ACCEPT_BTN_GPIO
 * GPIO pin for button to wake the currently selected device on the display menu
 */
#define ACCEPT_BTN_GPIO     18
/**
 * \def INFO_BTN_GPIO
 * GPIO pin for button to display information relating to wifi on the display screen
 */
#define INFO_BTN_GPIO       19 

/**
 * \def BTN_BEHAVIOUR_IRQ
 * GPIO pin for button to define behaviour of button (in this case power is passed through the buttons)
 */
#define BTN_BEHAVIOUR_IRQ   GPIO_IRQ_EDGE_RISE