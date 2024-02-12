#include "hw_config.h"
#include "configuration.h"


static spi_t sd_card_spi = {
    .hw_inst = FLASH_SPI_INSTANCE,  // SPI component
    .miso_gpio = FLASH_SPI_RX_GPIO, // GPIO number (not pin number)
    .mosi_gpio = FLASH_SPI_TX_GPIO,
    .sck_gpio = FLASH_SPI_SCK_GPIO,
    .baud_rate = FLASH_SPI_BAUD_RATE,  
};

static sd_card_t sd_card = {
    .pcName = "0:",   // Name used to mount device
    .spi = &sd_card_spi,  // Pointer to the SPI driving this card
    .ss_gpio = FLASH_SPI_CS_GPIO,    // The SPI slave select GPIO for this SD card
};

size_t spi_get_num(){
    return sizeof(sd_card_spi);
}

spi_t* spi_get_by_num(size_t num){
    return &sd_card_spi;
}

size_t sd_get_num(){
    return sizeof(sd_card);
}

sd_card_t* sd_get_by_num(size_t num){
    return &sd_card;
}