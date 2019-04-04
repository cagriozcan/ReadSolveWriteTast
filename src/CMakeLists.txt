cmake_minimum_required(VERSION 3.13)
project(src)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-m64)

include_directories(.)
include_directories(includes)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
set(BOOST_LIBRARYDIR /boost/lib)

add_executable(src
        CMakeLists.txt
        File_Reader.cpp
        File_Reader.h
        PuzzleSolver.cpp
        PuzzleSolver.h
        FileWriter.cpp
        FileWriter.h
        main.cpp)

TARGET_LINK_LIBRARIES( src LINK_PUBLIC ${Boost_LIBRARIES} )