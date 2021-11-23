//
// Created by Mo Aboulmagd on 11/20/21.
//

/*
 * This problem was asked by Google.
 *
 * Given an array of strictly the characters 'R', 'G', and 'B',
 * segregate the values of the array so that all the Rs come first, the Gs come second, and the Bs come last.
 * You can only swap elements of the array.
 *
 * Do this in linear time and in-place.
 * For example, given the array ['G', 'B', 'R', 'R', 'B', 'R', 'G'], it should become ['R', 'R', 'R', 'G', 'G', 'B', 'B'].
 */

#include "include.h"

// Complexity Analysis:
// Time: O(N)
// Space: O(1)

// The key ideas is that all colors < zeros_ptr are 0 and all colors > twos_ptr are 2
vector<int> DutchNationalFlag(vector<int> colors) {
    const int colors_size = static_cast<int>(colors.size());

    int zeros_ptr = 0;
    int twos_ptr = colors_size - 1;

    for (int i = 0; i <= twos_ptr; ) {
        if (colors[i] == 2) {
            swap(colors[i], colors[twos_ptr]);
            --twos_ptr;
        }
        else if (colors[i] == 0) {
            swap(colors[i], colors[zeros_ptr]);
            ++zeros_ptr;
            ++i;
        }
        else {
            ++i;
        }
    }

    return colors;
}

TEST(DutchNationalFlagTests, Tests) {
    // Basic LeetCode tests
    ASSERT_THAT(DutchNationalFlag({ 2,0,2,1,1,0 }), ElementsAre(0,0,1,1,2,2));
    ASSERT_THAT(DutchNationalFlag({ 2,0,1 }), ElementsAre(0,1,2));
    ASSERT_THAT(DutchNationalFlag({ 0 }), ElementsAre(0));
    ASSERT_THAT(DutchNationalFlag({ 1 }), ElementsAre(1));

    ASSERT_THAT(DutchNationalFlag({ 0,1,0 }), ElementsAre(0,0,1));
    ASSERT_THAT(DutchNationalFlag({ 2,2,0,1,2,0 }), ElementsAre(0,0,1,2,2,2));
    ASSERT_THAT(DutchNationalFlag({ 1,0,2,1,0 }), ElementsAre(0,0,1,1,2));
}