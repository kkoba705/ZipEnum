cmake_minimum_required(VERSION 3.21)

set(version 1.2.0)

project(zip_enum VERSION ${version}
    DESCRIPTION "zip, enumerate for range-based for statement" 
    LANGUAGES CXX)

##################################
add_library(ZipEnum INTERFACE)

target_include_directories(ZipEnum INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set(CMAKE_CXX_STANDARD 17)

add_executable(sample sample/sample.cpp)
target_link_libraries(sample ZipEnum)


include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/ZipEnumConfigVersion.cmake
  VERSION ${version}
  COMPATIBILITY SameMajorVersion )

##################################

install(TARGETS ZipEnum
    EXPORT ZipEnumConfig
)

install(EXPORT ZipEnumConfig
    NAMESPACE ZipEnum::
    DESTINATION lib/cmake/ZipEnum
)

install(FILES
    ${CMAKE_SOURCE_DIR}/include/ZipEnum.hpp
    DESTINATION include
)

install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/ZipEnumConfigVersion.cmake
    DESTINATION lib/cmake/ZipEnum
)
