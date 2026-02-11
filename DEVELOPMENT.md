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

### Feb 11, 2026 | Task 2: Advanced Input Parsing & The "Space Trap"
- **Objective:** Enable the shell to handle commands with arguments and survive inconsistent whitespace (e.g., "  /bin/ls  ").
- **Challenge 1: The Functional Bug (The Space Trap)**
    - **Issue:** The automated checker failed when commands were surrounded by spaces.
    - **Symptom:** `execve` returned "No such file or directory" because it was trying to execute the literal string `" /bin/ls "` instead of the command `/bin/ls`.
    - **Solution:** Implemented a pointer-based "trim" logic to skip leading spaces and null-terminate trailing spaces.
- **Challenge 2: The Compilation Wall (C90 Compliance)**
    - **Issue:** GCC reported `error: ISO C90 forbids mixed declarations and code`.
    - **Cause:** Variables like `char *start` were declared in the middle of the function logic.
    - **Solution:** Moved all variable declarations to the very top of the `main` block, satisfying the `-std=gnu89` strict requirements.
- **Challenge 3: Syntax Integrity**
    - **Issue:** `error: expected declaration or statement at end of input`.
    - **Cause:** Mismatched curly braces `{}` within the nested `while` and `if` blocks.
    - **Solution:** Performed a manual brace-audit to ensure every opened block was correctly closed, allowing the compiler to reach the final `return (0)`.
- **Key Learning:** In C90, the "Scope" of a variable is as important as its logic. Proper indentation and brace-tracking are the only things standing between code and a compiler crash.

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
