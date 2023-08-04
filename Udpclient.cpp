#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main() {
    struct sockaddr_in server_addr;
    int sockfd, addr_len;
    char buffer[BUFFER_SIZE];

    // 소켓 생성
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    while (1) {
        std::cout << "Enter message to send to server (or 'exit' to quit): ";
        std::cin.getline(buffer, BUFFER_SIZE);

        // 'exit'를 입력하면 클라이언트 종료
        if (strcmp(buffer, "exit") == 0)
            break;

        addr_len = sizeof(server_addr);

        // 서버로 데이터 전송
        sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, addr_len);

        // 서버로부터 응답 수신
        int received_bytes = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
        buffer[received_bytes] = '\0';
        std::cout << "Received from server: " << buffer << std::endl;
    }

    close(sockfd);
    return 0;
}
