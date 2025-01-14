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

