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

#define LIMIT 100000

static void allocUsingMemoryPool(int start, int end, vector<ComplexClass1*> objs, MemoryPool<ComplexClass1>* pool) {
	for(int i=start; i<end; i++) {
		objs[i] = pool->alloc(ComplexClassFactory::GenerateStr(), ComplexClassFactory::GenerateInt(), ComplexClassFactory::GenerateDouble(), ComplexClassFactory::GenerateCharPtr());
	}
}

static void freeUsingMemoryPool(int start, int end, vector<ComplexClass1*> objs, MemoryPool<ComplexClass1>* pool) {
	for(int i=start; i<end; i++) {
		pool->free(objs[i]);
	}
}

static void memoryPoolAllocation() {
	
	vector<ComplexClass1*> objs(LIMIT);
	MemoryPool<ComplexClass1> pool(LIMIT * sizeof(ComplexClass1));
	
	allocUsingMemoryPool(0, LIMIT, objs, &pool);
	freeUsingMemoryPool(0, LIMIT, objs, &pool);
}

static void allocUsingMalloc(int start, int end, vector<ComplexClass1*> objs) {
	for(int i=start; i<end; i++) {
		ComplexClass1* obj = reinterpret_cast<ComplexClass1*>(malloc(sizeof(ComplexClass1)));
		objs[i] = new(obj) ComplexClass1(ComplexClassFactory::GenerateStr(), ComplexClassFactory::GenerateInt(), ComplexClassFactory::GenerateDouble(), ComplexClassFactory::GenerateCharPtr());
	}
}

static void freeMalloc(int start, int end, vector<ComplexClass1*> objs) {
	for(int i=start; i<end; i++) {
		free(objs[i]);
	}
}

static void mallocAllocation() {
	
	vector<ComplexClass1*> objs(LIMIT);
	
	allocUsingMalloc(0, LIMIT, objs);
	freeMalloc(0, LIMIT, objs);
}

static void NewDeleteAllocation() {
	
	vector<ComplexClass1*> objs(LIMIT);
	for(int i=0; i<LIMIT; i++) {
		objs[i] = new ComplexClass1(ComplexClassFactory::GenerateStr(), ComplexClassFactory::GenerateInt(), ComplexClassFactory::GenerateDouble(), ComplexClassFactory::GenerateCharPtr());
	}
	
	for(int i=0; i<LIMIT; i++) {
		delete objs[i];
	}
}

static void BM_MemoryPool(benchmark::State& state) {
	for (auto _ : state)
		memoryPoolAllocation();
}
BENCHMARK(BM_MemoryPool);

static void BM_Malloc(benchmark::State& state) {
	for (auto _ : state)
		mallocAllocation();
}
BENCHMARK(BM_Malloc);

static void BM_NewDelete(benchmark::State& state) {
	for (auto _ : state)
		NewDeleteAllocation();
}
BENCHMARK(BM_NewDelete);
