#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

static void add_token(char ***tokens, size_t *count, size_t *capacity, char *token)
{
    if (*count + 1 >= *capacity) {
        size_t next = *capacity * 2;
        char **grown = realloc(*tokens, next * sizeof(**tokens));
        if (grown == NULL) { free(*tokens); perror("realloc"); exit(EXIT_FAILURE); }
        *tokens = grown;
        *capacity = next;
    }
    (*tokens)[(*count)++] = token;
}

char **parse_line(char *line)
{
    size_t count = 0, capacity = 16;
    char **tokens = malloc(capacity * sizeof(*tokens));
    char *p = line;
    if (tokens == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
    while (*p != '\0') {
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0') break;
        if (p[0] == '2' && p[1] == '>') {
            add_token(&tokens, &count, &capacity, "2>"); p += 2; continue;
        }
        if (*p == '<') { add_token(&tokens, &count, &capacity, "<"); p++; continue; }
        if (*p == '|') { add_token(&tokens, &count, &capacity, "|"); p++; continue; }
        if (*p == '>') {
            if (p[1] == '>') { add_token(&tokens, &count, &capacity, ">>"); p += 2; }
            else { add_token(&tokens, &count, &capacity, ">"); p++; }
            continue;
        }
        char *start = p;
        while (*p && !isspace((unsigned char)*p) && *p != '<' && *p != '>' && *p != '|') p++;
        if (*p) {
            char delimiter = *p;
            *p = '\0';
            add_token(&tokens, &count, &capacity, start);
            if (isspace((unsigned char)delimiter)) p++;
            else *p = delimiter;
        } else add_token(&tokens, &count, &capacity, start);
    }
    tokens[count] = NULL;
    return tokens;
}

void free_tokens(char **tokens) { free(tokens); }
