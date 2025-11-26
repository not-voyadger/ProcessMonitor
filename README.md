# ProcessMonitor

**ProcessMonitor** is a lightweight Windows C++ application that allows you to monitor system performance in real-time. It tracks CPU usage as well as active processes, providing detailed information about each running process.


---

## Features

- Monitor CPU usage in real-time.
- Track active processes and their resource consumption.

---

### Prerequisites

- **C++17** compatible compiler (e.g., MSVC, GCC, Clang)
- **CMake** (optional, if you want to use a CMake build)
- Windows

### Build Instructions

#### Using Visual Studio (Windows)

1. Open the project folder in **Visual Studio**.
2. Select the build configuration: `Debug` or `Release`.
3. Press **Build Solution** (`Ctrl + Shift + B`).
4. The executable will be located in the `Debug` or `Release` folder.

#### Using CMake (Cross-platform)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
---

