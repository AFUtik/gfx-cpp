cmake_minimum_required(VERSION 4.1.2)
project(GFX VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c"
)

add_executable(GFX ${SOURCES})

target_precompile_headers(GFX PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp>"
)

target_include_directories(GFX PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

find_package(Vulkan REQUIRED)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(GFX PRIVATE 
    glfw
    Vulkan::Vulkan
    GPUOpen::VulkanMemoryAllocator
    glm::glm)

if (WIN32)
    target_link_libraries(GFX PRIVATE opengl32)
else()
    target_link_libraries(GFX PRIVATE GL)
endif()
