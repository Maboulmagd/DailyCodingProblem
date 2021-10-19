//
// Created by Mo Aboulmagd on 10/18/21.
//

#include "include.h"

// TODO Try to move these to be part of the include header-only file
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;

/*
 * This problem was asked by Uber.
 * Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.
 * For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].
 * Follow-up: what if you can't use division?
 */

/*
 * The key idea to solve this without using division, is to store the multiplication values from right to left, and then iterate
 * over the array again, but this time from the more natural left to right, while keeping track of the total product.
 */

// Complexity Analysis:
// Time: O(2 * N) = O(N)
// Space: O(1)
vector<int> ProductOfArrayExceptSelf(const vector<int>& nums) {
    const int nums_size = static_cast<int>(nums.size());
    vector<int> result(nums_size, 1);

    // Let's assume we are working with {-1,1,0,-3,3}
    for (int i = nums_size - 2; i >= 0; --i) {
        result[i] *= (nums[i + 1] * result[i+1]);
    }
    // Now result should look like this: {0,0,-9,3,1}

    // Now maintain a running product from left to right, and multiply number at each index by the running product while updating the running product.
    int running_product = nums[0];
    for (int i = 1; i < nums_size; ++i) {
        result[i] *= running_product;
        running_product *= nums[i];
    }

    return result;
}

// Demonstrate some basic assertions.
TEST(ProductOfArrayExceptSelf, BasicLCTests) {
    ASSERT_THAT(ProductOfArrayExceptSelf({1,2,3,4}), ElementsAre(24,12,8,6));
    ASSERT_THAT(ProductOfArrayExceptSelf({-1,1,0,-3,3}), ElementsAre(0,0,9,0,0));
    ASSERT_THAT(ProductOfArrayExceptSelf({2,3,0,0}), ElementsAre(0,0,0,0));
    ASSERT_THAT(ProductOfArrayExceptSelf({1,1}), ElementsAre(1,1));

    // Basic test from problem description
    ASSERT_THAT(ProductOfArrayExceptSelf({1,2,3,4,5}), ElementsAre(120,60,40,30,24));
}