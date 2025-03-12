cmake_minimum_required(VERSION 3.15)

# Setup vcpkg script with CMake (note: should be placed before project() call)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
#include(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
#set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-osx")

project(Example)

set(CMAKE_CXX_STANDARD 20)

# Vcpkg 경로 설정 (플랫폼에 맞게 변경)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(VCPKG_INSTALLED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/vcpkg_installed/x64-windows)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(VCPKG_INSTALLED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/vcpkg_installed/x64-linux)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(VCPKG_INSTALLED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/vcpkg_installed/x64-osx)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

# Include 경로 추가
include_directories(
    ${VCPKG_INSTALLED_DIR}/include
    ${VCPKG_INSTALLED_DIR}/include/uWebSockets
    ${VCPKG_INSTALLED_DIR}/include/usockets
    ${VCPKG_INSTALLED_DIR}/include/zlib
    ${VCPKG_INSTALLED_DIR}/include/libuv
)

add_library(libuv STATIC IMPORTED)
set_target_properties(libuv PROPERTIES
    IMPORTED_LOCATION ${VCPKG_INSTALLED_DIR}/lib/libuv.a
)

# 라이브러리 추가
add_library(usockets STATIC IMPORTED)
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set_target_properties(usockets PROPERTIES
        IMPORTED_LOCATION ${VCPKG_INSTALLED_DIR}/lib/libusockets.a
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set_target_properties(usockets PROPERTIES
        IMPORTED_LOCATION ${VCPKG_INSTALLED_DIR}/lib/libuSockets.a
    )
endif()


add_library(zlib STATIC IMPORTED)
set_target_properties(zlib PROPERTIES
    IMPORTED_LOCATION ${VCPKG_INSTALLED_DIR}/lib/libz.a
)


# Specify the triplet
# set(VCPKG_TARGET_TRIPLET "x64-osx" CACHE STRING "Vcpkg target triplet")

# vcpkg dependencies
find_package(fmt CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

# Ensure include directories are set up
# include_directories(${uWebSockets_INCLUDE_DIRS})

add_subdirectory(lib)
add_subdirectory(app)