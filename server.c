#include "pipe_networking.h"
#include <signal.h>
#include <stdlib.h>

volatile sig_atomic_t running = 1;
// Signal handler for SIGINT
static void handle_signal(int sig) {
  printf("\nServer: Received SIGINT of SIGPIPE, cleaning up...\n");
  unlink(WKP); // Delete the WKP
  unlink(private_pipe);
  running = 0; // Stop the server loop
}

int main() {
  // Set up signal handling for shutdown
  signal(SIGPIPE, handle_signal);
  signal(SIGINT, handle_signal);

  FILE * csv = fopen("Storage.csv", "a+");
  char * Name, DOB, Age, Major;
  while (running) {
    printf("Server: Waiting for a client...\n");
    int to_client;
    int from_client = server_side_authentication(&to_client);

    printf("Server: Client connected. Entering communication loop...\n");

    char * init_message = "You are connected, please type in the path to your file";
    write(to_client, init_message, sizeof(init_message));
    char buffer[256];
    while (read(from_client, buffer, sizeof(buffer)) > 0) {
      printf("Server: Received from client: %s\n", buffer);
    }
    fflush(csv);
    memset(buffer, 0, sizeof(buffer));
    char * message = "Thank you for sending your file";
    write(to_client, message, sizeof(message) + 1); 

    printf("Server: Client disconnected.\n");
    close(from_client); // Close upstream pipe
    close(to_client);   // Close downstream pipe
  }
  fclose(csv);
  remove(WKP);
  printf("Server: Shutting down...\n");
}