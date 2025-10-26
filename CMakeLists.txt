cmake_minimum_required(VERSION 3.28)
project(NavierStokesSolver)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

add_executable(NavierStokesSolver main.cpp grid.cpp coords.cpp)
target_link_libraries(NavierStokesSolver PRIVATE raylib)
