import socket

# or do `nc -v localhost 8080`

with socket.create_connection(("127.0.0.1", 8080)) as sock:
    with open('text.txt', 'r') as f:
        sock.sendall(f.read().encode())

