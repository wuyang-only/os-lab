#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // 创建新的进程
    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("This is the child process with PID %d\n", getpid());
    } else {
        printf("This is the parent process with PID %d\n", getpid());
    }
    return 0;
}
