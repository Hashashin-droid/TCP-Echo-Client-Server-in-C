#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void message(FILE *fp, int sockfd) {

    char send_buf[1024], recv_buf[1024];
    while (fgets(send_buf, sizeof(send_buf), fp) != NULL) {
        send(sockfd, send_buf, strlen(send_buf), 0);
        int n = recv(sockfd, recv_buf, sizeof(recv_buf) - 1, 0);
        if (n == 0) {
            printf("server disconnected\n");
            return;
        }
        recv_buf[n] = '\0';
        fputs(recv_buf, stdout);
    }
}

int main() {
    int client_fd;
    struct sockaddr_in serv_addr = {0};

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }else {
        printf("Connected to the server...\n");
    }
    message(stdin, client_fd);
}
