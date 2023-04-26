/* main.c */

#include "main.h"

/**
 * main - Entry point of the program
 *
 * Return: Always returns 0.
 */
int main(void)
{
    char *line; /* Pointer to the line read from stdin */
    char **args;/* Array of arguments parsed from the line */
    int status;/* Status of the executed command */

    do {
        printf(" :) shell > ");
        line = read_line(); /* Read the line from stdin */
        args = split_line(line);  /* Split the line into an array of arguments */
        status = execute(args); /* Execute the command with its arguments */

        free(line); /* Free the memory allocated for the line */
        free(args); /* Free the memory allocated for the arguments */

    } while (status); /* Continue the loop until the shell is exited */

    return EXIT_SUCCESS; /* exit */
}
