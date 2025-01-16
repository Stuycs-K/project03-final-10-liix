#include "pipe_networking.h"
char private_pipe[256];
int running = 1;
struct Student {
    char name[100];
    char date_of_birth[20];
    char year[10];
    char major[100];
};

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
        char message[] = "sending file now";
        if (write(to_server, message, strlen(message) + 1) == -1) {
            perror("Client: Error sending message");
            break;
        }
        
        read_csv(file);
        printf(students[1]);
        printf(count);
        for(int i = 0; i < count; i++) {
            if(write(to_server, students[i], sizeof(struct Student))) {
                perror("Client Error sending while parsing file");
                break;
            }

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


