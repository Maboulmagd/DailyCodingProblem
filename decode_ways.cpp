//
// Created by Mo Aboulmagd on 10/22/21.
//

/*
 * This problem was asked by Facebook.
 * Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count the number of ways it can be decoded.
 * For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'.
 * You can assume that the messages are decodable.
 * For example, '001' is not allowed.
 */

#include "include.h"

#include <gtest/gtest.h>

/*
 * Brute force way is to just use recursion (backtracking if you want to visualize the decoded strings), without memoizing any of the function calls.
 * It works correctly, but will time out for large test cases.
 */

// Complexity Analysis:
// Time: O(N) as that is roughly how many recursive calls we make, don't be fooled by the loop, it can be reduced to a clean recursive call with some checks.
// Space: O(N) for function calls placed on the stack as well as for the memo map.

void helper(const string& s, const vector<int>& char_value, int& ways, vector<string>& decoded_strings, string& curr_str) {
    if (s.length() == 0) {
        ++ways;
        decoded_strings.push_back(curr_str);
        return;
    }

    const int s_len = static_cast<int>(s.length());
    for (int i = 0; i < s_len; ++i) {
        const string& curr_substr = s.substr(0, i + 1);
        // Now are we able to decode curr_substr?

        // Handle zero's
        if (curr_substr[0] == '0') {
            break;
        }

        const int int_repr = stoi(curr_substr);
        if (int_repr > 26) { break; }

        curr_str += (char)char_value[int_repr - 1];
        //cout << "curr_str: " << curr_str << '\n';
        helper(s.substr(i + 1), char_value, ways, decoded_strings, curr_str);

        // Backtrack
        curr_str.pop_back();
    }
}

int helper2(const string& s, unordered_map<string, int>& memo) {
    if (s.length() <= 1) {
        if (s.length() == 1 && s[0] == '0') {
            return 0;
        }
        return 1;
    }
    else if (memo.find(s) != memo.cend()) {
        return memo[s];
    }

    const int s_len = static_cast<int>(s.length());
    for (int i = 0; i < s_len; ++i) {
        const string& curr_substr = s.substr(0, i + 1);
        // Now are we able to decode curr_substr?

        // Handle zero's
        if (curr_substr[0] == '0') {
            break;
        }

        const int int_repr = stoi(curr_substr);
        if (int_repr > 26) { break; }

        memo[s] += helper2(s.substr(i + 1), memo);
    }

    return memo[s];
}

int NumDecodings(string s) {
    unordered_map<string, int> memo;
    memo.reserve(s.length());

    return helper2(s, memo);

//    NOTE This code below will time out for large test cases
//    vector<int> char_value(26, 0);
//    for (int i = 1; i <= 26; ++i) {
//        char_value[i - 1] = 97 + i - 1;
//    }
//
//    // Follow up: deal with leading zeros?
//
//    int ways = 0;
//    vector<string> decoded_strings;
//    string curr_str;
//    curr_str.reserve(s.length());
//    helper(s, char_value, ways, decoded_strings, curr_str);
//
//    for (const auto& decoded_string : decoded_strings) {
//        cout << decoded_string << ' ';
//    }
//    if (decoded_strings.size() > 0) {
//        cout << '\n';
//    }
//
//    return ways;
}

// Demonstrate some basic assertions.
TEST(NumDecodings, BasicLCTests) {
    ASSERT_EQ(NumDecodings("12"), 2);
    ASSERT_EQ(NumDecodings("226"), 3);
    ASSERT_EQ(NumDecodings("0"), 0);
    ASSERT_EQ(NumDecodings("06"), 0);

    // Basic test from problem description
    ASSERT_EQ(NumDecodings("111"), 3);
}

TEST(NumDecodings, Tests) {
    ASSERT_EQ(NumDecodings("123456789"), 3);
    ASSERT_EQ(NumDecodings("01234506789"), 0);
    ASSERT_EQ(NumDecodings("1234506789"), 0);
    ASSERT_EQ(NumDecodings("2611055971756562"), 4);
    ASSERT_EQ(NumDecodings("111111111111111111111111111111111111111111111"), 1836311903);
}