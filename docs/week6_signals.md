# Week 6 - Signals and Process Control

**Milestone:** keep the interactive shell available after Ctrl+C while allowing a foreground command to receive the interrupt.

Signals notify a process about asynchronous events. ShellForge ignores `SIGINT` in the parent shell. Before executing an external program, the child restores the default `SIGINT` action, so Ctrl+C interrupts a foreground child such as `sleep 30`, while the shell remains alive.

The parent waits for its foreground child using `waitpid()`, retrying if interrupted. This collects the child's exit status and prevents a zombie. The implementation uses `sigaction()` to set the shell's signal disposition.

Try `sleep 30`, press Ctrl+C, then run `pwd` and `exit`.
