cmake_minimum_required(VERSION 2.8)
project(OkHttpFork)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB_RECURSE INCLUDE RELATIVE "${PROJECT_SOURCE_DIR}" "include/*")
file(GLOB LIB RELATIVE "${PROJECT_SOURCE_DIR}" "lib/*") # namespace ohf

#[[file(GLOB LIB_APPEND RELATIVE "${PROJECT_SOURCE_DIR}" "lib/ssl/*") # namespace ohf::ssl
list(APPEND LIB ${LIB_APPEND})
file(GLOB LIb_APPEND RELATIVE "${PROJECT_SOURCE_DIR}" "lib/tcp/*") # namespace ohf::tcp
list(APPEND LIB ${LIB_APPEND})
file(GLOB LIB_APPEND RELATIVE "${PROJECT_SOURCE_DIR}" "lib/util/*")
list(APPEND LIB ${LIB_APPEND})]]
file(GLOB_RECURSE LIB RELATIVE "${PROJECT_SOURCE_DIR}" "lib/*")

# Files for different systems
if(WIN32)
    file(GLOB FILES RELATIVE "${PROJECT_SOURCE_DIR}" "lib/unix/*")
elseif(UNIX)
    file(GLOB FILES RELATIVE "${PROJECT_SOURCE_DIR}" "lib/win32/*")
endif()
list(REMOVE_ITEM LIB ${FILES})

option(BUILD_SHARED "Type of the library: static or shared" OFF)
if (BUILD_SHARED)
    add_library(ohf SHARED ${INCLUDE} ${LIB})
else()
    add_library(ohf STATIC ${INCLUDE} ${LIB})
endif()

# Libraries
# OpenSSL
find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(ohf ${OPENSSL_LIBRARIES})
endif()

# Socket
if (WIN32)
    target_link_libraries(ohf wsock32)
endif()

# Install
set_target_properties(ohf PROPERTIES PUBLIC_HEADER "${INCLUDE}")
install(TARGETS ohf
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Tests
option(TESTS "Unit-tests for the library using Catch2" ON)
if(TESTS)
    add_subdirectory(tests)
endif()
