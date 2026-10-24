<!-- page 1 -->
60

10 APPLICATIONS OF UNIFICATION

Skolemization yields

The clauses are

Note that ¬ _P(a, a)_ is an instance of the first clause and that _P(a, a)_ is an instance of the second, contradiction. This is a one-step proof! But it involves both resolution and factoring, since the 2-literal clauses must collapse to singleton clauses.

Example 37 Let us prove ∃ _x_ [ _P_ → _Q(x)_ ] ∧∃ _x_ [ _Q(x)_ → _P_ ] →∃ _x_ [ _P_ ↔ _Q(x)_ ]. The clauses are

A short resolution proof follows. The complementary literals are underlined:

_Exercise 32_ Show the steps of converting ∃ _x_ [ _P_ → _Q(x)_ ]∧∃ _x_ [ _Q(x)_ → _P_ ] → ∃ _x_ [ _P_ ↔ _Q(x)_ ] into clauses. Then show two resolution proofs different from the one shown above.

_Exercise 33_ Is the clause { _P(x, b), P(a, y)_ } logically equivalent to the unit clause { _P(a, b)_ }? Is the clause { _P(y, y), P(y, a)_ } logically equivalent to { _P(y, a)_ }? Explain both answers.

## 10.3 Prolog clauses

Prolog clauses, also called Horn clauses, have at most one positive literal. A _definite_ clause is one of the form

It is logically equivalent to _(A_ 1 ∧· · · ∧ _Am)_ → _B_ . Prolog’s notation is

<!-- page 2 -->
61

10.4 Prolog computations

If _m_ = 0 then the clause is simply written as _B_ and is sometimes called a _fact_ . A _negative_ or _goal_ clause is one of the form

Prolog permits just one of these; it represents the list of unsolved goals. Prolog’s notation is

A Prolog database consists of definite clauses. Observe that definite clauses cannot express negative assertions, since they must contain a positive literal. From a mathematical point of view, they have little expressive power; every set of definite clauses is consistent! Even so, definite clauses are a natural notation for many problems.

_Exercise 34_ Show that every set of definite clauses is consistent. (Hint: first consider propositional logic, then extend your argument to first order logic.)

## 10.4 Prolog computations

A Prolog computation takes a database of definite clauses together with one goal clause. It repeatedly resolves the goal clause with some definite clause to produce a new goal clause. If resolution produces the empty goal clause, then execution succeeds.

Here is a diagram of a Prolog computation step:

This is a _linear_ resolution (§7). Two program clauses are never resolved with each other. The result of each resolution step becomes the next goal clause; the previous goal clause is discarded after use.

Prolog resolution is efficient, compared with general resolution, because it involves less search and storage. General resolution must consider all possible pairs of clauses; it adds their resolvents to the existing set of clauses; it spends

<!-- page 3 -->
62

10 APPLICATIONS OF UNIFICATION

a great deal of effort getting rid of subsumed (redundant) clauses and probably useless clauses. Prolog always resolves some program clause with the goal clause. Because goal clauses do not accumulate, Prolog requires little storage. Prolog never uses factoring and does not even remove repeated literals from a clause.

Prolog has a fixed, deterministic execution strategy. The program is is regarded as a list of clauses, not a set; the clauses are tried strictly in order. With a clause, the literals are also regarded as a list. The literals in the goal clause are proved strictly from left to right. The goal clause’s first literal is replaced by the literals from the unifying program clause, preserving their order.

Prolog’s search strategy is depth-first. To illustrate what this means, suppose that the goal clause is simply ← _P_ and that the program clauses are _P_ ← _P_ and _P_ ← . Prolog will resolve _P_ ← _P_ with ← _P_ to obtain a new goal clause, which happens to be identical to the original one. Prolog never notices the repeated goal clause, so it repeats the same useless resolution over and over again. Depthfirst search means that at every ‘choice point,’ such as between using _P_ ← _P_ and _P_ ← , Prolog will explore every avenue arising from its first choice before considering the second choice. Obviously, the second choice would prove the goal trivially, but Prolog never notices this.

## 10.5 Example of Prolog execution

Here are axioms about the English succession: how _y_ can become King after _x_ .

king _(_ richardIII _)_

### defeat _(_ henryVII _,_ richardIII _)_

### oldestson _(_ henryVIII _,_ henryVII _)_

The goal is to prove king _(_ henryVIII _)_ .

These axioms correspond to the following definite clauses:

<!-- page 4 -->
10.5 Example of Prolog execution

63

The goal clause is

Figure 2 shows the execution. The subscripts in the clauses are to rename the variables.

Note how crude this formalization is. It says nothing about the passage of time, about births and deaths, about not having two kings at once. Henry VIII was the second son of Henry VII; the first son, Arthur, died before his father. Logic is clumsy for talking about situations in the real world.

The Frame Problem in Artificial Intelligence reveals another limitation of logic. Consider writing an axiom system to describe a robot’s possible actions. We might include an axiom to state that if the robot lifts an object at time _t_ , then it will be holding the object at time _t_ + 1. But we also need to assert that the positions of everything else remain the same as before. Then we must consider the possibility that the object is a table and has other things on top of it _. . ._

Prolog is a powerful and useful language, but it is not necessarily logic. Most Prolog programs rely on special predicates that affect execution but have no logical meaning. There is a huge gap between the theory and practice of logic programming.

_Exercise 35_ Convert these formulæ into clauses, showing each step: negating the formula, eliminating → and ↔, pushing in negations, moving the quantifiers, Skolemizing, dropping the universal quantifiers, and converting the matrix into CNF.

- ¬∃ _y_ ∀ _x (R(x, y)_ ↔¬∃ _z (R(x, z)_ ∧ _R(z, x)))_

<!-- page 5 -->
64

10 APPLICATIONS OF UNIFICATION

<!-- Start of picture text -->
definite clause goal clause ⌢⋐⊣⌋ � {¬os (y 1 , x 1 ),  ¬k (x 1 ),  k (y 1 ) } {¬k ( henryVIII ) } {os ( henryVIII ,  henryVII ) } {¬os ( henryVIII , x 1 ),  ¬k (x 1 ) } {¬defeat (y 2 , x 2 ),  ¬k (x 2 ),  k (y 2 ) } {¬k ( henryVII ) } {defeat ( henryVII ,  richardIII ) } {¬defeat ( henryVII , x 2 ),  ¬k (x 2 ) } {k ( richardIII ) } {¬k ( richardIII ) } □ <!-- End of picture text -->

Figure 2: Execution of a Prolog program (os = oldestson, k = king)

<!-- page 6 -->
65

_Exercise 36_ Consider the Prolog program consisting of the definite clauses

Describe the Prolog computation starting from the goal clause ← _P(v)_ . Keep track of the substitutions affecting _v_ to determine what answer the Prolog system would return.

_Exercise 37_ Find a refutation from the following set of clauses using resolution with factoring.

_Exercise 38_ Prove the following formulæ by resolution, showing all steps of the conversion into clauses. Remember to negate first!

# 11 Modal Logics

There are many forms of modal logic. Each one is based upon two parameters:

- _W_ is the set of _possible worlds_ (machine states, future times, _. . ._ )

- _R_ is the _accessibility relation_ between worlds (state transitions, flow of time, _. . ._ )

The pair _(W, R)_ is called a _modal frame_ .

The two _modal operators_ , or _modalities_ , are _2_ and _3_ :

- _2A_ means _A_ is _necessarily true_

- _3A_ means _A_ is _possibly true_

Here ‘necessarily true’ means ‘true in all worlds accessible from the present one’. The modalities are related by the law ¬ _3A_ ≃ _2_ ¬ _A_ ; in words, ‘ _A_ is necessarily false’ is equivalent to ‘it is not possible that _A_ is true’.

_Complex modalities_ are made up of strings of the modal operators, such as _22A_ , _23A_ , _32A_ , etc. Typically many of these are equivalent to others; in _S_ 4, a standard modal logic, _22A_ is equivalent to _2A_ .
