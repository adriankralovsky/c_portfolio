# Persistent Key-Value Store

A high-performance database engine that stores key-value pairs in a single binary file with **O(1)** lookup time.

## 📝 Overview
Unlike simple log files, this database implements a fixed-size **Hash Table** directly within the file header. It allows immediate access to data records using `fseek` without scanning the entire file.

## ⚙️ Technical Features
* **Disk-Based Hashing:** Implementation of `djb2` hash function mapped to file offsets.
* **Collision Resolution:** Handling hash collisions using Linear Probing.
* **CRUD Operations:** Supports Create, Read, Update, and Delete operations on binary data.

## 🔨 Build & Usage

    make

**Init & Insert:**

    ./kvdb -n 100 -f data.kv
    ./kvdb -i "user:1" -v "admin" -f data.kv

**Retrieve:**

    ./kvdb -g "user:1" -f data.kv