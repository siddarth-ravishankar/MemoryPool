//
//  MemoryPool.hpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/8/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#include "MemoryPool.hpp"
#include "ComplexClass.hpp"
#include <benchmark/benchmark.h>

using namespace std;

#define NUM_THREADS 4
#define LIMIT 100000

class MemoryPoolBenchmark {
public:
	
	static void MemoryPoolAllocation() {
		
		MemoryPool<ComplexClass1> pool(LIMIT * sizeof(ComplexClass1));
		
		vector<ComplexClass1*> objs(LIMIT);
		for(int i=0; i<LIMIT; i++) {
			objs[i] = pool.alloc( 	ComplexClassFactory::GenerateStr(),
								 ComplexClassFactory::GenerateInt(),
								 ComplexClassFactory::GenerateDouble(),
								 ComplexClassFactory::GenerateCharPtr());
		}
		
		for(int i=0; i<LIMIT; i++) {
			pool.free(objs[i]);
		}
	}
	
	static void MallocAllocation() {
		
		vector<ComplexClass1*> objs(LIMIT);
		for(int i=0; i<LIMIT; i++) {
			ComplexClass1* obj = reinterpret_cast<ComplexClass1*>(malloc(sizeof(ComplexClass1)));
			objs[i] = new(obj) ComplexClass1(	ComplexClassFactory::GenerateStr(),
											 ComplexClassFactory::GenerateInt(),
											 ComplexClassFactory::GenerateDouble(),
											 ComplexClassFactory::GenerateCharPtr());
		}
		
		for(int i=0; i<LIMIT; i++) {
			free(objs[i]);
		}
	}
};

static void BM_Malloc(benchmark::State& state) {
	for (auto _ : state)
		MemoryPoolBenchmark::MallocAllocation();
}
BENCHMARK(BM_Malloc);

static void BM_MemoryPool(benchmark::State& state) {
	for (auto _ : state)
		MemoryPoolBenchmark::MemoryPoolAllocation();
}
BENCHMARK(BM_MemoryPool);
