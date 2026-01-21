# Custom Heap Memory Allocator

An implementation of standard C memory management functions (`malloc`, `free`, `realloc`) built from scratch.

## 📝 Overview
This library manages a contiguous block of memory and serves allocation requests. It replaces the system's default allocator to demonstrate the internal mechanics of memory management, fragmentation, and pointer arithmetic.

## ⚙️ Technical Features
* **Explicit Free List:** Tracking free blocks using a doubly-linked list embedded in the heap.
* **Coalescing:** Merging adjacent free blocks during `free()` to reduce external fragmentation.
* **Allocation Strategy:** Implementation of the **Best-Fit** algorithm.

## 🔨 Build & Usage

    make test
    ./memtest