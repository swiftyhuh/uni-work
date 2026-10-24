<!-- page 1 -->
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

# 9 Unification

Unification is the operation of finding a common instance of two terms. Though the concept is simple, it involves a complicated theory. Proving the unification algorithm’s correctness (especially termination) is difficult.

To introduce the idea of unification, consider a few examples. The terms _f (x, b)_ and _f (a, y)_ have the common instance _f (a, b)_ , replacing _x_ by _a_ and _y_

<!-- page 2 -->
9 UNIFICATION

### 50

by _b_ . The terms _f (x, x)_ and _f (a, b)_ have no common instance, assuming that _a_ and _b_ are distinct constants. The terms _f (x, x)_ and _f (y, g(y))_ have no common instance, since there is no way that _x_ can have the form _y_ and _g(y)_ at the same time — unless we admit the infinite term _g(g(g(_ · · · _)))_ .

Only variables may be replaced by other terms. Constants are not affected (they remain constant!). If a term has the form _f (t, u)_ then instances of that term must have the form _f (t_′ _, u_′ _)_ , where _t_′ is an instance of _t_ and _u_′ is an instance of _u_ .

## 9.1 Substitutions

We have already seen substitutions informally. It is now time for a more detailed treatment.

Definition 17 A _substitution_ is a finite set of replacements

where _x_ 1, _. . ._ , _xk_ are distinct variables such that _ti_ ̸ = _xi_ for all _i_ = 1 _, . . . , k_ . We use Greek letters _φ_ , _θ_ , _σ_ to stand for substitutions.

The finite set { _x_ 1 _, . . . , xk_ } is called the _domain_ of the substitution. The domain of a substitution _θ_ is written dom _(θ)_ .

A substitution _θ_ = [ _t_ 1 _/x_ 1 _, . . . , tk/xk_ ] defines a function from the variables { _x_ 1 _, . . . , xk_ } to terms. Postfix notation is usual for applying a substitution; thus, for example, _xi θ_ = _ti_ . Substitutions may be applied to terms, not just to variables. Substitution on terms is defined recursively as follows:

Here _f_ is an _n_ -place function symbol. The operation substitutes in the arguments of functions, and leaves unchanged any variables outside of the domain of _θ_ .

Substitution may be extended to literals and clauses as follows:

Here _P_ is an _n_ -place predicate symbol (or its negation), while _L_ 1 _, . . . , L m_ are the literals in a clause.

<!-- page 3 -->
51

9.2 Composition of substitutions

Example 23 The substitution _θ_ = [ _h(y)/x, b/y_ ] says to replace _x_ by _h(y)_ and _y_ by _b_ . The replacements occur simultaneously; it does _not_ have the effect of replacing _x_ by _h(b)_ . Its domain is dom _(θ)_ = { _x, y_ }. Applying this substitution gives

## 9.2 Composition of substitutions

If _φ_ and _θ_ are substitutions then so is their _composition φ_ ◦ _θ_ , which satisfies

Can we write _φ_ ◦ _θ_ as a set of replacements? It has to satisfy the above for all relevant variables:

Thus it must be the set consisting of the replacements

_Equality_ of substitutions _φ_ and _θ_ is defined as follows: _φ_ = _θ_ if _xφ_ = _xθ_ for all variables _x_ . Under these definitions composition enjoys an associative law. It also has an identity element, namely [], the empty substitution.

Example 24 Let _φ_ = [ _j (x)/u,_ 0 _/y_ ] and _θ_ = [ _h(z)/x, g(_ 3 _)/y_ ]. Then dom _(φ)_ = { _u, y_ } and dom _(θ)_ = { _x, y_ }, so dom _(φ)_ ∪ dom _(θ)_ = { _u, x, y_ }. Thus

Notice that _y(φ_ ◦ _θ)_ = _(yφ)θ_ = 0 _θ_ = 0; the replacement _g(_ 3 _)/y_ has disappeared.

_Exercise 30_ Verify that ◦ is associative and has [] for an identity.

<!-- page 4 -->
52

9 UNIFICATION

## 9.3 Unifiers

Definition 18 A substitution _θ_ is a _unifier_ of terms _t_ 1 and _t_ 2 if _t_ 1 _θ_ = _t_ 2 _θ_ . More generally, _θ_ is a unifier of terms _t_ 1, _t_ 2, _. . ._ , _tm_ if _t_ 1 _θ_ = _t_ 2 _θ_ = · · · = _tmθ_ . The term _t_ 1 _θ_ is called the _common instance_ of the unified terms. A unifier of two or more literals is defined similarly.

Two terms can only be unified if they have similar structure apart from variables. The terms _f (x)_ and _h(y, z)_ are clearly non-unifiable since no substitution can do anything about the differing function symbols. It is easy to see that _θ_ unifies _f (t_ 1 _, . . . , tn)_ and _f (u_ 1 _, . . . , un)_ if and only if _θ_ unifies _ti_ and _ui_ for all _i_ = 1 _, . . . , n_ .

Example 25 The substitution [3 _/x, g(_ 3 _)/y_ ] unifies the terms _g(g(x))_ and _g(y)_ . The common instance is _g(g(_ 3 _))_ . These terms have many other unifiers, including the following:

|unifying substitution|common instance|
|---|---|
|[_f (u)/x, g( f (u))/y_]|_g(g( f (u)))_|
|[_z/x, g(z)/y_]|_g(g(z))_|
|[_g(x)/y_]|_g(g(x))_|

Note that _g(g(_ 3 _))_ and _g(g( f (u)))_ are instances of _g(g(x))_ . Thus _g(g(x))_ is more general than _g(g(_ 3 _))_ and _g(g( f (u)))_ ; it admits many other instances. Certainly _g(g(_ 3 _))_ seems to be arbitrary — neither of the original terms mentions 3! A separate point worth noting is that _g(g(x))_ is equivalent to _g(g(z))_ , apart from the name of the variable. Let us formalize these intuitions.

## 9.4 Most general unifiers

Definition 19 The substitution _θ_ is _more general_ than _φ_ if _φ_ = _θ_ ◦ _σ_ for some substitution _σ_ .

Example 26 Recall the unifiers of _g(g(x))_ and _g(y)_ . The unifier [ _g(x)/y_ ] is more general than the others listed, for
