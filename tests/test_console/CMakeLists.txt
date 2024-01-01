cmake_minimum_required(VERSION 3.7)
project(test_console)

set(CREAM_INCLUDE_DIRECTORY "../../include")

include_directories(${CREAM_INCLUDE_DIRECTORY}/)

#测试的源文件
file(GLOB TEST_CPP *.cpp)

#编译测试文件
add_executable(${PROJECT_NAME} ${TEST_CPP})
