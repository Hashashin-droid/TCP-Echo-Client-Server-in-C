# TCP Echo Client/Server in C

## Overview

A minimal TCP echo server and client written in C using POSIX sockets.

This project demonstrates basic client–server communication over TCP and how processes interact using socket programming.

### How it works

1. The client reads a line of text from standard input.
2. The client sends the line to the server.
3. The server receives the data and echoes it back.
4. The client receives the echoed message and prints it to standard output.

---

## TCP Echo Server — `main` Function Flow

1. Create a TCP socket using `socket()`.
2. Configure a `sockaddr_in` structure with IP address and port.
3. Bind the socket to the address using `bind()`.
4. Put the socket into listening mode with `listen()`.
5. Accept incoming client connections with `accept()`.
6. Fork a child process to handle each client.
7. Receive client data using `recv()`.
8. Echo the data back using `send()`.

---

## TCP Echo Server - `handle_client` Function Flow

This function runs inside the child process created by `fork()` and is responsible for handling communication with a connected client.

1. Wait for incoming buffer from client using `recv()`
2. If buffer is received, immediately echoes it back using `send()`
3. Repeats until the client disconnects

---

## TCP Echo Client — `main` Function Flow

1. Create a TCP socket using `socket()`.
2. Configure server address information.
3. Connect to the server using `connect()`.
4. Read user input from standard input.
5. Send the data to the server using `send()`.
6. Receive echoed data using `recv()`.
7. Display the response.

---

## TCP Echo Client - `message` Function Flow

This function manages the client interaction with the server.

1. Read user input from standard input (stdin) using `fgets()`.
2. Send the typed message to the server using `send()`.
3. Wait for the server’s echoed reply using `recv()`.
4. Print the received message to standard output.
5. Repeat until input ends or the server disconnects.

## Compile

```bash
gcc server.c -o server
gcc client.c -o client
```

---

## Run

Start the server:

```bash
./server
```

In another terminal, run the client:

```bash
./client
```

Type messages in the client terminal to see them echoed back.

---

## Learning Goals

* TCP socket programming fundamentals
* Client–server communication model
* Process handling with `fork()`
* Blocking I/O behavior
* Error handling in network applications

---

## Notes

* Designed for Linux/Unix environments.
* Uses blocking sockets for simplicity.
* Educational example — not production hardened.

---

## Author

Ikhwan Khairudin

