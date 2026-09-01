# Fresh Theory Cheat-Sheet Staging Notes

Validated high-density facts to use when building the final sheet.

## Abbreviation Key

- OS = Operating System; CPU = Central Processing Unit; I/O = Input/Output.
- LDE = Limited Direct Execution; PCB = Process Control Block.
- FCFS/FIFO = First Come First Served / First In First Out.
- SJF = Shortest Job First; STCF/SRTF = Shortest Time-to-Completion First / Shortest Remaining Time First.
- RR = Round Robin; MLFQ = Multi-Level Feedback Queue.
- VM = Virtual Memory; MMU = Memory Management Unit; VA/PA = Virtual/Physical Address.
- VPN/PFN = Virtual Page Number / Physical Frame Number; PTE = Page-Table Entry; PTBR = Page-Table Base Register.
- AMAT = Average Memory Access Time; LRU/LFU = Least Recently/Frequently Used.
- IPC = Inter-Process Communication; FIFO (IPC) = named pipe.
- EOF = End Of File; PID = Process ID.

## CPU Virtualization / Processes

- LDE: run user code directly on CPU; retain control using user mode, traps/syscalls, timer interrupts.
- System call: wrapper prepares number/arguments -> trap -> kernel handler -> return-from-trap.
- Context switch: save old register context, choose ready process, restore next context.
- Trap does not necessarily cause a context switch; OS may resume the same process.
- RUNNING -> READY: preemption. RUNNING -> BLOCKED: waits for event/I/O. BLOCKED -> READY: event completes.
- Register context: PC, SP, general registers, flags. PCB also stores PID/state/scheduling/memory/file information.

## Scheduling

- turnaround = completion - arrival
- response = first_run - arrival
- waiting = turnaround - runtime
- FIFO/FCFS: non-preemptive arrival order; convoy effect.
- SJF: non-preemptive shortest ready job; optimal average turnaround under ideal known-runtime assumptions.
- STCF/SRTF: preemptive SJF; choose shortest remaining time.
- RR: fixed quantum; small quantum improves response but increases context-switch overhead; large quantum approaches FIFO.
- I/O completion: BLOCKED -> READY, not directly RUNNING.

## MLFQ

- Higher priority runs first; equal priority uses RR; new jobs start highest.
- Quantum = maximum one CPU turn. Allotment = cumulative CPU time allowed per job at a priority.
- Exhaust own allotment -> demote, regardless of yields/I/O; prevents gaming.
- Periodic boost moves all active jobs to highest priority; prevents starvation and handles behavior changes.

## Proportional Share

- Tickets represent relative share; lottery gives probabilistic long-run share, not exact short-term share.
- Ticket currency: divide a fixed user share locally; global share is preserved.
- Ticket transfer: temporarily move existing tickets; total preserved; useful client -> server.
- Ticket inflation: change ticket count; changes relative shares; safe only among trusted jobs.
- Lottery implementation: random winner in `[0,total-1]`; cumulative ticket scan; first cumulative total `> winner` runs.
- Lottery unfairness metric: `U = completion_first / completion_second`; ideal fairness approaches `1` over long runs.
- Ticket assignment is policy, not solved by the lottery mechanism.
- Stride: `stride = BIG / tickets`; run minimum `pass`; then `pass += stride`.
- New stride job should start near current minimum pass, not `0`, or it may monopolize CPU while catching up.
- Lottery: probabilistic, flexible, little history. Stride: deterministic, predictable, must maintain pass state.

## Memory / Address Translation

- Heap: `malloc` is uninitialized; `calloc` zeroes bytes; initialize before read; `realloc` may move; exactly one valid `free` after final use.
- Base/bounds: valid if virtual address is within bounds; `physical = base + virtual`; invalid access traps.
- Segmentation: separate variable-sized code/heap/stack mappings; saves unmapped gaps; causes external fragmentation.
- Stack segment grows toward lower addresses; protection bits control read/write/execute; read-only code can be shared.
- Internal fragmentation = waste inside allocated unit. External = free space split into non-contiguous holes.
- Free-space mechanisms: split large free block; coalesce adjacent free blocks; allocation header stores size.
- Fit policies: first = first adequate; next = continue from cursor; best = smallest adequate; worst = largest.
- Buddy allocator splits powers of two and recursively coalesces free buddies; fast merge, internal fragmentation.

## Paging / Replacement

- Virtual address = VPN + offset. Page table maps VPN -> PFN; offset stays unchanged.
- `VPN = VA / page_size`; `offset = VA % page_size`; `PA = PFN * page_size + offset`.
- Paging removes external fragmentation; partially used final page causes internal fragmentation.
- Valid=0 means illegal virtual page. Valid=1 and present=0 means legal but absent -> page fault.
- Page fault: trap -> find/free frame -> load page -> update PTE -> restart instruction.
- Dirty victim needs disk write; clean victim can be discarded/recovered without write-back.
- FIFO evicts oldest loaded and can show Belady anomaly. OPT evicts farthest future but is only benchmark.
- LRU evicts least recently used; LFU least frequently used; both rely on locality.
- Clock: reference 1 -> clear/give second chance; first reference 0 -> victim.
- Thrashing = working sets exceed RAM, causing constant paging and little useful work.
- `AMAT = P_hit*T_memory + P_miss*T_disk`; disk miss cost makes even small miss rates expensive.

## RAID

- RAID = Redundant Array of Inexpensive Disks; combines physical disks behind one logical-disk interface.
- `N` disks, capacity `B` each, sequential rate `S`, random rate `R` IOPS.
- RAID 0: stripe, capacity `N*B`, tolerate 0 failures; seq/random read/write up to `N*S` / `N*R`.
- RAID 1: mirror pairs, capacity `(N*B)/2`; random read `N*R`, random write `(N/2)*R`; each write updates both copies.
- RAID 4: dedicated parity, capacity `(N-1)*B`, tolerate 1; random read `(N-1)*R`, small random write `R/2`; parity disk bottleneck.
- RAID 5: rotating parity, capacity `(N-1)*B`, tolerate 1; random read `N*R`, small random write `(N/4)*R`.
- Small parity write: read old data + old parity; write new data + new parity = 4 physical I/Os.
- XOR reconstructs one missing block from remaining data and parity.
- Stripe = one row of chunks across disks; chunk = consecutive data placed on one disk before moving to next.
- Degraded mode = redundant RAID running after failure; rebuild reconstructs replacement and lowers performance.
- Hot spare = installed unused replacement disk. RAID 6 uses two parity values, capacity `(N-2)*B`, tolerates 2 failures.

## Inodes

- Inode = index node; stores file type, size, owner/group, permissions, times, hard-link count, and data-block pointers.
- Filename is stored in directory entry: `name -> inode number`; not normally inside inode.
- Inode byte location: `inode_table_start + inumber * sizeof(inode)`.
- Inodes per block: `block_size / inode_size`; inode-table block index: `(inumber * inode_size) / block_size`.
- Example: table starts 12 KB, inode size 256 B, inode 32 -> `12 KB + 32*256 B = 20 KB`.
- Direct capacity: `number_of_direct_pointers * block_size`; e.g. `12*4 KB = 48 KB`.
- Pointers per indirect block: `block_size / pointer_size`; e.g. `4096/4 = 1024`.
- Single-indirect capacity: `(block_size/pointer_size) * block_size`; e.g. `1024*4 KB = 4 MB`.
- Direct + single example: `(12+1024)*4 KB = 4144 KB`.
- Double-indirect capacity: `(block_size/pointer_size)^2 * block_size`; `1024^2*4 KB = 4 GB`.
- Triple-indirect capacity: `(block_size/pointer_size)^3 * block_size`; `1024^3*4 KB = 4 TB`.
- Direct crosses 0 pointer blocks; single crosses 1; double crosses 2; triple crosses 3.
- Extent = starting disk block + consecutive-block length; compact, but fragmented files need multiple extents.
