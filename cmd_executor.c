#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char line[1024];
    char *args[64];

    while (1) {
        // 1. Display the prompt
        printf("cmd> ");
        fflush(stdout);

        // 2. Read input from the user
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        // Remove the newline character (\n) from the end of the string
        line[strcspn(line, "\n")] = '\0';

        // Handle empty line input (if user just presses Enter)
        if (strlen(line) == 0) {
            continue;
        }

        // 3. Tokenize the input string by spaces
        int i = 0;
        args[i] = strtok(line, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // 4. Handle built-in commands
        if (strcmp(args[0], "exit") == 0) {
            break;
        } 
        else if (strcmp(args[0], "pwd") == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            }
            continue;
        }

        // 5. Execute external commands by creating a child process
        pid_t pid = fork();

        if (pid < 0) {
            // Fork failed error
            printf("fork failed\n");
        } 
        else if (pid == 0) {
            // Child process: Execute the command
            if (execvp(args[0], args) < 0) {
                printf("command not found: %s\n", args[0]);
                exit(1);
            }
        } 
        else {
            // Parent process: Wait for child to prevent zombie processes
            wait(NULL);
        }
    }

    return 0;
}
