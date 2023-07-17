import socket
import random

def main():

  client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  client_socket.connect(("localhost", 8080))

  random_number = random.randint(1, 100)

  client_socket.sendall(str(random_number).encode("utf-8")
  
  received_random_number = client_socket.recv(1024).decode("utf-8")

  print("The random number is:", received_random_number)

if __name__ == "__main__":
  main()
