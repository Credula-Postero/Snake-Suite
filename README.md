\# Modern Snake Suite (2D \& 3D)



A multi-target arcade engine demonstrating the evolution from a classic 2D grid-based implementation to a 3D spatial simulation, built with \*\*Modern C++ (C++20)\*\* and \*\*Raylib\*\*.



\---



\## Architecture \& Technical Highlights



\- \*\*Data Structures \& Optimization:\*\*

&#x20;   - Powered by `std::deque<Vector2>` (2D) and `std::deque<Vector3>` (3D) to guarantee $O(1)$ amortized complexity for head progression and tail pruning.

&#x20;   - Compile-time type safety via standard `static\_cast`.

\- \*\*Spatial Systems:\*\*

&#x20;   - \*\*2D Mode:\*\* Strict 25px discrete grid coordinates and frame-speed scaling logic.

&#x20;   - \*\*3D Mode:\*\* Matrix transformations, perspective camera projections (`CAMERA\_PERSPECTIVE`), 3D axis boundaries, and bounding box/wireframe rendering.

\- \*\*Unified Build Pipeline:\*\*

&#x20;   - Single \*\*CMake (v3.23+)\*\* root configuration managing both targets.

&#x20;   - Zero external setup: leverages `FetchContent` to compile Raylib 5.0 on the fly across Windows, Linux, and macOS.



\---



\## Project Structure



```

Snake-Suite/

├── CMakeLists.txt     # Root CMake building both targets

├── README.md          # Engineering overview

└── src/

&#x20;   ├── Snake2D.cpp    # Classic 2D implementation

&#x20;   └── Snake3D.cpp    # 3D spatial implementation

```

