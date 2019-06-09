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
	
protected:
	
	const int default_max = 12;
	int max = default_max;
	MemoryPool<int> pool;
	vector<int> values;
	vector<int*> ptrs;
	
	void SetUp() override {
		srand((unsigned int)time(NULL));
		values = vector<int>(max);
		ptrs = vector<int*>(max);
	}
	
	// void TearDown() override {}
	
public:
	void AllocAndInitRandomValues(int start, int end) {
		for(int i=start; i<end; i++) {
			values[i] = rand() % max;
			ptrs[i] = pool.alloc(values[i]);
		}
	}
	
};

TEST_F(IntegerTests, AllocteFromSingleThread) {
	
	for(int i=0; i<max; i++) {
		values[i] = rand() % max;
		ptrs[i] = pool.alloc(values[i]);
	}
	
	for(int i=0; i<max; i++)
		EXPECT_EQ(*ptrs[i], values[i]);
	
	for(auto ptr : ptrs)
		pool.free(ptr);
}

TEST_F(IntegerTests, AllocteFromMultipleThreads) {
	
	int start = 0;
	int num_threads = 4;
	
	thread threads[num_threads];
	
	for(int i=0; i<num_threads; i++) {
		int end = start + max / num_threads;
		threads[i] = thread(&IntegerTests::AllocAndInitRandomValues, this, start, end);
		start += max / num_threads;
	}
	
	for(int i=0; i<num_threads; i++)
		threads[i].join();
	
	for(int i=0; i<max; i++)
		EXPECT_EQ(*ptrs[i], values[i]);
	
	for(auto ptr : ptrs)
		pool.free(ptr);
}
