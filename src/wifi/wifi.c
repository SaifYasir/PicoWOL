#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "wifi.h"

#include "wol/wol.h"


int start_wifi(wifi_credential* wifi_credential){
    cyw43_arch_enable_sta_mode();
    return cyw43_arch_wifi_connect_blocking(
        wifi_credential.ssid,
        wifi_credential.ssid_password,
        CYW43_AUTH_WPA2_AES_PSK);
}

