#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid == 0) {
        // This is the child process
        printf("Child process is running with PID: %d\n", getpid());
        
        // Execute a command using exec
        char *args[] = {"/bin/ls", "-l", NULL};
        execvp(args[0], args);
        
        // execvp only returns if there is an error
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (child_pid > 0) {
        // This is the parent process
        printf("Parent process is running with PID: %d\n", getpid());
        
        // Wait for the child process to finish
        printf("Parent process waiting for the child process to finish...\n");
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process exited abnormally\n");
        }
    } else {
        // fork() failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}
