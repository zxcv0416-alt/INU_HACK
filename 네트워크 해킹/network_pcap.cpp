#include <stdio.h>
#include <pcap.h>

// gcc 컴파일 할 때 #gcc -o pn network_pcap.c -lpcap 으로 할 것.

int main () {

    pcap_if_t *alldevs;
    pcap_if_t *d;
    int i = 0;

    char errbuf[PCAP_ERRBUF_SIZE];

    if(pcap_findalldevs(&alldevs, errbuf) < 0) {
        printf("pcap_findalldevs error\n");
        return 1;
    }

    if(!alldevs) {
        printf("%s\n", errbuf);
    }

    for(d = alldevs; d; d = d->next) {
        printf("%p : %d. %s",d, ++i, d->name);

        if(d -> description) printf("(%s)", d->description);
        printf("\n");
    }

    pcap_freealldevs(alldevs);

    return 0;
}