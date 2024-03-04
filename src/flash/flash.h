#pragma once

#include "flash/configuration.h"

#ifdef FF_USE_STRFUNC
#undef FF_USE_STRFUNC
#define FF_USE_STRFUNC 2
#endif
#ifndef FF_USE_STRFUNC
#define FF_USE_STRFUNC 2
#endif

void initialise_sd_card();
void sd_card_read_and_initialise_wifi_credentials();
void sd_card_read_and_initialise_wol_profiles();