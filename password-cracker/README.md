# Parallel Password Cracker

A multi-threaded brute-force utility designed to find a password corresponding to a given hash.

## 📝 Overview
This project demonstrates the power of parallel computing in C. The tool splits the search space of possible character combinations among multiple worker threads to utilize all CPU cores.

## ⚙️ Technical Features
* **POSIX Threads:** Using `pthread_create` and `pthread_join` for parallelism.
* **Synchronization:** Implementing Mutexes and Atomic variables to prevent race conditions.
* **Load Balancing:** Algorithmic splitting of the key space.

## 🔨 Build & Usage

    make

**Run with 4 threads:**

    ./cracker -t 4 -l 4 -h 0xDEADBEEF