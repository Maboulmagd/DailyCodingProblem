//
// Created by Mo Aboulmagd on 11/11/21.
//

/*
 * This problem was asked by Facebook.
 * Given a string of round, curly, and square open and closing brackets, return whether the brackets are balanced (well-formed).
 * For example, given the string "([])[]({})", you should return true.
 * Given the string "([)]" or "((()", you should return false.
 */

#include "include.h"

// Complexity Analysis:
// Time: O(N) as we are iterating over all characters in the string (in the worst case scenario)
// Space: O(N) as we are using a stack container, and in the worst case scenario, our entire string is composed of open parentheses.

bool ValidParentheses(string s) {
    const int s_len = static_cast<int>(s.length());
    bool res = true;
    stack<char> stck;

    for (int i = 0; res && i < s_len; ++i) {
        const char& curr_char = s[i];
        if (curr_char == '(' || curr_char == '[' || curr_char == '{') {
            stck.push(curr_char);
        }
        else { // If curr_char is a closing parentheses
            if (stck.empty()) {
                res = false;
            }
            else {
                const char last_paren = stck.top();
                stck.pop();

                switch (last_paren) {
                    case '(': {
                        res = curr_char == ')';
                        break;
                    }
                    case '[': {
                        res = curr_char == ']';
                        break;
                    }
                    case '{': {
                        res = curr_char == '}';
                        break;
                    }
                    default:
                        res = false;
                        break;
                }
            }
        }
    }

    // Lastly need to check that the stack is empty (no open parentheses still in it)
    if (!stck.empty()) { res = false; }
    return res;
}

TEST(ValidParentheses, ValidParenthesesTests) {
    ASSERT_TRUE(ValidParentheses("()"));
    ASSERT_TRUE(ValidParentheses("()[]{}"));
    ASSERT_FALSE(ValidParentheses("(]"));
    ASSERT_FALSE(ValidParentheses("([)]"));
    ASSERT_TRUE(ValidParentheses("{[]}"));
    ASSERT_FALSE(ValidParentheses("]"));

    // Basic tests from problem description
    ASSERT_TRUE(ValidParentheses("([])[]({})"));
    ASSERT_FALSE(ValidParentheses("([)]"));
    ASSERT_FALSE(ValidParentheses("((()"));
}