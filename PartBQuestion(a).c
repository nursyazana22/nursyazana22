#include <iostream>
#include <random>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

MIN_NUMBER = 50000
MAX_NUMBER = 80000

    int main () {
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 12345)
server_socket.bind(server_address)

server_socket.listen(1)
print('Server is listening on {}:{}'.format(*server_address))

def handle_client(client_socket):
    random_number = random.randint(MIN_NUMBER, MAX_NUMBER)

    number_bytes = str(random_number).encode('utf-8')

    client_socket.sendall(number_bytes)


    client_socket.close()


def start_server():
    while True:
      
        client_socket, client_address = server_socket.accept()
        print('Received connection from {}:{}'.format(*client_address))

  
        client_thread = threading.Thread(target=handle_client, args=(client_socket,))
        client_thread.start()
    
    return 0
    }

start_server()
