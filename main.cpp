#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    std::string targetIP;
    int startPort, endPort;

    std::cout << "Введіть IP-адресу або хост: ";
    std::cin >> targetIP;
    std::cout << "Введіть початковий порт: ";
    std::cin >> startPort;
    std::cout << "Введіть кінцевий порт: ";
    std::cin >> endPort;

    for (int port = startPort; port <= endPort; port++) {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            std::cerr << "Помилка створення сокета" << std::endl;
            return 1;
        }

        sockaddr_in targetAddr;
        targetAddr.sin_family = AF_INET;
        targetAddr.sin_port = htons(port);
        inet_pton(AF_INET, targetIP.c_str(), &(targetAddr.sin_addr));

        if (connect(sockfd, (struct sockaddr *)&targetAddr, sizeof(targetAddr)) == 0) {
            std::cout << "Порт " << port << " відкритий." << std::endl;
            close(sockfd);
        } else {
            // Якщо connect() повернула помилку, то порт закритий або недоступний.
            close(sockfd);
        }
    }

    return 0;
}

