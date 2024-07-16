#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "icmp.h"

void dump_icmp_header(struct icmphdr *icmphdr) {

    printf("[ICMP][Type : %d][Code : %d]\n",
            icmphdr->type, icmphdr->code);
}