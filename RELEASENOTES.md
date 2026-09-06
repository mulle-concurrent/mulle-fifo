### 0.1.8



* stress test now uses ``mulle_thread_yield()`` instead of tight spin loops
* new ``MULLE_TEST_VALGRIND`` environment variable shrinks the item count for valgrind runs
* item counts are passed as thread arguments instead of using the global fixed constant



* all FIFO write functions now return -2 for NULL pointers, previously a debug-only assert could store NULL and corrupt the FIFO in release builds
* **BREAKING**: ``_read_barrier`` variants are removed; the plain `read` functions provide full publication guarantees via `seq_cst` atomics
* dynamic FIFO `done` is now idempotent and safe to call on a storage-free fifo
* added single-thread contract tests and multithreaded publication/stress tests



* API documentation moved to asset/dox/api/toc/
* README now links to API Summary documentation

### 0.1.7

Various small improvements
