#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
bool isPrime(int number) {
    if (number < 2) {
        return false;
    }
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(12345);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        return 1;
    }
    if (listen(serverSocket, 1) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 12345" << std::endl;

    while (true) {
        sockaddr_in clientAddress{};
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
        if (clientSocket == -1) {
            std::cerr << "Failed to accept client connection" << std::endl;
            continue;
        }

        std::cout << "Received connection from client" << std::endl;
        char numberBuffer[256];
        memset(numberBuffer, 0, sizeof(numberBuffer));
        ssize_t bytesRead = recv(clientSocket, numberBuffer, sizeof(numberBuffer) - 1, 0);
        if (bytesRead == -1) {
            std::cerr << "Failed to receive data from the client" << std::endl;
            close(clientSocket);
            continue;
        }
        int number = std::stoi(numberBuffer);
      bool isPrimeNumber = isPrime(number);

        std::string response = isPrimeNumber ? "Prime" : "Not Prime";
        if (send(clientSocket, response.c_str(), response.length(), 0) == -1) {
            std::cerr << "Failed to send data to the client" << std::endl;
        }

        close(clientSocket);
    }

    close(serverSocket);

    return 0;
}
