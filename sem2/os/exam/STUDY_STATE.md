# OS Written Exam Study State

## Communication Mode

- Caveman full mode active.
- Keep answers short, direct, low-token.
- One big idea per message when teaching.
- Use clear examples.
- Correct me every time I am wrong or slightly off.
- Use only local/course sources unless I ask otherwise.
- Do not over-explain if I understand.
- Do not ask me to write code unless I ask for code practice.
- For theory, use exam-style answers.
- For code, keep teacher/simple style.
- Globals are allowed for exam/practice unless problem says otherwise and we decide to follow it.

## Main Sources

- `documentation/image.png` = official topic map.
- `documentation/Operating Systems.html` = official exam/course info.
- `ex/gsa/teaching-notes.pdf` = main lecture notes.
- `exam/thelinuxcommandline.pdf` = use only mapped chapters.
- `exam/Operating Systems - Three Easy Pieces.pdf` = use only mapped chapters.
- `exam/2024/13_iunie_2024.txt` = newest written exam model.
- `exam/!mibu/*.txt` = old written models.
- `exam/!mibu/REZOLVARI/*.txt` = solved old subjects.
- `exam/2024/EXAM prep.pdf` = useful recap for GSA/shell/process notes.

## Exam Format

- Written exam.
- 60 minutes.
- 20 free-answer questions.
- A4 double-sided handwritten cheat sheet allowed.
- Almost no time to search cheat sheet, so cheat sheet must contain only hard syntax, formulas, traps.

## Done So Far

### GSA

We worked through:
- `exam/learningsesiune/GSA/grepsedawkproblems.pdf`
- regex basics: `.`, `*`, `+`, `?`, `{}`, `[]`, `[^]`, `^`, `$`, `\<`, `\>`
- grep contains vs only contains vs does not contain
- sed capture groups and replacements
- sed `\1`, `\2`, etc. mean “put saved group”, not replace group
- sed `y/source/dest/` translates characters by position
- awk basics: `$0`, `$1`, `NR`, `NF`, `BEGIN`, `END`, arrays
- awk condition syntax: `$0 ~ /regex/`

Important discussed examples:
- `sed -E 's/([0-9]+)/\1\1/g'`
- `sed -E 's/((a)(b))|((b)(a))/\3\2\6\5/g'`
- `awk -F: '$1 > $2 {s += $3} END {print s}' a.txt`
- `ps -ef | grep -E -v "^UID" | awk '{print $1}' | sort | uniq -c`

### Bash / Shell

We used `exam/learningsesiune/BS/bash.txt`.
Need know:
- `$1`, `$@`, `$#`
- `[ ]` tests: `-f`, `-d`, `-x`, `-r`, `-e`, `-z`, `-n`
- `for A in "$@"; do ... done`
- `while`
- `shift`
- command substitution: `$(cmd)` or backticks
- arithmetic: `$((...))`
- combine `find`, `grep`, `sed`, `awk`, `sort`, `uniq`, `wc`, `du`, `file`

We decided no deeper bash for now.

### fork / wait / exit

Key points:
- `fork()` creates child process.
- After `fork`, both parent and child continue after same line.
- `fork()` returns:
  - `0` in child
  - child PID in parent
  - `-1` on error
- Forked child has copied memory, not shared memory like threads.
- `wait()` lets parent wait and collect child exit status.
- Zombie = child finished but parent did not call `wait/waitpid`.
- `exit(0)` stops current process.
- Process count questions are important.

Solved/explained:
- `exam/learningsesiune/fwe/2.c` linear hierarchy.
- Difference:
  - one parent creates many children
  - linear hierarchy: each child creates next child

### exec

Key points:
- successful `exec` replaces current process image
- same PID
- code after successful `exec` does not run
- failed `exec` returns `-1`, old process continues
- keep `exit(0)` after exec in child in case exec fails

Must know:
- `execl(path, argv0, arg1, ..., NULL)`
- `execlp(program, argv0, arg1, ..., NULL)` searches PATH
- `execv(path, argv_array)`
- `execvp(program, argv_array)` searches PATH
- `execv/execvp` useful when args already in `argv`

### popen

Key points:
- `popen(command, mode)` runs shell command and gives `FILE *`
- `"r"` means C reads command output
- `"w"` means C writes to command input
- close with `pclose`, not `fclose`, because child command must be waited
- can run full shell pipelines

Example:
- `FILE *fp = popen("ps -ef | awk '{print $1}'", "r");`

### dup / dup2

Key points:
- file descriptors:
  - `0` stdin
  - `1` stdout
  - `2` stderr
- `dup2(oldfd, newfd)` makes `newfd` point where `oldfd` points.
- Used before `exec` for redirection/pipelines.

Examples:
- `dup2(fd, 1)` redirects stdout to file.
- `dup2(p[1], 1)` makes command write into pipe.
- `dup2(p[0], 0)` makes command read from pipe.
- To undo: `int saved = dup(1); ... dup2(saved, 1);`

### pipes

Key points:
- `int p[2]; pipe(p);`
- `p[0]` = read end
- `p[1]` = write end
- Create pipe before `fork`.
- Parent/child inherit both ends.
- Close unused ends.
- For two-way communication use two pipes:
  - `p2c`
  - `c2p`

Behavior:
- `read` on empty pipe waits if writer still open.
- `read` returns `0` EOF if all write ends closed.
- `write` can block if pipe full.

### FIFO

Key points:
- FIFO = named pipe.
- Has path/name in filesystem.
- Can connect unrelated processes.
- Create with `mkfifo("a2b", 0600)` or shell `mkfifo a2b`.
- Open with `open("a2b", O_RDONLY)` or `open("a2b", O_WRONLY)`.
- Read-only open waits for writer.
- Write-only open waits for reader.
- FIFO is not deleted automatically; use `unlink` or `rm`.
- For two-way communication use two FIFOs:
  - `a2b`
  - `b2a`
- One FIFO for bidirectional communication is bad because same stream can cause process to read own/unexpected data.

### signals

Key points:
- signal = software interrupt to process.
- `Ctrl+C` sends `SIGINT`.
- `SIGKILL` cannot be caught/ignored.
- `SIGUSR1`, `SIGUSR2` are user signals.
- Register handler: `signal(SIGUSR1, handler);`
- Send signal: `kill(pid, SIGUSR1);`
- Handler signature: `void handler(int sig)`.
- When signal arrives, normal execution interrupted, handler runs, then process continues if signal does not terminate it.

## Need To Do Next

### 1. Quick Recap Yesterday

Do 10-15 exam questions on:
- fork return values
- wait/zombie
- exec success/fail
- pipe read/write behavior
- FIFO blocking behavior
- signal basics

### 2. Threads Sync Fast Rewind

Need cover:
- `pthread_create`, `pthread_join`
- passing args
- returning values
- race condition
- mutex
- rwlock
- condition variable
- semaphore
- barrier
- deadlock

Use global variables for simple implementations.

Important teacher traps:
- critical section must be small
- `pthread_cond_wait` unlocks mutex while waiting, then re-locks before returning
- must recheck condition after `pthread_cond_wait`
- semaphore `sem_wait` decrements / may block, `sem_post` increments
- barrier initialized with 1 lets every caller pass immediately
- replacing mutex lock with read lock is wrong if data is modified
- deadlock prevention: lock resources in same order

### 3. OS Theory

Need cover from image:
- processes
- process states
- scheduling
- deadlock
- address translation
- segmentation
- paging
- replacement policies
- free space management
- filesystem
- Linux inode
- RAID

### 4. Cheat Sheet

Build smart A4 double-sided sheet after weak topics.
Should include only:
- syntax hard to remember
- formulas
- traps
- compact tables

Must include:
- GSA syntax
- shell tests
- fork/exec/pipe/FIFO/popen/dup2 patterns
- pthread sync syntax
- process state transitions
- inode formulas
- memory formulas
- replacement policy table
- deadlock conditions/prevention

## Working Rule Tomorrow

- Continue exactly in this style.
- Short, exam-focused.
- Ask question-by-question when recapping.
- No large code unless requested.
- Correct wrong answers immediately.
- Use old exam patterns from `exam/!mibu`.
