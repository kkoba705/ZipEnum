cmake_minimum_required(VERSION 3.21)
set(exename "sample")
project(${exename} CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(ZipEnum REQUIRED)

add_executable(${exename} ${exename}.cpp)
target_link_libraries(${exename} ZipEnum::ZipEnum)
