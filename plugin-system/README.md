# Dynamic Plugin Loader

An extensible calculator application that loads mathematical operations from external shared libraries (`.so`) at runtime.

## 📝 Overview
This project demonstrates runtime extensibility. The main program has no built-in math functions; it scans a directory, dynamically links found libraries, and executes their code.

## ⚙️ Technical Features
* **Dynamic Linking:** Using `dlopen`, `dlsym`, and `dlclose` (POSIX `dlfcn.h`).
* **Function Pointers:** Invoking functions without knowing their names at compile time.
* **Modular Design:** Strict separation between the core engine and logic plugins.

## 🔨 Build & Usage

    make
    ./dynacalc

**Interactive:**

    > load plugins
    > add 10 20
    Result: 30