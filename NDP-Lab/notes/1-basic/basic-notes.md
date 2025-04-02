# Basics

Simple Client-Server program where they exchange one message each and close connections.

## Server Code

1. `socket()` / `accept()` vs. `bind()` / `listen()`

Both `socket()` and `accept()` return file descriptors (integers), which are used in `bind()`/`listen()` and communicating w connected client respectively. That's why we store them in a variable.

`bind()` and `listen()` dont return file descriptors, only 0 or -1 indicating success or failure respectively. So, no need to store them in a variable, just call them.

2. `sizeof(address)` in bind() but `(socklen_t*)&addrlen` in accept()

`bind()` takes the actual size of the `struct sockaddr_in address` as an argument, while `sizeof(address)` directly gives the size of the `struct sockaddr_in structure`.

`accept()` fills in the address structure with details of the connected client. When a client connects, the server doesn’t always know the exact address format (it could be IPv4, IPv6, etc.). This is why we pass `&addrlen`, so `accept()` can change it.

3. Address Structure

**Server** must bind to an address and port so that it can listen for incoming connections. The **client** does not bind to a specific IP; instead, it connects to a server. Hence, the client fills address with server details while server can fill it however.

4. Why Two Sockets?

The server needs two sockets:

**Listening socket** (sockfd) → Waits for connections  
**Connected socket** (newsock) → Communicates with a specific client

`socket()` creates `sockfd` which only listens for new connections. It doesnt exchange any data.  
When a client connects, `accept()` returns a `newsock` which does the data exchange, while `sockfd` keeps listening for new clients. This allows multiple clients to connect simultaneously.

5. Why 2 `struct sockaddr_in`?

We can use just `address` for `accept()` instead of a separate `client_addr`, but it's better to use a new `client_addr` coz:

- Avoids overwriting server's address. Otherwise calling `accept()`  holds the client address instead of server.
- Clarity, leading to easier understanding and debugging.
- Best practice in real world.

## Client Code

1. Why only 1 Socket?

Clients only need **one** socket, `sockfd`, to connect to a server and exchange data.

2. Address Structure

Must be set for the server's address as client needs to connect to server for communication.

3. `inet_pton()` for `serv_addr.sin_addr` instead of `inet_addr()`

`inet_pton` is **recommended** as it supports both IPv4 and IPv6. `inet_addr` does not support IPv6 and is considered **obsolete** in modern systems.

4. Avoiding garbage value in buffer

Initialize buffer to {0} or else we may get garbage values. Use `char buffer[1024] = {0};`.
