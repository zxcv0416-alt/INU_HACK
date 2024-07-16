#ifndef _UDP_H
#define _UDP_H

#include <stdint.h>

struct udphdr {
    uint16_t uh_sport;
    uint16_t uh_dport;
    uint16_t uh_ulen;
    uint16_t uh_sum;
};

__attribute__((__packed__));

void dump_udp_header(struct udphdr *udphdr);

#endif