cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SolarSim)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(SolarSim
    src/main.cpp
    src/body.cpp
    src/renderer.cpp
)

# Include directories
target_include_directories(SolarSim PRIVATE include)

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