cmake_minimum_required(VERSION 3.0)

project(AdliBeta VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

file(GLOB NODES src/nodes/*.cpp)
file(GLOB PARSER src/parser/*.cpp)

add_executable(${PROJECT_NAME}
        main.cpp
        src/filereader.cpp
        src/tokenizer.cpp
        src/node.cpp
        ${NODES}
        src/astparser.cpp
        ${PARSER}
        src/astdebug.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_directories(${PROJECT_NAME} PUBLIC lib)