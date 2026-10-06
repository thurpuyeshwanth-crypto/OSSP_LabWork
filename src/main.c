#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "input.h"
#include "parser.h"
#include "process.h"
#include "builtin.h"
#include "signals.h"
#include "pipes.h"
#include "redirect.h"

int main(void)
{
    initialize_signals();
    printf("=====================================\n%s Version %s\n=====================================\n", SHELL_NAME, VERSION);

    for (;;) {
        printf("myshell> ");
        fflush(stdout);
        char *line = read_line();
        if (feof(stdin)) { free(line); break; }
        char **tokens = parse_line(line);
        if (tokens[0] == NULL) { free_tokens(tokens); free(line); continue; }

        size_t pipe_index = 0;
        int pipe_count = 0;
        while (tokens[pipe_index] != NULL) {
            if (strcmp(tokens[pipe_index], "|") == 0) { pipe_count++; break; }
            pipe_index++;
        }
        if (pipe_count) {
            tokens[pipe_index] = NULL;
            if (tokens[0] == NULL || tokens[pipe_index + 1] == NULL)
                fprintf(stderr, "ShellForge: pipe needs a command on both sides\n");
            else {
                for (size_t i = pipe_index + 1; tokens[i] != NULL; i++)
                    if (strcmp(tokens[i], "|") == 0) pipe_count++;
                if (pipe_count > 1)
                    fprintf(stderr, "ShellForge: only one two-command pipe is supported\n");
                else execute_pipe(tokens, &tokens[pipe_index + 1]);
            }
        } else {
            int builtin_result = execute_builtin(tokens);
            if (builtin_result < 0) {
                free_tokens(tokens); free(line); break;
            }
            if (builtin_result == 0 && execute_redirection(tokens) == 0)
                execute(tokens);
        }
        free_tokens(tokens);
        free(line);
    }
    puts("Goodbye!");
    return 0;
}
