cmake_minimum_required(VERSION 3.21)

set(TICLANG_ARMCOMPILER $ENV{TICLANG_ARMCOMPILER})
set(IAR_ARMCOMPILER $ENV{IAR_ARMCOMPILER})
set(GCC_ARMCOMPILER $ENV{GCC_ARMCOMPILER})

# Only look in local folders for components and platforms
set(CMAKE_ONLY_WRAPPER_COMPONENTS 1)
set(CMAKE_ONLY_LOCAL_PLATFORMS 1)

# Setup the CMake build environment
# set(CMAKE_COMMON_INSTALL_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_COMMON_INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR})
include(source/cmake/scripts/cmake-common/Configure.cmake)
project(coresdk LANGUAGES)

# Include directories that participate in the library build
add_subdirectory(kernel/freertos)
add_subdirectory(kernel/nortos)
add_subdirectory(source/third_party/ecc)
add_subdirectory(source/third_party/fatfs)
add_subdirectory(source/third_party/hsmddk)
add_subdirectory(source/third_party/spiffs)
add_subdirectory(source/ti/devices/cc23x0r2)
add_subdirectory(source/ti/devices/cc23x0r5)
add_subdirectory(source/ti/devices/cc27xx)
add_subdirectory(source/ti/display)
add_subdirectory(source/ti/drivers)
add_subdirectory(source/ti/log)
add_subdirectory(source/ti/utils)
add_subdirectory(source/ti/utils/json)
