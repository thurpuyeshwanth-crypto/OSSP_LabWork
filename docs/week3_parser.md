# Week 3 - The Parser

**Milestone:** split a command line into tokens in the `argv[]` format expected by process execution functions.

## Example

Input:

```text
ls -l /home
```

Parsed arguments:

```text
argv[0] = "ls"
argv[1] = "-l"
argv[2] = "/home"
argv[3] = NULL
```

## How parsing works

`parse_line()` uses `strtok()` to split the input at spaces, tabs, and line separators. The returned token strings point into the original input buffer; they are not separately allocated. The parser allocates a growable array of pointers and ends it with `NULL`.

`free_tokens()` frees only that pointer array. The caller frees the original input line separately after it is done with the tokens.

## Current limitation

This introductory parser treats whitespace as separators. It does not yet implement shell quoting, escaped spaces, pipes, or command execution. Those features belong to later milestones.

## Build and try it

```bash
make clean
make
make run
```

Try `ls -l /home`, several spaces between words, a blank line, and `exit`. ShellForge displays parsed arguments but does not execute the requested command yet.
