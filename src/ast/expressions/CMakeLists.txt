aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SOURCES)
add_library(AST_EXPRESSIONS ${DIR_SOURCES})

target_link_libraries(
        AST_EXPRESSIONS
        CFG
)

target_include_directories(
        AST_EXPRESSIONS
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)