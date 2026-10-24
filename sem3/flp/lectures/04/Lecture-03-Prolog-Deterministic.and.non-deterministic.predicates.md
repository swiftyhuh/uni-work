<!-- page 1 -->
# Lecture 3 - Deterministic and non-deterministic predicates

# Content

1. Deterministic and non-deterministic predicates

- 1.1 Predefined predicates

- 1.2 Collect all solutions

- 1.3 Negation - “not”, “\+”

- 1.4 Lists and recursion

- 1.4.1 Head & tail of a list

- 1.4.2 List processing

- 1.4.3 Using lists

2. Examples

# Bibliography

Czibula, G., Pop, H.F., Elemente avansate de programare în Lisp şi Prolog. Aplicaţii în Inteligenţa Artificială, Ed. Albastră, ClujNapoca, 2012

1

<!-- page 2 -->
# 1. Deterministic and non-deterministic predicates

Types of predicates, ideal implementation:

- deterministic

   - a deterministic predicate has only one solution

- non-deterministic `o` an non-deterministic predicate has several solutions

# SWI Prolog implementation:

- A deterministic predicate always succeeds exactly once and does not leave a choicepoint.

- A semi-deterministic predicate succeeds at most once. If it succeeds it does not leave a choicepoint.

- A non-deterministic predicate is the most general case and no claims are made on the number of solutions and whether or not the predicate leaves a choicepoint on the last solution.

<u>Remark.</u> A predicate can be deterministic in one flow model, and non-deterministic in other flow models.

# 1.1 Predefined predicates

<mark>var (X) = true if X is free, false if bound number (X) = true if X is bound to a number integer (X) = true if X is bound to an integer float (X) = true if X is bound to a real number atom (X) = true if X is bound to an atom atomic (X) = atom (X) or number (X)</mark>

2

<!-- page 3 -->
# 1.2 Collect all solutions

Prolog provides ways to collect in a list all the solutions of a predicate.

findall (X, goal_on_X, L) setof (X, goal_on_X, L) bagof (X, goal_on_X, L)

They have the following parameters:

- the first parameter specifies the predicate parameter to be collected in the list;

- the second parameter specifies the predicate to be solved;

- the third parameter specifies the list where all the solutions will be collected.

The difference between these three predicates follows:

- findall

   - collects all the solutions of X in L

   - any variable in goal not in the first argument is not instantiated

- setof

   - removes from L all duplicate outputs and answers are sorted

   - any variable in goal not in the first argument results in separate solutions

- bagof

   - does not remove from L duplicates and the answers may not be sorted

   - any variable in goal not in the first argument results in separate solutions

3

<!-- page 4 -->
# <u>EXAMPLE 1:</u>

p (a, b). p (b, c). p (a, c). p (a, d). all (X, L) :- findall (Y, p (X, Y), L).

?- all (a, L). L = [b, c, d]

# <u>EXAMPLE 2:</u>

age(peter, 7). age(ann, 5). age(pat, 8). age(tom, 5). age(ann, 5).

# ?- setof(Child, age(Child, Age), Results).

Age = 5

Results = [ann, tom] ;

Age = 7

Results = [peter] ;

Age = 8 Results = [pat] .

4

<!-- page 5 -->
# ?- bagof(Child, age(Child, Age), Results).

Age = 5

Results = [ann, tom, ann] ;

Age = 7

Results = [peter] ;

Age = 8

Results = [pat] .

# ?- findall(Child, age(Child, Age), Results).

Results = [peter, ann, pat, tom, ann] .

A way to group parameters in pairs uses the notation A/B or A-B :

?- setof(Age/Child, age(Child, Age), Results).

Results = [5/ann, 5/tom, 7/peter, 8/pat].

# ?- setof(Age-Child, age(Child, Age), Results).

Results = [5-ann, 5-tom, 7-peter, 8-pat].

# ?- bagof(Age/Child, age(Child, Age), Results).

Results = [7/peter, 5/ann, 8/pat, 5/tom, 5/ann].

# ?- findall(Age/Child, age(Child, Age), Results).

Results = [7/peter, 5/ann, 8/pat, 5/tom, 5/ann].

5

<!-- page 6 -->
# 1.3 Negation - “not”, “\+”

Negation is true if the subgoal fails (can't be proven to be true).

not (subgoal (Arg1, ..., ArgN)) \+ subgoal (Arg1, ..., ArgN)

?- \+ (2 = 4). ?- not (2 = 4). true. true.

# 1.4 Lists and recursion

In Prolog, a list is an object that contains an arbitrary number of other objects. The lists in SWI-Prolog are heterogeneous (the component elements can have different types). Lists are built using square brackets. Their elements are separated by a comma.

Here are some examples:

[1, 2, 3] [dog, cat, canary] [“valerie ann”,“jennifer caitlin”,“benjamin thomas”]

If we were to declare the type of a (homogeneous) list with integer elements, we would use a domain declaration of the following type

element = integer list = element *

6

<!-- page 7 -->
# 1.4.1 Head & tail of a list

A list is a recursive object. It consists of two parts: the head, which is the first element of the list, and the tail, which is the rest of the list. The head of the list is an element, and the tail is a list:

The head of the list [a, b, c] is The tail of [a, b, c] is [b, c] The head of the list [c] is c The tail of [c] is []

The empty list [] cannot be split into head and tail.

# 1.4.2 List processing

Prologue provides a way to make the head and tail of a list explicit. Instead of separating the elements of a comma list, we will separate the head of the queue with the character '|'.

For example, the following lists are equivalent:

[a b c] [a | [b, c]] [a | [b | [c]]] [a | [b | [c | []]]]

Also, before the '|' sign several elements may be written, not just the first. For example, the list [a, b, c] above is equivalent to

[a | [b, c]] [a, b | [c]] [a, b, c | []]

- Following the unification of list [a, b, c] with list [H | T] (H, T being free variables)

   - H binds to a; T binds to [b, c]

- Following the unification of list [a, b, c] with list [H | [H1 | T]] (H, H1, T being free variables)

   - H binds to a; H1 binds to b; T binds to [c]

7

<!-- page 8 -->
# 1.4.3 Using lists

Because a list is a recursive data structure, recursive algorithms are needed to process it. The basic way to process the list is to work with it, performing certain operations with each element of it, until the end is reached.

Such an algorithm generally needs two clauses. One of them says what to do with an empty list. The other says what to do with a non-empty list, which can be broken down in its head and its tail.

8

<!-- page 9 -->
# 2. Examples

<u>EXAMPLE 2.1</u> Given a non null natural number N, compute F = N!. Simulate the iterative computation process.

_I_  1 _P_  1

While _I_ < _N_ do

_I_  _I_ + 1 _P_  _P_ * _I_

End While

_F_  _P_

The description is not directly recursive, collector variables (i, P) are used

% fact (N: integer, F: integer) % (i, i), (i, o) - deterministic fact (N, F) :- fact_aux (N, F, 1, 1).

% fact_aux (N: integer, F: integer, I: integer, P: integer) % (i, i, i, i), (i, o, i, i) - deterministic

fact_aux (N, F, N, F) :- !. % fact_aux (N, F, I, P) :- I is N, F is P,!. fact_aux (N, F, I, P) :- NewI is I + 1,

NewP is P * NewI, fact_aux (N, F, NewI, NewP).

9

<!-- page 10 -->
The result is a tail recursion. All cycling variables were introduced as arguments to the fact_aux predicate.

# <u>HOMEWORK:</u>

Consider a factorial predicate (N, F) that works in all four flow models (i, i), (i, o), (o, i), (o,o). What are the difficulties here?

10

<!-- page 11 -->
<u>EXAMPLE 2.2</u> Verify the membership of an item in a list.

% (i, i)

To describe the membership in a list we will construct the member predicate (element, list) which will investigate whether a certain element is a member of the list. The algorithm to be implemented would (declaratively) be the following:

1. E is a member of the list L if it is its head.

2. Otherwise, E is a member of the list L if it is a member of the tail of L.

From a procedural point of view:

1. To verify that E is a member of the list L, verify that it is the head of L;

2. Otherwise, verify that it is a member of the tail of L.

Alternatively:

1. To find a member of the list L, find its head;

2. Otherwise, find a member of its tail.

𝑓𝑎𝑙𝑠𝑒     𝑖𝑓 𝑖𝑠 𝑒𝑚𝑝𝑡𝑦 𝑡𝑟𝑢𝑒     𝑖𝑓 𝑙1 = 𝐸 𝑚𝑒𝑚𝑏𝑒𝑟(𝐸, 𝑙1𝑙2 … 𝑙𝑛) = {𝑚𝑒𝑚𝑏𝑒𝑟(𝐸, 𝑙2 … 𝑙𝑛) 𝑜𝑡ℎ𝑒𝑟𝑤𝑖𝑠𝑒

# Version 1

% member1(e: element, L: list)

% (i, i) - (non) deterministic

% (o, i) - non-deterministic

11

<!-- page 12 -->
member1(E, [E | _]). member1(E, [_ | L]) :- member1(E, L).

# Version 2

% member2 (e: element, L: list) % (i, i) - deterministic %(o, i) - deterministic

member2(E, [E | _]) :- !. member2(E, [_ | L]) :- member2(E, L).

# Version 3

% member3 (e: element, L: list) % (i, i) - (non) deterministic % (o, i) - non-deterministic

member3(E, [_ | L]) :- member3(E, L). member3(E, [E | _]).

?- member3(E, [1,2,3]). E = 3; E = 2; E = 1.

?-member3 (4, [1,2,3]). false.

12

<!-- page 13 -->
# ?- member3 (2, [1,2,3]).

true;

false.

As it can be seen, the predicate member it also works in the flow model (o, i), in which it is non-deterministic .

13

<!-- page 14 -->
# <u>EXAMPLE 2.3 Add an item at the end of a list.</u>

? add (3, [1, 2], L). L = [1, 2, 3]

Recursive formula:

𝑎𝑑𝑑(𝑒, 𝑙1𝑙2 … 𝑙𝑛) = {(𝑒)     𝑑𝑎𝑐𝑎 𝑙 𝑒 𝑣𝑖𝑑𝑎 𝑙1 ⊕𝑎𝑑𝑑(𝑒, 𝑙2 … 𝑙𝑛) 𝑎𝑙𝑡𝑓𝑒𝑙

# Version 1

% add (e: element, L: list, LRez: list) % (i, i, o) – deterministic

add (E, [], [E]). add (E, [H | T], [H | Rez]) :- add (E, T, Rez). % add (E, [H | T], Rez) :- % add (E, T, L), Rez = [H | L].

# Version 2

% add (L: list, e: element, LRez: list) % (i, i, o) – deterministic

add ([], E, [E]). add ([H | T], E, [H | Rez]) :- add (T, E, Rez). % add ([H | T], E, Rez) :- % add (T, E, L), Rez = [H | L].

The time complexity of the operation of adding an item to the end of the list of a list of n items is  (n).

14

<!-- page 15 -->
# <u>EXAMPLE 2.4 Determine the inverse of a list.</u>

% inverse (L: list, LRez: list) % (i, o) – deterministic

inverse ([], []). inverse ([H | T], Rez) :- inverse (T, L), add (H, L, Rez).

The time complexity of the operation of reversing a list of n elements (using the addition at the end) is  (n2 ).

<u>Version B</u> <u>(with collector variable)</u>

𝑖𝑛𝑣𝑒𝑟𝑠_𝑎𝑢𝑥(𝑙1𝑙2 … 𝑙𝑛, 𝐶𝑜𝑙) = {    𝐶𝑜𝑙                          𝑑𝑎𝑐𝑎 𝑙 𝑒 𝑣𝑖𝑑𝑎𝑖𝑛𝑣𝑒𝑟𝑠_𝑎𝑢𝑥(𝑙2 … 𝑙𝑛, 𝑙1 ⊕𝐶𝑜𝑙)  𝑎𝑙𝑡𝑓𝑒𝑙 𝑖𝑛𝑣𝑒𝑟𝑠(𝑙1𝑙2 … 𝑙𝑛) = 𝑖𝑛𝑣𝑒𝑟𝑠_𝑎𝑢𝑥(𝑙1𝑙2 … 𝑙𝑛,  )

% inverse (L: list, LRez: list) % (i, o) – deterministic

inverse (L, Rez) :- invers_aux ([], L, Rez).

15

<!-- page 16 -->
% invers_aux (Col: list, L: list, LRez: list)

% Col is the collector

% (i, i, o) - deterministic

invers_aux (Col, [], Col). invers_aux (Col, [H | T], Rez) :- invers_aux ([H | Col], T, Rez).

The time complexity of the operation of reversing a list of n elements (using a collector variable) is  (n).

<u>Remark.</u> Using a collector variable does not lead to a decrease in complexity in all cases. There are situations in which the use of a collector variable increases the complexity (ex: the addition in collectors is done at the end of it, not at the beginning).

16

<!-- page 17 -->
<u>EXAMPLE 2.5 Determine the list of even items in a list (keep</u> the order of the items in the original list).

<u>Version A</u> <u>(direct recursion)</u>

% even (L: list, LRez: list) % (i, o) – deterministic

even([], []). even([H | T], [H | Rez]) :- H mod 2 =: = 0, !, even(T, Rez). even([_ | T], Rez) :- even(T, Rez).

The time complexity of the operation is  (n), n being the number of items in the list.

<u>Version B</u> <u>(with collector variable)</u>

𝑒𝑣𝑒𝑛_𝑎𝑢𝑥(𝑙1𝑙2 … 𝑙𝑛, 𝐶𝑜𝑙)

𝐶𝑜𝑙                          𝑑𝑎𝑐𝑎 𝑙 𝑒 𝑣𝑖𝑑𝑎 𝑒𝑣𝑒𝑛_𝑎𝑢𝑥(𝑙2 … 𝑙𝑛, 𝐶𝑜𝑙⊕𝑙1)  𝑑𝑎𝑐𝑎 𝑙1  𝑝𝑎𝑟 = { 𝑒𝑣𝑒𝑛_𝑎𝑢𝑥(𝑙2 … 𝑙𝑛, 𝐶𝑜𝑙)      𝑎𝑙𝑡𝑓𝑒𝑙 𝑒𝑣𝑒𝑛(𝑙1𝑙2 … 𝑙𝑛) = 𝑒𝑣𝑒𝑛_𝑎𝑢𝑥(𝑙1𝑙2 … 𝑙𝑛,  )

17

<!-- page 18 -->
% even (L: list, LRez: list) % (i, o) – deterministic

even(L, Rez) :- even_aux (L, Rez, []).

% even_aux(L: list, LRez: list, Col: list) % (i, o, i) – deterministic

even_aux ([], Rez, Rez). even_aux ([H | T], Rez, Col) :- H mod 2 =: = 0, !, add (H, Col, ColN), % add at the end even_aux (T, Rez, ColN). even_aux ([_ | T], Rez, Col) :- even_aux (T, Rez, Col).

The time complexity of the operation is  (n2), n being the number of items in the list.

18

<!-- page 19 -->
# <u>EXAMPLE 2.6</u> Given a numerical list, determine the list of strictly ascending pairs of elements in the list.

?- pairs ([2, 1, 3, 4], L) L = [[2, 3], [2, 4], [1, 3], [1, 4], [3, 4]]

?- pairs ([5, 4, 2], L) false

We will use the following predicates:

- the nondeterministic predicate pair (element, list, list) (flow model (i, i, o)), which will produce pairs in ascending order between the given element and elements of the argument list

?- pair (2, [1, 3, 4], L) L = [2, 3] L = [2, 4]

𝑝𝑎𝑖𝑟(𝑒, 𝑙1𝑙2 … 𝑙𝑛) = 1. (e, 𝑙1)                𝑒< 𝑙1 2. 𝑝𝑎𝑖𝑟(𝑒, 𝑙2 … 𝑙𝑛)

% pair (E: element, L: list, LRez: list) % (i, i, o) – non-deterministic

pair (A, [B | _], [A, B]) :- A  B. pair (A, [_ | T], P) :- pair (A, T, P).

19

<!-- page 20 -->
- the nondeterministic predicate pairs (list, list) (flow model (i, o)), which will produce pairs in ascending order between the elements of the argument list

? pairs ([2, 1, 4], L) L = [2, 4] L = [1, 4]

𝑝𝑎𝑖𝑟𝑠(𝑙1𝑙2 … 𝑙𝑛) = 1. 𝑝𝑎𝑖𝑟(𝑙1,𝑙2 … 𝑙𝑛) 2. 𝑝𝑎𝑖𝑟𝑠(𝑙2 … 𝑙𝑛)

% pairs (L: list, LRez: list) % (i, o) – non-deterministic

pairs ([H | T], P) :- pair(H, T, P). pairs ([_ | T], P) :- pairs(T, P).

- the main predicate allPairs (list, listRez) (flow model (i, o)), which will collect all solutions of the nondeterministic predicate pairs.

% allPairs (L: list, LRez: list) % (i, o) –deterministic

allPairs (L, LRes) :- findall (X, pairs (L, X), LRez).

20
