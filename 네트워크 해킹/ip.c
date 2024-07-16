#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ip.h"

void dump_ip_header(struct ip *ip) {
    char src_ip[1024];
    char dst_ip[1024];

    strcpy(src_ip, inet_ntoa(ip->ip_src));
    strcpy(dst_ip, inet_ntoa(ip->ip_dst));

    printf("[IP] %s->%s (ttl:%d, cksum:0x04x)\n",
            src_ip, dst_ip, ip->ip_ttl, ntohs(ip->ip_sum));
}