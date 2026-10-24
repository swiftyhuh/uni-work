<!-- page 1 -->
7.3 Introduction to resolution

37

_Exercise 20_ Apply the Davis-Putnam procedure to the clause set

# 7.3 Introduction to resolution

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

<!-- page 2 -->
## 38

## 7 CLAUSE METHODS FOR PROPOSITIONAL LOGIC

strategy, and the new clause is added to it. If _m_ = 0 or _n_ = 0 then the new clause will be smaller than one of the parent clauses; if _m_ = _n_ = 0 then the new clause will be empty. A clause is true (in some interpretation) just when one of the literals is true; thus the empty clause indicates contradiction. It is written □. If the empty clause is generated, resolution terminates successfully.

# 7.4 Examples of ground resolution

Let us try to prove

Convert its negation to CNF:

We can combine steps 1 (eliminate →) and 2 (push negations in) using the law ¬ _(A_ → _B)_ ≃ _A_ ∧¬ _B_ :

Step 3, push disjunctions in, has nothing to do. The clauses are

We resolve { _P_ } and {¬ _Q,_ ¬ _P_ } as follows:

The resolvent is {¬ _Q_ }. Resolving { _Q_ } and with this new clause gives

The resolvent is the empty clause, properly written as □. We have proved _P_ ∧ _Q_ → _Q_ ∧ _P_ by assuming its negation and deriving a contradiction. It is nicer to draw a tree like this:

<!-- page 3 -->
7.5 A proof using a set of assumptions

39

Another example is _(P_ ↔ _Q)_ ↔ _(Q_ ↔ _P)_ . The steps of the conversion to clauses is left as an exercise; remember to negate the formula first! The final clauses are

A tree for the resolution proof is

Note that the tree contains { _Q_ } and {¬ _Q_ } rather than { _Q, Q_ } and {¬ _Q,_ ¬ _Q_ }. If we forget to suppress repeated literals, we can get stuck. Resolving { _Q, Q_ } and {¬ _Q,_ ¬ _Q_ } (keeping repetitions) gives { _Q,_ ¬ _Q_ }, a tautology. Tautologies are useless. Resolving this one with the other clauses leads nowhere. Try it.

These examples could mislead. Must a proof use each clause exactly once? No! A clause may be used repeatedly, and many problems contain redundant clauses. Here is an example:

Redundant clauses can make the theorem-prover flounder; this is a challenge facing the field.

_Exercise 21_ Prove _(A_ → _B_ ∨ _C)_ → [ _(A_ → _B)_ ∨ _(A_ → _C)_ ] using resolution.

# 7.5 A proof using a set of assumptions

In this example we assume

and prove _H_ → _P_ . It turns out that we can generate clauses separately from the assumptions (taken _positively_ ) and the conclusion ( _negated_ ).

<!-- page 4 -->
40

## 7 CLAUSE METHODS FOR PROPOSITIONAL LOGIC

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

<!-- page 5 -->
7.6 Deletion of redundant clauses

41

Working from the goal. In each resolution step, at least one clause involves the negated conclusion (possibly via earlier resolution steps). We do not blindly derive facts from the assumptions — for, provided the assumptions are consistent, any contradiction will have to involve the negated conclusion. This strategy is called _set of support_ .

Linear resolution. The proof has a linear structure: each resolvent becomes the parent clause for the next resolution step. Furthermore, the other parent clause is always one of the original set of clauses. This simple structure is very efficient because only the last resolvent needs to be saved. It is similar to the execution strategy of Prolog.

_Exercise 22_ Explain in more detail the conversion of this example into clauses.

_Exercise 23_ Prove Peirce’s law, _((P_ → _Q)_ → _P)_ → _P_ , using resolution.

_Exercise 24_ Prove _(Q_ → _R)_ ∧ _(R_ → _P_ ∧ _Q)_ ∧ _(P_ → _Q_ ∨ _R)_ → _(P_ ↔ _Q)_ using resolution.

# 7.6 Deletion of redundant clauses

During resolution, the number of clauses builds up dramatically; it is important to delete all redundant clauses.

Each new clause is a consequence of the existing clauses. A contradiction can only be derived if the original set of clauses is inconsistent. A clause can be deleted if it does not affect the consistency of the set. Any tautology should be deleted, since it is true in all interpretations.

Here is a subtler case. Consider the clauses

Resolving the first two yields { _P, R_ }. Since each clause is a disjunction, any interpretation that satisfies { _P, R_ } also satisfies { _P, Q, R_ }. Thus { _P, Q, R_ } cannot cause inconsistency, and should be deleted.

Put another way, _P_ ∨ _R_ implies _P_ ∨ _Q_ ∨ _R_ . Anything that could be derived from _P_ ∨ _Q_ ∨ _R_ could also be derived from _P_ ∨ _R_ . This sort of deletion is called _subsumption_ ; clause { _P, R_ } _subsumes_ { _P, Q, R_ }.

_Exercise 25_ Prove _(P_ ∧ _Q_ → _R)_ ∧ _(P_ ∨ _Q_ ∨ _R)_ → _((P_ ↔ _Q)_ → _R)_ by resolution. Show the steps of converting the formula into clauses.
