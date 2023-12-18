cmake_minimum_required(VERSION 3.26)
project(p1 C)

set(CMAKE_C_STANDARD 11)

include_directories(sql)
include_directories(src)

add_executable(input src/input.c src/doctor.c src/helpers.c sql/sqlite3.c)