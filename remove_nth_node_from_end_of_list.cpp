//
// Created by Mo Aboulmagd on 11/11/21.
//

/*
 * This problem was asked by Google.
 * Given a singly linked list and an integer k, remove the kth last element from the list. k is guaranteed to be smaller than the length of the list.
 * The list is very long, so making more than one pass is prohibitively expensive.
 * Do this in constant space and in one pass.
 */

#include "include.h"

// Complexity Analysis:
// Time: O(N), one pass, as we are iterating over each node in the list only once.
// Space: O(1)

// Key idea: use two ptrs, and delay the slow ptr by n nodes, that way the slow ptr will be n nodes behind the fast ptr.
ListNode* RemoveNthFromEndOfList(ListNode* head, const int n) {
    if (!head->next) {// Edge case, and we know 1 <= n <= length of list, so no need to worry about that
        head = nullptr;
        return head;
    }

    ListNode* slow = head;
    ListNode* fast = head;

    int x = 0;
    while (fast && fast->next) {
        if (x >= n) {
            slow = slow->next.get();
        }

        fast = fast->next.get();
        ++x;
    }

    if (x < n) {// Edge case where we delete slow itself -> for example [1,2], n = 2, we want to delete 1
        ListNode* to_return = slow->next.get();
        slow = nullptr;
        return to_return;
    }

    ListNode* to_delete = slow->next.get();
    slow->next.get();
    to_delete->next.get();
    to_delete->next = nullptr;// Disconnect node to be deleted from rest of the linked list

    return head;
}

class RemoveNthFromEndOfListTest : public ::testing::Test {
protected:
    explicit RemoveNthFromEndOfListTest() {
        // [1]
        unique_ptr<ListNode> head = make_unique<ListNode>(1);

        lists.push_back(move(head));

        // [1,2]
        head = make_unique<ListNode>(1);
        head->next = make_unique<ListNode>(2);

        lists.push_back(move(head));

        // [1,2,3,4,5]
        head = make_unique<ListNode>(1);
        head->next = make_unique<ListNode>(2);
        head->next->next = make_unique<ListNode>(3);
        head->next->next->next = make_unique<ListNode>(4);
        head->next->next->next->next = make_unique<ListNode>(5);

        lists.push_back(move(head));
    }

    ~RemoveNthFromEndOfListTest() {
    }

    vector<unique_ptr<ListNode>> lists;
};

TEST_F(RemoveNthFromEndOfListTest, List0Test1) {
    ASSERT_THAT(RemoveNthFromEndOfList(lists[0].get(), 1), nullptr);
}

TEST_F(RemoveNthFromEndOfListTest, List1Test1) {
    ASSERT_THAT(RemoveNthFromEndOfList(lists[1].get(), 1), lists[1].get());
}

TEST_F(RemoveNthFromEndOfListTest, List1Test2) {
    ASSERT_THAT(RemoveNthFromEndOfList(lists[1].get(), 2), lists[1]->next.get());
}

TEST_F(RemoveNthFromEndOfListTest, List2Test1) {
    ASSERT_THAT(RemoveNthFromEndOfList(lists[2].get(), 1), lists[2].get());
}

TEST_F(RemoveNthFromEndOfListTest, List2Test2) {
    EXPECT_THAT(RemoveNthFromEndOfList(lists[2].get(), 2), lists[2].get());
}

TEST_F(RemoveNthFromEndOfListTest, List2Test3) {
    EXPECT_THAT(RemoveNthFromEndOfList(lists[2].get(), 5), lists[2]->next.get());
}
