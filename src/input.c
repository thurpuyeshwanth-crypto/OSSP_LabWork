#include <stdio.h>
#include <stdlib.h>
#include "input.h"

#define INITIAL_SIZE 64

char *read_line(void)
{
    size_t size = INITIAL_SIZE;
    size_t position = 0;
    char *buffer = malloc(size);
    int ch;

    if (buffer == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while ((ch = getchar()) != EOF && ch != '\n')
    {
        if (position + 1 >= size)
        {
            size *= 2;
            char *grown = realloc(buffer, size);
            if (grown == NULL)
            {
                free(buffer);
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            buffer = grown;
        }
        buffer[position++] = (char)ch;
    }

    buffer[position] = '\0';
    return buffer;
}
