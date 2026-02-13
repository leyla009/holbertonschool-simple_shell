# Simple Shell Development Log

This file tracks the technical progress, challenges, and solutions encountered during the development of the `hsh` project.

## Project Status Overview
- Phase: Task 6 (Simple Shell 1.0)
- Current Goal: Milestone Achievement - Full path resolution and basic built-in commands (`exit`, `env`).
- Betty Status: 0 Errors, 0 Warnings (Strict compliance maintained).
- Memory Status: Valgrind-clean; all heap allocations (`getline`, `strdup`, `find_path`) are tracked and freed.

## Completed Features
- **Core Execution:** Fork-Wait-Execve lifecycle is stable.
- **Path Resolution:** Commands are located via the `PATH` environment variable.
- **Env Built-in:** Displays current environment variables using `environ`.
- **Exit Built-in:** Shell terminates with the correct status using `exit`, handling both manual exits and EOF (Ctrl+D).
- **Error Handling:** Returns 127 for missing commands and 2 for illegal operations.
- **Custom Getline:** Built-in buffer management using static variables and manual `read` calls to replace restricted library functions.
- **Memory Management:** Manual `_realloc` implementation handles dynamic buffer expansion for large inputs without forbidden symbols.
- **String Library:** Independent utility suite (`_strlen`, `_strcmp`, `_strtok`, etc.) eliminates dependencies on `<string.h>`.

## Current Goal

Handling command-line arguments for the exit built-in (Task 9)

---

## Log Entries

### Feb 11, 2026 | Task 0: Foundations & Documentation
- **Objective:** Establish the project repository, README, and AUTHORS.
- **Challenge:** Divergent branches error when pushing to GitHub after editing the README online.
- **Solution:** Configured Git to use the merge strategy (`git config pull.rebase false`) to reconcile local and remote histories.
- **Key Learning:** Always `git pull` before starting local work to stay synchronised.

### Feb 11, 2026 | Task 0: Manual Page Construction
- **Objective:** Create a UNIX-style man page (`man_1_simple_shell`).
- **Challenge:** The system environment was minimized and the `man` command was missing.
- **Solution:** Utilised `nroff -man ./man_1_simple_shell | less` to preview the ROFF formatting without needing a full system restore.
- **Key Learning:** Learned the ROFF macro language (`.SH`, `.IP`, `.TP`) for professional documentation.

### Feb 11, 2026 | Task 1: Main Loop Initialisation
- **Objective:** Create the "Heart" of the shell in `main.c`.
- **Challenge:** Handling the End-of-File (EOF) condition to prevent infinite loops.
- **Solution:** Used the return value of `getline`. When `nread == -1`, the shell breaks the loop and frees memory.
- **Key Learning:** `isatty(STDIN_FILENO)` is essential to differentiate between a human typing and a script piping commands.

### Feb 11, 2026 | The "Betty Battle" (Style Compliance)
- **Objective:** Pass the `betty-style` and `betty-doc` linters.
- **Challenge:** 13 errors and 20 warnings regarding indentation and spaces.
- **Solution:** 1. Used `unexpand -t 8` to convert spaces to hard tabs.
    2. Used `sed` to strip trailing whitespaces.
    3. Reconfigured the editor to a tabstop of 8.
- **Key Learning:** Betty requires strict adherence to tabstops; code inside nested conditionals must land exactly on the next 8-character mark.

### Feb 11, 2026 | Task 2: Handling the "Space Trap"
- **Objective:** Fix the bug where commands failed if surrounded by spaces (e.g., `" /bin/ls "`).
- **Challenge: The Functional Bug (The Space Trap)**
    - **Issue:** ISO C90 standards forbid mixed declarations. Attempting to fix the logic by declaring variables mid-block introduced compiler errors.
    - **Solution:** Reorganised `main.c` to declare all variables at the top of the function. Implemented a pointer-based "trim" logic to sanitise input before passing it to the executor.
- **Key Learning:** In strict C90 (gnu89), the structure of the code is as important as the logic. Every variable must be accounted for before the first line of executable code.

### Feb 11, 2026 | Task 3: Command Line Arguments and Tokenisation
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
    - **Cause:** `main.h` contained both the old `char *` and new `char **` prototypes.
    - **Solution:** Cleaned `main.h` to maintain a "Single Source of Truth," leaving only the pointer-to-pointer signature.
- **Key Learning:** A shell is essentially a bridge between a human-readable string and a kernel-readable array. The synchronisation between `main.h`, `main.c`, and `exec.c` is the most fragile part of the architecture.

### Feb 11, 2026 | Task 4: Path Resolution (Simple Shell 0.3)
- **Objective:** Allow the shell to execute commands without requiring absolute paths (e.g., `ls` instead of `/bin/ls`).
- **Challenge:** The `execve` system call does not automatically search the PATH. When the user inputs `ls`, the shell currently fails because it only looks in the current working directory.
- **Planned Solution:** 1. Retrieve the `PATH` string from the `environ` global variable.
    2. Tokenise the `PATH` into individual directory strings using `:` as a delimiter.
    3. For each directory, prepend it to the user's command (e.g., `/bin/` + `ls`).
    4. Use `stat()` to check if the resulting path is a valid executable.
- **Constraint:** Must not use `getenv()`; must manually iterate through `environ`.
### Feb 11, 2026 | Task 4: Header Refactoring
- **Objective:** Clean up legacy code and synchronise prototypes for PATH resolution.
- **Action:** Removed `display_prompt` and `read_input` functions.
- **Reasoning:** Simplified the main loop logic to improve readability and ensure Betty compliance. Consolidating logic inside the main loop reduces the overhead of passing multiple pointers between small helper functions.
- **Result:** Successfully resolved "conflicting types" and "implicit declaration" errors.

### Feb 11, 2026 | Task 4: PATH Integration & Execution Guard
- **Objective:** Enable the shell to handle simple commands (ls) and prevent unnecessary forks.
- **Challenge:** Intercepting the command string to resolve its location without breaking the existing argv structure.
- **Solution:** Modified the main loop to call `find_path` immediately after tokenization. 
    - If a path is found: `argv[0]` is updated, `execute_command` is called, and the path is freed.
    - If not found: An error message is printed to `stderr`, and no fork occurs.
- **Result:** The shell now behaves like a real sh/bash instance, resolving paths dynamically.

### Feb 11, 2026 | Task 4: Syntax Correction & Scope Resolution
- **Objective:** Resolve compilation errors in `main.c` related to block scoping.
- **Challenge:** Encountered `error: expected declaration or statement at end of input`. This was caused by an imbalance in curly braces after nesting the PATH resolution logic.
- **Solution:** Performed a manual audit of the control flow. Closed the `while` loop properly and ensured the `main` function returns `0` to satisfy the `int` return type.
- **Key Learning:** Deeply nested `if-else` blocks in C require strict attention to indentation and brace matching, especially when adhering to C90 standards.

### Feb 11, 2026 | Task 4: Final Compilation and Return Logic
- **Objective:** Resolve the `control reaches end of non-void function` compiler error.
- **Challenge:** Even though the shell logic exists within an infinite loop, the C90 standard requires a guaranteed return path for functions declared with a non-void return type.
- **Solution:** Appended `return (0);` at the end of the `main` function scope. This ensures that if the loop ever terminates (e.g., EOF/Ctrl+D), the process exits with a success status.
- **Result:** Code now compiles cleanly with `-Wall -Werror -Wextra -pedantic`.

### Feb 11, 2026 | Task 4: Variable Scoping and Exit Codes
- **Objective:** Fix "undeclared identifier" error for the status variable.
- **Challenge:** Under C90 standards, variables must be declared at the beginning of the block. Adding `status` in the middle of the logic caused a compilation failure.
- **Solution:** Relocated the `int status` declaration to the top of the `main` function alongside `line` and `argv`.
- **Key Learning:** Compiler errors like `undeclared (first use in this function)` are often a reminder of strict C90 variable placement rules, even if the logic itself is sound.

### Feb 11, 2026 | Task 4: Strict PATH Resolution logic
- **Objective:** Correct behaviour when the `PATH` environment variable is unset.
- **Challenge:** The shell was incorrectly executing local binaries when `PATH` was missing, failing the `path_path1_var` test case which expects a 'not found' error.
- **Solution:** - Implemented a check using `strchr` to see if a command is a path (contains `/`).
    - If no slash is present and `PATH` is NULL, the search immediately fails.
    - This prevents the shell from accidentally finding binaries in the current directory unless explicitly invoked with `./`.
- **Result:** Shell now correctly returns 127 and the 'not found' error message when `PATH` is absent from the environment.

### Feb 11, 2026 | Task 4: Variable Audit and Optimisation
- **Objective:** Ensure all declared variables are utilised to maintain clean code and Betty compliance.
- **Action:** Audited `find_path.c` and `main.c` for unused variables like `cmd_len` or `dir_len`.
- **Reasoning:** Unused variables increase the memory footprint of the stack frame unnecessarily and trigger warnings in strict compilation environments. 
- **Result:** Streamlined local variable declarations, ensuring every `int` and `char *` serves a functional purpose in the PATH search algorithm.
### Feb 11, 2026 | Task 4: Robust Path Resolution
- **Objective:** Fix edge cases for missing PATH and local execution.
- **Challenge:** The shell was finding local files even when PATH was missing, which is incorrect behaviour for a simple shell.
- **Solution:** - Added a check for `/` in the command string to handle absolute/relative paths immediately.
    - Added a safety check to return `NULL` if `_getenv("PATH")` fails.
    - Maintained `cmd_len` and `dir_len` for efficient `malloc` calculations.
- **Result:** Now passes the `path_path1_var` checker test by correctly failing to find commands when the `PATH` variable is specifically absent.

### Feb 11, 2026 | Task 4: Path Resolution (Simple Shell 0.3) [SUMMARY]
- **Objective:** Enable the shell to execute commands without requiring absolute paths (e.g., allow `ls` instead of `/bin/ls`) by searching the `PATH` environment variable.
- **Key Challenges & Solutions:**
- **The Forbidden `getenv`:** Since the standard library getenv is restricted, I implemented a custom `_getenv` function to manually traverse the `char **environ` array.
- **PATH Environment Edge Cases:** Fixed a critical bug where the shell was incorrectly searching the current directory when the `PATH` variable was missing or renamed (e.g., `PATH1`).
- **The "No-Fork" Requirement:** Implemented a guard to ensure `fork()` and `execute_command()` are only called if the binary is verified to exist using `stat()`.
- **Memory Management:** Managed dynamic memory for `path_copy` and `file_path` to prevent leaks during tokenisation, ensuring every `malloc` has a corresponding `free`.
- **Exit Status Compliance:** Standardised the shell to return an exit status of 127 when a command is not found, matching the behaviour of /bin/sh.

## Architecture Changes
- `_getenv.c`: Manually scans the environment for a specific key.
- `find_path.c`: Tokenises the PATH string and uses `stat()` to validate command locations.
- `main.h`: Synchronised with new prototypes to avoid "implicit declaration" warnings under C90.
- `main.c`: Refactored the loop to intercept commands and resolve paths before forking.

### Feb 12, 2026 | Task 5: Built-in 'exit' Implementation
- **Objective:** Implement a way for the user to terminate the shell session gracefully.
- **Challenge:** Distinguishing between built-in commands and external binaries. Built-ins must be executed in the parent process.
- **Solution:** Added a `strcmp` check at the start of the execution logic. If the input is "exit", the shell cleans up its primary memory buffers and calls the `exit()` system call.
- **Key Learning:** Built-ins like `exit` or `cd` cannot be external programs because they need to modify the state of the shell process itself.

### Feb 12, 2026 | Task 5: C90 Scope Compliance
- **Issue:** `redeclaration of ‘full_path’` and `mixed declarations and code` errors.
- **Root Cause:** In the C90 standard, variables must be declared at the very beginning of a block (immediately after a `{`). I had an executable `if` statement followed by a new variable declaration.
- **Solution:** Moved `char *full_path;` to the top of the `if (argv[0] != NULL)` block and changed the initialisation line to a simple assignment (`full_path = ...`).
- **Key Learning:** C90 is much less flexible than modern C (C99/C11). The "Declaration -> Logic" sequence is mandatory.

### Feb 12, 2026 | Task 5: Exit Status Synchronisation
- **Issue:** Shell exiting with code 0 instead of the exit code of the last failed command.
- **Problem:** The `execute_command` function was forking and waiting, but the exit status of the child was being lost in the parent process.
- **Solution:** Modified `execute_command` to return the result of `WEXITSTATUS(status)`. Updated the main loop to assign this return value to the global `status` variable.
- **Result:** When `/bin/ls` fails with status 2, the shell now correctly exits with status 2 when the `exit` command is called.

### Feb 13, 2026 | Task 6: Environment Built-in (Simple Shell 1.0)
- **Objective:** Implement the env built-in command to display all current environment variables, providing the user with a snapshot of the shell's configuration.
- **Key Challenges & Solutions:**
- **Global Variable Access:** Used the `extern char **environ` global variable. Since this isn't provided in a header file by default, declaring it as `extern` was necessary to link to the environment array provided by the system.
- **Loop Termination:** Handled the `environ` array as a NULL-terminated list of strings. The loop continues until it hits the `NULL` pointer, ensuring all variables are printed without overflowing memory.
- **Built-in Priority:** Integrated the `env` check immediately after the `exit` check. This ensures that the shell doesn't attempt to search the `PATH` for an external "env" binary, which improves performance and adheres to built-in logic standards.
- **Key Learning:** Understanding that environ is a NULL-terminated array of strings, similar to argv, but provided by the OS to every process.

### Logic Flow:
1. User inputs `env`.
2. `strtok` parses the command.
3. The shell compares `argv[0]` to "`env`".
4. If matched, the shell iterates through `environ[i]` and prints each string followed by `\n`.
5. The shell resets the `status` to `0` and returns to the prompt.

### Feb 13, 2026 | Task 9 Development Log: Issues & Resolutions
### 1. The "Built-in" Conflict
- **Issue:** GCC flagged a "conflicting types" or "note: built-in declared here" error for functions like `strncmp`.
- **Cause:** The compiler has internal versions of standard library functions. When we implemented our own versions without using the standard headers, the names collided.
- **Solution:** Prefixed all custom utility functions with an underscore (e.g., `_strncmp`, `_strlen`, `_strtok`). This created a unique namespace and prevented the compiler from confusing our code with GLIBC built-ins.

### 2. The "Const Qualifier" Mismatch
- **Issue:** Error: `passing argument discards ‘const’ qualifier from pointer target type`.
- **Cause:** Functions like `_getenv` use `const char *` for the environment variable name (to ensure it isn't accidentally modified). Our helper functions like `_strncmp` were originally defined to take `char *` (mutable), which the compiler saw as a security risk.
- **Solution:** Refactored all string utility prototypes in `main.h` and definitions in `strings.c` to use `const char *` for source strings.

### 3. The Linker Duplicate Definition
- **Issue:** `ld: multiple definition of '_getenv'`.
- **Cause:** The project had the same function implementation in two different source files (`_getenv.c` and `env_utils.c`). The linker couldn't decide which one to use for the final executable.
- **Solution:** Consolidated all environment-related logic into `env_utils.c` and deleted the redundant `_getenv.c` file.

### 4. Forbidden Function: `fileno`
- **Issue:** Checker rejected the binary with the message `Function 'fileno' is not allowed`.
- **Cause:** `fileno` is a library function used to convert a `FILE *` stream to an integer file descriptor. The project constraints require direct system calls.
- **Solution:** Bypassed the stream abstraction entirely. In `_getline.c`, changed the read call to use the hardcoded file descriptor `0` (or `STDIN_FILENO`) instead of `fileno(stream)`.

### 5. Forbidden Function: `realloc`
- **Issue:** Checker rejected the binary with the message `Function 'realloc' is not allowed`.
- **Cause:** To handle large inputs, `_getline` needs to resize its buffer. Using the standard `realloc` was forbidden to test manual memory management skills.
- **Solution:** Implemented a custom `_realloc` function in `memory.c`. This function manually handles the "Allocate-Copy-Free" lifecycle:
  - `malloc` a new block of `new_size`.
  - Manually copy data from the old pointer using a `for` loop (to avoid forbidden `memcpy`).
  - `free` the old pointer.

### 6. Undeclared Identifiers in New Files
- **Issue:** `memory.c: error: ‘NULL’ undeclared and implicit declaration of function ‘malloc’`.
- **Cause:** In C, every `.c` file is an independent unit. A new file like `memory.c` does not automatically know about the headers included in `main.c`.
- **Solution:** Added `#include "main.h"` to the top of every `.c` file to ensure the compiler has access to the standard library definitions (via our central header).

### 7. Unused Parameter Warnings
- **Issue:** `error: unused parameter ‘stream’ [-Werror=unused-parameter]`.
- **Cause:** Once `fileno(stream)` was removed, the `stream` variable was no longer used, but the task required we keep the specific function signature for `_getline`.
- **Solution:** Used the `(void)stream`; idiom at the start of the function to explicitly tell the compiler the parameter is intentionally unused.

### Feb 13, 2026 | Milestone: 1.0 Production Readiness

- **Optimization:** Replaced all remaining standard `realloc` and `fileno` calls with custom implementations.
- **Architecture:** Consolidated memory management into `memory.c` and environment logic into `env_utils.c`.
- **Standardization:** Validated all function signatures against `gnu89` strict type-checking requirements.

 ---

## Contribution Tracking
*Updated: Feb 13, 2026*

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
