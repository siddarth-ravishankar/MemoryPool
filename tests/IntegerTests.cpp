//
//  MemoryPoolIntegerTests.cpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/9/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#include <thread>
#include <vector>
#include "gtest/gtest.h"
#include "MemoryPool.hpp"

using namespace std;

#define DEFAULT_LIMIT 100

/*
 Test if MemoryPool can create and allocate memory for multiple objects of integer data type.
 This test also verifies memory allocation can happen in parallel.
 */


class IntegerTests : public ::testing::Test {
	
protected:
	
	vector<int*> ptrs;			// List of pointers created using MemoryPool
	vector<int> expected;
	MemoryPool<int> pool;
	int limit = DEFAULT_LIMIT;
	
	void SetUp() override {
		srand((unsigned int)time(NULL));
		expected = vector<int>(limit);
		ptrs = vector<int*>(limit);
	}
	
	// void TearDown() override {}
	
	void FreeAllObjects() {
		for(auto ptr : ptrs)
			pool.free(ptr);
	}
	
public:
	void AllocAndInitRandomValues(int start, int end) {
		for(int i=start; i<end; i++) {
			expected[i] = rand();
			ptrs[i] = pool.alloc(expected[i]);
		}
	}
	
};

TEST_F(IntegerTests, AllocteFromSingleThread) {
	
	AllocAndInitRandomValues(0, limit);
	
	for(int i=0; i<limit; i++)
		EXPECT_EQ(expected[i], *ptrs[i]);
	
	FreeAllObjects();
}

TEST_F(IntegerTests, AllocteFromMultipleThreads) {
	
	int start = 0;
	int num_threads = 4;
	thread threads[num_threads];
	
	for(int i=0; i<num_threads; i++) {
		int end = start + limit / num_threads;
		threads[i] = thread(&IntegerTests::AllocAndInitRandomValues, this, start, end);
		start += limit / num_threads;
	}
	for(int i=0; i<num_threads; i++)
		threads[i].join();
	
	for(int i=0; i<limit; i++)
		EXPECT_EQ(expected[i], *ptrs[i]);
	
	FreeAllObjects();
}
