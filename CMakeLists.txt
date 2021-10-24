cmake_minimum_required(VERSION 3.20)
project(DailyCodingProblem)

set(CMAKE_CXX_STANDARD 23)

#add_executable(DailyCodingProblem two_sum.cpp product_of_array_except_self.cpp)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/16f637fbf4ffc3f7a01fa4eceb7906634565242f.zip)

# TODO For Windows: Prevent overriding the parent project's compiler/linker settings, but how?
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        DailyCodingProblem
        two_sum.cpp
        product_of_array_except_self.cpp
        first_missing_positive.cpp
        serialize_and_deserialize_binary_tree.cpp
        car_and_cdr.cpp
        xor_linked_list.cpp
        decode_ways.cpp
        unival_tree.cpp)

add_subdirectory(include)
#target_link_libraries(DailyCodingProblem PUBLIC include)
target_link_libraries(DailyCodingProblem gtest_main gmock_main include)

include(GoogleTest)
gtest_discover_tests(DailyCodingProblem)


