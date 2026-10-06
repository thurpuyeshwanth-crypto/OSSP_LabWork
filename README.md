# OSSP_LabWork

Operating Systems and Systems Programming coursework. The weekly project is **ShellForge**, a small Unix-like shell built step by step in C.

## ShellForge weekly project

| Week | Status | Work completed |
|---|---|---|
| 1 | Done | Project structure and interactive REPL |
| 2 | Done | Dynamically sized command input |
| 3 | Done | Tokenization into a NULL-terminated `argv[]` |
| 4 | Done | External execution using `fork()`, `execvp()`, and `waitpid()` |
| 5 | Done | Built-ins: `cd`, `pwd`, `env`, `help`, `clear`, and `exit` |
| 6 | Done | Ctrl+C handling and child reaping |
| 7 | Done | Two-command pipelines using `pipe()` and `dup2()` |
| 8 | Done | Smoke tests and Makefile targets for Valgrind and AddressSanitizer |
| 9 | Done | `<`, `>`, `>>`, and `2>` redirection for external commands |

## Source code

- [Main program](src/main.c)
- [Dynamic input reader](src/input.c)
- [Command parser](src/parser.c)
- [External process execution](src/process.c)
- [Built-in commands](src/builtin.c)
- [Pipelines](src/pipes.c)
- [I/O redirection](src/redirect.c)
- [Makefile](Makefile)

## Build, test, and run

Requirements: GCC, GNU Make, and Linux or WSL.

```bash
make
make test
make run
```

Optional memory checks: `make asan` and `make valgrind`.

Try `ls | grep .c`, `echo hello > output.txt`, `cat < output.txt`, `echo again >> output.txt`, or `ls missing 2> errors.txt`.

## Week notes

- [Week 1](docs/week1_machine_beneath_prompt.md) · [Week 2](docs/week2_toolchain_memory.md) · [Week 3](docs/week3_parser.md)
- [Week 4](docs/week4_process_execution.md) · [Week 5](docs/week5_builtins_environment.md) · [Week 6](docs/week6_signals.md)
- [Week 7 - Pipes](docs/week7_pipes.md) · [Week 8 - Memory and debugging](docs/week8_memory_debugging.md) · [Week 9 - Redirection](docs/week9_redirection.md)

## Current limitations

ShellForge supports one two-command pipeline and redirects on external commands. It does not implement shell quoting, variable expansion, longer pipelines, redirection of built-in output, or combining pipes with redirection.
