#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, grandchild_pid;
    int status;

    child_pid = fork();

    if (child_pid == 0) {
        // This is the child process
        printf("Child process is running with PID: %d\n", getpid());

        grandchild_pid = fork();

        if (grandchild_pid == 0) {
            // This is the grandchild process
            printf("Grandchild process is running with PID: %d\n", getpid());
            printf("Grandchild process will exit.\n");
            exit(EXIT_SUCCESS);
        } else if (grandchild_pid > 0) {
            // This is the child process
            printf("Child process is waiting for the grandchild process to finish.\n");
            wait(&status);
            printf("Child process finished waiting.\n");
            printf("Child process will exit.\n");
            exit(EXIT_SUCCESS);
        } else {
            // fork() failed
            perror("fork");
            exit(EXIT_FAILURE);
        }
    } else if (child_pid > 0) {
        // This is the parent process
        printf("Parent process is running with PID: %d\n", getpid());
        printf("Parent process is waiting for the child process to finish.\n");
        wait(&status);
        printf("Parent process finished waiting.\n");
        printf("Parent process will exit.\n");
    } else {
        // fork() failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}