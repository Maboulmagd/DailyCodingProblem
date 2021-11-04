cmake_minimum_required(VERSION 3.20)
project(DailyCodingProblem)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        DailyCodingProblem
        two_sum.cpp
        product_of_array_except_self.cpp
        first_missing_positive.cpp
        serialize_and_deserialize_binary_tree.cpp
        car_and_cdr.cpp
        xor_linked_list.cpp
        decode_ways.cpp
        unival_tree.cpp
        house_robber.cpp
        job_scheduler.cpp
        autocomplete.cpp
        climbing_stairs.cpp
        longest_substr_at_most_k_distinct_characters.cpp
        estimate_pi.cpp
        random_number_from_stream.cpp
        last_ith_element_from_log.cpp
        longest_absolute_file_path.cpp
        sliding_window_maximum.cpp paint_house.cpp)

add_subdirectory(include)
target_link_libraries(DailyCodingProblem include)

#include(GoogleTest)
#gtest_discover_tests(DailyCodingProblem)


