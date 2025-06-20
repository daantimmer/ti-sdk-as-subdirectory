find_package(DeviceCC23X0R5 REQUIRED)

add_executable(target)

target_include_directories(target PUBLIC
    .
)

target_link_libraries(target PRIVATE
    Device::cc23x0r5
    Drivers::drivers_cc23x0r5
    NoRtos::nortos_cc23x0r5
)

target_sources(target PRIVATE
    Atomic.cpp
    Main.cpp
    Ccfg.c
)

target_link_options(target PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/cc23x0r5.cmd"
)

set(CRC_TOOL "${CMAKE_SOURCE_DIR}/external/simplelink-lowpower-f3-sdk-lpf3-8.40.02.01/tools/common/crc_tool/crc_tool")

add_custom_command(
    TARGET target
    POST_BUILD
    COMMAND ${CRC_TOOL} patch-image --elf "$<TARGET_FILE:target>" --output "$<TARGET_FILE:target>" --symbol-prefix ti_utils_build_GenMap_sym_CRC
)
