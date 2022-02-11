add_subdirectory(declarations)
add_subdirectory(expressions)
add_subdirectory(formal_parameters)
add_subdirectory(primary_expressions)
add_subdirectory(statements)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SOURCES)
add_library(AST ${DIR_SOURCES})

target_link_libraries(
        AST
        AST_DECLARATIONS
        AST_EXPRESSIONS
        AST_FORMAL_PARAMETERS
        AST_PRIMARY_EXPRESSIONS
        AST_STATEMENTS
)

target_include_directories(
        AST
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)