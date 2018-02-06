project(ohf_tests)

# Coverage
option(COVERAGE "Enable coverage reporter" OFF)
if(COVERAGE)
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/coveralls-cmake/cmake")

	include(Coveralls)

	coveralls_turn_on_coverage()
	coveralls_setup(${SOURCE_FILES} ON "${PROJECT_SOURCE_DIR}/coveralls-cmake/cmake")
endif()

# Files
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Catch2/CMakeLists.txt")
	message(FATAL_ERROR "Catch2 submodule not found")
endif()

set(CATCH_INCLUDE_DIR "Catch2/include")

include_directories(${CATCH_INCLUDE_DIR})
include_directories("../include")

file(GLOB_RECURSE CATCH RELATIVE ${PROJECT_SOURCE_DIR} "${CATCH_INCLUDE_DIR}/*")
file(GLOB SOURCE_FILES RELATIVE ${PROJECT_SOURCE_DIR} "./*")

# Target
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${CATCH})
target_link_libraries(${PROJECT_NAME} ohf)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
