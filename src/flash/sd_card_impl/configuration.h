#pragma once

#define SD_GO_IDLE_STATE_CMD_BIT              0x00
#define SD_SEND_OP_COMMAND_CMD_BIT            0x01
#define SD_SWITCH_FUNC_CMD_BIT                0x06   
#define SD_SEND_IF_COND_CMD_BIT               0x08
#define SD_SEND_CSD_CMD_BIT                   0x09
#define SD_SEND_CID_CMD_BIT                   0x0A
#define SD_STOP_TRANSMISSION_CMD_BIT          0x0C
#define SD_SEND_STATUS_CMD_BIT                0x0D
// Only works on SDCS cards; SDHC and SDCX set to 512 bytes.
#define SD_SET_BLOCKLEN_CMD_BIT               0x10
#define SD_READ_SINGLE_BLOCK_CMD_BIT          0x11
#define SD_READ_MULTIPLE_BLOCK_CMD_BIT        0x12
#define SD_WRITE_BLOCK_CMD_BIT                0x18
#define SD_WRITE_MULTIPLE_BLOCK_CMD_BIT       0x19
#define SD_PROGRAM_CSD_CMD_BIT                0x1B
// Does not work on SDHC and SDXC cards
#define SD_SET_WRITE_PROTECT_CMD_BIT          0x1C
// Does not work on SDHC and SDXC cards
#define SD_CLR_WRITE_PROT_CMD_BIT             0x1D
// Does not work on SDHC and SDXC cards
#define SD_SEND_WRITE_PROT_CMD_BIT            0x1E
#define SD_ERASE_WR_BLK_START_ADDR_CMD_BIT    0x20
#define SD_ERASE_WR_BLK_END_ADDR_CMD_BIT      0x21
#define SD_ERASE_CMD_BIT                      0x26
#define SD_LOCK_UNLOCK_CMD_BIT                0x2A
#define SD_APP_CMD_CMD_BIT                    0x37
#define SD_GEN_CMD_CMD_BIT                    0x38
#define SD_READ_OCR_CMD_BIT                   0x3A
#define SD_CRC_ON_OFF_CMD_BIT                 0x3B

#define SD_SD_STATUS_APP_CMD_BIT              0x0D
#define SD_SEND_NUM_WR_BLOCKS_APP_CMD_BIT     0x16
#define SD_SET_WR_ERASE_COUNT_APP_CMD_BIT     0x17
#define SD_SD_SEND_OP_COND_APP_CMD_BIT        0x29
#define SD_SET_CLR_CARD_DETECT_APP_CMD_BIT    0x2A
#define SD_SEND_SCR_APP_CMD_BIT               0x33


