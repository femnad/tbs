all: tbs_client.c tbs_server.c

client: tbs_client.c
	clang tbs_client.c -o tbs_client -l zmq

server: tbs_server.c
	clang tbs_server.c -o tbs_server -l zmq
