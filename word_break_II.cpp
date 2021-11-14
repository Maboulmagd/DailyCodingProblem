//
// Created by Mo Aboulmagd on 11/6/21.
//

/*
 * This problem was asked by Microsoft.
 * Given a dictionary of words and a string made up of those words (no spaces), return the original sentence in a list.
 * If there is more than one possible reconstruction, return any of them. If there is no possible reconstruction, then return null.

 * For example, given the set of words 'quick', 'brown', 'the', 'fox', and the string "thequickbrownfox",
 * you should return ['the', 'quick', 'brown', 'fox'].
 * Given the set of words 'bed', 'bath', 'bedbath', 'and', 'beyond', and the string "bedbathandbeyond",
 * return either ['bed', 'bath', 'and', 'beyond] or ['bedbath', 'and', 'beyond'].
 */

#include "include.h"

deque<deque<string>> Helper(string s, const unordered_set<string>& word_dict, unordered_map<string, deque<deque<string>>>& memo) {
    if (s.empty()) {
        return { {} };
    }
    if (memo.find(s) != memo.cend()) {
        return memo[s];
    }

    const int s_len = static_cast<int>(s.length());
    for (int i = 0; i < s_len; ++i) {
        const string& word = s.substr(0, i + 1);
        if (word_dict.find(word) != word_dict.cend()) {// Word has been matched if this executes
            const string& remaining_string = s.substr(i + 1);

            // Remainder string's sentences
            deque<deque<string>> sentences = Helper(remaining_string, word_dict, memo);

            // Add (matched) word to the front of each sentence in sentences
            for (deque<string>& sentence : sentences) {
                sentence.push_front(word);
            }

            // Update memo
            if (memo.find(s) != memo.cend()) {
                for (const deque<string>& sentence : sentences) {
                    memo[s].push_back(sentence);
                }
            }
            else {
                memo[s] = sentences;
            }
        }
    }

    return memo[s];
}

vector<string> WordBreakII(string s, vector<string> word_dict) {
    unordered_set<string> dict(word_dict.cbegin(), word_dict.cend());
    unordered_map<string, deque<deque<string>>> memo;// This memo stores all possible breaks for a string

    Helper(s, dict, memo);

    vector<string> res;

    for (const deque<string>& sentence : memo[s]) {
        string sub_res;

        for (const string& word : sentence) {
            sub_res += word + " ";
        }

        // Get rid of last space...
        sub_res.pop_back();
        res.emplace_back(sub_res);
    }

    return res;
}

TEST(WordBreakII, BasicTests) {
    string s("catsanddog");
    vector<string> word_dict{"cat", "cats", "and", "sand", "dog"};
    vector<string> res = { "cat sand dog", "cats and dog" };
    ASSERT_EQ(WordBreakII(s, word_dict), res);

    s = "pineapplepenapple";
    word_dict = {"apple", "pen", "applepen", "pine", "pineapple"};
    res = { "pine apple pen apple", "pine applepen apple", "pineapple pen apple" };
    ASSERT_EQ(WordBreakII(s, word_dict), res);

    s = "catsandog";
    word_dict = {"cats", "dog", "sand", "and", "cat"};
    res = {};
    ASSERT_EQ(WordBreakII(s, word_dict), res);

    // Basic tests from problem description
    s = "thequickbrownfox";
    word_dict = {"quick", "brown", "the", "fox"};
    res = { "the quick brown fox" };
    ASSERT_EQ(WordBreakII(s, word_dict), res);

    s = "bedbathandbeyond";
    word_dict = { "bed", "bath", "bedbath", "and", "beyond" };
    res = { "bed bath and beyond", "bedbath and beyond" };
    ASSERT_EQ(WordBreakII(s, word_dict), res);
}