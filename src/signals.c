#include <signal.h>
#include <stdio.h>
#include <string.h>
#include "signals.h"

void initialize_signals(void)
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = SIG_IGN;
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGINT, &action, NULL) < 0)
        perror("ShellForge: sigaction(SIGINT)");
}
