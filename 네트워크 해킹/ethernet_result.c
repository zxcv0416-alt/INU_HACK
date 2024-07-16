#include <stdio.h>
#include <string.h>

#include <netinet/in.h>

#include "ethernet.h"

int main() {
    struct ether_header ether_header;
    int i;

    ether_header.ether_type = htons(ETHERTYPE_IP);

    for(i = 0; i < 6; i++) {
        ether_header.ether_dhost[i] = i;
    }

    for(i = 0; i < 6; i++) {
        ether_header.ether_shost[i] = i + 0x10;
    }

    printf("ether_header : %lu\n", (unsigned long)sizeof(struct ether_header));

    dump_ether_header(&ether_header);

    return 0;
}