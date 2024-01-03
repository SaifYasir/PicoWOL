#include "button.h"

#include "hardware/gpio.h"

void left_btn_callback(void){
    if(gpio_get_irq_event_mask(LEFT_BTN_GPIO) & BTN_BEHAVIOUR_IRQ){
        gpio_acknowledge_irq(LEFT_BTN_GPIO,BTN_BEHAVIOUR_IRQ);
        //Complete logic here
    }
}

void right_btn_callback(void){
    if(gpio_get_irq_event_mask(RIGHT_BTN_GPIO) & BTN_BEHAVIOUR_IRQ){
        gpio_acknowledge_irq(RIGHT_BTN_GPIO,BTN_BEHAVIOUR_IRQ);
        //Complete logic here
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