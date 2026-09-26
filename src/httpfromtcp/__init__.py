import socket
def get_lines_from_channel(f):
    r = ""
    while a := f.recv(8):
        r += a.decode("utf-8")
    return r.split('\n')

def main() -> None:

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("127.0.0.1", 8080))
    server.listen()

    conn, _addr = server.accept()
    lines = get_lines_from_channel(conn)
    for i in lines:
        print(f"read: {i}")
    conn.close()
    server.close()

