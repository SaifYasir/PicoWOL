#pragma once

#include "wol/wol.h"


int start_wifi(wifi_credential* wifi_credential);

int send_wol_packet(machine* machine);