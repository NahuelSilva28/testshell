#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define DELIMITER " \t\r\n\a"


/* Function prototypes */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
extern char **environ;



#endif /* MAIN_H */
