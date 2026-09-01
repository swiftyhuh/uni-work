# DSA Final — Thu→Mon Study Plan

Exam: **Monday**. Today: **Thursday**. You're starting fresh but learning fast with hours to spare. This plan front-loads understanding, then shifts to active recall and timed practice — the two things that actually move exam scores.

**Golden rule:** don't just *read*. After each block, close the guide and reproduce the procedure on blank paper. If you can't, you don't know it yet.

---

## Thursday — Foundations & ADTs (the conceptual base)

**Goal:** understand complexity + the ADT zoo so everything later has a place to attach.

1. **Complexity (§1).** O vs Ω vs Θ, the hierarchy, loop counting, amortized analysis. Drill: classify 5 random polynomials into O/Ω/Θ.
2. **ADTs & Dynamic Array (§2–3).** What each container is for; why dynamic-array append is Θ(1) amortized.
3. **Linked lists (§4).** SLL/DLL/CSLL, and **write the reverse-SLL algorithm from memory** until automatic.
4. **End-of-day self-test:** explain amortized analysis out loud; reproduce reverse-SLL on paper.

---

## Friday — Linear structures & Heaps

**Goal:** master stacks, queues, and binary heaps (heaps are guaranteed Part B points).

1. **Stack & Queue (§5).** Implementations + the two-stack puzzle + **postfix evaluation** (do 3 expressions by hand).
2. **PriorityQueue & binary heap (§6).** Array indexing, sift-up/down. **Drill the sample exam B3** heap problem end to end, drawing every step. Then invent your own array and build a heap from it.
3. **Binomial heap** — concept + why mergeable (lighter touch).
4. **End-of-day self-test:** add 5 elements to an empty max-heap and remove twice, drawing each tree, with zero reference.

---

## Saturday — Hash tables & Trees (the heaviest day)

**Goal:** the two biggest topics; expect both on the exam.

1. **Hash tables (§7).** Separate chaining → open addressing → cuckoo/perfect/linked. **Do the sample exam B2** (hash table with AVL buckets): hash 8,99,40,19,56,16,17,28,62 and compute the load factor.
2. **Quiz questions** on open addressing (n vs m, probe-count) — make sure the *justifications* are crisp.
3. **Binary trees & BST (§8).** All four traversals on 2–3 trees; BST insert/delete (3 cases); the "what's at node X" quiz.
4. **AVL (§8).** The four rotations. Insert a sequence into an empty AVL, rebalancing as you go.
5. **End-of-day self-test:** build one hash table each way; do all traversals on a fresh tree; insert into an AVL hitting an LR or RL case.

---

## Sunday — Part C & full timed practice

**Goal:** convert knowledge into exam performance.

1. **Morning — Part C method (§10).** Write the **max-in-binary-tree** algorithm from memory. Work the **Quartiler** design fully (two-heap approach): representation, drawing, each operation's complexity, pseudocode for deleteTopQuartile.
2. **Midday — full mock exam.** Do the entire **SampleExamSubject.pdf** in **100 minutes, closed book, on paper.** No peeking.
3. **Afternoon — grade & patch.** Check against the guide; list every miss; redo those specific procedures until clean.
4. **Evening — sample questions.** Work through **Other_questions.pdf** Part A items; write a one-line justification for each.

---

## Monday — Light warm-up only

No new material. 60–90 min:

- Run the **§11 checklist** in the study guide — anything you can't do instantly, drill that one thing.
- Re-derive reverse-SLL and tree-max once each.
- Re-skim the §9 complexity table and the four AVL rotation cases.
- Stop early, rest. A calm, rested brain beats last-minute cramming.

---

## If you fall behind

Priority order (highest exam yield first): **Heaps → Hash tables → Tree traversals/AVL → Complexity → Part C algorithms → linked-list variants/skip lists.** Skip XOR lists, skip lists, binomial-heap internals, and perfect hashing details before you skip anything above.

---

## How I can help along the way

- Generate practice quizzes by topic and grade your answers.
- Walk through any worked example step by step.
- Make flashcards (Anki-style) for the complexity table and rotation cases.
- Build a one-page cheat-sheet for final review.
- Act as examiner for your Sunday mock and score it.

Just tell me which, and we go.
