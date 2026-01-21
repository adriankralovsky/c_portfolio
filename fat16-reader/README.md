# FAT16 File System Explorer

A user-space utility that reads and extracts files from a raw **FAT16 disk image** without mounting it.

## 📝 Overview
This project simulates an Operating System's file system driver. It parses the Boot Sector, traverses the File Allocation Table (FAT), and follows cluster chains to reconstruct fragmented files stored on the disk image.

## ⚙️ Technical Features
* **Cluster Chaining:** Following linked lists of clusters in the FAT table to read fragmented data.
* **Binary Parsing:** Reading BIOS Parameter Blocks (BPB) and 8.3 filenames.
* **LBA Addressing:** Converting logical cluster indices to physical byte offsets.

## 🔨 Build & Usage

    make

**List Root Directory:**

    ./fatcat -l -f disk.img

**Extract File:**

    ./fatcat -x README.TXT -f disk.img