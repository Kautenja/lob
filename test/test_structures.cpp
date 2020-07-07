// Test cases for types and structures for the LimitOrderBook: order, limit
//
// Copyright (c) 2020 Christian Kauten
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "structures.hpp"

using namespace LOB;

TEST_CASE("should invert Side::Sell") {
    REQUIRE(Side::Buy == !Side::Sell);
}

TEST_CASE("should invert Side::Buy") {
    REQUIRE(Side::Sell == !Side::Buy);
}

// ---------------------------------------------------------------------------
// MARK: Order
// ---------------------------------------------------------------------------

TEST_CASE("initialize default Order") {
    Order order;
    REQUIRE(order.next == nullptr);
    REQUIRE(order.prev == nullptr);
    REQUIRE(order.uid == 0);
    REQUIRE(order.side == Side::Sell);
    REQUIRE(order.size == 0);
    REQUIRE(order.price == 0);
    REQUIRE(order.arrival == 0);
    REQUIRE(order.execution == 0);
    REQUIRE(order.limit == nullptr);
}

SCENARIO("initialize Order") {
    GIVEN("arbitrary legal parameters") {
        UID uid = 5;
        Side side = Side::Buy;
        Size size = 100;
        Price price = 5746;
        Timestamp arrival = 1000000001;
        Timestamp execution = 1000000002;
        WHEN("an Order is initialized without optionals") {
            Order order = {uid, side, size, price};
            THEN("the order is created with parameters") {
                REQUIRE(order.next == nullptr);
                REQUIRE(order.prev == nullptr);
                REQUIRE(order.uid == uid);
                REQUIRE(order.side == side);
                REQUIRE(order.size == size);
                REQUIRE(order.price == price);
                REQUIRE(order.arrival == 0);
                REQUIRE(order.execution == 0);
                REQUIRE(order.limit == nullptr);
            }
        }
        WHEN("an Order is initialized with optional arrival") {
            Order order = {uid, side, size, price, arrival};
            THEN("the order is created with parameters") {
                REQUIRE(order.next == nullptr);
                REQUIRE(order.prev == nullptr);
                REQUIRE(order.uid == uid);
                REQUIRE(order.side == side);
                REQUIRE(order.size == size);
                REQUIRE(order.price == price);
                REQUIRE(order.arrival == arrival);
                REQUIRE(order.execution == 0);
                REQUIRE(order.limit == nullptr);
            }
        }
        WHEN("an Order is initialized with optional execution") {
            Order order = {uid, side, size, price, arrival, execution};
            THEN("the order is created with parameters") {
                REQUIRE(order.next == nullptr);
                REQUIRE(order.prev == nullptr);
                REQUIRE(order.uid == uid);
                REQUIRE(order.side == side);
                REQUIRE(order.size == size);
                REQUIRE(order.price == price);
                REQUIRE(order.arrival == arrival);
                REQUIRE(order.execution == execution);
                REQUIRE(order.limit == nullptr);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// MARK: Limit
// ---------------------------------------------------------------------------

TEST_CASE("initialize default Limit") {
    Limit limit;
    REQUIRE(limit.key == 0);
    REQUIRE(limit.parent == nullptr);
    REQUIRE(limit.left == nullptr);
    REQUIRE(limit.right == nullptr);
    REQUIRE(limit.size == 0);
    REQUIRE(limit.volume == 0);
    REQUIRE(limit.order_head == nullptr);
    REQUIRE(limit.order_tail == nullptr);
}

SCENARIO("initialize Limit") {
    GIVEN("arbitrary legal parameters and a new order") {
        Size size = 100;
        Price price = 5;
        Order order = {5, Side::Buy, size, price};
        WHEN("a Limit is initialized") {
            Limit limit = {&order};
            THEN("the limit is created with parameters") {
                REQUIRE(limit.key == price);
                REQUIRE(limit.parent == nullptr);
                REQUIRE(limit.left == nullptr);
                REQUIRE(limit.right == nullptr);
                REQUIRE(limit.size == 1);
                REQUIRE(limit.volume == size);
                REQUIRE(limit.order_head == &order);
                REQUIRE(limit.order_tail == &order);
            }
        }
    }
}
