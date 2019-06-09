//
//  ObjectTests.cpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/9/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#include "gtest/gtest.h"
#include "MemoryPool.hpp"

using namespace std;

class ComplexClass1 {
	string str;
	int int_val;
	double double_val;
	char* char_ptr;
	
public:
	
	ComplexClass1() {
		
	}

	ComplexClass1(string _str, int _int_val, double _double_val, char* _char_ptr) {
		str = _str;
		int_val = _int_val;
		double_val = _double_val;
		char_ptr = _char_ptr;
	}
	
	string GetStr(){
		return str;
	}
	int GetInt(){
		return int_val;
	}
	double GetDouble(){
		return double_val;
	}
	char* GetCharPtr(){
		return char_ptr;
	}
};

class ComplexClassTests : public ::testing::Test {
	
	const int default_limit = 12;
	
	string GenerateStr(){
		return "A string " + to_string(rand());
	}
	int GenerateInt(){
		return rand();
	}
	double GenerateDouble(){
		return (double)rand() / (double)RAND_MAX;
	}
	char* GenerateCharPtr(){
		string str = "A char ptr " + to_string(rand());
		return (char*)str.c_str();
	}
	
protected:
	MemoryPool<ComplexClass1> pool;
	int limit = default_limit;
	
	struct ComplexClassPlaceholder {
		string str;
		int int_val;
		double double_val;
		char* char_ptr;
	};
	
	vector<ComplexClassPlaceholder> placeholders;
	vector<ComplexClass1*> complexClassObjects;
	
	void SetUp() override {
		srand((unsigned int)time(NULL));
		placeholders = vector<ComplexClassPlaceholder>(limit);
		complexClassObjects = vector<ComplexClass1*>(limit);
	}
	
	// void TearDown() override {}
	
	void FreeAllObjects() {
		for (auto obj : complexClassObjects) {
			pool.free(obj);
		}
	}

public:
	void AllocAndInitRandomValues(int start, int end) {
		for(int i=start; i<end; i++) {
			ComplexClassPlaceholder placeholder {
				GenerateStr(),
				GenerateInt(),
				GenerateDouble(),
				GenerateCharPtr(),
			};
			complexClassObjects[i] = pool.alloc(placeholder.str, placeholder.int_val, placeholder.double_val, placeholder.char_ptr);
			placeholders[i] = placeholder;
		}
	}
};

TEST_F(ComplexClassTests, SingleAllocation) {
	
	ComplexClass1* obj = pool.alloc("A sample string.", 1, 200000.5, (char*)"Char array string.");
	
	EXPECT_EQ("A sample string.", obj->GetStr());
	EXPECT_EQ(1, obj->GetInt());
	EXPECT_EQ(200000.5, obj->GetDouble());
	EXPECT_EQ("Char array string.", obj->GetCharPtr());
	
	pool.free(obj);
}

TEST_F(ComplexClassTests, MultipleAllocations) {
	
	AllocAndInitRandomValues(0, limit);
	
	for(int i=0; i<limit; i++) {
		EXPECT_EQ(placeholders[i].str, complexClassObjects[i]->GetStr());
		EXPECT_EQ(placeholders[i].int_val, complexClassObjects[i]->GetInt());
		EXPECT_EQ(placeholders[i].double_val, complexClassObjects[i]->GetDouble());
		EXPECT_EQ(placeholders[i].char_ptr, complexClassObjects[i]->GetCharPtr());
	}
	
	FreeAllObjects();
}

TEST_F(ComplexClassTests, AllocateFromMultipleThreads) {
	
	int start = 0;
	int num_threads = 4;
	thread threads[num_threads];
	
	for(int i=0; i<num_threads; i++) {
		int end = start + limit / num_threads;
		threads[i] = thread(&ComplexClassTests::AllocAndInitRandomValues, this, start, end);
		start += limit / num_threads;
	}
	
	for(int i=0; i<num_threads; i++)
		threads[i].join();
	
	for(int i=0; i<limit; i++) {
		EXPECT_EQ(placeholders[i].str, complexClassObjects[i]->GetStr());
		EXPECT_EQ(placeholders[i].int_val, complexClassObjects[i]->GetInt());
		EXPECT_EQ(placeholders[i].double_val, complexClassObjects[i]->GetDouble());
		EXPECT_EQ(placeholders[i].char_ptr, complexClassObjects[i]->GetCharPtr());
	}
	
	FreeAllObjects();
}
