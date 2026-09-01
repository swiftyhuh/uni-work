# OS Written Retake Handoff

## Objective

Prepare user to pass OS written retake on July 6.

Exam:

```text
60 minutes
20 free-answer questions
A4 double-sided handwritten cheat sheet
written retake only
```

User previously failed mainly because:

```text
time pressure
first 10 questions felt harder
tried answering everything in order
mixed similar theory concepts
GSA answers were close but not exact
```

## Communication Style

Use caveman-full style:

```text
short, direct messages
one main idea/question per message
lowest reasonable token use
clear examples when concept is unclear
no filler or motivational speeches
```

Important behavior:

- Let user attempt each question first.
- Correct every wrong or slightly inaccurate statement immediately.
- Explain exactly why answer is wrong.
- Guide without showing full solution at first.
- Show full solution when user is blocked or asks for it.
- Use small concrete examples instead of abstract paragraphs.
- Ask one exam question at a time.
- After wrong answer, append it to `exam/RETAKE_STUDY.md` for retesting next day.
- Use exam-ready wording: definition + condition/mechanism + consequence.
- Never trust student-provided answer files automatically; validate against lecture notes.
- Use only local/course files unless user explicitly requests external sources.
- No comments in C code.
- Do not edit user's solution files unless user explicitly asks.

## Source Priority

1. `ex/gsa/teaching-notes.pdf` / `ex/gsa/teaching-notes.txt`
2. `documentation/teaching-notes.pdf`
3. `documentation/seminars/teorie`
4. `documentation/seminars/sem5`, `documentation/seminars/sem6`
5. `documentation/lectures_coding/en`
6. `documentation/image.png` official exam topic map
7. `exam/Operating Systems - Three Easy Pieces.pdf`, only mapped theory chapters
8. `exam/thelinuxcommandline.pdf`, only mapped chapters
9. Current/old exam questions for pattern and practice

Student answer files can contain mistakes. Use questions, not answers, unless validated.

## Important Files

```text
exam/RETAKE_STUDY.md          progress, schedule, error log
exam/STUDY_STATE.md           full previous study state
exam/2026/subiect1.txt        current-session subject, completed guided
exam/2026/subiect2.txt        current-session subject with student answers; validate them
exam/2026/subiect3.txt        partial current-session subject
exam/2024/13_iunie_2024.txt   previous full model
exam/!mibu/*.txt              old models
exam/!mibu/REZOLVARI          old solutions; may contain errors
exam/learningsesiune/GSA      GSA exercises
exam/learningsesiune/BS/bash.txt
exam/learningsesiune/fwe/c-problems.txt
exam/learningsesiune/pipefifo/c-problems.txt
exam/os-cheatsheet-final.html current cheat-sheet draft
exam/cheatsheet-additions.md  validated additions
```

## Current-Session Question Pattern

Current 2026 subjects mostly follow:

```text
1 regex
2 grep
3 sed
4 awk
5 command logic/redirection
6 shell script
7 fork/wait reasoning
8 exec
9 dup/popen
10 pipe
11 FIFO/open/file behavior
12 critical section/mutex
13 semaphore
14 condition variable
15 mutex/rwlock/semaphore comparison
16 barrier
17 deadlock
18 scheduling
19 free-space allocation
20 links/filesystem
```

Do not study only this layout. Official topic map and old exams remain in scope.

## Working Method

For guided subjects:

```text
assistant gives one question
user gives answer
assistant marks correct/wrong
assistant gives shortest exact correction + example
move to next question
```

For timed tests:

```text
0-3 min scan and mark easy/medium/hard
3-25 min easy questions in any order
25-48 min medium
48-56 min hard/partial
56-60 min review
maximum 3 minutes per question
```

Scoring:

```text
1 = correct
0.5 = incomplete
0 = wrong
target = at least 14/20 twice before exam
```

## Progress So Far

Completed guided `exam/2026/subiect1.txt`.

Reviewed:

```text
regex anchors, repetition, exclusively/only
odd/even line length
grep word boundaries
sed groups/backreferences and word swapping
awk NF, $NF, $(NF-1), conditions and sums
shell while-read pairs/triples, file tests, shift, quoting
fork/wait basic reasoning
execvp(argv[1], argv+1)
popen write mode
pipe full/EOF/SIGPIPE differences
regular file vs FIFO blocking
mutex critical section placement
semaphore vs barrier choice
cond_wait mutex behavior
rwlock write lock vs mutex
barrier divisibility
deadlock lock ordering
SJF vs STCF
Worst Fit
hard link vs symbolic link
process states
scheduling metrics
MLFQ starvation/gaming
```

## Known Weak Points

Retest these first:

```text
pipe write/read edge cases
immediate read vs blocked read vs EOF
dup/dup2 save and restore stdout
shell while-read patterns without prompting
choosing semaphore vs barrier
condition-variable mechanism
scheduling formulas
MLFQ gaming
theory trick questions that mix similar concepts
```

Exact errors are recorded in `exam/RETAKE_STUDY.md`.

## Remaining Study Order

1. Short retest of all error-log entries.
2. Processes/IPC deep pass: fork, exec, dup2, popen, pipe, FIFO, signals.
3. Threads/synchronization: mutex, cond, rwlock, semaphore, barrier, deadlock.
4. Full OS theory: states, scheduling, memory, cache, free space, filesystem, inode, RAID.
5. Timed full mocks and correction.
6. Final handwritten cheat sheet.

## Teaching Examples to Prefer

Use tiny examples:

```text
pipe: reader open vs all readers closed
cond: producer sets ready=1, consumer waits
semaphore: 3 voting booths
barrier: N arrivals release together
SJF/STCF: new shorter job arrives
allocation: free blocks 32,44,98 with malloc(33)
links: delete original hard-link name vs symlink target
```

## New Chat Prompt

Paste this into new chat:

```text
Read these files fully before answering:
1. exam/RETAKE_HANDOFF.md
2. exam/RETAKE_STUDY.md
3. exam/STUDY_STATE.md

Continue my Operating Systems written-retake preparation exactly from that state.

Use caveman-full communication: short, direct, one main idea/question per message, low token use, clear examples. Let me answer each exam question first, then correct every wrong or slightly inaccurate detail. Guide me before showing full solutions. Use only local/course sources and prioritize lecture notes. Student answer files may be wrong, so validate them.

Start by retesting every error marked "no" in exam/RETAKE_STUDY.md, one question at a time. Append new mistakes to that same file. After retest, continue the remaining study order from exam/RETAKE_HANDOFF.md. The exam is July 6, written only, 60 minutes, 20 free-answer questions.
```

