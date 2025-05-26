# CLIWrapper

**CLIWrapper** is a lightweight C++ command line tool that analyzes your shell history (e.g., `.bash_history`) and displays your most frequently used commands with beautifully formatted output.

---

## Features

- Parses and analyzes shell history
- Normalizes similar tools (e.g., `/usr/bin/python3.12` → `python`)
- Outputs clean, aligned usage statistics with ASCII bars


---

## Build and Run

### Requirements

- `g++` with C++17 support
- `make`

### Usage

```bash
make run
