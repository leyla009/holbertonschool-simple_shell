<img height="50" align="right" src="https://raw.githubusercontent.com/fchavonet/fchavonet/refs/heads/main/assets/images/logo-holberton_school.webp" alt="Holberton School logo">

# Simple Shell Project

## Project Content
<details>
    <a href="#overview">Overview</a>
    <br>
    <a href="#features">Features</a>
    <br>
    <a href="#tech-stack">Tech stack</a>
    <br>
    <a href="#techincal-specifications">Techincal Specifications</a>
    <br>
    <a href="#file-structure">File Structure</a>
    <br>
    <a href="#usage">Usage</a>
    <br> 
    <a href="#authors">Authors</a>
</details>

## <span id="overview">Overview</span>
This project is the collaboration between **Leyla Khaspoladova** and **David Abdurahmanov**. The Simple Shell is a custom implementation of the **Thompson Shell** (sh). This command-line interpreter provides a user interface for the Unix operating system. 
The program reads commands from either the standard input or a file and executes them. This project was developed to explore the depths of **system calls**, **process management** (fork, exec, wait), and **memory management**.

## <span id="features">Features</span>

* **Dual Execution Modes:** Fully functional in both interactive (terminal) and non-interactive (piped) modes.
* **Process Management:** Utilises the `fork`, `execve`, and `wait` system calls to manage command execution lifecycles.
* **Path Resolution:** Dynamically handles command execution by searching the `PATH` environment variable.
* **Built-in Commands:** Support for internal shell commands, including `exit` and `env`.
* **Input Handling:** Robust command-line tokenization and handling of the End-of-File (`EOF`) condition.

## <span id="tech-stack">Tech stack</span>

<p align="left">
    <img src="https://img.shields.io/badge/C-a8b9cc?logo=&logoColor=black&style=for-the-badge" alt="C badge">
    <img src="https://img.shields.io/badge/GIT-f05032?logo=git&logoColor=white&style=for-the-badge" alt="Git badge">
    <img src="https://img.shields.io/badge/GITHUB-181717?logo=github&logoColor=white&style=for-the-badge" alt="GitHub badge">
    <img src="https://img.shields.io/badge/VIM-019733?logo=vim&logoColor=white&style=for-the-badge" alt="VIM badge">
</p>

## <span id="techical-specifications">Techical Specifications</span>
### Compilation
The shell is compiled using the following flags to ensure code quality and standard compliance:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
### Standards and Constraints
* **Style**: All code adheres to the Betty Style guide for C.
* **Memory Management**: Zero tolerance for memory leaks; verified through systematic testing via `valgrind`.
* **Modular Design**: A strict limit of five functions per source file to ensure maintainability.
* **System Interface**: Optimised use of system calls to interact directly with the kernel.

## <span id="file-structure">File Structure</span>

| **FILE**             | **FUNCTIONALITY**                                               |
| :------------------: | --------------------------------------------------------------- |
| `main.c`             | Core logic and the primary execution loop.                      |
| `main.h`             | Global header containing prototypes and include guards.         |
| `exec.c`             | Logic for command execution and process synchronisation.        |
| `args.c`             | String parsing, tokenisation, and `PATH` handling.              |
| `env.c`              | Functions for environment variable access and manipulation.     |
| `commands.c`         | Implementation of internal shell built-ins.                     |
| `man_1_simple_shell` | Comprehensive manual page for the interpreter.                  |
| `AUTHORS`            | Credit for project contributors.                                |


## <span id="usage">Usage</span>
### Interactive Mode
```
$ ./hsh
($) /bin/ls
main.c  main.h  exec.c  hsh
($) exit
```
### Non-Interactive Mode
```
$ echo "/bin/ls" | ./hsh
main.c  main.h  exec.c  hsh
```

## <span id="authors">Authors</span>

**Leyla Khaspoladova**
- GitHub: [@leyla009](https://github.com/leyla009)

**David Abdurahmanov**
- Github: [@](https://github.com/)
