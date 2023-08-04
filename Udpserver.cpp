#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    struct sockaddr_in server_addr, client_addr;
    int sockfd, addr_len, received_bytes;
    char buffer[BUFFER_SIZE];

    // 소켓 생성
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 소켓에 주소 바인딩
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in binding");
        exit(EXIT_FAILURE);
    }

    std::cout << "UDP server listening on port " << PORT << "...\n";

    while (1) {
        addr_len = sizeof(client_addr);

        // 클라이언트로부터 데이터 수신
        received_bytes = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len);

        // 수신된 데이터 출력
        buffer[received_bytes] = '\0';
        std::cout << "Received from client: " << buffer << std::endl;

        // 클라이언트로 응답 전송 (echo)
        sendto(sockfd, buffer, received_bytes, 0, (const struct sockaddr *)&client_addr, addr_len);
    }

    close(sockfd);
    return 0;
}


