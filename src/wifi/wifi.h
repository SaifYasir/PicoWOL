#pragma once

#include "wol/wol.h"

/**
 * Add to this stack, then poll to wake up devices
*/
extern machine_stack* default_udp_polling_machine_stack;

int start_wifi(wifi_credential* wifi_credential);

void poll_udp_packets(machine_stack** machine_stack);