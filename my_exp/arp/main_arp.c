/*---------------------------------------------------------------------------
 * 
 * main_arp.c 
 *
 *     09/04/2014 - 
 *
 *     <esatrod@egi.ericsson.com>
 *
 *     Copyright (c) 2014 RedBack Networks, Inc.
 *     All rights reserved.
 *
 *---------------------------------------------------------------------------
 */

#include"headers.h"


struct arp_header {
    uint16_t htype;
    uint16_t ptype;
    char haddr_len;
    char paddr_len;
    uint16_t opcode;
    char sender_haddr[6];
    char sender_ip[4];
    char target_haddr[6];
    char target_ip[4];
};

main()
{
    int sock_eth;                                   // ethernet socket.
    char buf[MAX_MTU];                              // Packet buffer.
    struct sockaddr_ll dst;                         // destination IP address.
    int ret = 0;                                    // return.
    struct ether_header *eth_hdr;                   // ether header
    struct ifreq req;
    char my_hdr[6] = {0x5c, 0x26, 0x0a, 0x83, 0xb1, 0x08};
    struct arp_header *arp_hdr_ptr = NULL;

    /*
     * Get the ethernet socket.
     */
    sock_eth = get_eth_sock();

    /*
     * Create the ethernet frame.
     */
    eth_hdr = (struct ether_header *)buf;
    eth_hdr->ether_dhost[0] = 0xff;
    eth_hdr->ether_dhost[1] = 0xff;
    eth_hdr->ether_dhost[2] = 0xff;
    eth_hdr->ether_dhost[3] = 0xff;
    eth_hdr->ether_dhost[4] = 0xff;
    eth_hdr->ether_dhost[5] = 0xff;

    eth_hdr->ether_shost[0] = 0x5c;
    eth_hdr->ether_shost[1] = 0x26;
    eth_hdr->ether_shost[2] = 0x0a;
    eth_hdr->ether_shost[3] = 0x83;
    eth_hdr->ether_shost[4] = 0xb1;
    eth_hdr->ether_shost[5] = 0x08;

    bcopy(my_hdr, &eth_hdr->ether_shost, 6);

    eth_hdr->ether_type = htons(0x0806);

    /*
     * get the if index.
     */

    strcpy((char *)&req.ifr_name, "eth0");
    if (ioctl(sock_eth, SIOCGIFINDEX, &req) < 0 ) {
        perror("SIOCGIFINDEX");
    }

       
    bzero(&dst, sizeof(dst));
    dst.sll_family = PF_PACKET;
    dst.sll_protocol = htons(ETH_P_ARP);
    dst.sll_ifindex = req.ifr_ifindex;
    dst.sll_pkttype = 0;
    dst.sll_hatype = ARPHRD_ETHER;
    dst.sll_halen = 0;
    dst.sll_addr[6] = 0x00;
    dst.sll_addr[7] = 0x00;
    

    if ( bind(sock_eth, (const struct sockaddr *)&dst, sizeof(dst))<0) {
        perror("bind");
    }

    /*
     * fill ARP header
     */
    arp_hdr_ptr = (struct arp_header *)&buf[14];

    arp_hdr_ptr->htype = htons(0x0001);
    arp_hdr_ptr->ptype = htons(0x0800);
    arp_hdr_ptr->haddr_len = 0x06;
    arp_hdr_ptr->paddr_len = 0x04;
    arp_hdr_ptr->opcode = htons(0x0001);
    bcopy(my_hdr, &arp_hdr_ptr->sender_haddr, 6);
    arp_hdr_ptr->sender_ip[0] = 100; 
    arp_hdr_ptr->sender_ip[1] = 96; 
    arp_hdr_ptr->sender_ip[2] = 9; 
    arp_hdr_ptr->sender_ip[3] = 108; 
    memset(&arp_hdr_ptr->target_haddr, 0xff, 6);
    arp_hdr_ptr->target_ip[0] = 100;
    arp_hdr_ptr->target_ip[1] = 96;
    arp_hdr_ptr->target_ip[2] = 9;
    arp_hdr_ptr->target_ip[3] = 27;



    

    /*
     * Send the arp request.
     */
    ret = sendto(sock_eth, buf, 42, 0, 
                 (struct sockaddr *)&dst, sizeof(dst));
    /*
     * receive the arp response
     */
    while(1) {

    ret = recvfrom(sock_eth, buf, MAX_MTU, 0, NULL, NULL);

    if (buf[12] == 0x08 &&
        buf[13] == 0x06 ) {
//        arp_hdr_ptr->sender_ip[0] == 100 &&
  //      arp_hdr_ptr->sender_ip[1] == 96 &&
    //    arp_hdr_ptr->sender_ip[2] == 9 &&
      //  arp_hdr_ptr->sender_ip[3] == 128 ) {
    printf("\n%3d.%3d.%3d.%3d->%02x:%02x:%02x:%02x:%02x:%02x", 
           (unsigned char)arp_hdr_ptr->sender_ip[0],
           (unsigned char)arp_hdr_ptr->sender_ip[1],
           (unsigned char)arp_hdr_ptr->sender_ip[2],
           (unsigned char)arp_hdr_ptr->sender_ip[3],
           (unsigned char)arp_hdr_ptr->sender_haddr[0],
           (unsigned char)arp_hdr_ptr->sender_haddr[1],
           (unsigned char)arp_hdr_ptr->sender_haddr[2], 
           (unsigned char)arp_hdr_ptr->sender_haddr[3], 
           (unsigned char)arp_hdr_ptr->sender_haddr[4],
           (unsigned char)arp_hdr_ptr->sender_haddr[5]);
    }
    }



    /*
     * Print the response.
     */


}
