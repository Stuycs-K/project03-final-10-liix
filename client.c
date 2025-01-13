#include "pipe_networking.h"
char private_pipe[256];
int running = 1;

int main() {
    int from_server;
    int to_server;
    from_server = client_side_authentication(&to_server);
    char buffer[256];
    read(to_server, buffer, sizeof(buffer));
    snprintf(private_pipe, sizeof(private_pipe), "client_pipe_%d", getpid());
    printf(buffer);

    printf("Please type the file that you want to transfer to the server");
    char file[256];
    while (running) {
        printf("Client: Enter a file (or type 'exit' to quit): ");
        fgets(file, sizeof(file), stdin);
        file[strcspn(file, "\n")] = 0; // Remove newline character

        if (strcmp(file, "exit") == 0) {
        printf("Client: Disconnecting...\n");
        break;
        }

        if (write(to_server, file, strlen(file) + 1) == -1) {
        perror("Client: Error sending message");
        break;
        }

        char response[256];
        if (read(from_server, response, sizeof(response)) > 0) {
            printf("Client: Received from server: %s\n", response);
        } else {
            perror("Client: Error reading response");
            break;
        }
    }
    close(to_server);
    close(from_server);
    unlink(private_pipe); // Ensure private pipe is removed
    printf("Client: Cleaned up and exiting.\n");
    return 0;
}


