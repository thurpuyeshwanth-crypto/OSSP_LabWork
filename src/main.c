#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "input.h"
#include "parser.h"
#include "process.h"
#include "builtin.h"
#include "signals.h"

int main(void)
{
    char *line;
    char **tokens;
    int builtin_result;
    initialize_signals();
    printf("=====================================\n%s Version 6.0\n=====================================\n", SHELL_NAME);
    while (1) {
        printf("myshell> "); fflush(stdout);
        line = read_line();
        if (feof(stdin)) { free(line); break; }
        tokens = parse_line(line);
        if (tokens[0] != NULL) {
            builtin_result = execute_builtin(tokens);
            if (builtin_result < 0) { free_tokens(tokens); free(line); break; }
            if (builtin_result == 0) execute(tokens);
        }
        free_tokens(tokens);
        free(line);
    }
    puts("Goodbye!");
    return 0;
}
