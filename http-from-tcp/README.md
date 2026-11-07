# HTTP from TCP

_This is based on the [TCP from HTTP](https://www.boot.dev/lessons/83e169b2-51ce-4fa8-96a0-031505e1008e) lesson and [video](https://youtu.be/FknTw9bJsXM?si=wBy37icexWwvlCC5)._

run the program `uv run http`
on another pane, `nc -v localhost 8080`
and type things and see them appear on the other side.
> [!NOTE]
> `nc` sends data as you type it.
 Pressing **Enter** typically causes the line to be sent.
 TCP may deliver that data to your server in different-sized chunks.
 Your `recv(8)` controls how much your program reads at a time.

---

Also u can try http via `curl localhost:8080` and see all it fancy headers
`curl -I --http2 localhost:8080`
`curl -X POST http://localhost:8080 \
  -H "Content-Type: application/json" \
  -d '{"name":"Alice","age":25}'
`
---

I'll be skipping the `stream` and `bytes` part of this project.
