#pragma once

#include "wol/wol.h"

#include "pico/util/queue.h"

#define MAX_QUEUE_WOL            5
#define QUEUE_SPINLOCK_ID        1

#define UDP_PORT_NUMBER          7

#define MAC_SERVER_DELIMITER    ','
#define INDEX_SERVER_DELIMITER  ';'
#define STRING_SERVER_DELIMITER '.'

/**
 * Add to this stack, then poll to wake up devices
*/
extern queue_t* default_udp_polling_machine_queue;

int start_wifi(wifi_credential* wifi_credential);
int start_udp_server();

void initialise_polling_queue(queue_t** queue);
void push_to_polling_queue(queue_t* queue, machine* machine);
void poll_udp_packets(queue_t* machine_queue);

int pico_get_port_number();
void pico_get_mac_address(uint8_t mac[6]);
void pico_get_ip_address(char* data);
