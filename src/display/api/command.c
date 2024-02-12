#include <string.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "command.h"

void i2c_write_byte(uint8_t val);
void lcd_toggle_enable(uint8_t val);
void lcd_send_byte(uint8_t val, int mode);
void display_i2c_pico_init();
void display_i2c_lcd_init();
void lcd_clear();
void lcd_set_cursor(int line, int position);
void lcd_send_char(char val);
void lcd_send_string(const char* string);
void centre_send_message(char* line_one, char* line_two);
void display_wol_profile(machine* wol_profile);

void i2c_write_byte(uint8_t val){
    if(LCD_I2C_INSTANCE == 0){
        i2c_write_blocking(i2c0,LCD_ADDR,&val,1,false);
    } else {
        i2c_write_blocking(i2c1,LCD_ADDR,&val,1,false);
    }
}

/*
* Enable bit on standard bridge chip is 0x04, by ORing data with 0x04
* and sending, the bridge chip "pulls up" the enable pin, allowing data 
* to be read by the LCD. This is then inverted after to let the bridge chip to "pull down"
* and the LCD to stop reading
*/
void lcd_toggle_enable(uint8_t val){
    busy_wait_us(DELAY_US);
    i2c_write_byte(val | LCD_ENABLE_BIT);
    busy_wait_us(DELAY_US);
    i2c_write_byte(val | ~LCD_ENABLE_BIT);
}

//sends byte as 2 nibbles (to properly interact with LCD)
void lcd_send_byte(uint8_t val, int mode){
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void display_i2c_pico_init(){
    if(LCD_I2C_INSTANCE == 0){
        i2c_init(i2c0,100 * 1000);
    } else {
        i2c_init(i2c1, 100 * 1000);
    }
    gpio_set_function(LCD_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(LCD_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(LCD_I2C_SDA_PIN);
    gpio_pull_up(LCD_I2C_SCL_PIN);

    bi_decl(bi_2pins_with_func(LCD_I2C_SDA_PIN, LCD_I2C_SCL_PIN,
    GPIO_FUNC_I2C));
}

void display_i2c_lcd_init(){

    /* Function sets LCD display to 8 bit mode (so we know the state), 
    this is done multiple times to ensure the LCD reads data */
    lcd_send_byte(0x03,LCD_COMMAND);
    lcd_send_byte(0x03,LCD_COMMAND);
    lcd_send_byte(0x03,LCD_COMMAND);

    // Sets LCD to 4 bit mode (what is wanted)
    lcd_send_byte(0x02, LCD_COMMAND);

    // Sets Display to use 2 rows
    lcd_send_byte(LCD_FUNCTION_SET | LCD_2_ROWS, LCD_COMMAND);

    // Sets cursor direction to move left (on LCD display)
    lcd_send_byte(LCD_ENTRY_MODE_SET | LCD_ENTRY_DIRECTION_LEFT, LCD_COMMAND);

    // Turns display on
    lcd_send_byte(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON, LCD_COMMAND);

    lcd_clear();
}

void lcd_clear(){
    lcd_send_byte(LCD_CLEAR_DISPLAY,LCD_COMMAND);
}

/*
 *  0X80 is the beginning of the first line, use line number 0
 *  0XC0 is the begginning of the second line, use line number 1
*/
void lcd_set_cursor(int line, int position){
    int set_cursor_pos = (line == 0) ? 0x80 + position : 0xC0 + position;
    lcd_send_byte(set_cursor_pos,LCD_COMMAND);
}

void lcd_send_char(char val) {
    lcd_send_byte(val, LCD_CHARACTER);
}

void lcd_send_string(const char* string){
    while (*string){
        lcd_send_char(*string++);
    }
}


void centre_send_message(char* line_one, char* line_two){
    lcd_clear();
    lcd_set_cursor(0,(LCD_MAX_CHARS/2) - (strlen(line_one) / 2));
    lcd_send_string(line_one);

    lcd_set_cursor(1,(LCD_MAX_CHARS/2) - (strlen(line_two) / 2));
    lcd_send_string(line_two);
}

void display_wol_profile(machine* wol_profile){
    centre_send_message("hello","there");
    if(wol_profile == NULL){
        machine* wol_selected = get_machine_at_index(default_wol_profiles,default_selected_wol_profile);
        centre_send_message(wol_selected->machine_name,"");
    }
    else{
        centre_send_message(wol_profile->machine_name,"");
    }
}