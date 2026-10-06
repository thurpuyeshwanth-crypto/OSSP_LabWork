#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "redirect.h"

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

static int open_target(const char *op, const char *path)
{
    if (strcmp(op, "<") == 0) return open(path, O_RDONLY);
    if (strcmp(op, ">>") == 0) return open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    return open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

int execute_redirection(char **args)
{
    size_t argc = 0, out_count = 0;
    int fds[3] = {-1, -1, -1};
    int targets[3] = {STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};
    char **clean;
    int found = 0, ok = 1;
    while (args[argc]) argc++;
    clean = calloc(argc + 1, sizeof(*clean));
    if (clean == NULL) { perror("calloc"); return 1; }

    for (size_t i = 0; i < argc; i++) {
        int target_index = -1;
        if (strcmp(args[i], "<") == 0) target_index = 0;
        else if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0) target_index = 1;
        else if (strcmp(args[i], "2>") == 0) target_index = 2;
        if (target_index < 0) { clean[out_count++] = args[i]; continue; }
        found = 1;
        if (i + 1 >= argc || args[i + 1][0] == '\0' || strcmp(args[i + 1], "<") == 0 || strcmp(args[i + 1], ">") == 0 || strcmp(args[i + 1], ">>") == 0 || strcmp(args[i + 1], "2>") == 0) {
            fprintf(stderr, "ShellForge: missing filename after %s\n", args[i]); ok = 0; break;
        }
        if (fds[target_index] >= 0) close(fds[target_index]);
        const char *op = args[i];
        const char *path = args[i + 1];
        i++;
        fds[target_index] = open_target(op, path);
        if (fds[target_index] < 0) { perror("ShellForge: open"); ok = 0; break; }
    }
    clean[out_count] = NULL;
    if (!found) { free(clean); return 0; }
    if (ok && clean[0] == NULL) { fprintf(stderr, "ShellForge: redirection needs a command\n"); ok = 0; }

    pid_t pid = -1;
    if (ok) {
        pid = fork();
        if (pid < 0) { perror("ShellForge: fork"); ok = 0; }
        else if (pid == 0) {
            child_signals_default();
            for (int i = 0; i < 3; i++)
                if (fds[i] >= 0 && dup2(fds[i], targets[i]) < 0) { perror("ShellForge: dup2"); _exit(127); }
            for (int i = 0; i < 3; i++) if (fds[i] >= 0) close(fds[i]);
            execvp(clean[0], clean);
            perror("ShellForge: execvp"); _exit(127);
        }
    }
    for (int i = 0; i < 3; i++) if (fds[i] >= 0) close(fds[i]);
    if (pid > 0) {
        int status;
        while (waitpid(pid, &status, 0) < 0)
            if (errno != EINTR) { perror("ShellForge: waitpid"); break; }
    }
    free(clean);
    return 1;
}
