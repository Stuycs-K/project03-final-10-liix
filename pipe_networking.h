#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#ifndef pipe_networking_h
#define NETWORKING_H
#define WKP "non"
int rand();
int server_setup();
int server_side_authentication(char *to_client);
int client_side_authentication(char *to_server);
int server_connect(int from_client);

 #define pipe_size 256
#endif