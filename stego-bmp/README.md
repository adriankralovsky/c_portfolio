# BMP Steganography Tool

A CLI utility implemented in C that hides secret text messages inside BMP image files using the **Least Significant Bit (LSB)** steganography method.

## 📝 Overview
This tool manipulates the raw binary data of uncompressed BMP images. By altering only the lowest bit of color channels, it embeds data without creating visible artifacts in the image.

## ⚙️ Technical Features
* **Manual Header Parsing:** Directly reads and validates `BITMAPFILEHEADER` and `BITMAPINFOHEADER` structs.
* **Bitwise Manipulation:** Uses masks (`&`, `|`, `~`, `<<`, `>>`) to inject bits into pixel data.
* **Memory Safety:** Specific attention to buffer management when handling large image files.

## 🔨 Build & Usage

    make

**Encode:**

    ./stego -e -i input.bmp -o output.bmp -m "Hidden Message"

**Decode:**

    ./stego -d -i output.bmp