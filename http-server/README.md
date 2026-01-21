# Multithreaded HTTP Server

A lightweight web server implemented in C using BSD Sockets, capable of serving static content to modern web browsers.

## 📝 Overview
This daemon listens on a specific port, accepts incoming TCP connections, parses HTTP/1.1 requests (`GET`), and responds with the appropriate files or error codes (404/500).

## ⚙️ Technical Features
* **BSD Sockets:** Using `socket`, `bind`, `listen`, `accept`.
* **Concurrency:** Thread-per-connection model to handle multiple clients simultaneously.
* **HTTP Parsing:** String manipulation to parse headers and determine MIME types.

## 🔨 Build & Usage

    make
    ./server -p 8080 -d ./www