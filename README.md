# C Systems Programming Portfolio

Welcome to my portfolio of low-level system programming projects. This repository demonstrates my proficiency in **C (C99/C11)**, memory management, POSIX system calls, and algorithm design.

The projects are implemented from scratch with a focus on clean code, manual memory management, and efficient resource usage.

## 📂 Project Categories

### 🧠 Core Systems & Virtualization
Deep dives into how operating systems and computers work under the hood.

| Project | Description | Key Concepts |
| :--- | :--- | :--- |
| **[Micro Shell](./micro-shell)** | A custom UNIX command interpreter supporting external commands, pipes, and I/O redirection. | `fork`, `exec`, `pipes`, `signals`, `process control` |
| **[Stack Virtual Machine](./stack-vm)** | Implementation of a stack-based CPU emulator with a custom bytecode instruction set. | `fetch-decode-execute`, `stack manipulation`, `binary parsing` |
| **[Heap Allocator](./heap-manager)** | A custom implementation of `malloc`, `free`, and `realloc` managing memory blocks. | `sbrk`, `explicit free list`, `memory fragmentation`, `pointer arithmetic` |
| **[Plugin Loader](./plugin-system)** | An extensible calculator app that loads mathematical operations from shared libraries at runtime. | `dlopen`, `dlsym`, `dynamic linking`, `API design` |

### 🌐 Networking & Concurrency
Projects focusing on communication protocols, sockets, and parallel processing.

| Project | Description | Key Concepts |
| :--- | :--- | :--- |
| **[HTTP Server](./http-server)** | A multithreaded web server capable of handling concurrent client requests and serving static files. | `BSD sockets`, `TCP/IP`, `multithreading`, `HTTP parsing` |
| **[Network Traffic Analyzer](./netparser)** | A tool that parses binary PCAP files and analyzes Ethernet, IPv4, and TCP/UDP headers. | `packet sniffing`, `network byte order`, `protocol structures` |
| **[Parallel Password Cracker](./password-cracker)** | A brute-force tool utilizing multiple threads to find collisions for a given hash. | `pthreads`, `mutex`, `synchronization`, `race conditions` |

### 💾 File Systems & Storage
Handling binary data, persistence, and custom file formats.

| Project | Description | Key Concepts |
| :--- | :--- | :--- |
| **[FAT16 Explorer](./fat16-reader)** | A utility to read, list, and extract files from a raw FAT16 disk image without mounting it. | `file systems`, `cluster chains`, `endianness`, `binary structs` |
| **[Key-Value Database](./kv-store)** | A persistent on-disk database using a hash index for O(1) data retrieval. | `hashing`, `linear probing`, `random file access`, `serialization` |
| **[MiniTAR Archiver](./minitar)** | A tool to serialize multiple files into a single binary archive and extract them back. | `serialization`, `file metadata`, `buffer management` |

### 🎨 Algorithms & Media Processing
Advanced data manipulation, compression, and graphics.

| Project | Description | Key Concepts |
| :--- | :--- | :--- |
| **[Huffman Compressor](./huffman-tool)** | A lossless file compression tool using Huffman coding trees. | `binary trees`, `priority queues`, `bit manipulation` |
| **[Image Processor](./image-filters)** | An application that applies convolution filters (blur, edge detection) to PPM/PGM images. | `2D arrays`, `convolution kernels`, `image processing` |
| **[Steganography Tool](./stego-bmp)** | A utility to hide secret messages inside the least significant bits (LSB) of BMP images. | `bitwise operations`, `BMP format`, `data hiding` |
| **[Terminal RPG](./ncurses-game)** | An interactive rogue-like game running in the terminal. | `ncurses library`, `state machines`, `game loop` |

---

## 🛠️ Technical Stack

* **Language:** C (C99 Standard)
* **Build System:** Makefile / CMake
* **Version Control:** Git
* **Debugging & Profiling:** GDB, Valgrind
* **Platform:** Linux / UNIX-like systems

## 🚀 Build Instructions

Each project is contained within its own directory and includes a standalone `Makefile`. To build and run a specific project, navigate to its folder:

Example for **Micro Shell**:

```bash
# 1. Navigate to the project folder
cd micro-shell

# 2. Build the project
make

# 3. Run the executable
./myshell
