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
ListNode* RemoveNthFromEndOfList(ListNode** head, const int n) {
    if (!(*head)->next) {// Edge case
        delete *head;
        *head = nullptr;
        return *head;
    }

    ListNode* slow = *head;
    ListNode* fast = *head;

    int x = 0;
    while (fast && fast->next) {
        if (x >= n) {
            slow = slow->next;
        }

        fast = fast->next;
        ++x;
    }

    if (x < n) {// Edge case where we delete slow itself -> for example [1,2], n = 2, we want to delete 1
        ListNode* to_return = slow->next;
        slow->next = nullptr;// Disconnect node from rest of list

        if (slow == *head) {
            *head = to_return;
        }

        delete slow;
        slow = nullptr;

        return to_return;
    }

    ListNode* to_delete = slow->next;
    slow->next = to_delete->next;
    to_delete->next = nullptr;// Disconnect node to be deleted from rest of the linked list
    delete to_delete;
    to_delete = nullptr;

    return *head;
}

class RemoveNthFromEndOfListTest : public ::testing::Test {
protected:
    explicit RemoveNthFromEndOfListTest() {
        // [1]
        ListNode* head = new ListNode(1);

        lists.push_back(move(head));

        // [1,2]
        head = new ListNode(1);
        head->next = new ListNode(2);

        lists.push_back(move(head));

        // [1,2,3,4,5]
        head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);

        lists.push_back(move(head));
    }

    ~RemoveNthFromEndOfListTest() {
        for (ListNode* list : lists) {
            DeleteList(list);
        }
    }

    vector<ListNode*> lists;
};

TEST_F(RemoveNthFromEndOfListTest, List0Test1) {
    ASSERT_THAT(RemoveNthFromEndOfList(&lists[0], 1), nullptr);
}

TEST_F(RemoveNthFromEndOfListTest, List1Test1) {
    ASSERT_THAT(RemoveNthFromEndOfList(&lists[1], 1), lists[1]);
}

TEST_F(RemoveNthFromEndOfListTest, List1Test2) {
    ASSERT_THAT(RemoveNthFromEndOfList(&lists[1], 2), lists[1]->next);
}

TEST_F(RemoveNthFromEndOfListTest, List2Test1) {
    ASSERT_THAT(RemoveNthFromEndOfList(&lists[2], 1), lists[2]);
}

TEST_F(RemoveNthFromEndOfListTest, List2Test2) {
    EXPECT_THAT(RemoveNthFromEndOfList(&lists[2], 2), lists[2]);
}

TEST_F(RemoveNthFromEndOfListTest, List2Test3) {
    EXPECT_THAT(RemoveNthFromEndOfList(&lists[2], 5), lists[2]->next);
}
