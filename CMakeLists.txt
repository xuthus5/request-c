cmake_minimum_required(VERSION 3.23)
project(request_c C)

set(CMAKE_C_STANDARD 11)

# curl
find_package(CURL REQUIRED)

if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    message(STATUS "Curl Found: ${CURL_VERSION_STRING} ${CURL_LIBRARIES} ${CURL_LINK_LIBRARIES}!")
else(CURL_FOUND)
    message(FATAL_ERROR "Could not find the CURL library and development files.")
endif()

add_executable(request_c
        request.c
        request.h
        request_test.c)

target_link_libraries(request_c ${CURL_LIBRARIES})