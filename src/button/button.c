#include "button.h"

#include "hardware/gpio.h"

uint8_t BUTTON_FLAG;

void left_btn_callback(void){
    if(gpio_get_irq_event_mask(LEFT_BTN_GPIO) & BTN_BEHAVIOUR_IRQ){
        gpio_acknowledge_irq(LEFT_BTN_GPIO,BTN_BEHAVIOUR_IRQ);
        BUTTON_FLAG = 1;
    }
}

void right_btn_callback(void){
    if(gpio_get_irq_event_mask(RIGHT_BTN_GPIO) & BTN_BEHAVIOUR_IRQ){
        gpio_acknowledge_irq(RIGHT_BTN_GPIO,BTN_BEHAVIOUR_IRQ);
        BUTTON_FLAG = 2;
    }
}

void accept_btn_callback(void){
    if(gpio_get_irq_event_mask(ACCEPT_BTN_GPIO) & BTN_BEHAVIOUR_IRQ){
        gpio_acknowledge_irq(ACCEPT_BTN_GPIO,BTN_BEHAVIOUR_IRQ);
        BUTTON_FLAG = 3;
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