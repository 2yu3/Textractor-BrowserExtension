cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0037 OLD)

add_compile_options(
  /std:c++17
  /MP
  /wd4018 # signed/unsigned msismatch
  /DVERSION="${VERSION}"
  /DUNICODE # config.pri
  /D_UNICODE
)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(CMAKE_FINAL_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/builds/${CMAKE_BUILD_TYPE}_x64)
  link_directories(x64libs)
else()
  set(CMAKE_FINAL_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/builds/${CMAKE_BUILD_TYPE}_x86)
  link_directories(x86libs)
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_FINAL_OUTPUT_DIRECTORY}>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_FINAL_OUTPUT_DIRECTORY}>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_FINAL_OUTPUT_DIRECTORY}>)

find_package(Qt5 COMPONENTS Core Widgets WebSockets REQUIRED)
add_library(BrowserWebSocket MODULE Extension.cpp ExtensionImpl.cpp)
target_link_libraries(BrowserWebSocket Qt5::WebSockets Qt5::Core)
add_custom_command(
    TARGET BrowserWebSocket POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::WebSockets>
        $<TARGET_FILE_DIR:BrowserWebSocket>
)
add_custom_command(
    TARGET BrowserWebSocket POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Network>
        $<TARGET_FILE_DIR:BrowserWebSocket>
)