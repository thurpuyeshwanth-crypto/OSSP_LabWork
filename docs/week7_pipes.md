# Week 7 - Pipes and Inter-Process Communication

**Milestone:** support one pipeline connecting two external commands.

An anonymous pipe is a kernel-managed byte stream with a read end and a write end. ShellForge forks two children, redirects the first child's standard output to the pipe with `dup2()`, redirects the second child's standard input, closes unused descriptors, and waits for both children.

Try:

```text
ls -l | grep .c
echo hello | wc -c
```

This milestone supports one two-command pipeline. Quoting and longer pipelines are not implemented.
