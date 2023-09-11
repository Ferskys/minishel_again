# Minishell

Minishell is a C project written for the purpose of creating a shell program. It implements various functionalities of a shell, such as displaying a prompt, maintaining a command history, searching and executing commands, handling redirections and pipes, and managing environment variables.

## Common Instructions

- The project must be written in C and follow the Norm.
- The functions should not quit unexpectedly, except for undefined behaviors.
- All heap allocated memory space must be properly freed.
- Submit a Makefile that compiles the source files with the flags -Wall, -Wextra, and -Werror.
- The Makefile must contain rules for `$(NAME)`, `all`, `clean`, `fclean`, and `re`.
- Optional: Include a `bonus` rule in the Makefile for additional headers, libraries, or functions.
- If using a `libft`, copy its sources and Makefile to a `libft` folder and compile it separately.
- Testing programs are encouraged but not required for submission.

## Mandatory Part

### Program Name: minishell

#### Turn in files:
- Makefile
- \*.h
- \*.c

#### Makefile rules:
- `NAME`: Compiles the program.
- `all`: Compiles the program.
- `clean`: Removes object files.
- `fclean`: Removes object files and the executable.
- `re`: Removes object files and the executable, then recompiles.

#### External Functions:
`readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

#### Description:
The minishell program should have the following functionalities:

- Display a prompt when waiting for a new command.
- Maintain a working history.
- Search and execute the correct executable based on the PATH variable or provided path.
- Use only one global variable, with an explanation of its purpose.
- Not interpret unclosed quotes or unnecessary special characters such as `\` or `;`.
- Handle single quotes (`'`) to prevent interpretation of metacharacters within the quoted sequence.
- Handle double quotes (`"`) to prevent interpretation of metacharacters within the quoted sequence, except for `$` (dollar sign).
- Implement redirections:
  - `<` should redirect input.
  - `>` should redirect output.
  - `<<` should read input until a line containing the specified delimiter is seen.
  - `>>` should redirect output in append mode.
- Implement pipes (`|`). The output of each command in the pipeline should be connected to the input of the next command via a pipe.
- Handle environment variables (`$`) that expand to their values.
- Handle `$?`, which should expand to the exit status of the most recently executed foreground pipeline.
- Handle `ctrl-C`, `ctrl-D`, and `ctrl-\` as in bash.
- In interactive mode:
  - `ctrl-C` should display a new prompt on a new line.
  - `ctrl-D` should exit the shell.
  - `ctrl-\` should do nothing.
- Implement the following built-in commands:
  - `echo` with option `-n`
  - `cd` with a relative or absolute path
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options

### Note:
The `readline()` function may cause memory leaks, but your own code should not have any memory leaks.

### Additional Requirements:
Limit your implementation to the requirements specified in the subject description. Anything not asked for is not required. For any doubts about a requirement, take bash as a reference.

## Bonus Part

The bonus part will only be assessed if the mandatory part is perfect. The bonus part includes:

- Implement `&&` and `||` with parenthesis for priorities.
- Allow wildcards (`*`) to work for the current working directory.

## References

- [C Programming Language](https://en.wikipedia.org/wiki/C_(programming_language))
- [Makefile Tutorial](https://makefiletutorial.com/)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)
