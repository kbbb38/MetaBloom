cmake_minimum_required(VERSION 3.13)
project(MetaBloom LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(METABLOOM_DEBUG "Enable debug build with extra diagnostics" OFF)

if(METABLOOM_DEBUG)
    message(STATUS "Configuring debug build")
    set(FLAGS "-O0 -g -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -DDEBUG")
else()
    message(STATUS "Configuring deployment build")
    set(FLAGS "-O3 -DNDEBUG")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")
set(SOURCE_FILES MetaBloom.cpp src/BitVector.h src/Config.h src/IBFIndex.h src/MspReader.h src/MspReader.cpp src/Spectrum.h)

include_directories(include)

add_executable(MetaBloom ${SOURCE_FILES})