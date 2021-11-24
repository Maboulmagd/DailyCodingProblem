cmake_minimum_required(VERSION 3.20)
project(DailyCodingProblem)

set(CMAKE_CXX_STANDARD 23)

add_executable(DailyCodingProblem
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
        sliding_window_maximum.cpp
        paint_house.cpp
        intersection_of_two_linked_lists.cpp
        meeting_rooms.cpp
        word_break_II.cpp
        shortest_possible_path_in_a_maze.cpp
        lockable_tree.cpp
        regular_expression_matching.cpp
        remove_nth_node_from_end_of_list.cpp
        valid_parentheses.cpp
        text_justification.cpp
        encode_and_decode_string.cpp
        trapping_rain_water.cpp
        edit_distance.cpp
        currency_arbitrage.cpp
        find_median_from_data_stream.cpp
        minimum_insertion_steps_to_make_a_string_palindrome.cpp
        dutch_national_flag.cpp
        second_maximum_node_in_a_bst.cpp
        subsets.cpp
        n_queens.cpp
        game_of_life.cpp)

add_subdirectory(include)
target_link_libraries(DailyCodingProblem include)

#include(GoogleTest)
#gtest_discover_tests(DailyCodingProblem)


