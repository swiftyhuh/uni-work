<!-- page 1 -->
# _Logic and Proof_

Computer Science Tripos Part IB Michaelmas Term

_Lawrence C Paulson_ Computer Laboratory University of Cambridge

```
lcp@cl.cam.ac.uk
```

Copyright ⃝c 2000 by Lawrence C. Paulson

<!-- page 2 -->
## Contents

|1|Introduction and Learning Guide|1|
|---|---|---|
|2|Propositional Logic|3|
|3|Proof Systems for Propositional Logic|12|
|4|Ordered Binary Decision Diagrams|19|
|5|First-order Logic|22|
|6|Formal Reasoning in First-Order Logic|29|
|7|Clause Methods for Propositional Logic|34|
|8|Skolem Functions and Herbrand’s Theorem|42|
|9|Unification|49|
|10 |Applications of Unification|58|
|11 |Modal Logics|65|
|12 |Tableaux-Based Methods|70|

i

<!-- page 3 -->
ii

<!-- page 4 -->
1

## 1 Introduction and Learning Guide

This course gives a brief introduction to logic, with including the resolution method of theorem-proving and its relation to the programming language Prolog. Formal logic is used for specifying and verifying computer systems and (sometimes) for representing knowledge in Artificial Intelligence programs.

The course should help you with _Prolog for AI_ and its treatment of logic should be helpful for understanding other theoretical courses. Try to avoid getting bogged down in the details of how the various proof methods work, since you must also acquire an intuitive feel for logical reasoning.

The most suitable course text is this book:

Michael Huth and Mark Ryan, _Logic in Computer Science: Modelling and Reasoning about Systems_ (CUP, 2000)

It costs _£_ 18.36 from Amazon. It covers most aspects of this course with the exception of resolution theorem proving. It includes material that may be useful in _Specification and Verification II_ next year, namely symbolic model checking.

Quite a few books on logic can be found in the Mathematics section of any academic bookshop. They tend to focus more on results such as the compleness theorem rather than on algorithms for proving theorems by machine. A typical example is

Dirk van Dalen, _Logic and Structure_ (Springer, 1994)

The following book is nearly 600 pages long and proceeds at a very slow pace. It is not cheap.1

Jon Barwise and John Etchemendy, _Language Proof and Logic_ (CSLI Publications, 1999)

It briefly covers some course topics (resolution and unification) but omits many others (OBDDs, the Davis-Putnam method, modal logic). Formal proofs are done in the Fitch style instead of using the sequent calculus. The book comes with a CD-ROM (for Macs and IBM PCs) containing some programs to support the text. You may find it useful if you find my course notes too concise.

Also relevant is

Melvin Fitting, _First-Order Logic and Automated Theorem Proving_ (Springer, 1996)

> 1The publisher’s price is _£_ 50, but from Amazon it costs only _£_ 29.

<!-- page 5 -->
2

#### 1 INTRODUCTION AND LEARNING GUIDE

The following book provides a different perspective on modal logic, and it carefully develops propositional logic, though you may be reluctant to spend _£_ 32 for a book that covers only a few course lectures.

Sally Popkorn, _First Steps in Modal Logic_ (CUP, 1994)

Other useful books are out of print but may be found in College libaries:

C.-L. Chang and R. C.-T. Lee, _Symbolic Logic and Mechanical Theorem Proving_ (Academic Press, 1973)

Antony Galton, _Logic for Information Technology_ (Wiley, 1990) Steve Reeves and Michael Clarke, _Logic for Computer Science_ (Addison-Wesley, 1990)

There are numerous exercises in these notes, and they are suitable for supervision purposes. Old examination questions for _Foundations of Logic Programming_ (the former name of this course) are still relevant:

- 1999 Paper 5 Question 10: Prolog resolution versus general resolution

- 1999 Paper 6 Question 10: Herbrand models and clause form

- 1998 Paper 5 Question 10: OBDDs, sequent calculus, etc. (Lect. 4)

- 1998 Paper 6 Question 10: modal logic (Lect. 11); resolution (Lect. 10)

- 1997 Paper 5 Question 10: first-order logic (Lect. 5)

- 1997 Paper 6 Question 10: sequent rules for quantifiers (Lect. 6)

- 1996 Paper 5 Question 10: sequent calculus (Lect. 3, 6, 11)

- 1996 Paper 6 Question 10: Davis-Putnam versus Resolution (Lect. 10)

- 1995 Paper 5 Question 9: OBBDs (Lect. 4)

- 1995 Paper 6 Question 9: outline logics; sequent calculus (Lect. 3, 6, 11)

- 1994 Paper 5 Question 9: Resolution versus Prolog (Lect. 10)

- 1994 Paper 6 Question 9: Herbrand models (Lect. 8)

- 1994 Paper 6 Question 9: Most general unifiers and resolution (Lect. 10)

- 1993 Paper 3 Question 3: Resolution and Prolog (Lect. 10)

<!-- page 6 -->
3

Acknowledgements. Reuben Thomas pointed out numerous errors in these notes. David Richerby and Ross Younger made detailed suggestions. Thanks also to Thomas Forster and Steve Payne.

## 2 Propositional Logic

Propositional logic deals with truth values and the logical connectives ‘and,’ ‘or,’ ‘not,’ etc. It has no variables of any kind and is unable to express anything but the simplest mathematical statements. It is studied because it is simple and because it is the basis of more powerful logics. Most of the concepts in propositional logic have counterparts in first-order logic. A logic comprises a _syntax_ , which is a formal notation for writing assertions and a _semantics_ , which gives a meaning to assertions. Its _proof theory_ gives syntactic—and therefore mechanical—methods for reasoning about assertions.

### 2.1 Syntax of propositional logic

We take for granted a set of propositional symbols _P_ , _Q_ , _R_ , _. . ._ , including the truth values t and f . A formula consisting of a propositional symbol is called _atomic_ .

Formulæ are constructed from atomic formulæ using the logical connectives

These are listed in order of precedence; ¬ is highest. We shall suppress needless parentheses, writing, for example,

In the ‘metalanguage’ (these notes), the letters _A_ , _B_ , _C_ , _. . ._ stand for arbitrary formulæ. The letters _P_ , _Q_ , _R_ , _. . ._ stand for atomic formulæ.

Some authors use ⊃ for the implies symbol and ≡ for if-and-only-if.

### 2.2 Semantics

Propositional Logic is a formal language. Each formula has a meaning (or semantics) — either t or f — relative to the meaning of the propositional symbols it

<!-- page 7 -->
4

#### 2 PROPOSITIONAL LOGIC

contains. The meaning can be calculated using the standard truth tables.

|_A_|_B_|¬_A_|_A_∧_B_|_A_∨_B_|_A_→_B_|_A_↔_B_|
|---|---|---|---|---|---|---|
|t|t|f|t|t|t|t|
|t|f|f|f|t|f|f|
|f|t|t|f|t|t|f|
|f|f|t|f|f|t|t|

By inspecting the table, we can see that _A_ → _B_ is equivalent to ¬ _A_ ∨ _B_ and that _A_ ↔ _B_ is equivalent to _(A_ → _B)_ ∧ _(B_ → _A)_ . (The latter is also equivalent to ¬ _(A_ ⊕ _B)_ , where ⊕ is exclusive or.)

Note that we are using t and f in two distinct ways: as symbols on the printed page, and as the truth values themselves. In this simple case, there should be no confusion. When it comes to first-order logic, we shall spend some time on the distinction between symbols and their meanings.

We now make some definitions that will be needed throughout the course.

Definition 1 An _interpretation_ , or _truth assignment_ , for a set of formulæ is a function from its set of propositional symbols to { t _,_ f }.

An interpretation _satisfies_ a formula if the formula evaluates to t under the interpretation.

A set _S_ of formulæ is _valid_ (or a _tautology_ ) if every interpretation for _S_ satisfies every formula in _S_ .

A set _S_ of formulæ is _satisfiable_ (or _consistent_ ) if there is some interpretation for _S_ that satisfies every formula in _S_ .

A set _S_ of formulæ is _unsatisfiable_ (or _inconsistent_ ) if it is not satisfiable.

A set _S_ of formulæ _entails A_ if every interpretation that satisfies all elements of _S_ , also satisfies _A_ . Write _S_ |= _A_ .

Formulæ _A_ and _B_ are _equivalent_ , _A_ ≃ _B_ , provided _A_ |= _B_ and _B_ |= _A_ .

It is usual to write _A_ |= _B_ instead of { _A_ } |= _B_ . We may similarly identify a one-element set with a formula in the other definitions.

Note that |= and ≃ are not logical connectives but relations between formulæ. They belong not to the logic but to the metalanguage: they are symbols we use to discuss the logic. They therefore have lower precedence than the logical connectives. No parentheses are needed in _A_ ∧ _A_ ≃ _A_ because the only possible reading is _(A_ ∧ _A)_ ≃ _A_ . We may not write _A_ ∧ _(A_ ≃ _A)_ because _A_ ≃ _A_ is not a formula.

In propositional logic, a valid formula is also called a _tautology_ . Here are some examples of these definitions.

- The formulæ _A_ → _A_ and ¬ _(A_ ∧¬ _A)_ are valid for every formula _A_ .

<!-- page 8 -->
5

2.3 Applications of propositional logic

- The formulæ _P_ and _P_ ∧ _(P_ → _Q)_ are satisfiable: they are both true under the interpretation that maps _P_ and _Q_ to t . But they are not valid: they are both false under the interpretation that maps _P_ and _Q_ to f .

- The formula ¬ _A_ is unsatisfiable for every valid formula _A_ . This set of formulæ is unsatisfiable: { _P, Q,_ ¬ _P_ ∨¬ _Q_ }

_Exercise 1_ Is the formula _P_ →¬ _P_ satisfiable? Is it valid?

### 2.3 Applications of propositional logic

Hardware design is the obvious example. Propositional logic is used to minimize the number of gates in a circuit, and to show the equivalence of combinational circuits. There now exist highly efficient tautology checkers, such as OBDDs (Ordered Binary Decision Diagrams), which have been used to verify complex combinational circuits. This is an important branch of hardware verification.

Chemical synthesis is a more offbeat example.2 Under suitable conditions, the following chemical reactions are possible:

Show we can make H2CO3 given supplies of HCl, NaOH, O2, and C.

Chang and Lee formalize the supplies of chemicals as four axioms and prove that H2CO3 logically follows. The idea is to formalize each compound as a propositional symbol and express the reactions as implications:

Note that this involves an ideal model of chemistry. What if the reactions can be inhibited by the presence of other chemicals? Proofs about the real world _always_ depend upon general assumptions. It is essential to bear these in mind when relying on such a proof.

2Chang and Lee, page 21, as amended by Ross Younger

<!-- page 9 -->
6

2 PROPOSITIONAL LOGIC

### 2.4 Equivalences

Note that _A_ ↔ _B_ and _A_ ≃ _B_ are different kinds of assertions. The formula _A_ ↔ _B_ refers to some fixed interpretation, while the metalanguage statement _A_ ≃ _B_ refers to all interpretations. On the other hand, |= _A_ ↔ _B_ means the same thing as _A_ ≃ _B_ . Both are metalanguage statements, and _A_ ≃ _B_ is equivalent to saying that the formula _A_ ↔ _B_ is a tautology.

Similarly, _A_ → _B_ and _A_ |= _B_ are are different kinds of assertions, while |= _A_ → _B_ and _A_ |= _B_ mean the same thing. The formula _A_ → _B_ is a tautology if and only if _A_ |= _B_ .

Here is a listing of some of the more basic equivalences of propositional logic. They provide one means of reasoning about propositions, namely by transforming one proposition into an equivalent one. They are also needed to convert propositions into various normal forms.

_commutative laws_

_A_ ∧ _B_ ≃ _B_ ∧ _A A_ ∨ _B_ ≃ _B_ ∨ _A_

_associative laws_

_distributive laws_

_A_ ∨ _(B_ ∧ _C)_ ≃ _(A_ ∨ _B)_ ∧ _(A_ ∨ _C) A_ ∧ _(B_ ∨ _C)_ ≃ _(A_ ∧ _B)_ ∨ _(A_ ∧ _C)_

_de Morgan laws_

_definitions of connectives_

_A_ ↔ _B_ ≃ _(A_ → _B)_ ∧ _(B_ → _A)_ ¬ _A_ ≃ _A_ → f

_A_ → _B_ ≃¬ _A_ ∨ _B_

<!-- page 10 -->
2.5 Normal forms

7

_more negation laws_

#### _simplification_

Propositional logic enjoys a principle of duality: for every equivalence _A_ ≃ _B_ there is another equivalence _A_′ ≃ _B_′ , where _A_′ , _B_′ are derived from _A_ , _B_ by exchanging ∧ with ∨ and t with f . Before applying this rule, remove all occurrences of → and ↔, since they implicitly involve ∧ and ∨.

_Exercise 2_ Verify some of the equivalences using truth tables.

### 2.5 Normal forms

The language of propositional logic is redundant: many of the connectives can be defined in terms of others. By repeatedly applying certain equivalences, we can transform a formula into a _normal form_ . A typical normal form eliminates certain connectives entirely, and uses others in a restricted manner. The restricted structure makes the formula easy to process, although the normal form may be exponentially larger than the original formula. Most normal forms are unreadable, although Negation Normal Form is not too bad.

Definition 2 A _literal_ is an atomic formula or its negation. Let _K_ , _L_ , _L_′ , _. . ._ stand for literals.

A _maxterm_ is a literal or a disjunction of literals.

A _minterm_ is a literal or a conjunction of literals.

- A formula is in _Negation Normal Form_ (NNF) if the only connectives in it are

- ∧, ∨, and ¬, where ¬ is only applied to atomic formulæ.

- A formula is in _Conjunctive Normal Form_ (CNF) if it has the form _A_ 1 ∧· · · ∧

- _Am_ , where each _Ai_ is maxterm.

A formula is in _Disjunctive Normal Form_ (DNF) if it has the form _A_ 1 ∨· · · ∨ _Am_ , where each _Ai_ is a minterm.

<!-- page 11 -->
8

2 PROPOSITIONAL LOGIC

An atomic formula like _P_ is in all the normal forms NNF, CNF, and DNF. The formula

is in CNF. To get an example of a DNF formula, exchange ∧ and ∨ above. Every formula in CNF or DNF is also in NNF, but the NNF formula

is neither CNF nor DNF.

One advantage of NNF is that it reveals the true nature of a formula. For example, converting ¬ _(A_ → _B)_ to NNF yields _A_ ∧¬ _B_ . This reveals that the original formula was effectively a conjunction.

### 2.6 Translation to normal form

Every formula can be translated into an equivalent formula in NNF, CNF, or DNF by means of the following steps.

Step 1. Eliminate ↔ and → by repeatedly applying the following equivalences:

Step 2. Push negations in until they apply only to atoms, repeatedly replacing by the equivalences

At this point, the formula is in Negation Normal Form.

Step 3. To obtain CNF, push disjunctions in until they apply only to literals. Repeatedly replace by the equivalences

These two equivalences obviously say the same thing, since disjunction is commutative. In fact, we have

Use this equivalence when you can, to save writing.

<!-- page 12 -->
2.7 Tautology checking using CNF

9

Step 4. Simplify the resulting CNF by deleting any maxterm that contains both _P_ and ¬ _P_ , since it is equivalent to t . Also delete any maxterm that includes another maxterm (meaning, every literal in the latter is also present in the former). This is correct because _A_ ∧ _(A_ ∨ _B)_ ≃ _A_ . Finally, two maxterms of the form _P_ ∨ _A_ and ¬ _P_ ∨ _A_ can be replaced by _A_ , thanks to the equivalence

This simplification is related to the resolution rule, which we shall study later.

Since ∨ is commutative, saying ‘a maxterm of the form _A_ ∨ _B_ ’ refers to any possible way of arranging the literals into two parts. This includes _A_ ∨ f , since one of those parts may be empty and the empty disjunction is false. So in the last simplification above, two maxterms of the form _P_ and ¬ _P_ can be replaced by f .

Steps 3’ and 4’. To obtain DNF, apply instead the other distributive law:

Exactly the same simplifications can be performed for DNF as for CNF, exchanging the roles of ∧ and ∨.

### 2.7 Tautology checking using CNF

Here is a method of proving theorems in propositional logic. To prove _A_ , reduce it to CNF. If the simplified CNF formula is t then _A_ is valid because each transformation preserves logical equivalence. And if the CNF formula is not t , then _A_ is not valid.

To see why, suppose the CNF formula is _A_ 1 ∧· · · ∧ _Am_ . If _A_ is valid then each _Ai_ must also be valid. Write _Ai_ as _L_ 1 ∨· · · ∨ _L n_ , where the _L j_ are literals. We can make an interpretation _I_ that falsifies every _L j_ , and therefore falsifies _Ai_ . Define _I_ such that, for every propositional letter _P_ ,

This definition is legitimate because there cannot exist literals _L j_ and _L k_ such that _L j_ is ¬ _L k_ ; if there did, then simplification would have deleted the disjunction _Ai_ .

The powerful OBDD method is related to this CNF method. It uses an if-thenelse data structure, an ordering on the propositional letters, and some standard algorithmic techniques (such as hashing) to gain efficiency.

<!-- page 13 -->
10

2 PROPOSITIONAL LOGIC

Example 1 Start with

Step 1, eliminate →, gives

Step 2, push negations in, gives

Step 3, push disjunctions in, gives

Simplifying yields

The interpretation _P_ �→ t _, Q_ �→ f _, R_ �→ f falsifies this formula, which is equivalent to the original formula. So the original formula is not valid.

Example 2 Start with

Step 1, eliminate →, gives

Step 2, push negations in, gives

Step 3, push disjunctions in, gives

Simplifying yields t ∧ t , which is t . Both conjuncts are valid since they contain a formula and its negation. Thus _P_ ∧ _Q_ → _Q_ ∧ _P_ is valid.

<!-- page 14 -->
2.7 Tautology checking using CNF

11

Example 3 Peirce’s law is another example. Start with

Step 1, eliminate →, gives

Step 2, push negations in, gives

Step 3, push disjunctions in, gives

Simplifying again yields t . Thus Peirce’s law is valid.

There is a dual method of refuting _A_ (proving inconsistency). To refute _A_ , reduce it to DNF, say _A_ 1 ∨· · · ∨ _Am_ . If _A_ is inconsistent then so is each _Ai_ . Suppose _Ai_ is _L_ 1 ∧· · · ∧ _L n_ , where the _L j_ are literals. If there is some literal _L_′ such that the _L j_ include both _L_′ and ¬ _L_′ , then _Ai_ is inconsistent. If not then there is an interpretation that verifies every _L j_ — and so _Ai_ .

To prove _A_ , we can use the DNF method to refute ¬ _A_ . The steps are exactly the same as the CNF method because the extra negation swaps every ∨ and ∧. Gilmore implemented a theorem prover based upon this method in 1960 (see Chang and Lee, page 62).

_Exercise 3_ Each of the following formulæ is satisfiable but not valid. Exhibit an interpretation that makes the formula true and another interpretation that makes the formula false.

_Exercise 4_ Convert of the following propositional formulæ into Conjunctive Normal Form and also into Disjunctive Normal Form. For each formula, state whether it is valid, satisfiable, or unsatisfiable; justify each answer.

<!-- page 15 -->
3 PROOF SYSTEMS FOR PROPOSITIONAL LOGIC

#### 12

_Exercise 5_ Using ML or Lisp, define data structures for representing propositions and interpretations. Write a function to test whether or not a proposition holds under an interpretation (both supplied as arguments). Write a function to convert a proposition to Negation Normal Form.

## 3 Proof Systems for Propositional Logic

We can verify any tautology by checking all possible interpretations, using the truth tables. This is a _semantic_ approach, since it appeals to the meanings of the connectives.

The _syntactic_ approach is formal proof: generating theorems, or reducing a conjecture to a known theorem, by applying syntactic transformations of some sort. We have already seen a proof method based on CNF. Most proof methods are based on axioms and inference rules.

What about efficiency? Deciding whether a propositional formula is satisfiable is an NP-complete problem (Aho, Hopcroft and Ullman 1974, pages 377–383). Thus all approaches are likely to be exponential in the length of the formula.

### 3.1 A Hilbert-style proof system

Here is a simple proof system for propositional logic. There are countless similar systems. They are often called _Hilbert systems_ after the logician David Hilbert, although they existed before him.

This proof system provides rules for implication only. The other logical connectives are not taken as primitive. They are instead _defined_ in terms of implication:

Obviously, these definitions apply when we are discussing this proof system! Note that _A_ → _(B_ → _A)_ is a tautology. Call it Axiom K. Also,

is a tautology. Call it Axiom S. The Double-Negation Law ¬¬ _A_ → _A_ , is a tautology. Call it Axiom DN.

These axioms are more properly called _axiom schemes_ , since we assume all instances of them that can be obtained by substituting formulæ for _A_ , _B_ and _C_ .

<!-- page 16 -->
3.2 Gentzen’s Natural Deduction Systems

13

Whenever _A_ → _B_ and _A_ are both valid, it follows that _B_ is valid. We write this as the inference rule

This rule is traditionally called Modus Ponens. Together with Axioms K, S, and DN and the definitions, it suffices to prove all tautologies of (classical) propositional logic.3 However, this formalization of propositional logic is inconvenient to use. For example, try proving _A_ → _A_ !

A variant of this proof system replaces the Double-Negation Law by the Contrapositive Law:

Another formalization of propositional logic consists of the Modus Ponens rule plus the following axioms:

Here _A_ ∧ _B_ and _A_ → _B_ are defined in terms of ¬ and ∨.

Where do truth tables fit into all this? Truth tables define the _semantics_ , while proof systems define what is sometimes called the _proof theory_ . A proof system is should respect the truth tables. Above all, we expect the proof system to be _sound_ : every theorem it generates must be a tautology. For this to hold, every axiom must be a tautology and every inference rule must yield a tautology when it is applied to a tautology.

The converse property is _completeness_ : the proof system can generate every tautology. Completeness is harder to achieve and to demonstrate. There are complete proof systems even for first-order logic. G¨odel’s incompleteness theorem says that there are no “interesting” complete proof systems for logical theories strong enough to define the properties of the natural numbers.

### 3.2 Gentzen’s Natural Deduction Systems

Natural proof systems do exist. Natural deduction, devised by Gerhard Gentzen, is based upon three principles:

> 3If the Double-Negation Law is omitted, only the intuitionistic tautologies are provable. This axiom system is connected with the combinators _S_ and _K_ and the _λ_ -calculus.

<!-- page 17 -->
14

3 PROOF SYSTEMS FOR PROPOSITIONAL LOGIC

1. Proof takes place within a varying context of assumptions.

2. Each logical connective is defined independently of the others. (This is possible because item 1 eliminates the need for tricky uses of implication.)

3. Each connective is defined by _introduction_ and _elimination_ rules.

For example, the _introduction_ rule for ∧ describes how to deduce _A_ ∧ _B_ :

The _elimination_ rules for ∧ describe what to deduce _from A_ ∧ _B_ :

The elimination rule for → says what to deduce from _A_ → _B_ . It is just Modus Ponens:

The introduction rule for → says that _A_ → _B_ is proved by assuming _A_ and deriving _B_ :

For simple proofs, this notion of assumption is pretty intuitive. Here is a proof of the formula _A_ ∧ _B_ → _A_ :

The key point is that rule _(_ → _i) discharges_ its assumption: the assumption could be used to prove _A_ from _A_ ∧ _B_ , but is no longer available once we conclude _A_ ∧ _B_ → _A_ .

The introduction rules for ∨ are straightforward:

<!-- page 18 -->
15

3.3 The sequent calculus

The elimination rule says that to show some _C_ from _A_ ∨ _B_ there are two cases to consider, one assuming _A_ and one assuming _B_ :

The scope of assumptions can get confusing in complex proofs. Let us switch attention to the sequent calculus, which is similar in spirit but easier to use.

### 3.3 The sequent calculus

The _sequent calculus_ resembles natural deduction, but it makes the set of assumptions explicit. Thus, it is more concrete.

A _sequent_ has the form _�_ ⇒ _�_ , where _�_ and _�_ are finite sets of formulæ.4 These sets may be empty. The sequent

is _true_ if _A_ 1 ∧ _. . ._ ∧ _Am_ implies _B_ 1 ∨ _. . ._ ∨ _Bn_ . In other words, we assume that each of _A_ 1, _. . ._ , _Am_ are true and try to show that at least one of _B_ 1, _. . ._ , _Bn_ is true.

A _basic_ sequent is one in which the same formula appears on both sides, as in _P, B_ ⇒ _B, R_ . This sequent is true because, if all the formulæ on the left side are true, then in particular _B_ is; so, least one right-side formula ( _B_ again) is true. Our calculus therefore regards all basic sequents as proved.

Every basic sequent might be written in the form { _A_ } ∪ _�_ ⇒{ _A_ } ∪ _�_ , where _A_ is the common formula and _�_ and _�_ are the other left- and right-side formulæ, respectively. The sequent calculus identifies the one-element set { _A_ } with its element _A_ and denotes union by a comma. Thus, the correct notation for the general form of a basic sequent is _A, �_ ⇒ _A, �_ .

Sequent rules are almost always used backward. We start with the sequent that we would like to prove and, working backwards, reduce it to simpler sequents in the hope of rendering them trivial. The forward direction would be to start with known facts and derive new facts, but this approach tends to generate random theorems rather than ones we want.

Sequent rules are classified as _right_ or _left_ , indicating which side of the ⇒ symbol they operate on. Rules that operate on the right side are analogous to natural deduction’s introduction rules, and left rules are analogous to elimination rules.

4With minor changes, sequents can instead be lists or multisets.

<!-- page 19 -->
16 3 PROOF SYSTEMS FOR PROPOSITIONAL LOGIC

The sequent calculus analogue of _(_ → _i)_ is the rule

Working backwards, this rule breaks down some implication on the right side of a sequent; _�_ and _�_ stand for the sets of formulæ that are unaffected by the inference. The analogue of the pair _(_ ∨ _i_ 1 _)_ and _(_ ∨ _i_ 2 _)_ is the single rule

This breaks down some disjunction on the right side, replacing it by both disjuncts. Thus, the sequent calculus is a kind of multiple-conclusion logic. Figure 1 summarises the rules.

_Negation rules_ :

_Conjunction rules_ :

_Disjunction rules_ :

_Implication rules_ :

Figure 1: Sequent Rules for Propositional Logic

To illustrate the use of multiple formulæ on the right, let us prove the classical theorem _(A_ → _B)_ ∨ _(B_ → _A)_ . Working backwards (or upwards), we reduce this

<!-- page 20 -->
3.3 The sequent calculus

17

formula to a basic sequent:

The basic sequent has a line over it to emphasize that it is provable.

This example is typical of the sequent calculus: start with the desired theorem and apply rules _backwards_ in a fairly arbitrary manner. This yields a surprisingly effective proof procedure.

Here is part of a proof of the distributive law _A_ ∨ _(B_ ∧ _C)_ ≃ _(A_ ∨ _B)_ ∧ _(A_ ∨ _C)_ :

The second, omitted proof tree proves _A_ ∨ _(B_ ∧ _C)_ ⇒ _A_ ∨ _C_ similarly.

Finally, here is a failed proof of the invalid formula _A_ ∨ _B_ → _B_ ∨ _C_ .

The sequent _A_ ⇒ _B, C_ has no line over it because it is not valid! The interpretation _A_ �→ t _, B_ �→ f _, C_ �→ f falsifies it. We have already seen this as Example 1 (page 10).

_Structural_ rules concern sequents in general rather than particular connectives. The _weakening_ rules allow additional formulæ to be inserted on the left or right side. Obviously, if _�_ ⇒ _�_ holds then the sequent continues to hold after further assumptions or goals are added:

_Exchange_ rules allow formulæ in a sequent to be re-ordered. We don’t need them because our sequents are sets rather than lists. Contraction rules allow formulæ to be used more than once:

<!-- page 21 -->
18

3 PROOF SYSTEMS FOR PROPOSITIONAL LOGIC

Because the sets { _A_ } and { _A, A_ } are identical, we don’t need contraction rules either. Moreover, it turns out that we almost never need to use a formula more than once. Exceptions are ∀ _x A_ (when it appears on the left) and ∃ _x A_ (when it appears on the right).

The _cut rule_ allows the use of lemmas. Some formula _A_ is proved in the first premise, and assumed in the second premise. A famous result, the _cut-elimination theorem_ , states that this rule is not required. All uses of it can be removed from any proof, but the proof could get exponentially larger.

This special case of cut may be easier to understand. We prove lemma _A_ from _�_ and use _A_ and _�_ together to reach the conclusion _B_ .

Since _�_ contains as much information as _A_ , it is natural to expect that such lemmas should not be necessary, but the cut-elimination theorem is quite hard to prove.

Note On the Thor directory `/group/clteach/lcp/Logic` there is a simple theorem prover called `folderol.ML` . It can prove easy first-order theorems using the sequent calculus, and outputs a summary of each proof. The file begins with very basic instructions describing how to run it. The file `testsuite.ML` contains further instructions and numerous examples.

_Exercise 6_ Prove the following sequents:

_Exercise 7_ Prove the following sequents:

<!-- page 22 -->
19

## 4 Ordered Binary Decision Diagrams

A binary decision tree represents a propositional formulæ by binary decisions, namely if-then-else expressions over the propositional letters. (In the relevant literature, propositional letters are called _variables_ .) A tree may contain much redundancy; a binary decision _diagram_ is a directed graph, sharing identical subtrees. An _ordered_ binary decision diagram (OBDD) is based upon giving an ordering _<_ to the variables: they must be tested in order. Further refinements ensure that each propositional formula is mapped to a unique OBDD, for a given ordering.

An OBDD representation must satisfy the following conditions:

- _ordering_ : if _P_ is tested before _Q_ , then _P < Q_ (thus in particular, _P_ cannot be tested more than once on a single path)

- _uniqueness_ : identical subgraphs are stored only once (to do this efficiently, hash each node by its variable and pointer fields)

- _irredundancy_ : no test leads to identical subgraphs in the t and f cases (thanks to uniqueness, redundant tests can be detected by comparing pointers)

Because the OBDD representation of each formula is unique, it is called a _canonical form_ . Canonical forms usually lead to good algorithms — for a start, you can test whether two things are equivalent by comparing their canonical forms.

The OBDD form of any tautology is t . Similarly, that of any inconsistent formula is f . To check whether two formulæ are logically equivalent, convert both to OBDD form and then — thanks to uniqueness — simply compare the pointers.

A recursive algorithm converts a formula to an OBDD. All the logical connectives can be handled directly, including → and ↔. (Exclusive ‘or’ is also used, especially in hardware examples.) The expensive transformation of _A_ ↔ _B_ into _(A_ → _B)_ ∧ _(B_ → _A)_ is unnecessary.

Here is how to convert a conjunction _A_ ∧ _A_′ to an OBDD. In this algorithm, _X__P_ _Y_is a decision node that tests the variable_P_, with a ‘true’ link to_X_and a ‘false’ link to _Y_ . In other words, _XPY_ is the OBDD equivalent of the decision ‘if _P_ then _X_ else _Y_ .’

1. Recursively convert _A_ and _A_′ to OBDDs _Z_ and _Z_′ .

2. Check for trivial cases. If _Z_ = _Z_′ (pointer comparison) then the result is _Z_ ; if either operand is f , then the result is f ; if either operand is t , then the result is the other operand.

<!-- page 23 -->
#### 20 4 ORDERED BINARY DECISION DIAGRAMS

3. In the general case, let _Z_ = _XPY_ and _Z_′ = _X_ ′ _PY_′′.There are three possibili- ties:

   - (a) If _P_ = _P_′ then recursively build the OBDD _X_ ∧ _X_ ′ _PY_ ∧ _Y_ ′. This means convert _X_ ∧ _X_′ and _Y_ ∧ _Y_′ to OBDDs _U_ and _U_′ , then construct a new decision node from _P_ to them. Do the usual simplifications. If _U_ = _U_′ then the resulting OBDD for the conjunction is _U_ . If an identical decision node from _P_ to _(U, U_′ _)_ has been created previously, then that existing node is used instead of creating a new one.

   - (b) If _P < P_′ then recursively build the OBDD _X_ ∧ _Z_ ′ _PY_ ∧ _Z_ ′. When building OBDDs on paper, it is easier to pretend that the second decision node also starts with _P_ : assume that it has the redundant decision _Z_ ′ _PZ_ ′ and proceed as in case (3a).

   - (c) If _P > P_′ is treated analogously to the previous case.

Other connectives are treated similarly; they differ only in the trivial cases. The negation of the OBDD _XPY_ is ¬ _XP_ ¬ _Y_ . In essence we copy the OBDD, and when we reach the leaves, exchange t and f .

During this processing, the same input (consisting of a connective and two OBDDs) may be transformed into an OBDD repeatedly. Efficient implementations therefore have an additional hash table, which associates inputs to the corresponding OBDDs. The result of every transformation is stored in the hash table so that it does not have to be computed again.

For more details, please see Bryant (1992), part of which is attached as an appendix to these notes. Section 3.1 describes a construction method that can be done using pencil and paper. In essence, the idea goes like this:

- Draw the two OBDDs to be combined by a connective such as ∧.

- Label the nodes of the first one _A_ 1, _. . ._ , _Am_ and of the second one _B_ 1, _. . ._ , _Bn_ .

- Draw the graph that results from merging the two OBDDs while respecting the variable ordering. Each node of the new graph will have a label of the form _Ai B j_ , and will be a decision on the earlier of the two Boolean variables.

- Apply the connective to the zeroes and ones in the leaves.

- Simplify the new OBDD by deleting redundant nodes.

You will need to read Section 3.1 of Bryant (1992) in order to understand this method properly.

<!-- page 24 -->
21

Example 4 We apply the OBDD Canonicalisation Algorithm to _P_ ∨ _Q_ → _Q_ ∨ _R_ . First, we make tiny OBDDs for _P_ and _Q_ . Then, we combine them using ∨ to make a small OBDD for _P_ ∨ _Q_ :

The OBDD for _Q_ ∨ _R_ has a similar construction, so we omit it. We combine the two small OBDDs using → to obtain the final OBDD:

<!-- Start of picture text -->
P Q P P → Q Q Q R R 0 1 0 1 0 1 <!-- End of picture text -->

We can read off from this that the original formula is always true except if _P_ is true while _Q_ and _R_ are false.

_Exercise 8_ Compute the OBDD for each of the following formulæ, taking the variables as alphabetically ordered:

_Exercise 9_ Verify the following equivalences using OBDDs:

<!-- page 25 -->
5 FIRST-ORDER LOGIC

22

_Exercise 10_ Verify the following equivalences using OBDDs:

## 5 First-order Logic

First-order logic (FOL) extends propositional logic to allow reasoning about the members (such as numbers) of some non-empty universe. It uses the quantifiers ∀ (‘for all’) and ∃ (‘there exists’). First-order logic has variables ranging over ‘individuals,’ but not over functions or predicates; such variables are found in second- or higher-order logic.

### 5.1 Syntax of first-order Logic

_Terms_ stand for individuals while _formulæ_ stand for truth values. We assume there is an infinite supply of _variables x_ , _y_ , _. . ._ that range over individuals. A _first-order language_ specifies symbols that may appear in terms and formulæ. A first-order language _L_ contains, for all _n_ ≥ 0, a set of _n_ -place _function symbols f_ , _g_ , _. . ._ and _n_ -place _predicate symbols P_ , _Q_ , _. . ._ . These sets may be empty, finite, or infinite.

_Constant symbols a_ , _b_ , _. . ._ are simply 0-place function symbols. Intuitively, they are names for fixed elements of the universe. It is not required to have a constant for each element; conversely, two constants are allowed to have the same meaning.

Predicate symbols are also called _relation symbols_ . Prolog programmers refer to function symbols as _functors_ .

Definition 3 The _terms t_ , _u_ , _. . ._ of a first-order language are defined recursively as follows:

- A variable is a term.

- A constant symbol is a term.

- If _t_ 1, _. . ._ , _tn_ are terms and _f_ is an _n_ -place function symbol then _f (t_ 1 _, . . . , tn)_ is a term.

Definition 4 The _formulæ A_ , _B_ , _. . ._ of a first-order language are defined recursively as follows:

<!-- page 26 -->
5.2 Examples of statements in first-order logic

23

- If _t_ 1, _. . ._ , _tn_ are terms and _P_ is an _n_ -place predicate symbol then _P(t_ 1 _, . . . , tn)_ is a formula (called an _atomic formula_ ).

- If _A_ and _B_ are formulæ then ¬ _A_ , _A_ ∧ _B_ , _A_ ∨ _B_ , _A_ → _B_ , _A_ ↔ _B_ are also formulæ.

- If _x_ is a variable and _A_ is a formula then ∀ _x A_ and ∃ _x A_ are also formulæ.

Brackets are used in the conventional way for grouping. Terms and formulæ are tree-like data structures, not strings.

The quantifiers ∀ _x A_ and ∃ _x A_ bind tighter than the binary connectives; thus ∀ _x A_ ∧ _B_ is equivalent to _(_ ∀ _x A)_ ∧ _B_ . Sometimes you will see an alternative quantifier syntax, ∀ _x . A_ and ∃ _x . B_ , which binds looser than the binary connectives; thus ∀ _x . A_ ∧ _B_ is equivalent to ∀ _x . (A_ ∧ _B)_ . The dot is the giveaway; be careful!

Nested quantifications such as ∀ _x_ ∀ _y A_ are abbreviated to ∀ _xy A_ .

Example 5 A language for arithmetic might have the constant symbols 0, 1, 2, _. . ._ , and function symbols +, −, ×, _/_ , and the predicate symbols =, _<_ , _>_ , _. . ._ . We informally may adopt an infix notation for the function and predicate symbols. Terms include 0 and _(x_ + 3 _)_ − _y_ ; formulæ include _y_ = 0 and _x_ + _y < y_ + _z_ .

### 5.2 Examples of statements in first-order logic

Here are some sample formulæ with a rough English translation. English is easier to understand but is too ambiguous for long derivations.

_All professors are brilliant_ :

_The income of any banker is greater than the income of any bedder_ :

Note that _>_ is a 2-place relation symbol. The infix notation is simply a convention. _Every student has a supervisor_ :

This does not preclude a student having several supervisors. _Every student’s tutor is a member of the student’s College_ :

∀ _xy (_ student _(x)_ ∧ college _(y)_ ∧ member _(x, y)_ → member _(_ tutor _(x), y))_

<!-- page 27 -->
5 FIRST-ORDER LOGIC

24

The use of a function ‘tutor’ incorporates the assumption that every student has exactly _one_ tutor.

A mathematical example: _there exist infinitely many Pythagorean triples_ :

Here the superscript 2 refers to the squaring function. Equality (=) is just another relation symbol (satisfying suitable axioms) but there are many special techniques for it.

First-order logic assumes a non-empty domain: thus ∀ _x P(x)_ implies ∃ _x P(x)_ . If the domain could be empty, even ∃ _x_ t could fail to hold. Note also that ∀ _x_ ∃ _y y_2 = _x_ is true if the domain is the complex numbers, and is false if the domain is the integers or reals. We determine properties of the domain by asserting the set of statements it must satisfy.

There are many other forms of logic. _Many-sorted first-order logic_ assigns types to each variable, function symbol and predicate symbol, with straightforward type checking; types are called _sorts_ and denote non-empty domains. _Second-order logic_ allows quantification over functions and predicates. It can express mathematical induction by

using quantification over the unary predicate _P_ . In second-order logic, these functions and predicates must themselves be first-order, taking no functions or predicates as arguments. _Higher-order logic_ allows unrestricted quantification over functions and predicates of any order. The list of logics could be continued indefinitely.

### 5.3 Formal semantics of first-order logic

Let us rigorously define the meaning of formulæ. An interpretation of a language maps its function symbols to actual functions, and its relation symbols to actual relations. For example, the predicate symbol ‘student’ could be mapped to the set of all students currently enrolled at the University.

Definition 5 Let _L_ be a first-order language. An _interpretation I_ of _L_ is a pair _(D, I )_ . Here _D_ is a nonempty set, the _domain_ or _universe_ . The operation _I_ maps symbols to individuals, functions or sets:

- if _c_ is a constant symbol (of _L_ ) then _I_ [ _c_ ] ∈ _D_

- if _f_ is an _n_ -place function symbol then _I_ [ _f_ ] ∈ _D__n_ → _D_ (which means _I_ [ _f_ ] is an _n_ -place function on _D_ )

<!-- page 28 -->
5.4 What is truth?

25

- if _P_ is an _n_ -place relation symbol then _I_ [ _P_ ] ⊆ _D__n_ (which means _I_ [ _P_ ] is an _n_ -place relation on _D_ )

There are various ways of talking about the values of variables under an interpretation. One way is to ‘invent’ a constant symbol for every element of _D_ . More natural is to represent the values of variables using an environment, known as a _valuation_ .

Definition 6 A _valuation V_ of _L_ over _D_ is a function from the variables of _L_ into _D_ . Write _IV_ [ _t_ ] for the value of _t_ with respect to _I_ and _V_ , defined by

Write _V_ { _a/x_ } for the valuation that maps _x_ to _a_ and is otherwise the same as _V_ . Typically, we modify a valuation one variable at a time. This is a semantic analogue of substitution for the variable _x_ .

### 5.4 What is truth?

We now can define truth itself. (First-order truth, that is!) This formidable definition formalizes the intuitive meanings of the connectives. Thus it almost looks like a tautology. It effectively specifies each connective by English descriptions. Valuations help specify the meanings of quantifiers. Alfred Tarski first defined truth in this manner.

Definition 7 Let _A_ be a formula. Then for an interpretation _I_ = _(D, I )_ write |= _I,V A_ to mean ‘ _A_ is true in _I_ under _V_ .’ This is defined by cases on the construction of the formula _A_ :

- |= _I,V P(t_ 1 _, . . . , tn)_ if _I_ [ _P_ ] _(IV_ [ _t_ 1] _, . . . , IV_ [ _tn_ ] _)_ holds (that is, the actual relation _I_ [ _P_ ] holds of the values of the arguments)

- |= _I,V t_ = _u_ if _IV_ [ _t_ ] equals _IV_ [ _u_ ] (if = is a predicate symbol of the language, then we insist that it really denotes equality)

- |= _I,V_ ¬ _B_ if |= _I,V B_ does not hold

- |= _I,V B_ ∧ _C_ if |= _I,V B_ and |= _I,V C_

- |= _I,V B_ ∨ _C_ if |= _I,V B_ or |= _I,V C_

|= _I,V B_ → _C_ if |= _I,V B_ does not hold or |= _I,V C_

<!-- page 29 -->
26 5 FIRST-ORDER LOGIC

|= _I,V_ ∃ _x B_ if there exists _m_ ∈ _D_ such that |= _I,V_ { _m/x_ } _B_ holds (that is, _B_ holds when _x_ has the value _m_ )

The cases for ∧, ∨, → and ↔ follow the propositional truth tables.

Write |= _I A_ provided |= _I,V A_ for all _V_ . Clearly, if _A_ is closed (contains no free variables) then its truth is independent of the valuation. If _A_ contains free variables _x_ 1, _. . ._ , _xn_ then these in effect are universally quantified:

The definitions of valid, satisfiable, etc. carry over almost verbatim from Section 2.2.

Definition 8 An interpretation _I satisfies_ a formula if |= _I A_ holds.

A set _S_ of formulæ is _valid_ if every interpretation of _S_ satisfies every formula in _S_ .

A set _S_ of formulæ is _satisfiable_ (or _consistent_ ) if there is some interpretation of _S_ that satisfies every formula in _S_ .

A set _S_ of formulæ is _unsatisfiable_ (or _inconsistent_ ) if it is not satisfiable. (Each interpretation falsifies some formula of _S_ .)

A _model_ of a set _S_ of formulæ is an interpretation that satisfies every formula in _S_ . We also consider models that satisfy a single formula.

Unlike in propositional logic, models can be infinite and there can be an infinite number of models. There is no chance of proving validity by checking all models. We must rely on proof.

Example 6 The formula _P(a)_ ∧¬ _P(b)_ is satisfiable. Consider the interpretation with _D_ = {0 _,_ 1} and _I_ defined by

On the other hand, _P(x)_ ∧¬ _P(y)_ is unsatisfiable. Its free variables are taken to be universally quantified, so it is equivalent to ∀ _xy (P(x)_ ∧¬ _P(y))_ .

The formula _(_ ∃ _x P(x))_ → _P(c)_ holds in the interpretation _(D, I )_ where _D_ = {0 _,_ 1}, _I_ [ _P_ ] = {0}, and _I_ [ _c_ ] = 0. (Thus _P(x)_ means ‘ _x_ equals 0’ and _c_ denotes

<!-- page 30 -->
5.4 What is truth?

27

0.) If we modify this interpretation by making _I_ [ _c_ ] = 1 then the formula no longer holds. Thus it is satisfiable but not valid.

The formula _(_ ∀ _x P(x))_ → _(_ ∀ _x P( f (x)))_ is valid, for let _(D, I )_ be an interpretation. If ∀ _x P(x)_ holds in this interpretation then _P(x)_ holds for all _x_ ∈ _D_ , thus _I_ [ _P_ ] = _D_ . The symbol _f_ denotes some actual function _I_ [ _f_ ] ∈ _D_ → _D_ . Since _I_ [ _P_ ] = _D_ and _I_ [ _f_ ] _(x)_ ∈ _D_ for all _x_ ∈ _D_ , formula ∀ _x P( f (x))_ holds. The formula ∀ _xy x_ = _y_ is satisfiable but not valid; it is true in every domain that consists of exactly one element. (The empty domain is not allowed in firstorder logic.)

Example 7 Let _L_ be the first-order language consisting of the constant 0 and the (infix) 2-place function symbol +. An interpretation _I_ of this language is any non-empty domain _D_ together with values _I_ [0] and _I_ [+], with _I_ [0] ∈ _D_ and _I_ [+] ∈ _D_ × _D_ → _D_ . In the language _L_ we may express the following axioms:

(Remember, free variables in effect are universally quantified, by the definition of |= _I A_ .) One model of these axioms is the set of natural numbers, provided we give 0 and + the obvious meanings. But the axioms have many other models.5 Below, let _A_ be some set.

1. The set of all strings (in ML say) letting 0 denote the empty string and + string concatenation.

2. The set of all subsets of _A_ , letting 0 denote the empty set and + union.

3. The set of functions in _A_ → _A_ , letting 0 denote the identity function and + composition.

_Exercise 11_ To test your understanding of quantifiers, consider the following formulæ: _everybody loves somebody_ vs _there is somebody that everybody loves_ :

Does (1) imply (2)? Does (2) imply (1)? Consider both the informal meaning and the formal semantics defined above.

> 5Models of these axioms are called _monoids_ .

<!-- page 31 -->
5 FIRST-ORDER LOGIC

28

_Exercise 12_ Describe a formula that is true in precisely those domains that contain at least _m_ elements. (We say it _characterises_ those domains.) Describe a formula that characterises the domains containing at most _m_ elements.

_Exercise 13_ Let ≈ be a 2-place predicate symbol, which we write using infix notation as _x_ ≈ _y_ instead of ≈ _(x, y)_ . Consider the axioms

Let the universe be the set of natural numbers, _N_ = {0 _,_ 1 _,_ 2 _, . . ._ }. Which axioms hold if _I_ [≈] is

- the empty relation, ∅?

- the universal relation, { _(x, y)_ | _x, y_ ∈ _N_ }?

- the equality relation, { _(x, x)_ | _x_ ∈ _N_ }?

- the relation { _(x, y)_ | _x, y_ ∈ _N_ ∧ _x_ + _y_ is even}?

- the relation { _(x, y)_ | _x, y_ ∈ _N_ ∧ _x_ + _y_ = 100}?

- the relation { _(x, y)_ | _x, y_ ∈ _N_ ∧ _x_ ≡ _y (_ mod 16 _)_ }?

_Exercise 14_ Taking = and _R_ as 2-place relation symbols, consider the following axioms:

Exhibit two interpretations that satisfy axioms 1–3 and falsify axioms 4 and 5. Exhibit two interpretations that satisfy axioms 1–4 and falsify axiom 5. Exhibit two interpretations that satisfy axioms 1–5. Consider only interpretations that make = denote the equality relation. (This exercise asks whether you can make the connection between the axioms and typical mathematical objects satisfying them.)

<!-- page 32 -->
29

## 6 Formal Reasoning in First-Order Logic

This section reviews some syntactic notations: free variables versus bound variables and substitution. It lists some of the main equivalences for quantifiers. Finally it describes and illustrates the quantifier rules of the sequent calculus.

### 6.1 Free vs bound variables

The notion of bound variable occurs widely in mathematics: consider the role of _x_ in � _f (x)dx_ and the role of _k_ in lim∞ _k_ =0_ak_.Similarconceptsoccurinthe _λ_ -calculus. In first-order logic, variables are bound by quantifiers (rather than by _λ_ ).

Definition 9 An occurrence of a variable _x_ in a formula is _bound_ if it is contained within a subformula of the form ∀ _x A_ or ∃ _x A_ .

An occurrence of the form ∀ _x_ or ∃ _x_ is called the _binding occurrence_ of _x_ .

- An occurrence of a variable is _free_ if it is not bound.

- A _closed_ formula is one that contains no free variables.

A _ground_ term, formula or clause is one that contains no variables at all.

In ∀ _x_ ∃ _y R(x, y, z)_ , the variables _x_ and _y_ are bound while _z_ is free.

In _(_ ∃ _x P(x))_ ∧ _Q(x)_ , the occurrence of _x_ just after _P_ is bound, while that just after _Q_ is free. Thus _x_ has both free and bound occurrences. Such situations can be avoided by renaming bound variables. Renaming can also ensure that all bound variables in a formula are distinct.

Example 8 Renaming bound variables in a formula preserves its meaning, provided no name clashes are introduced. Consider the following renamings of ∀ _x_ ∃ _y R(x, y, z)_ :

∀ _u_ ∃ _y R(u, y, z)_ OK ∀ _x_ ∃ _w R(x, w, z)_ OK ∀ _u_ ∃ _y R(x, y, z)_ not done consistently ∀ _y_ ∃ _y R(y, y, z)_ clash with bound variable _y_ ∀ _z_ ∃ _y R(z, y, z)_ clash with free variable _z_

### 6.2 Substitution

If _A_ is a formula, _t_ is a term, and _x_ is a variable, then _A_ [ _t/x_ ] is the formula obtained by substituting _t_ for _x_ throughout _A_ . The substitution only affects the _free_ occurrences of _x_ . Pronounce _A_ [ _t/x_ ] as ‘ _A_ with _t_ for _x_ .’ We also use _u_ [ _t/x_ ] for substitution in a term _u_ and _C_ [ _t/x_ ] for substitution in a clause _C_ .

<!-- page 33 -->
30

#### 6 FORMAL REASONING IN FIRST-ORDER LOGIC

Substitution is only sensible provided all bound variables in _A_ are distinct from all variables in _t_ . This can be achieved by renaming the bound variables in _A_ . For example, if ∀ _x A_ then _A_ [ _t/x_ ] is true for all _t_ ; the formula holds when we drop the ∀ _x_ and replace _x_ by any term. But ∀ _x_ ∃ _y x_ = _y_ is true in all models, while ∃ _y y_ + 1 = _y_ is not. We may not replace _x_ by _y_ + 1, since the free occurrence of _y_ in _y_ + 1 gets captured by the ∃ _y_ . First we must rename the bound _y_ , getting say ∀ _x_ ∃ _z x_ = _z_ ; now we may replace _x_ by _y_ + 1, getting ∃ _z y_ + 1 = _z_ . This formula is true in all models, regardless of the meaning of the symbols + and 1.

### 6.3 Equivalences involving quantifiers

These equivalences are useful for transforming and simplifying quantified formulæ. Later, we shall use them to convert formulæ into _prenex normal form_ , where all quantifiers are at the front.

_pulling quantifiers through negation (infinitary de Morgan laws)_

_pulling quantifiers through conjunction and disjunction_

_(provided x is not free in B)_

_distributive laws_

_implication: A_ → _B as_ ¬ _A_ ∨ _B (provided x is not free in B)_

_expansion:_ ∀ _and_ ∃ _as infinitary conjunction and disjunction_

<!-- page 34 -->
6.3 Equivalences involving quantifiers

31

With the help of the associative and commutative laws for ∧ and ∨, a quantifier can be pulled out of any conjunct or disjunct.

The distributive laws differ from pulling: they replace two quantifiers by one. (Note that the quantified variables will probably have different names, so one of them will have be renamed.) Depending upon the situation, using distributive laws can be either better or worse than pulling. There are no distributive laws for ∀ over ∨ and ∃ over ∧. If in doubt, do not use distributive laws!

Two substitution laws do not involve quantifiers explicitly, but let us use _x_ = _t_ to replace _x_ by _t_ in a restricted context:

Many first-order formulæ have easy proofs using equivalences:

The following formula is quite hard to prove using the sequent calculus, but using equivalences it is simple:

If you are asked to prove a formula, but no particular formal system (such as the sequent calculus) has been specified, then you may use any convincing argument. Using equivalences as above can shorten the proof considerably. Also, take advantage of symmetries; in proving _A_ ∧ _B_ ≃ _B_ ∧ _A_ , it obviously suffices to prove _A_ ∧ _B_ |= _B_ ∧ _A_ .

_Exercise 15_ Verify these equivalences by appealing to the truth definition for first-order logic:

<!-- page 35 -->
32

#### 6 FORMAL REASONING IN FIRST-ORDER LOGIC

_Exercise 16_ Explain why the following are not equivalences. Are they implications? In which direction?

### 6.4 Sequent rules for the universal quantifier

Here are the sequent rules for ∀:

Rule _(_ ∀ _r )_ holds _provided x_ is not free in the conclusion! This restriction ensures that _x_ is really arbitrary; if _x_ is free in _�_ or _�_ then the sequent is assuming properties of _x_ . To understand the proviso, contrast the proof of the theorem ∀ _x_ [ _P(x)_ → _P(x)_ ] with an attempted proof of the invalid formula _P(x)_ →∀ _x P(x)_ . Since _X_ is a bound variable, you may rename it to get around the restriction, and obviously _P(x)_ →∀ _y P(y)_ will have no proof.

Rule _(_ ∀ _l)_ lets us create many instances of ∀ _x A_ . The exercises below include some examples that require more than one copy of the quantified formula. Since we regard sequents as consisting of sets, we may regard them as containing unlimited quantities of each of their elements. But except for the two rules _(_ ∀ _l)_ and _(_ ∃ _r )_ (see below), we only need one copy of each formula.

Example 9 In this elementary proof, rule _(_ ∀ _l)_ is applied to instantiate the bound variable _x_ with the term _f (y)_ . The application of _(_ ∀ _r )_ is permitted because _y_ is not free in the conclusion (which, in fact, is closed).

Example 10 This proof concerns part of the law for pulling universal quantifiers out of conjunctions. Rule _(_ ∀ _l)_ just discards the quantifier, since it instantiates the bound variable _x_ with the free variable _x_ .

<!-- page 36 -->
6.5 Sequent rules for the existential quantifier

33

Example 11 The sequent ∀ _x (A_ → _B)_ ⇒ _A_ →∀ _x B_ is valid provided _x_ is not free in _A_ . That condition is required for the application of _(_ ∀ _r )_ below:

What if the condition fails to hold? Let _A_ and _B_ both be the formula _x_ = 0. Then ∀ _x (x_ = 0 → _x_ = 0 _)_ is valid, but _x_ = 0 →∀ _x (x_ = 0 _)_ is not valid (it fails under any valuation that sets _x_ to 0).

_Exercise 17_ Prove ¬∀ _y_ [ _(Q(a)_ ∨ _Q(b))_ ∧¬ _Q(y)_ ] using equivalences, and then formally using the sequent calculus.

_Exercise 18_ Prove the following using the sequent calculus:

### 6.5 Sequent rules for the existential quantifier

Here are the sequent rules for ∃:

Rule _(_ ∃ _l)_ holds _provided x_ is not free in the conclusion! These rules are strictly dual to the ∀-rules; any example involving ∀ can easily be transformed into one involving ∃ and having a proof of precisely the same form. For example, the sequent ∀ _x P(x)_ ⇒∀ _y P( f (y))_ can be transformed into ∃ _y P( f (y))_ ⇒∃ _x P(x)_ .

Example 12 Here is half of the ∃ distributive law. Rule _(_ ∃ _r )_ just discards the quantifier, instantiating the bound variable _x_ with the free variable _x_ . In the general case, it can instantiate the bound variable with any term.

<!-- page 37 -->
#### 34

#### 7 CLAUSE METHODS FOR PROPOSITIONAL LOGIC

Example 13 The sequent ∃ _x A_ ∧∃ _x B_ ⇒∃ _x (A_ ∧ _B)_ is not valid, because the value of _x_ that makes _A_ true could differ from the value of _x_ that makes _B_ true. This comes out clearly in the proof attempt, where we are not allows to apply _(_ ∃ _l)_ twice with the same variable name, _x_ . As soon as we are forced to rename the second variable to _y_ , it becomes obvious that the two values could differ. Turning to the right side of the sequent, no application of _(_ ∃ _r )_ can lead to a proof. We have nothing to instantiate _x_ with:

_Exercise 19_ Prove the following using the sequent calculus:

## 7 Clause Methods for Propositional Logic

This section discusses two proof methods in the context of propositional logic: the Davis-Putnam procedure and resolution.

The Davis-Putnam procedure dates from 1960, and its application to firstorder logic has been regarded as obsolete for decades. However, propositional logic has grown in importance, and Davis-Putnam has been rediscovered as an efficient decision procedure. It has been applied to solve some open questions in combinatorial mathematics, such as the existence of certain Latin squares. Its main rival is OBDDs, which have been applied mainly to hardware design.

Resolution is a powerful proof method for first-order logic. We first consider _ground_ resolution, which works for propositional logic. Though of little practical use, ground resolution introduces some of the main concepts. The resolution method is not natural for hand proofs, but it is easy to automate: it has only one inference rule and no axioms.

Both methods require the original formula to be negated, then converted into CNF. Recall that CNF is a conjunction of disjunction of literals. A disjunction of literals is called a _clause_ , and written as a set of literals. Converting the negated formula to CNF yields a set of such clauses. Both methods seek a contradiction in

<!-- page 38 -->
7.1 Clausal notation 35

the set of clauses; if the clauses are unsatisfiable, then so is the negated formula, and therefore the original formula is valid.

To _refute_ a set of clauses is to prove that they are inconsistent. The proof is called a _refutation_ .

### 7.1 Clausal notation

Definition 10 A _clause_ is a disjunction of literals

written as a set

Since ∨ is commutative, associative, and idempotent, the order of literals in a clause does not matter. The above clause is logically equivalent to the implication

Kowalski notation abbreviates this to

and when _n_ = 1 we have the familiar Prolog clauses, also known as _definite clauses_ .

### 7.2 The Davis-Putnam Method

The Davis-Putnam method is based upon some obvious identities:

Here is an outline of the algorithm:

1. Delete tautological clauses: { _P,_ ¬ _P, . . ._ }

2. For each unit clause { _L_ },

   - delete all clauses containing _L_

<!-- page 39 -->
36 7 CLAUSE METHODS FOR PROPOSITIONAL LOGIC

   - delete ¬ _L_ from all clauses

3. Delete all clauses containing _pure literals_ . A literal _L_ is _pure_ if there is no clause containing ¬ _L_ .

4. If the empty clause is generated, then we have a refutation. Conversely, if all clauses are deleted, then the original clause set is satisfiable.

5. Perform a _case split_ on some literal _L_ , and recursively apply the algorithm to the _L_ and ¬ _L_ subcases. The clause set is satisfiable if and only if one of the subcases is satisfiable.

This is a decision procedure. It must terminate because each case split eliminates a propositional symbol. Zhang and Stickel (1994) have proposed some efficient algorithms for the Davis-Putnam procedure.

Tautological clauses are deleted because they are always true, and thus cannot participate in a contradiction. A pure literal can always be assumed to be true; deleting the clauses containing it can be regarded as a degenerate case split, in which there is only one case.

Example 14 The Davis-Putnam method can show that a formula is not a theorem. Consider the formula _P_ ∨ _Q_ → _Q_ ∨ _R_ . After negating this and converting to CNF, we obtain the three clauses { _P, Q_ }, {¬ _Q_ } and {¬ _R_ }. The Davis-Putnam method terminates rapidly:

The clauses are satisfiable by _P_ �→ t _, Q_ �→ f _, R_ �→ f . This interpretation falsifies _P_ ∨ _Q_ → _Q_ ∨ _R_ .

Example 15 Here is an example of a case split. Consider the clause set {¬ _Q, R_ } {¬ _R, P_ } {¬ _R, Q_ } {¬ _P, Q, R_ } { _P, Q_ } {¬ _P,_ ¬ _Q_ } _._

There are no unit clauses or pure literals, so we arbitrarily select _P_ for case splitting:

<!-- page 40 -->
7.3 Introduction to resolution

37

_Exercise 20_ Apply the Davis-Putnam procedure to the clause set

### 7.3 Introduction to resolution

Resolution is essentially the following rule of inference:

To convince yourself that this rule is sound, note that _B_ must be either false or true.

- if _B_ is false, then _B_ ∨ _A_ is equivalent to _A_ , so we get _A_ ∨ _C_

- if _B_ is true, then ¬ _B_ ∨ _C_ is equivalent to _C_ , so we get _A_ ∨ _C_

You might also understand this rule via transitivity of → (with _D_ = ¬ _A_ ):

A special case of resolution is when _A_ and _C_ are empty:

This detects contradictions.

Resolution works with disjunctions. The aim is to prove a contradiction, refuting a formula. Here is the method for proving a formula _A_ :

1. Translate ¬ _A_ into CNF as _A_ 1 ∧· · · ∧ _Am_ .

2. Break this into a set of clauses: _A_ 1, _. . ._ , _Am_ .

3. Repeatedly apply the resolution rule to the clauses, producing new clauses. These are all consequences of ¬ _A_ .

4. If a contradiction is reached, we have refuted ¬ _A_ .

In set notation the resolution rule is

Resolution takes two clauses and creates a new one. A collection of clauses is maintained; the two clauses are chosen from the collection according to some

<!-- page 41 -->
#### 38

#### 7 CLAUSE METHODS FOR PROPOSITIONAL LOGIC

strategy, and the new clause is added to it. If _m_ = 0 or _n_ = 0 then the new clause will be smaller than one of the parent clauses; if _m_ = _n_ = 0 then the new clause will be empty. A clause is true (in some interpretation) just when one of the literals is true; thus the empty clause indicates contradiction. It is written □. If the empty clause is generated, resolution terminates successfully.

### 7.4 Examples of ground resolution

Let us try to prove

Convert its negation to CNF:

We can combine steps 1 (eliminate →) and 2 (push negations in) using the law ¬ _(A_ → _B)_ ≃ _A_ ∧¬ _B_ :

Step 3, push disjunctions in, has nothing to do. The clauses are

We resolve { _P_ } and {¬ _Q,_ ¬ _P_ } as follows:

The resolvent is {¬ _Q_ }. Resolving { _Q_ } and with this new clause gives

The resolvent is the empty clause, properly written as □. We have proved _P_ ∧ _Q_ → _Q_ ∧ _P_ by assuming its negation and deriving a contradiction. It is nicer to draw a tree like this:

<!-- page 42 -->
7.5 A proof using a set of assumptions

39

Another example is _(P_ ↔ _Q)_ ↔ _(Q_ ↔ _P)_ . The steps of the conversion to clauses is left as an exercise; remember to negate the formula first! The final clauses are

A tree for the resolution proof is

Note that the tree contains { _Q_ } and {¬ _Q_ } rather than { _Q, Q_ } and {¬ _Q,_ ¬ _Q_ }. If we forget to suppress repeated literals, we can get stuck. Resolving { _Q, Q_ } and {¬ _Q,_ ¬ _Q_ } (keeping repetitions) gives { _Q,_ ¬ _Q_ }, a tautology. Tautologies are useless. Resolving this one with the other clauses leads nowhere. Try it.

These examples could mislead. Must a proof use each clause exactly once? No! A clause may be used repeatedly, and many problems contain redundant clauses. Here is an example:

Redundant clauses can make the theorem-prover flounder; this is a challenge facing the field.

_Exercise 21_ Prove _(A_ → _B_ ∨ _C)_ → [ _(A_ → _B)_ ∨ _(A_ → _C)_ ] using resolution.

### 7.5 A proof using a set of assumptions

In this example we assume

and prove _H_ → _P_ . It turns out that we can generate clauses separately from the assumptions (taken _positively_ ) and the conclusion ( _negated_ ).

<!-- page 43 -->
40

#### 7 CLAUSE METHODS FOR PROPOSITIONAL LOGIC

If we call the assumptions _A_ 1, _. . ._ , _Ak_ and the conclusion _B_ , then the desired theorem is

Try negating this and converting to CNF. Using the law ¬ _(A_ → _B)_ ≃ _A_ ∧¬ _B_ , the negation converts in one step to

Since the entire formula is a conjunction, we can separately convert _A_ 1, _. . ._ , _Ak_ , and ¬ _B_ to clause form and pool the clauses together.

Assumption _H_ → _M_ ∨ _N_ is essentially in clause form already:

Assumption _M_ → _K_ ∧ _P_ becomes two clauses:

Assumption _N_ → _L_ ∧ _P_ also becomes two clauses:

The negated conclusion, ¬ _(H_ → _P)_ , becomes two clauses:

A tree for the resolution proof is

<!-- Start of picture text -->
{ H } {¬ H, M, N } { M, N } {¬ M, P } { N , P } ⌢⋐⊣⌋ � {¬ N , P } { P } {¬ P } □ <!-- End of picture text -->

The clauses were not tried at random. Here are some points of proof strategy.

Ignoring irrelevance. Clauses {¬ _M, K_ } and {¬ _N , L_ } lead nowhere, so they were not tried. Resolving with one of these would make a clause containing _K_ or _L_ . There is no way of getting rid of either literal, for no clause contains ¬ _K_ or ¬ _L_ . So this is not a way to obtain the empty clause.

<!-- page 44 -->
7.6 Deletion of redundant clauses

41

Working from the goal. In each resolution step, at least one clause involves the negated conclusion (possibly via earlier resolution steps). We do not blindly derive facts from the assumptions — for, provided the assumptions are consistent, any contradiction will have to involve the negated conclusion. This strategy is called _set of support_ .

Linear resolution. The proof has a linear structure: each resolvent becomes the parent clause for the next resolution step. Furthermore, the other parent clause is always one of the original set of clauses. This simple structure is very efficient because only the last resolvent needs to be saved. It is similar to the execution strategy of Prolog.

_Exercise 22_ Explain in more detail the conversion of this example into clauses.

_Exercise 23_ Prove Peirce’s law, _((P_ → _Q)_ → _P)_ → _P_ , using resolution.

_Exercise 24_ Prove _(Q_ → _R)_ ∧ _(R_ → _P_ ∧ _Q)_ ∧ _(P_ → _Q_ ∨ _R)_ → _(P_ ↔ _Q)_ using resolution.

### 7.6 Deletion of redundant clauses

During resolution, the number of clauses builds up dramatically; it is important to delete all redundant clauses.

Each new clause is a consequence of the existing clauses. A contradiction can only be derived if the original set of clauses is inconsistent. A clause can be deleted if it does not affect the consistency of the set. Any tautology should be deleted, since it is true in all interpretations.

Here is a subtler case. Consider the clauses

Resolving the first two yields { _P, R_ }. Since each clause is a disjunction, any interpretation that satisfies { _P, R_ } also satisfies { _P, Q, R_ }. Thus { _P, Q, R_ } cannot cause inconsistency, and should be deleted.

Put another way, _P_ ∨ _R_ implies _P_ ∨ _Q_ ∨ _R_ . Anything that could be derived from _P_ ∨ _Q_ ∨ _R_ could also be derived from _P_ ∨ _R_ . This sort of deletion is called _subsumption_ ; clause { _P, R_ } _subsumes_ { _P, Q, R_ }.

_Exercise 25_ Prove _(P_ ∧ _Q_ → _R)_ ∧ _(P_ ∨ _Q_ ∨ _R)_ → _((P_ ↔ _Q)_ → _R)_ by resolution. Show the steps of converting the formula into clauses.

<!-- page 45 -->
#### 42 8 SKOLEM FUNCTIONS AND HERBRAND’S THEOREM

_Exercise 26_ Using linear resolution, prove that _(P_ ∧ _Q)_ → _(R_ ∧ _S)_ follows from _P_ → _R_ and _R_ ∧ _P_ → _S_ .

_Exercise 27_ Convert these axioms to clauses, showing all steps. Then prove _Winterstorm_ → _Miserable_ by resolution:

_Rain_ ∧ _(Windy_ ∨¬ _Umbrella)_ → _Wet Winterstorm_ → _Storm_ ∧ _Cold Wet_ ∧ _Cold_ → _Miserable Storm_ → _Rain_ ∧ _Windy_

## 8 Skolem Functions and Herbrand’s Theorem

Propositional logic is the basis of many proof methods for first-order logic. Eliminating the quantifiers from a first-order formula reduces it nearly to propositional logic. This section describes how to do so.

### 8.1 Prenex normal form

The simplest method of eliminating quantifiers from formula involves first moving them to the front.

Definition 11 A formula is in _prenex normal form_ if and only if it has the form

where _A_ is quantifier-free, each _Qi_ is either ∀ or ∃, and _n_ ≥ 0. The string of quantifiers is called the _prefix_ and _A_ is called the _matrix_ .

Using the equivalences described above, any formula can be put into prenex normal form.

#### Examples of translation.

The affected subformulæ will be underlined.

#### Example 16 Start with

Pull out the ∃ _x_ :

<!-- page 46 -->
8.2 Removing quantifiers: Skolem form

43

Pull out the ∃ _y_ :

Pull out the ∃ _y_ again:

Pull out the ∀ _z_ :

Pull out the ∀ _z_ again:

Pull out the ∀ _x_ :

Example 17 Start with

Remove the implication:

Pull out the ∀ _x_ :

Distribute ∃ over ∨, renaming _y_ to _x_ :6

Finally, pull out the ∀ _z_ :

### 8.2 Removing quantifiers: Skolem form

Now that the quantifiers are at the front, let’s eliminate them! We replace every existentially bound variable by a Skolem constant or function. This transformation does not preserve the meaning of a formula; it does preserve _inconsistency_ , which is the critical property, since resolution works by detecting contradictions.

> 6Or simply pull out the quantifiers separately. Using the distributive law is marginally better here because it will result in only one Skolem constant instead of two; see the following section.

<!-- page 47 -->
44

8 SKOLEM FUNCTIONS AND HERBRAND’S THEOREM

#### How to Skolemize a formula

Suppose the formula is in prenex normal form.7 Starting from the left, if the formula contains an existential quantifier, then it must have the form

where _A_ is a prenex formula, _k_ ≥ 0, and ∃ _y_ is the leftmost existential quantifier. Choose a _k_ -place function symbol not present in _A_ (that is, a _new_ function symbol). Delete the ∃ _y_ and replace all other occurrences of _y_ by _f (x_ 1 _, x_ 2 _, . . . , xk)_ . The result is another prenex formula:

If _k_ = 0 above then the prenex formula is simply ∃ _y A_ , and other occurrences of _y_ are replaced by a new constant symbol _c_ . The resulting formula is _A_ [ _c/y_ ].

The remaining existential quantifiers, if any, are in _A_ . Repeatedly eliminate all of them, as above. The new symbols are called _Skolem functions_ (or Skolem constants).

After Skolemization the formula is just ∀ _x_ 1 ∀ _x_ 2 · · · ∀ _xk A_ where _A_ is quantifier-free. Since the free variables in a formula are taken to be universally quantified, we can drop these quantifiers, leaving simply _A_ . We are almost back to the propositional case, except the formula typically contains terms. We shall have to handle constants, function symbols, and variables.

#### Examples of Skolemization

The affected expressions are underlined.

Example 18 Start with

Eliminate the ∃ _x_ using the Skolem constant _a_ :

Eliminate the ∃ _z_ using the 1-place Skolem function _f_ :

Finally, drop the ∀ _y_ and convert the remaining formula to a clause:

> 7This makes things easier to follow. However, some proof methods merely require the formula to be in negation normal form. The basic idea is the same: remove the outermost existential quantifier, replacing its bound variable by a Skolem term. Pushing quantifiers in as far as possible, instead of pulling them out, yields a better set of clauses.

<!-- page 48 -->
45

8.2 Removing quantifiers: Skolem form

Example 19 Start with

<u>∃</u> _<u>u</u>_ <u>∀</u> _v_ ∃ _w_ ∃ _x_ ∀ _y_ ∃ _z ((P(h(u, v))_ ∨ _Q(w))_ ∧ _R(x, h(y, z)))_

Eliminate the ∃ _u_ using the Skolem constant _c_ :

∀ _v_ <u>∃</u> _<u>w</u>_ ∃ _x_ ∀ _y_ ∃ _z ((P(h(c, v))_ ∨ _Q(w))_ ∧ _R(x, h(y, z)))_

Eliminate the ∃ _w_ using the 1-place Skolem function _f_ :

Eliminate the ∃ _x_ using the 1-place Skolem function _g_ :

∀ _v_ ∀ _y_ <u>∃</u> _<u>z ((P(h(c, v))</u>_ ∨ _Q( f (v)))_ ∧ _R(g(v), h(y, z)))_

Eliminate the ∃ _z_ using the 2-place Skolem function _j_ (note that function _h_ is already used!):

Finally drop the universal quantifiers, getting a set of clauses:

#### Correctness of Skolemization

Skolemization does _not_ preserve meaning. The version presented above does not even preserve validity! For example,

is valid. (Why? In any model, the required value of _x_ exists — it is just the value of _a_ in that model.)

Replacing the ∃ _x_ by the Skolem constant _b_ gives

This has a different meaning since it refers to a constant _b_ not previously mentioned. And it is not valid! For example, it is false in the interpretation where _P(x)_ means ‘ _x_ equals 0’ and _a_ denotes 0 and _b_ denotes 1.

Our version of Skolemization does preserve _consistency_ — and therefore inconsistency. Consider one Skolemization step.

<!-- page 49 -->
#### 46 8 SKOLEM FUNCTIONS AND HERBRAND’S THEOREM

- The formula ∀ _x_ ∃ _y A_ is consistent iff it holds in some interpretation _I_ = _(D, I )_

- iff for all _x_ ∈ _D_ there is some _y_ ∈ _D_ such that _A_ holds

- iff there is some function on _D_ , say _f_ˆ ∈ _D_ → _D_ , such that for all _x_ ∈ _D_ , if _y_ = _f_ˆ _(x)_ then _A_ holds

- iff there is an interpretation _I_′ extending _I_ so that the symbol _f_ denotes the function _f_ˆ , and _A_ [ _f (x)/y_ ] holds for all _x_ ∈ _D_ .

- iff the formula ∀ _x A_ [ _f (x)/y_ ] is consistent.

Note that _I_ above does not interpret _f_ because Skolem functions have to be new. Thus _I_ may be extended to _I_′ by giving an interpretation for _f_ .

This argument easily generalizes to the case ∀ _x_ 1 ∀ _x_ 2 · · · ∀ _xk_ ∃ _y A_ . Thus, if a formula is consistent then so is the Skolemized version. If it is inconsistent then so is the Skolemized version. That is what we need: resolution works by proving that a formula is inconsistent.

There is a dual version of Skolemization that preserves validity rather than consistency. It replaces universal quantifiers, rather than existential ones, by Skolem functions.

_Exercise 28_ Describe this dual version of Skolemization and demonstrate that it preserves validity. What might it be used for?

### 8.3 Herbrand interpretations

A Herbrand interpretation basically consists of all terms that can be written using just the constant and function symbols in a set of clauses _S_ (or quantifier-free formula). Why define Herbrand interpretations? A mathematical reason: for consistency of _S_ we need only consider Herbrand interpretations. A programming reason: the data processed by a Prolog program _S_ is simply its Herbrand universe.

To define the Herbrand universe for the set of clauses _S_ we start with sets of the constant and function symbols in _S_ , _including Skolem functions_ .

Definition 12 Let _C_ be the set of all constants in _S_ . If there are none, let _C_ = { _a_ } for some constant symbol _a_ of the first-order language.8 For _n >_ 0 let _Fn_ be the set of all _n_ -place function symbols in _S_ and let _Pn_ be the set of all _n_ -place predicate symbols in _S_ .

8This step ensures that the resulting domain will be non-empty.

<!-- page 50 -->
8.3 Herbrand interpretations

47

The _Herbrand universe_ is the set _H_ =� _i_ ≥0_Hi_, where

By this construction, _H_ turns out to satisfy the recursive equation

The _Herbrand base_ (or atom set) consists of all possible applications of predicate symbols in _S_ to terms of the Herbrand universe for _S_ :

Note that the elements of _H_ are ground terms — this is a syntactic interpretation. An interpretation _(H, I )_ is a _Herbrand interpretation_ provided _I_ [ _t_ ] = _t_ for all ground terms _t_ . The interpretation of the predicates is given by a subset of the Herbrand base; this specifies which predicate applications are true.

Example 20 Suppose we have the set (consisting of two clauses)

Then

_H_ = { _a, f (a), g(a, a), f ( f (a)), g( f (a), a), g(a, f (a)), g( f (a), f (a)), . . ._ } _H B_ = { _P(a), Q(a), P( f (a)), Q( f (a)), P(g(a, a)), Q(g(a, a)),_

_P( f ( f (a))), Q( f ( f (a))), P(g( f (a), a)), Q(g( f (a), a)),_

_P(g(a, f (a))), Q(g(a, f (a))), P(g( f (a), f (a))), Q(g( f (a), f (a))), . . ._ }

Every interpretation _I_ over an arbitrary universe can be mimicked by some Herbrand interpretation: just take

This is a subset of _H B_ . Each subset of _H B_ specifies a Herbrand interpretation by listing the values (in _H_ ) for which each predicate holds. To mimic the interpretation _I_ we take exactly the set of ground atomic formulæ that hold in _I_ ; this is a Herbrand interpretation.

Thus, we have informally proved the following two results (Chang and Lee, page 55):

<!-- page 51 -->
#### 48 8 SKOLEM FUNCTIONS AND HERBRAND’S THEOREM

Lemma 13 _Let S be a set of clauses. If an interpretation satisfies S, then an_ Herbrand _interpretation satisfies S._

Theorem 14 _A set S of clauses is unsatisfiable if and only no Herbrand interpretation satisfies S._

Equality may behave strangely in Herbrand interpretations. Given an interpretation _I_ , the denotation of = is the set of all pairs of ground terms _(t_ 1 _, t_ 2 _)_ such that _t_ 1 = _t_ 2 according to _I_ . In a context of the natural numbers, the denotation of = could include pairs like _(_ 1 + 1 _,_ 2 _)_ — the two components need not be identical, contrary to the normal situation with equality.

### 8.4 The Skolem-G¨odel-Herbrand Theorem

Finally we have the Skolem-G¨odel-Herbrand Theorem. A version of the Completeness Theorem, it tells us that unsatisfiability can always be detected by a _finite_ process. It does not tell us how to detect satisfiability, for there is no general method.9

Definition 15 An _instance_ of a clause _C_ is a clause that results by replacing variables in _C_ by terms. A _ground instance_ of a clause _C_ is an instance of _C_ that contains no variables. (It can be obtained by replacing all variables in _C_ by elements of a Herbrand universe, which are ground terms.)

Since the variables in a clause are taken to be universally quantified, every instance of _C_ is a logical consequence of _C_ .

Example 21 This clause is valid in the obvious integer model:

Replacing _x_ by _y_ + _y_ in _C_ results in the instance

Replacing _y_ by 2 in _C_′ results in the ground instance

> 9It is often confused with Herbrand’s Theorem, a stronger result.

<!-- page 52 -->
49

Example 22 Consider the clause

Replacing _x_ by _f (z)_ in _C_ results in the instance

Replacing _y_ by _j (a)_ and _z_ by _b_ in _C_′ results in the instance

Assuming that _a_ and _b_ are constants, _C_′′ is a ground instance of _C_ .

Theorem 16 _A set S of clauses is unsatisfiable if and only if there is a finite unsatisfiable set S_′ _of ground instances of clauses of S._

The proof is rather involved; see Chang and Lee, pages 56–61, for details. The _(_ �⇒ _)_ direction is the interesting one. It uses a non-constructive argument to show that if there is no finite unsatisfiable set _S_′ , then there must be a model of _S_ .

The _(_ ⇐� _)_ direction simply says that if _S_′ is unsatisfiable then so is _S_ . This is straightforward since every clause in _S_′ is a logical consequence of some clause in _S_ . Thus if _S_′ is inconsistent, the inconsistency is already present in _S_ .

Question: how do we discover _which_ ground instances? Answer: by _unification_ .

_Exercise 29_ Consider a first-order language with 0 and 1 as constant symbols, with − as a 1-place function symbol and + as a 2-place function symbol, and with _<_ as a 2-place predicate symbol.

- (a) Describe the Herbrand Universe for this language.

- (b) The language can be interpreted by taking the integers for the universe and giving 0 1, −, +, and _<_ their usual meanings over the integers. What do those symbols denote in the corresponding Herbrand model?

## 9 Unification

Unification is the operation of finding a common instance of two terms. Though the concept is simple, it involves a complicated theory. Proving the unification algorithm’s correctness (especially termination) is difficult.

To introduce the idea of unification, consider a few examples. The terms _f (x, b)_ and _f (a, y)_ have the common instance _f (a, b)_ , replacing _x_ by _a_ and _y_

<!-- page 53 -->
9 UNIFICATION

#### 50

by _b_ . The terms _f (x, x)_ and _f (a, b)_ have no common instance, assuming that _a_ and _b_ are distinct constants. The terms _f (x, x)_ and _f (y, g(y))_ have no common instance, since there is no way that _x_ can have the form _y_ and _g(y)_ at the same time — unless we admit the infinite term _g(g(g(_ · · · _)))_ .

Only variables may be replaced by other terms. Constants are not affected (they remain constant!). If a term has the form _f (t, u)_ then instances of that term must have the form _f (t_′ _, u_′ _)_ , where _t_′ is an instance of _t_ and _u_′ is an instance of _u_ .

### 9.1 Substitutions

We have already seen substitutions informally. It is now time for a more detailed treatment.

Definition 17 A _substitution_ is a finite set of replacements

where _x_ 1, _. . ._ , _xk_ are distinct variables such that _ti_ ̸ = _xi_ for all _i_ = 1 _, . . . , k_ . We use Greek letters _φ_ , _θ_ , _σ_ to stand for substitutions.

The finite set { _x_ 1 _, . . . , xk_ } is called the _domain_ of the substitution. The domain of a substitution _θ_ is written dom _(θ)_ .

A substitution _θ_ = [ _t_ 1 _/x_ 1 _, . . . , tk/xk_ ] defines a function from the variables { _x_ 1 _, . . . , xk_ } to terms. Postfix notation is usual for applying a substitution; thus, for example, _xi θ_ = _ti_ . Substitutions may be applied to terms, not just to variables. Substitution on terms is defined recursively as follows:

Here _f_ is an _n_ -place function symbol. The operation substitutes in the arguments of functions, and leaves unchanged any variables outside of the domain of _θ_ .

Substitution may be extended to literals and clauses as follows:

Here _P_ is an _n_ -place predicate symbol (or its negation), while _L_ 1 _, . . . , L m_ are the literals in a clause.

<!-- page 54 -->
51

9.2 Composition of substitutions

Example 23 The substitution _θ_ = [ _h(y)/x, b/y_ ] says to replace _x_ by _h(y)_ and _y_ by _b_ . The replacements occur simultaneously; it does _not_ have the effect of replacing _x_ by _h(b)_ . Its domain is dom _(θ)_ = { _x, y_ }. Applying this substitution gives

### 9.2 Composition of substitutions

If _φ_ and _θ_ are substitutions then so is their _composition φ_ ◦ _θ_ , which satisfies

Can we write _φ_ ◦ _θ_ as a set of replacements? It has to satisfy the above for all relevant variables:

Thus it must be the set consisting of the replacements

_Equality_ of substitutions _φ_ and _θ_ is defined as follows: _φ_ = _θ_ if _xφ_ = _xθ_ for all variables _x_ . Under these definitions composition enjoys an associative law. It also has an identity element, namely [], the empty substitution.

Example 24 Let _φ_ = [ _j (x)/u,_ 0 _/y_ ] and _θ_ = [ _h(z)/x, g(_ 3 _)/y_ ]. Then dom _(φ)_ = { _u, y_ } and dom _(θ)_ = { _x, y_ }, so dom _(φ)_ ∪ dom _(θ)_ = { _u, x, y_ }. Thus

Notice that _y(φ_ ◦ _θ)_ = _(yφ)θ_ = 0 _θ_ = 0; the replacement _g(_ 3 _)/y_ has disappeared.

_Exercise 30_ Verify that ◦ is associative and has [] for an identity.

<!-- page 55 -->
52

9 UNIFICATION

### 9.3 Unifiers

Definition 18 A substitution _θ_ is a _unifier_ of terms _t_ 1 and _t_ 2 if _t_ 1 _θ_ = _t_ 2 _θ_ . More generally, _θ_ is a unifier of terms _t_ 1, _t_ 2, _. . ._ , _tm_ if _t_ 1 _θ_ = _t_ 2 _θ_ = · · · = _tmθ_ . The term _t_ 1 _θ_ is called the _common instance_ of the unified terms. A unifier of two or more literals is defined similarly.

Two terms can only be unified if they have similar structure apart from variables. The terms _f (x)_ and _h(y, z)_ are clearly non-unifiable since no substitution can do anything about the differing function symbols. It is easy to see that _θ_ unifies _f (t_ 1 _, . . . , tn)_ and _f (u_ 1 _, . . . , un)_ if and only if _θ_ unifies _ti_ and _ui_ for all _i_ = 1 _, . . . , n_ .

Example 25 The substitution [3 _/x, g(_ 3 _)/y_ ] unifies the terms _g(g(x))_ and _g(y)_ . The common instance is _g(g(_ 3 _))_ . These terms have many other unifiers, including the following:

|unifying substitution|common instance|
|---|---|
|[_f (u)/x, g( f (u))/y_]|_g(g( f (u)))_|
|[_z/x, g(z)/y_]|_g(g(z))_|
|[_g(x)/y_]|_g(g(x))_|

Note that _g(g(_ 3 _))_ and _g(g( f (u)))_ are instances of _g(g(x))_ . Thus _g(g(x))_ is more general than _g(g(_ 3 _))_ and _g(g( f (u)))_ ; it admits many other instances. Certainly _g(g(_ 3 _))_ seems to be arbitrary — neither of the original terms mentions 3! A separate point worth noting is that _g(g(x))_ is equivalent to _g(g(z))_ , apart from the name of the variable. Let us formalize these intuitions.

### 9.4 Most general unifiers

Definition 19 The substitution _θ_ is _more general_ than _φ_ if _φ_ = _θ_ ◦ _σ_ for some substitution _σ_ .

Example 26 Recall the unifiers of _g(g(x))_ and _g(y)_ . The unifier [ _g(x)/y_ ] is more general than the others listed, for

<!-- page 56 -->
9.5 A simple unification algorithm

53

The last line above illustrates that every substitution _θ_ is more general than itself because _θ_ = _θ_ ◦ []; ‘more general’ is a reflexive relation.

If two substitutions _θ_ and _φ_ are each more general than the other then they differ at most by renaming of variables, and can be regarded as equivalent. For instance, [ _y/x, f (y)/w_ ] and [ _x/y, f (x)/w_ ] are equivalent:

What does all this mean in practice? Suppose we would like to apply either _θ_ or _φ_ , where _φ_ = _θ_ ◦ _σ_ . If we apply _θ_ then we can still get the effect of _φ_ by applying _σ_ later. Furthermore, there is an algorithm to find a most general unifier of two terms; by composition, this one unifier can generate all the unifiers of the terms.

Definition 20 A substitution _θ_ is a _most general unifier_ (MGU) of terms _t_ 1, _. . ._ , _tm_ if

- _θ_ unifies _t_ 1, _. . ._ , _tm_ , _and_

- _θ_ is more general than every other unifier of _t_ 1, _. . ._ , _tm_ .

A most general unifier of two or more _literals_ is defined similarly.

Thus if _θ_ is an MGU of terms _t_ 1 and _t_ 2 and _t_ 1 _φ_ = _t_ 2 _φ_ then _φ_ = _θ_ ◦ _σ_ for some substitution _σ_ .

### 9.5 A simple unification algorithm

In many books, the unification algorithm is presented as operating on the concrete syntax of terms, scanning along character strings. But terms are really tree structures and are so represented in a computer. Unification should be presented as operating on trees. In fact, we need consider only binary trees, since these can represent _n_ -ary branching trees. Unification is easily implemented in Lisp, where the basic data structure (the S-expression) is a binary tree with labelled leaves.

Our trees have three kinds of nodes:

- A _variable x_ , _y_ , _. . ._ — can be modified by substitution

- A _constant a_ , _b_ , _. . ._ — handles function symbols also

- A _pair (t, u)_ — where _t_ and _u_ are terms

<!-- page 57 -->
54

9 UNIFICATION

Unification of two terms considers nine cases, most of which are trivial. It is impossible to unify a constant with a pair; in this case the algorithm fails. When trying to unify two constants _a_ and _b_ , if _a_ = _b_ then the most general unifier is []; if _a_ ̸ = _b_ then unification is impossible. The interesting cases are variable-anything and pair-pair.

#### Unification with a variable

Consider unifying a variable _x_ with a term _t_ , where _x_ ̸ = _t_ . If _x_ does not occur in _t_ then the substitution [ _t/x_ ] has no effect on _t_ , so it does the job trivially:

It is not hard to show that [ _t/x_ ] is a _most general_ unifier.

If _x does_ occur in _t_ then no unifier exists, for if _xθ_ = _tθ_ then the term _xθ_ would be a subterm of itself, which is impossible.

Example 27 The terms _x_ and _f (x)_ are not unifiable. If _xθ_ = _u_ then _f (x)θ_ = _f (u)_ . Thus _xθ_ = _f (x)θ_ would imply _u_ = _f (u)_ . We could, perhaps, introduce the infinite term

as a unifier, but this would require a rigorous definition of the syntax and semantics of infinite terms.

#### Unification of two pairs

Unifying the pairs _(t_ 1 _, t_ 2 _)_ with _(u_ 1 _, u_ 2 _)_ requires two recursive calls of the unification algorithm. If _θ_ 1 unifies _t_ 1 with _u_ 1 and _θ_ 2 unifies _t_ 2 _θ_ 1 with _u_ 2 _θ_ 1 then _θ_ 1 ◦ _θ_ 2 unifies _(t_ 1 _, t_ 2 _)_ with _(u_ 1 _, u_ 2 _)_ :

It is possible to prove that if _θ_ 1 and _θ_ 2 are _most general_ unifiers then so is _θ_ 1 ◦ _θ_ 2. If either recursive call fails then the pairs are not unifiable.

<!-- page 58 -->
9.5 A simple unification algorithm

55

Note that the substitution _θ_ 1 is applied to _t_ 2 and _u_ 2 before the second recursive call. Will this terminate, even if _t_ 2 _θ_ 1 and _u_ 2 _θ_ 1 are much bigger than _t_ 2 and _u_ 2? One can show that either _θ_ 1 does not affect _t_ 2 and _u_ 2, or else _θ_ 1 reduces the number of variables in the pair of terms. This is enough to show termination.

As given above, the algorithm works from left to right. An equally good alternative is to begin by unifying _t_ 2 and _u_ 2.

#### Examples of unification

These examples are given for terms rather than binary trees. The translation to binary trees is left as an exercise.

In most of these examples, the two terms have no variables in common. Most uses of unification (including resolution, see below) rename variables in one of the terms to ensure this. However, such renaming is _not_ part of unification itself.

Example 28 Unify _f (x, b)_ with _f (a, y)_ . Steps:

Unify _x_ and _a_ getting [ _a/x_ ].

Unify _b_ and _y_ getting [ _b/y_ ].

Result is [ _a/x_ ] ◦ [ _b/y_ ], which is [ _a/x, b/y_ ].

Strictly speaking we also have to unify _f_ with _f_ , but this just gives [], the null substitution.

Example 29 Unify _f (x, x)_ with _f (a, b)_ . Steps:

Unify _x_ and _a_ getting [ _a/x_ ].

Try to unify _x_ [ _a/x_ ] and _b_ [ _a/x_ ].

These are _a_ and _b_ , distinct constants. Fail.

Example 30 Unify _f (x, g(y))_ with _f (y, x)_ . Steps:

Unify _x_ and _y_ getting [ _y/x_ ].

Try to unify _g(y)_ [ _y/x_ ] and _x_ [ _y/x_ ]. These are _g(y)_ and _y_ , violating the occurs check. Fail.

If we had renamed the variables in one of the terms beforehand, unification would have succeeded. In the next example, the two terms have no variables in common, but unification fails anyway.

<!-- page 59 -->
56

9 UNIFICATION

Example 31 Unify _f (x, x)_ with _f (y, g(y))_ . Steps:

Unify _x_ and _y_ getting [ _y/x_ ].

Try to unify _x_ [ _y/x_ ] and _g(y)_ [ _y/x_ ].

These are _y_ and _g(y)_ , where _y_ occurs in _g(y)_ . Fail.

Example 32 Unify _j (w, a, h(w))_ with _j ( f (x, y), x, z)_ . Steps:

Unify _w_ and _f (x, y)_ getting [ _f (x, y)/w_ ].

Unify _a_ and _x_ (the substitution has no effect) getting [ _a/x_ ]. Unify _(h(w)_ [ _f (x, y)/w_ ] _)_ [ _a/x_ ] and _(z_ [ _f (x, y)/w_ ] _)_ [ _a/x_ ]. These are _h( f (x, y))_ [ _a/x_ ] and _z_ [ _a/x_ ].

These are _h( f (a, y))_ and _z_ ; unifier is [ _h( f (a, y))/z_ ].

Result is [ _f (x, y)/w_ ] ◦ [ _a/x_ ] ◦ [ _h( f (a, y))/z_ ]. Performing the compositions, this simplifies to [ _f (a, y)/w, a/x, h( f (a, y))/z_ ].

Example 33 Unify _j (w, a, h(w))_ with _j ( f (x, y), x, y)_ . This is the previous example but with a _y_ in place of a _z_ .

Unify _w_ and _f (x, y)_ getting [ _f (x, y)/w_ ].

Unify _a_ and _x_ getting [ _a/x_ ].

Unify _(h(w)_ [ _f (x, y)/w_ ] _)_ [ _a/x_ ] and _(y_ [ _f (x, y)/w_ ] _)_ [ _a/x_ ].

These are _h( f (a, y))_ and _y_ , but _y_ occurs in _h( f (a, y))_ . Fail.

Diagrams can be helpful. The lines indicate variable replacements:

<!-- Start of picture text -->
j (w, a, h(w)) j ( f (x, y), x, y) a/x f (a, y)/w h( f (a, y))/y ??? <!-- End of picture text -->

<!-- page 60 -->
57

9.6 Examples of theorem proving

#### Implementation remarks

To unify terms _t_ 1, _t_ 2, _. . ._ , _tm_ for _m >_ 2, compute a unifier _θ_ of _t_ 1 and _t_ 2, then recursively compute a unifier _σ_ of the terms _t_ 2 _θ_ , _. . ._ , _tmθ_ . The overall unifier is then _θ_ ◦ _σ_ . If any unification fails then the set is not unifiable.

A real implementation does not need to compose substitutions. Most represent variables by pointers and effect the substitution [ _t/x_ ] by updating pointer _x_ to _t_ . The compositions are cumulative, so this works. However, if unification fails at some point, the pointer assignments must be undone!

To avoid pointers you can store the updates as a list of pairs, called an _environment_ . For example, the environment _a/x, f (x)/y_ represents the substitution [ _a/x, f (a)/y_ ]. The algorithm sketched here can take exponential time in unusual cases. Faster algorithms exist, although they are more complex and are seldom adopted.

Prolog systems, for the sake of efficiency, omit the occurs check. This can result in circular data structures and looping. It is unsound for theorem proving.

### 9.6 Examples of theorem proving

These two examples are fundamental. They illustrate how the occurs check enforces correct quantifier reasoning.

#### Example 34 Consider a proof of

_(_ ∃ _y_ ∀ _x R(x, y))_ → _(_ ∀ _x_ ∃ _y R(x, y))._

Produce clauses separately for the antecedent and for the negation of the consequent; this is more efficient than producing clauses for the negation of the entire formula.

- The antecedent is ∃ _y_ ∀ _x R(x, y)_ ; replacing _y_ by the Skolem constant _a_ yields the clause { _R(x, a)_ }.

- In ¬ _(_ ∀ _x_ ∃ _y R(x, y))_ , pushing in the negation produces ∃ _x_ ∀ _y_ ¬ _R(x, y)_ . Replacing _x_ by the Skolem constant _b_ yields the clause {¬ _R(b, y)_ }.

Unifying _R(x, a)_ with _R(b, y)_ detects the contradiction _R(b, a)_ ∧¬ _R(b, a)_ .

Example 35 In a similar vein, let us try to prove

_(_ ∀ _x_ ∃ _y R(x, y))_ → _(_ ∃ _y_ ∀ _x R(x, y))._

<!-- page 61 -->
58

10 APPLICATIONS OF UNIFICATION

- Here the antecedent is ∀ _x_ ∃ _y R(x, y)_ ; replacing _y_ by the Skolem function _f_ yields the clause { _R(x, f (x))_ }.

- The negation of the consequent is ¬ _(_ ∃ _y_ ∀ _x R(x, y))_ , which becomes ∀ _y_ ∃ _x_ ¬ _R(x, y)_ . Replacing _x_ by the Skolem function _g_ yields the clause {¬ _R(g(y), y)_ }.

Observe that _R(x, f (x))_ and _R(g(y), y)_ are not unifiable because of the occurs check. And so it should be, because the original formula is not a theorem!

_Exercise 31_ For each of the following pairs of terms, give a most general unifier or explain why none exists. Do not rename variables prior to performing the unification.

## 10 Applications of Unification

By means of unification, we can extend resolution to first-order logic. As a special case we obtain Prolog. Other theorem provers are also based on unification. Other applications include polymorphic type checking for the language ML.

### 10.1 Binary resolution

We now define the binary resolution rule with unification:

As before, the first clause contains _B_ and other literals, while the second clause contains ¬ _D_ and other literals. The substitution _σ_ is a unifier of _B_ and _D_ (almost always a _most general_ unifier). This substitution is applied to all remaining literals, producing the conclusion.

The variables in one clause are renamed before resolution to prevent clashes with the variables in the other clause. Renaming is sound because the scope of each variable is its clause. Resolution is sound because it takes an instance of each clause — the instances are valid, because the clauses are universally valid —

<!-- page 62 -->
59

10.2 Factoring

and then applies the propositional resolution rule, which is sound. For example, the two clauses

yield the empty clause in a single resolution step. This works by renaming variables — say, _x_ to _y_ in the second clause — and unifying _P(x)_ with _P(g(y))_ . Forgetting to rename variables is fatal, because _P(x)_ cannot be unified with _P(g(x))_ .

### 10.2 Factoring

In the general case, the resolution rule must perform _factoring_ . This uses additional unifications to identify literals in the same clause. Factoring can make the clause { _P(x, b), P(a, y)_ } behave like the clause { _P(a, b)_ }, since _P(a, b)_ is the result of unifying _P(x, b)_ with _P(a, y)_ .

The factoring unifications are done at the same time as the unification of the complementary literals in the two clauses. The binary resolution rule with factoring is

where _σ_ is the most general substitution such that

Resolution with factoring is _refutation complete_ : it will find a contradiction if there is one. Showing this is difficult.

The search space is huge: resolution with factoring can be applied in many different ways, every time. Modern resolution systems use highly complex heuristics to limit the search. Typically they only perform resolutions that can lead (perhaps after several steps) to very short clauses, and they discard the intermediate clauses produced along the way. Dozens of flags and parameters influence their operation.

Example 36 Let us prove ∀ _x_ ∃ _y_ ¬ _(P(y, x)_ ↔¬ _P(y, y))_ . Negate and expand the ↔, getting

Its negation normal form is

<!-- page 63 -->
60

10 APPLICATIONS OF UNIFICATION

Skolemization yields

The clauses are

Note that ¬ _P(a, a)_ is an instance of the first clause and that _P(a, a)_ is an instance of the second, contradiction. This is a one-step proof! But it involves both resolution and factoring, since the 2-literal clauses must collapse to singleton clauses.

Example 37 Let us prove ∃ _x_ [ _P_ → _Q(x)_ ] ∧∃ _x_ [ _Q(x)_ → _P_ ] →∃ _x_ [ _P_ ↔ _Q(x)_ ]. The clauses are

A short resolution proof follows. The complementary literals are underlined:

_Exercise 32_ Show the steps of converting ∃ _x_ [ _P_ → _Q(x)_ ]∧∃ _x_ [ _Q(x)_ → _P_ ] → ∃ _x_ [ _P_ ↔ _Q(x)_ ] into clauses. Then show two resolution proofs different from the one shown above.

_Exercise 33_ Is the clause { _P(x, b), P(a, y)_ } logically equivalent to the unit clause { _P(a, b)_ }? Is the clause { _P(y, y), P(y, a)_ } logically equivalent to { _P(y, a)_ }? Explain both answers.

### 10.3 Prolog clauses

Prolog clauses, also called Horn clauses, have at most one positive literal. A _definite_ clause is one of the form

It is logically equivalent to _(A_ 1 ∧· · · ∧ _Am)_ → _B_ . Prolog’s notation is

<!-- page 64 -->
61

10.4 Prolog computations

If _m_ = 0 then the clause is simply written as _B_ and is sometimes called a _fact_ . A _negative_ or _goal_ clause is one of the form

Prolog permits just one of these; it represents the list of unsolved goals. Prolog’s notation is

A Prolog database consists of definite clauses. Observe that definite clauses cannot express negative assertions, since they must contain a positive literal. From a mathematical point of view, they have little expressive power; every set of definite clauses is consistent! Even so, definite clauses are a natural notation for many problems.

_Exercise 34_ Show that every set of definite clauses is consistent. (Hint: first consider propositional logic, then extend your argument to first order logic.)

### 10.4 Prolog computations

A Prolog computation takes a database of definite clauses together with one goal clause. It repeatedly resolves the goal clause with some definite clause to produce a new goal clause. If resolution produces the empty goal clause, then execution succeeds.

Here is a diagram of a Prolog computation step:

This is a _linear_ resolution (§7). Two program clauses are never resolved with each other. The result of each resolution step becomes the next goal clause; the previous goal clause is discarded after use.

Prolog resolution is efficient, compared with general resolution, because it involves less search and storage. General resolution must consider all possible pairs of clauses; it adds their resolvents to the existing set of clauses; it spends

<!-- page 65 -->
62

10 APPLICATIONS OF UNIFICATION

a great deal of effort getting rid of subsumed (redundant) clauses and probably useless clauses. Prolog always resolves some program clause with the goal clause. Because goal clauses do not accumulate, Prolog requires little storage. Prolog never uses factoring and does not even remove repeated literals from a clause.

Prolog has a fixed, deterministic execution strategy. The program is is regarded as a list of clauses, not a set; the clauses are tried strictly in order. With a clause, the literals are also regarded as a list. The literals in the goal clause are proved strictly from left to right. The goal clause’s first literal is replaced by the literals from the unifying program clause, preserving their order.

Prolog’s search strategy is depth-first. To illustrate what this means, suppose that the goal clause is simply ← _P_ and that the program clauses are _P_ ← _P_ and _P_ ← . Prolog will resolve _P_ ← _P_ with ← _P_ to obtain a new goal clause, which happens to be identical to the original one. Prolog never notices the repeated goal clause, so it repeats the same useless resolution over and over again. Depthfirst search means that at every ‘choice point,’ such as between using _P_ ← _P_ and _P_ ← , Prolog will explore every avenue arising from its first choice before considering the second choice. Obviously, the second choice would prove the goal trivially, but Prolog never notices this.

### 10.5 Example of Prolog execution

Here are axioms about the English succession: how _y_ can become King after _x_ .

king _(_ richardIII _)_

#### defeat _(_ henryVII _,_ richardIII _)_

#### oldestson _(_ henryVIII _,_ henryVII _)_

The goal is to prove king _(_ henryVIII _)_ .

These axioms correspond to the following definite clauses:

<!-- page 66 -->
10.5 Example of Prolog execution

63

The goal clause is

Figure 2 shows the execution. The subscripts in the clauses are to rename the variables.

Note how crude this formalization is. It says nothing about the passage of time, about births and deaths, about not having two kings at once. Henry VIII was the second son of Henry VII; the first son, Arthur, died before his father. Logic is clumsy for talking about situations in the real world.

The Frame Problem in Artificial Intelligence reveals another limitation of logic. Consider writing an axiom system to describe a robot’s possible actions. We might include an axiom to state that if the robot lifts an object at time _t_ , then it will be holding the object at time _t_ + 1. But we also need to assert that the positions of everything else remain the same as before. Then we must consider the possibility that the object is a table and has other things on top of it _. . ._

Prolog is a powerful and useful language, but it is not necessarily logic. Most Prolog programs rely on special predicates that affect execution but have no logical meaning. There is a huge gap between the theory and practice of logic programming.

_Exercise 35_ Convert these formulæ into clauses, showing each step: negating the formula, eliminating → and ↔, pushing in negations, moving the quantifiers, Skolemizing, dropping the universal quantifiers, and converting the matrix into CNF.

- ¬∃ _y_ ∀ _x (R(x, y)_ ↔¬∃ _z (R(x, z)_ ∧ _R(z, x)))_

<!-- page 67 -->
64

10 APPLICATIONS OF UNIFICATION

<!-- Start of picture text -->
definite clause goal clause ⌢⋐⊣⌋ � {¬os (y 1 , x 1 ),  ¬k (x 1 ),  k (y 1 ) } {¬k ( henryVIII ) } {os ( henryVIII ,  henryVII ) } {¬os ( henryVIII , x 1 ),  ¬k (x 1 ) } {¬defeat (y 2 , x 2 ),  ¬k (x 2 ),  k (y 2 ) } {¬k ( henryVII ) } {defeat ( henryVII ,  richardIII ) } {¬defeat ( henryVII , x 2 ),  ¬k (x 2 ) } {k ( richardIII ) } {¬k ( richardIII ) } □ <!-- End of picture text -->

Figure 2: Execution of a Prolog program (os = oldestson, k = king)

<!-- page 68 -->
65

_Exercise 36_ Consider the Prolog program consisting of the definite clauses

Describe the Prolog computation starting from the goal clause ← _P(v)_ . Keep track of the substitutions affecting _v_ to determine what answer the Prolog system would return.

_Exercise 37_ Find a refutation from the following set of clauses using resolution with factoring.

_Exercise 38_ Prove the following formulæ by resolution, showing all steps of the conversion into clauses. Remember to negate first!

## 11 Modal Logics

There are many forms of modal logic. Each one is based upon two parameters:

- _W_ is the set of _possible worlds_ (machine states, future times, _. . ._ )

- _R_ is the _accessibility relation_ between worlds (state transitions, flow of time, _. . ._ )

The pair _(W, R)_ is called a _modal frame_ .

The two _modal operators_ , or _modalities_ , are _2_ and _3_ :

- _2A_ means _A_ is _necessarily true_

- _3A_ means _A_ is _possibly true_

Here ‘necessarily true’ means ‘true in all worlds accessible from the present one’. The modalities are related by the law ¬ _3A_ ≃ _2_ ¬ _A_ ; in words, ‘ _A_ is necessarily false’ is equivalent to ‘it is not possible that _A_ is true’.

_Complex modalities_ are made up of strings of the modal operators, such as _22A_ , _23A_ , _32A_ , etc. Typically many of these are equivalent to others; in _S_ 4, a standard modal logic, _22A_ is equivalent to _2A_ .

<!-- page 69 -->
66

11 MODAL LOGICS

### 11.1 Semantics of propositional modal logic

Here are some basic definitions, with respect to a particular frame _(W, R)_ :

An _interpretation I_ maps the propositional letters to subsets of _W_ . For each letter _P_ , the set _I (P)_ consists of those worlds in which _P_ is regarded as true.

If _w_ ∈ _W_ and _A_ is a modal formula, then _w_ ⊩ _A_ means _A_ is true in world _w_ . This relation is defined as follows:

_w_ ⊩ _P_ ⇐⇒ _w_ ∈ _I (P) w_ ⊩ _2A_ ⇐⇒ _v_ ⊩ _A_ for all _v_ such that _R(w, v) w_ ⊩ _3A_ ⇐⇒ _v_ ⊩ _A_ for some _v_ such that _R(w, v) w_ ⊩ _A_ ∨ _B_ ⇐⇒ _w_ ⊩ _A_ or _w_ ⊩ _B w_ ⊩ _A_ ∧ _B_ ⇐⇒ _w_ ⊩ _A_ and _w_ ⊩ _B w_ ⊩ ¬ _A_ ⇐⇒ _w_ ⊩ _A_ does not hold

This definition of truth is more complex than we have seen previously (§2.2), because of the extra parameters _W_ and _R_ . We shall not consider quantifiers at all; they really complicate matters, especially if the universe is allowed to vary from one world to the next.

For a particular frame _(W, R)_ , further relations can be defined in terms of _w_ ⊩ _A_ :

Now |= _A_ means |= _W,R A_ for all frames. We say that _A_ is _universally valid_ . In particular, all tautologies of propositional logic are universally valid.

Typically we make further assumptions on the accessibility relation. We may assume, for example, that _R_ is transitive, and consider whether a formula holds under all such frames. More formulæ become universally valid if we restrict the accessibility relation, as they exclude some modal frames from consideration. The purpose of such assumptions is to better model the task at hand. For instance, to model the passage of time, we might want _R_ to be reflexive and transitive; we could even make it a linear ordering, though branching-time temporal logic is popular.

### 11.2 Hilbert-style proof systems for the modal logics

Start with any proof system for propositional logic. Then add the _distribution_ axiom

<!-- page 70 -->
67

11.3 Sequent Calculus Rules for _S_ 4

and the _necessitation_ rule:

There are no axioms or inference rules for _3_ . The modality is viewed simply as an abbreviation:

The distribution axiom clearly holds in our semantics. The propositional connectives obey their usual truth tables in each world. If _A_ holds in all worlds, and _A_ → _B_ holds in all worlds, then _B_ holds in all worlds. Thus if _2A_ and _2(A_ → _B)_ hold then so does _2B_ , and that is the essence of the distribution axiom.

The necessitation rule states that all theorems are necessarily true. In more detail, if _A_ can be proved, then it holds in all worlds; therefore _2A_ is also true.

The modal logic that results from adding the distribution axiom and necessitation rule is called _K_ . It is a pure modal logic, from which others are obtained by adding further axioms. Each axiom corresponds to a property that is assumed to hold of all accessibility relations. Here are just a few of the main ones:

Logic _T_ includes axiom T: reflexivity. Logic _S_ 4 includes axioms T and 4: reflexivity and transitivity. Logic _S_ 5 includes axioms T, 4 and B: reflexivity, transitivity and symmetry; these imply that the accessibility relation is an equivalence relation, which is a strong condition.

Other conditions on the accessibility relation concern forms of _confluence_ . One such condition might state that if _w_ 1 and _w_ 2 are both accessible from _w_ then there exists some _v_ that is accessible from both _w_ 1 and _w_ 2.

### 11.3 Sequent Calculus Rules for _S_ 4

We shall mainly look at _S_ 4, which is one of the mainstream modal logics. The sequent calculus for _S_ 4 extends the usual sequent rules for propositional logic with additional ones for _2_ and _3_ . Four rules are required because the modalities may occur on either the left or right side of a sequent.

<!-- page 71 -->
68

11 MODAL LOGICS

The _(2r )_ rule is analogous to the necessitation rule. But now _A_ may be proved from other formulæ. This introduces complications. Modal logic is notorious for requiring strange conditions in inference rules. The symbols _�_∗ and _�_∗ stand for sets of formulæ, defined as follows:

In effect, applying rule _(2r )_ in a backward proof throws away all left-hand formulæ that do not begin with a _2_ and all right-hand formulæ that do not begin with a _3_ .

If you consider why the _(2r )_ rule actually holds, it is not hard to see why those formulæ must be discarded. If we forgot about the restriction, then we could use _(2r )_ to infer _A_ ⇒ _2A_ from _A_ ⇒ _A_ , which is ridiculous. The restriction ensures that the proof of _A_ in the premise is independent of any particular world.

The rule _(3l)_ is an exact dual of _(2r )_ . The obligation to discard formulæ forces us to plan proofs carefully. If rules are applied in the wrong order, vital information may have to be discarded and the proof will fail.

### 11.4 Some sample proofs in _S_ 4

A few examples will illustrate how the _S_ 4 sequent calculus is used.

The distribution axiom is assumed in the Hilbert-style proof system. Using the sequent calculus, we can prove it:

A few applications of _(_ → _r )_ yield the desired theorem, _2(A_ → _B)_ → _(2A_ → _2B)_ .

<!-- page 72 -->
69

11.4 Some sample proofs in _S_ 4

Working backwards, the first step is to apply rule _(2r )_ . This rule discards non- _2_ formulæ, but there happen not to be any. Had we first applied _(2l)_ , removing the boxes from the left side, then we should get stuck:

Applying _(2r )_ before _(2l)_ is analogous to applying _(_ ∀ _r )_ before _(_ ∀ _l)_ . The analogy because _2A_ has an implicit universal quantifier: for all accessible worlds.

The following two proofs establish the equivalence _2323A_ ≃ _23A_ . Strings of modalities, like _2323_ and _23_ , are called _operator strings_ . So the pair of results establish an operator string equivalence.

Here is the first entailment in the equivalence. As usual we apply _(2r )_ before _(2l)_ . Dually, and analogously to the treatment of the ∃ rules, we apply _(3l)_ before _(3r )_ :

The opposite entailment is easy to prove:

Logic _S_ 4 enjoys many operator string equivalences, including _22A_ ≃ _2A_ . And for every operator string equivalence, its dual (obtained by exchanging _2_ with _3_ ) also holds. In particular, _33A_ ≃ _3A_ and _3232A_ ≃ _32A_ hold. So we only need to consider operator strings in which the boxes and diamonds alternate, and whose length does not exceed three.

The distinct _S_ 4 operator strings are therefore _2_ , _3_ , _23_ , _32_ , _232_ and _323_ .

Finally, here are two attempted proofs that fail — because their conclusions are not theorems! The modal sequent _A_ ⇒ _23A_ states that if _A_ holds now then it necessarily holds again: from each accessible world, another world is accessible in which _A_ holds. This formula is valid if the accessibility relation is symmetric;

<!-- page 73 -->
70

12 TABLEAUX-BASED METHODS

then one could simply return to the original world. The formula is therefore a theorem of _S_ 5 modal logic, but not _S_ 4.

Here, the modal sequent _3A, 3B_ ⇒ _3(A_ ∧ _B)_ states that if _A_ holds in some accessible world, and _B_ holds in some accessible world, then both _A_ and _B_ hold in some accessible world. It is a fallacy because those two worlds need not coincide. The _(3l)_ rule prevents us from removing the diamonds from both _3A_ and _3B_ ; if we choose one we must discard the other:

The topmost sequent may give us a hint as to why the conclusion fails. Here we are in a world in which _B_ holds, and we are trying to show _A_ ∧ _B_ , but there is no reason why _A_ should hold in that world.

_Exercise 39_ Why does the dual of an operator string equivalence also hold?

_Exercise 40_ Prove the sequent _3(A_ ∨ _B)_ ⇒ _3A, 3B_ .

_Exercise 41_ Prove the sequent _3A_ ∨ _3B_ ⇒ _3(A_ ∨ _B)_ . Together with the previous exercise, this yields _3(A_ ∨ _B)_ ≃ _3A_ ∨ _3B_ .

_Exercise 42_ Prove the sequent _3(A_ → _B), 2A_ ⇒ _3B_ .

_Exercise 43_ Prove the equivalence _2(A_ ∧ _B)_ ≃ _2A_ ∧ _2B_ .

## 12 Tableaux-Based Methods

There is a lot of redundancy among the connectives ¬, ∧, ∨, →, ↔, ∀, ∃. We could get away using only three of them (two if we allowed exclusive ‘or’), but use the full set for readability. There is also a lot of redundancy in the sequent calculus, because it was designed to model human reasoning, not to be as small as possible.

One approach to removing redundancy results in the resolution method. Clause notation replaces the connectives, and there is only one inference rule.

<!-- page 74 -->
12.1 Simplifying the sequent calculus

71

A less radical approach still removes much of the redundancy, while preserving much of the natural structure of formulæ. This approach is often adopted by proof theorists because of its logical simplicity; it is also amenable to implementation.

### 12.1 Simplifying the sequent calculus

The usual formalisation of first-order logic involves seven connectives, or nine in the case of modal logic. For each connective the sequent calculus has a left and a right rule. So, apart from the structural rules (basic sequent and cut) there are 14 rules, or 18 for modal logic.

Suppose we allow only formulæ in negation normal form. This immediately disposes of the connectives → and ↔. Really ¬ is discarded also, as it is allowed only on propositional letters. So only four connectives remain, six for modal logic.

The greatest simplicity gain comes in the sequent rules. The only sequent rules that move formulæ from one side to the other (across the ⇒ symbol) are the rules for the connectives that we have just discarded. Half of the sequent rules can be discarded too. It makes little difference whether we discard the left-side rules or the right-side rules.

Let us discard the right-side rules. The resulting system allows sequents of the form _A_ ⇒ . It is a form of refutation system (proof by contradiction), since the formula _A_ has the same meaning as the sequent ¬ _A_ ⇒ . Moreover, a basic sequent has the form of a contradiction.

Rule _(_ ∃ _l)_ has the usual proviso: it holds _provided x_ is not free in the conclusion!

We can extend the system to _S_ 4 modal logic by adding just two further rules, one for _2_ and one for _3_ :

As previously, _�_∗ is defined to erase all non- _2_ formulæ:

<!-- page 75 -->
72

12 TABLEAUX-BASED METHODS

We have gone from 14 rules to four, ignoring the structural rules. For modal logic, we have gone from 18 rules to six.

A simple proof will illustrate how the simplified system works. Let us prove ∀ _x (A_ → _B)_ ⇒ _A_ →∀ _x B_ , where _x_ is not free in _A_ . We must negate the formula and convert it to NNF; the resulting sequent is _A_ ∧∃ _x_ ¬ _B,_ ∀ _x (_ ¬ _A_ ∨ _B)_ ⇒ . Elaborate explanations should not be necessary because this sequent calculus is essentially a subset of the one described in §6.

### 12.2 Mechanising the technique

Some proof theorists adopt the simplified sequent calculus as their formalisation of first-order logic. It has most of the advantages of the usual sequent calculus, without the redundancy. But can we use it as the basis for a theorem prover? Implementing the calculus (or indeed, implementing the full sequent calculus) requires a treatment of quantifiers. As with the resolution method, we can use unification together with Skolemization.

First, consider how to add unification. The rule _(_ ∀ _l)_ substitutes some term for the bound variable. Since we do not know in advance what the term ought to be, instead substitute a free variable. The variable ought to be fresh, not used elsewhere in the proof:

Then allow unification to instantiate variables with terms. This should occur when trying to solve any goal containing two formulæ, ¬ _A_ and _B_ . Try to unify _A_ with _B_ , producing a basic sequent. Of course, instantiating a variable updates the entire proof tree.

Rule _(_ ∃ _l)_ , used in backward proof, must create a fresh variable. That will no longer do, in part because we now allow variables to become instantiated by terms. We have a choice of techniques, but the simplest is to Skolemize the formula. All existential quantifiers disappear, so we can discard rule _(_ ∃ _l)_ .

Previously (§8.2) we performed Skolemization on formulæ in prenex form: all quantifiers at the front. The outermost existentially-bound variable was replaced by a function, which took as many arguments as there were enclosing universal

<!-- page 76 -->
12.3 Sample proofs

73

quantifiers. But there is no need to pull quantifiers to the front. Precisely the same approach works, although now the existential quantifiers are found in subformulæ instead of being lined up in a row.

The Skolem form of ∀ _y_ ∃ _z Q(y, z)_ ∧∃ _x P(x)_ is ∀ _y Q(y, f (y))_ ∧ _P(a)_ . The subformula ∃ _x P(x)_ goes to _P(a)_ and not to _P(g(y))_ because it is outside the scope of the ∀ _y_ .

### 12.3 Sample proofs

To demonstrate the system, let us prove the formula ∃ _x_ ∀ _y_ [ _P(x)_ → _P(y)_ ]. First negate it and convert to NNF, getting ∀ _x_ ∃ _y_ [ _P(x)_ ∧¬ _P(y)_ ]. The Skolemized sequent to be proved is ∀ _x_ [ _P(x)_ ∧¬ _P( f (x))_ ] ⇒ . Unification completes the proof by creating a basic sequent; there are two distinct ways of doing so:

In the first inference from the bottom, the universal formula is retained because it must be used again. In principle, universally quantified formulæ ought always to be retained, as they may be used any number of times. I normally erase them to save space.

Pulling quantifiers to the front is not merely unnecessary; it can be harmful. Skolem functions should have as few arguments as possible, as this leads to shorter proofs. Attaining this requires that quantifiers should have the smallest possible scopes; we ought to push quantifiers in, not pull them out. This is sometimes called _miniscope_ form.

For example, the formula ∃ _x_ ∀ _y_ [ _P(x)_ → _P(y)_ ] is tricky to prove. But putting it in miniscope form makes its proof trivial. Let us do this step by step:

Negate; convert to NNF: ∀ _x_ ∃ _y_ [ _P(x)_ ∧¬ _P(y)_ ] Push in the ∃ _y_ : ∀ _x_ [ _P(x)_ ∧∃ _y_ ¬ _P(y)_ ] Push in the ∀ _x_ : ∀ _x P(x)_ ∧∃ _y_ ¬ _P(y)_ Skolemize: ∀ _x P(x)_ ∧¬ _P(a)_ ]

The formula ∀ _x P(x)_ ∧¬ _P(a)_ ] is obviously inconsistent. Here is its refutation

<!-- page 77 -->
74

#### 12 TABLEAUX-BASED METHODS

in the modified sequent calculus:

A failed proof is always illuminating. Let us try to prove the invalid formula

Negation and conversion to NNF gives ∃ _x_ ¬ _P(x)_ ∧∃ _x_ ¬ _Q(x),_ ∀ _x_ [ _P(x)_ ∨ _Q(x)_ ].

Skolemization gives ¬ _P(a)_ ∧¬ _Q(b),_ ∀ _x_ [ _P(x)_ ∨ _Q(x)_ ].

The proof fails because _a_ and _b_ are distinct constants. It is impossible to instantiate _y_ to both simultaneously.

### 12.4 Tableaux-based theorem provers

An _analytic tableau_ represents a partial proof as a set of _branches_ of formulæ. Each formula on a branch is _expanded_ until this is no longer possible (and the proof fails) or until the proof succeeds.

Expanding a conjunction _A_ ∧ _B_ on a branch replaces it by the two conjuncts, _A_ and _B_ . Expanding a disjunction _A_ ∨ _B_ splits the branch in two, with one branch containing _A_ and the other branch _B_ . Expanding the quantification ∀ _x A_ extends the branch by a formula of the form _A_ [ _t/x_ ]. If a branch contains both _A_ and ¬ _A_ then it is said to be _closed_ . When all branches are closed, the proof has succeeded.

A tableau is, in fact, nothing but a compact, graph-based representation of a set of sequents. The branch operations described above correspond to our sequent rules in an obvious way.

Quite a few theorem provers have been based upon the tableau method. The simplest by far is due to Beckert and Posegga (1994) and is called lean _T__A_ _P_ . The entire program appears below! Its deductive system is similar to the reduced sequent calculus we have just studied. It relies on some Prolog tricks, and is certainly not pure Prolog code. It demonstrates just how simple a theorem prover can be. lean _T__A_ _P_ does not outperform big resolution systems. But it quickly proves some fairly hard theorems.

<!-- page 78 -->
75

REFERENCES

```
prove((A,B),UnExp,Lits,FreeV,VarLim):-!,
prove(A,[B|UnExp],Lits,FreeV,VarLim).
prove((A;B),UnExp,Lits,FreeV,VarLim):-!,
prove(A,UnExp,Lits,FreeV,VarLim),
prove(B,UnExp,Lits,FreeV,VarLim).
prove(all(X,Fml),UnExp,Lits,FreeV,VarLim):-!,
\+length(FreeV,VarLim),
copy_term((X,Fml,FreeV),(X1,Fml1,FreeV)),
append(UnExp,[all(X,Fml)],UnExp1),
prove(Fml1,UnExp1,Lits,[X1|FreeV],VarLim).
prove(Lit,_,[L|Lits],_,_):-
(Lit=-Neg;-Lit=Neg)->
(unify(Neg,L);prove(Lit,[],Lits,_,_)).
prove(Lit,[Next|UnExp],Lits,FreeV,VarLim):-
prove(Next,UnExp,[Lit|Lits],FreeV,VarLim).
```

(Note: you are not expected to memorize this program or understand how it works in any detail.)

_Exercise 44_ Use the tableau calculus to prove examples given in previous sections.

## References

- Beckert, B. and Posegga, J. (1994). leanTAP: Lean, tableau-based theorem proving. In A. Bundy, editor, _Automated Deduction — CADE-12 International Conference_ , LNAI 814, pages 793–797. Springer.

- Bryant, R. E. (1992). Symbolic boolean manipulation with ordered binary-decision diagrams. _Computing Surveys_ , 24 (3), 293–318.

- Zhang, H. and Stickel, M. E. (1994). An efficient algorithm for unit propagation. Technical Report 94-12, Computer Science Dept., University of Iowa.
