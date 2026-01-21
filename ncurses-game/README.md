# Terminal Dungeon Crawler

An interactive rogue-like game running in the terminal, built using the `ncurses` library.

## 📝 Overview
A game engine that renders a tile-based map, handles player input, and manages game state (inventory, health, collisions). It demonstrates how to build interactive TUI applications in C.

## ⚙️ Technical Features
* **Ncurses Library:** Managing terminal windows, colors, and non-blocking input.
* **Game Loop:** A continuous loop handling Input → Logic Update → Rendering.
* **Dynamic Maps:** Loading level layouts from text files into dynamic 2D arrays.

## 🔨 Build & Usage
*(Requires libncurses-dev)*

    make
    ./game maps/level1.map