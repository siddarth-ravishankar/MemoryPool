//
//  SimplePrimitiveTypeTests.cpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/9/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#include "MemoryPool.hpp"
#include "gtest/gtest.h"

TEST(SimplePrimitiveTypeTests, Int) {
	MemoryPool<int> pool;
	int *a = pool.alloc();
	*a = 999;
	EXPECT_EQ(*a, 999);
	pool.free(a);
}

TEST(SimplePrimitiveTypeTests, Double) {
	MemoryPool<double> pool;
	double *a = pool.alloc();
	*a = 1234.567895;
	EXPECT_EQ(*a, 1234.567895);
	pool.free(a);
}

TEST(SimplePrimitiveTypeTests, Char) {
	MemoryPool<char> pool;
	char *c = pool.alloc();
	*c = 'z';
	EXPECT_EQ(*c, 'z');
	pool.free(c);
}
