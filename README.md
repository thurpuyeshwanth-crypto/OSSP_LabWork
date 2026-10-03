# OSSP_LabWork

Operating Systems and Systems Programming coursework. The weekly project is **ShellForge**, a small Unix-like shell built step by step in C.

## ShellForge weekly project

| Week | Status | Work completed |
|---|---|---|
| 1 | Done | Project structure, interactive REPL, Makefile, and Git setup |
| 2 | Done | Dynamically sized command input using `malloc()`, `realloc()`, and `free()` |
| 3 | Done | Command tokenization with `strtok()` and a NULL-terminated `argv[]` |
| 4 onward | Planned | Process creation and execution will be added in later work sessions |

## Build and run

Requirements: GCC, GNU Make, and a Linux environment such as Ubuntu or WSL.

```bash
make
make run
```

Type `exit` to close ShellForge. Remove generated build output with `make clean`.

## Project layout

```text
.
├── Makefile
├── README.md
├── include/
│   ├── input.h
│   ├── parser.h
│   └── shell.h
├── src/
│   ├── input.c
│   ├── main.c
│   └── parser.c
├── docs/
├── tests/
├── screenshots/
└── bin/                 # generated executable; ignored by Git
```

## Week notes

- [Week 1 - The Machine Beneath the Prompt](docs/week1_machine_beneath_prompt.md)
- [Week 2 - The C Toolchain and Memory Model](docs/week2_toolchain_memory.md)
- [Week 3 - The Parser](docs/week3_parser.md)

## Current scope

ShellForge currently reads a full input line and displays its parsed tokens. The parser prepares arguments in the format required by `execvp()`, but command execution is a later milestone.
