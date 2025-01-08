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

//Performs the serverside part of the 3-way handshake when esablishing connection with client.
//Returns SYN_ACK (Will prompt users for an input)
char * server_side_authentication(char *to_client) {
    int SYN = server_setup();
    char private_pipe1[pipe_size];
    read(SYN, private_pipe1, sizeof(private_pipe1));
    int SYN_ACK = open(private_pipe1, O_WRONLY);
    char message[256];
    strcpy(message, "Testing");
    write(SYN_ACK, message, strlen(message) + 1);
    printf("SYN_ACK being sent to client");
    char from_server[256];
    read(SYN, from_server, sizeof(from_server));
    if(strcmp(message, from_server)) {
        printf("Success\n");
    } else {
        printf("Server failed to send");
    }
    printf("SYN_ACK recieved through WKP");
    *to_client = from_server;
    return to_client;
}

char * client_side_authentication(char *to_server) {
    
}
void send_file_to_server(char *file_path);
void receive_feedback_from_server();
void handle_file_transfer(int pipe_fd, char *file_path);
void process_client_request(int wkp_fd);
