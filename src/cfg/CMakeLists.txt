aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SOURCES)
add_library(CFG ${DIR_SOURCES})

target_include_directories(
        CFG
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include/cfg
)
