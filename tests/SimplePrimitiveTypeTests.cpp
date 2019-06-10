//
//  SimplePrimitiveTypeTests.cpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/9/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#include "gtest/gtest.h"
#include "MemoryPool.hpp"

/*
 Test if MemoryPool can create and allocate memory for primitive data types - int, char annd double.
 */

TEST(SimplePrimitiveTypeTests, Int) {
	MemoryPool<int> pool;
	int *a = pool.alloc(999);
	EXPECT_EQ(999, *a);
	pool.free(a);
}

TEST(SimplePrimitiveTypeTests, Double) {
	MemoryPool<double> pool;
	double *a = pool.alloc(1234.567895);
	EXPECT_EQ(1234.567895, *a);
	pool.free(a);
}

TEST(SimplePrimitiveTypeTests, Char) {
	MemoryPool<char> pool;
	char *c = pool.alloc('z');
	EXPECT_EQ('z', *c);
	pool.free(c);
}
