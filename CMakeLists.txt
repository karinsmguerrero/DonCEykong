cmake_minimum_required(VERSION 3.10)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled DK.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-2.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(untitled ${GTK3_LIBRARIES})
