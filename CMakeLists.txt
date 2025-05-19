cmake_minimum_required(VERSION 3.28)
project(Tetris VERSION 1.0 LANGUAGES CXX)

# specify C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# use to export compiler commands for intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# gather all of the source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(tetris ${SOURCES})

# include the include directory which contains all the header files
target_include_directories(tetris PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_compile_features(tetris PRIVATE cxx_std_17)
target_link_libraries(tetris PRIVATE SFML::Graphics)
