//
// Created by Mo Aboulmagd on 11/23/21.
//

/*
 * This problem was asked by Google.
 *
 * The power set of a set is the set of all its subsets. Write a function that, given a set, generates its power set.
 *
 * For example, given the set {1, 2, 3}, it should return {{}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}}.
 * You may also use a list or array to represent a set.
 */

#include "include.h"

// Complexity Analysis:
// Time: O(N * 2^N) = O(2^N), as for each integer, we have 2 choices, either include or exclude it.
// Space: O(2^N) for the function call stack space.

void Helper(const vector<int>& nums, const int nums_size, vector<vector<int>>& res, vector<int>& sub_res, int n) {
    res.push_back(sub_res);
    if (n == nums_size) {
        return;
    }

    for (int i = n; i < nums_size; ++i) {
        sub_res.push_back(nums[i]);
        Helper(nums, nums_size, res, sub_res, i + 1);
        // Backtrack
        sub_res.pop_back();
    }
}

vector<vector<int>> Subsets(vector<int> nums) {
    const int nums_size = static_cast<int>(nums.size());
    vector<vector<int>> res;
    res.reserve(static_cast<int>(powf(2, nums_size)));

    vector<int> sub_res;
    sub_res.reserve(nums_size);

    Helper(nums, nums_size, res, sub_res, 0);

    return res;
}

TEST(Subsets, Test) {
    vector<vector<int>> res = { {}, {1}, {1,2}, {1,2,3}, {1,3}, {2}, {2,3}, {3}};
    vector<vector<int>> my_res = Subsets({1,2,3});

    ASSERT_THAT(my_res[0], ElementsAre());
    ASSERT_THAT(my_res[1], ElementsAre(1));
    ASSERT_THAT(my_res[2], ElementsAre(1,2));
    ASSERT_THAT(my_res[3], ElementsAre(1,2,3));
    ASSERT_THAT(my_res[4], ElementsAre(1,3));
    ASSERT_THAT(my_res[5], ElementsAre(2));
    ASSERT_THAT(my_res[6], ElementsAre(2,3));
    ASSERT_THAT(my_res[7], ElementsAre(3));
}