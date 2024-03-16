#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/util/queue.h"

#include "wifi.h"
#include "wol/wol.h"

#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/netif.h"
#include "lwip/ip4.h"


queue_t* default_udp_polling_machine_queue;

int start_wifi(wifi_credential* wifi_credential){
    cyw43_arch_enable_sta_mode();
    return cyw43_arch_wifi_connect_blocking(
        wifi_credential->ssid,
        wifi_credential->ssid_password,
        CYW43_AUTH_WPA2_AES_PSK);
}

int pico_get_port_number(){
    return UDP_PORT_NUMBER;
}

void pico_get_mac_address(uint8_t mac[6]){
    cyw43_wifi_get_mac(&cyw43_state,CYW43_ITF_STA,mac);
}

void pico_get_ip_address(char* data){
    u32_t addr = netif_default->ip_addr.addr  & netif_default->netmask.addr;
    ip4_addr_t* ip_address = netif_ip4_addr(netif_default);
    char* ip_address_str = ipaddr_ntoa(ip_address);
    memcpy(data,ip_address_str,strlen(ip_address_str) + 1);
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
    ip_addr_t broadcast_address;
    
    // get broadcast address
    broadcast_address.addr = (netif_default->ip_addr.addr & netif_default->netmask.addr) | ~netif_default->netmask.addr;
    udp_connect(pcb,&broadcast_address,UDP_PORT_NUMBER);

    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT,MAGIC_PACKET_BYTES,PBUF_RAM);
    pbuf_take(p,wol_packet,MAGIC_PACKET_BYTES);
    
    err_t er = udp_send(pcb,p);
    cyw43_arch_poll();

    pbuf_free(p);
    udp_remove(pcb);
    return er;
}

void initialise_polling_queue(queue_t** queue){
   *queue = malloc(sizeof(machine) * MAX_QUEUE_WOL);
   queue_init_with_spinlock(*queue,sizeof(machine),MAX_QUEUE_WOL,QUEUE_SPINLOCK_ID);
}

void push_to_polling_queue(queue_t* queue, machine* machine){
    queue_try_add(queue,machine);
}

void poll_udp_packets(queue_t* machine_queue){
    int queue_size = queue_get_level(machine_queue);
    for (int i = 0; i < queue_size; i++)
    {
        machine machine_to_wake;
        queue_remove_blocking(machine_queue,&machine_to_wake);
        send_wol_packet(&machine_to_wake);
    }
}