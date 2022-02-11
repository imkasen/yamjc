aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SOURCES)
add_library(AST_FORMAL_PARAMETERS ${DIR_SOURCES})

target_include_directories(
        AST_FORMAL_PARAMETERS
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include/
)