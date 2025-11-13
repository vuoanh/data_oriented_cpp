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

## Latency vs banwidth

## Cache memory

### Apple M4 CPU Cache Architecture

 #### L1 Cache (Per Core)

Performance Cores (P-cores):
  - L1 Instruction Cache: 192 KB per core
  - L1 Data Cache: 128 KB per core
  - Total L1: 320 KB per P-core
  - Latency: ~3-4 cycles

 Efficiency Cores (E-cores):
  - L1 Instruction Cache: 128 KB per core
  - L1 Data Cache: 64 KB per core
  - Total L1: 192 KB per E-core
  - Latency: ~3-4 cycles

#### L2 Cache (Shared within cluster)

 Performance Cores:
  - 12 MB shared L2 per P-core cluster
  - Shared among P-cores in the same cluster
  - Latency: ~15-20 cycles

  Efficiency Cores:
  - 4 MB shared L2 per E-core cluster
  - Latency: ~15-20 cycles

 #### System Level Cache (SLC)

  - Shared across all CPU cores and GPU
  - Acts as a unified L3-equivalent cache
  - Size varies by chip variant (typically 16-32 MB)
  - Latency: ~40-50 cycles

#### M4 Configuration Examples

| Chip      | P-cores | E-cores | Total L1 | P-core L2 | E-core L2 |
| --------- | ------- | ------- | -------- | --------- | --------- |
| M4 (base) | 4       | 6       | ~4.4 MB  | 12 MB     | 4 MB      |
| M4 Pro    | 10-12   | 4-6     | ~8+ MB   | 24 MB     | 8 MB      |
| M4 Max    | 14-16   | 4-6     | ~10+ MB  | 36 MB     | 8 MB      |





