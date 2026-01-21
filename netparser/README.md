# NetParser (PCAP Analyzer)

A network traffic analysis tool that reads binary **PCAP (Packet Capture)** files and decodes the protocol stack.

## 📝 Overview
This tool mimics basic Wireshark functionality. It parses raw binary network packets and decodes nested protocols: **Ethernet II → IPv4 → TCP/UDP**. It handles network byte order conversions and validates protocol headers.

## ⚙️ Technical Features
* **Protocol Decoding:** Pointer arithmetic to traverse nested packet headers.
* **Endianness Handling:** Converting Big Endian (Network) to Little Endian (Host) using `ntohs`/`ntohl`.
* **Struct Packing:** Using `__attribute__((packed))` to map C structs to binary data.

## 🔨 Build & Usage

    make

**Analyze Traffic:**

    ./netparser -v -f traffic.pcap

**Filter Protocol:**

    ./netparser -v -f traffic.pcap -p tcp