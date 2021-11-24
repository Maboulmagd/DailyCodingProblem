//
// Created by Mo Aboulmagd on 10/19/21.
//

/*
 * This problem was asked by Stripe.
 * Given an array of integers, find the first missing positive integer in linear time and constant space.
 * In other words, find the lowest positive integer that does not exist in the array. The array can contain duplicates and negative numbers as well.
 * For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.
 * You can modify the input array in-place.
 */

#include "include.h"

/*
 * The first key observation is that negative integers and 0 don't matter, as well as duplicates.
 */

// Complexity Analysis:
// Time: O(2N) = O(N)
// Space: O(N)

// Let's first try to solve this question using extra space
int FirstMissingPositiveWithSet(vector<int> nums) {
    unordered_set<int> set(nums.cbegin(), nums.cend());
    const int nums_size = static_cast<int>(nums.size());

    for (int i = 1; i <= nums_size; ++i) {
        if (set.find(i) == set.cend()) {
            return i;
        }
    }

    return nums_size + 1;
}

// Complexity Analysis:
// Time: O(4N) = O(N)
// Space: O(1)

// Idea is to mimic the behavior of the set using the given input array to mark integers seen as visited...somehow...
int FirstMissingPositive(vector<int> nums) {
    const int nums_size = static_cast<int>(nums.size());

    // First, we want to check if 1 is missing, if it is, then simply return 1
    bool one_found = false;
    for (const auto num : nums) {
        if (num == 1) {
            one_found = true;
            break;
        }
    }
    if (!one_found) { return 1; }

    // Now, if 1 exists, then we can simply convert all elements <= 0 to a 1, since it won't matter.
    for (auto& num : nums) {
        if (num <= 0) {
            num = 1;
        }
    }

    // Now our entire array consists of positive integers, we can do some trickery with abs and -1 multiplication
    for (int i = 0; i < nums_size; ++i) {
        if (abs(nums[i]) > nums_size) { continue; }// Deal with numbers greater than our array size
        nums[abs(nums[i]) - 1] = abs(nums[abs(nums[i]) - 1]) * -1;// Always ensure it is negative
    }

    // Now that our array is marked up, we can see if a number at an index is not negative, then it means the number (index) is missing
    // If none are positive, then just return nums_size + 1
    for (int i = 0; i < nums_size; ++i) {
        if (nums[i] > 0) {// We've found the first missing positive integer
            return i + 1;
        }
    }

    return nums_size + 1;
}

TEST(FirstMissingPositive, SolvingWithSetTests) {
    ASSERT_EQ(FirstMissingPositiveWithSet({1, 2, 3, 4}), 5);
    ASSERT_EQ(FirstMissingPositiveWithSet({3, 2, 0, -3, 1, 5}), 4);
    ASSERT_EQ(FirstMissingPositiveWithSet({3, 2, 0, -3, 1}), 4);
    ASSERT_EQ(FirstMissingPositiveWithSet({-1, 1, 0, -3, 3}), 2);
    ASSERT_EQ(FirstMissingPositiveWithSet({2, 3, 0, 0}), 1);
    ASSERT_EQ(FirstMissingPositiveWithSet({1, 1}), 2);
    ASSERT_EQ(FirstMissingPositiveWithSet({1, 2, 3, 4, 5}), 6);
    ASSERT_EQ(FirstMissingPositiveWithSet({1, 1000}), 2);
    ASSERT_EQ(FirstMissingPositiveWithSet({0}), 1);
    ASSERT_EQ(FirstMissingPositiveWithSet({7, 8, 9, 11, 12}), 1);
    ASSERT_EQ(FirstMissingPositiveWithSet({1, 2, 0}), 3);

    // Basic test from problem description
    ASSERT_EQ(FirstMissingPositiveWithSet({3, 4, -1, 1}), 2);
}

TEST(FirstMissingPositive, Tests) {
    ASSERT_EQ(FirstMissingPositive({1, 2, 3, 4}), 5);
    ASSERT_EQ(FirstMissingPositive({3, 2, 0, -3, 1}), 4);
    ASSERT_EQ(FirstMissingPositive({-1, 1, 0, -3, 3}), 2);// -> {1,1,1,1,3} -> {-1,1,-1,1,3}
    ASSERT_EQ(FirstMissingPositive({2, 3, 0, 0}), 1);
    ASSERT_EQ(FirstMissingPositive({1, 1}), 2);
    ASSERT_EQ(FirstMissingPositive({1, 2, 3, 4, 5}), 6);
    ASSERT_EQ(FirstMissingPositive({1, 1000}), 2);
    ASSERT_EQ(FirstMissingPositive({0}), 1);
    ASSERT_EQ(FirstMissingPositive({7, 8, 9, 11, 12}), 1);
    ASSERT_EQ(FirstMissingPositive({1, 2, 0}), 3);

    // Basic test from problem description
    ASSERT_EQ(FirstMissingPositive({3, 4, -1, 1}), 2);// -> {3,4,1,1} -> {-3,4,-1,-1}
}