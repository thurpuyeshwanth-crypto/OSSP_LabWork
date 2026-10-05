#ifndef BUILTIN_H
#define BUILTIN_H
/* 1 = handled, 0 = external command, -1 = exit shell */
int execute_builtin(char **args);
#endif
