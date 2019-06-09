//
//  MemoryPool.hpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/8/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#ifndef MemoryPool_hpp
#define MemoryPool_hpp

#include <iostream>

template <class ELEM_TYPE>
class MemoryPool {
	
public:
	template <class... Args> ELEM_TYPE* alloc(Args&&...);
	void free(ELEM_TYPE*);
};

template <class ELEM_TYPE>
template <class... Args>
ELEM_TYPE* MemoryPool<ELEM_TYPE>::alloc(Args&&... args) {
	ELEM_TYPE* ptr = new ELEM_TYPE;
	return new(ptr) ELEM_TYPE(std::forward<Args>(args)...);
}

template <class ELEM_TYPE>
void MemoryPool<ELEM_TYPE>::free(ELEM_TYPE* ptr) {
	delete ptr;
}

#endif /* MemoryPool_hpp */
