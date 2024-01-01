#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "wifi.h"

#include "wol/wol.h"


int start_wifi(wifi_credential* wifi_credential){
    cyw43_arch_enable_sta_mode();
    return cyw43_arch_wifi_connect_blocking(
        wifi_credential->ssid,
        wifi_credential->ssid_password,
        CYW43_AUTH_WPA2_AES_PSK);
}

int send_wol_packet(machine* machine){
    uint8_t wol_packet[MAGIC_PACKET_BYTES];
    get_magic_packet(machine,wol_packet);

    struct udp_pcb* pcb = udp_new();
    if(udp_bind(pcb, IP_ADDR_ANY, 0) == ERR_USE)
    {
        return ERR_USE;
    }

    ip_addr_t target_addr;

    //find a way to put broadcast address here
    ip4addr_aton("",&target_addr);
    udp_connect(pcb,&target_addr,7);

    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT,MAGIC_PACKET_BYTES,PBUF_RAM);
    pbuf_take(p,wol_packet,MAGIC_PACKET_BYTES);
    
    err_t er = udp_send(pcb,p);
    cyw43_arch_poll();

    pbuf_free(p);
    udp_remove(pcb);
    return er;
}