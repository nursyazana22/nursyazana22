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
        std::cerr << "Failed to connect to the server" << std::endl;
        return 1;
    }
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;

    std::string numberString = std::to_string(number);

    if (send(clientSocket, numberString.c_str(), numberString.length(), 0) == -1) {
        std::cerr << "Failed to send data to the server" << std::endl;
        return 1;
    }
    char resultBuffer[256];
    memset(resultBuffer, 0, sizeof(resultBuffer));
    ssize_t bytesRead = recv(clientSocket, resultBuffer, sizeof(resultBuffer) - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive data from the server" << std::endl;
        return 1;
    }

    std::cout << "Result from server: " << resultBuffer << std::endl;

    close(clientSocket);

    return 0;
}

