# Week 5 - Built-in Commands and Environment Variables

**Milestone:** add commands that need to change or inspect ShellForge's own state.

Built-ins run in the shell process. This matters for `cd`: changing directory in a child would leave the parent shell in its old directory. ShellForge implements:

- `cd [directory]` using `chdir()`; without an argument it uses `HOME`.
- `pwd` using `getcwd()`.
- `env` to display the process environment.
- `help`, `clear`, and `exit`.

Other commands use the Week 4 `fork()` and `execvp()` path. Environment variables are inherited by child processes and can be inspected with `getenv()` or `env`.
