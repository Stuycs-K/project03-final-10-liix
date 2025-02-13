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
    remove(WKP);
    if (mkfifo(WKP, 0666) == -1) {
        perror("Could not create WKP");
    }
    printf("WKP created. Waiting for client connection...\n");

    if((SYN = open(WKP, O_RDONLY)) == -1) {
        perror("Could not open WKP for reading");
        remove(WKP);
        exit(1);
    }
    printf("Server: Client connected and sent private pipe name.\n");
    return SYN;
}

//Performs the serverside part of the 3-way handshake when establishing connection with client.
//Returns upstream pipe)
int server_side_authentication(int *to_client) {
    int SYN = server_setup();
    char client_pipe[pipe_size];
    if(read(SYN, client_pipe, sizeof(client_pipe)) == -1) {
        perror("Failed to read from WKP");
    }

    int SYN_ACK = open(client_pipe, O_WRONLY);
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
    if(strcmp(message, to_server) == 0) {
        printf("Success\n");
    } else {
        printf("Server failed to receive ACK");
    }
    printf("ACK recieved through WKP");
    *to_client = SYN_ACK;
    return SYN;
}

////Performs the clientside part of the 3-way handshake when establishing connection with server.
//Returns SYN_ACK 
void client_side_authentication(int *to_server) {
    mkfifo(private_pipe, 0666);
    printf("trying to run");
    //Sends private_pipe descriptor to server 
    int SYN = open(WKP, O_WRONLY);
    if(SYN == -1) {
        perror("what is this msitake");
        exit(1);
    }
    write(SYN, private_pipe, strlen(private_pipe) + 1);
    *to_server = SYN;
    close(SYN);

    //Gets the SYN_ACK from the server through the private_pipe
    int SYN_ACK = open(private_pipe, O_RDONLY);
    char message[256];
    memset(message, 0, sizeof(message));
    read(SYN_ACK, message, sizeof(message));
    printf("%s", message);

    //Sends ACK back
    if (strcmp(message, "Testing") == 0) {
        char ACK[sizeof(message)] = "Testing";
        write(SYN, ACK, strlen(ACK) + 1);
        close(SYN);
    }
    close(SYN_ACK);
    unlink(private_pipe);
}

int server_connect(int from_client) {
    int to_client = 0;
    return to_client;
}