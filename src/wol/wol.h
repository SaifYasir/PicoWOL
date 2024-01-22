#pragma once

#include <stdint.h>

#define MAGIC_PACKET_BYTES 102

typedef struct __wifi_credential{
    char* ssid;
    char* ssid_password;
    uint32_t broadcast_address;
} wifi_credential;

typedef struct __machine{
    uint8_t mac_address[6];
} machine;

typedef struct __machine_stack{
    machine* value;
    struct __machine_stack* next_machine;
} machine_stack;

/**
 * Constructs magic packet for use, packet arg size should be 102
*/
uint8_t* get_magic_packet(machine* machine, uint8_t* packet);

machine_stack* push_to_machine_stack(machine_stack* stack, machine* value);
machine* pop_machine_stack(machine_stack** stack);

machine_stack** create_machine_stack(machine_stack** stack);
void clear_machine_stack(machine_stack** stack);

uint8_t get_machine_stack_size(machine_stack* stack);
