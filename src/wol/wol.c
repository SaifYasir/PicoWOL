#include <stdlib.h>

#include "wol.h"

char* get_magic_packet(machine* machine){
    uint8_t packet[MAGIC_PACKET_BYTES];
    for (int i = 0; i < 6; i++)
    {
        packet[i] = UINT8_MAX;
    }
    for (int i = 6; i < MAGIC_PACKET_BYTES; i++)
    {
        packet[i] = machine->mac_address[i % 6];
    }
    return packet;

    //FIX THE LOCAL VARIABLE PACKET WILL GET DESTROYED
}