
all: client server
client: client.o pipe_networking.o
  gcc -o client basic_client.o pipe_networking.o

server: server.o pipe_networking.o
	gcc -o server basic_server.o pipe_networking.o

client.o: client.c pipe_networking.h
	gcc -c client.c

server.o: server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

file_handling.o: file_handling.c file_handling.h pipe_networking.h
	gcc -c file_handling.c

clean:
	rm *.o
	rm *~
