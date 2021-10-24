//
// Created by Mo Aboulmagd on 10/16/21.
//

/*
 * This problem was recently asked by Google.
 * Given a list of numbers and a number k, return whether any two numbers from the list add up to k.
 * For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.
 * Bonus: Can you do this in one pass?
 */

#include "include.h"

// TODO Try to move this to be part of include
#include <gtest/gtest.h>

/*
 * Brute force way is just a nested loop, iterating over all pairs, we can do better in just 1 pass if we use an unordered_set and
 * keep track of which integers we've seen so far, and on the current integer, check if we have seen remainder in the set. If so, we can
 * safely set found to true, and break.
 */

// Complexity Analysis:
// Time: O(N)
// Space: O(N)
bool TwoSum(vector<int> nums, int target) {
    bool found = false;

    unordered_set<int> set;
    set.reserve(nums.size());

    for (const int num : nums) {
        if (set.find(target - num) != set.cend()) {
            found = true;
            break;
        }
        set.insert(num);
    }

    return found;
}

// Demonstrate some basic assertions.
TEST(TwoSum, BasicLCTests) {
    ASSERT_EQ(TwoSum({2,7,11,15}, 9), true);
    ASSERT_EQ(TwoSum({3,2,4}, 6), true);
    ASSERT_EQ(TwoSum({3,3}, 6), true);

    // Basic test from problem description
    ASSERT_EQ(TwoSum({10,15,3,7}, 17), true);
}