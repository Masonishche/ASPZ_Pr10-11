#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i;

    printf("Parent process (PID: %d) starting\n", getpid());

    // Create 3 child processes
    for (i = 0; i < 3; i++) {
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork failed\n");
            exit(1);
        } else if (pid == 0) {
            // Child process
            printf("Child process %d (PID: %d) created\n", i + 1, getpid());
            sleep(1); // Simulate some work
            printf("Child process %d (PID: %d) exiting\n", i + 1, getpid());
            exit(0);
        }
    }

    // Parent process waits for all children
    for (i = 0; i < 3; i++) {
        pid = wait(NULL);
        if (pid > 0) {
            printf("Parent: Child process (PID: %d) has completed\n", pid);
        } else {
            fprintf(stderr, "Wait failed\n");
            exit(1);
        }
    }

    printf("Parent process (PID: %d) exiting\n", getpid());
    return 0;
}
