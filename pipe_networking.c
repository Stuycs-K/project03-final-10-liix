#include "pipe_networking.h"

//Setup:
//Creates a WKP and waits for a connnection and removes WKP when connection is made
//Returns file descriptor for the upstream pipe WKP

int server_setup() {
    char * WKP;
    int SYN = 0;
    if (mkfifo(WKP, 0666) == -1) {
        perror("Could not create WKP");
    }
    printf("WKP created. Waiting for client connection...\n");

    if(SYN = open(WKP, O_RDONLY) == -1) {
        perror("Could not open WKP for reading");
        remove(WKP);
        exit(1);
    }

    printf("Client connected. Removing WKP...\n");
    remove("non");
    return SYN;
}


void send_file_to_server(char *file_path);
void receive_feedback_from_server();
void handle_file_transfer(int pipe_fd, char *file_path);
void process_client_request(int wkp_fd);
