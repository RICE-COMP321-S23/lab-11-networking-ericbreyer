# Exercises

## Client

This exercise builds on the information in Section 3 of the lab page. You may
want to refer back to that section as you work on this exercise.

### Client Exercise #1

Complete the implementation of the `open_client()` function in the supplied
source file [echoclient.c](echoclient.c).

The file `echoserver-sol` provided in your repository is a complete executable
program of an echo server that is compatible with the way that your echo client
should work (and similarly, the file `echoclient-sol` provided in your
repository is a complete executable program of an echo client). To test your own
echo client, you should first start the provided echo server running with the
command:

```
./echoserver-sol port &
```

where *port* is some unique integer between 1024 and 65,535, inclusive. (All
port numbers less than 1024 are reserved for well-known services.) If you pick a
port that is already in use, you will get the following error message:

```
open_listen error: Address already in use
```

In that case, you should pick a different port number and try starting
`echoserver-sol` again.  Once the provided echo server solution,
`echoserver-sol`, is running, you should connect to it with your own echo client
by running the command:

```
./echoclient hostname port
```

where *hostname* is the hostname of the specific CLEAR server that you are
logged on to, and *port* is the same port number that you used in starting the
echo server. If you don't know the name of the specific CLEAR server you are
logged on to, it can be found by running the command

```
uname -n
```

**IMPORTANT:** When you are done testing your echo client, be sure to stop the
execution of the echo server that you started above. This can be done either
with the `kill` command or with a combination of the `fg` command and typing
control-C.

## Server

This exercise builds on the information in Section 4 of the lab page. You may
want to refer back to that section as you work on this exercise.

### Server Exercise #1

Complete the implementation of the `open_listen()` and `main()` functions in the
supplied source file [echoserver.c](echoserver.c).

To test your work, you should first run your echo server with the command:

```
./echoserver port &
```

The argument *port* should be the unique port number you want to use for this
server, as described above for Client Exercise #1. Once the echo server is
running, you need to connect to it with your echo client by running the command:

```
./echoclient hostname port
```

The argument *hostname* should be the name of the specific CLEAR server that you
are logged on to, and *port* should be the same port number as you used for the
server, above. Again, if you don't know the name of the specific CLEAR server
you are logged on to, you can find it by running the command

```
uname -n
```

**IMPORTANT:** Again, when you are done with this testing, be sure to stop the
execution of the echo server that you started above. This can be done either
with the `kill` command or with a combination of the `fg` command and typing
control-C.

## Concurrency

This exercise builds on the information in Section 5 of the lab page. You may
want to refer back to that section as you work on this exercise.

### Concurrent Server Exercise #1

Modify your echo server to utilize *process concurrency* using the
fork-after-accept technique. The new child process should handle the actual echo
task, whereas the parent should continue to accept new connections.

Make sure that the accepting process (the main server) reaps its children to
prevent zombie processes from accumulating and consuming host resources.

Make sure you close sockets in the right places. In particular, note that the
file descriptor for each accepted connection needs to be closed in two places!
Why?

To test your work, connect to your server with multiple clients at the same time
and ensure that they all work.

**IMPORTANT:** Once again, when you are done with this testing, be sure to stop
the execution of the echo server that you started above. This can be done either
with the `kill` command or with a combination of the `fg` command and typing
control-C.
