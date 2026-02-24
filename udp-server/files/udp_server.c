#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    socklen_t client_len = sizeof(client_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        return EXIT_FAILURE;
    }

    printf("UDP Server listening on port %d\n", PORT);

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        int activity = select(sockfd + 1, &readfds, NULL, NULL, NULL);

        if (activity < 0 && errno != EINTR) {
            perror("select error");
            break;
        }

        if (FD_ISSET(sockfd, &readfds)) {
            int len = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                               (struct sockaddr*)&client_addr, &client_len);

            if (len > 0) {
                buffer[len] = '\0';
                printf("Received: %s\n", buffer);

                sendto(sockfd, buffer, len, 0,
                       (struct sockaddr*)&client_addr, client_len);
            }
        }
    }

    close(sockfd);
    return EXIT_SUCCESS;
}