cmake_minimum_required(VERSION 3.2)
project(BroadcastC__11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(BroadcastC__11 ${SOURCE_FILES} PaqueteDatagrama.cpp SocketDatagrama.cpp)