#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    child_pid = vfork();

    if (child_pid > 0) {
        // This is the parent process
        printf("Parent process is running.\n");
        printf("Parent process created a child process with PID: %d\n", child_pid);
        printf("Parent process will wait for child process to terminate.\n");
        wait(NULL); // Wait for child process to terminate
        printf("Parent process finished.\n");
    } else if (child_pid == 0) {
        // This is the child process
        printf("Child process is running.\n");
        printf("Child process will exit immediately.\n");
        exit(0);
    } else {
        // vfork() failed
        perror("vfork");
        return 1;
    }

    return 0;
}
