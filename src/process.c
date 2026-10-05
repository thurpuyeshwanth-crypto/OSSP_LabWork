#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "process.h"

int execute(char **tokens)
{
    pid_t pid;
    int status;
    if (tokens == NULL || tokens[0] == NULL) return 0;
    pid = fork();
    if (pid < 0) { perror("ShellForge: fork"); return -1; }
    if (pid == 0) {
        struct sigaction action;
        action.sa_handler = SIG_DFL;
        sigemptyset(&action.sa_mask);
        action.sa_flags = 0;
        if (sigaction(SIGINT, &action, NULL) < 0) { perror("ShellForge: sigaction"); _exit(127); }
        execvp(tokens[0], tokens);
        perror("ShellForge: execvp");
        _exit(127);
    }
    while (waitpid(pid, &status, 0) < 0) {
        if (errno != EINTR) { perror("ShellForge: waitpid"); return -1; }
    }
    return 0;
}
