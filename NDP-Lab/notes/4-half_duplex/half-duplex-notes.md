# Half Duplex

Turn-based message exchange where only one side communicates at a time, while the other waits.

## How to achieve?

- Socket setup will be same as basic.
- **Receiving** and **Sending** messages will be in a `while(1)` for infinite conversation.
- Client socket will be closed **OUTSIDE** of `while(1)` (unlike iterative server). This is coz the connection has to be infinite, not single message exchange and close.
- Server socket closes same as basic.

## Iterative/Concurrent?

Half-duplex can be done in both iterative and concurrent. You just have to paste the logic into the iterative/concurrent boilerplate.

## Server and Client

New function we are using is `memset(buffer, 0, sizeof(buffer))`.

When messages are sent/received **multiple** times (in a loop), `memset()` MUST be used before **storing** (receiving) data in buffers. This is because:

- Older data might persist in buffer from previous message exchange.
- `recv()` does not automatically add `\0` at the end.

However in case of **sending** messages, `memset()` is not necessary bcoz:

- Even if there are leftover characters in buffer, `strlen(buffer)` ensures that only the meaningful portion is sent.
- `fgets()` takes care of inserting the input properly and terminates it with `\0`.
