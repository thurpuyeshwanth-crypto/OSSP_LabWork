# Week 9 - File Descriptors and I/O Redirection

**Milestone:** redirect standard input, output, append output, and standard error for external commands.

ShellForge recognizes `<`, `>`, `>>`, and `2>` even when adjacent to a word, such as `2>errors.txt`. It opens the target with the appropriate flags, forks a child, uses `dup2()` to replace file descriptor 0, 1, or 2, then executes the command. The parent closes its descriptors and waits.

Examples:

```text
echo hello > output.txt
cat < output.txt
echo again >> output.txt
ls missing-file 2> errors.txt
```

Redirection currently applies to external commands and does not combine with pipelines or redirect built-in output. Quoting and shell expansion are not implemented.
