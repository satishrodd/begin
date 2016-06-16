#include "headers.h"

main(int argc, char *argv[])
{
    int sock_eth, sock_icmp;                        // sockets
    int ret, one = 1;
    u_int8_t ttl = 1;
    char buf_in[MAX_MTU], buf_out[MAX_MTU];         // Buffer for packets
    char hop_ip[20];
    struct ether_header *eth_hdr;                   // eth hdr pointer
    struct ip *ip_hdr_in, *ip_hdr_out;              // ip header pointers
    struct icmp *icmp_hdr_in, *icmp_hdr_out;        // icmp header pointers
    struct ifaddrs *my_addr;
    struct sockaddr_in dst, src, *src_ptr;
    int ip_len, icmp_len, icmp_data_len;
    char dest_ip[15], src_if[255], src_ip[15];

    sock_eth = get_eth_sock();
    sock_icmp = get_icmp_sock();

    if ((ret = setsockopt(sock_icmp, IPPROTO_IP, IP_HDRINCL,
                          (char *)&one, sizeof(one))) < 0) {
        perror("setsockopt");
        exit(1);
    }

    if (argv[1] == NULL || argv[2] == NULL) {
        printf("insufficient arguments\n");
        exit(1);
    }
    memset(buf_in, 0, MAX_MTU);
    memset(buf_out, 0, MAX_MTU);

    strncpy(dest_ip, argv[1], 15);
    strncpy(src_if, argv[2], strlen(argv[2]));

    /*
     * Set all the header pointers to the location in the packet buffer.
     */
    ip_hdr_in = (struct ether_header *)buf_in;
    icmp_hdr_in = (struct icmp *)(((char *)ip_hdr_in) + sizeof(struct ip));

    ip_hdr_out = (struct ip *) buf_out;
    icmp_hdr_out = (struct icmp *) (((char *)ip_hdr_out) + sizeof(struct ip));


    /*
     * Get the my IP address;
     */
    my_addr = get_ip_addr(argv[2]);
    strncpy(src_ip, argv[2], 15); 

    printf("SRC IP: %s\n", src_ip);

    /*
     * BIND recv socket.
     */
    ip_hdr_out->ip_src.s_addr = inet_addr(src_ip);
    bzero(&src, sizeof(src));
    src.sin_family = AF_INET;
    src.sin_addr.s_addr = ip_hdr_out->ip_src.s_addr;
    if (bind(sock_icmp, (struct sockaddr *)&src,
             sizeof(struct sockaddr_in)) < 0) {
        perror("bind");
        exit(1);
    }

    while (ttl <= MAX_TTL-10) {
        // IP HEADER
        ip_hdr_out->ip_v            = 0x4;
        ip_hdr_out->ip_hl           = (int)(sizeof(struct ip) / 4);
        ip_hdr_out->ip_tos          = 0;
        ip_hdr_out->ip_tos          = 0;
        ip_hdr_out->ip_len          = htons(sizeof(struct ip)
                                      + sizeof(struct icmp));
        ip_hdr_out->ip_id           = 0;
        ip_hdr_out->ip_off          = 0;
        ip_hdr_out->ip_ttl          = ttl;
        ip_hdr_out->ip_p            = IPPROTO_ICMP;
        ip_hdr_out->ip_sum          = 0;
        ip_hdr_out->ip_dst.s_addr   = inet_addr(dest_ip);
        ip_hdr_out->ip_src.s_addr   = inet_addr(src_ip);

        ip_hdr_out->ip_sum = in_cksum((unsigned short *)buf_out,
                                      ip_hdr_out->ip_hl);

        // ICMP HEADER
        icmp_hdr_out->icmp_type  = 8;
        icmp_hdr_out->icmp_code  = 0;
        icmp_hdr_out->icmp_cksum = 0;
        icmp_hdr_out->icmp_id    = 0x435;
        icmp_hdr_out->icmp_seq   = 0;

        ip_len = ntohs(ip_hdr_out->ip_len);
        icmp_len = ip_len - sizeof(struct iphdr);
        icmp_data_len =  icmp_len - sizeof(struct icmphdr);

        bzero(&dst, sizeof(dst));
        dst.sin_family = AF_INET;
        dst.sin_addr.s_addr = ip_hdr_out->ip_dst.s_addr;

        memset(icmp_hdr_out->icmp_data, 0, icmp_data_len);

        icmp_hdr_out->icmp_cksum = in_cksum((unsigned short
                                             *)icmp_hdr_out, icmp_len);
        /*
         * Send the packet out.
         */
        ret = sendto(sock_icmp, buf_out, ip_len, 0,
                     (struct sockaddr *)&dst, sizeof(dst));
        if (ret < 0) {
            perror("sendto");
        }

        /*
         * read the incoming packet, and print the src_addr.
         */
        ret = recv(sock_icmp, buf_in, sizeof(buf_in), 0 ); 
        if (ret < 0) {
            perror("recv");
            exit(1);
        }

        printf("%d. %s\n", ttl, inet_ntoa(ip_hdr_in->ip_src));
        /*
         * ++ the TTL.
         */
        ttl++;
        if (icmp_hdr_in->icmp_type == 0) {
            printf("TRACE DONE!!!\n");
            exit(1);
        }
    }

}
