from io import TextIOWrapper
import socket
def get_lines_from_channel(f: TextIOWrapper) -> list[str]:
    r = []
    s = ""
    while a := f.read(8):
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
    with open("text.txt", "r") as f:
        lines = get_lines_from_channel(f)
        for i in lines:
            print(f"read: {i}")

