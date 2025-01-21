#include "file_handling.h"

static void handle_signal(int sig) {
  printf("\nServer: Received SIGINT, cleaning up...\n");
  unlink(private_pipe);
}

int main() {
    signal(SIGINT, handle_signal);
    int to_server;
    client_side_authentication(&to_server);
    char buffer[256];
    int from_server = open(private_pipe, O_RDONLY);
    read(from_server, buffer, sizeof(buffer));
    printf("%s eeeeeeeee", buffer);

    char file[256];
    printf("Client: Enter a file: ");
    fgets(file, sizeof(file), stdin);
    file[strcspn(file, "\n")] = 0; // Remove newline character
    if (strcmp(file, "exit") == 0) {
        printf("Client: Disconnecting...\n");
        close(to_server);
        unlink(private_pipe); // Ensure private pipe is removed
        printf("Client: Cleaned up and exiting.\n");
        return 0;
    }
    char message[] = "sending file now";
    if (write(to_server, message, strlen(message) + 1) == -1) {
        perror("Client: Error sending message");
        close(to_server);
        unlink(private_pipe); // Ensure private pipe is removed
        printf("Client: Cleaned up and exiting.\n");
        return 0;
    }
    
    struct Student * students;
    int count = count_lines(file);
    students = malloc(count * sizeof(struct Student));
    students = read_csv(file, students, count);
    printf("%s", &students[1]);
    for(int i = 0; i < count; i++) {
        if(write(to_server, &students[i], sizeof(struct Student))) {
            perror("Client Error sending while parsing file");
            close(to_server);
            unlink(private_pipe); // Ensure private pipe is removed
            printf("Client: Cleaned up and exiting.\n");
            return 0;
        }
    }
    char response[256];
    if (read(from_server, response, sizeof(response)) > 0) {
        printf("Client: Received from server: %s\n", response);
    } else {
        perror("Client: Error reading response");
        close(to_server);
        unlink(private_pipe); // Ensure private pipe is removed
        printf("Client: Cleaned up and exiting.\n");
        return 0;
    }
    free(students);
    close(to_server);
    unlink(private_pipe); // Ensure private pipe is removed
    printf("Client: Cleaned up and exiting.\n");
    return 0;
}


