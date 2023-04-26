/* functions.c */
#include "main.h"

/**
 * read_line - Reads a line of input from stdin.
 *
 * Return: A pointer to a buffer containing the line of input.
 */
char *read_line(void)
{
    char *line = NULL;  /* initialize the pointer to the input line */
    size_t bufsize = 0;  /* initialize the size of the buffer */

    if (getline(&line, &bufsize, stdin) == -1) {  /*read the input line*/
        perror("getline");
        exit(EXIT_FAILURE);
    }

    return line;
}

/**
 * split_line - split a line into tokens
 * @line: the line to split
 * @bufsize: a pointer to the size of the buffer
 * Return: an array of tokens
 */
char **split_line(char *line)
{
    int bufsize = BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*)); /* allocate memory for an array of tokens */
    char *token, *saveptr;

    if (!tokens) { /* check if memory allocation was successful */
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok_r(line, TOKEN_DELIMITERS, &saveptr); /* split the line into tokens */
    while (token != NULL) {
        tokens[position] = strdup(token);  /* allocate memory for each token and store it in the array */
        if (!tokens[position]) {  /* check memo */
            fprintf(stderr, "Allocation error\n");
            exit(EXIT_FAILURE);
        }
        position++;

        if (position >= bufsize) { /* check if the buffer is full */
            bufsize += BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));  /* reallocate memory */
            if (!tokens) {  /* check if memory allocation was successful */
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok_r(NULL, TOKEN_DELIMITERS, &saveptr); /* get the next token */
    }
    tokens[position] = NULL; /* set the last element of the array to NULL */
    return tokens;
}

/**
 * exit_shell - Exits the shell.
 *
 * Return: Nothing.
 */
void exit_shell(void)
{
    printf("Exiting shell...\n");
    exit(EXIT_SUCCESS);
}

/**
 * execute - Executes a command with arguments.
 * @args: The array of arguments, including the command.
 *
 * Return: The status code of the executed command.
 */
int execute(char **args)
{
    pid_t pid;    /*"pid" variable will store the process ID of the child process created by the fork() system call*/
    int status;   /* the "status" variable will store the exit status of the child process.*/

    if (args[0] == NULL) {
        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
        exit_shell();
    }

    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execvp(args[0], args) == -1) {  /*create a child process using the fork() system call.
                                            If the return value of fork() is 0, the current process is the child process.
                                            In the child process, the execvp() system call is used to replace the current process with the new process specified by the "args" array.
                                            If execvp() returns -1, an error occurred and perror() is called to print an error message*/
            perror("execute");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Error forking */
        perror("execute");
    } else {
        /* Parent process */
        waitpid(pid, &status, WUNTRACED); /* In the parent process, waitpid() is used to wait for the child process to finish 
        executing. The WUNTRACED option tells waitpid() to return immediately if the child process is stopped,
        but not terminated. The exit status of the child process is stored in the "status" variable */
    }

    return 1;
}
