import json
from email.header import Header
from collections import defaultdict
from dataclasses import dataclass, asdict
import socket

def get_lines_from_channel(f):
    r = ""
    while a := f.recv(8):
        r += a.decode("utf-8")
    return r

def main() -> None:

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("127.0.0.1", 8080))
    server.listen()

    conn, _addr = server.accept()
    req = get_lines_from_channel(conn)
    request = request_from_reader(req)
    print(json.dumps(asdict(request), indent=2))
    conn.close()
    server.close()

@dataclass
class RequestLine:
    http_version: str
    request_target: str
    method: str

@dataclass
class HTTPReqest:
    request_line: RequestLine
    headers: defaultdict
    body: str # supposed to be bytes

def request_from_reader(req: str):

    lines = req.split('\r\n')
    request_line = lines[0].split()
    if len(request_line) != 3:
        raise ValueError(f"Malformed request_line: {request_line}")
    if request_line[0] not in ["GET", "POST"]:
        raise ValueError(f"Sorry mate only GET or POST no {request_line[0]}")
    if request_line[2] != "HTTP/1.1":
        raise ValueError(f"We only support HTTP/1.1 not {request_line[2]}")
    parts = req.split('\r\n\r\n')
    if len(parts) != 2:
        raise ValueError(f"malformed request, no header separation \\r\\n\\r\\n")
    headers = parts[0].split('\r\n')[1:]
    headers_dict = defaultdict()
    for header in headers:
        try:
            i = header.index(':')
        except ValueError:
            raise ValueError(f"malformed header {header}")
        key = header[:i]
        value = header[i+1:].strip()
        headers_dict[key] = value
    return HTTPReqest(
            request_line=RequestLine(
                method=request_line[0],
                request_target=request_line[1],
                http_version=request_line[2]
            ),
            headers=headers_dict,
            body=parts[1]
        )

def test():
    a = request_from_reader("GET / HTTP/1.1\r\nHost: localhost:42069\r\nUser-Agent: curl/7.81.0\r\nAccept: */*\r\n\r\n")
    print(asdict(a))
