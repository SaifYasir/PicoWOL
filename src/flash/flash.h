#pragma once

#include "flash/configuration.h"

/**
 * \file flash.h
 * \brief Functions to initialise and read from SD card via SPI interface using variables set in \ref configuration.h
*/

/**
 * \def FF_USE_STRFUNC
 * This constant is defined in fatfs for the FAT file system, this value "Enables string functions with LF-CRLF conversion."
 * Read more at <a href="http://elm-chan.org/fsw/ff/doc/config.html#use_strfunc">Fatfs FF_USE_STRFUNC<a>
 */
#ifdef FF_USE_STRFUNC
#undef FF_USE_STRFUNC
#define FF_USE_STRFUNC 2
#endif
#ifndef FF_USE_STRFUNC
#define FF_USE_STRFUNC 2
#endif

/**
 * \brief Initialises the SD card connected to support communication
 */
void initialise_sd_card();
/**
 * \brief Reads SD card in root directory for file defined \ref FLASH_WIFI_FILENAME
 * 
 * The wifi credentials should be stored as so: SSID;SSID_PASS e.g. VM1126431;passwordhere
 */
void sd_card_read_and_initialise_wifi_credentials();
/**
 * \brief Reads the SD card in the root directory for file defined \ref FLASH_WOL_FILENAME
 * 
 * The wifi credentials should be stored as so: profilename;MACaddress e.g. remote_pc;6045CBA5A2A8
 */
void sd_card_read_and_initialise_wol_profiles();