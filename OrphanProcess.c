#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid > 0) {
        // This is the parent process
        printf("Parent process is running with PID: %d\n", getpid());
        printf("Parent process will sleep for 10 seconds.\n");
        sleep(10);
        printf("Parent process finished.\n");
    } else if (child_pid == 0) {
        // This is the child process
        printf("Child process is running with PID: %d\n", getpid());
        printf("Child process will sleep for 5 seconds.\n");
        sleep(5);
        printf("Child process finished.\n");
    } else {
        // fork() failed
        perror("fork");
        return 1;
    }

    return 0;
}
