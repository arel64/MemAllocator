cmake_minimum_required(VERSION 3.22)
project(MemAllocator C)

set(CMAKE_C_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")

add_executable(MemAllocator main.c Mem/allocator.c Mem/allocator.h Mem/linkedList.c Mem/linkedList.h)
target_link_libraries(MemAllocator m)
