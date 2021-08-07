cmake_minimum_required(VERSION 3.20)
project(Mini_Java_Compiler)

set(CMAKE_CXX_STANDARD 17)

configure_file(graph.sh ${CMAKE_CURRENT_BINARY_DIR}/graph.sh COPYONLY)

# FLEX and BISON
find_package(BISON 3.5 REQUIRED)
find_package(FLEX 2.6 REQUIRED)

BISON_TARGET(
        MyParser
        src/parser.yy
        ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.hh
)

FLEX_TARGET(
        MyScanner
        src/lexer.ll
        ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)


aux_source_directory(src/ast/ ASTS)
aux_source_directory(src/st/ STS)

add_executable(
        compiler
        src/main.cpp
        ${ASTS}
        ${STS}
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)

target_link_libraries(compiler ${FLEX_LIBRARIES})

target_include_directories(
        compiler PRIVATE ${PROJECT_SOURCE_DIR}/include
)
