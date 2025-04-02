# Full Duplex

Full Duplex can be implemented in socket programming by using either `pthreads` (new thread) or `fork()` (new process).  
Usually, **threads** are recommended for full-duplex chat apps because they allow easy message handling with shared resources. But here we are implementing it using `fork()`.

## How it works

- **Parent process:** Handles sending messages to the client.
- **Child process:** Handles receiving messages from the client.

## Buffers

Use two buffers for full-duplex communication to prevent interference between sending and receiving processes.

Benefits:

- No Data Collision: Separate buffers prevent overwriting.

- Better Clarity: Each process manages its own buffer.

- Scalability: Easier to expand the logic (e.g., adding message queues).

## Server

Same as basic till `accept()`. Then `fork()` to create child and parent.

In the **Child** Process:

- Close `sockfd` immediately.
- The child only needs `newsock` (client connection), not the original listening socket.
- If we don't close `sockfd` in the child:
  - It will remain open, leading to resource leaks.
  - The server might have too many open sockets if many clients connect.
- Create a buffer to recv messages.
- Start a `while(1)` loop to infinitely receive and display the message.
- Outside the while (when client leaves), close `newsock` and `exit(0)` to terminate child.

In the **Parent** Process:

- Keep `sockfd` open to continue accepting clients (or manage the connection if only one client). Here we arent dealing w multi clients so keep it open for managing.
- Create a new buffer to send messages.
- Start a `while(1)` loop to infinitely send and display the message.
- Outside the while, close `newsock`.

## Child

Connection setup same as basic.  
Full-duplex logic same as server.

This will be same for other full duplex too (iterative/concurrent).
