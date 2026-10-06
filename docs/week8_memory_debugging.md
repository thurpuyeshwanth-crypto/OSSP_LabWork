# Week 8 - Memory Management and Debugging

This week checks the accumulated shell for leaks and invalid memory use. Input lines and token arrays are freed after each command. Redirection and pipeline descriptors are closed in the parent and child paths, and children are waited for.

```bash
make clean && make
make test
make asan
printf 'pwd\necho check\nexit\n' | valgrind --leak-check=full ./bin/shellforge
```

Use `gdb ./bin/shellforge`, then `break main`, `run`, `next`, `backtrace`, and `quit` to inspect execution. AddressSanitizer checks memory errors during a run; Valgrind reports heap use and leaks. `make valgrind` provides a short scripted check when Valgrind is installed.
