#pragma once


// Commands
#define LCD_CLEAR_DISPLAY           0x01
#define LCD_RETURN_HOME             0x02
#define LCD_ENTRY_MODE_SET          0x04
#define LCD_DISPLAY_CONTROL         0x08
#define LCD_CURSOR_SHIFT            0x10
#define LCD_FUNCTION_SET            0x20
#define LCD_SET_CGRAM_ADDR          0x40
#define LCD_SET_DDRAM_ADDR          0x80

// Flags for display entry mode
#define LCD_ENTRY_SHIFT_INCREMENT   0x01
#define LCD_ENTRY_DIRECTION_LEFT    0x02

// Flags for display and cursor control
#define LCD_BLINK_ON                0x01
#define LCD_CURSOR_ON               0x02
#define LCD_DISPLAY_ON              0x04

// Flags for display and cursor shift
#define LCD_MOVE_RIGHT              0x04
#define LCD_DISPLAY_MOVE            0x08

// Flags for function set
#define LCD_5x10_DOTS               0x04
#define LCD_2_ROWS                  0x08
#define LCD_8_BIT_MODE              0x10

// Flags for backlight control
#define LCD_ENABLE_BIT              0x04
#define LCD_BACKLIGHT               0x08

// Default address of LCD for I2C
#define LCD_ADDR                    0x27

// Hardware Limitations
#define LCD_MAX_LINES                2
#define LCD_MAX_CHARS                16

