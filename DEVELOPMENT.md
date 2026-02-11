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

### Feb 11, 2026 | Task 2: Advanced Input Parsing & The Space Trap
- **Objective:** Enable the shell to handle commands with arguments and extra whitespace.
- **The Discovery (First Checker Run):**
    - **Issue:** Running `/bin/ls` with surrounding spaces caused "No such file or directory" errors.
    - **Data:** The checker sent `"/bin/ls\n"`, `" /bin/ls\n"`, and `"/bin/ls \n"`. 
    - **Result:** My Task 1 logic only handled the first case; the others failed because `execve` treated the spaces as part of the filename.
- **The Implementation (The Fix):**
    - **Strategy:** Transitioned from simple newline-stripping to full string tokenization.
    - **Tool:** Utilized `strtok` to split the input string using `" \t\n"` as delimiters.
    - **Outcome:** This naturally ignores leading, trailing, and multiple consecutive spaces, isolating only the "words" (tokens) needed for execution.
- **Key Learning:** Handling a command-line is less about *running* the command and more about *cleaning* the string. Robust parsing is the foundation of a reliable shell.

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
