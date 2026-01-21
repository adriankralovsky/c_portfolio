# Micro Shell

A custom implementation of a UNIX command-line interpreter (shell), compatible with standard system commands.

## 📝 Overview
Micro Shell replicates the core functionality of `bash` or `zsh`. It provides a prompt where users can execute programs, pass arguments, manage background processes, and chain commands.

## ⚙️ Technical Features
* **Process Management:** Using `fork()`, `execvp()`, and `waitpid()` lifecycle.
* **I/O Redirection:** Implementing `>` and `<` operators using `dup2()`.
* **IPC (Pipes):** Connecting the output of one process to the input of another (`cmd1 | cmd2`).

## 🔨 Build & Usage

    make
    ./myshell

**Example:**

    myshell$ ls -la | grep ".c" > sources.txt