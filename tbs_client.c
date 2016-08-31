#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>

#include "cave_string.h"

#define BUFFER_SIZE 256
#define CONNECT_PROTOCOL "tcp"
#define TMUX_SET_BUFFER_COMMAND "tmux set-buffer \"%s\""

int main(int argc, char *argv []) {
    if (argc != 3) {
        printf("Usage: tbs_client <host> <port>\n");
        exit(1);
    }
    char *host = argv[1];
    char *port = argv[2];
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    char *connect_address = cave_get_string("%s://%s:%s", CONNECT_PROTOCOL,
                                            host, port);
    int rc = zmq_connect(subscriber, connect_address);
    if (rc != 0) {
        perror("Connect error");
    }
    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);
    if (rc != 0) {
        perror("Socket option error");
    }
    char buffer[BUFFER_SIZE];
    while (1) {
        int recv_length = zmq_recv(subscriber, buffer, BUFFER_SIZE, 0);
        char *received_buffer = cave_truncate_string(buffer, recv_length);
        char *command = cave_get_string(TMUX_SET_BUFFER_COMMAND,
                                        received_buffer);
        system(command);
    }
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
}
