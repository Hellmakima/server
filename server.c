# include <sys/socket.h>
# include <stdio.h>
# include <stdlib.h>

int main (void){
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("Socket error");
        exit(1);
    }
    printf("socket fd %d\n", server);

    return 0;
}
