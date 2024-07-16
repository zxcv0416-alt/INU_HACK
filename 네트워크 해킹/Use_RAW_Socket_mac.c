#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <netinet/in.h>
#include "ethernet.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "icmp.h"

#define BUFSIZE 2048

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    struct ether_header *ether_header = (struct ether_header *)packet;
    void *header_ptr = (void *)(packet + sizeof(struct ether_header));

    printf("-------------------------------------\n");

    dump_ether_header(ether_header);

    switch(ntohs(ether_header->ether_type)) {
        case ETHERTYPE_ARP:
            printf("ARP packet detected\n");
            break;
        case ETHERTYPE_IP:
        {
            struct ip *ip = (struct ip *)header_ptr;
            dump_ip_header(ip);
            void *next_header_ptr = (void *)((char *)ip + (ip->ip_hl << 2));

            switch(ip->ip_p) {
                case IPPROTO_TCP:
                    dump_tcp_header(ip);
                    break;
                case IPPROTO_UDP:
                    dump_udp_header((struct udphdr *)next_header_ptr);
                    break;
                case IPPROTO_ICMP:
                    dump_icmp_header((struct icmphdr *)next_header_ptr);
                    break;
                default:
                    printf("Unknown IP protocol: %d\n", ip->ip_p);
                    break;
            }
            break;
        }
        default:
            printf("Unknown Ethernet type: 0x%04x\n", ntohs(ether_header->ether_type));
            break;
    }
    printf("-------------------------------------\n");
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Usage: %s [interface]\n", argv[0]);
        return 1;
    }

    char *dev = argv[1];
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(dev, BUFSIZE, 1, 1000, errbuf);

    if(handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return 2;
    }

    pcap_loop(handle, -1, packet_handler, NULL);

    pcap_close(handle);

    return 0;
}
