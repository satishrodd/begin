#include "headers.h"
#include "globals.h"


int
get_eth_sock() {
    int sock_eth;
    if ((sock_eth = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
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

#if 0
/*
 * in_cksum --
 *      Checksum routine for Internet Protocol family headers (C Version)
 */
unsigned short in_cksum(unsigned short *addr,int len)
{
        register int sum = 0;
        u_short answer = 0;
        register u_short *w = addr;
        register int nleft = len;

        /*
         * Our algorithm is simple, using a 32 bit accumulator (sum), we add
         * sequential 16 bit words to it, and at the end, fold back all the
         * carry bits from the top 16 bits into the lower 16 bits.
         */
        while (nleft > 1)  {
                sum += *w++;
                nleft -= 2;
        }

        /* mop up an odd byte, if necessary */
        if (nleft == 1) {
                *(u_char *)(&answer) = *(u_char *)w ;
                sum += answer;
        }

        /* add back carry outs from top 16 bits to low 16 bits */
        sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
        sum += (sum >> 16);                     /* add carry */
        answer = ~sum;                          /* truncate to 16 bits */
        return(answer);
}
#endif 
