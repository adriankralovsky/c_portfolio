# Stack-Based Virtual Machine

A lightweight emulator of a custom CPU architecture that executes bytecode instructions.

## 📝 Overview
This VM implements the classic **Fetch-Decode-Execute** cycle found in real processors. It uses a stack for all arithmetic and logic operations, making the instruction set simple yet Turing-complete.

## ⚙️ Technical Features
* **CPU Emulation:** Simulating Instruction Pointer (IP), Stack Pointer (SP), and ALU.
* **Bytecode Interpretation:** Parsing custom binary opcodes (PUSH, POP, ADD, JMP, etc.).
* **Error Handling:** detecting stack overflow/underflow and division by zero.

## 🔨 Build & Usage

    make

**Run Program:**

    ./svm programs/fibonacci.bin