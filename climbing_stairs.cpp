//
// Created by Mo Aboulmagd on 10/27/21.
//

/*
 *This problem was asked by Amazon.
 * There exists a staircase with N steps, and you can climb up either 1 or 2 steps at a time.
 * Given N, write a function that returns the number of unique ways you can climb the staircase. The order of the steps matters.
 * For example, if N is 4, then there are 5 unique ways:

    1, 1, 1, 1
    2, 1, 1
    1, 2, 1
    1, 1, 2
    2, 2

 * What if, instead of being able to climb 1 or 2 steps at a time, you could climb any number from a set of positive integers X?
 * For example, if X = {1, 3, 5}, you could climb 1, 3, or 5 steps at a time.
 */

#include "include.h"

int helper(const int n, const vector<int>& steps_set, unordered_map<int, int>& memo) {
    if (n == 0 || n == 1) {
        return 1;
    }
    else if (memo.find(n) != memo.cend()) {
        return memo[n];
    }

    for (const int step : steps_set) {
        if (n < step) { continue; }// Can't use this step
        memo[n] += helper(n - step, steps_set, memo);
    }

    return memo[n];
}

int ClimbingStairs(int n, vector<int> steps_set) {
    unordered_map<int, int> memo;;

    return helper(n, steps_set, memo);
}

TEST(ClimbingStairs, BasicTests) {
    ASSERT_EQ(ClimbingStairs(2, {1, 2}), 2);
    ASSERT_EQ(ClimbingStairs(3, {1, 2}), 3);
    ASSERT_EQ(ClimbingStairs(10, {1, 2}), 89);
    ASSERT_EQ(ClimbingStairs(45, {1, 2}), 1836311903);

    // Basic test from problem description
    ASSERT_EQ(ClimbingStairs(4, {1, 2}), 5);
}

TEST(ClimbingStairs, Tests) {
    ASSERT_EQ(ClimbingStairs(1, {1, 3, 5}), 1);
    ASSERT_EQ(ClimbingStairs(2, {1, 3, 5}), 1);
    ASSERT_EQ(ClimbingStairs(3, {1, 3, 5}), 2);
    ASSERT_EQ(ClimbingStairs(4, {1, 3, 5}), 3);
    ASSERT_EQ(ClimbingStairs(5, {1, 3, 5}), 5);
    ASSERT_EQ(ClimbingStairs(6, {1, 3, 5}), 8);
}
