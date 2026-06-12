cmake_minimum_required(VERSION 3.10)
project(GFX VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c"
)

add_executable(GFX ${SOURCES})

target_include_directories(GFX PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

find_package(glfw3 REQUIRED)

target_link_libraries(GFX PRIVATE glfw)

if (WIN32)
    target_link_libraries(GFX PRIVATE opengl32)
else()
    target_link_libraries(GFX PRIVATE GL)
endif()