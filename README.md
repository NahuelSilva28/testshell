# testshell

This is a simple shell program written in C. It provides a basic shell interface for running commands on a Unix-like operating system.


# main.c

This is the main file of a simple shell program written in C. The main function is the entry point of the program, and it contains a loop that displays a prompt, reads input from the user, splits the input into tokens, and executes a command with the given arguments.

In the loop, the read_line function is called to read a line of input from stdin, which is then passed to the split_line function to split it into an array of tokens. The resulting array of tokens is then passed to the execute function to execute the command with the given arguments.

If the execute function returns a non-zero status, indicating that the program should continue running, the loop continues. Otherwise, the program exits with a status of EXIT_SUCCESS.

At the end of each loop iteration, the memory allocated for the line and arguments is freed using the free function.


# functions.c

read_line 
This function reads a line of input from standard input (stdin) and returns a pointer to a buffer containing the line of input. If there is an error, it prints an error message and exits the program.

split_line
The split_line function takes a line of input and splits it into separate tokens based on a set of delimiter characters. It returns an array of pointers to the tokens. The function uses dynamic memory allocation to allocate memory for the tokens and reallocates memory as necessary to accommodate more tokens. If there is an allocation error, the function prints an error message and exits the program. The function also sets the last element of the array to NULL to indicate the end of the list of tokens.

exit_shell
The exit_shell function simply prints a message indicating that the shell is exiting and then calls the exit function with a success status code, causing the program to terminate.

execute
This function executes a command with arguments by forking a child process, calling execvp to replace the child process with the specified command, and waiting for the child process to complete. If the command is "exit", it calls exit_shell function to exit the shell. The function returns the status code of the executed command. If the command is not recognized, it returns 1.
