<!-- page 1 -->
# Lecture 1 - Introduction in declarative programming. Recursion

# Official web site: https://hfpop.ro/teaching/pfl

# Contents

References

Programming and programming languages Recursion

Examples of recursion

# References

Czibula, G., Pop, H.F., Elemente avansate de programare în Lisp şi Prolog. Aplicaţii în Inteligenţa Artificială., Ed. Albastră, ClujNapoca, 2012

# Programming and programming languages

# Algorithms, programs and data structures:

- Algorithm . An algorithm is the outline, the essence of a computational procedure, a sequence of instructions, given as a text.

- Program . A program is an implementation of an algorithm in some programming language.

- Data structure . Many data structures are needed to write a program that solves a problem. They are used to separate various structures and operations on these structures. A correct use of data structures leads to increased clarity and reduced complexity.

1

<!-- page 2 -->
# Algorithm - American Heritage Dictionary of the English Language, 5th Edition:

- A finite set of unambiguous instructions that, given some set of initial conditions, can be performed in a prescribed sequence to achieve a certain goal and that has a recognizable set of end conditions.

- A precise rule (or set of rules) specifying how to solve some problem; a set of procedures guaranteed to find the solution to a problem.

Concerning the meaning of an algorithm, the effect of its execution:

- each algorithm defines a mathematical function

- an algorithm is written to solve a specific problem

- more algorithms are available for solving a certain problem.

The main characteristics of an algorithm are:

- generality : the algorithm solves a problem for all possible values of the input data, not only in particular cases;

- uniqueness : the repeated execution of an algorithm for the same input data provides the same results;

- finitude : the algorithm is a finite text in a description language;

- correctness .

We would also like to note the following:

- An algorithm describes actions on the input instance.

- There are usually more than one correct algorithms for the same algorithmic problem.

2

<!-- page 3 -->
# The declarative view

Declarative programming means writing code in such a way that it describes what you want to do, and not how you want to do it.

# Programming rules

- R1 Know and follow the meaning of each variable.

- R2 Use different names for variables with different meaning.

- R2’ Do not use the same name for variables of different meaning.

- R3 Do not use global / invisible variables.

- R4 Completely know the problem to be solved.

- R5 Do not use uninitialized variables.

- R6  Do not reevaluate the limits and do not modify the loop variable  inside a FOR repetitive structure.

- R7 Choose suggestive names for variables.

- R8 Postpone for later the insignificant details; concentrate your attention to the important decisions of the moment.

- R9  Avoid reading and printing in a subalgorithm.

- R10 Create a subalgorithm independent of the context where it will be used.

3

<!-- page 4 -->
# LANGUAGES

# Procedural (imperative) - high level languages

- Fortran, Cobol, Algol, Pascal, C, ...

- program - sequence of instructions

- <u>the assignment statement, control structures - for the control</u> of sequential execution, branching and cycling

- the role of the programmer - “what” and “how”

   1. (“what”) to describe what is to be calculated

   2. (“how”) to organize the calculation

   3. (“how”) to organize memory management

- !!! it is argued that assignment is dangerous in high-level languages, just as GO TO was considered dangerous for structured programming in the '68s.

# Declarative (descriptive, applied) - very high level languages

- based on expressions

- expressive, easy to understand (have a simple basis), extensible

- programs can be seen as descriptions that state information about values, rather than instructions to determine values or effects.

- they give up instructions

   - thus they protect users from making too many mistakes

   - they are generated from mathematical principles - analysis, design, specification, implementation, abstraction and reasoning (deductions of consequences and properties) become more and more formal activities.

- the role of the programmer - “what” (not “how”)

4

<!-- page 5 -->
# Two classes of declarative languages

Functional languages (e.g. Lisp, ML, Scheme, Haskell, Erlang)

focus on values of data described by expressions (built through applications of functions and definitions of functions), with automatic evaluation of expressions

Logical languages (e.g. Prolog, Datalog, Parlog)

focus on logical assertions that describe the relationships between data values and automatic derivations of answers to questions, starting from these assertions.

# Applications in Artificial Intelligence

automated proofs, natural language processing and speech understanding, expert systems, machine learning, intelligent agents, etc.

- Multiparadigm languages: F#, Python, Scala (imperative, functional, object oriented)

- Interactions between declarative and imperative languages - declarative languages that provide interfaces with imperative languages (eg C, Java): SWI Prolog, GNU Prolog, etc.

- Logtalk – integrates logic and object-oriented programming

- Logic programming in Python :

   - Karen

   - SymPy – library for simbolic computations

5

<!-- page 6 -->
# Recursion

- general mechanism to elaborate programs

- recursion arose from practical necessities (direct transcription of recursive mathematical formulas; see Ackermann's function)

- recursion is the mechanism by which a subprogram (function, procedure) calls itself

   - two types of recursion: direct or indirect

- !!! Result

   - any calculable function can therefore be expressed and programmed) in terms of recursive functions

- two things to consider in describing a recursive algorithm: `o` the recursive rule

      - the termination condition

- advantage of recursion: source text that is extremely short and very clear.

- disadvantage of recursion: filling the stack segment if the number of recursive calls, respectively of the formal and local parameters of the recursive subprograms is high enough.

      - declarative languages have specific mechanisms to optimize the recursion (see the mechanism of tail recursion in Prolog).

6

<!-- page 7 -->
# Why recursion?

- Some data structures are recursive by nature: lists, trees and expressions.

- The structure of the program can closely follow the recursive definition of the problem.

- In functional and logic programming, recursion often replaces explicit loops and mutable state.

# General recursive pattern

f(x) = base(x), if the termination condition holds f(x) = combine(x, f(smaller(x))), otherwise

Three questions:

- What is the base case?

- What is the smaller problem?

- How are the results combined?

# Recursion versus iteration

Iteration : loop; explicit state; loop termination condition; usually constant stack.

Recursion : self-call; state carried by parameters/call stack; base case; potentially growing stack.

7

<!-- page 8 -->
# Important results

# Function

f : X → Y associates to each element of X exactly one element of Y E.g. f : N → N, f(n) = n+1

# Partial function

f : X → Y is a function defined on a subset S of X to Y

E.g. f : R → R, f(n) = 1/n, is not defined for n=0

# Total function

A partial function where S = X (It is defined for every input) E.g. f : N → N, f(n) = n2 is total, it’s defined for every n in N

# Computable function

If there exists an algorithm that can to its job E.g. f : N → N, f(n) = n2 is computable, we have an algorithm

For partial functions, the algorithm may not terminate for certain inputs. If the algorithm terminates, it produces the correct result.

# General recursive function (or) Partial recursive function

A partial function N → N that is computable

It is, essentially, a function defined by a mathematical formalism, and may be undefined for certain entries. These functions may enter an infinite loop for certain values.

8

<!-- page 9 -->
# Total recursive function (or) Recursive function (*) A general recursive function that is total

It is a recursive function defined on any input, and the algorithm that computes the result always terminates.

E.g. f : N → N, f(n) = n! is total recursive.

Primitive recursive function (*)

A function that can be computed by a computer program whose loops are all “for” loops, i.e. an upper bound of all iterations of every loop can be determined before entering the loop.

E.g. f(0) = 0 and f(n+1) = f(n) + 1. These compute f(n) = n.

Other examples: sum, multiplication, power, factorial, comparison, polynomials.

Difference:

Primitive recursive ⊂ Total recursive ⊂ Partial recursive

Partial : may not have a result for some inputs Total : has a result for any input Computable : there is an algorithm to compute the result Recursive : may be defined in formalism of recursive functions Primitive recursive : uses recursion and upper bounds loops

9

<!-- page 10 -->
# Importance:

# 1. Distinguishes between the terminating computation and the endless computation (i.e. infinite recursion)

The distinction between total and partial functions allow us to state whether and algorithm ends for all the entries.

# 2. Connects mathematical definitions to algorithms

A recursive function is a mathematical description, and a computable function is a function with a known algorithm.

# 3. Helps in problens classification

Not all problems are “equally” calculable. We may have:

- functions that compute and always terminate;

- functions that compute for some entries only;

- problems with no known general algorithm.

There is no universal algorithm to decide that, for any program and any input whether the program terminates or not.

# 4. Shows the difference between recursion types

The primitive recursive functions use a simple and controlled recursion type. Since the number of steps is limited , they always terminate.

The general recursive functions are stronger, they may express more complex algorithms, but sometimes the termination is not obvious.

# 5. Allows proving termination

For more recursive functions, we prove termination using a positive value that strictly decreases at each call.

10

<!-- page 11 -->
# 6. Clarifies the relationship between mathematics and programming

These answer three fundamental questions:

- Is there an algorithm for this function?

- Does the algorithm produce a result for any input?

- Can we prove that the algorithm terminates?

Example: The Ackermann function

One of the simplest and earliest-discovered functions:

- total computable function

- not primitive recursive (no upper bound for loops)

# Version 1

F(m,n,0) = m+n F(m,0,1) = 0 F(m,0,2) = 1 F(m,0,p) = m p>2 F(m,n,p) = F(m, F(m,n-1,p),p-1) n,p>0

# Version 2

A(0,n) = n+1 A(m+1,0) = A(m,1) A(m+1, n+1) = A(m, A(m+1,n))

# Version 3

A0(n) = n+1 Am+1(n) = Amn+1 (1) where fn+1 (x) = f(fn (x))

11

<!-- page 12 -->
# What happens when a recursive function is evaluated? Example: sum(3)

sum(3) → 3 + sum(2) → 3 + 2 + sum(1) → 3 + 2 + 1 + sum(0) → 3 + 2 + 1 + 0 → 6

The pending calls are kept on the call stack until the base case is reached; then the results are returned in reverse order.

Tail recursion

Non-tail recursive: sum(n) = n + sum(n − 1)

Tail recursive: sum(n, acc) = sum(n − 1, acc + n)

In a tail-recursive call, no operation remains to be performed after the recursive call returns.

12

<!-- page 13 -->
# Examples of recursion

# <u>Remarks and notation</u>

   - a list is a sequence of items ( 𝑙1𝑙2 … 𝑙𝑛 )

   - the empty list (with 0 elements) is denoted by ⊘

   - adding an item to a list is denoted by ⊕

1. Create list (1,2,3, ... n)

# a) directly recursive

𝑐𝑟𝑒𝑎𝑟𝑒𝐿𝑖𝑠𝑡𝑎(𝑛) = { 𝑐𝑟𝑒𝑎𝑟𝑒𝐿𝑖𝑠𝑡𝑎(𝑛−1)⨁ 𝑛        𝑎𝑙𝑡𝑓𝑒𝑙⊘                                     𝑑𝑎𝑐𝑎 𝑛= 0

b) using a recursive auxiliary function to create the sublist (i, i + 1, ..., n)

// create the list consisting of the elements i, i + 1,…, n Recursive mathematical model

𝑐𝑟𝑒𝑎𝑟𝑒(𝑖, 𝑛) = {𝑖⊕𝑐𝑟𝑒𝑎𝑟𝑒(𝑖+ 1, 𝑛)      𝑎𝑙𝑡𝑓𝑒𝑙  𝑑𝑎𝑐𝑎  𝑖> 𝑛

- // create the list consisting of elements 1, 2,…, n 𝑐𝑟𝑒𝑎𝑟𝑒𝐿𝑖𝑠𝑡𝑎(𝑛) = 𝑐𝑟𝑒𝑎𝑟𝑒(1, 𝑛)

13

<!-- page 14 -->
# Pseudocode

Data representation: singly linked list with dynamic allocation of nodes.

# NodeLSI

e: TElement // useful information of node urm: ^NodeLSI // address the following node is stored

# LSI

prim: ^NodeLSI // address of the first node in the list

# Function createNodeLSI(e)

{pre: e: TElement} {post: return a ^NodeLSI having e as useful information } {allocates a storing space for a NodeLSI } {p: ^NodLSI} allocate (p) [p].e  e [p].urm  NIL {result returned by the function } createNodeLSI  p

EndFunction

# Function create(i, n)

{post: return a ^NodLSI, pointer towards the head of the linked list formed by }

{ elements i, i+1,…, n }

If i > n then

create  NIL

14

<!-- page 15 -->
else

{ allocate a storage space for a NodeLSI with usefun information e }

q  createNodeLSI (i) { create the link between node q and the head of } { the linked list formed by elements i+1,…, n } [q].urm  create (i+1, n) create  q

EndIf

# EndFunction

# Function createList(n)

{post: return a ^NodeLSI, pointer towards the head of the linked list formed by }

{ elements 1, 2,…, n }

createList  create (1, n)

EndFunction

2. Given a natural number n, calculate the sum 1 + 2 + 3 +… + n. a) directly recursive

b) using a recursive auxiliary function for calculating the sum i + (i + 1) +… + n

𝑠𝑢𝑚𝑎_𝑎𝑢𝑥(𝑛, 𝑖) = { 𝑖+ 𝑠𝑢𝑚𝑎(𝑛, 𝑖+ 1)          𝑎𝑙𝑡𝑓𝑒𝑙0                                𝑑𝑎𝑐𝑎 𝑖> 𝑛 𝑠𝑢𝑚𝑎(𝑛) = 𝑠𝑢𝑚𝑎_𝑎𝑢𝑥(𝑛, 0)

15

<!-- page 16 -->
# 3. Add an item at the end of a list.

// build the list (l1, l2,…, ln, e) 𝑎𝑑𝑎𝑢𝑔(𝑒, 𝑙1𝑙2 … 𝑙𝑛) = {𝑙(𝑒)     𝑑𝑎𝑐𝑎 𝑙 𝑒 𝑣𝑖𝑑𝑎 1 ⊕𝑎𝑑𝑎𝑢𝑔(𝑒, 𝑙2 … 𝑙𝑛) 𝑎𝑙𝑡𝑓𝑒𝑙

# 4. Search for an element in a list .

# 5. Count the number of occurrences of an item in the list.

# 6. Check if a numeric list is set.

# 7. Transform a numeric list into a set.

16

<!-- page 17 -->
# 8. Return the inverse of a list.

# 9. Remove all occurrences of an item from a list.

# 10. Return the k-th element of a list (k> = 1).

11. Return the difference between two sets represented as lists.

17

<!-- page 18 -->
Patterns seen in recursive list processing

- Stop when the list is empty.

- Process the first element.

- Recurse on the rest of the list.

- Keep, discard or transform the current element.

- Combine the current result with the result of the recursive call.

Most of the previous examples are variations of this same structural pattern.

# <u>Homework</u>

1. Verify whether a natural number is prime.

2. Calculate the sum of the first k elements in a numeric list ( 𝑙1𝑙2 … 𝑙𝑛 )

3. Remove the first k even numbers from a numeric list.

18
