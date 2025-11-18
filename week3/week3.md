# Week3: Memory

## Memory organization

Process memory:

- Stack: grow from 1 end
- Heap: grows from another end
- global varables literals: global variables occypy fixed memory size, and persist through program lifetime (static program allocation)

Heap data:

  - Dynamic storage duration - manual allocation/deallocation
  - Slower allocation - involves memory management overhead
  - Large size (limited by available RAM)
  - Flexible lifetime - persists until explicitly freed
  - Stores:
    - Objects created with new/delete
    - Objects managed by smart pointers
    - Large data structures

```cpp
auto v1 = (double*)malloc(N*sizeof(double)); // not recommended
auto v2 = new double[N]; // not recommended
auto v3 = vector<double>(N);
```

 Stack

  - Automatic storage duration - memory is automatically allocated/deallocated
  - Fast allocation - just move the stack pointer
  - Fixed size (typically 1-8 MB depending on OS)
  - LIFO (Last In, First Out) structure
  - Stores:
    - Local variables
    - Function parameters
    - Return addresses
    - Small automatic objects

## Virtual memory

Issues with unprotected RAM access

- security and stability
- insufficient memory
- memory fragmentation

Virtual memory:

- a process sees a virtual address space(logical addresses)
- At a memory request, the logical address is translated to a physical address
- granualarity of the virtual addresses into pages of 4kB each (16KB on M4)
- each page can be backed by a frame in the physical memory

## Memory mamagement unit

Steps:

- Cpu makes memory requests pass through MMU
- MMU: implement the virtual memory 
- looks for physical address in the page table in RAM.
- Page table lookup-page walk is expensive 
- TLB( Translation lookaside buffer) store recent address translations. Most memmory requests can be handled with TLB alone (TLB hit). a TLB miss will lead to an expensive page walk..

How to avoid TLB misses:

-  avoid spread out your memory usages => use compact data structures

## Memory latency

Typical access times:

- CPU cycle (for 4GHZ): 1/4 ns
- L1 Cache memory (SRAM): 1ns => latency time(time to reception of data after issuing a read request) is 1 ns
- main memory (DRAM): 110ns
- External storage (SSD): 50K ns

SRAM vs DRAM:

- SRAM: fast memory, need 4-6 transistors for 1 bit
- DRAM: slower, 1 transister + 1 capacitor (slow charge+ need refresh ~64ms) for a bit

Memory row: read complete memeory row of ~1kB

## ![Screenshot 2025-11-13 at 4.47.28 PM](/Users/vuoanh/Documents/courses/data_oriented_cpp/week3/latency_in_mem_access.png)Latency vs banwidth

Memory bus: transfers data from/to memory at a provided frequency

- multiple channels(interfaces)
- channel width 

memory latency: time it takes to transfers data (100 ns for main memory bus)

memory banwidth: amount of memory transfered per second (100GB/s)

cache: place to deposit data for intermediate storage

## Cache memory

- Data in cache is mirror in RAM, can temporarily have different value than RAM data

- Locality in time: memory that is accessed once tends to be accessed again => when data arrived in cache, keep it in cache for a while
- Locality in space: if an item is accessed in memory, other items at nearby memory address tend to be accessed soon =>  fill the cache with consecutive data to anticipate future data use

Cache line address lookup: associative memory:

- Address and data are stored together
- content seached for match

How Address Lookup [Tag | Set Index | Offset] - Example with 64-byte cache lines:

  - Offset (6 bits): Identifies which byte within the 64-byte cache line
    (2^6 = 64)
  - Set Index (varies): Identifies which cache set to look in
  - Tag (remaining bits): Identifies which specific memory block is in that
    set

### Apple M4 CPU Cache Architecture

```
Machine (3499MB total)
  Package L#0
    NUMANode L#0 (P#0 3499MB)
    L2 L#0 (4096KB)
      L1d L#0 (64KB) + L1i L#0 (128KB) + Core L#0 + PU L#0 (P#0)
      L1d L#1 (64KB) + L1i L#1 (128KB) + Core L#1 + PU L#1 (P#1)
      L1d L#2 (64KB) + L1i L#2 (128KB) + Core L#2 + PU L#2 (P#2)
      L1d L#3 (64KB) + L1i L#3 (128KB) + Core L#3 + PU L#3 (P#3)
      L1d L#4 (64KB) + L1i L#4 (128KB) + Core L#4 + PU L#4 (P#4)
      L1d L#5 (64KB) + L1i L#5 (128KB) + Core L#5 + PU L#5 (P#5)
    L2 L#1 (16MB)
      L1d L#6 (128KB) + L1i L#6 (192KB) + Core L#6 + PU L#6 (P#6)
      L1d L#7 (128KB) + L1i L#7 (192KB) + Core L#7 + PU L#7 (P#7)
      L1d L#8 (128KB) + L1i L#8 (192KB) + Core L#8 + PU L#8 (P#8)
      L1d L#9 (128KB) + L1i L#9 (192KB) + Core L#9 + PU L#9 (P#9)
  CoProc(OpenCL) "opencl0d0"
```

## Cache latency in practice

### Random traversal

![Screenshot 2025-11-17 at 12.11.22 PM](/Users/vuoanh/Documents/courses/data_oriented_cpp/week3/random-traversal.png)

Performance on intel Xeon Gold 6240R with 144 GB/s RAM

- 2048 elements => 1.51 ns (data fits into the L1 cache-32KB)
- L2 cache size: 1MB, latency: 3.4ns
- L3 cache size: 36.6MB, latency: 21ns
- 4*10^9 element => 118ns

## Data prefetching

Types:

- Consecutive prefetching: when data is accessed consecutively, prefetching takes place with increasing memory addresses (locality in space)
- Prefetching with strides: when data is accessed with regular intervals, the prefetching algorithm recognizes strides and prefetching takes place accordingly (locality in time)

### Padding fills cache line: NPAD =7

for linear transveral 

![Screenshot 2025-11-17 at 1.12.27 PM](/Users/vuoanh/Documents/courses/data_oriented_cpp/week3/padding-fills-cache-line.png)

![Screenshot 2025-11-17 at 1.16.05 PM](/Users/vuoanh/Documents/courses/data_oriented_cpp/week3/two-cache-lines-npad=15.png)

Rules: accesses memory in a predictable patterns and access things that are close in space

## Vector instructions - SIMD

If you have latency issue, you try to compensate by exploiting the bandwidth.

Example: linear traversal :

- loop transversal : prefetching multiple elements
- Lopp + optim flag: multiple elements per cpu cycle => parallelism

![Screenshot 2025-11-17 at 3.16.02 PM](/Users/vuoanh/Documents/courses/data_oriented_cpp/week3/compiler-vector-instruction.png)

Vector operations:

- mutiple same operations packed in a single CPU instruction
- SSE (16 B) fits 2 doubles/4 floats
- AVX (32B) fits 4 doubles/8 floats
- AVX2 (32B)
- AVX512 (64B) fits 8 doubles/16 floats
- M4 (16B)

How to get Vectorized code:

- use compiler directives
- help compiler identify opportunities ( uniform loops, data structures)
- write SIMD-capable code (avoid conditions in a loop -> break loop uniformity)
- assign vector operations manually using intrinsics
- use libraries like intel oneAPI math kernel lib, eigen C++

## RAM vs CPU

- when the data is small and can fit in the L1 cache, time scales with the number of operations => compute-bound
- When the data is large and must be stored in the RAM, increases in operations doesnt increase computing time as much => the program is memory bound

## FLOPS and AI

FLOPS - float-point operation : only +, -, *

## Roofline performance model

