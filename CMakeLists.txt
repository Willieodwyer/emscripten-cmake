# emsdk
configure_file(Emscripten.txt.in emsdk-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/emsdk-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/emsdk-download" )

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_BINARY_DIR}/emsdk-src/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" CACHE PATH "toolchain file")

set(project "hello")
project(${project})
cmake_minimum_required(VERSION 3.12)

set(src 
   src/main.cpp
 )

include_directories(inc)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_C_COMPILER emcc)
    set(CMAKE_CPP_COMPILER em++)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

# specify the project
add_executable(${project} ${src})
set_target_properties(${project} PROPERTIES LINK_FLAGS "-s WASM=1 -s EXPORT_ALL=1")

