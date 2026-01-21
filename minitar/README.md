# MiniTAR Archiver

A custom file archiving tool inspired by the UNIX `tar` utility. It serializes multiple files into a single binary package.

## 📝 Overview
MiniTAR demonstrates the fundamentals of file systems and serialization. It creates a custom binary format containing a global header, followed by a sequence of file headers and raw data, preserving metadata like permissions and file sizes.

## ⚙️ Technical Features
* **Binary Serialization:** Combining multiple data streams into one contiguous binary format.
* **Metadata Preservation:** Using `stat()` syscalls to capture file attributes.
* **Stream Processing:** Reading and writing data in chunks to handle files larger than available RAM.

## 🔨 Build & Usage

    make

**Create Archive:**

    ./minitar -c -f archive.mtar file1.txt photo.jpg

**Extract Archive:**

    ./minitar -x -f archive.mtar