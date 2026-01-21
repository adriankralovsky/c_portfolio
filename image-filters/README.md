# Image Processor (Convolution Filters)

A graphics tool that applies mathematical convolution filters to PPM/PGM images to perform operations like Blurring and Edge Detection.

## 📝 Overview
The core of this tool is a generic convolution engine. It applies a kernel matrix to every pixel of the input image, recalculating its value based on its neighbors.

## ⚙️ Technical Features
* **Convolution Kernels:** Implementation of Sobel (Edge Detection) and Box Blur matrices.
* **2D Buffer Management:** Handling image data and boundary conditions (padding).
* **Data Clamping:** Ensuring calculated pixel values stay within valid ranges.

## 🔨 Build & Usage

    make

**Apply Filter:**

    ./imgproc -f sobel -i input.ppm -o output.ppm