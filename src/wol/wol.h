#pragma once

#include <stdint.h>

#define MAGIC_PACKET_BYTES 102

typedef struct __wifi_credential{
    char* ssid;
    char* ssid_password;
    uint32_t broadcast_address;
} wifi_credential;

typedef struct __machine{
    char* machine_name;
    uint8_t mac_address[6];
} machine;

typedef struct __machine_stack{
    machine* value;
    struct __machine_stack* next_machine;
} machine_stack;

extern machine_stack* default_wol_profiles;
extern uint8_t default_selected_wol_profile;
extern wifi_credential* default_wifi_credentials;

/**
 * Constructs magic packet for use, packet arg size should be 102
*/
uint8_t* get_magic_packet(machine* machine, uint8_t* packet);
uint8_t* get_magic_packet_mac_addr(uint8_t* machine_mac, uint8_t* packet);

machine* create_machine(const char* machine_name, const uint8_t mac_address[6]);
void destroy_machine(machine* machine_to_destroy);

machine_stack** push_to_machine_stack(machine_stack** stack, machine* value);
machine* pop_machine_stack(machine_stack** stack);
machine* get_machine_at_index(machine_stack* stack, uint8_t index);

void clear_machine_stack(machine_stack** stack);
uint8_t get_machine_stack_size(machine_stack* stack);
