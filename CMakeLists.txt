cmake_minimum_required(VERSION 3.31)
project(NavierStokesSolver)

set(CMAKE_CXX_STANDARD 20)

add_executable(NavierStokesSolver
        main.cpp
        grid.cpp
        coords.cpp
)