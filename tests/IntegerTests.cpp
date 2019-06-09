//
//  MemoryPoolIntegerTests.cpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/9/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#include "MemoryPool.hpp"
#include "gtest/gtest.h"
#include <thread>
#include <vector>

using namespace std;

class IntegerTests : public ::testing::Test {
	
	const int default_limit = 12;
protected:
	
	int limit = default_limit;
	MemoryPool<int> pool;
	vector<int> values;
	vector<int*> ptrs;
	
	void SetUp() override {
		srand((unsigned int)time(NULL));
		values = vector<int>(limit);
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
			values[i] = rand();
			ptrs[i] = pool.alloc(values[i]);
		}
	}
	
};

TEST_F(IntegerTests, AllocteFromSingleThread) {
	
	AllocAndInitRandomValues(0, limit);
	
	for(int i=0; i<limit; i++)
		EXPECT_EQ(*ptrs[i], values[i]);
	
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
		EXPECT_EQ(*ptrs[i], values[i]);
	
	FreeAllObjects();
}
