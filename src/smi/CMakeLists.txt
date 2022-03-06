aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SOURCES)
add_library(SMI ${DIR_SOURCES})

target_include_directories(
        SMI
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include/smi
)
