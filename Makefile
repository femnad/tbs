all: tbs_client tbs_server

tbs_client: tbs_client.c
	clang tbs_client.c -o tbs_client -l zmq

tbs_server: tbs_server.c
	clang tbs_server.c -o tbs_server -l zmq

clean:
	rm -f tbs_client
	rm -f tbs_server
