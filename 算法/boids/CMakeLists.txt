cmake_minimum_required (VERSION 4.0)
 
project (boids)

add_executable(boids main.cpp)

target_link_libraries(boids sfml-graphics)
target_link_libraries(boids sfml-window)
target_link_libraries(boids sfml-system)