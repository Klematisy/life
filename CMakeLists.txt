cmake_minimum_required(VERSION 3.28)
project(live C)

set(CMAKE_C_STANDARD 11)

add_executable(live src/main.c
                    src/game.c)

target_link_libraries(live PRIVATE ${CMAKE_SOURCE_DIR}/src/vladlib/build/libvladlib.dylib)