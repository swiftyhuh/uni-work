<!-- page 1 -->
# <u>Remark:</u>

a(X) :‐ b(X), !, c(X). a(X) :‐ (b(X) ‐> c(X) ; d(X)). a(X) :‐ d(X).

If b(X) succeeds, then run c(X). Even if c(X) fails, do not try d(X). If b(X) fails, then run d(X).

1.2 The predicate ʺfailʺ

The evaluation of _fail_ is failure. This encourages backtracking. Its effect is the same as that of an impossible predicate, such as 2 = 3. Consider the following example:

predicate (a, b). all :‐ predicate (c, d). predicate (X, Y), predicate (e, f). write (X), write (Y), nl, fail.

all1 :‐ predicate (X, Y), write (X), write (Y), nl.

The predicates all and all1 are without parameters, and as such the system will have to answer whether there exist X and Y such that these predicates hold.

?‐ all. ?‐ all1. ab ab cd true ; ef cd false . true ; ef true.

9

<!-- page 2 -->
? ‐predicate (X, Y). X = a, Y = b; X = c, Y = d; X = e, Y = f.

The fact that the predicate call all ends with fail (which always fails) forces Prolog to start backtracking through the body of the rule all . Prolog will return to the last call which can provide more solutions. The write predicate cannot give other solutions, so it returns to the call of predicate .

# <u>Remarks</u> <u>.</u>

- That false from the end of the solutions means that the predicate all has not been satisfied.

- There is no point in writing a predicate after fail , because Prolog will never get to execute it.

Note. The following sequences are equivalent:

as long as _condition_ executes predicate :‐ _body condition_ , _body_ , fail.

10

<!-- page 3 -->
# EXAMPLE

Consider the following Prolog code

% q (E: integer) % (o) – non‐deterministic q (1). q (2). q (3). q (4). p :‐ q (I), I <3, write (I), nl,fail.

What is the result of the question

?‐ p.

considering that fail occurs / does not occur at the end of last clause?

- with fail at the end of the clause, the solutions are 1 2

false

 without fail at the end of the clause, the solutions are 1 true; 2 true; false

11

<!-- page 4 -->
# 1.3. Cut followed by fail

First:

a(X) :‐ b(X), !, c(X), fail. a(X) :‐ d(X). b(1). b(4). c(1). c(3). d(4).

?‐ a(X). false.

1. a(X) first tries its first clause.

2. b(X) succeeds with its first solution, so X = 1.

3. The cut ! is then executed.

4. This commits Prolog to the current clause and to the current solution of b(X).

5. c(1) succeeds.

6. fail then forces the whole clause to fail.

7. Prolog tries to backtrack, but the cut prevents returning to b(4).

8. The cut also prevents trying the second clause a(X) :‐ d(X).

9. Therefore d(4) is never reached.

10. The query ?‐ a(X). finally returns false.

# Second:

a(X) :‐ b(X), !, c(X). a(X) :‐ d(X). b(1). b(4). c(1). c(3). d(4).

12

<!-- page 5 -->
# ?‐ a(X).

X = 1.

1. a(X) first tries its first clause.

2. b(X) succeeds with its first solution, so X = 1.

3. The cut ! is then executed.

4. This commits Prolog to the current clause and to b(1).

5. c(1) succeeds, so the query succeeds with X = 1.

6. If more solutions are requested, Prolog tries to backtrack.

7. The cut prevents returning to b(4).

8. It also prevents trying the second clause a(X) :‐ d(X).

9. Therefore no solution with X = 4 is produced.

10. The only answer is X = 1.

# Third:

a(X) :‐ b(X), c(X), fail.

a(X) :‐ d(X).

b(1). b(4).

c(1). c(3).

d(4).

?‐ a(X).

X = 4.

1. a(X) first tries its first clause.

2. b(X) succeeds with X = 1.

3. c(1) succeeds.

4. fail then forces this branch to fail.

5. Prolog backtracks to c(1), with no other matching c facts.

6. It then backtracks to b(X) and tries b(4).

13

<!-- page 6 -->
7. c(4) fails, so the first clause of a() is exhausted.

8. Prolog then tries the second clause a(X) :‐ d(X).

9. d(4) succeeds, so the final answer is X = 4.

- !, fail The cut‐fail combination “If you reach here, you should stop trying to satisfy this goal. Return false.”

# What about these ones?

a(X):‐ b(X), !, fail.

1. b(X) is called first.

2. If b(X) succeeds, say with X = 1, Prolog reaches !.

3. The cut commits to that solution of b(X) and to this clause of a().

4. Then fail forces the clause to fail.

5. Because of the cut, Prolog cannot backtrack to another solution of b(X).

6. So if this is the only clause of a(), a(X) fails completely.

not(A) :‐ A, !, fail.

not(_).

1. Prolog first tries the first clause.

2. A is called as a goal.

3. If A succeeds, the cut ! commits to the first clause.

4. fail is then executed, so not(A) fails.

5. Because of the cut, Prolog cannot try the second clause.

6. If A fails, execution never reaches the cut.

7. Prolog then tries the second clause not(_).

8. That clause always succeeds.

14

<!-- page 7 -->
# Other examples:

is_integer(0). is_integer(X) :‐ is_integer(Y), X is Y+1.

?‐ is_integer(X).

X = 0; X = 1; X = 2; …

?‐ member(a, [a,b,a,a,b]).

true;

true; true; false.

15

<!-- page 8 -->
# 2. Simple objects and composed objects

# Simple objects

A simple object is either a variable or a constant. A constant is either a character, a number, or an atom (symbol or string).

Prolog variables are local, not global. That is, if two clauses each contain a variable called X, the two variables are distinct and usually have no effect on each other.

# Composed objects and functors

Composed objects allow us to treat more information as a single element, in such a way that we can also use it by the components themselves. Consider, for example, the date of _2 February 1998_ . It consists of three pieces of information, day, month and year, but it is useful to treat it as a single object with a tree structure:

This can be done by writing the composed object as follows:

date (2, “February”, 1998)

This looks like a Prolog fact, but it is only an object (a given data) that we can handle in the same way as a symbol or a number. Syntactically, it starts with a name (or functor , in this case the word date ) followed by three arguments.

16

<!-- page 9 -->
Note. The functor in Prolog is not the same as the function in other programming languages. Itʹs just a name that identifies a type of composed data and holds the arguments together.

The arguments of a composed data can be composed themselves. Here is an example:

birth (person (“Ioan”, “Popescu”), date (2, “February”, 1918))

Unification of composed objects

A composed object can be unified with either a simple variable or a composed object that matches it. E.g,

date (2, “February”, 1998)

matches the free variable X and results in the binding of X to date (...). The above composed object also matches

date (Day, Mon, Year)

and results in linking the variable Day to the value 2, the variable Mon to the value “February” and the variable Year to the value 1998.

# <u>Remarks</u>

- We agree to use the following statement to specify an alternative domain

   - % domain = alternative1(dom, dom, ..., dom); % alternative2(dom, dom, ..., dom); % ...

17

<!-- page 10 -->
- Functors can be used to control arguments that may have multiple types

% element = i (integer); r (real); s (string)

Heterogeneous list

In SWI‐Prolog the lists are heterogeneous, the component elements can be of different types. To determine the type of an element of the list, predefined predicates are used in SWI ( number , is_list , etc.) .

<u>Version 1.</u> A heterogeneous list of numbers, symbols and / or lists of numbers is given. Determine the sum of the numbers in the heterogeneous list.

?‐ sum ([1, a, [1,2,3], 4], S). S = 11.

?‐ sum ([a, b, []], S). S = 0.

% (L: list of numbers, S: number) % (i, o) ‐ deterministic

sumlist ([], 0). sumlist ([H | T], S) :‐ sumlist (T, S1), S is S1 + H.

18

<!-- page 11 -->
% (L: list, S: number) % (i, o) ‐ deterministic sum ([], 0). sum ([H | T], S) :‐ number (H), !, sum (T, S1), S is H + S1. sum ([H | T], S) :‐ is_list (H), !, sumlist (H, S1), sum (T, S2), S is S1 + S2. sum ([_ | T], S) :‐ sum (T, S).

<u>Version 2.</u> Another (more general) possibility to manage heterogeneous lists is using composed objects / functors.

?‐ sum ([n(1), s(a), l([1,2,3]), n(4)], S). S = 11.

?‐ sum ([s(a), s(b), l([])], S). S = 0.

% (L: list of numbers, S: number) % (i, o) ‐ deterministic sumlist ([], 0). sumlist ([H | T], S) :‐ sumlist (T, S1), S is S1 + H.

19

<!-- page 12 -->
% (L: list, S: number) % (i, o) ‐ deterministic sum ([], 0). sum ([n(H) | T], S) :‐ !,

sum (T, S1), S is H + S1.

sum ([l(H) | T], S) :‐ !, sumlist (H, S1), sum (T, S2), S is S1 + S2.

sum ([_ | T], S) :‐ % _ is enough, the head here is necessarily s(_) sum (T, S).

A list of integers and / or symbols is given. Determine the sum of even integers in the list.

? ‐ sum ([i(1), s(a), i(2)], S). S = 2.

? ‐ sum ([s(a), s(b), i(1)], S). S = 0.

20

<!-- page 13 -->
% sum (L: heterogeneous list, S: number) % (i, o) – deterministic

sum([], 0).

% when i(H) is the head of the list, and H is even,

% add it to the sum sum([i(H) | T], S) :‐ H mod 2 =:= 0, !, sum (T, S1), S is S1 + H.

% anything other than i(H) is ignored when computing the sum sum ([_ | T], S) :‐ sum (T, S1).

% sum([s(H) | T], S) :‐ … is not explicitly required,

% since the symbols do not participate in the sum

21

<!-- page 14 -->
# 3. Examples

<u>EXAMPLE 3.1</u> Write a predicate that concatenates two lists.

- ? concatenate ([1, 2], [3, 4], L). L = [1, 2, 3, 4].

To combine the lists L1 and L2 to form the list L3 we will use a recursive algorithm such as:

1. If L1 = [] then L3 = L2.

2. Otherwise, the head of L3 is the head of L1 and the tail of L3 is obtained by combining the tail of L1 with the list L2.

Letʹs explain this algorithm a little bit. Let the lists be L1 = [a1, ..., an] and L2 = [b1, ..., bm]. Then the list L3 will have to be L3 = [a1, ..., an, b1, ..., bm] or, if we separate it in its head and tail, L3 = [a1 | [a2, ..., an, b1, ..., bm]]. It follows that:

1. the head of list L3 is the head of list L1;

2. the tail of the list L3 is obtained by concatenating the tail of the list L1 with the list L2.

Furthermore, since the recursion consists in reducing the complexity of the problem by shortening the first list, it follows that the exit from recursion will take place with the exhaustion of the list L1, so when L1 is []. Note that the inverse condition, namely if L2 is [] then L3 is L1, is not necessary.

The SWI‐Prolog program is as follows:

% concatenate (L1: list, L2: list, L3: list)

% (i, i, o) ‐ deterministic

22

<!-- page 15 -->
concatenate ([], L, L). concatenate ([H | L1], L2, [H | L3]) :‐ concatenate (L1, L2, L3).

We remark that the concatenation predicate described above works with several flow models, being non‐deterministic in some flow models, and deterministic in others.

Consider, as example, the following questions:

? concatenate (L1, L2, [1, 2, 3]). % flow model (o, o, i) – non‐deterministic L1 = [] L2 = [1, 2, 3] L1 = [1] L2 = [2, 3]

- ? concatenate (L, [3, 4], [1, 2, 3, 4]). % flow model (o, i, i) or (i, o, i) ‐ deterministic L = [1, 2]

23

<!-- page 16 -->
<u>EXAMPLE 3.2</u> Write a predicate that determines the list of subsets of a list represented as a set.

? subsets ([1, 2], L) will produce L = [[], [2], [1], [1, 2]]

Remark: If the list is empty, its subset is the empty list. To determine the subsets of a list [E | L], which has the head E and the tail L, we will proceed as follows:

- i. determine a subset of the list L

- ii. place the element E on the first position in a subset of the list L

𝑠𝑢𝑏𝑠𝑒𝑡�𝑙�, 𝑙�, … , 𝑙��� 1. ∅                           𝑖𝑓 𝑙 𝑖𝑠 𝑒𝑚𝑝𝑡𝑦 2. 𝑠𝑢𝑏𝑠𝑒𝑡�𝑙�, … , 𝑙�� 3. 𝑙� ⨁ 𝑠𝑢𝑏𝑠𝑒𝑡�𝑙�, … , 𝑙��

We will use the non‐deterministic subset predicate that will generate the subsets one by one, after which all its solutions will be collected, using the findall predicate.

% subset (L: list, S: list) % (i, o) – non‐deterministic

subset ([], []). subset ([_ | T], S) :‐ subset (T, S). subset ([H | T], [H | S]) :‐ subset (T, S).

24

<!-- page 17 -->
% subsets (L: list, S: list of lists) % (i, o) – deterministic

subsets (L, Ld) :‐ findall (X, subset(L, X), Ld).

25

<!-- page 18 -->
<u>EXAMPLE 3.3</u> Given a set of numbers (represented as a list), write two predicates to return all the subsets of an even / odd sum.

|% sEven (L: list of numbers, L: list of numbers) % (i, o) – non‐deterministic|% sOdd (L: list of numbers, L: list of numbers) % (i, o) – non‐deterministic|
|---|---|
|sEven ([], []). sEven ([_ | T], S) :‐ sEven (T, S). sEven ([H | T], [H | S]) :‐ H mod 2 =:= 0, !, sEven (T, S). sEven ([H | T], [H | S]) :‐ sOdd(T,S).|sOdd ([H], [H]) :‐ H mod 2 =\= 0, !. sOdd ([_ | T], S) :‐ sOdd (T, S). sOdd ([H | T], [H | S]) :‐ H mod 2 =:= 0, !, sOdd (T, S). sOdd ([H | T], [H | S]) :‐ sEven(T,S).|
|?‐ sEven ([1, 2, 3], S).|?‐ sOdd ([1, 2, 3], S).|
|[]|[3]|
|[2]|[2. 3]|
|[1, 3]|[1]|
|[1, 2, 3]|[1, 2] false|

26

<!-- page 19 -->
<u>EXAMPLE 3.4</u> Consider the following definitions of predicates. What is the effect of the following query?

?‐ det([1,2,1,3,1,7,8], 1, L).

% det( L:list of elements, E:element, LRez: list of numbers) %(i, i, o) – deterministic

det(L, E, LRez) :‐

det_aux(L, E, LRez, 1).

% det_aux(L: list of elem, E: elem, LRez: list of numbers, P:integer) % (i, i, o, i) ‐ deterministic

det_aux([], _, [], _).

det_aux([E|T], E, [P|LRez], P) :‐ !, P1 is P+1, det_aux(T, E, LRez, P1).

det_aux([_|T], E, LRez, P) :‐ P1 is P+1, det_aux(T, E, LRez, P1).

Version without cut. What is the difference?

det(L, E, LRez) :‐ det_aux(L, E, LRez, 1).

det_aux([], _, [], _).

27

<!-- page 20 -->
det_aux([H|T], E, [P|LRez], P) :‐ H = E, P1 is P+1, det_aux(T, E, LRez, P1).

det_aux([H|T], E, LRez, P) :‐ H \= E, P1 is P+1, det_aux(T, E, LRez, P1).

<u>A solution to avoid the repeated call to det_aux</u> is to use an auxiliary predicate. _Think in terms of a common factor in a logical proposition._

det_aux([], _, [], _). det_aux([H|T], E, LRez, P) :‐ P1 is P+1, det_aux(T, E, L, P1), det_second(H, E, P, L, LRez).

% det_second(H: elem, E: elem, P: nr, L:list, LRez: list of nr) % (i, i, i , i, o) ‐ deterministic

det_second(E, E, P, L, [P| L]) :‐ !.

det_second(_, _, _, L, L).

28
