aux_source_directory(declarations DECLARATIONS)
aux_source_directory(formal_parameters PARAMETERS)
aux_source_directory(statements STATEMENTS)
aux_source_directory(expressions EXPRESSIONS)
aux_source_directory(primary_expressions PRIMARY_EXPRESSIONS)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SOURCES)
add_library(
        AST
        ${DIR_SOURCES}

        ${DECLARATIONS}
        ${PARAMETERS}
        ${STATEMENTS}
        ${EXPRESSIONS}
        ${PRIMARY_EXPRESSIONS}
)

target_include_directories(
        AST
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)