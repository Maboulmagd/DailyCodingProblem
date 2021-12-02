//
// Created by Mo Aboulmagd on 12/1/21.
//

/*
 * This problem was asked by Facebook.
 *
 * Given a array of numbers representing the stock prices of a company in chronological order,
 * write a function that calculates the maximum profit you could have made from buying and selling that stock once.
 * You must buy before you can sell it.
 *
 * For example, given [9, 11, 8, 5, 7, 10], you should return 5, since you could buy the stock at 5 dollars and sell it at 10 dollars.
 */

#include "include.h"

// Complexity Analysis:
// Time: O(N)
// Space: O(1)

// Key idea is to just keep track of minimum price seen so far throughout our traversal of the array, and also to keep track of the
// maximum profit we can make, by selling the highest price we encounter and buying at the minimum price we've seen earlier.
int max_profit(vector<int> prices) {
    const size_t num_days = prices.size();

    int min_so_far = prices[0];
    int max_profit = 0;

    for (size_t day = 1; day < num_days; ++day) {
        max_profit = max(max_profit, prices[day] - min_so_far);
        min_so_far = min(min_so_far, prices[day]);
    }

    return max_profit;
}

TEST(BestTimeToBuyAndSellStock, Test) {
    ASSERT_EQ(max_profit({7,1,5,3,6,4}), 5);
    ASSERT_EQ(max_profit({7,6,4,3,1}), 0);
    ASSERT_EQ(max_profit({3,2,6,5,0,3}), 4);
    ASSERT_EQ(max_profit({1}), 0);

    // Test from problem description
    ASSERT_EQ(max_profit({9,11,8,5,7,10}), 5);
}