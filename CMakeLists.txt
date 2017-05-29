cmake_minimum_required(VERSION 3.6)
project(main)

find_package(CGAL REQUIRED COMPONENTS)
include(${CGAL_USE_FILE})

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp mst.h mst.cpp edge.h edge.cpp k_mst.h k_mst.cpp)

target_link_libraries(main ${CGAL_LIBRARIES})
