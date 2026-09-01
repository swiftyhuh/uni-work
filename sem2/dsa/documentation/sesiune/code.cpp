// SLLA deleteElement pseudocode

subalgorithm deleteElement(slla, elem):
    // Step 1 search for the element
    currentNode <- slla.head
    prevNode <- -1

    while currentNode != -1 and slla.elems[currentNode] != elem execute
        prevNode <- currentNode
        currentNode <- slla.next[currentNode]
    end-while

    // step 2 if we found the element, -1 means NIL/ end of the array
    if currentNode != -1 then
        // if we find it at the head, we are changing the head to the next one
        if currentNode = slla.head then
            slla.head <- slla.next[slla.head]
        else
            // if its not in the first place, we link the next of the previous one to the next of the current that we are deleting
            slla.next[prevNode] <- slla.next[currentNode]
        end if

        // Step 2b: the recycling trick !!!!!!!!!
        // ADd the deleted position currentNode to the list of empty spaces
        slla.next[currentNode] <- slla.firstEmpty
        slla.firstEmpty <- currentNode

    else
        @the element doesn't exist

    end-if

end-subalgorithm



// FOR DLLA EVERY "SWAP" MUST BE BOTHWAYS!!!!
// Allocate helper for DLLA (double linked list on array)


function allocate(dlla):
    newElem <- dlla.firstEmpty
    if newElem != -1 then
        // 1. Move firstEmpty to the next available slot
        dlla.firstEmpty <- dlla.nodes[dlla.firstEmpty].next
        if dlla.firstEmpty != -1 then
            dlla.nodes[dlla.firstEmpty].prev <- -1
        end if
        
        // 2. Clear the links for the brand new node
        dlla.nodes[newElem].next <- -1
        dlla.nodes[newElem].prev <- -1

    end if

    allocate <- newElem

end-function

// Free helper for DLLA (double linked list on array)

subalgorithm free(dlla, pos):
    // 1. Point the freed node to the current firstEmpty
    dlla.nodes[pos].next <- dlla.firstEmpty
    dlla.nodes[pos].prev <- -1

    // 2. Point the current fistEmpty back to the freed node

    if dlla.fistEmpty != -1 then
        dlla.nodes[dlla.firstEmpty].prev <- pos
    end if

    // 3. Offically update firstEmpty to the freed node
    dlla.firstEmpty <- pos
end-subalgorithm

//  How they both look in an Exam Algorithm (insertPosition)


subalgorithm insertPosition(dlla, elem, pos):
    // check if pos is valid .....

    newElem <- allocate(dlla)

    if newElem = -1 then
        @resize // the array its full
        newElem <-allocate(dlla)
    end if

    dlla.nodes[newElem].info <- elem

    // ... the rest is standar dll pointer swapping, using newElem as your index

end-subalgorithm


// insertFirst for CSLL

subalgorithm insertFirst(csll, elem)
    newNode <- allocate()
    [newNode].info <- elem
    [newNode].next <- newNode // temporarily

    if csll.head = NIL then
        clss.head <- newNode
    else
        // 1. walk the list to find the very last node
        lastNode <- csll.head
        while [lastNode].next != csll.head execute
            lastNoode <- [lastNode].next
        end-while

        // 2. Attach the new node and update the last node's link

        [newNode].next <- csll.head
        [lastNode].next <- newNode
        clss.head - newNode

   end-if

end-subalgorithm
      

// printListForward for XOR List
    
subalgorithm printListForward(xorl):
    prevNode <- NIL
    currentNode <- xorl.head

    while currentNode != NILL execute
        write [currentNode].info

        nextNode <- prevNode XOR [currentNode].link

        prevNode <- CurrentNode
        currentNode <- nextNode

    end-while

end-subalgorithm

// search operation for Skip List

function search(sl, elem):
    current <- sl.head

    // step 1: start at the highest lane and drop down
    for i <- sl.maxlevel down to 0 execute
        
        // step 2, keep driving riht on this lane as long as the next value is st
        while [current].next[i] != NIL and [[current].next[i]].info < elem execute
            current <- [current].next[i] // move right
        end while

        // step 3, we are now at lvl 0
        // current is sitting on the largest number strictyl smaller than elem
        current <- [current].next

        if current != NIL and [current].info = elem then
            search <- True
        else
            search <- False

        end if
  
end function


//  STACK on dynamic array

subalgorithm push(s, elem):
    // if the array is full we must resize firstly
    if s.nrElem = s.cap then
        @resize(s)
    end if

    s.elemns[s.nrElem] <- elem
    s.nrElem++
end-subalgorithm

subalgorithm pop(s):
    if s.nrElem = 0 then
        @throw exception
    end if

    // grab the last element
    removedElem <- s.elems[s.nrElem -1]

    // delete it by symply shirking the size boundary
    s.nrElem--
    pop <- removedElem

end-subalgorithm


// Resize for circular array queue

subalgorithm resize(q):
    newCap <- q.cap * 2
    newElems <- allocate array of size newCamp

    // the "unroll" loop
    for i <- 0 to q.size - 1 execute
    // we use mod to safely wrap arod the old array if needed!
        oldPos <- (q.front + i) mod q.cap
        newElems[i] <- q.elems[oldPos]
    end-for

    q.elems <- newElems
    q.cap <- newCap
    q.front <- 0
    q.rear <- q.size

end sub-algo


// Add and bubble-up for binary heap

subalgorithm add(heap, e):
    is heap.len = heap.cap then
        @resize
    end-if

    heap.elems[heap.len + 1] <- e
    heap.len++

    bubble-up(heap, heap.len)

end-subalgorithm

subalgorithm bubble-up(heap, p):
    pos <- p
    elem <- heap.elems[p]
    parent <- p/2

    // while we aren t at the root, and the element its bigger than its parent
    while pos > 1 and elem > heap.elems[parent] execute
        heap.elems[pos] <- heap.elems[parent]

        pos <- parent
        parent <- pos/2
    end-while

    heap.elems[pos] <- elem

end-subalgorithm

subalgorithm bubble-down(heap, p) is: 
    // p is the position from which we move down the element
    poz <- p 
    elem <- heap.elems[p] 
    
    while poz < heap.len execute
        maxChild <- -1 
        
        // Check if it has a left child, assume it is the maximum initially
        if poz * 2 <= heap.len then 
            maxChild <- poz * 2 
        end-if 
        
        // Check if it has a right child AND if the right child is strictly greater than the left child
        if poz * 2 + 1 <= heap.len and heap.elems[2 * poz + 1] > heap.elems[2 * poz] then
            maxChild <- poz * 2 + 1 
        end-if
        
        // If a valid larger child exists, swap it with the current position
        if maxChild != -1 and heap.elems[maxChild] > elem then 
            tmp <- heap.elems[poz] 
            heap.elems[poz] <- heap.elems[maxChild] 
            heap.elems[maxChild] <- tmp 
            poz <- maxChild
        else 
            poz <- heap.len + 1 // Forces the while loop to stop (the tree is fixed!)
        end-if 
    end-while
end-subalgorithm


subalgorithm buildHeap(heap)
    // Start from the last parent node and work backwards to the root
    for i <- heap.len / 2 down to 1 execute
        bubble-down(heap, i)
    end-for

end-subalgorithm

// RECAP DAY 2
//
// ADT STACK: uniq - strict last in first out
//            extra - to achive theta(1) on a dynamic arrya, we must place the top at the end (size -1)so we never have toshift elements left or right
//
// ADT QUEUE: uniq - strict first in first out
//            extra - must use a circular array to avoid O(n) shifts, if it fill up the resize requir manually unroll the circle usign a loop so the sequence is pefectly straight again in the new array
//
// ADT DEQUE: uniq - double ended acces (insert/remove at both front and rear)
//            extra - for strictly Theta(1) operations without amortized resizes, we must use a DLL. if using the C++ STL Array of blocks, remmeber the trap: the firrst block fillsbackwards, right to left
//
// ADT Priority Queue & binary heap
// Uniq - strict Highest priority first, it bypasses O(n) bottleneckby faking a binary tree inside a flat dynamic array
// Extra - you must leave index 0 empty, the magic index math makes left child = 2*i, right child 2*i+1, the parrent i /2. we must bubble-up for insertions and bubble-down for removals to mantain the O(log2n) time
//


// insert separated chaining

subalgorithm insert(ht,k):
    pos <- ht.h(k)
    allocate(newNode)
    [newNode].key <- k
    [newNode].next <-ht.T[pos]
    ht.T[po] <- newNode
end-subalgorithm

// coalesced chaining code

subalgorithm insert(ht, k):
    if ht.firstEmpty = cap then 
        @resize
    end-if

    pos <- ht.h(k) // k % capacity
    
    if ht.T[pos] = -1
    // empty slot
        ht.T[pos] <- k
        ht.next[pos] <- -1

        if pos == ht.firstEmpty
            changeFE(ht)
        end if
    else
        // collision
        current <- pos

        // walk to the end of the chain
        while ht.next[current] != -1 execute
            current <- ht.next[current]
        end-while

        // drop element in the first empty slot
        ht.T[ht.firstEmpty] <- k
        ht.next[ht.firstEmpty] <- -1

        ht.next[current] <- ht.firstEmpty

        changeFE(ht)
    end if
end subalgorithm

subalgorithm changeFE(ht):
    ht.firstEmpty++

    //kepp walking right until we hit an empty slot
    while ht.firstEmpty < ht.c and ht.T[ht.firstEmpty] != -1 execute
        ht.firstEmpty++
    end-while
end-subalgorithm

subalgorithm delete(ht, k):
    pos <- ht.h(k)
    current <- pos
    previous <- -1

    // search inside collision chain for exact k
    while current != -1 and ht.T[current] != k execute
        previous <- current
        current <- ht.next[current]
    end-while

    // if we don t find it
    if current = -1 then
        return false
    end-if

    // case 1: deleting head of chain
    if current = pos then
        if ht.next[current] = -1
            // only one element in the chain
            ht.T[current] <- -1
            ht.next[current] <- -1

            // lets say our current its 0, and the first empty was 3, now we set
            // first empty to 0
            if current < ht.firstEmpty then
                ht.firstEmpty <- current
            end-if

        else
            // move next node into the head
            nextPos <- ht.next[current]

            ht.T[current] <- ht.T[nextPos] // second from the chain now its the head
            ht.next[current] <- ht.next[nextPos] // change the next too

            ht.T[nextpos] <- -1
            ht.next[nextPos] <- -1

            if nextPos < ht.firstEmpty then
                ht.firstEmpty -< nextPos
            end-if
        end-if
    else
        // case 2: deleting middle/end of the chain
        ht.next[previous] <- ht.next[current]

        ht.T[current] <- -1
        ht.next[current] <- -1

        if current < ht.firstEmpty then
            ht.firstEmpty <- current
        end-if
    end-if
end-subalgorithm


// code for open addressing with deleted -2

// 1) search oepration, -1 empty, -2 deleted (jumps over them)

function serach(ht, k)
    i<-0
    pos<-ht.h(k,i)

    // keep probing untill we hit a empty slot (not deleted)
    while i < ht.cap and ht.T[pos] != -1 execute
        if ht.T[pos] = k then
            search <- True
            return
        end-if
        i++
        pos <- ht.h(k,i)
    end-while
    search <- false
end-function

// 2) Insert, we stop probing if we find -1 or -2

subalgorithm insert(ht, k)
    i <- 0
    pos <- ht.h(k, i)

    // stop probing if slot is empty or deleted
    while i < ht.cap and ht.T[pos] != -1 and ht.T[pos] != -2 execute
        i++
        pos <- ht.h(k, i)
    end-whle

    if i = ht.cap then
        @resize
        @rehash
    else
        ht.T[pos] <- k
    end-if
end-subalgorithm




// Cuckoo hashing insert

subalgorithm insert(k) is:
  currentKey <- k
  tableID <- 1
  
  // Loop until we find a free spot or hit a cycle limit
  while loopCount < MAX_LIMIT execute:
    
    if tableID = 1 then
      pos <- h1(currentKey)
      if T1[pos] is EMPTY then
        T1[pos] <- currentKey
        return // Successfully inserted!
      else
        // KICK OUT! Swap the new key with the old key
        swap(currentKey, T1[pos])
        tableID <- 2 // The kicked-out key flies to Table 2
      end-if
      
    else // tableID = 2
      pos <- h2(currentKey)
      if T2[pos] is EMPTY then
        T2[pos] <- currentKey
        return // Successfully inserted!
      else
        // KICK OUT! Swap and fly back to Table 1
        swap(currentKey, T2[pos])
        tableID <- 1
      end-if
    end-if
    
    loopCount <- loopCount + 1
  end-while
  
  // If we reach here, we are stuck in an infinite cycle
  @resize and rehash everything!
end-subalgorithm


// Perfect Hashing (aici ii greu tata)

subalgorithm buildSecondaryTable(slot_j, collidedKeys):
    nj <- size(collidedKeys)

    // the magic size to guarantee high succes rate
    m <- nj * nj
    allocate(secondaryTable of size m)
    
    collisionFound <- True
    //keep roling the dice until we get 0 collisions!
    while collisionFound = true execute:
        a <- random(1, p-1)
        b <- random(0, p-1)
        
        collisionFound <- False
        @clear secondaryTable

        // try to place all keys with these specific a and b
        for each key in collidedKeys execute:
            pos <- ((a*key+b)%p)%m

            if secondaryTable[pos] = EMPTY then
                secondaryTable[pos] = key
            else
                //the magic math faile!
                // break the loop and try a new random a and b
                collisionFound <- True
                break
            end if
        end for
    end while

    // we surive the loop, we found theperfect formula
    // save a and b so the search funcion can use them later
    slot_j.a <- a
    slot_j.b <- b
    slot_j.table <- secondaryTable
end-subalgorithm

// Linked hash table insert

subalgorithm insert(lht, k)
    allocate(newNode)
    newNode.info <- k
    // init all thre pointer to nil
    newNode.prevL <- nil, newNode.nextL <- nil, newNode.nextH <- Nil

    // phase 1: hash table insertion
    pos <- lth.h(k)
    if lht.T[pos] = NIL then
        lht.T[pos] <- newNode
    else
        // drop it at the fron of the collision list
        newNode.nextH <- lht.T[pos]
        lht.T[pos] <- newNode
    end-if

    //plase 2 timeline insertion
    if lth.head = NIL then
    // its the first element ever
        lht.head <- newNode
        lht.tail <- newNode
    else
        //link it to the end of the timeline
        newnode.prevL <- lth.tail
        lth.tail.nextL<-newNode
        lth.tail <-newNode
    end-if
end-subalgorithm


// Insert subalgorithm for AVL tree

function insertRec(node, elem) is
    // 1. standart bst inseraton
    if node = NIL then
        insertRec <- createNode(elem)
    else if elem <= [node].info then
        [node].left <- insertRec([node].left, elem)
    else
        [node].right <- insertRec([node].right, elem)
    end-if

    // 2. the rebalance phase
    recomputeHeight(node)
    balance <- getBalanceFactor(node) // HeightLeft - HeightRight
    
    if balance = -2 then
        rightBalance <- getBalanceFactor([node].right)
        if rightBalance < 0 then
            // right child its heavy right, right right case
            node <- SLR(node) // singly left rot
        else
            node <- DLR(node) // double left rot

    else if balance = 2 then
        leftBalance <- getBalanceFactor([node].right)
        if leftBalance > 0 then
            node <- SRR(node) //single right rotation
        else
            node <- DRR(node) // double right rot

    end-if

    insertREc <- node
end-function

function height(node) is
    if node = NIL then
        height <- -1
    else
        height <- [node].h
    end-if
end-function

function recomputeHeight(node) is
    if node != NIL then
        leftH <- height([node].left)
        rightH <- height([node].right)
        [node].h <- 1+ max(leftH, rightH)
    end-if
end-function

function getBalanceFactor(node) is
    if node = NIL then
        getBalanceFactor <- 0
    else
        getBalanceFactor <- height([node].left) - height([node].right)
    end-if
end-function


// rotating sll

if not( sll.head == nil or [sll.head].next == nil) then
    first <- sll.head
    sll.head <- [sll.head].next
    
    current <- sll.head

    while [current].next != NIL execute
        current <- [current].next
    end-while

    [current].next <- first
    [first].next <- NIL
end if


// find max in a binary tree (not sorted)

subalgorithm findMax(node) is
    if node = NIL then
        findmax = -infinity
    else
        maxLeft <- findMax([node].left)
        maxRight <- findMax([node].right)

        currentMax <- [node].info

        if maxLeft > currentMax then currentMax <- maxLeft
        if maxRight > currentMax then currentMax <- maxRight

        findmax <- currentMax
    end-if
end-subalgorithm

// reverse sll

subalgorithm salut(sll)
    prev <- nil
    current <-sll.head
    while current != nill execute
        next <- [current].next
        current.next <- prev
        prev <- current
        current <- next
    end-while

    sll.head <- prev
end-subalgorithm


// move-to-back singly linked list

subalgorithm salut(sll,e)
    prev <- nil
    current <- sll.head
    while current != nil and [current].info != e execute
        prev <- current
        current <- [current].next
    end-while

    if current = NIL or [current].next = NIL then
        return
    end-if

    if prev = NIL then
        sll.head <- [current].next
    else
        [prev].next <- [current].next
    end-if

    walk <- sll.head
    while [walk].next != nil execute
        walk <- [walk].next
    end-while

    [walk].next <- current
    [current].next <- nil

end-subalgorithm // O(n)


// stack1 starts from the index 1 and ++
// stack2 start from the cap, and --
// top1 top of the stack 1, top2 top of the stack 2, elems array of elems
// cap the max of the array, resize when the both stacks found eachothers
//

subalgorithm push(ts, elem, stackNR):
    if ts.top1 + 1 = ts.top2 then
        resize(ts)
    end-if

    if StackNR = 1 then
        ts.top1 <- ts.top1 + 1
        ts.elems[ts.top1] <- elem
    else
        ts.top2 <- ts.top-1
        ts.elems[ts.top2] <-elem
    end-if
end-subalgorithm


// c2
subalgorithm findmax(nodes)
    if node = NIL then
        findmax = -infinity
    else
        maxleft <- findmax([node].left)
        maxright <- findmax([node].right)
        currentmax <- [node].info

        if maxLeft > currentMax then currentmax <- maxleft
        if maxright > currentMax then currentMax <- right

        findmax <- currentMax
    end-if
    end-sublagorithm
    

// Rearragen an SLL s.t all even number are in gront of all odd numbers

subalgorithm evensBeforeOdds(sll):
    headEven <- NIL
    headOdd <- NIL
    tailEven <- NIL
    tailOdd <- NIL

    current < sll.head

    while current != NIL
        nextNode <- [current].next
        [current].next <- NIL

        if [current].info %2 == 0
            if headEven = NIL then
                headEven <- current
                tailEven <- current
            else
                [tailEven].next <- current
                tailEven <- current
            end-if
        else
            if headOdd = NIL then
                headOdd <- current
                tailOdd <- current
            else
                [tailOdd].next <- current
                taildOdd <- current
            end-if
        end-if
    end-while

    if headEven = nil then
        sll.head <- headOdd
    else
        [tailEven].next <- headOdd
        sll.head <- headEven
    end-if
end-subalgorithm

// Determine the sum of the largest k elements from an array containing n distinct numbers. The Trick: If they ask you to do something with the "K largest" or "K smallest" elements, the answer is always a Binary Heap

subalgorithm sumLargestK(array, n, k)
    init(minHeap, "<=") // create an empty min heap

    for i <- 0, k - 1, execute
        push(minHeap, a[i])
    end-for

    for i <- k, n-1 execute
        if a[i] > top(minHeap) then
            pop(minHeap)
            push(minHeap, a[i])
        end-if
    end-for

    sum <- 0
    while not isEmpty(minHeap) execute
        sum <- sum + pop(minHeap)
    end-while

    return sum
    end-function

