#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: xargs <command> [args...]\n");
        exit(1);
    }

    char *exec_argv[MAXARG];
    for (int i = 1; i < argc; i++) {
        exec_argv[i - 1] = argv[i];  // Copy initial command arguments
    }

    char buf[512];
    int len = 0;

    // Read input line by line
    while ((len = read(0, buf, sizeof(buf) - 1)) > 0) {
        buf[len] = '\0'; // Null-terminate the input

        int line_start = 0;
        for (int i = 0; i <= len; i++) {
            if (buf[i] == '\n' || buf[i] == '\0') { // Each line as an argument
                buf[i] = '\0'; // End the current argument

                // Set up exec_argv for the command + line input
                int j;
                for (j = 1; j < argc; j++) {
                    exec_argv[j - 1] = argv[j];
                }
                exec_argv[j - 1] = &buf[line_start];
                exec_argv[j] = 0; // Null-terminate the argument list

                if (fork() == 0) {
                    exec(exec_argv[0], exec_argv);
                    printf("exec %s failed\n", exec_argv[0]);
                    exit(1);
                }
                wait(0); // Wait for each command to finish

                line_start = i + 1; // Move to the next line
            }
        }
    }
    exit(0);
}