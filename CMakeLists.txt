cmake_minimum_required(VERSION 3.6)
project(main)

find_package(CGAL REQUIRED COMPONENTS)
include(${CGAL_USE_FILE})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenGL -O3")

add_executable(main main.cpp mst.h mst.cpp edge.h edge.cpp generate.h generate.cpp)

target_link_libraries(main ${CGAL_LIBRARIES})
target_link_libraries(main glfw glew)
