project(ohf_tests)

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

# Coverage
option(COVERAGE "Enable coverage reporter" OFF)
if(COVERAGE)
	file(DOWNLOAD
			https://raw.githubusercontent.com/bilke/cmake-modules/master/CodeCoverage.cmake
			${PROJECT_SOURCE_DIR}/CodeCoverage.cmake)
	include(CodeCoverage.cmake)

	if(GCC OR MINGW)
		append_coverage_compiler_flags()
	endif()

	setup_target_for_coverage(
			coverage
			${PROJECT_NAME}
			${PROJECT_NAME}
	)
endif()
