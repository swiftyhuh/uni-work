# Algorithms Reference — Thursday + Friday

Every algorithm you've covered so far, with pseudocode, a plain explanation, and complexity. These are the ones you should be able to write or trace from memory. Pseudocode uses the course style: `[p].field` to access a field through a pointer, `NIL` for null, `allocate(p)` to create a node.

---

## A. Dynamic array

### A1. getElement(i) — Θ(1)
```
function getElement(da, i) is:
    getElement ← da.elems[i]
end-function
```
**Why:** the element's memory address is computed directly (`base + i·size`), so it's one step regardless of how big the array is. This O(1) random access is the dynamic array's whole advantage over linked lists.

### A2. append(e) — Θ(1) amortized
```
subalgorithm append(da, e) is:
    if da.size = da.capacity then
        resize(da)                ▷ allocate 2× array, copy all, free old — Θ(n)
    end-if
    da.elems[da.size + 1] ← e
    da.size ← da.size + 1
end-subalgorithm
```
**Why amortized Θ(1):** most appends are one write (Θ(1)). Occasionally the array is full and you must double the capacity and copy everything (Θ(n)). But because the capacity *doubles*, those copies are rare — over n appends the total copy work is n + n/2 + n/4 + … < 2n. Averaged across n appends that's Θ(1) each. (If you grew by a fixed +1 instead, every append would copy → Θ(n) amortized — that's why doubling matters.)

---

## B. Singly linked list

Representation: `SLLNode {info, next}`, list keeps `head`.

### B1. reverse — Θ(n) time, Θ(1) space  ⭐ (the C1 classic)
```
subalgorithm reverse(list) is:
    prev ← NIL
    curr ← [list].head
    while curr ≠ NIL execute
        nxt ← [curr].next      ▷ SAVE the rest before overwriting
        [curr].next ← prev     ▷ flip this node's link backward
        prev ← curr            ▷ advance prev
        curr ← nxt             ▷ advance curr
    end-while
    [list].head ← prev         ▷ old last node becomes the new head
end-subalgorithm
```
**Why:** three pointers walk the list once, flipping each `next` to point at the previous node. The crucial line is saving `nxt = curr.next` *before* you overwrite `curr.next` — otherwise you'd lose the rest of the list. One pass ⇒ Θ(n); only three pointers no matter the size ⇒ Θ(1) extra space.

### B2. length — Θ(n)
```
function length(list) is:
    cnt ← 0
    curr ← [list].head
    while curr ≠ NIL execute
        cnt ← cnt + 1
        curr ← [curr].next
    end-while
    length ← cnt
end-function
```
**Why:** you must walk every node to count them ⇒ Θ(n). (Only Θ(1) if the list keeps a `size` field updated on every add/remove.)

### B3. search — Θ(n) worst, Θ(1) best
```
function search(list, e) is:
    curr ← [list].head
    while curr ≠ NIL execute
        if [curr].info = e then
            search ← true
            return
        end-if
        curr ← [curr].next
    end-while
    search ← false
end-function
```
**Why:** walk until you find `e` or hit the end. Best case it's the first node (Θ(1)); worst case it's absent or last (Θ(n)). No random access, so even a *sorted* linked list can't binary-search.

### B4. insertAfter(p, e) — Θ(1)
```
subalgorithm insertAfter(p, e) is:
    allocate(newNode)
    [newNode].info ← e
    [newNode].next ← [p].next     ▷ point new node at p's old successor
    [p].next ← newNode            ▷ point p at the new node
end-subalgorithm
```
**Why Θ(1):** you were *given* the node `p`, so no traversal — just a fixed number of pointer updates. Order matters: set `newNode.next` *before* overwriting `p.next` (same save-before-overwrite rule as reverse).

### B5. insertAfterValue(v, e) — Θ(n)
```
subalgorithm insertAfterValue(list, v, e) is:
    curr ← [list].head
    while curr ≠ NIL AND [curr].info ≠ v execute
        curr ← [curr].next
    end-while
    if curr ≠ NIL then            ▷ found the first node with info = v
        allocate(newNode)
        [newNode].info ← e
        [newNode].next ← [curr].next
        [curr].next ← newNode
    end-if
end-subalgorithm
```
**Why Θ(n):** finding `v` is a search (Θ(n)); the insert itself is Θ(1), so the search dominates. Putting the `≠ v` test in the while condition makes the loop stop *at* the first match (insert once, not after every match).

---

## C. Stack (LIFO) — all Θ(1)

On a dynamic array, operate at the **end**:
```
subalgorithm push(s, e) is:        function pop(s) is:              function top(s) is:
    append(s.da, e)                    e ← s.da.elems[s.da.size]       top ← s.da.elems[s.da.size]
end-subalgorithm                       s.da.size ← s.da.size − 1       end-function
                                       pop ← e
                                   end-function
```
**Why:** "last in, first out." Pushing/popping at the array's end touches only one slot ⇒ Θ(1). (On an SLL you'd push/pop at the *front* instead — also Θ(1).)

---

## D. Queue (FIFO) — all Θ(1) on a circular array

Keep `front`, `rear` indices and wrap with modulo:
```
subalgorithm push(q, e) is:             function pop(q) is:
    q.elems[q.rear] ← e                     e ← q.elems[q.front]
    q.rear ← (q.rear mod capacity) + 1      q.front ← (q.front mod capacity) + 1
    q.size ← q.size + 1                     q.size ← q.size − 1
end-subalgorithm                            pop ← e
                                        end-function
```
**Why circular:** "first in, first out" needs add at the rear and remove at the front. If you used a plain array and popped from index 0, every pop would shift all elements (Θ(n)). Wrapping the front/rear indices around with `mod` avoids shifting ⇒ both ops Θ(1).

---

## E. Postfix (RPN) evaluation — Θ(n), uses a stack
```
function evalPostfix(expr) is:
    s ← empty stack
    for each token in expr (left to right) execute
        if token is a number then
            push(s, token)
        else                              ▷ token is an operator
            right ← pop(s)                ▷ FIRST popped = right operand
            left  ← pop(s)                ▷ SECOND popped = left operand
            push(s, apply(left, token, right))
        end-if
    end-for
    evalPostfix ← pop(s)                  ▷ the one value left is the answer
end-function
```
**Why:** numbers wait on the stack; each operator consumes the two most-recent values (which are exactly its operands) and pushes the result. Order matters for `−` and `÷`: it's `left OP right` = second-popped OP first-popped (e.g. `9 6 −` → 9 − 6 = 3). One scan ⇒ Θ(n).

---

## F. Binary heap (priority queue)

Stored in a 1-based array: children of `i` at `2i`, `2i+1`; parent at `⌊i/2⌋`. Below is the **max-heap** version (root = max). For a **min-heap**, flip every comparison (`>` becomes `<`, "larger child" becomes "smaller child").

### F1. add — Θ(log n)  (insert then sift up)
```
subalgorithm add(h, e) is:
    h.size ← h.size + 1
    h.elems[h.size] ← e          ▷ place at the next free leaf (end of array)
    siftUp(h, h.size)
end-subalgorithm

subalgorithm siftUp(h, i) is:
    while i > 1 AND h.elems[i] > h.elems[⌊i/2⌋] execute   ▷ bigger than parent?
        swap(h.elems[i], h.elems[⌊i/2⌋])
        i ← ⌊i/2⌋                ▷ move up to the parent's slot
    end-while
end-subalgorithm
```
**Why:** the new value starts at the bottom and "bubbles up," swapping with its parent while it's bigger, until it's in a valid spot (or becomes the root). It travels at most the tree height ≈ log₂n ⇒ Θ(log n).

### F2. removeRoot — Θ(log n)  (replace root, sift down)
```
function removeRoot(h) is:
    maxVal ← h.elems[1]
    h.elems[1] ← h.elems[h.size]   ▷ move the LAST element to the root
    h.size ← h.size − 1
    siftDown(h, 1)
    removeRoot ← maxVal
end-function

subalgorithm siftDown(h, i) is:
    while true execute
        largest ← i
        left ← 2*i ;  right ← 2*i + 1
        if left ≤ h.size AND h.elems[left] > h.elems[largest] then largest ← left
        if right ≤ h.size AND h.elems[right] > h.elems[largest] then largest ← right
        if largest = i then return        ▷ both children smaller → done
        swap(h.elems[i], h.elems[largest])
        i ← largest                        ▷ follow the element down
    end-while
end-subalgorithm
```
**Why:** the root is the answer (the max). To keep the tree *complete*, you fill the hole with the last element, then let it "sink" — repeatedly swapping with its **larger** child (swapping with the smaller one would break the property) until both children are smaller. At most one root-to-leaf path ⇒ Θ(log n).

### F3. buildHeap — Θ(n)
```
subalgorithm buildHeap(h) is:
    for i ← ⌊h.size / 2⌋ downto 1 execute   ▷ from the last internal node up
        siftDown(h, i)
    end-for
end-subalgorithm
```
**Why:** sift-down each internal node, starting from the bottom. It looks like n·log n, but most nodes are near the leaves and sink only a little; the sum works out to Θ(n) — cheaper than n separate adds (which would be Θ(n log n)).

### Heapsort — Θ(n log n)
Build a max-heap (Θ(n)), then repeatedly swap the root to the end of the array and `siftDown` the new root over the shrinking heap. n removals × Θ(log n) ⇒ Θ(n log n), in place.

---

## G. Priority Queue (ADT)

A container where every element has a **priority**; removal always returns the **highest-priority** element (regardless of insertion order). Operations: `push(e, p)`, `pop()` (remove highest priority), `top()`/`peek()`, `isEmpty()`.

Same ADT, very different costs by representation:

| Representation | push | pop / top |
|---|---|---|
| Unsorted array/list | Θ(1) (append) | Θ(n) (scan for max) |
| Sorted array/list | Θ(n) (insert in order) | Θ(1) (it's at the end) |
| **Binary heap** | **Θ(log n)** | **Θ(log n)** (top Θ(1)) |

**Why the heap wins:** unsorted/sorted each make one operation cheap and the other Θ(n); the binary heap balances both at Θ(log n) — so it's the standard implementation. Used in Dijkstra, schedulers, Huffman coding, heapsort.

---

## H. Binomial Heap

**Why it exists:** a binary heap cannot **merge** two heaps faster than Θ(n). A binomial heap supports **union in O(log n)** — a *mergeable* priority queue.

**Binomial tree `B_k`** (recursive): `B₀` = one node; `B_k` = two `B_{k-1}` trees linked (root of one becomes the leftmost child of the other's root).
- `B_k` has exactly **2^k nodes**, its **root has k children** (roots of `B₀…B_{k-1}`), and height k. (Nodes at depth d = "k choose d" — the binomial coefficients.)

**Binomial heap** = a **forest** of binomial trees with: **at most one tree of each order**, each obeying the heap property. The orders present = the **binary representation of n** (e.g. n=13=1101₂ → trees B₃, B₂, B₀). So there are at most **⌊log₂n⌋ + 1 trees**.

**Operations** (all built on `union`):
- `union(h1, h2)` — merge like **binary addition**: scan trees by increasing order; when two `B_k` collide, **link** them into a `B_{k+1}` (the "carry"). **O(log n)**.
- `insert(e)` — make a one-node heap (`B₀`), union it in. O(log n) worst, **O(1) amortized**.
- `findMin` — scan the roots (≤ log n of them). O(log n), or O(1) with a min-pointer.
- `extractMin` — remove the min root; its k children form a new binomial heap; union it back. O(log n).

**One-line summary:** a forest of power-of-2 binomial trees (one per set bit of n) giving **mergeable** priority-queue ops in O(log n); merge = binary addition with carries. Know the structure and *why* (mergeability) — you won't be asked to draw a complex union.

---

## Quick recall table

| Algorithm | Complexity | One-line idea |
|-----------|-----------|---------------|
| DA getElement | Θ(1) | direct address |
| DA append | Θ(1) amortized | double + copy, rarely |
| SLL reverse | Θ(n) / Θ(1) space | 3 pointers, flip each link |
| SLL length / search | Θ(n) | walk the nodes |
| SLL insertAfter(p) | Θ(1) | relink, no traversal |
| SLL insertAfterValue | Θ(n) | search dominates |
| Stack push/pop/top | Θ(1) | operate at one end |
| Queue push/pop | Θ(1) | circular array, mod indices |
| Postfix eval | Θ(n) | push nums, fold operators |
| Heap add (siftUp) | Θ(log n) | bubble up vs parent |
| Heap removeRoot (siftDown) | Θ(log n) | sink vs larger/smaller child |
| buildHeap | Θ(n) | siftDown bottom-up |
| Heapsort | Θ(n log n) | build heap, pop n times |
| PriorityQueue on binary heap | Θ(log n) push/pop | top Θ(1); standard impl |
| Binomial heap union | Θ(log n) | mergeable; binary-addition merge |

**The recurring theme:** in every pointer/array reshuffle (reverse, insertAfter, heap swaps), never overwrite a link before you've saved what it pointed to.
