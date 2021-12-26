//
// Created by Mo Aboulmagd on 12/16/21.
//

/*
 * This problem was asked by Facebook.
 *
 * There is an N by M matrix of zeroes.
 * Given N and M, write a function to count the number of ways of starting at the top-left corner and getting to the bottom-right corner.
 * You can only move right or down.
 *
 * For example, given a 2 by 2 matrix, you should return 2, since there are two ways to get to the bottom-right:
 * Right, then down
 * Down, then right
 *
 * Given a 5 by 5 matrix, there are 70 ways to get to the bottom-right.
 */

#include "include.h"

// Complexity Analysis:
// Time: O(M * N)
// Space: O(M * N)

// Key observation is that we can simply cache/memoize the number of paths we can reach any given target cell.
int UniquePaths(int m, int n) {
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int c = m-1; c >= 0; --c) { dp[n-1][c] = 1; }

    for (int r = n-1; r >= 0; --r) { dp[r][m-1] = 1; }

    for (int r = n-2; r >= 0; --r)
    {
        for (int c = m-2; c >= 0; --c)
        {
            dp[r][c] = dp[r+1][c] + dp[r][c+1];
        }
    }

    return dp[0][0];
}

TEST(UniquePaths, Tests) {
    ASSERT_EQ(UniquePaths(3, 7), 28);
    ASSERT_EQ(UniquePaths(3, 2), 3);

    // Basic tests from problem description
    ASSERT_EQ(UniquePaths(2, 2), 2);
    ASSERT_EQ(UniquePaths(5, 5), 70);
}