project(ohf_tests)

# Catch2
set(CATCH_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Catch2/include")
if(NOT EXISTS ${CATCH_INCLUDE_DIR})
	message(FATAL_ERROR "Catch2 submodule not found")
endif()

include_directories(${CATCH_INCLUDE_DIR})
file(GLOB_RECURSE CATCH ${PROJECT_SOURCE_DIR} "${CATCH_INCLUDE_DIR}/*")

# Tests
include_directories("../include")
file(GLOB TESTS_FILES ${PROJECT_SOURCE_DIR} "*.hpp" "*.cpp")

# Target
add_executable(${PROJECT_NAME} ${TESTS_FILES} ${CATCH})
target_link_libraries(${PROJECT_NAME} ohf)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
