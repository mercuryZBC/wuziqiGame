cmake_minimum_required(VERSION 3.0.0)
project(wuziqiServer VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Enable C++11
set(CMAKE_CXX_STANDARD 17)
# file(GLOB SOURCES *.cpp)
aux_source_directory(src SOURCES)
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(include)
set(mysqlclient /usr/local/mysql/lib/mysqlclient)
target_link_libraries(${PROJECT_NAME} mysqlclient) 


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lredis++ -lhiredis -pthread")
