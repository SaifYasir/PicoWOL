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
struct udp_pcb* pcb = NULL;

int initialise_udp_pcb(){
    pcb = udp_new();
    if(udp_bind(pcb, IP_ADDR_ANY, UDP_PORT_NUMBER) == ERR_USE)
    {
        return ERR_USE;
    }
}

int start_wifi(wifi_credential* wifi_credential){
    cyw43_arch_enable_sta_mode();
    return cyw43_arch_wifi_connect_blocking(
        wifi_credential->ssid,
        wifi_credential->ssid_password,
        CYW43_AUTH_WPA2_AES_PSK);
}

void recieve_packet_server(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port){
    // Decipher packet into 1 of 3 options,
    // index, string, mac address
    printf("Received packet: %s",p->payload);
    char first_char = *((char*)(p->payload));
    udp_sendto(pcb,p,addr,port);
    int response = 0;
    if (first_char == INDEX_SERVER_DELIMITER)
    {
        // assume this means index
        int index = atoi((char*)(p->payload + 1));
        machine* machine = get_machine_at_index(default_wol_profiles,index);

        //Add packet to polling thing
        push_to_polling_queue(default_udp_polling_machine_queue,machine);
    }
    else if(response == STRING_SERVER_DELIMITER){
        //Assume check for string has happened
        //Implement a check for searching names
    }
    else if(first_char == MAC_SERVER_DELIMITER){
        // assume mac address is given in straight order IE A61421
    }
    
}

int start_udp_server(){
    if(pcb == NULL){
        initialise_udp_pcb();
    }
    udp_recv(pcb,recieve_packet_server,NULL);
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

    if(pcb == NULL){
        initialise_udp_pcb();
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