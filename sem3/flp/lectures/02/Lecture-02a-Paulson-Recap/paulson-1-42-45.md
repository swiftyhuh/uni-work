<!-- page 1 -->
### 42 8 SKOLEM FUNCTIONS AND HERBRAND’S THEOREM

_Exercise 26_ Using linear resolution, prove that _(P_ ∧ _Q)_ → _(R_ ∧ _S)_ follows from _P_ → _R_ and _R_ ∧ _P_ → _S_ .

_Exercise 27_ Convert these axioms to clauses, showing all steps. Then prove _Winterstorm_ → _Miserable_ by resolution:

_Rain_ ∧ _(Windy_ ∨¬ _Umbrella)_ → _Wet Winterstorm_ → _Storm_ ∧ _Cold Wet_ ∧ _Cold_ → _Miserable Storm_ → _Rain_ ∧ _Windy_

# 8 Skolem Functions and Herbrand’s Theorem

Propositional logic is the basis of many proof methods for first-order logic. Eliminating the quantifiers from a first-order formula reduces it nearly to propositional logic. This section describes how to do so.

## 8.1 Prenex normal form

The simplest method of eliminating quantifiers from formula involves first moving them to the front.

Definition 11 A formula is in _prenex normal form_ if and only if it has the form

where _A_ is quantifier-free, each _Qi_ is either ∀ or ∃, and _n_ ≥ 0. The string of quantifiers is called the _prefix_ and _A_ is called the _matrix_ .

Using the equivalences described above, any formula can be put into prenex normal form.

### Examples of translation.

The affected subformulæ will be underlined.

### Example 16 Start with

Pull out the ∃ _x_ :

<!-- page 2 -->
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

## 8.2 Removing quantifiers: Skolem form

Now that the quantifiers are at the front, let’s eliminate them! We replace every existentially bound variable by a Skolem constant or function. This transformation does not preserve the meaning of a formula; it does preserve _inconsistency_ , which is the critical property, since resolution works by detecting contradictions.

> 6Or simply pull out the quantifiers separately. Using the distributive law is marginally better here because it will result in only one Skolem constant instead of two; see the following section.

<!-- page 3 -->
44

8 SKOLEM FUNCTIONS AND HERBRAND’S THEOREM

### How to Skolemize a formula

Suppose the formula is in prenex normal form.7 Starting from the left, if the formula contains an existential quantifier, then it must have the form

where _A_ is a prenex formula, _k_ ≥ 0, and ∃ _y_ is the leftmost existential quantifier. Choose a _k_ -place function symbol not present in _A_ (that is, a _new_ function symbol). Delete the ∃ _y_ and replace all other occurrences of _y_ by _f (x_ 1 _, x_ 2 _, . . . , xk)_ . The result is another prenex formula:

If _k_ = 0 above then the prenex formula is simply ∃ _y A_ , and other occurrences of _y_ are replaced by a new constant symbol _c_ . The resulting formula is _A_ [ _c/y_ ].

The remaining existential quantifiers, if any, are in _A_ . Repeatedly eliminate all of them, as above. The new symbols are called _Skolem functions_ (or Skolem constants).

After Skolemization the formula is just ∀ _x_ 1 ∀ _x_ 2 · · · ∀ _xk A_ where _A_ is quantifier-free. Since the free variables in a formula are taken to be universally quantified, we can drop these quantifiers, leaving simply _A_ . We are almost back to the propositional case, except the formula typically contains terms. We shall have to handle constants, function symbols, and variables.

### Examples of Skolemization

The affected expressions are underlined.

Example 18 Start with

Eliminate the ∃ _x_ using the Skolem constant _a_ :

Eliminate the ∃ _z_ using the 1-place Skolem function _f_ :

Finally, drop the ∀ _y_ and convert the remaining formula to a clause:

> 7This makes things easier to follow. However, some proof methods merely require the formula to be in negation normal form. The basic idea is the same: remove the outermost existential quantifier, replacing its bound variable by a Skolem term. Pushing quantifiers in as far as possible, instead of pulling them out, yields a better set of clauses.

<!-- page 4 -->
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

### Correctness of Skolemization

Skolemization does _not_ preserve meaning. The version presented above does not even preserve validity! For example,

is valid. (Why? In any model, the required value of _x_ exists — it is just the value of _a_ in that model.)

Replacing the ∃ _x_ by the Skolem constant _b_ gives

This has a different meaning since it refers to a constant _b_ not previously mentioned. And it is not valid! For example, it is false in the interpretation where _P(x)_ means ‘ _x_ equals 0’ and _a_ denotes 0 and _b_ denotes 1.

Our version of Skolemization does preserve _consistency_ — and therefore inconsistency. Consider one Skolemization step.
