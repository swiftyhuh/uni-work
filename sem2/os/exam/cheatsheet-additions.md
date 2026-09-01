# Cheat Sheet Additions / Fixes

Use this as running validated list before final HTML update.

## UNIX Command Line

```text
man 1 cmd | man 2 syscall | man 3 libc
fd: 0 stdin, 1 stdout, 2 stderr
cmd >out 2>&1
cmd 2>&1 | other
pipe: stdout -> stdin
exit status in shell: 0 = success/true, nonzero = fail/false
Ctrl-C sends SIGINT, Ctrl-D sends EOF, Ctrl-R searches history
```

## Regex / Grep / Sed / Awk

```text
shell * != regex *
regex any sequence = .*
last field = $NF, previous = $(NF-1)
word match = \<word\>
sed g = all matches on line
sed y/source/dest/ = char-by-char transliteration, not regex
```

Correct neighboring digit swap:

```bash
sed -E 's/([0-9])([0-9])/\2\1/g' a.txt
```

## Processes / IPC

```text
pipe: int p[2]; pipe(p); p[0] read, p[1] write
FIFO: named pipe; data in kernel buffer, not stored inside file
FIFO open(O_RDONLY) blocks until writer opens
FIFO open(O_WRONLY) blocks until reader opens
exec success: same PID, old image replaced, no code after exec
exec fail: returns -1, old process continues
popen -> pclose because pclose waits child
dup2(fd,1) redirects stdout to fd
open with O_CREAT needs mode argument
zombie remains until parent wait/waitpid, or parent exits and init/systemd reaps
```

Redirect file before exec:

```c
int fd = open("b.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
dup2(fd, 1);
execlp("cat", "cat", "a.txt", NULL);
```

## Threads / Sync

```text
threads share globals+heap, own stack+registers
race condition = result depends on scheduling
pass args: use id[i] array or struct array, not &i
do not return address of local stack variable
mutex protects critical section; lock only important shared access
cond_wait unlocks mutex while sleeping, re-locks before return
cond_wait must be inside while, not if
sem_wait: if value > 0 decrement; if value == 0 block
sem_post increments and wakes one waiting thread if any
barrier count = number of threads that must reach it
barrier count 1 = no real waiting
rwlock_rdlock only for reading; use wrlock for modification
deadlock prevention: fixed global lock order
```

## Processes / CPU Virtualization

```text
process = OS abstraction of running program
CPU virtualization = time-sharing CPU between processes
PCB/process control block = state, registers, PID, scheduling info, memory info
user mode = restricted program execution
kernel mode = privileged OS execution
trap = controlled entry from user mode to kernel mode for syscall/exception
return-from-trap = back to user mode
timer interrupt lets OS regain CPU from running process
context switch = save current process context, restore next process context
```

Limited Direct Execution:

```text
run program directly on CPU for speed
limit it using user mode + trap/syscall + timer interrupt
```

## Process States

```text
RUNNING = currently on CPU
READY = can run, waiting for CPU
WAIT/BLOCKED = waiting for I/O/event

READY -> RUNNING = scheduled
RUNNING -> READY = descheduled/preempted/timer interrupt
RUNNING -> WAIT = blocking call, I/O, read, wait, sleep
WAIT -> READY = event/I/O done

I/O path: RUNNING -> WAIT -> READY -> RUNNING
trap: I/O done does not go directly to RUNNING
```

## Scheduling

```text
turnaround = completion_time - arrival_time
response = first_run_time - arrival_time
waiting = turnaround - runtime

FIFO = simple, convoy effect, bad avg turnaround if long job first
SJF = shortest job first, optimal avg turnaround if jobs known
STCF = preemptive SJF, shortest remaining time
RR = round robin/time slice, good response, bad turnaround, context switch overhead
MLFQ = multiple priority queues, learns from behavior
```

MLFQ:

```text
if priority(A) > priority(B), A runs
same priority => round robin
new jobs start top priority
use full allotment => move down
periodic boost all to top => prevents starvation
```

## Deadlock

```text
deadlock = threads/processes wait forever for each other's resources

4 necessary conditions:
1 mutual exclusion
2 hold and wait
3 no preemption
4 circular wait

programmer prevention: break circular wait
how: acquire locks/resources in same global order everywhere
example: always lock A before B, never B before A
```

## Memory: Address Translation / Segmentation

```text
address space = process view of memory
virtual address translated to physical address by hardware + OS-managed tables/registers

base+bounds:
if VA < bounds => PA = base + VA
else trap/protection fault

segmentation:
one base+bounds per logical segment: code, heap, stack
segment selected from high bits of virtual address
stack grows downward/backwards
```

Fragmentation:

```text
segmentation = variable-size chunks => external fragmentation
paging = fixed-size pages => no external fragmentation, possible internal fragmentation + page table overhead
```

## Paging / Cache / Replacement

```text
physical memory acts as cache for virtual pages
page fault = page needed but not present in RAM
present bit 0 => page not in physical memory, OS must fetch from disk
dirty/modified bit = page was written; eviction needs disk write
reference/use bit = page was accessed recently

AMAT = hit_time + miss_rate * miss_penalty
```

Replacement:

```text
OPT/MIN = evict page used farthest in future; theoretical best
FIFO = evict oldest loaded page; can suffer Belady anomaly
LRU = evict least recently used; uses locality; no Belady anomaly
Clock = approximate LRU with use/reference bit
```

NRU priority:

```text
best victim = not referenced, not modified = (R=0, M=0)
then (0,1), then (1,0), then (1,1)
clean page cheaper to evict than dirty page
```

Expanded cache notes to include in final sheet because weak topic:

```text
RAM = small fast cache for disk-backed virtual pages
hit = page already in RAM
miss/page fault = page not in RAM, load from disk
if RAM full => evict victim page

FIFO example: evict page loaded earliest, even if used recently
LRU example: evict page not used for longest time
NRU chooses cheap+unlikely victim using R/M bits
R=0 => not used recently
M=0 => clean, no disk write needed
```

Cache organization:

```text
direct mapped: each block has one possible cache slot; fast but collisions/trashing
fully associative: block can go anywhere; flexible but search expensive
set associative: cache split into sets; block maps to one set, can use any line in set
set = block_address % nr_sets
```

## Free Space Management

```text
free space management = manage variable-size free/used memory chunks
external fragmentation = free space split into small holes

header before allocated block stores size/metadata
free(ptr) finds header at ptr - sizeof(header)
allocator needs requested_size + header_size

splitting = large free block split into allocated part + remaining free part
coalescing = merge adjacent free blocks after free()
```

Placement:

```text
first-fit = first block big enough; fast; small holes near start
best-fit = smallest block big enough; slow full search; tiny holes
worst-fit = largest block; slow full search; can create medium fragmentation
buddy = powers of 2 blocks; fast split/merge with buddy; internal fragmentation
```

## Filesystem / Inode / RAID

```text
filesystem = persistent storage organization
directory = maps filename -> inode number
inode = metadata + pointers to data blocks
metadata = type, permissions, owner, size, timestamps, link count, block pointers
```

Linux inode addressing:

```text
0-9 direct pointers
10 single indirect
11 double indirect
12 triple indirect

B = block size, A = address/pointer size, N = B/A pointers per block
single = N data blocks
double = N^2 data blocks
triple = N^3 data blocks
max file size = (10 + N + N^2 + N^3) * B
```

Links:

```text
hard link = new directory entry to same inode
hard link cannot cross filesystems/partitions
symlink = separate file containing path to target
unlink/rm removes name and decrements link count
data freed when link count is 0 and no process has file open
```

RAID:

```text
RAID 0 = striping; fast/full capacity; no redundancy
RAID 1 = mirroring; reliable; usable capacity about 50%; fast reads
RAID 4 = dedicated parity disk; tolerates 1 disk failure; parity disk bottleneck
RAID 5 = distributed parity; tolerates 1 disk failure; removes dedicated parity bottleneck
small write parity update = read old data + read old parity + write new data + write new parity
```
