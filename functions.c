/* functions.c */
#include "main.h"

/**
 * read_line - Reads a line of input from stdin.
 *
 * Return: A pointer to a buffer containing the line of input.
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

/**
 * split_line - Splits a line of input into an array of arguments.
 * @line: The line of input to split.
 *
 * Return: An array of pointers to the arguments.
 */
char **split_line(char *line)
{
    int bufsize = BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (tokens == NULL)
    {
        fprintf(stderr, "Error: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIMITER);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (tokens == NULL)
            {
                fprintf(stderr, "Error: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIMITER);
    }
    tokens[position] = NULL;
    return tokens;
}
/* execute */
int execute(char **args)
{
    int status = 0;
    pid_t pid;

    /* Check if command exists in PATH */
    char *path = getenv("PATH");
    char *dir = strtok(path, ":");
    while (dir != NULL)
    {
        char *cmd_path = malloc(strlen(dir) + strlen(args[0]) + 2);
        sprintf(cmd_path, "%s/%s", dir, args[0]);

        if (access(cmd_path, X_OK) == 0)
        {
            /* Command found in directory */
            printf("Executing command: %s\n", cmd_path);
            args[0] = cmd_path;

            pid = fork();
            if (pid == -1)
            {
                perror("Error: fork failed");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                /* Child process */
                if (execv(args[0], args) == -1)
                {
                    perror("Error: exec failed");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                /* Parent process */
                wait(&status);
                if (WIFEXITED(status))
                {
                    status = WEXITSTATUS(status);
                }
            }

            /* Free memory */
            free(cmd_path);

            return status;
        }

        /* Free memory */
        free(cmd_path);

        /* Move to next directory in PATH */
        dir = strtok(NULL, ":");
    }

    /* Command not found */
    fprintf(stderr, "Error: command not found: %s\n", args[0]);
    return 1;
}
