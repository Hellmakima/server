from io import TextIOWrapper
import socket
def get_lines_from_channel(f) -> list[str]:
    r = []
    s = ""
    while a := f.recv(8):
        a = a.decode("utf-8")
        if not a:
            break
        if '\n' in a:
            a = a.split('\n')
            s += a[0]
            r.append(s)
            s = a[1]
        else:
            s += a
    return r


def main() -> None:
    # with open("text.txt", "r") as f:
    #     lines = get_lines_from_channel(f)
    #     for i in lines:
    #         print(f"read: {i}")

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("127.0.0.1", 8080))
    server.listen()

    conn, addr = server.accept()
    lines = get_lines_from_channel(conn)
    for i in lines:
        print(f"read: {i}")
    conn.close()
    server.close()

