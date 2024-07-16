#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {

    int sock;
    struct sockaddr_in addr;
    char buffer[1024];
    int len;
    const char *http_request = "GET /HTTP/1.0\r\n\r\n";

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    memset(&addr, 0x00, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("121.78.131.190");
    addr.sin_port = htons(80);

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return 1;
    }

    if(send(sock, http_request, strlen(http_request), 0) < 0) {
        perror("send");
        return 1;
    }

    while((len = recv(sock, buffer, 1024, 0)) > 0) {
        buffer[len] = '\0';
        printf("%s", buffer);
    }

    close(sock);

    return 0;
}