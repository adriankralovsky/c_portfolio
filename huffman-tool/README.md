# Huffman Compression Tool

A lossless file compression utility based on the Huffman coding algorithm.

## 📝 Overview
The tool analyzes byte frequency in a file to generate a prefix-free binary tree. Frequent characters are assigned shorter binary codes, resulting in significant file size reduction for text-heavy data.

## ⚙️ Technical Features
* **Data Structures:** Implementation of Min-Heap (Priority Queue) and Binary Trees.
* **Bit Manipulation:** Reading/writing variable-length bit sequences (not byte-aligned).
* **Tree Serialization:** Storing the decoding tree structure within the file header.

## 🔨 Build & Usage

    make

**Compress:**

    ./huff -c -i huge.log -o compressed.huff

**Decompress:**

    ./huff -d -i compressed.huff -o restored.log