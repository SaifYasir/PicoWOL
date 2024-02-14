#pragma once

#include "hardware/spi.h"

/*
    This program implements SPI to interface with flash storage devices
*/

#define FLASH_SPI_INSTANCE          spi1

#define FLASH_SPI_CS_GPIO           13
#define FLASH_SPI_RX_GPIO           12
#define FLASH_SPI_TX_GPIO           11
#define FLASH_SPI_SCK_GPIO          10

#define FLASH_SPI_BAUD_RATE         200 * 1000

#define FLASH_WIFI_FILENAME         "wifi_credentials.txt"
#define FLASH_WOL_FILENAME          "wol_profiles.txt"
#define FLASH_CSV_DELIMITER         ";\r\n"