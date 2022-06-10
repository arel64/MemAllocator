cmake_minimum_required(VERSION 3.22)
project(MemAllocator C)

set(CMAKE_C_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(THREADS_PREFER_PTHREAD_FLAG ON)


add_executable(MemAllocator main.c Mem/allocator.c Mem/allocator.h Mem/linkedList.c Mem/linkedList.h Mem/globaldef.h Mem/defragger.c Mem/defragger.h Mem/log.h Test/tests.c)
find_package(Threads REQUIRED)
include(FetchCMocka.cmake)

target_link_libraries(MemAllocator PRIVATE Threads::Threads cmocka-static m)