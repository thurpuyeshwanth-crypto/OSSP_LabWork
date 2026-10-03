# Week 1 - The Machine Beneath the Prompt

**Milestone:** create the ShellForge project, a basic Read-Evaluate-Print Loop (REPL), and a Makefile build.

## What the shell does

A shell reads commands from a user and asks the operating system to perform work. In this first milestone, ShellForge reads a line, recognizes `exit`, and echoes other input. It does not execute commands yet.

## REPL behavior

The program repeats these steps:

1. **Read** a line from the terminal.
2. **Evaluate** whether the line is `exit`.
3. **Print** the entered line when it is not `exit`.
4. **Loop** back to the prompt.

## Project foundation

The project uses `src/` for C source, `include/` for headers, and a Makefile to compile the program into `bin/shellforge`. Build output is excluded from Git through `.gitignore`.

```bash
make
make run
```

## Week 1 result

The repository now has a repeatable build and an interactive shell loop. This foundation is extended in Week 2 with dynamically allocated input.
