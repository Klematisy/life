cmake_minimum_required(VERSION 3.28.1)
project(vladlib)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)

include_directories(vladlib ${CMAKE_SOURCE_DIR}/deps/include/)
include_directories(vladlib ${CMAKE_SOURCE_DIR}/utils)

add_library(vladlib SHARED
            vladlib.c
            vmath.c
            utils/vertex_buffer_object.c
            utils/index_buffer_obj.c
            utils/vertex_array_object.c
            utils/shaders.c
            utils/glew.c
)

target_link_libraries(vladlib ${CMAKE_SOURCE_DIR}/deps/library/libglfw.3.4.dylib)
target_link_libraries(vladlib OpenGL::GL)

