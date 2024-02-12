#pragma once

#include <stdint.h>

#include "configuration.h"

// 1 denotes shifting display to left, 2 denotes shifting bit to the right
extern uint8_t BUTTON_FLAG;

void initialise_left_btn();
void initialise_right_btn();
void initialise_accept_btn();


void disable_all_buttons();

/**
 * Needs to be disabled first, otherwise initialise each button
*/
void reenable_all_buttons();
