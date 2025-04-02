# Iterative

One step above basic client-server program. In an **iterative server**, the server calls `accept()` INSIDE a `while(1)` and handles them further. Point of iterative (or concurrent) is it lets the server receive **multiple clients** and **stay on** even if one disconnects. However, it's still not truly multi-client.

## Boilerplate

1. Basice code till `listen()`
2. Start an inifinte while loop `while(1)`
3. `accept()` into `newsock` inside the loop. This lets more clients connect.
4. Paste the logic you want to implement (simplex, half-duplex, full-duplex). This code illustrates just 1 msg exchange then disconnects.
5. Close `newsock` inside the loop. Close `sockfd` outside the loop like in basic code.

## Features

- **Single-client handling:** The server processes **one** client at a time.
- **Sequential execution:** It waits for a client, serves it, then moves to the next.
- **Blocking operations:** The server blocks (waits) on `accept()`, `recv()`, and `send()` until they complete.
- **No concurrency:** If one client is being served, others must **wait** until it finishes.

## Server Code

- `socket()`, `bind()` and `listen()` are used same as basic code.
- `accept()` is called in `while(1)` to infintely handle clients, one after the other.
- Client should be closed (`close(newsock)`) in the `while(1)` itself, as the handled client must be disconnected to accept the next client.
- Server close (`close(sockfd)`) same as basic code, outside the loop. However, its never reached. One way of closing server is Ctrl+C. Another is to break the `while(1)` on a particular client message.

## Client Code

Client is ran twice (in 2 terminals). This lets both client 1 and client 2 connect to server, but server only accepts one at a time. So client 2 will have to wait until server responds to client 1. Only then it can accept client 2.

If client 2 has sent any message before server has accepted its connection, it is queued by the OS. The moment client 2 is accepted, the message will be displayed on the server.
