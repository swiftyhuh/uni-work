<!-- page 1 -->
# LECTURE 7 — FUNCTIONAL PROGRAMMING

From mathematical foundations to Lisp

From symbolic AI to modern functional programming

<!-- page 2 -->
# Why functional programming?

Problem: sum the squares of all even numbers in a list. Imperative view: initialize a sum, iterate through the list, test and update. Functional view: filter even numbers → square them → add the results. Both compute the same value; the difference is how the solution is expressed. Central question: what does each intermediate transformation mean?

<!-- page 3 -->
# Two ways of describing computation

Imperative programming emphasizes sequences of operations and changes of state.

Functional programming emphasizes values, expressions and composition. A function can be understood as a transformation from input values to output values.

This is a programming discipline—not merely a new syntax or language. The same perspective can be adopted in C++ or Python.

<!-- page 4 -->
# What makes the functional style useful?

Pure functions have explicit inputs and predictable results.

Immutable values can be reused without fear of unexpected modification. Higher-order functions combine operations into larger abstractions. Independent computations are easier to test and can be parallelized with less coordination.

The goal is to manage complexity by limiting hidden dependencies.

<!-- page 5 -->
# Before electronic computers

The starting question was mathematical: what does ‘effectively computable’ mean? Cantor studied infinite sets; Kronecker emphasized finite constructions. Peano and Skolem helped develop recursive descriptions of arithmetic. In the 1930s, mathematicians formalized mechanical computation.

These theories came before modern electronic computers.

<!-- page 6 -->
# Five approaches to computation

Recursive functions: construct calculations from simple functions and formal rules. Lambda calculus: compute by applying functions and reducing expressions. Turing machines: read, write and move on an abstract tape. Post systems: manipulate symbols by production rules. Markov algorithms: apply ordered string-rewriting rules.

<!-- page 7 -->
# Recursive functions: build from simple rules

Start with zero, successor S(n) = n + 1 and projection functions. Composition and recursion generate more complicated functions. Example: add(x, 0) = x; add(x, y + 1) = S(add(x, y)). Multiplication can then be defined through repeated addition. Minimization extends the framework to general partial computable functions.

<!-- page 8 -->
# Lambda calculus: computation by substitution

Define a function and apply it to an argument.

Illustration: (λx. x + 1) 3 → 4; the argument replaces x. In pure lambda calculus, even numbers and conditionals can be encoded as functions.

No mutable memory or physical machine is required in the mathematical model. This is a central intellectual ancestor of functional programming.

<!-- page 9 -->
# Turing, Post and Markov: mechanical rules

Turing: a finite set of instructions controls a read/write head on an unbounded tape. Unary illustration: 111 → 1111 increments 3 to 4.

Post: symbolic expressions can be generated or transformed by formal productions. Markov: repeatedly apply the first applicable rule in an ordered rule list. Very different mechanics can express the same computable functions.

<!-- page 10 -->
# The Church–Turing thesis

Lambda-definable, general recursive and Turing-computable functions coincide. That equivalence is a mathematical result about formal systems. The Church–Turing thesis identifies effective algorithms with Turing computability.

It is a thesis, not a theorem: ‘effective algorithm’ is an informal notion. Computable does not mean that every question is decidable.

<!-- page 11 -->
# Two pioneering languages

FORTRAN: numerical computation and efficient manipulation of numerical data. Lisp (1958): symbolic expressions, recursive structures and list processing. Both emerged during the early era of high-level programming languages. Lisp grew alongside the first research programs in artificial intelligence. The central contrast is symbolic structure versus numerical calculation.

<!-- page 12 -->
# McCarthy and the birth of Lisp

1956: Dartmouth summer research project helped establish AI as a field. 1958: John McCarthy began developing Lisp at MIT.

Symbolic differentiation encouraged recursive processing of expression trees. 1960: ‘Recursive Functions of Symbolic Expressions and Their Computation by Machine’.

1962: Lisp 1.5; later dialects developed in several directions.

<!-- page 13 -->
# Why symbolic computation?

Given the expression x² + 3x, produce the expression 2x + 3. This is not simply evaluating the function at a particular number x. A symbolic program recognizes operators, operands and nesting. It applies algebraic rules and constructs a new expression tree. Lists and recursion fit this kind of processing naturally.

<!-- page 14 -->
# Lisp: programs can be data

Lisp expressions are represented using lists and symbols.

The same structures can hold ordinary data or program expressions. A program may construct or inspect representations of another program. This makes interpreters, symbolic transformations and macros natural. The idea is often called homoiconicity: code and data share a structure.

<!-- page 15 -->
# The EVAL idea

Lisp's evaluator interprets an expression according to the language rules. McCarthy described evaluation mathematically using Lisp-like functions. An implemented evaluator helped turn this description into an interpreter. The surprising point: a language can express important parts of its own interpreter. Interactive evaluation became a defining feature of Lisp systems.

<!-- page 16 -->
# Pure functions

Same arguments → same result, with no observable side effects. Pure example: elapsed_seconds(start, end), given two fixed time values. Impure example: a function that reads the current clock each time. Reading a changing file or modifying global state also introduces effects. Purity makes behavior easier to reproduce, test and reason about.

<!-- page 17 -->
# Immutability: transformations preserve old values Start with the immutable list [1, 2, 3].

Adding an element produces a new list [1, 2, 3, 4]. The original list remains [1, 2, 3] and can still be used safely. Existing values are predictable; functions can share them without coordination. Persistent structures may reuse unchanged parts instead of copying everything.

<!-- page 18 -->
# Referential transparency

An expression may be replaced by its value without changing the result of a program.

Example: square(2) can be replaced by 4 when square is pure. This supports local reasoning: understand one expression at a time. It also makes tests and certain compiler optimizations easier. Pure functions operating on immutable inputs help preserve this property.

<!-- page 19 -->
# Functions are first-class values

A function may be assigned to a variable or included in a data structure. A function may be passed as an argument to another function. A function may be returned as the result of another function. These operations let us abstract over behavior, not only over data. A higher-order function takes a function or returns one.

<!-- page 20 -->
# Filter → map → reduce

Start: [1, 2, 3, 4, 5, 6]. FILTER even values → [2, 4, 6]. MAP square → [4, 16, 36]. REDUCE by addition → 56. Each stage has one clear responsibility; stages can be composed.

<!-- page 21 -->
# Lists, sequences and abstraction

A sequence is an abstraction; an implementation may use a linked list or another structure.

Lisp lists are built from CONS cells and can be processed recursively. CONS attaches an element to the front of a list.

Abstract types separate operations from particular representations. Constructors create values; selectors retrieve parts; discriminators test applicability.

<!-- page 22 -->
# FP versus OOP — I

Primary abstraction

FP: Functions and function composition. OOP: Objects, classes and interactions. Data and behavior FP: Operations are separate from data. OOP: Objects encapsulate state and behavior. State and mutability FP: Prefers immutable values. OOP: Commonly modifies state through methods.

<!-- page 23 -->
# FP versus OOP — II

Programming model

FP: Describes computations using expressions. OOP: Models entities and their responsibilities. Side effects

FP: Pure functions have no side effects.

OOP: Methods may change state or the environment. Composition and reuse

FP: Combines functions and higher-order functions. OOP: Uses delegation, interfaces and polymorphism.

<!-- page 24 -->
# FP versus OOP — III

Iteration

FP: Recursion, map, filter and fold. OOP: Loops, iterators and method calls. Evaluation order

FP: Flexible for independent pure calls. OOP: State changes often impose an order. Parallel programming

FP: Immutable data limits interference. OOP: Shared mutable state needs synchronization.

<!-- page 25 -->
# FP versus OOP — IV

Main focus

FP: Abstraction over behavior.

OOP: Abstraction over data and state.

Note:

Characteristic differences, not restrictions imposed on every language. The same language can support both paradigms.

<!-- page 26 -->
# Functional languages in practice

Haskell organizes ordinary computation around pure functions and explicit effects.

Common Lisp supports functional and imperative techniques, including mutable objects.

Scheme emphasizes procedures and a comparatively small language design. Clojure emphasizes persistent immutable data structures on the Java platform. Lazy evaluation is a separate language-design choice, not a requirement of FP.

<!-- page 27 -->
# Lisp's evolution: important branches

1960s–1970s: MacLisp, Interlisp and Franz Lisp; MACSYMA used Lisp for algebra. 1970s: Scheme, with a compact design and lexical scope.

1980s: Lisp machines offered highly integrated interactive environments. 1994: Common Lisp became an ANSI-standardized language.

Lisp is a family of related languages rather than one frozen 1958 design.

<!-- page 28 -->
# Backus challenges the von Neumann style

John Backus, the principal designer of FORTRAN, criticized assignment-heavy programs.

His 1977 Turing Award lecture was published in 1978.

Question: ‘Can Programming Be Liberated from the von Neumann Style?’ He proposed a functional style organized around operations on whole structures. The critique came from one of the architects of conventional high-level programming.

<!-- page 29 -->
# From Lisp machines to Clojure

Specialized Lisp workstations flourished during the symbolic-AI era. Their commercial market declined, but interactive development ideas endured. In 2007 Rich Hickey introduced Clojure, a modern Lisp on the Java platform. Clojure emphasizes immutable persistent structures and concurrency. Common Lisp, Scheme, Racket and Clojure remain distinct design traditions.

<!-- page 30 -->
# Lisp, symbolic AI and contemporary AI

Classical symbolic AI emphasizes rules, logical relations and explicit knowledge. Lisp suited theorem proving, expert systems and symbolic transformations. Modern AI also relies on large-scale statistical learning and numerical optimization.

Symbolic techniques remain useful in theorem proving and program analysis. Both symbolic and statistical approaches can contribute to modern systems.

<!-- page 31 -->
# Why study Lisp now?

Lisp connects mathematical computability with practical symbolic programming. Its legacy includes functions as values, interactive evaluation and garbage collection.

Code-as-data supports powerful metaprogramming techniques. Functional programming offers another way to decompose and reason about programs.

Next: Lisp expressions, lists, evaluation and recursive functions.
