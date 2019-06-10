## ThreadSafe Memory Pool

Implemented a thread-safe memory pool that can allocate and free one object of given type. Code related to MemoryPool are present in src/MemoryPool.hpp.

MemoryPool class initializes a default chunk of memory and returns free memory segments on every alloc() function. This class also uses a list of available_segments to track memory that are freed for later use. The alloc() function uses "placement new" operator to foward constructor parameters.

There is a limitation with MemoryPool class. It cannot track double freeing of objets. For e.g., if MemoryPool<ELEM_TYPE>::free(ELEM_TYPE* ptr) is called twice with same pointer, it might result in undefined behaviour. This is done intentionally to align this concept with malloc which does not track double free.

## Tests

The project uses google tests annd benchmark, built from [Google Tests](https://github.com/google/googletest). The tests/ folder contains main.cpp, that runs all related tests and benchmarks related to MemoryPool class.

Tests are classified into 4 categories:

1. MemoryPoolTests - Tests the basic functionalities of MemoryPool class.
2. SimplePrimitiveTypeTests - that uses MemoryPool<> on primitive datatypes like int, char and double to verify if memory is allocated and values are stored and freed correctly.
3. IntegerTests - tries to allocate multiple pointers from an integer MemoryPool using single and multiple threads.
4. ComplexClassTests - tries to allocate a class containing member variables and functions from MemoryPool using single and multiple threads.

In addition to tests, the code also runs Benchmark on allocating and deallocating ComplexClass using MemoryPool, malloc / free and new / delete operators and compares results.

Both tests and benchmarks are run as a part of main function and the binary built from my machine is checked into binaries/ which can be run using ./MemoryPoolTests.

The project is built in Mac using xcode and project file is checked into proj/. The project should be ready to be run on "MemoryPool" target and should run all tests / benchmark. Address Sanitizer is enbabled for project to deduct any memory violations.