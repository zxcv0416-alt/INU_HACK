#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
// server
int main (){
    int sock, client_sock;
    struct sockaddr_in addr, client_addr;
    char buffer[1024];
    int len, recv_len;
    socklen_t addr_len;

    const char * http_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<html>\r\n"
        "<head>\r\n"
        "<title>Hi_inu_hack#1</title>\r\n"
        "</head>\r\n"
        "<body>\r\n"
        "<h1>Menu_Hi_inu_hack</h1>\r\n"
        "<a href="">naver</a><br>\r\n"
        "</body></hrml>";

    
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    memset(&addr, 0x00, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }

    if(listen(sock, 5) < 0) {
        perror("listen");
        return 1;
    }

    addr_len = sizeof(client_addr);

    printf("waiting for client...\n");

    while((client_sock = accept(sock, (struct sockaddr *)&client_addr, &addr_len)) > 0) {
        printf("client ip : %s\n", inet_ntoa(client_addr.sin_addr));

        if((recv_len = recv(client_sock, buffer, 1024, 0)) < 0) {
            perror("recv");
            break;
        }

        buffer[recv_len] = '\0';

        printf("%s\n", buffer);

        send(client_sock, http_response, strlen(http_response), 0);

        printf("%s\n", http_response);

        close(client_sock);
    }

    close(sock);

    return 0;
}