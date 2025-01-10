#include "pipe_networking.h"
#include "pipe_networking.h"
#include <signal.h>
#include <stdlib.h>

int running = 1;
// Signal handler for SIGINT
void handle_sigint(int sig) {
  printf("\nServer: Received SIGINT, cleaning up...\n");
  unlink(WKP); // Delete the WKP
  running = 0; // Stop the server loop
}

int main() {
  // Set up signal handling for shutdown
  signal(SIGINT, handle_sigint);

  while (running) {
    printf("Server: Waiting for a client...\n");
    int from_client = server_setup();

    int to_client;
    from_client = server_handshake(&to_client);

    printf("Server: Client connected. Entering communication loop...\n");

    char buffer[256];
    while (read(from_client, buffer, sizeof(buffer)) > 0) {
      printf("Server: Received from client: %s\n", buffer);
      char sample = "Please send message";
      write(to_client, sample, sizeof(sample)); 
    }

    printf("Server: Client disconnected.\n");
    close(from_client); // Close upstream pipe
    close(to_client);   // Close downstream pipe
  }
  printf("Server: Shutting down...\n");
}