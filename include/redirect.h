#ifndef REDIRECT_H
#define REDIRECT_H
/* Return 1 when redirection syntax was handled; 0 when none was present. */
int execute_redirection(char **args);
#endif
