#pragma once

#include "wol/wol.h"

#include "pico/util/queue.h"

/**
 * \file wifi.h
 * \brief This file specifies functions relating to wifi
 */

/**
 * \def MAX_QUEUE_WOL
 * \todo Remove this
*/
#define MAX_QUEUE_WOL            5
#define QUEUE_SPINLOCK_ID        1

/**
 * \def UDP_PORT_NUMBER
 * Port number for UDP server to work on
 */
#define UDP_PORT_NUMBER          7

/**
 * \def MAC_SERVER_DELIMITER
 * Defines the delimiter used to signify MAC input in a UDP recieved packet
 */
#define MAC_SERVER_DELIMITER    ','
/**
 * \def INDEX_SERVER_DELIMITER
 * Defines the delimiter used to signify the input is an index in a UDP recieved packet
 */
#define INDEX_SERVER_DELIMITER  ';'
/**
 * \def STRING_SERVER_DELIMITER
 * Defines the delimiter used to signify input represents a substring in a UDP recieved packet
 */
#define STRING_SERVER_DELIMITER '.'

/**
 * Add to this stack, then poll to wake up devices
*/
extern queue_t* default_udp_polling_machine_queue;

/**
 * \brief Starts WIFI connecting procedure
 * 
 * \param wifi_credential \ref wifi_credential pointer to attain needed credentials
 * \return int 
 */
int start_wifi(wifi_credential* wifi_credential);

/**
 * \brief Begins UDP server to receive external inputs
 * 
 * \todo explain potential inputs
 * 
 * \return int 
 */
int start_udp_server();

void initialise_polling_queue(queue_t** queue);
void push_to_polling_queue(queue_t* queue, machine* machine);
void poll_udp_packets(queue_t* machine_queue);

int pico_get_port_number();
void pico_get_mac_address(uint8_t mac[6]);
void pico_get_ip_address(char* data);
