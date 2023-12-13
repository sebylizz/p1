cmake_minimum_required(VERSION 3.26)
project(p1 C)

set(CMAKE_C_STANDARD 11)

add_executable(main src/main.c src/doctor.c src/helpers.c sql/sqlite3.c)

enable_testing()

add_subdirectory(testing)