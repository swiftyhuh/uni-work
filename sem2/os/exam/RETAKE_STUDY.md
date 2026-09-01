# OS Written Retake - July 6

## Rules

- Maximum 3 minutes per question.
- Skip blocked questions and return later.
- Score: `1` correct, `0.5` incomplete, `0` wrong.
- Validate from lecture notes, not student answers.
- Write confirmed facts only; do not mix concepts.

## Exam Protocol

```text
0-3 min: scan; mark easy / medium / hard
3-25 min: easy questions, any order
25-48 min: medium questions
48-56 min: hard questions / partial answers
56-60 min: review
```

## June 30 - Baseline

- [x] Work through `exam/2026/subiect1.txt` question by question
- [x] Identify and classify main errors
- [x] Repair key misunderstandings during correction
- [ ] Repeat six hardest questions under 18 minutes

## July 1 - GSA / Shell

- [ ] Regex, grep, sed, awk
- [ ] `&&`, `||`, redirection, exit status
- [ ] `while read`, file tests, quoting, `shift`
- [ ] Two timed six-question sets; target 10/12

## July 2 - Processes / IPC

- [x] fork/wait/exit and process trees
- [x] exec, dup/dup2, popen/pclose
- [x] pipe/FIFO behavior
- [x] signals and blocking file operations
- [ ] Full mock; target 80% process/IPC

## July 3 - Threads / Sync

- [x] create/join and arguments
- [x] mutex, condition variable, rwlock
- [x] semaphore, barrier, deadlock
- [ ] Full mock; target 85% synchronization

## July 4 - OS Theory

- [x] states and scheduling
- [x] translation, segmentation, paging
- [x] cache/replacement and free-space policies
- [x] filesystem, inode, links, RAID
- [x] Ten theory questions; target 8/10

## July 5 - Final Simulation

- [ ] Full mock A; target 14/20
- [ ] Final handwritten cheat sheet
- [ ] Full mock B; target 14/20
- [ ] Rapid recall and early stop

## Error Log

| Date | Question/topic | Error type | Wrong idea | Correct rule | Retested |
|---|---|---|---|---|---|
| June 30 | Shell file pairs | knowledge | Thought duplicate tracking/vector was required | `while read F1 F2; do ...; done < file` processes each pair | yes |
| June 30 | Full pipe | mixed concepts | Expected SIGPIPE because other writers closed | Full pipe blocks while readers exist; SIGPIPE only when all readers closed | yes |
| June 30 | Voting limit | wrong primitive | Used barrier to limit concurrent voters | Counting semaphore initialized to limit | yes |
| June 30 | Condition variable | knowledge | Mutex behavior unclear | `cond_wait` unlocks, sleeps, then re-locks; use `while` | yes |
| June 30 | Theory traps | mixed concepts | Similar mechanisms mixed under pressure | Give definition + exact condition + consequence | yes |
| July 2 | Scheduling metrics | formula | Used duration instead of arrival for turnaround | turnaround = completion - arrival; waiting = turnaround - runtime | yes |
| July 2 | MLFQ gaming | knowledge | Gaming mechanism unclear | Count cumulative CPU allotment; yielding early does not avoid demotion | yes |
| July 2 | `read` state transitions | mixed concepts | Expected READY/BLOCKED for immediate EOF/data | Available data or EOF returns immediately; empty pipe with writer open blocks | yes |
| July 2 | `dup/dup2` | knowledge | Restore-redirection mechanism unknown | Save fd with `dup`, redirect/restore with `dup2`, close saved fd | yes |
| July 2 | Hard link deletion | precision | Called a hard link a copy; omitted open-file condition | Hard link is another directory entry to the same inode; data is freed at link count 0 only when no process has it open | yes |
| July 2 | `wait` descendants | precision | Said parent wakes after all child processes exit | `wait` waits for one terminated direct child, not grandchildren or all descendants | yes |
| July 2 | `wait(NULL)` | mixed concepts | Thought `NULL` means wait for the first child | `wait` selects any terminated direct child; `NULL` only means do not store exit status | yes |
| July 2 | Pipe with no readers | mixed concepts | Thought `write()` blocks until a reader opens | Writing with all read ends closed raises `SIGPIPE`; by default process terminates, or `write` returns `-1`/`EPIPE` if signal is handled or ignored | yes |
| July 2 | Zombie semantics | precision | Described zombie as parent not waiting for child to finish | Zombie is an already-terminated child whose exit status has not yet been reaped by its living parent using `wait`/`waitpid` | yes |
| July 2 | `execl` path lookup | mixed concepts | Evaluated command output before checking whether `execl("expr",...)` can find the executable | `execl` requires a path and does not search `PATH`; after it fails, following code runs. `execlp` searches `PATH` | yes |
| July 2 | `open` for overwrite | syntax | Used only `O_WRONLY`, which neither creates nor truncates | Use `O_WRONLY | O_CREAT | O_TRUNC` and provide a mode when `O_CREAT` is present; then `dup2(fd, 1)` | yes |
| July 2 | `dup2` then `close` | mechanism | Thought closing the original descriptor also closes its duplicate | After `dup2(p[1], 1)`, descriptors `p[1]` and `1` refer to the same pipe end independently; closing `p[1]` leaves descriptor `1` open | yes |
| July 3 | Thread loop argument `&i` | incomplete | Identified shared address but omitted data race, lifetime, and exact separate-storage fix | Give each thread stable unique storage (`ids[i]` or one heap allocation each) that remains valid until read | yes |
| July 3 | `pthread_cond_wait` return | precision | Explained unlock/sleep but omitted mutex reacquisition and treated signal as guarantee | `cond_wait` atomically unlocks and waits, then re-locks mutex before returning; always recheck predicate in `while` | yes |
| July 3 | Producer/consumer semaphore updates | incomplete | Found lock-order deadlock but missed that producer posted `empty` after insertion | Producer: wait `empty`, wait `mutex`, insert, post `mutex`, post `full`; consumer uses the inverse | yes |
| July 3 | Writer starvation | precision | Said a starved writer will eventually run | Starvation can continue indefinitely while other threads progress; deadlock prevents the involved threads from progressing | yes |
| July 3 | Mutex vs binary semaphore | precision | Gave counter mechanics but omitted mutex ownership | Binary semaphore initialized to 1 can provide exclusion, but mutex has an owner and only that thread should unlock; any thread may `sem_post` | yes |
| July 3 | Condition signal vs broadcast | wrong primitive operation | Chose broadcast for one newly available item to avoid starvation | Use `signal` when one waiter can proceed; `broadcast` wakes all and causes unnecessary contention when only one predicate instance is available | yes |
| July 3 | `pthread_join` before signal | ordering | Said program terminates when main joins before performing the only state update/signal | Signal the worker before joining; otherwise main waits for worker while worker waits for main, causing deadlock | yes |
| July 3 | Thread return-value ownership | incomplete | Chose heap allocation but omitted who frees returned storage | Worker may allocate and return an `int *`; after successful join, main owns, reads, and frees it | yes |
| July 3 | Barrier reinitialization | precision | Proposed initializing an already initialized reusable barrier with a new count | After no thread uses/waits on it, destroy then reinitialize, or use a separate barrier with the new count | yes |
| July 4 | Lottery ticket transfer | attention | Transferred A's tickets to B instead of the stated receiver C | Ticket transfer subtracts from donor and adds the same count to the named receiver; total tickets remain constant | yes |
| July 5 | External fragmentation remedy | precision | Said separated holes need to be compacted, without distinguishing normal C heap limitations | Coalescing joins only adjacent free blocks; compaction moves live allocations and normal C allocators cannot safely do that because pointers would become invalid | no |
| July 5 | Page-fault PTE bits | mixed concepts | Assumed present=0 always means swap and dirty=1 means no disk copy exists | Present=0 means page is absent from RAM; backing may be swap, file, or recreated. Dirty=1 means RAM copy changed and backing copy is missing or stale, so write-back is required before eviction | no |
| July 5 | Clock replacement trace | incomplete trace | Chose C correctly but said only that a bit becomes 0, omitting that inspected A and B are cleared | Clock clears each inspected reference bit of 1 and advances; first page already at 0 is evicted | no |
| July 5 | AMAT miss penalty | mixed concepts | Said a cache/page miss means OS must build back data | A miss/page fault normally loads the absent page from disk into RAM; RAID reconstruction is a separate failure-recovery operation. Small miss rates hurt because disk latency is orders of magnitude larger than RAM latency | no |
| July 5 | Blocking-I/O state trace | incomplete trace | Gave BLOCKED-to-READY completion behavior but omitted initial RUNNING-to-BLOCKED transition | Blocking I/O: RUNNING -> BLOCKED; completion: BLOCKED -> READY; scheduler later chooses READY -> RUNNING | no |
| July 5 | 2026 Subject 2 regex repetition | incomplete regex | Wrote one even-digit/lowercase/odd-digit/uppercase unit but omitted whole-string anchors and exactly three repetitions | Group the full unit and anchor it: `^([02468][a-z][13579][A-Z]){3}$` | yes |
| July 5 | 2026 Subject 2 odd-length grep | handwriting typo | Regex logic was correct; quote/file omission was not conceptual | Valid forms: `grep -E '^(..)*.$' file` and `grep -E '^.(..)*$' file` | yes |
| July 5 | 2026 Subject 2 sed second lowercase | knowledge | Needed a hint and used `[^a-z]*`, which can cross spaces into later words | Normalize spaces, then constrain the second-word prefix to `[A-Z]*[a-z][A-Z]*`; match the next `[a-z]` outside the kept capture | no |
| July 5 | 2026 Subject 2 deadlock prevention | mixed condition names | Correctly imposed global lock order but said it breaks mutual exclusion | Global resource order prevents a cycle and therefore breaks the circular-wait Coffman condition; mutual exclusion remains | no |
| July 5 | 2026 Subject 2 hard-link lifetime | incomplete | Said data is freed at link count 0 but omitted active open-file references | Unlink removes one name and decrements link count; storage is reclaimed after link count reaches 0 and no process still has the inode open | no |

## Score Log

| Date | Test | Score | Time | Main weakness |
|---|---|---:|---:|---|
| June 30 | 2026 Subject 1 guided | not timed | guided | shell pairs, IPC edge cases, primitive choice, theory traps |
| July 2 | Process/IPC 10-question check | 7/10 | guided, not timed | `wait(NULL)` precision, `execl` path lookup, overwrite flags, `dup2` descriptor copies |
| July 3 | Threads/Sync 10-question check | 8.5/10 | guided, not timed | condition-wait precision, producer/consumer counter update, starvation guarantee |
| July 3 | Threads/Sync unseen 6-question set | 3.5/6 | interrupted, not timed | semaphore ownership, signal vs broadcast, join ordering, thread return ownership |
| July 3 | Threads/Sync final unseen validation | 3.5/4 | not timed | barrier reinitialization lifecycle |
| July 4 | Process states/scheduling check | 5.5/6 | not timed | ticket-transfer attention error |
| July 5 | OS theory recap | 8/10 | not timed | page-fault bits, clock trace, AMAT explanation, full blocking-I/O state trace |
| July 5 | 2026 Subject 2 | 18/20 | guided, not timed | second-lowercase sed, Coffman condition name, full hard-link lifetime |
