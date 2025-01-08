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
    if(read(SYN, private_pipe1, sizeof(private_pipe1)) == -1) {
        perror("Failed to read from private_pipe");
    }

    int SYN_ACK = open(private_pipe1, O_WRONLY);
    if(SYN_ACK == -1) {
        perror("Failed to open private_pipe for writing");
    }

    char message[256];
    strcpy(message, "Testing");
    if(write(SYN_ACK, message, strlen(message) + 1) == -1) {
        perror("Failed to write into private_pipe");
    }
    printf("SYN_ACK being sent to client");

    char to_server[256];
    if(read(SYN, to_server, sizeof(to_server)) == -1) {
        perror("Failed to read the upstream message from client");
    }
    if(strcmp(message, to_server)) {
        printf("Success\n");
    } else {
        printf("Server failed to receive ACK");
    }
    printf("ACK recieved through WKP");
    *to_client = SYN_ACK;
    return SYN;
}

char * client_side_authentication(char *to_server) {

}
void send_file_to_server(char *file_path);
void receive_feedback_from_server();
void handle_file_transfer(int pipe_fd, char *file_path);
void process_client_request(int wkp_fd);
