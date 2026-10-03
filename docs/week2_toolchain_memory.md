# Week 2 - The C Toolchain and Memory Model

**Milestone:** read commands that are longer than a fixed-size input array.

## Compilation pipeline

C source passes through preprocessing, compilation, assembly, and linking to produce an executable. The Makefile runs the compiler with warnings enabled and writes the executable under `bin/`.

## Dynamic input and memory ownership

`read_line()` starts with a small heap buffer. When it fills, `realloc()` grows it. The function returns a null-terminated string, and `main()` releases that string with `free()` after using it.

- The stack holds local variables and function-call state automatically.
- The heap holds memory requested at runtime with functions such as `malloc()`.
- Keep the original pointer safe when using `realloc()`: store its result temporarily, check for failure, then update the pointer.

## Week 2 result

ShellForge accepts longer input lines without a fixed 1,024-character limit. The input reader is separated into `src/input.c` with its public declaration in `include/input.h`.
