//
//  main.cpp
//  tests
//
//  Created by Hosack, Matthew on 7/17/15.
//  Copyright (c) 2015 Hosack, Matthew. All rights reserved.
//

#include <gtest/gtest.h>
#include "RingBuffer.h"
#include <iostream>

#define MAX_SIZE 10
#define DTYPE double

class RingBufferFixture : public testing::Test{
    virtual void SetUp() {
        r = new RingBuffer<DTYPE>(MAX_SIZE);
    }
    virtual void TearDown() {
        delete r;
    }
public:
    RingBuffer<DTYPE> *r;
};


TEST_F(RingBufferFixture, WriteOneReadOneEquals)
{
    DTYPE out;
    r->push(1);
    r->pop(out);
    EXPECT_EQ(1, out);
}

TEST_F(RingBufferFixture, WriteMultipleReadMultipleEquals)
{
    DTYPE out;
    r->push(1);
    r->push(2);
    r->push(3);
    r->pop(out);
    EXPECT_EQ(1, out);
    r->pop(out);
    EXPECT_EQ(2, out);
    r->pop(out);
    EXPECT_EQ(3, out);
}

TEST_F(RingBufferFixture, WriteMoreThanCapacity)
{
    DTYPE out;
    for(int i = 0; i < 12; ++i)
    {
        r->push(i + 1);
    }

    r->pop(out);
    EXPECT_EQ((DTYPE)3, out);
    r->pop(out);
    EXPECT_EQ((DTYPE)4, out);
    r->pop(out);
    EXPECT_EQ((DTYPE)5, out);
    r->pop(out);
    EXPECT_EQ((DTYPE)6, out);
    r->pop(out);
    EXPECT_EQ((DTYPE)7, out);
    r->pop(out);
    EXPECT_EQ((DTYPE)8, out);
    r->pop(out);
    EXPECT_EQ((DTYPE)9, out);
    r->pop(out);
    EXPECT_EQ((DTYPE)10, out);
    r->pop(out);
    EXPECT_EQ(11, out);
    r->pop(out);
    EXPECT_EQ(12, out);
}

TEST_F(RingBufferFixture, StartsEmpty)
{
    EXPECT_EQ(true, r->isEmpty());
}

TEST_F(RingBufferFixture, AvailableStartsTen)
{
    EXPECT_EQ(MAX_SIZE, r->available());
}

TEST_F(RingBufferFixture, SizeStartsZero)
{
    EXPECT_EQ(0, r->size());
}

int main(int argc, const char * argv[]) {
    testing::InitGoogleTest(&argc, (char**) argv);
    return RUN_ALL_TESTS();
}
