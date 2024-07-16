#ifndef _ICMP_H
#define _ICMP_H

#include <stdint.h>

struct icmphdr {
    uint8_t type;       //message type
    uint8_t code;       //type sub-code
    uint16_t checksum;
    uint16_t id;
    uint16_t sequence;
};

__attribute__((__packed__));

void dump_icmp_header(struct icmphdr *icmphdr);

#endif