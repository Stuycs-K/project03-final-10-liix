#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#ifndef pipe_networking_h

void setup();
void send_file_to_server(char *file_path);
void receive_feedback_from_server();
void handle_file_transfer(int pipe_fd, char *file_path);
void process_client_request(int wkp_fd);

#endif