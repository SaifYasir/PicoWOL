#include <string.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "button.h"

#include "wol/wol.h"
#include "wifi/wifi.h"
#include "display/api/command.h"

uint8_t BUTTON_FLAG;

void left_btn_callback(void){
    if(gpio_get_irq_event_mask(LEFT_BTN_GPIO) & BTN_BEHAVIOUR_IRQ){
        gpio_acknowledge_irq(LEFT_BTN_GPIO,BTN_BEHAVIOUR_IRQ);
        if(default_selected_wol_profile > 0){
            default_selected_wol_profile--;
            //display move left
            display_wol_profile(NULL);
        }
    }
}

void right_btn_callback(void){
    if(gpio_get_irq_event_mask(RIGHT_BTN_GPIO) & BTN_BEHAVIOUR_IRQ){
        gpio_acknowledge_irq(RIGHT_BTN_GPIO,BTN_BEHAVIOUR_IRQ);
        if(default_selected_wol_profile < get_machine_stack_size(default_wol_profiles) - 1){
            default_selected_wol_profile++;
            //display move right
            display_wol_profile(NULL);
        }
    }
}

void accept_btn_callback(void){
    if(gpio_get_irq_event_mask(ACCEPT_BTN_GPIO) & BTN_BEHAVIOUR_IRQ){
        gpio_acknowledge_irq(ACCEPT_BTN_GPIO,BTN_BEHAVIOUR_IRQ);
        machine* wol_selected = get_machine_at_index(default_wol_profiles,default_selected_wol_profile);

        // push to wol udp stack
        push_to_machine_stack(&default_udp_polling_machine_stack,wol_selected);

        //display sent message?
        char* sent_message = "WOL SENT!";
        lcd_set_cursor(1,(LCD_MAX_CHARS/2) - (strlen(sent_message) / 2));
        lcd_send_string(sent_message);
    }
}

void initialise_left_btn(){
    gpio_set_irq_enabled(LEFT_BTN_GPIO,BTN_BEHAVIOUR_IRQ,true);
    gpio_add_raw_irq_handler(LEFT_BTN_GPIO,left_btn_callback);
}

void initialise_right_btn(){
    gpio_set_irq_enabled(RIGHT_BTN_GPIO,BTN_BEHAVIOUR_IRQ,true);
    gpio_add_raw_irq_handler(RIGHT_BTN_GPIO,right_btn_callback);
}


void initialise_accept_btn(){
    gpio_set_irq_enabled(ACCEPT_BTN_GPIO,BTN_BEHAVIOUR_IRQ,true);
    gpio_add_raw_irq_handler(ACCEPT_BTN_GPIO,accept_btn_callback);
}

void disable_all_buttons(){
    gpio_set_irq_enabled(LEFT_BTN_GPIO,BTN_BEHAVIOUR_IRQ,false);
    gpio_set_irq_enabled(RIGHT_BTN_GPIO,BTN_BEHAVIOUR_IRQ,false);
    gpio_set_irq_enabled(ACCEPT_BTN_GPIO,BTN_BEHAVIOUR_IRQ,false);
}

void reenable_all_buttons(){
    gpio_set_irq_enabled(LEFT_BTN_GPIO,BTN_BEHAVIOUR_IRQ,true);
    gpio_set_irq_enabled(RIGHT_BTN_GPIO,BTN_BEHAVIOUR_IRQ,true);
    gpio_set_irq_enabled(ACCEPT_BTN_GPIO,BTN_BEHAVIOUR_IRQ,true);
}