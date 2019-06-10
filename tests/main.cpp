//
//  main.cpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/9/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#include "gtest/gtest.h"
#include <benchmark/benchmark.h>

int main(int argc, char ** argv) {
	::benchmark::Initialize(&argc, argv);
	::testing::InitGoogleTest(&argc, argv);
	int test_results = RUN_ALL_TESTS();
	::benchmark::RunSpecifiedBenchmarks();
	return test_results;
}
