cmake_minimum_required(VERSION 3.0)

project(AdliBeta VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(AdliBeta src/main.cpp src/tokenizer.cpp src/astparser.cpp src/filereader.cpp src/astdebug.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_directories(${PROJECT_NAME} PUBLIC lib)