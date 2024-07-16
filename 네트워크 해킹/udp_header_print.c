#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "udp.h"

struct packet {
    struct udphdr udphdr;
    char data[100];
};

__attribute__((__packed__));

int main() {
    struct packet packet;

    packet.udphdr.uh_sport = htons(1234);
    packet.udphdr.uh_dport = htons(100);

    packet.udphdr.uh_ulen = htons(sizeof(struct udphdr) + 100);

    strcpy(packet.data, "hello_udp_inu_hack");

    printf("struct udphdr : %lu", (unsigned long)sizeof(struct udphdr));

    dump_udp_header(&packet.udphdr);

    return 0;
}