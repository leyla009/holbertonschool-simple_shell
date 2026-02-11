# Simple Shell Development Log

This file tracks the technical progress, challenges, and solutions encountered during the development of the `hsh` project.

## Project Status Overview
- **Phase:** Task 1 (Core Execution)
- **Current Goal:** Implementing the Fork-Wait-Execve lifecycle.
- **Betty Status:** 0 Errors, 0 Warnings.

---

## Log Entries

### Feb 11, 2026 | Task 0: Foundations & Documentation
- **Objective:** Establish the project repository, README, and AUTHORS.
- **Challenge:** Divergent branches error when pushing to GitHub after editing the README online.
- **Solution:** Configured Git to use the merge strategy (`git config pull.rebase false`) to reconcile local and remote histories.
- **Key Learning:** Always `git pull` before starting local work to stay synchronized.

### Feb 11, 2026 | Task 0: Manual Page Construction
- **Objective:** Create a UNIX-style man page (`man_1_simple_shell`).
- **Challenge:** The system environment was minimized and the `man` command was missing.
- **Solution:** Utilized `nroff -man ./man_1_simple_shell | less` to preview the ROFF formatting without needing a full system restore.
- **Key Learning:** Learned the ROFF macro language (`.SH`, `.IP`, `.TP`) for professional documentation.

### Feb 11, 2026 | Task 1: Main Loop Initialization
- **Objective:** Create the "Heart" of the shell in `main.c`.
- **Challenge:** Handling the End-of-File (EOF) condition to prevent infinite loops.
- **Solution:** Used the return value of `getline`. When `nread == -1`, the shell breaks the loop and frees memory.
- **Key Learning:** `isatty(STDIN_FILENO)` is essential to differentiate between a human typing and a script piping commands.

### Feb 11, 2026 | The "Betty Battle" (Style Compliance)
- **Objective:** Pass the `betty-style` and `betty-doc` linters.
- **Challenge:** 13 errors and 20 warnings regarding indentation and spaces.
- **Solution:** 1. Used `unexpand -t 8` to convert spaces to hard tabs.
    2. Used `sed` to strip trailing whitespaces.
    3. Reconfigured editor to a tabstop of 8.
- **Key Learning:** Betty requires strict adherence to tabstops; code inside nested conditionals must land exactly on the next 8-character mark.

### Feb 11, 2026 | Task 2: Command Line Arguments & Tokenization
- **Objective:** Enable the shell to handle commands with options (e.g., `ls -l /var`) and handle inconsistent whitespace.
- **Challenge 1: The Functional Bug (The Space Trap)**
    - **Issue:** The shell failed when commands had leading or trailing spaces. `execve` was treating the spaces as part of the filename.
    - **Solution:** Moved from simple newline stripping to full string tokenisation using `strtok`. This automatically treats multiple spaces as a single delimiter.
- **Challenge 2: Argument Vector (`argv`) Implementation**
    - **Issue:** `execve` requires an array of strings (`char **`), but `getline` provides a single buffer.
    - **Solution:** Created a `char *argv[32]` array and used a `while` loop with `strtok(NULL, " \t\n")` to populate it. Added a mandatory `NULL` terminator at the end of the array.
- **Challenge 3: C90 & Header Synchronization**
    - **Issue 1:** `error: ISO C90 forbids mixed declarations`. Fixed by moving `int i`, `char *token`, and `char **argv` to the top of `main`.
    - **Issue 2:** `error: conflicting types for ‘execute_command’`.
    - **Cause:** `main.h` contained both the old char * and new char ** prototypes.
    - **Solution:** Cleaned `main.h` to maintain a "Single Source of Truth," leaving only the pointer-to-pointer signature.
- **Key Learning:** A shell is essentially a bridge between a human-readable string and a kernel-readable array. The synchronisation between `main.h`, `main.c`, and `exec.c` is the most fragile part of the architecture.

---

## Contribution Tracking
*Updated: Feb 11, 2026*

| Contributor | Roles | Focus Area |
| :--- | :--- | :--- |
| **Leyla** | Contributor | Architecture, Git Management, Style Compliance |

---

## Tech Stack Notes
- **Language:** C (Standard: gnu89)
- **OS:** Ubuntu 20.04 LTS
- **Compiler:** `gcc -Wall -Werror -Wextra -pedantic -std=gnu89`
- **Tools:** `valgrind` (Memory), `betty` (Style)
- **Error Handling:** `perror` for system call failures.
- **Memory Management:** `getline` with explicit `free()` calls to maintain a zero-leak status.
- **Parsing:** `strtok` with delimiters `" \t\n\r\a"`.
- **Process Management:** `fork()` -> `execve()` -> `wait()`.
- **Compliance:** ANSI C (C90) / gnu89.
- **Memory Safety:** Verified 0 leaks via Valgrind.
