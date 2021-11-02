//
// Created by Mo Aboulmagd on 10/31/21.
//

/*
 * This problem was asked by Twitter.
 * You run an e-commerce website and want to record the last N order ids in a log.
 * Implement a data structure to accomplish this, with the following API:
 *      record(order_id): adds the order_id to the log
 *      get_last(i): gets the ith last element from the log. i is guaranteed to be smaller than or equal to N.
 * You should be as efficient with time and space as possible.
 */

#include "include.h"

/*
 * Since we know the maximum amount of orders that we'll be asked to keep track of at any given point in time, this problem becomes an excellent
 * candidate for the use of a circular buffer/queue data structure.
 */

// Complexity Analysis:
// Time: O(1) for Record and GetLast functions.
// Space: O(N) for the buffer, where N is the maximum amount of orders that we'll be keeping track of, at any given moment in time.

struct Order final {
    string order_id;
    // Add other fields

    friend bool operator==(const Order& a, const Order& b) {
        return a.order_id == b.order_id;
    }
};

class OrderRecorder final {
public:
    explicit OrderRecorder(const int number_of_orders) : insert_index_(0), number_of_orders_(number_of_orders) {
        buffer_.reserve(number_of_orders_);
    }

    void Record(const string order_id) {
        if (Size() == number_of_orders_) {
            buffer_[insert_index_] = Order{order_id};
        }

        else {// This will only ever run n times
            buffer_.push_back(Order{order_id});
        }

        insert_index_ = ++insert_index_ % number_of_orders_;
    }

    Order GetLast(const int i) const {
        return buffer_[(insert_index_ - i + number_of_orders_) % number_of_orders_];
    }

    // Other utility API methods
    size_t Capacity() const {
        return buffer_.capacity();
    }

    size_t Size() const {
        return buffer_.size();
    }

private:
    vector<Order> buffer_;
    int insert_index_;
    int number_of_orders_;// This denotes the maximum size of our buffer at any given point in time.
};

TEST(LastNOrdersInLog, Tests) {
    const int num_orders = 3;
    OrderRecorder order_recorder_(num_orders);

    ASSERT_EQ(order_recorder_.Capacity(), num_orders);
    ASSERT_EQ(order_recorder_.Size(), 0);

    // Insert an order associated with order_id 1
    order_recorder_.Record("1");
    ASSERT_EQ(order_recorder_.Capacity(), num_orders);
    ASSERT_EQ(order_recorder_.Size(), 1);
    ASSERT_EQ(order_recorder_.GetLast(1), Order{"1"});

    // Insert an order associated with order_id 2
    order_recorder_.Record("2");
    ASSERT_EQ(order_recorder_.Capacity(), num_orders);
    ASSERT_EQ(order_recorder_.Size(), 2);
    ASSERT_EQ(order_recorder_.GetLast(1), Order{"2"});
    ASSERT_EQ(order_recorder_.GetLast(2), Order{"1"});

    // Insert an order associated with order_id 3
    order_recorder_.Record("3");
    ASSERT_EQ(order_recorder_.Capacity(), num_orders);
    ASSERT_EQ(order_recorder_.Size(), 3);
    ASSERT_EQ(order_recorder_.GetLast(1), Order{"3"});
    ASSERT_EQ(order_recorder_.GetLast(2), Order{"2"});
    ASSERT_EQ(order_recorder_.GetLast(3), Order{"1"});

    // Insert an order associated with order_id 4
    order_recorder_.Record("4");
    ASSERT_EQ(order_recorder_.Capacity(), num_orders);
    ASSERT_EQ(order_recorder_.Size(), 3);
    ASSERT_EQ(order_recorder_.GetLast(1), Order{"4"});
    ASSERT_EQ(order_recorder_.GetLast(2), Order{"3"});
    ASSERT_EQ(order_recorder_.GetLast(3), Order{"2"});

    // Insert an order associated with order_id 5
    order_recorder_.Record("5");
    ASSERT_EQ(order_recorder_.Capacity(), num_orders);
    ASSERT_EQ(order_recorder_.Size(), 3);
    ASSERT_EQ(order_recorder_.GetLast(1), Order{"5"});
    ASSERT_EQ(order_recorder_.GetLast(2), Order{"4"});
    ASSERT_EQ(order_recorder_.GetLast(3), Order{"3"});
}