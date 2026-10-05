# Week 4 - Processes and Command Execution

**Milestone:** run external Linux programs from ShellForge.

A program is a file stored on disk. A process is that program while it is running. ShellForge uses `fork()` to create a child process. The child calls `execvp()` to replace itself with the requested program, while the parent waits with `waitpid()` before showing the next prompt.

```text
ShellForge -> fork() -> child -> execvp(command)
                    parent -> waitpid(child)
```

If `fork()` or `execvp()` fails, ShellForge reports the error. The child uses `_exit()` after a failed `execvp()` so it does not accidentally run parent cleanup code.

Try external commands such as `ls`, `date`, or `echo hello`. Unknown commands display an error and return to the prompt.
