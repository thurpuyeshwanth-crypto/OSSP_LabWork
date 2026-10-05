# OSSP_LabWork

Operating Systems and Systems Programming coursework. The weekly project is **ShellForge**, a small Unix-like shell built step by step in C.

## ShellForge weekly project

| Week | Status | Work completed |
|---|---|---|
| 1 | Done | Project structure and interactive REPL |
| 2 | Done | Dynamically sized command input using `malloc()`, `realloc()`, and `free()` |
| 3 | Done | Command tokenization with `strtok()` and NULL-terminated `argv[]` |
| 4 | Done | External command execution with `fork()`, `execvp()`, and `waitpid()` |
| 5 | Done | Built-ins: `cd`, `pwd`, `env`, `help`, `clear`, and `exit` |
| 6 | Done | Shell ignores Ctrl+C; foreground child receives SIGINT; child status is reaped |

## Source code

- [Main program](src/main.c)
- [Dynamic input reader](src/input.c)
- [Command parser](src/parser.c)
- [External process execution](src/process.c)
- [Built-in commands](src/builtin.c)
- [Signal setup](src/signals.c)
- [Headers](include/)
- [Makefile](Makefile)

## Build and run

Requirements: GCC, GNU Make, and Linux or WSL.

```bash
make
make run
```

Try `pwd`, `cd ..`, `env`, `help`, or an external command such as `ls`. Type `exit` to close ShellForge. Press Ctrl+C during a foreground command to interrupt that child and return to the shell. Use `make clean` to remove generated output.

## Week notes

- [Week 1 - The Machine Beneath the Prompt](docs/week1_machine_beneath_prompt.md)
- [Week 2 - The C Toolchain and Memory Model](docs/week2_toolchain_memory.md)
- [Week 3 - The Parser](docs/week3_parser.md)
- [Week 4 - Processes and Command Execution](docs/week4_process_execution.md)
- [Week 5 - Built-in Commands and Environment Variables](docs/week5_builtins_environment.md)
- [Week 6 - Signals and Process Control](docs/week6_signals.md)

## Current scope

ShellForge runs whitespace-separated commands, implements basic built-ins, and launches external programs. It does not yet support shell quoting, redirection, or pipelines.
