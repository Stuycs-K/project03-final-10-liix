#include "file_handling.h"
volatile sig_atomic_t running = 1;

static void handle_signal(int sig) {
  printf("\nServer: Received SIGINT of SIGPIPE, cleaning up...\n");
  unlink(WKP); // Delete the WKP
  unlink(private_pipe);
  running = 0; // Stop the server loop
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGPIPE, handle_signal);
    int to_server;
    printf("Does client");
    client_side_authentication(&to_server);
    int from_server = open(private_pipe, O_RDONLY);
    char buffer[256];
    read(to_server, buffer, sizeof(buffer));
    printf("%s", buffer);

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
        
        struct Student * students;
        int count = count_lines(file);
        students = malloc(count * sizeof(struct Student));
        students = read_csv(file, students, count);
        printf("%s", &students[1]);
        for(int i = 0; i < count; i++) {
            if(write(to_server, &students[i], sizeof(struct Student))) {
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
        free(students);
    }
    close(to_server);
    unlink(private_pipe); // Ensure private pipe is removed
    printf("Client: Cleaned up and exiting.\n");
    return 0;
}


