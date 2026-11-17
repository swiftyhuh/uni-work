<!-- page 1 -->
# `Lecture 6 – Database manipulation & Backtracking

1. Database manipulation

There are four database manipulation predicates: assert , retract , asserta , assertz .

listing displays the contents of the internal database listing(…) assert( _fact_ ) adds _fact_ to the internal database

assert( ( _rule_ ) ) adds _rule_ to the internal database

asserta(…) places asserted material at the _beginning_ of the database

assertz(…) places asserted material at the _end_ of the database

retract( _fact_ ) removes the first occurrence of _fact_ from the internal database

retract( _fact_ (_)), fail. removes all occurrences of _fact_ .

Predicates that are modified this way need to be declared using the dynamic directive:

:- dynamic predicate/arity.

1

<!-- page 2 -->
# Example:

Start with this directive and consider this predicate definition:

:- dynamic sum/3.

additiontable(A) :- member(B, A), member(C, A), D is B+C, assertz(sum(B, C, D)), fail.

The following goal fails, but there is a side effect on the database.

?- additiontable([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]).

The database now contains:

sum(0,0,0). sum(0,1,1). sum(0,2,2). sum(0,3,3). sum(0,4,4). sum(0,5,5). sum(0,6,6). …

The following goal removes all these facts from the database:

?- retract(sum(_, _, _)), fail.

2

<!-- page 3 -->
# 2. Backtracking

# Backtracking method:

- generally applicable to problems that have several solutions.

- allows the generation of all solutions to a problem

- depth first search in the space of solutions to the problem

- may have exponential time complexity

- general method for solving problems in the class of Constraint Satisfaction Problems (CSP)

- Prolog is suitable for solving CSP class problems

   - the control structure used by the Prolog interpreter is based on backtracking

# <u>Formalization</u>

- the problem solution is represented as a list/vector ( _x1_ , ..., _xn_ ), with _xi_ ∈ _Di_

- the solution vector is incrementally generated

- we denote by _col_ the list that collects a solution to the problem

- we denote by final the predicate verifying whether the _col_ list is a solution to the problem

- we denote by constraints the predicate verifying whether the _col_ list may lead to a solution of the problem

To determine a solution to the problem, the following cases are possible:

- i. if _col_ satisfies final , then there is a solution to the problem;

- ii. otherwise, we extend _col_ with an element _e_ (which we will call candidate ) such that col ⊕ _e_ satisfies constraints

3

<!-- page 4 -->
# Remarks

- if the generation of the element _e_ the _col_ collector at point ii will be extended with is non-deterministic, then all solutions to the problem will be generated

- there are problems with no final conditions imposed

The general recursive model for generating solutions is:

𝑠𝑜𝑙𝑢𝑡𝑖𝑜𝑛(𝑐𝑜𝑙) = 1.  𝑐𝑜𝑙                                       𝑖𝑓 𝑐𝑜𝑙 𝑣𝑒𝑟𝑖𝑓𝑖𝑒𝑠 𝑡ℎ𝑒 𝑓𝑖𝑛𝑎𝑙 𝑐𝑜𝑛𝑑𝑖𝑡𝑖𝑜𝑛𝑠 2. 𝑠𝑜𝑙𝑢𝑡𝑖𝑜𝑛(𝑐𝑜𝑙⊕𝑒)            𝑖𝑓 𝑒 𝑖𝑠 𝑎 𝑝𝑜𝑠𝑠𝑖𝑏𝑙𝑒 𝑐𝑎𝑛𝑑𝑖𝑑𝑎𝑡𝑒 𝑎𝑛𝑑 𝑐𝑜𝑙⊕𝑒 𝑣𝑒𝑟𝑖𝑓𝑖𝑒𝑠 𝑡ℎ𝑒 𝑐𝑜𝑛𝑠𝑡𝑟𝑎𝑖𝑛𝑡 𝑐𝑜𝑛𝑑𝑖𝑡𝑖𝑜𝑛𝑠

The simplified Prolog code structure follows:

% E – a candidate value for the current variable

candidate(E, …) :-

% X – the candidate solution

final(X, …) :-

% E – the candidate value for the current variable

% X – the partial solution found so far

constraints(E, X, …) :-

4

<!-- page 5 -->
% S – the solution list – the solution to the problem

problem(…, S) :- solution([], S, …).

% X – the candidate solution – the complete list

solution(X, X, …) :- final(X, …).

% X – the past variables with assigned values % S – the solution list % E – the candidate value for the current variable

solution(X, S, …) :- candidate(E, …), constraints(E, X, …), solution([E | X], S, …).

5

<!-- page 6 -->
<u>EXAMPLE 2.1.</u> Write a non-deterministic predicate that generates combinations with k elements of a non-empty set whose elements are non-zero natural numbers, so that the sum of the elements in the combination is a given value S.

- ? combSum ([3, 2, 7, 5, 1, 6], 3, 9, C).

/* flow model (i, i, i, o) – non-deterministic */ /* k = 3, S = 9 */ C = [2, 1, 6]; C = [3, 5, 1].

? allCombSum ([3, 2, 7, 5, 1, 6], 3, 9, LC).

LC = [[2, 1, 6], [3, 5, 1]].

For solving this problem, we will give three solutions, the last one based on the backtracking method described above.

<u>Solution 1</u> We generate the solutions of the problem using direct recursion.

To determine the combinations of a list [E | L] (which has the head E and the tail L) taken K at a time, of given sum S the following cases are possible:

- i. if K = 1 and E is equal to S, then [E] is a combination

- ii. determine a combination with K elements of the list L, having the sum S;

- iii.place the element E on the first position in the combinations with K-1 elements of the list L, of sum S-E (if K> 1 and S-E> 0).

6

<!-- page 7 -->
The recursive model for generation is:

𝑐𝑜𝑚𝑏𝑆𝑢𝑚(𝑙1 𝑙2 … 𝑙𝑛, 𝑘, 𝑆) = 1. (𝑙1)                                                          𝑖𝑓 𝑘= 1 𝑎𝑛𝑑 𝑙1 = 𝑆 2. 𝑐𝑜𝑚𝑏𝑆𝑢𝑚(𝑙2 … 𝑙𝑛, 𝑘, 𝑆) 3. 𝑙1 ⊕𝑐𝑜𝑚𝑏𝑆𝑢𝑚(𝑙2 … 𝑙𝑛, 𝑘−1, 𝑆−𝑙1)   𝑖𝑓 𝑘> 1 𝑎𝑛𝑑 𝑆−𝑙1 > 0

We will use the non-deterministic predicate combSum which will generate all combinations. If you want to collect combinations in a list, you can use the findall predicate.

The SWI-Prolog program is as follows:

% combSum(L: list, K: integer, S: integer, C: list) % (i, i, i, o) – non-deterministic

combSum([H | _], 1, H, [H]). combSum([_ | T], K, S, C) :- combSum(T, K, S, C). combSum([H | T], K, S, [H | C]) :- K > 1, S1 is S-H, S1 > 0, K1 is K-1, combSum(T, K1, S1, C).

<u>Solution 2</u> The combinations with k elements are first generated and then verified whether the sum of elements is S. This solution is less efficient, considering that combinations are generated that may not have sum S.

7

<!-- page 8 -->
The following predicates will be used:

- the comb predicate for generating a combination with k elements from a list, predicate described in lecture 5

- the predicate sum (L: list of numbers, S: integer), flow model (i, i) that checks if the sum of the elements of the list L is equal to S.

% combSum(L: list, K: integer, S: integer, C: list) % (i, i, i, o) – non-deterministic combSum(L, K, S, C) :- comb(L, K, C), sum(C, S).

<u>Solution 3</u> We use a non-deterministic predicate candidate (E: element, L: list), flow model (o, i), which generates all the elements of a list.

? candidate (E, [1, 2, 3]). E = 1; E = 2; E = 3.

𝑐𝑎𝑛𝑑𝑖𝑑𝑎𝑡𝑒(𝑙1𝑙2 … 𝑙𝑛) = 1. 𝑙1                𝑖𝑓 𝑙 𝑖𝑠 𝑛𝑜𝑡 𝑒𝑚𝑝𝑡𝑦 2. 𝑐𝑎𝑛𝑑𝑖𝑑𝑎𝑡𝑒(𝑙2 … 𝑙𝑛)

% candidate(E: item, L: list) % (o, i) – non-deterministic candidate(E, [E | _]). candidate(E, [_ | T]) :- candidate(E, T).

8

<!-- page 9 -->
- The main predicate will generate a candidate E and will start generating the solution with this element.

- % combSum(L: list, K: integer, S: integer, C: list)

- % (i, i, i, o) – non-deterministic combSum(L, K, S, C) :- candidate(E, L), combAux(L, K, S, C, 1, E, [E]).

The non-deterministic auxiliary predicate combAux will generate combinations of a given sum.

% combAux (L: list, K: integer, S: integer, C: list, Lg: integer, Sum: integer, Col: list)

% (i, i, i, o, i, i, i) – non-deterministic combAux(_, K, S, C, K, S, C) :- !. combAux(L, K, S, C, Lg, Sum, [H | T]) :-

Lg < K, candidate(E, L), E < H, Sum1 is Sum + E, Sum1 =< S, Lg1 is Lg + 1, combAux(L, K, S, C, Lg1, Sum1, [E, H | T]).

9

<!-- page 10 -->
- % alternative for the second clause

- % refactoring – an auxiliary predicate to verify the condition

- % constraints(K:int, S:int, Lg:int, Sum:int, H:int, E:int)

- % (i, i, i, i, i, i, i) –deterministic

- % checks whether E satisfies the constraints with the partial solution found so far

constraints(K, S, LenRes, SumRes, HRes, E) :- LenRes < K, E < HRes, NewSum is SumRes + E, NewSum =< S.

- % return the solution

combAux(_, K, S, C, K, S, C) :- !.

- % get a legal candidate and add it to partial solution found so far combAux(L, K, S, C, LenRes, SumRes, [HRes|TRes]):candidate(E, L),

   - constraints(K, S, LenRes, SumRes, HRes, E), NewLen is LenRes+1,

NewSum is SumRes + E,

combAux(L, K, S, C, NewLen, NewSum, [E, HRes|TRes]).

10

<!-- page 11 -->
<u>EXAMPLE 2.2.</u> Given a set represented as list, the subsets of even sum formed by odd numbers only should be generated.

? submSP([1, 2, 3, 4, 5], S).

/* flow model (i, o) – non-deterministic */ S = [1, 3]; S = [1, 5] ; S = [3, 5];

<u>EXAMPLE 2.3.</u> Given two natural values n (n> 2) and v (v nonzero), a Prolog predicate is required which returns the permutations of the elements 1, 2 ...., n with the property that any two consecutive elements have the absolute difference greater than or equal to v.

# <u>Recursive models</u>

_candidate (n) =_

_1. n_

_2. candidate (n-1) if n > 1_

11

<!-- page 12 -->
The following predicates will be used

- the non-deterministic predicate candidate (N, I) (i, o) generates a solution candidate (a value between 1 and N);

- the non-deterministic predicate permutations_aux (N, V, LResult, Length, Collector) (i, i, o, i, i) collects the elements of a permutation in Collector of length Length. Generation stops when the collector contains n elements. In this case, Collector will contain a solution permutation, and LResult will be bound to Collector.

- the non-deterministic predicate permutations (N, V, L) (i, i, o) generates a solution permutation;

- the predicate member (E, L) which tests the membership of an element in a list (to collect in solution only the distinct elements); it is used as \+ member(…) to avoid duplicates.

% candidate (N: integer, I: integer) % (i, o) – non-deterministic candidate (N, N). candidate (N, I) :- N> 1, N1 is N-1, candidate (N1, I).

% permutations (N: integer, V: integer, L: list) % (i, i, o) – non-deterministic permutations (N, V, L) :- candidate (N, I), permutations_aux (N, V, L, 1, [I]).

12

<!-- page 13 -->
% permutations_aux (N: integer, V: integer, L: list, Lg: integer, Col: list) % (i, i, o, i, i) – non-deterministic permutations_aux (N, _, Col, N, Col) :- !. permutations_aux(N, V, L, Lg, [H | T]) :- candidate (N, I), abs (H-I) >= V, \+ member (I, [H | T]), % (i, i) Lg1 is Lg + 1, permutations_aux (N, V, L, Lg1, [I, H | T]).

13

<!-- page 14 -->
<u>EXAMPLE 2.4.</u> Consider a set of strictly positive integers represented as a list. Determine all the possibilities to write a number N as a sum of elements from this list.

- % list=integer*

- % candidate(list, integer) (i, o) – non-deterministic

- % an element possibly to be added in the solution list candidate([E|_],E). candidate([_|T],E) :- candidate(T,E).

- % solution(list,integer,list) (i,i,o) – non-deterministic solution(L, N, Rez) :-

candidate(L, E), E =< N,

solution_aux(L, N, Rez, [E], E).

- % solution_aux(list,integer,list,list,integer) (i,i,o,i,i) – nondeterministic

- % the fourth parameter collects the solution

- % the fifth parameter represents the sum of all elements in the collector

solution_aux(_, N, Rez, Rez, N) :- !.

solution_aux(L, N, Rez, [H | Col], S) :-

candidate(L, E), E < H, S1 is S+E, S1 =< N,

solution_aux(L, N, Rez, [E, H | Col], S1).

14

<!-- page 15 -->
# <u>EXAMPLE 2.5</u> <u>. THE PROBLEM OF THE THREE HOUSES.</u>

1. The Englishman lives in the first house on the left.

2. In the house immediately to the right of the one where the wolf is, he smokes Lucky Strike.

3. The Spaniard smokes Kent.

4. The Russian has a horse.

Who smokes LM? Whose dog is it?

We remark that the problem has two solutions:

|I. English|dog|LM|
|---|---|---|
|Spanish|wolf|Kent|
|Russian|horse|LS|
|II. English|wolf|LM|
|Russian|horse|LS|
|Spanish|dog|Kent|

This is a typical constraint satisfaction problem.

We encode the data of the problem and remark that a solution consists of triplets of the form (N, A, T) where:

N belongs to the set [eng, spa, rus]

A belongs to the set [dog, wolf, horse]

T belongs to the set [lm, ls, kent]

We will use the following predicates:

- non-deterministic predicate solve (N, A, T) (o, o, o) which generates a solution of the problem

15

<!-- page 16 -->
- non-deterministic predicate candidates (N, A, T) (o, o, o) that generates all candidate solutions

- deterministic predicate constraints (N, A, T) (i, i, i) which verifies whether a candidate for solution satisfies the constraints imposed by the problem

- non-deterministic predicate perm (L, L1) (i, o) which generates the permutations of the list L

% solve - (o, o, o) solve (N, A, T) :- candidates(N, A, T), constraints(N, A, T).

% candidates - (o, o, o) candidates(N, A, T) :-

perm([eng, spa, rus], N), perm([dog, wolf, horse], A), perm([lm, kent, ls], T).

16

<!-- page 17 -->
% constraints - (i, i, i) constraints(N, A, T) :- aux (N, A, T, eng, _, _, 1), aux (N, A, T, _, wolf, _, Nr1), right (Nr1, Nr2), aux (N, A, T, _, _, ls, Nr2), aux (N, A, T, spa, _, kent, _), aux (N, A, T, rus, horse, _, _).

% right - (i, o) right (I, J) :- J is I + 1.

% aux (i, i, i, o, o, o, o) aux ([N1, _, _], [A1, _, _], [T1, _, _], N1, A1, T1,1). aux ([_, N2, _], [_, A2, _], [_, T2, _], N2, A2, T2,2). aux ([_, _, N3], [_, _, A3], [_, _, T3], N3, A3, T3,3).

% insert (s) insert (E, L, [E | L]). insert (E, [H | L], [H | T]) :- insert (E, L, T).

% perm (i, o) perm ([], []). perm ([H | T], L) :- perm (T, P), insert (H, P, L).

17

<!-- page 18 -->
<u>EXAMPLE 2.6.</u> THE PROBLEM OF THE FIVE HOUSES.

There are 15 facts and 2 questions: Who owns a zebra and who drinks water?

- 1) There are 5 colored houses in a row, each with an owner, an animal, a cigarette, a drink.

- 2) The English lives in the red house.

- 3) The Spaniard owns a dog.

- 4) In the green house they drink coffee.

- 5) The Ukrainian drinks tea.

- 6) The green house is next to the white house.

- 7) The Winston smoker owns a serpent.

- 8) In the yellow house they smoke Kool.

- 9) In the middle house they drink milk.

- 10) The Norwegian lives in the first house from the left.

- 11) The Chesterfield smoker lives near the fox owner.

- 12) In the house near the house with the horse they smoke Kool.

- 13) The Lucky Strike smoker drinks juice.

- 14) The Japanese smokes Kent.

- 15) The Norwegian lives near the blue house.

18

<!-- page 19 -->
<u>EXAMPLE 2.7.</u> Arrange N queens on a NxN chessboard so that they do not attack each other.

% (integer, list) - (i, o) non-deterministic queen (N, Rez) :- candidate (E, N), queen_aux (N, Rez, [[N, E]], N), printSolution (N, Rez).

% (integer, integer) - (o, i) non-deterministic candidate (N, N). candidate (E, N) :- N > 1, N1 is N-1, candidate (E, N1).

% (integer, list, list, integer) - (i, o, i, i) non-deterministic queen_aux (_, Rez, Rez, 1) :- !.

19

<!-- page 20 -->
queen_aux (N, Rez, C, Lin) :- candidate (Col1, N), Lin1 is Lin-1, valid (Lin1, Col1, C), queen_aux (N, Rez, [[Lin1, Col1] | C], Lin1).

% (integer, integer, list) - (i, i, i) deterministic valid (_, _, []). valid (Lin, Col, [[Lin1, Col1] | T]) :- Col =\= Col1, DCol is Col-Col1, DLin is Lin-Lin1, abs (DLin) =\= abs (DCol), valid (Lin, Col, T).

% (integer, list) - (i, i) deterministic printSolution (_, []) :- nl. printSolution (N, [[_, Col] | T]) :- printLine (N, Col), printSolution (N, T).

% (integer, char) - (i, o) deterministic character (1, '*') :- !. character(_,'-').

% (integer, list) - (i, i) deterministic printLine (0, _) :- nl, !. printLine (N, Col) :- character (Col, C), write (C), N1 is N-1, Col1 is Col-1, printLine (N1, Col1).

20

<!-- page 21 -->
# <u>HOMEWORK</u>

1. The chess knight’s tour problem: Find the path a knight has to follow on a chess board using legal knight moves and visiting every square exactly once.

2. A list of distinct integer elements is given. Generate all subsets with elements in strictly ascending order .

3. A list of distinct integer elements is given. Generate all subsets with k elements in arithmetic progression .

21
