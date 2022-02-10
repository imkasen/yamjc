aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SOURCES)
add_library(ST ${DIR_SOURCES})

target_include_directories(
        ST
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include/st
)
