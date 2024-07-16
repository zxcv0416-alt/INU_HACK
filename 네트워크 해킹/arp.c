#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "arp.h"

void dump_arp_header(struct ether_arp *arp) {
    char src_ip[1024], dst_ip[1024];

    unsigned char *s = arp->arp_sha;         //sender hardware address
    unsigned char *t = arp->arp_tha;         //target hardware address

    struct in_addr ina_src_ip, ina_dst_ip;

    memcpy(&(ina_src_ip.s_addr), arp->arp_spa, 4); //sender protocol address
    sprintf(src_ip, "%s", inet_ntoa(ina_src_ip));

    memcpy(&(ina_dst_ip.s_addr), arp->arp_tpa, 4); //target protocol address
    sprintf(dst_ip, "%s", inet_ntoa(ina_dst_ip));
   
    printf("[ARP][OP:%d][%2x:%2x:%2x:%2x:%2x:%2x ->"\
    "%2x:%2x:%2x:%2x:%2x:%2x] [%s->%s]\n",
    ntohs(arp->arp_op),
    s[0],s[1],s[2],s[3],s[4],s[5],
    t[0],t[1],t[2],t[3],t[4],t[5],
    src_ip, dst_ip );

}