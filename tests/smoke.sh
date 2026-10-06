#!/bin/sh
set -eu
shell=${1:-./bin/shellforge}
tmp_out=tests/out.tmp
tmp_err=tests/err.tmp
trap 'rm -f "$tmp_out" "$tmp_err" tests/session.tmp' EXIT
printf 'echo hello > %s\ncat < %s\necho again >> %s\nls | grep Makefile\nno_such_shellforge_cmd 2> %s\nexit\n' "$tmp_out" "$tmp_out" "$tmp_out" "$tmp_err" | "$shell" > tests/session.tmp
printf 'hello\nagain\n' | cmp -s - "$tmp_out"
grep -q 'hello' tests/session.tmp
grep -q 'Makefile' tests/session.tmp
grep -q 'execvp' "$tmp_err"
printf 'ShellForge smoke tests passed.\n'
