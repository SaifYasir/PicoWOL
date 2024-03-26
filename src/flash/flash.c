#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flash.h"

#include "wol/wol.h"

#include "ff.h"
#include "f_util.h"
#include "hw_config.h"

char* parse_csv_line(const char* string, uint8_t field_position){
    char* string_copy = malloc(strlen(string) + 1);
    strcpy(string_copy,string);
    char* string_position;
    for (string_position = strtok(string_copy,FLASH_CSV_DELIMITER); string_position && *string_position; string_position = strtok(NULL,FLASH_CSV_DELIMITER))
    {
        if(!--field_position){
            return string_position;
        }
    }
    return NULL;
}

void hex_string_to_byte_array(const char* hex_string, uint8_t* byte_array, size_t byte_array_size){
    size_t hex_string_length = strlen(hex_string);
    if(hex_string_length != (byte_array_size * 2)){
        printf("Hex string to byte array invalid input!");
        return;
    }
    for(size_t i = 0; i < hex_string_length; i += 2){
        sscanf(hex_string + i, "%2hhx", &byte_array[i/2]);
    }
}

void initialise_sd_card(){
    sd_card_t* pSD = sd_get_by_num(0);
    FRESULT mount_result = f_mount(&pSD->fatfs,pSD->pcName,1);
    if (FR_OK != mount_result) panic("f_mount error: %s (%d)\n", FRESULT_str(mount_result), mount_result);
}

void sd_card_read_and_initialise_wol_profiles(){
    FIL wol_profiles_file;
    FRESULT result = f_open(&wol_profiles_file,FLASH_WOL_FILENAME,FA_READ);
    if(result != FR_OK){
        panic("Could not read file: %s, FatFS reported this result: %s \n",FLASH_WIFI_FILENAME,FRESULT_str(result));
    }
    char line[300];
    while(f_gets(line,sizeof(line),&wol_profiles_file)){
        //Read lines and create profiles
        machine* new_wol_profile = malloc(sizeof(machine));
        new_wol_profile->machine_name = parse_csv_line(line,1);
        char* second_line = parse_csv_line(line,2);
        hex_string_to_byte_array(second_line,new_wol_profile->mac_address,sizeof(new_wol_profile->mac_address));
        push_to_machine_stack(&default_wol_profiles,new_wol_profile);
    }
    result = f_close(&wol_profiles_file);
    if(result != FR_OK){
        printf("Could not close file: %s, reason:  %s \n",FLASH_WIFI_FILENAME,FRESULT_str(result));
    }
}

void sd_card_read_and_initialise_wifi_credentials(){
    FIL wifi_credentials_file;
    FRESULT result = f_open(&wifi_credentials_file,FLASH_WIFI_FILENAME,FA_READ);
    if(result != FR_OK){
        panic("Could not read file: %s, FatFS reported this result: %s \n",FLASH_WIFI_FILENAME,FRESULT_str(result));
    }
    char line[300];
    f_gets(line,sizeof(line),&wifi_credentials_file);
    default_wifi_credentials = malloc(sizeof(wifi_credential));
    default_wifi_credentials->ssid = parse_csv_line(line,1);
    default_wifi_credentials->ssid_password = parse_csv_line(line,2);
    result = f_close(&wifi_credentials_file);
    if(result != FR_OK){
        printf("Could not close file: %s, reason:  %s \n",FLASH_WIFI_FILENAME,FRESULT_str(result));
    }
}