cmake_minimum_required(VERSION 3.0)
project(tile_output)

MESSAGE(STATUS "TILE BINARY dir: " ${${PROJECT_NAME}_BINARY_DIR})
MESSAGE(STATUS "TILE SOURCE dir: " ${${PROJECT_NAME}_SOURCE_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR} TILE_FILES)

message(STATUS "files: " ${TILE_FILES})

add_library(${PROJECT_NAME} STATIC ${TILE_FILES})

include_directories(
    ${PROJECT_SOURCE_DIR}
    ../render
    ../logger
    ../common
)

# link_directories()

target_link_libraries(
    ${PROJECT_NAME}
    render_output
)