cmake_minimum_required(VERSION 3.15)
project(Mini_Java_Compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed!")
endif()

configure_file(graph.sh ${PROJECT_BINARY_DIR}/graph.sh COPYONLY)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
    set(
            CMAKE_BUILD_TYPE RelWithDebInfo
            CACHE
            STRING "Set default build type: RelWithDebInfo"
            FORCE
    )
    set_property(
            CACHE
            CMAKE_BUILD_TYPE
            PROPERTY
            STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
    )
endif()

# FLEX and BISON
find_package(BISON 3.5 REQUIRED)
find_package(FLEX 2.6 REQUIRED)

BISON_TARGET(
        MyParser
        src/parser.yy
        ${PROJECT_BINARY_DIR}/parser.cpp
        DEFINES_FILE ${PROJECT_BINARY_DIR}/parser.tab.hh
)

FLEX_TARGET(
        MyScanner
        src/lexer.ll
        ${PROJECT_BINARY_DIR}/lexer.cpp
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
        compiler
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_BINARY_DIR}
)
