#include <stdio.h>
#include <string.h>
#include <netinet/in.h>

#include "ip.h"
#include "tcp.h"

struct packet {
    struct ip ip;
    struct tcphdr tcphdr;
    char buffer[100];
};

__attribute__((__packed__));

int main() {
    struct packet packet;
    strcpy(packet.buffer, "hello! inu_hack!!");

    packet.ip.ip_hl = (sizeof(struct ip) >> 2);
    packet.ip.ip_len = htons(sizeof(struct packet));

    packet.tcphdr.th_off = sizeof(struct tcphdr) >> 2;

    packet.tcphdr.th_sport = htons(1234);
    packet.tcphdr.th_dport = htons(80);

    packet.tcphdr.th_seq = htonl(1);
    packet.tcphdr.th_ack = htonl(2);

    packet.tcphdr.th_flags = 0;
    packet.tcphdr.th_flags |= TH_SYN;
    packet.tcphdr.th_flags |= TH_ACK;

    printf("tcphdr : %lu\n", (unsigned long)sizeof(struct tcphdr));

    dump_tcp_header(&packet.ip);

    return 0;
}