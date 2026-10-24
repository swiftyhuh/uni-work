<!-- page 1 -->
58

10 APPLICATIONS OF UNIFICATION

- Here the antecedent is ∀ _x_ ∃ _y R(x, y)_ ; replacing _y_ by the Skolem function _f_ yields the clause { _R(x, f (x))_ }.

- The negation of the consequent is ¬ _(_ ∃ _y_ ∀ _x R(x, y))_ , which becomes ∀ _y_ ∃ _x_ ¬ _R(x, y)_ . Replacing _x_ by the Skolem function _g_ yields the clause {¬ _R(g(y), y)_ }.

Observe that _R(x, f (x))_ and _R(g(y), y)_ are not unifiable because of the occurs check. And so it should be, because the original formula is not a theorem!

_Exercise 31_ For each of the following pairs of terms, give a most general unifier or explain why none exists. Do not rename variables prior to performing the unification.

# 10 Applications of Unification

By means of unification, we can extend resolution to first-order logic. As a special case we obtain Prolog. Other theorem provers are also based on unification. Other applications include polymorphic type checking for the language ML.

## 10.1 Binary resolution

We now define the binary resolution rule with unification:

As before, the first clause contains _B_ and other literals, while the second clause contains ¬ _D_ and other literals. The substitution _σ_ is a unifier of _B_ and _D_ (almost always a _most general_ unifier). This substitution is applied to all remaining literals, producing the conclusion.

The variables in one clause are renamed before resolution to prevent clashes with the variables in the other clause. Renaming is sound because the scope of each variable is its clause. Resolution is sound because it takes an instance of each clause — the instances are valid, because the clauses are universally valid —

<!-- page 2 -->
59

10.2 Factoring

and then applies the propositional resolution rule, which is sound. For example, the two clauses

yield the empty clause in a single resolution step. This works by renaming variables — say, _x_ to _y_ in the second clause — and unifying _P(x)_ with _P(g(y))_ . Forgetting to rename variables is fatal, because _P(x)_ cannot be unified with _P(g(x))_ .

## 10.2 Factoring

In the general case, the resolution rule must perform _factoring_ . This uses additional unifications to identify literals in the same clause. Factoring can make the clause { _P(x, b), P(a, y)_ } behave like the clause { _P(a, b)_ }, since _P(a, b)_ is the result of unifying _P(x, b)_ with _P(a, y)_ .

The factoring unifications are done at the same time as the unification of the complementary literals in the two clauses. The binary resolution rule with factoring is

where _σ_ is the most general substitution such that

Resolution with factoring is _refutation complete_ : it will find a contradiction if there is one. Showing this is difficult.

The search space is huge: resolution with factoring can be applied in many different ways, every time. Modern resolution systems use highly complex heuristics to limit the search. Typically they only perform resolutions that can lead (perhaps after several steps) to very short clauses, and they discard the intermediate clauses produced along the way. Dozens of flags and parameters influence their operation.

Example 36 Let us prove ∀ _x_ ∃ _y_ ¬ _(P(y, x)_ ↔¬ _P(y, y))_ . Negate and expand the ↔, getting

Its negation normal form is

<!-- page 3 -->
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
