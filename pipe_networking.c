#include "pipe_networking.h"

int rand(){ // generates random int
  int buff[1];
  int random = open("/dev/urandom", O_RDONLY, 0);
  read(random,buff,4);
  close(random);
  if(buff[0] < 0){
    buff[0] *= -1;
  }
  return *buff;
}


//Setup:
//Creates a WKP and waits for a connnection and removes WKP when connection is made
//Returns file descriptor for the upstream pipe WKP

int server_setup() {
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
//Returns upstream pipe)
int server_side_authentication(int *to_client) {
    int SYN = server_setup();
    char private_pipe[pipe_size];
    if(read(SYN, private_pipe, sizeof(private_pipe)) == -1) {
        perror("Failed to read from private_pipe");
    }

    int SYN_ACK = open(private_pipe, O_WRONLY);
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

////Performs the serverside part of the 3-way handshake when esablishing connection with client.
//Returns SYN_ACK 
int client_side_authentication(int *to_server) {
    char private_pipe[pipe_size];
    mkfifo(private_pipe, 0666);

    //Sends private_pipe descriptor to server 
    int SYN = open(WKP, O_WRONLY);
    write(SYN, private_pipe, strlen(private_pipe) + 1);

    //Gets the SYN_ACK from the server through the private_pipe
    int SYN_ACK = open(private_pipe, O_RDONLY);
    remove(private_pipe);
    char message[256];
    read(SYN_ACK, message, sizeof(message));
    printf(message);

    //Sends ACK back
    char ACK[sizeof(message)];
    write(SYN, message, strlen(message) + 1);
    *to_server = SYN;
    return SYN_ACK;
}

int server_connect(int from_client) {
    int to_client = 0;
    return to_client;
}