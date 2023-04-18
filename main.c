/* main.c */

#include "main.h"

/**
 * main - Entry point of the program
 *
 * Return: Always returns 0.
 */
int main(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("$ ");
        line = read_line();
        args = split_line(line);
        status = execute(args);
        free(line);
        free(args);
    } while (status == 0);

    return (0);
}
