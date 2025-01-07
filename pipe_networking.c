#include "pipe_networking.h"

//Setup:
//Creates a WKP and removes when done
void setup();
void send_file_to_server(char *file_path);
void receive_feedback_from_server();
void handle_file_transfer(int pipe_fd, char *file_path);
void process_client_request(int wkp_fd);
