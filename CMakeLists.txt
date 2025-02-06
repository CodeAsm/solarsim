cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SolarSim)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    src/main.cpp
    src/simulation.cpp
    src/renderer.cpp
)

# Set OpenGL preference to GLVND
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

# Find and include GLFW using pkg-config
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW3 REQUIRED glfw3)
include_directories(${GLFW3_INCLUDE_DIRS})

# Find and include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Add the executable
add_executable(SolarSim ${SOURCES})

# Include directories
target_include_directories(SolarSim PRIVATE include)

# Link libraries
target_link_libraries(SolarSim ${GLFW3_LIBRARIES} ${OPENGL_LIBRARIES})

# Add shaders as resources
set(SHADERS
    shaders/vertex.glsl
    shaders/fragment.glsl
)

# Copy shaders to the build directory
foreach(SHADER ${SHADERS})
    add_custom_command(
        TARGET SolarSim POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/${SHADER}
                ${CMAKE_BINARY_DIR}/${SHADER}
    )
endforeach()