cmake_minimum_required(VERSION 3.10)
project(Boids)

# c++98
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/Boid.cpp
    src/Vector.cpp
    src/utils.cpp
    src/main.cpp
)

add_executable(boids ${SOURCES})

target_link_libraries(boids ${SDL2_LIBRARIES})