//
//  SimplePrimitiveTypeTests.cpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/9/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#include "MemoryPool.hpp"
#include "gtest/gtest.h"

class SimplePrimitiveTypeTests : public ::testing::Test {
protected:
	// void SetUp() override {}
	
	// void TearDown() override {}
	
};

TEST_F(SimplePrimitiveTypeTests, Int) {
	MemoryPool<int> pool;
	int *a = pool.alloc();
	*a = 999;
	EXPECT_EQ(*a, 999);
	pool.free(a);
}

TEST_F(SimplePrimitiveTypeTests, Double) {
	MemoryPool<double> pool;
	double *a = pool.alloc();
	*a = 1234.567895;
	EXPECT_EQ(*a, 1234.567895);
	pool.free(a);
}

TEST_F(SimplePrimitiveTypeTests, Char) {
	MemoryPool<char> pool;
	char *c = pool.alloc();
	*c = 'z';
	EXPECT_EQ(*c, 'z');
	pool.free(c);
}
