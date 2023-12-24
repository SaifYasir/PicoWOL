#pragma once

#include <stdint.h>

#define MAGIC_PACKET_BYTES 102

typedef struct __wifi_credential{
    char* ssid;
    char* ssid_password;
    uint32_t broadcast_address;
} wifi_credential;


typedef struct __machine
{
    uint8_t mac_address[6];
} machine;

char* get_magic_packet(machine* machine);
