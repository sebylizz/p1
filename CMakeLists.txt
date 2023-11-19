cmake_minimum_required(VERSION 3.26)
project(p1 C)

set(CMAKE_C_STANDARD 11)

include_directories(sql)
include_directories(src)

add_executable(p1
        sql/sqlite3.c
        sql/sqlite3.h
        src/output.c
        src/output.h)
