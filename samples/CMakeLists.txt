cmake_minimum_required(VERSION 3.1)
project(ohf_samples)

include_directories("../include")

file(GLOB EXAMPLES RELATIVE ${PROJECT_SOURCE_DIR} "*.cpp")
foreach(item ${EXAMPLES})
	string(REPLACE ".cpp" "" name ${item})
	add_executable(${name} ${item})
	target_link_libraries(${name} ohf)
endforeach()
