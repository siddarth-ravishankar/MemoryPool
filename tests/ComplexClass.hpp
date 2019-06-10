//
//  ComplexClass.hpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/9/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#define DEFAULT_LIMIT 100

class ComplexClass1 {
	std::string str;
	int int_val;
	double double_val;
	char* char_ptr;
	
public:
	
	ComplexClass1() {}
	
	ComplexClass1(std::string _str, int _int_val, double _double_val, char* _char_ptr) {
		str = _str;
		int_val = _int_val;
		double_val = _double_val;
		char_ptr = _char_ptr;
	}
	
	std::string GetStr(){
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

class ComplexClassFactory {
public:
	static std::string GenerateStr(){
		return "A string " + std::to_string(rand());
	}
	static int GenerateInt(){
		return rand();
	}
	static double GenerateDouble(){
		return (double)rand() / (double)RAND_MAX;
	}
	static char* GenerateCharPtr(){
		std::string str = "A char ptr " + std::to_string(rand());
		return (char*)str.c_str();
	}
};

