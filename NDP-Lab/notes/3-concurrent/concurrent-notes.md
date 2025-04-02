# Concurrent Servers

## fork() vs pthreads

| **Feature**                | **`fork()` (Processes)**                       | **Threads**                            |
|----------------------------|-----------------------------------------------|----------------------------------------|
| **Memory Sharing**         | Each child process has **independent** memory. | All threads **share** the same memory. |
| **Data Isolation**         | Changes in one process do **not** affect others. | Changes in one thread **affect** others. |
| **Performance**            | **Slower** due to copying process memory.      | **Faster** since memory is shared.     |
| **Resource Usage**         | **More** memory due to separate address spaces. | **Less** memory as threads share resources. |
| **Communication**          | Requires **Inter-Process Communication (IPC)** (e.g., pipes, shared memory). | Use **global variables** or shared memory directly. |
| **Failure Isolation**      | **Safer**—a crash in one process does **not** affect others. | **Riskier**—a crash in one thread can **crash** the entire program. |
| **Complexity**             | **Simpler** for independent tasks.             | **More complex** due to synchronization (e.g., mutexes). |
| **Concurrency Handling**   | Each client is handled by a **separate** process. | Each client is handled by a **separate** thread. |
| **Scalability**            | **Less scalable** due to higher overhead.      | **Highly scalable**—easier to manage many clients. |
| **Security**               | **More secure**—clients cannot access each other's data. | **Less secure**—threads share the same address space. |
| **Overhead**               | **Higher**—each `fork()` call duplicates the process. | **Lower**—threads are created faster and use less memory. |
| **Use Case**               | Suitable for **independent** client requests (e.g., simple HTTP servers). | Suitable for **shared-state** applications (e.g., chatrooms, auctions). |

## Boilerplate

1. Basice code till `listen()`
2. Start an inifinte while loop `while(1)`
3. `accept()` into `newsock` inside the loop. This lets more clients connect **(same as iterative till here).**
4. `fork()` to create a child process which handles the client. Parent listens for more clients.
4. Paste the logic you want to implement (simplex, half-duplex, full-duplex) **in the client**. This code illustrates just 1 msg exchange then disconnects.
6. Close `sockfd` outside the loop, like in basic code.

## Features

- **Multi-client handling:** The server processes multiple clients simultaneously.
- **Parallel execution:** Each client connection is handled in a separate child process.
- **Non-blocking** The server continues listening for new connections while handling existing ones.
- **Concurrency:** Multiple clients can be served at the same time using fork().

## Server Code

- `socket()`, `bind()` and `listen()` are used same as basic code.
- `accept()` is called in `while(1)` to infintely handle clients, one after the other.
- `fork()` to create 2 processes (parent and child). This allows parallel execution where child handles client, parent listens for new clients.
- In child (pid = 0), first close `sockfd`. Then implement recv/send for 1 msg. After exchange, close `newsock` too.
- In parent (pid > 0), close `newsock` that's it.

## Client

Same as iterative, sends/receives single msg.
