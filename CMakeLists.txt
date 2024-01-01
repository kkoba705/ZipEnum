cmake_minimum_required(VERSION 3.21)

project(zip_enum VERSION 1.1.0 
    DESCRIPTION "zip, enumerate for range-based for statement" 
    LANGUAGES CXX)

##################################
add_library(ZipEnum INTERFACE)

target_include_directories(ZipEnum INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/ZipEnumVersion.cmake
  VERSION 1.1.0
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
    ${CMAKE_CURRENT_BINARY_DIR}/ZipEnumVersion.cmake
    DESTINATION lib/cmake/ZipEnum
)
