#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#ifndef pipe_networking_h
#define pip_networking_h
#define WKP "non"
char private_pipe[256];
int running = 1;
struct Student {
    char name[100];
    char date_of_birth[20];
    char year[10];
    char major[100];
};

int rand();
int server_setup();
int server_side_authentication(int *to_client);
int client_side_authentication(int *to_server);
int server_connect(int from_client);

 #define pipe_size 256
#endif