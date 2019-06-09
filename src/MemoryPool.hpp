//
//  MemoryPool.hpp
//  ThreadSafeMemoryPool
//
//  Created by Siddarth Pc on 6/8/19.
//  Copyright © 2019 Siddarth Pc. All rights reserved.
//

#ifndef MemoryPool_hpp
#define MemoryPool_hpp

#include <thread>
#include <forward_list>

#define DEFAULT_POOL_SIZE 16 * 1024

template <class ELEM_TYPE>
class MemoryPool {
	
	size_t segment_size;
	int pool_size;
	void* head;
	ELEM_TYPE* tail_segment;
	std::forward_list<ELEM_TYPE*> available_segments;
	
	ELEM_TYPE* getNextAvailableSegment();
	
public:
	MemoryPool();
	explicit MemoryPool(const int);
	~MemoryPool();
	template <class... Args> ELEM_TYPE* alloc(Args&&...);
	void free(ELEM_TYPE*);
};

template <class ELEM_TYPE>
MemoryPool<ELEM_TYPE>::MemoryPool() : MemoryPool::MemoryPool(DEFAULT_POOL_SIZE) {}

template <class ELEM_TYPE>
MemoryPool<ELEM_TYPE>::MemoryPool(const int _pool_size) {
	segment_size = sizeof(ELEM_TYPE);
	pool_size = _pool_size;
	head = std::malloc(pool_size);
	tail_segment = reinterpret_cast<ELEM_TYPE*>(head);
}

template <class ELEM_TYPE>
MemoryPool<ELEM_TYPE>::~MemoryPool() {
	std::free(head);
}

template <class ELEM_TYPE>
ELEM_TYPE* MemoryPool<ELEM_TYPE>::getNextAvailableSegment() {
	
	ELEM_TYPE* next_available_segmennt;

	if(available_segments.empty()) {
		next_available_segmennt = tail_segment;
		tail_segment++;
	}
	else {
		next_available_segmennt = available_segments.front();
		available_segments.pop_front();
	}
	
	return next_available_segmennt;
}

template <class ELEM_TYPE>
template <class... Args>
ELEM_TYPE* MemoryPool<ELEM_TYPE>::alloc(Args&&... args) {
	ELEM_TYPE* ptr = getNextAvailableSegment();
	return new(ptr) ELEM_TYPE(std::forward<Args>(args)...);
}

template <class ELEM_TYPE>
void MemoryPool<ELEM_TYPE>::free(ELEM_TYPE* ptr) {
	available_segments.push_front(ptr);
}

#endif /* MemoryPool_hpp */
