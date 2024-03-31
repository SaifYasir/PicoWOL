#pragma once

#include "wol/wol.h"

/**
 * \file wifi.h
 * \brief This file specifies functions relating to wifi
 */

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
extern machine_stack* default_udp_polling_machine_stack;

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


/**
 * \brief Checks the stack to see if any machines need to be awoken (a machine is awoken if its in the provided stack)
 * 
 * \param machine_polling_stack \ref machine_stack double pointer containing \ref machine to wake
 */
void poll_udp_packets(machine_stack** machine_polling_stack);

/**
 * \brief Returns the port number set for the application via \ref UDP_PORT_NUMBER
 * 
 * \return Port number 
 */
int pico_get_port_number();

/**
 * \brief Returns the MAC address for the wifi card onboard the Rasberry Pi Pico
 * 
 * \param mac data buffer to copy MAC address into
 */
void pico_get_mac_address(uint8_t mac[6]);

/**
 * \brief Returns the IP address assigned when the Pico is connected to WiFi (via \ref start_wifi)
 * 
 * \param data Data buffer to copy string formatted IPV4 address into
 */
void pico_get_ip_address(char* data);
