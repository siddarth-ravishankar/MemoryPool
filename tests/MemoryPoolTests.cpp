//
//  MemoryPoolTests.cpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/9/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#include "gtest/gtest.h"
#include "MemoryPool.hpp"

TEST(MemoryPoolTests, ShouldThrowOnBadAllocation) {
	
	// Create integer memory pool that can hold only 1 integer.
	MemoryPool<int> pool(sizeof(int));
	int *p1 = pool.alloc(1);
	EXPECT_EQ(*p1, 1);
	
	// Additional allocation should throw because memory pool is now full.
	EXPECT_THROW(pool.alloc(2), std::bad_alloc);
}


TEST(MemoryPoolTests, ShouldReuseFreedMemorySegments) {
	
	// Create integer memory pool that can hold only 1 integer.
	MemoryPool<int> pool(sizeof(int));
	int *p1 = pool.alloc(1);
	EXPECT_EQ(*p1, 1);
	pool.free(p1);
	
	// p2 and p3 should reuse freed memory.
	int *p2 = pool.alloc(2);
	EXPECT_EQ(*p2, 2);
	pool.free(p2);
	int *p3 = pool.alloc(3);
	EXPECT_EQ(*p3, 3);
	pool.free(p3);
}
