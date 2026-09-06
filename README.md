# README

# README

# Modern Snake Suite (2D & 3D)

A multi-target arcade engine demonstrating the evolution from a classic 2D grid-based implementation to a 3D spatial simulation, built with **Modern C++ (C++20)** and **Raylib**.

---

## Architecture & Technical Highlights

- **Data Structures & Optimization:**
    - Powered by `std::deque<Vector2>` (2D) and `std::deque<Vector3>` (3D) to guarantee $O(1)$ amortized complexity for head progression and tail pruning.
    - Compile-time type safety via standard `static_cast`.
- **Spatial Systems:**
    - **2D Mode:** Strict 25px discrete grid coordinates and frame-speed scaling logic.
    - **3D Mode:** Matrix transformations, perspective camera projections (`CAMERA_PERSPECTIVE`), 3D axis boundaries, and bounding box/wireframe rendering.
- **Unified Build Pipeline:**
    - Single **CMake (v3.23+)** root configuration managing both targets.
    - Zero external setup: leverages `FetchContent` to compile Raylib 5.0 on the fly across Windows, Linux, and macOS.

---

## Project Structure

```
Snake-Suite/
├── CMakeLists.txt     # Root CMake building both targets
├── README.md          # Engineering overview
└── src/
    ├── Snake2D.cpp    # Classic 2D implementation
    └── Snake3D.cpp    # 3D spatial implementation
```

---

## Build & Execution

### Prerequisites

- C++20-compliant compiler (MSVC 2019+, GCC 10+, Clang 11+)
- CMake 3.23+
- Git

### Build Instructions

```bash
# 1. Clone the repository
git clone [<https://github.com/MahmoudNazmi/Snake-Suite.git>](<https://github.com/MahmoudNazmi/Snake-Suite.git>)
cd Snake-Suite

# 2. Generate build cache
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 3. Build both executables
cmake --build build --config Release
```

## Running Games

- **2D Snake:** `./build/Snake2D` (Windows: `.\build\Release\Snake2D.exe`)
- **3D Snake:** `./build/3DSnakeGame` (Windows: `.\build\Release\3DSnakeGame.exe`)

## Controls

> 
> 
> 
> 
> | **Action** | **2D Classic** | **3D Spatial** |
> | --- | --- | --- |
> | **Movement** | Arrow Keys (`UP`, `DOWN`, `LEFT`, `RIGHT`) | Arrow Keys (`X` / `Z` axes) |
> | **Restart** | `SPACE` | `SPACE` |
> | **Exit** | `ESC` | `ESC` |

## Author

Credula-Postero