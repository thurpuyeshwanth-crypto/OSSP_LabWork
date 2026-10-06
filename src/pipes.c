#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "pipes.h"

static void child_signals_default(void)
{
    struct sigaction action;
    action.sa_handler = SIG_DFL;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    (void)sigaction(SIGINT, &action, NULL);
    (void)sigaction(SIGQUIT, &action, NULL);
    (void)sigaction(SIGTSTP, &action, NULL);
}

static void wait_for(pid_t pid)
{
    while (waitpid(pid, NULL, 0) < 0)
        if (errno != EINTR) { perror("ShellForge: waitpid"); break; }
}

int execute_pipe(char **left, char **right)
{
    int fd[2];
    pid_t first, second;
    if (left == NULL || right == NULL || left[0] == NULL || right[0] == NULL) {
        fprintf(stderr, "ShellForge: invalid pipe command\n"); return -1;
    }
    if (pipe(fd) < 0) { perror("ShellForge: pipe"); return -1; }
    first = fork();
    if (first < 0) { perror("ShellForge: fork"); close(fd[0]); close(fd[1]); return -1; }
    if (first == 0) {
        child_signals_default();
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) < 0) { perror("ShellForge: dup2"); _exit(127); }
        close(fd[1]);
        execvp(left[0], left);
        perror("ShellForge: execvp"); _exit(127);
    }
    second = fork();
    if (second < 0) {
        perror("ShellForge: fork"); close(fd[0]); close(fd[1]); wait_for(first); return -1;
    }
    if (second == 0) {
        child_signals_default();
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) < 0) { perror("ShellForge: dup2"); _exit(127); }
        close(fd[0]);
        execvp(right[0], right);
        perror("ShellForge: execvp"); _exit(127);
    }
    close(fd[0]); close(fd[1]);
    wait_for(first); wait_for(second);
    return 0;
}
