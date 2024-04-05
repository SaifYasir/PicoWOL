#pragma once

#include "hardware/spi.h"

/**
 * \file configuration.h
 * \brief Defines hard set variables used for SPI communication and file identification
*/

/**
 * \def FLASH_SPI_INSTANCE
 * Defines the SPI instance used on the PICO, 
 * this instance is dependent on the GPIO Pins used
 */
#define FLASH_SPI_INSTANCE          spi1

/**
 * \def FLASH_SPI_CS_GPIO
 * SPI Chip Select GPIO pin
 */
#define FLASH_SPI_CS_GPIO           13
/**
 * \def FLASH_SPI_RX_GPIO
 * SPI RX GPIO pin or MISO pin
 */
#define FLASH_SPI_RX_GPIO           12
/**
 * \def FLASH_SPI_TX_GPIO
 * SPI TX GPIO PIN or MOSI pin
 */
#define FLASH_SPI_TX_GPIO           11
/**
 * \def FLASH_SPI_SCK_GPIO
 * SPI Clock GPIO pin
 */
#define FLASH_SPI_SCK_GPIO          10

/**
 * \def FLASH_SPI_BAUD_RATE
 * Baud rate set for communication between SD card and PICO
 */
#define FLASH_SPI_BAUD_RATE         200 * 1000

/**
 * \def FLASH_WIFI_FILENAME
 * File name used to identify file containing wifi configuration settings
 */
#define FLASH_WIFI_FILENAME         "wifi_credentials.txt"
/**
 * \def FLASH_WOL_FILENAME
 * File name used to identify file containing WOL profiles to load 
 */
#define FLASH_WOL_FILENAME          "wol_profiles.txt"
/**
 * \def FLASH_CSV_DELIMITER
 * Specifies the CSV limiter used
 */
#define FLASH_CSV_DELIMITER         ";\r\n"