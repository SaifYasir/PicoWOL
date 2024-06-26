#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/binary_info.h"
#include "pico/util/queue.h"

#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/api.h"

#include "wol/wol.h"
#include "display/api/command.h"
#include "wifi/wifi.h"
#include "button/button.h"
#include "flash/flash.h"

/**
 * \brief The introduction message the display shows when starting the PICO
 * 
 */
char *INTRODUCTION_MSG[] = {"Pico","Wake On Lan"};

/**
 * \brief Main entry point to the program
 * 
 * Main starts and configures multiple components, such as the peripherals, wifi and running the server
*/
int main(){
    if(!stdio_init_all()){
        printf("Standard IO could not be initialised! \n");
    }
    if (cyw43_arch_init()) {
        printf("Wi-Fi initialisation failed! \n");
        return -1;
    }

    display_i2c_pico_init();
    display_i2c_lcd_init();

    // Tell user Pico is loading
    centre_send_message("Pico","Loading");

    //configure wol list
    initialise_sd_card();
    sd_card_read_and_initialise_wifi_credentials();

    if(start_wifi(default_wifi_credentials) != 0){
        printf("Connection to device failure, attempting again... \n");
        if(start_wifi(default_wifi_credentials) != 0){
            printf("Connection failed again, terminating! \n");
            return -1;
        }
    }

    //configure wol list
    sd_card_read_and_initialise_wol_profiles();

    initialise_all_buttons();
    disable_all_buttons();
    start_udp_server();

    // Show introduction message
    centre_send_message(INTRODUCTION_MSG[0],INTRODUCTION_MSG[1]);
    sleep_ms(1000);

    display_wol_profile(NULL);
    reenable_all_buttons();

    while(true){
        sleep_ms(1000);
        poll_udp_packets(&default_udp_polling_machine_stack);
    }

    clear_machine_stack(&default_wol_profiles);
}