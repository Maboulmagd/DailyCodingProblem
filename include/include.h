//
// Created by Mo Aboulmagd on 10/17/21.
//

// Header file for includes and namespaces

#pragma once

//#include <cstdio>
#include <iostream>

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;
using namespace ::testing;

// Definition for a binary tree node.
 struct TreeNode {
     int val;// TODO Try using std::variant/template here?
     unique_ptr<TreeNode> left;
     unique_ptr<TreeNode> right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, unique_ptr<TreeNode> left, unique_ptr<TreeNode> right) : val(x), left(move(left)), right(move(right)) {}
     friend bool operator==(const unique_ptr<TreeNode>& a, const unique_ptr<TreeNode>& b);
 };

// Definition for a linked list node.
