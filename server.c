#include <asm-generic/socket.h>
# include <netinet/in.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>
# include <sys/socket.h>
#include <sys/types.h>
# include <unistd.h>

int main (void){
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    int yes = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    // can't see any change after this setsockport

    if (bind(server, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(server, 10) < 0) {
        perror("listen");
        exit(1);
    }

    printf("Listening on port 8080\n");
    while (1) {
        int client = accept(server, NULL, NULL);
        if (client < 0) {
            perror("accept");
            exit(1);
        }

        printf("client fd %d\n", client);
        char request[4096];
        ssize_t n = read(client, request, sizeof(request) - 1);
        if (n <= 0) {
            close(client);
            continue;
        }

        request[n] = '\0';
        printf("%s", request);

        char* response =
            "HTTP/1.0 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "\r\n"
            "<h1>HELLMAKIMA</h1>\n";
        write(client, response, strlen(response));
        close(client);
    }

    return 0;
}
