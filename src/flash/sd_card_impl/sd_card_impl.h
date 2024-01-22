#pragma once

#include "stdint.h"

#include "configuration.h"
#include "flash/configuration.h"

#define SD_COMMAND_BIT_SIZE 40

typedef struct __sd_command{
    // should be 0x01
    uint8_t start_bit;
    // should be 0x01 or 0x00
    uint8_t transmission_bit;
    // should be between 0x00 <= 0x3F
    uint8_t command_index;
    uint32_t argument;
    //should be between 0x00 <= 0x7F
    uint8_t crc7_check;

    //should be 0x01
    uint8_t stop_bit;
} sd_command;

typedef struct _sd_properties{
    uint8_t cpol;
    uint8_t cpha;
} sd_properties;

uint8_t __generate_crc7(sd_command* sd_command);
void initialise_sd_card();
void send_sd_card_command(sd_command* sd_command);