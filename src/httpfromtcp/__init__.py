from dataclasses import dataclass
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
@dataclass
class Header:
    method: str
    destination: str
    version: str

@dataclass
class HTTPReqest:
    header: Header
    fields: dict = {}

def parse(req: str):
    req_lines = req.split('\r\n')
    start_line = req_lines[0].split()
    assert len(start_line) == 3

    start_line[2] == "HTTP/1.1"
