#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>

#define BUFFER_SIZE 256
#define CONNECT_PROTOCOL "tcp"
#define SLEEP_PERIOD 5

int main(int argc, char *argv []) {
    if (argc != 3) {
        printf("Usage: tbs_client <host> <port>\n");
        exit(1);
    }
    char *host = argv[1];
    char *port = argv[2];
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    char connect_address[BUFFER_SIZE];
    int address_length = sprintf(connect_address, "%s://%s:%s",
                                 CONNECT_PROTOCOL, host, port);
    connect_address[address_length] = '\0';
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
        buffer[recv_length] = '\0';
        char command[BUFFER_SIZE];
        int command_length = sprintf(command, "tmux set-buffer '%s'", buffer);
        command[command_length] = '\0';
        system(command);
        sleep(SLEEP_PERIOD);
    }
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
}
