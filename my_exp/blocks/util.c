#include "headers.h"
#include "globals.h"


int
get_eth_sock() {
    int sock_eth;
    if ((sock_eth = socket(AF_INET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
        perror("socket");
        exit(1);
    }
    return sock_eth;
}


int
get_icmp_sock() {
    int sock_icmp;
    if ((sock_icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
        perror("socket");
        exit(1);
    }
    return sock_icmp;
}


struct ifaddrs *
get_ip_addr(char *if_name)
{
    struct ifaddrs *all_addrs, *tmp;

    if (getifaddrs(&all_addrs)<0 ) {
        perror("getifaddrs");
        exit(1);
    }
    tmp = all_addrs;
    while(tmp){
        if (!strcmp(tmp->ifa_name, if_name)) {
            return tmp;
        }

        tmp = tmp->ifa_next;
    }
    return (NULL);
}

unsigned short
in_cksum(unsigned short *addr, int len)
{
    int nleft = len;
    int sum = 0;
    unsigned short *w = addr;
    unsigned short answer = 0;

    while (nleft > 1) {
       sum += *w++;
       nleft -= 2;
    }
    if (nleft == 1) {
        *(unsigned char *)(&answer)  = *(unsigned char *)w;
                                         sum += answer;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;
    return (answer);
}

/*
 * Function to fill the ether header.
 */
int
fill_ether_header (char *pkt, const char *intf, 
                   char *dst_mac)
{
    struct ether_header *eth_hdr;
    struct sockaddr my_mac;

    eth_hdr = (struct ether_header *)pkt;
    /*
     * Get the system MAC address.
     */
    get_my_mac(intf, &my_mac); 
    
    /*
     * Fill the mac to the pkt.
     */
/*    eth_hdr->ether_shost[0] = my_mac.sa_data[0];
    eth_hdr->ether_shost[1] = my_mac.sa_data[1];
    eth_hdr->ether_shost[2] = my_mac.sa_data[2];
    eth_hdr->ether_shost[3] = my_mac.sa_data[3];
    eth_hdr->ether_shost[4] = my_mac.sa_data[4];
    eth_hdr->ether_shost[5] = my_mac.sa_data[5];
*/  
    bcopy(&my_mac.sa_data, &eth_hdr->ether_shost, 6);
    eth_hdr->ether_type = htons(0x0806);

    /*
     * Fill the destination MAC;
     */
    bcopy(dst_mac, &eth_hdr->ether_dhost, 6);
}

/*
 * Function to fill ip header.
 */
int
fill_ip_header (char *pkt, char *dest_ip)
{

}

