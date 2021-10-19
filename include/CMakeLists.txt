project(include)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(include INTERFACE "include.h")
target_include_directories(include INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})