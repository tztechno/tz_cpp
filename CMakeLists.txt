cmake_minimum_required(VERSION 3.10)
project(BoostBeastExample)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.70 REQUIRED COMPONENTS system thread)

add_executable(BoostBeastExample main.cpp)
target_include_directories(BoostBeastExample PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(BoostBeastExample PRIVATE Boost::system Boost::thread)