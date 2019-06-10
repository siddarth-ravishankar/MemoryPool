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
	ELEM_TYPE* last_segment;
	ELEM_TYPE* tail_segment;
	std::forward_list<ELEM_TYPE*> available_segments;
	std::mutex segment_mutex;
	
	ELEM_TYPE* getTailSegment();
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
	
	pool_size = _pool_size;
	head = std::malloc(pool_size);
	segment_size = sizeof(ELEM_TYPE);
	tail_segment = reinterpret_cast<ELEM_TYPE*>(head);
	last_segment = reinterpret_cast<ELEM_TYPE*>(head) + pool_size - segment_size;
}

template <class ELEM_TYPE>
MemoryPool<ELEM_TYPE>::~MemoryPool() {
	std::free(head);
}

template <class ELEM_TYPE>
ELEM_TYPE* MemoryPool<ELEM_TYPE>::getTailSegment() {
	
	if (tail_segment > last_segment)
		throw "Unable to allocate memory. Memory pool depleated.";
	
	ELEM_TYPE* next_segment = tail_segment;
	tail_segment++;
	return next_segment;
}

template <class ELEM_TYPE>
ELEM_TYPE* MemoryPool<ELEM_TYPE>::getNextAvailableSegment() {
	
	ELEM_TYPE* next_available_segmennt;

	std::lock_guard<std::mutex> lock(segment_mutex);
	{
		if(available_segments.empty()) {
			next_available_segmennt = getTailSegment();
		}
		else {
			next_available_segmennt = available_segments.front();
			available_segments.pop_front();
		}
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
	
	std::lock_guard<std::mutex> lock(segment_mutex);
	available_segments.push_front(ptr);
}

#endif /* MemoryPool_hpp */
