#pragma once

#include <stdint.h>

/**
 * \file wol.h
 * \brief This file specifies structures and methods used for wake-on-lan
 */

/**
 * \def MAGIC_PACKET_BYTES
 * The amount of bytes used for a wake-on-lan packet
 */
#define MAGIC_PACKET_BYTES 102

/**
 * \struct wifi_credential wol.h wol
 * \brief Structure containing credentials when starting wifi on Pico
 */
typedef struct wifi_credential{
    char* ssid;                     /**< Pointer to the SSID string */
    char* ssid_password;            /**< Pointer to the SSID password string */
} wifi_credential;

/**
 * \struct machine wol.h wol
 * \brief Structure defining a wake-on-lan device
 */
typedef struct machine{
    char* machine_name;             /**< Pointer to device name (can be anything), used as the id of the device ie remote_machine*/
    uint8_t mac_address[6];         /**< mac address of the device */
} machine;

/**
 * \struct machine_stack wol.h wol
 * \brief Defines a stack for \ref machine structures to be stored
 */
typedef struct machine_stack{
    machine* value;                     /**< Pointer to \ref machine */
    struct machine_stack* next_machine; /**< Pointer to next \ref machine_stack creating a linked list*/
} machine_stack;

/**
 * \brief Defines a default \ref machine_stack the application will use
 */
extern machine_stack* default_wol_profiles;
/**
 * \brief Defines the currently selected machine within the \ref machine_stack -> \ref default_wol_profiles
 */
extern uint8_t default_selected_wol_profile;
/**
 * \brief Defines a default \ref machine_stack the application will use
 */
extern wifi_credential* default_wifi_credentials;

/**
 * \brief Constructs magic packet for use
 * \param[in] machine to generate magic packet from
 * \param[out] packet to store magic packet into, user must allocate memory for the packet of size \ref MAGIC_PACKET_BYTES
 * \return pointer to packet arguement
*/
uint8_t* get_magic_packet(machine* machine, uint8_t* packet);
/**
 * \brief Constructs magic packet for use, similar to \ref get_magic_packet but instead only requires the mac address rather than a \ref machine struct
 * \param[in] machine_mac mac_address to generate magic packet from, eg -> 00-1B-63-84-E6 would be stored as [0,27,99,132,230]
 * \param[out] packet to store magic packet into, user must allocate memory for the packet of size \ref MAGIC_PACKET_BYTES
 * \return pointer to packet arguement
*/
uint8_t* get_magic_packet_mac_addr(uint8_t* machine_mac, uint8_t* packet);

/**
 * \brief Creates a machine object, this function will duplicate values provided in the args to be stored
 * 
 * \param machine_name  Pointer to device name (can be anything), used as the id of the device ie remote_machine
 * \param mac_address   MAC address of the device
 * \return machine*     Pointer to the created machine
 */
machine* create_machine(const char* machine_name, const uint8_t mac_address[6]);

/**
 * \brief Deallocates and destorys machine instance
 * \param machine_to_destroy Pointer to the machine to be destroyed and freed
 */
void destroy_machine(machine* machine_to_destroy);

/**
 * @brief Pushes a \ref machine to a \ref machine_stackd)
 * 
 * @param stack stack to push to, does not need to be initialised (can be nulled)
 * @param value \ref machine to push to \ref machine_stack
 * @return machine_stack** Double pointer of passed stack arguement
 */
machine_stack** push_to_machine_stack(machine_stack** stack, machine* value);

/**
 * \brief Pops machine from \ref machine_stack
 * 
 * @param stack \ref machine_stack to pop, destroying the stack when the last machine is popped
 * @return \ref machine pointer that was popped
 */
machine* pop_machine_stack(machine_stack** stack);

/**
 * \brief Get the \ref machine stored at index
 * 
 * \param stack \ref machine_stack to search
 * \param index index of wanted machine, 0 indexed
 * \return \ref machine pointer stored at index
 */
machine* get_machine_at_index(machine_stack* stack, uint8_t index);

/**
 * \brief Cleares a \ref machine_stack of any machines stored inside
 * 
 * @param stack \ref machine_stack to be cleared
 */
void clear_machine_stack(machine_stack** stack);

/**
 * \brief Get the amount of machine devices within a stack
 * @param stack \ref machine_stack to be measured
 * @return uint8_t with the amount of machines stored
 */
uint8_t get_machine_stack_amount(machine_stack* stack);
