# Part C Mastery Sheet — algorithms, ADTs & how to pick a structure

Everything you need to write Part C confidently: how to choose a structure, the reusable templates, the must-know algorithms (full pseudocode), and a bank of ADT-design problems with the structure + approach for each.

Pseudocode style: `subalgorithm name(params) is: … end-subalgorithm`, `function name(params) is: … return via name ← value`, `[p].field`, `NIL`, `allocate(p)`.

---

## 1. Choose the structure from the requirement

When a Part C problem lists operations + required complexities, **read the complexities — they name the structure.**

| Requirement | Use | Why |
|---|---|---|
| Access by **index** in Θ(1); append Θ(1) amortized | **Dynamic array** | direct addressing |
| Θ(1) insert/remove at the **front**, no random access | **Singly linked list** | relink head |
| Θ(1) at **both ends** | **Doubly linked list** / circular array (deque) | prev pointer |
| **LIFO** | **Stack** | push/pop one end |
| **FIFO** | **Queue** (circular array, or SLL head+tail) | enqueue rear, dequeue front |
| Lookup **by key** Θ(1) average | **Hash table / map** | computed position |
| **count per key** (multiset, frequency) | **Hash map: key → count** | one lookup |
| Always get **min OR max** fast; Θ(log n) updates | **Binary heap** (min or max) | root = extreme |
| **median / percentile / k-th boundary** | **Two heaps** (max-heap low + min-heap high) | boundary = a root |
| `getMin`/`getMax` **alongside a stack**, all Θ(1) | **Stack + auxiliary stack** of running min/max | precomputed at top |
| **ordered** iteration + Θ(log n) search/insert/delete | **balanced BST (AVL)** | sorted structure, height log n |
| "**add a search**" to an existing ADT X | **X + a hash map** (mirror) | search becomes a lookup |
| **most recently used / order + lookup** | **hash map + doubly linked list** | O(1) move + find |

**The golden Part-C move:** if a needed op must be **Θ(1) average** → think *hash map*. If it must be **Θ(1) worst with log updates** → think *heap*. If both *ordered* and *log* → *AVL*. Then bolt the FIFO/LIFO/index structure on alongside.

---

## 2. The five reusable templates

**(T1) List traversal** — walk with `curr`, do work, advance. Θ(n).
```
curr ← [list].head
while curr ≠ NIL execute
    ▷ work with [curr].info
    curr ← [curr].next
end-while
```

**(T2) Tree recursion** — base case + combine(left, right, node). Θ(n).
```
function f(node) is:
    if node = NIL then f ← <base>; return end-if
    L ← f([node].left);  R ← f([node].right)
    f ← <combine L, R, [node].info>
end-function
```
Swap the combine: count nodes `1+L+R`; leaves `(leaf?1:L+R)`; height `1+max(L,R)`; sum `info+L+R`; max `max(info,L,R)`.

**(T3) Two heaps** — max-heap `low` + min-heap `high`, split at a boundary; the wanted element is a **root** (Θ(1)); on add/remove **rebalance** by moving one element across (O(log n)). Median = 1:1 sizes; 75th percentile = 3:1.

**(T4) Auxiliary stack** — mirror the main stack with a second stack holding the running min/max so `getMin`/`getMax` is the top of the aux stack (Θ(1)).

**(T5) Hash-map mirror** — to add `search`/`count`/`contains` to any ADT in Θ(1) average, keep a `key → count` map in sync with every add/remove.

---

## 3. Must-know algorithms (full pseudocode)

### 3A. Singly linked list  (`SLLNode {info, next}`, list keeps `head`, often `tail`)

**length** · Θ(n)
```
function length(list) is:
    c ← 0;  curr ← [list].head
    while curr ≠ NIL execute  c ← c+1;  curr ← [curr].next  end-while
    length ← c
end-function
```

**search** · Θ(n) worst
```
function search(list, e) is:
    curr ← [list].head
    while curr ≠ NIL execute
        if [curr].info = e then search ← true; return end-if
        curr ← [curr].next
    end-while
    search ← false
end-function
```

**findMax** · Θ(n)  (assume non-empty; init from head)
```
function findMax(list) is:
    best ← [[list].head].info;  curr ← [[list].head].next
    while curr ≠ NIL execute
        if [curr].info > best then best ← [curr].info end-if
        curr ← [curr].next
    end-while
    findMax ← best
end-function
```

**insertFront** · Θ(1)
```
subalgorithm insertFront(list, e) is:
    allocate(p); [p].info ← e; [p].next ← [list].head; [list].head ← p
end-subalgorithm
```

**insertEnd** (head-only) · Θ(n)  — with a tail pointer it's Θ(1)
```
subalgorithm insertEnd(list, e) is:
    allocate(p); [p].info ← e; [p].next ← NIL
    if [list].head = NIL then [list].head ← p; return end-if
    curr ← [list].head
    while [curr].next ≠ NIL execute curr ← [curr].next end-while
    [curr].next ← p
end-subalgorithm
```

**deleteFirstOccurrence(v)** · Θ(n)
```
subalgorithm delete(list, v) is:
    if [list].head = NIL then return end-if
    if [[list].head].info = v then [list].head ← [[list].head].next; return end-if
    prev ← [list].head;  curr ← [[list].head].next
    while curr ≠ NIL AND [curr].info ≠ v execute prev ← curr; curr ← [curr].next end-while
    if curr ≠ NIL then [prev].next ← [curr].next end-if
end-subalgorithm
```

**reverse (in place)** · Θ(n) time, Θ(1) space   ⭐ memorize
```
subalgorithm reverse(list) is:
    prev ← NIL;  curr ← [list].head
    while curr ≠ NIL execute
        nxt ← [curr].next        ▷ save before overwriting
        [curr].next ← prev
        prev ← curr;  curr ← nxt
    end-while
    [list].head ← prev
end-subalgorithm
```

**findMiddle (slow/fast)** · Θ(n)
```
function middle(list) is:
    slow ← [list].head;  fast ← [list].head
    while fast ≠ NIL AND [fast].next ≠ NIL execute
        slow ← [slow].next;  fast ← [[fast].next].next
    end-while
    middle ← slow          ▷ slow is at the middle node
end-function
```

**detect cycle (Floyd)** · Θ(n)
```
function hasCycle(list) is:
    slow ← [list].head;  fast ← [list].head
    while fast ≠ NIL AND [fast].next ≠ NIL execute
        slow ← [slow].next;  fast ← [[fast].next].next
        if slow = fast then hasCycle ← true; return end-if
    end-while
    hasCycle ← false
end-function
```

### 3B. Binary tree  (`BTNode {info, left, right}`, keeps `root`)

**traversals (recursive)** · Θ(n)
```
preorder(n):  if n≠NIL: visit n; preorder(n.left); preorder(n.right)
inorder(n):   if n≠NIL: inorder(n.left); visit n; inorder(n.right)
postorder(n): if n≠NIL: postorder(n.left); postorder(n.right); visit n
```

**level-order (BFS)** · Θ(n) — uses a **queue**
```
subalgorithm levelOrder(root) is:
    if root = NIL then return end-if
    q ← empty queue;  enqueue(q, root)
    while not isEmpty(q) execute
        n ← dequeue(q);  visit n
        if [n].left ≠ NIL then enqueue(q, [n].left) end-if
        if [n].right ≠ NIL then enqueue(q, [n].right) end-if
    end-while
end-subalgorithm
```

**height** (single node 0, empty −1) · Θ(n)
```
function height(n) is:
    if n = NIL then height ← −1; return end-if
    height ← 1 + max(height([n].left), height([n].right))
end-function
```

**countNodes / countLeaves / sum / maxValue** — template T2:
```
countNodes(n):  NIL→0;  else 1 + countNodes(left) + countNodes(right)
countLeaves(n): NIL→0;  leaf→1;  else countLeaves(left)+countLeaves(right)
sum(n):         NIL→0;  else info + sum(left) + sum(right)
maxValue(n):    NIL→−∞; else max(info, maxValue(left), maxValue(right))
```

### 3C. Binary Search Tree

**search** · O(h)
```
function search(n, k) is:
    while n ≠ NIL AND [n].info ≠ k execute
        if k < [n].info then n ← [n].left else n ← [n].right end-if
    end-while
    search ← (n ≠ NIL)
end-function
```

**insert** · O(h)
```
subalgorithm insert(tree, k) is:
    allocate(p); [p].info ← k; [p].left ← NIL; [p].right ← NIL
    if [tree].root = NIL then [tree].root ← p; return end-if
    n ← [tree].root
    while true execute
        if k < [n].info then
            if [n].left = NIL then [n].left ← p; return else n ← [n].left end-if
        else
            if [n].right = NIL then [n].right ← p; return else n ← [n].right end-if
        end-if
    end-while
end-subalgorithm
```

**delete** · O(h) — 3 cases: leaf → remove; one child → replace with child; two children → replace value with **inorder successor** (min of right subtree), then delete that successor.

### 3D. Heap (1-based array; children 2i,2i+1; parent ⌊i/2⌋). Max-heap shown; **min-heap flips every comparison**.

**siftUp / add** · O(log n)
```
subalgorithm add(h, e) is:
    h.size ← h.size+1;  h.elems[h.size] ← e;  siftUp(h, h.size)
end-subalgorithm
subalgorithm siftUp(h, i) is:
    while i > 1 AND h.elems[i] > h.elems[⌊i/2⌋] execute
        swap(h.elems[i], h.elems[⌊i/2⌋]);  i ← ⌊i/2⌋
    end-while
end-subalgorithm
```

**removeRoot / siftDown** · O(log n)
```
function removeRoot(h) is:
    top ← h.elems[1]
    h.elems[1] ← h.elems[h.size];  h.size ← h.size−1
    siftDown(h, 1);  removeRoot ← top
end-function
subalgorithm siftDown(h, i) is:
    while true execute
        big ← i;  l ← 2*i;  r ← 2*i+1
        if l ≤ h.size AND h.elems[l] > h.elems[big] then big ← l end-if
        if r ≤ h.size AND h.elems[r] > h.elems[big] then big ← r end-if
        if big = i then return end-if
        swap(h.elems[i], h.elems[big]);  i ← big
    end-while
end-subalgorithm
```
`buildHeap`: siftDown from ⌊size/2⌋ downto 1 → Θ(n). `peek` = elems[1] → Θ(1).

### 3E. Hashing (`h(k)=k mod m`)
- **Separate chaining:** array of linked lists; insert = prepend Θ(1); search/remove = scan that chain (Θ(1) avg).
- **Open addressing:** one element per slot; on collision probe `h(k)+i` (linear) / `+i²` (quadratic) / `+i·h₂(k)` (double); delete with **tombstones**.
- **Count-map** (multiset/frequency): `map[k] ← map[k]+1` to add; `map[k]` to query; both Θ(1) average.

---

## 4. ADT-design problems to practice  (structure + how it works)

For each: the *deliverable* is (1) representation, (2) a small drawing, (3) each op + complexity, (4) one op in pseudocode. Try them on paper; the structure + approach is given so you can self-check.

1. **MinStack / MaxStack** — push/pop/top/getMin all Θ(1). → **Stack + aux stack** of running min/max. (T4)
2. **Queue from two stacks** — enqueue Θ(1); dequeue amortized Θ(1). → push to `inS`; on dequeue, if `outS` empty pour `inS`→`outS`, then pop `outS`.
3. **Stack from two queues** — push Θ(1) *or* pop Θ(1) (one is Θ(n)). → rotate the new element to the front on push (push-costly version).
4. **SearchableQueue** — Queue + `search(e)` Θ(1) avg. → **Queue (SLL head+tail) + count-map**; search = `count[e] > 0`. (T5)
5. **SearchableStack** — Stack + `search(e)` Θ(1) avg. → Stack + count-map.
6. **MultiSet / Bag** — add, remove-one, nrOccurrences, all Θ(1) avg. → **hash map key→count**.
7. **MedianBag** — add O(log n), getMedian Θ(1). → **two heaps**, 1:1 sizes; median = low's root. (T3)
8. **Quartiler (75th percentile)** — add O(log n) amortized, getTop/deleteTop. → **two heaps**, 3:1 sizes; the percentile = low's root.
9. **Min-Priority-Queue** — insert/extractMin O(log n), peekMin Θ(1). → **binary min-heap**.
10. **Double-ended priority queue** — getMin & getMax both fast. → a min-heap + a max-heap (or min-max heap); know the two-heap idea.
11. **LRU-cache-like (order + lookup)** — get/put Θ(1) avg. → **hash map + doubly linked list** (map to nodes; move to front on use).
12. **FrequencyCounter / mode** — add, getCount Θ(1). → hash map key→count (+ optionally a max-heap of counts for "most frequent").
13. **Set with random element** — add/remove/contains Θ(1) avg, getRandom Θ(1). → **dynamic array + hash map (value→index)**; remove by swapping with last.
14. **Sparse vector / matrix** — store only nonzeros. → **map position→value** (hash) or a **sorted list / BST keyed by position**; `modify` to zero = delete, zero→nonzero = insert (your A1!).
15. **Browser history (back/forward)** — Θ(1) each. → **doubly linked list** with a current pointer (or two stacks: back-stack + forward-stack).
16. **Undo/redo** — → two stacks (undo + redo).
17. **Round-robin scheduler** — cycle forever. → **circular linked list**.
18. **First-non-repeating element (stream)** — → queue (order) + count-map; pop from front while front's count > 1.

---

## 5. Part C exam tactics (don't lose easy points)

- **Always state the representation first** (`Node {…}`, what the container holds), then draw a small example.
- **Write the return**: `functionName ← value`. (You dropped this once — make it a reflex.)
- **Handle the named edge cases**: empty, single element, head, not-found, already-last. The prompt usually names them.
- **State complexity with one reason** for every operation; "Θ(1) average" for hash, "O(log n)" for heap, "Θ(n)" for list scan.
- **Implement helpers you call** (e.g., your own `siftUp`/`siftDown`, `enqueue`) — the rules say you can't assume they exist.
- **Save before overwrite** in any pointer reshuffle (reverse, insertAfter, heap swaps).
- **Two heaps** = your go-to for median/percentile/"middle" questions; **count-map** = your go-to for search/frequency/multiset; **aux stack** = min/max with a stack.
