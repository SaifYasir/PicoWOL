#pragma once

#include "wol/wol.h"

#include "pico/util/queue.h"

#define MAX_QUEUE_WOL       5
#define QUEUE_SPINLOCK_ID   1

/**
 * Add to this stack, then poll to wake up devices
*/
extern queue_t* default_udp_polling_machine_queue;

int start_wifi(wifi_credential* wifi_credential);

void initialise_polling_queue(queue_t** queue);
void push_to_polling_queue(queue_t* queue, machine* machine);
void poll_udp_packets(queue_t* machine_queue);
