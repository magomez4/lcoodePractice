#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("I am the child process.\n");
    } else if (pid > 0) {
        printf("I am the parent process.\n");
    } else {
        printf("Fork failed.\n");
    }

    return 0;
}
