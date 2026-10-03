#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define TOKEN_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

char **parse_line(char *line)
{
    size_t size = TOKEN_SIZE;
    size_t position = 0;
    char **tokens = malloc(size * sizeof(*tokens));

    if (tokens == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line, TOKEN_DELIMITERS);
    while (token != NULL)
    {
        if (position + 1 >= size)
        {
            size *= 2;
            char **grown = realloc(tokens, size * sizeof(*tokens));
            if (grown == NULL)
            {
                free(tokens);
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            tokens = grown;
        }
        tokens[position++] = token;
        token = strtok(NULL, TOKEN_DELIMITERS);
    }

    tokens[position] = NULL;
    return tokens;
}

void free_tokens(char **tokens)
{
    free(tokens);
}
