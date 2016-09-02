#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>

#include "cave_string.h"

#define BUFFER_LENGTH 256
#define BIND_ADDRESS "*"
#define BIND_PORT 9753
#define BIND_PROTOCOL "tcp"
#define FIFO_NAME "/tmp/tbs"
#define SLEEP_PERIOD 1

int main(int argc, char *argv []) {
    mkfifo(FIFO_NAME, S_IRUSR | S_IWUSR);
    void *context = zmq_ctx_new();
    char *bind_address = cave_get_string("%s://%s:%d", BIND_PROTOCOL,
                                         BIND_ADDRESS, BIND_PORT);
    void *publisher = zmq_socket(context, ZMQ_PUB);
    int rc = zmq_bind(publisher, bind_address);
    if (rc != 0) {
        perror("Bind error");
        exit(1);
    }
    int fifo_fd;
    char buffer[BUFFER_LENGTH];
    while (1) {
        fifo_fd = open(FIFO_NAME, O_RDONLY);
        if (fifo_fd == -1) {
            perror("Error opening fifo");
            exit(2);
        }
        read(fifo_fd, buffer, BUFFER_LENGTH);
        zmq_send(publisher, buffer, strlen(buffer), 0);
        close(fifo_fd);
        sleep(SLEEP_PERIOD);
    }
    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}
