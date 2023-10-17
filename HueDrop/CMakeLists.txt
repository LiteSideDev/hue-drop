cmake_minimum_required(VERSION 3.22.1)

project(HueDrop)

find_package(CURL REQUIRED)
add_executable(${PROJECT_NAME} src/main.c)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
