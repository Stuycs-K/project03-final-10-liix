#include "pipe_networking.h"
#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

void parse_csv_line(char *line, struct Student *student);
int count_lines(const char *filename);
struct Student *read_csv(const char *filename);

#endif