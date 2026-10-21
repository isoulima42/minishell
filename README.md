*This project has been created as part of the 42 curriculum by isoulima and abouzidi.*

# minishell

<img src="score.png" width="150" alt="Score 100/100">

![Language](https://img.shields.io/badge/Language-C-blue)
![Norminette](https://img.shields.io/badge/Norminette-OK-brightgreen)

## Description

minishell is a minimalist command interpreter inspired by `bash`. It displays
a prompt, reads a line with `readline`, splits it into tokens, parses it into a sequence of
commands connected by pipes, expands variables and quotes, applies the
redirections, then runs each command (internal builtin or external binary through
`execve`). The project covers lexical analysis, parsing, process management
(`fork`/`pipe`/`wait`), redirections, heredocs, variable expansion and
fine-grained signal handling.

---

## Instructions

### Compilation

```bash
make
```

The `libft` library is built automatically, then the `minishell` executable
is generated. The build links `-lreadline`.

```bash
make clean    # removes the .o files
make fclean   # removes the .o files and minishell
make re       # rebuilds everything
```

### Usage

```bash
./minishell
```

Examples:

```bash
minishell$ echo "hello $USER" | cat -e
minishell$ ls -la | grep .c > list.txt
minishell$ cat << EOF
minishell$ export NAME=42 && echo $NAME      # (&& not handled in mandatory)
minishell$ cd /tmp ; pwd                     # (; not handled in mandatory)
```

---

## Features

- Interactive **prompt** and command **history** (`readline`, `add_history`)
- **Lookup and execution** of the right binary through `PATH`, a relative or an absolute path
- **Quotes**: `'` (no interpretation) and `"` (everything except `$`)
- **Expansion** of environment variables: `$VAR`, `${VAR}`, and `$?` (exit status
  of the last foreground pipeline)
- **Redirections**: `<` (input), `>` (truncated output), `>>` (appended output),
  `<<` (heredoc, with or without expansion depending on the delimiter's quotes)
- **Pipes** `|` connecting any number of commands
- **Builtins**: `echo` (`-n` option), `cd` (relative/absolute path), `pwd`, `export`,
  `unset`, `env`, `exit`
- **Signals** in interactive mode:
  - `Ctrl-C` displays a new prompt on a new line (`$?` = 130)
  - `Ctrl-D` exits the shell
  - `Ctrl-\` is ignored at the prompt; during a command it prints `Quit (core dumped)`
- Consistent **exit codes**: `127` (command not found), `126` (permission /
  directory), `128+n` (terminated by a signal), `2` (syntax error)

---

## Technical choices

- **Three-stage pipeline** — a *lexer* produces a list of tokens while respecting
  quotes; a *parser* groups them into `t_cmd` (argv + list of redirections) separated
  by pipes; an *expander* expands variables and quotes, then rebuilds `argv`.
- **Expansion with field splitting** — an unquoted variable containing spaces
  is split into several arguments, as in `bash`; inside quotes, spaces are kept
  and an empty expansion `""` produces an empty argument.
- **A single global variable** `g_signal` (int), limited to the number of the received
  signal, as required by the subject. The handlers are reconfigured depending on the
  context (prompt, execution, heredoc).
- **Builtins that modify the shell** (`cd`, `export`, `unset`, `exit`) run in the
  parent process when they are alone, so that their effects persist; inside a pipe
  they run in the child.
- **Heredoc** read in the parent before execution (interruptible with `Ctrl-C`), the content
  going through a `pipe()`.
- **Environment** stored as a `t_env` linked list (key/value), converted into a
  `char **` array only when calling `execve`.
- **libft dependency**: linked lists (`ft_lst*`), `ft_split`, `ft_substr`,
  `ft_strjoin`, `ft_itoa`, `ft_putstr_fd`, etc.

---

## Resources

- `man readline`, `man 3 rl_on_new_line`
- `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 2 wait`
- `man 2 open`, `man 2 access`, `man 3 getcwd`, `man 2 chdir`
- `man 2 signal`, `man 7 signal`
- Official 42 subject

---

## AI usage

AI was used only to:
- clarify the behavior of `readline` and signals, field splitting during
  expansion, and `bash` exit code conventions
- structure this README

The implementation, the architecture and the understanding of the code were done
manually.

---

## Authors

42 Lausanne
Logins: isoulima (execution, builtins, heredoc, signals, environment) and abouzidi (lexer, parser, expansion)
