#pragma once

#include <stdlib.h>

#include "wol/wol.h"

// Change configuration file for different pin configurations
#include "display/configuration.h"

// Change LCD configuration file if not using splc780 display
#include "display/bridge_PCF8574/configuration.h"

// Modes for lcd_send_byte
#define LCD_CHARACTER 1
#define LCD_COMMAND 0

// Ammount of time to wait for LCD enable toggle
#define DELAY_US 600

void display_i2c_pico_init();
void display_i2c_lcd_init();

void lcd_clear();
void lcd_set_cursor(int line, int position);
void lcd_send_string(const char* string);


void centre_send_message(char* line_one, char* line_two);

// Leave wol_profile as NULL to use default (default_wol_profiles with machine at index default_selected_wol_profile)
void display_wol_profile(machine* wol_profile);