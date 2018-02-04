cmake_minimum_required(VERSION 2.8)
project(ohf_tests)

set(CMAKE_CXX_STANDARD 11)

include_directories("Catch2/include")
include_directories("../include")

file(GLOB_RECURSE CATCH RELATIVE ${PROJECT_SOURCE_DIR} "Catch2/include/*")
file(GLOB SOURCE_FILES RELAIVE ${PROJECT_SOURCE_DIR} "./*")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${CATCH})
target_link_libraries(${PROJECT_NAME} ohf)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
