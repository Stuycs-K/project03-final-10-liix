#include "pipe_networking.h"

// Function to parse a CSV line into a Student struct
void parse_csv_line(char *line, struct Student *student) {
    char *token;

    // Parse name
    token = strsep(&line, ",");
    if (token != NULL) {
        strcpy(student->name, token);
    } else {
        strcpy(student->name, "");
    }

    // Parse date of birth
    token = strsep(&line, ",");
    if (token != NULL) {
        strcpy(student->date_of_birth, token);
    } else {
        strcpy(student->date_of_birth, "");
    }

    // Parse year
    token = strsep(&line, ",");
    if (token != NULL) {
        strcpy(student->year, token);
    } else {
        strcpy(student->year, "");
    }

    // Parse major
    token = strsep(&line, ",");
    if (token != NULL) {
        strcpy(student->major, token);
    } else {
        strcpy(student->major, "");
    }
}

int count_lines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int line_count = 0;
    char line[256];

    fgets(line, 256, file); // Skip the header row
    if (fgets(line, 256, file)) {
        while (fgets(line, 256, file)) {
            line_count++;
        }
    }

    fclose(file);
    return line_count;
}

struct Student *read_csv(const char *filename) {
    int count = count_lines(filename);
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        err();
    }

    char line[256];
    fgets(line, 256, file); // Skip the header row

    struct Student *students = malloc(sizeof(struct Student) * count);
    int counter = 0;

    while (fgets(line, 256, file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        parse_csv_line(line, &students[counter]);
        counter++;
    }

    fclose(file);
    return students;
}



