#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    int parent_fd[2], child_fd[2];
    char buf[10];

    if(pipe(parent_fd) < 0 || pipe(child_fd) < 0) {
        fprintf(2, "Error: Can't create pipe!\n");
        exit(1);
    }
    int pid = fork();

    if(pid == 0) {  //children process
        close(parent_fd[1]); //close write
        close(child_fd[0]);
        read(parent_fd[0], buf, 1);
        if(buf[0] == 'i') {
            printf("%d: received ping\n", getpid());
        }
        write(child_fd[1], "o", 1);
        close(parent_fd[0]);
        close(child_fd[1]);
    } else {
        close(parent_fd[0]);
        close(child_fd[1]);
        write(parent_fd[1], "i", 1);
        read(child_fd[0], buf, 1);
        if(buf[0] == 'o') {
            printf("%d: received pong\n", getpid());
        }
        close(parent_fd[1]);
        close(child_fd[0]);
    }
    exit(0);

}
