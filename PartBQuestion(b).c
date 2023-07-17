import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 8596)

client_socket.connect(server_address)

number_bytes = client_socket.recv(1024)

random_number = int(number_bytes.decode('utf-8'))

print('Received random number:', random_number)

client_socket.close()
