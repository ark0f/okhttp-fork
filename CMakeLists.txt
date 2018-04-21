cmake_minimum_required(VERSION 3.1)
project(okhttp-fork)

set(CMAKE_CXX_STANDARD 11)

# Compiler options
if(MSVC)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/W4")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")
endif()

# Options
option(BUILD_DTLS "Would compile DTLS" OFF)
if(BUILD_DTLS)
    add_definitions(-DOKHTTPFORK_DTLS)
endif()

enable_testing()
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

option(BUILD_EXAMPLES "Would compile examples" OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Common files
include_directories(include)
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${PROJECT_SOURCE_DIR} "include/*.hpp" "src/*.cpp" "src/*.hpp")

# Files for different systems
if(WIN32)
    file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "src/unix/*")
elseif(UNIX)
    file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "src/win32/*")
endif()
list(REMOVE_ITEM SOURCE_FILES ${FILES})

add_library(ohf ${SOURCE_FILES})

# Libraries
# OpenSSL
find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(ohf ${OPENSSL_LIBRARIES})

    if(WIN32)
        target_link_libraries(ohf crypt32)
    endif()
endif()

# Socket
if (WIN32)
    target_link_libraries(ohf ws2_32)
endif()

# Install
install(DIRECTORY "include/ohf/" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ohf")
install(TARGETS ohf
        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
