cmake_minimum_required(VERSION 3.6)
project(mpi_coursework)

set(CMAKE_CXX_STANDARD 11)

add_executable(mpi_coursework main.cpp Utils.h)
include_directories(/usr/include/mpich/mpi.h)

set(CMAKE_C_COMPILER "/usr/bin/mpicc")
set(CMAKE_CXX_COMPILER "/usr/bin/mpic++")