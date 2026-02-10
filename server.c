#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>

void handle_client(int sockfd) {
    ssize_t bytes;
    char recv_buf[1024];

    again:
        while ((bytes = recv(sockfd, recv_buf, sizeof(recv_buf) - 1, 0)) > 0) {
            send(sockfd, recv_buf, bytes, 0);
        }
    if (bytes < 0 && errno == EINTR) {
        goto again;
    }
    else if (bytes < 0) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

}

int main() {

    int client_fd, server_fd;
    struct sockaddr_in cli_addr, serv_addr = {0};
    pid_t pid;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while (1) {
        socklen_t cli_len = sizeof(cli_addr);
        if ((client_fd = accept(server_fd, (struct sockaddr *)&cli_addr, &cli_len)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == 0) {
            close(server_fd);
            handle_client(client_fd);
            exit(0);
        }
        close(client_fd);
    }
}
