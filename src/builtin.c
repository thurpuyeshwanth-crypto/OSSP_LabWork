#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"

extern char **environ;

int execute_builtin(char **args)
{
    char cwd[4096];
    if (args == NULL || args[0] == NULL) return 1;
    if (strcmp(args[0], "exit") == 0) return -1;
    if (strcmp(args[0], "pwd") == 0) {
        if (getcwd(cwd, sizeof(cwd)) == NULL) perror("ShellForge: pwd");
        else puts(cwd);
        return 1;
    }
    if (strcmp(args[0], "cd") == 0) {
        const char *dest = args[1] != NULL ? args[1] : getenv("HOME");
        if (dest == NULL) fprintf(stderr, "ShellForge: cd: HOME is not set\n");
        else if (chdir(dest) < 0) perror("ShellForge: cd");
        return 1;
    }
    if (strcmp(args[0], "clear") == 0) {
        fputs("\033[2J\033[H", stdout); fflush(stdout); return 1;
    }
    if (strcmp(args[0], "help") == 0) {
        puts("ShellForge built-ins: cd [dir], pwd, env, help, clear, exit"); return 1;
    }
    if (strcmp(args[0], "env") == 0) {
        char **entry;
        for (entry = environ; *entry != NULL; entry++) puts(*entry);
        return 1;
    }
    return 0;
}
