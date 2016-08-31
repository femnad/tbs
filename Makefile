CC=clang

CFLAGS=-Wall

all: tbs_client tbs_server

tbs_client: tbs_client.c
	$(CC) $(CFLAGS) tbs_client.c cave_string.c -o tbs_client -l zmq

tbs_server: tbs_server.c
	$(CC) $(CFLAGS) tbs_server.c cave_string.c -o tbs_server -l zmq

clean:
	rm -f tbs_client
	rm -f tbs_server
