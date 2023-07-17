#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

int main() {

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Invalid address or address not supported" << std::endl;
        return 1;
    }

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to connect " << std::endl;
        return 1;
    }
    char numberBuffer[256];
    memset(numberBuffer, 0, sizeof(numberBuffer));
    ssize_t bytesRead = recv(clientSocket, numberBuffer, sizeof(numberBuffer) - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive data" << std::endl;
        return 1;
    }

    std::cout << "Random number: " << numberBuffer << std::endl;

    // Close the socket
    close(clientSocket);

    return 0;
}
