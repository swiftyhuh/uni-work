# DSA Final — Master Study Guide

Built from your course (Lectures 1–14, seminars, labs, sample exam). Covers everything that appears on the exam. Read top to bottom the first time; after that, use it as a reference and drill the worked examples.

---

## 0. How the exam works

100 minutes, closed book, 3 parts on separate sheets:

- **Part A** — multiple choice, *justify every answer* (4 questions × 0.4p). Tests concepts: complexity classes, hashing behavior, stack/queue mechanics, tree properties.
- **Part B** — worked problems (3 × 1p). Typically: tree traversals, build/modify a hash table, build/modify a binary heap. You draw the result step by step.
- **Part C** — write pseudocode (C1 ~1.4p mandatory + choose C2 *or* C3). C1 is a concrete algorithm (e.g. reverse a linked list). C2/C3 is "design an ADT": pick a representation, draw it, explain operations, write one operation in pseudocode.

Key rules they give you: you may ignore deallocation (assume Θ(1)), you don't implement resize, and in Part C you must implement every helper you use (can't assume operations exist unless stated).

**Scoring strategy:** Part A justifications are cheap points — never leave them blank. Part B is mechanical once you know the procedures (practice them until automatic). Part C is where prep pays off — C1 is always a standard algorithm.

---

## 1. Complexity analysis

### The three notations

- **O(f)** — *upper bound.* `g ∈ O(f)` if g grows **no faster than** f. "Worst case is at most this."
- **Ω(f)** — *lower bound.* g grows **at least as fast as** f.
- **Θ(f)** — *tight bound.* g ∈ O(f) **and** g ∈ Ω(f). g grows exactly like f.

Formal: `g ∈ O(f)` iff ∃ c>0, n₀ such that g(n) ≤ c·f(n) for all n ≥ n₀.

### Computing complexity of a function

Drop constants and lower-order terms; keep the dominant term.

> **Example (sample exam A4):** `12n³ + n·log₂n + 52`. Dominant term is n³.
> So it is **Θ(n³)**. Also true: O(n³), O(n⁴), Ω(n³), Ω(n²), Ω(1). **False:** O(n²), Θ(n·logn), Θ(n⁴).
> Lesson: O is *any upper bound or looser*, Ω is *any lower bound or looser*, Θ is *exactly one class*.

### Complexity hierarchy (memorize the order)

```
Θ(1) < Θ(log n) < Θ(√n) < Θ(n) < Θ(n log n) < Θ(n²) < Θ(n³) < Θ(2ⁿ) < Θ(n!)
```

### Loop counting cheat-sheet

- Single loop `i = 1..n` → Θ(n)
- Nested `i=1..n`, `j=1..n` → Θ(n²)
- Loop where index **doubles/halves** (`i = i*2`) → Θ(log n)
- Nested where inner depends on outer (`j = 1..i`) → Σi = n(n+1)/2 → Θ(n²)

### Best / worst / average case

A single algorithm has all three. Example: linear search — best Θ(1) (first element), worst Θ(n) (absent/last), average Θ(n). These are separate from O/Ω/Θ (which describe *any* function's growth).

### Amortized analysis

Cost **averaged over a sequence** of operations, when occasional operations are expensive but rare.

> **Canonical case — Dynamic Array append.** Most appends are Θ(1). When full, you resize (allocate double, copy all n elements = Θ(n)). But doubling means resizes are rare: across n appends the total copying work is n + n/2 + n/4 + … < 2n. So **amortized cost per append = Θ(1)**, even though one append can be Θ(n).

This is why the sample exam's Quartiler asks for "O(log n) **amortized**" — it expects a structure (like a dynamic array / heap) whose occasional resize is amortized away.

---

## 2. ADTs, data structures, pseudocode

- **ADT (Abstract Data Type)** = *what* operations exist + their meaning (interface/contract). Says nothing about implementation. E.g. ADT Stack = {push, pop, top, isEmpty}.
- **Data structure** = *how* you store data in memory (array, linked nodes). One ADT can have many data-structure implementations, each with different complexities.

**Pseudocode conventions used in this course:** subalgorithms with `pre`/`post` conditions, pass containers by reference, `▷` for comments, explicit element/node types. In Part C, follow this style.

### Container ADTs at a glance

| ADT | Stores | Key idea |
|-----|--------|----------|
| **Bag (Multiset)** | elements *with* duplicates | `add`, `remove`, `search`, `nrOccurrences` |
| **Set** | elements, **no** duplicates | adding an existing element does nothing |
| **Map (Dictionary)** | (key → value) pairs, unique keys | `add(k,v)`, `search(k)`, `remove(k)` |
| **MultiMap** | one key → **multiple** values | `add(k,v)` keeps all values for k |
| **Matrix** | 2D (line, col) → value | often stored on a dynamic array; sparse variants |
| **List (Indexed/Iterated)** | ordered, position matters | get/set by position, or iterate |
| **Stack** | LIFO | `push`, `pop`, `top` |
| **Queue** | FIFO | `push` (rear), `pop` (front) |
| **Deque** | double-ended queue | add/remove at *both* ends |
| **PriorityQueue** | elements + priorities | always remove the **highest priority** |

"**Sorted**" variants (SortedSet, SortedMap, SortedBag…) keep elements in order, enabling ordered iteration but constraining the implementation (relation/comparator given at creation).

---

## 3. Dynamic Array

The foundational structure. A static array + tracked `capacity` and `size`.

- `getElement(i)` / `setElement(i,v)` → **Θ(1)**
- append at end → **Θ(1) amortized** (Θ(n) on resize; see §1)
- insert/remove at arbitrary position → **Θ(n)** (must shift elements)
- **Resize** = allocate a new array (capacity × 2), copy elements, free old. Done when full.

Used to implement: Bag, Set, Map, Matrix, Stack, Queue (circular), binary heap.

---

## 4. Linked lists

Nodes holding data + reference(s) to other node(s). No shifting on insert/remove, but no O(1) random access.

### Singly Linked List (SLL)

Node = `{info, next}`; list keeps `head` (sometimes `tail`).

- Insert/remove **at front** → Θ(1)
- Insert at end → Θ(1) *if* you keep a tail pointer, else Θ(n)
- Search / access position i → Θ(n)

> **C1 classic — Reverse an SLL in Θ(n) time, Θ(1) space.** Walk the list with three pointers, flipping each `next`:
> ```
> subalgorithm reverse(list):
>     prev ← NIL
>     curr ← list.head
>     while curr ≠ NIL execute
>         nxt ← curr.next     ▷ save next
>         curr.next ← prev    ▷ reverse the link
>         prev ← curr         ▷ advance
>         curr ← nxt
>     end-while
>     list.head ← prev
> end-subalgorithm
> ```
> Θ(n): visits each node once. Θ(1) extra space: only 3 pointers regardless of n. **Know this cold — it's a recurring C1.**

### Doubly Linked List (DLL)

Node = `{info, prev, next}`. Allows O(1) removal of a known node and backward traversal. Costs an extra pointer per node.

### Circular SLL (CSLL)

Last node's `next` points back to head. Useful for round-robin; lets you reach head from any node.

### Linked list on an array

Simulate nodes using parallel arrays / an array of structs, with an integer "next" index instead of a pointer, plus a **free list** of unused slots. Gives linked-list flexibility with array storage (cache-friendly, no dynamic allocation).

### XOR linked list

A doubly linked list using **one** pointer field per node = `prev XOR next`. Saves memory; you recover the other neighbor by XOR-ing with the address you came from. Trade-off: can't be traversed without knowing a starting neighbor.

### Skip list

A layered set of SLLs: bottom layer has all elements; higher layers are "express lanes" built probabilistically. Search/insert/delete in **O(log n) expected** time — a simpler probabilistic alternative to balanced trees.

---

## 5. Stack and Queue

### Stack — LIFO

`push`/`pop`/`top` all **Θ(1)**. Implement on a dynamic array (push/pop at end) or SLL (push/pop at front).

> **Sample exam A2 (two-stack puzzle).** Push 1,2,3,4,5,6 onto S1. Pop 4 times, pushing each onto S2. Popping S1 gives 6,5,4,3 → S2 now holds (bottom→top) 6,5,4,**3**. Pop S2 once → removes 3. Top of S2 is now **4**. *Answer: d) 4.* Trick: a stack reverses order; track the top carefully.

> **Sample exam A3 / Part-C topic — Postfix (RPN) evaluation.** Scan left→right: push numbers; on an operator pop the top two, apply, push the result.
> Evaluate `4 6 7 + 1 – 2 5 * + +`:
> - push 4,6,7 → [4,6,7]
> - `+`: 6+7=13 → [4,13]
> - `1` → [4,13,1]; `–`: 13−1=12 → [4,12]
> - `2`,`5` → [4,12,2,5]; `*`: 2*5=10 → [4,12,10]
> - `+`: 12+10=22 → [4,22]; `+`: 4+22=26 → [**26**]
> Result = 26 → *"a value above 15."* (Note operand order for `–` and `/`: it's `second_popped OP first_popped`.)

### Queue — FIFO

`push` at rear, `pop` at front, both **Θ(1)**. Best implemented as a **circular dynamic array** (front/rear indices wrap with modulo) or an SLL with head+tail.

### Deque

Add/remove at both ends in Θ(1). Implement on a DLL or circular array.

---

## 6. PriorityQueue and Heaps

**ADT PriorityQueue:** `push(elem, priority)`, `pop` (removes highest priority), `top`. Best implemented with a **heap**.

### Binary heap (the star of Part B)

A **complete binary tree** stored in an array, satisfying the **heap property**:
- **Max-heap:** every parent ≥ its children (root = max).
- **Min-heap:** every parent ≤ its children (root = min).

**Array indexing (1-based):** node at i → children at **2i** and **2i+1**, parent at **⌊i/2⌋**. (0-based: children `2i+1`, `2i+2`, parent `⌊(i−1)/2⌋`.)

**Operations:**
- `add` — put new element at the end, **sift-up** (swap with parent while it violates the property). Θ(log n).
- `remove root` (poll) — move last element to root, **sift-down** (swap with the larger child for max-heap, until valid). Θ(log n).
- `peek` — Θ(1).
- **build-heap** from an array — sift-down from the last internal node up to root → **Θ(n)** (better than n inserts).

> **Sample exam B3 walk-through.** Array `[41,54,13,73,68,98,63,100,76]` (1-based). This is a **MIN-heap** problem — the giveaway is that it asks you to fix it by swapping *two* elements, i.e. it's one swap from valid, which only holds under the min-heap reading.
> - Check parent ≤ child: the only violation is root 41 vs child 13 (41 > 13). **Swap 41 and 13** → valid min-heap `[13,54,41,73,68,98,63,100,76]`.
> - **Add 19, 18, 59:** each goes to the next array slot, then sift-up (swap while *smaller* than parent); redraw after each.
> - **Remove:** removeRoot returns the min (root); move last element → root, sift-down swapping with the *smaller* child; redraw.
> Practice drawing complete-tree levels: positions fill left-to-right, top-to-bottom. (Full worked solution in Worksheet 4.)

**Heapsort:** build a max-heap, repeatedly swap root with last element and shrink + sift-down → sorted array in **Θ(n log n)**, in place.

### Binomial heap

A collection of binomial trees (each Bₖ has 2ᵏ nodes). Supports **merge/union in O(log n)**, which a binary heap can't do efficiently. Insert and extract-min are O(log n). Know the concept and *why* it exists (mergeable heap); you won't be asked to draw complex unions, but understand the structure.

---

## 7. Hash tables

Store elements for **average O(1)** search/insert/delete via a **hash function** mapping keys → table positions.

- **Hash function — division method:** `h(k) = k mod m` (m = table size, ideally prime / not a power of 2).
- **Load factor α = n / m** (elements / positions). Performance degrades as α grows.
- **Collision** = two keys hash to the same position. The whole topic is *how to resolve collisions*.

### Separate chaining

Each position holds a **linked list** (or other structure) of all elements hashing there. Insert = prepend (Θ(1)). Search = scan that position's list. With good hashing, lists are short → average O(1). **n can exceed m** (chains just get longer).

> Variant from the sample exam (B2): each bucket is the **root of an AVL tree** instead of a list → search within a bucket becomes O(log(chain length)).

### Coalesced chaining

Chains live **inside the table itself** (no external lists); collided elements go to free slots and are linked via index pointers. Saves the overhead of separate lists.

### Open addressing

**All elements live in the table array**; on collision, **probe** for the next free slot. Requires **α ≤ 1** (n ≤ m).

- **Linear probing:** try `h(k), h(k)+1, h(k)+2, …` (mod m). Simple but causes *primary clustering*.
- **Quadratic probing:** try `h(k)+1², h(k)+2², …`. Reduces clustering; may not visit all slots unless m and constants are chosen well.
- **Double hashing:** step size from a second hash `h₂(k)`. Best distribution.

> **Quiz I (Other_questions):** "Can n > m with open addressing?" → **No.** Every element occupies a distinct slot, so n ≤ m always. (Answer a.)
> **Quiz II / Sample A1:** "Searching for e, can more than n positions be checked?" → **Yes, regardless of whether e is present (c).** Probing can pass over empty *and* deleted/occupied slots; the probe sequence length isn't bounded by n. Deletion needs **tombstones** (mark slot deleted, don't empty it) so probe chains aren't broken.

### Cuckoo hashing

**Two** hash tables with **two** hash functions. Each element sits in one of its two possible positions. On insert collision, **kick out** the resident element and re-insert *it* into its alternate table — repeat. If it cycles → resize & rehash. Guarantees **worst-case O(1) search** (check just 2 positions).

### Perfect hashing

For a **static** key set: a two-level scheme guaranteeing **no collisions** and **worst-case O(1)** search. Second-level tables sized to the square of their bucket count to avoid collisions.

### Linked hash table

A hash table that also maintains a linked list threading the entries to preserve **insertion order** for iteration (like Java's LinkedHashMap).

---

## 8. Trees

### Binary tree basics

Each node has ≤ 2 children (left/right). **Representations:** node with `{info, left, right}` (and optionally `parent` — but note the exam often says *don't* store parent). Can also store in an array.

### Traversals (Part B staple — memorize)

- **Preorder:** Root → Left → Right
- **Inorder:** Left → Root → Right  *(gives sorted order for a BST)*
- **Postorder:** Left → Right → Root
- **Level order (BFS):** level by level, left to right — use a **queue**.

> **Method for B1:** do them recursively in your head/paper. For preorder, write the root, then fully traverse left subtree, then right. For level order, process the root, enqueue its children, dequeue and repeat.

> **C2 classic — max value in a binary tree** (no parent pointer):
> ```
> function maxValue(node):           ▷ returns max in subtree rooted at node
>     if node = NIL then
>         return −∞
>     end-if
>     leftMax  ← maxValue(node.left)
>     rightMax ← maxValue(node.right)
>     return max(node.info, leftMax, rightMax)
> ```
> Complexity **Θ(n)** — visits every node once. Recursion uses the call stack (an auxiliary container); the iterative version uses an explicit stack/queue.

### Binary Search Tree (BST)

Ordering invariant: for every node, **all keys in the left subtree < node < all keys in the right subtree.**

- **Search / insert / delete:** O(h), where h = height. Balanced → O(log n); degenerate (sorted insertions) → O(n).
- **Inorder traversal yields keys in ascending order.**
- **Delete** 3 cases: (1) leaf → just remove; (2) one child → replace node with that child; (3) two children → replace with **inorder successor** (smallest in right subtree) or predecessor, then delete that.

> **Quiz III (Other_questions):** "what value could be at node X?" → use the BST property: X must be **greater than everything in its left-ancestor subtree and less than its right bounds.** Find the open interval forced by the path from the root and pick the option inside it.

### AVL trees (Lectures 13–14 — important)

A **self-balancing BST.** For every node, **balance factor** `bf = height(left) − height(right) ∈ {−1, 0, +1}`. If an insert/delete makes |bf| = 2, **rotate** to rebalance. Guarantees **height Θ(log n)** → all operations O(log n).

**Four rotation cases** (named by where the imbalance is):

- **LL** (left-heavy, inserted in left-left) → single **right** rotation.
- **RR** (right-heavy, right-right) → single **left** rotation.
- **LR** (left-heavy, but inserted in left-right) → **left** rotation on child, then **right** on node.
- **RL** (right-heavy, right-left) → **right** on child, then **left** on node.

> **How to spot the case:** find the lowest unbalanced node Z. Look at the path to the newly inserted node: the first two steps (L/L, R/R, L/R, R/L) name the case. Apply the matching rotation; update heights.

**Deletion** is the same idea but you may need to rebalance at multiple ancestors going up.

---

## 9. Operation complexity reference table

| Structure | Access/Search | Insert | Delete | Notes |
|-----------|---------------|--------|--------|-------|
| Dynamic array | Θ(1) index / Θ(n) search | Θ(1) amort. end, Θ(n) middle | Θ(n) | resize doubles |
| SLL / DLL | Θ(n) | Θ(1) at known end | Θ(1) at known node | no random access |
| Stack / Queue | — | Θ(1) | Θ(1) | LIFO / FIFO |
| Binary heap | Θ(1) peek | Θ(log n) | Θ(log n) root | build = Θ(n) |
| Hash (chaining) | Θ(1) avg, Θ(n) worst | Θ(1) avg | Θ(1) avg | depends on α |
| Hash (open addr.) | Θ(1) avg | Θ(1) avg | Θ(1) avg + tombstones | needs n ≤ m |
| Cuckoo hash | **Θ(1) worst** | Θ(1) amort. | Θ(1) | 2 tables |
| BST (balanced) | Θ(log n) | Θ(log n) | Θ(log n) | Θ(n) if degenerate |
| AVL tree | Θ(log n) | Θ(log n) | Θ(log n) | always balanced |
| Skip list | Θ(log n) exp. | Θ(log n) exp. | Θ(log n) exp. | probabilistic |

---

## 10. Part C — how to design an ADT (the C2/C3 method)

The Quartiler-style problem gives you operations + required complexities and asks you to design a representation. Method:

1. **Match complexities to structures.** "add O(log n), get/delete extreme in Θ(1) or O(log n)" → screams **heap**. "ordered iteration / by-position" → BST/AVL or sorted array. "by key O(1)" → hash table.
2. **Pick a representation**, possibly combining two (e.g. the Quartiler's 75th percentile can use **two heaps** — a max-heap of the bottom 75% and a min-heap of the top 25%, with the boundary kept in size ratio 3:1; the top quartile is the min-heap's root → Θ(1)).
3. **Draw** the representation with 5–10 sample elements.
4. **Explain each operation** and *why* it meets the complexity (cite the underlying structure's op cost).
5. **Write the requested operation** in pseudocode, implementing any helper you call.

**Two-heap trick** is the standard tool for median/percentile problems — remember it.

---

## 11. Last-48-hours checklist

- [ ] Recite the complexity hierarchy and classify a given polynomial (O/Ω/Θ).
- [ ] Explain amortized analysis using dynamic-array resize.
- [ ] Reverse an SLL in pseudocode from memory (Θ(n)/Θ(1)).
- [ ] Evaluate a postfix expression with a stack.
- [ ] Add/remove on a binary heap and **draw** the tree at each step.
- [ ] Build a hash table with separate chaining **and** open addressing; compute load factor.
- [ ] State why open addressing needs n ≤ m and why search can probe > n slots.
- [ ] Do all four traversals of a given binary tree.
- [ ] Insert into an AVL tree, identifying LL/RR/LR/RL and rotating.
- [ ] Delete from a BST (all three cases).
- [ ] Design an ADT from complexity requirements (two-heap trick).

You learn fast — get the procedures in §5–8 to the point where you can execute them without thinking, and Parts A & B are locked. Part C rewards the §10 method plus the two memorized algorithms (reverse SLL, tree max).
