minimum_cmake_required(VERSION 3.23)

project(SnakeSuite Languages CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------------------
# Dependency: Raylib (Fetched once for both targets)
# -------------------------------------------------------------
include(FecthContent)
FetchContent(
	raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
    	GIT_TAG        5.0

)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# -------------------------------------------------------------
# Target 1: 2D Classic Snake
# -------------------------------------------------------------

add_executable(Snake2D)
target_sources(Snake2D PRIVATE src/Snake2D.cpp)
target_link_libraries(Snake2D PRIVATE raylib)

# -------------------------------------------------------------
# Target 2: 3D Spatial Snake
# -------------------------------------------------------------
add_executable(Snake3D)
target_sources(Snake2D PRIVATE src/Snake3D.cpp)
target_link_libraries(Snake3D PRIVATE raylib)