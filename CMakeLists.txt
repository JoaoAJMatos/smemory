cmake_minimum_required(VERSION 3.15)
project(smart_ptr)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES src/smart_ptr.c)
set(HEADER_FILES include/smart_ptr.h)

add_library(smart_ptr STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(smart_ptr PUBLIC include)

install(TARGETS smart_ptr DESTINATION lib)
install(FILES include/smart_ptr.h DESTINATION include)

add_subdirectory(examples)