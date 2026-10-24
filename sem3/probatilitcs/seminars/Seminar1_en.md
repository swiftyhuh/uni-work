<!-- page 1 -->
# Seminar 1 - 2026

## Combinatorics

1. _The basic principle of counting:_ If _m_ experiments that are to be performed are such that the first one may result in any of _n_ 1 possible outcomes, and if, for each of these _n_ 1 possible outcomes, there are _n_ 2 possible outcomes of the second experiment, and if, for each of the possible outcomes of the first two experiments, there are _n_ 3 possible outcomes of the third experiment, and if..., then there is a total of _n_ 1 _· n_ 2 _· . . . · nm_ possible outcomes of the _m_ experiments.

_Example:_ In how many ways can a person choose to wear 3 shirts, 2 jeans and 4 pairs of shoes? A: 3 _·_ 2 _·_ 4 = 24.

2. _Arrangements of n objects taken k_ ( _k, n ∈_ N _, n ≥ k_ ): selections of _k_ distinct and ordered items from _n_ distinct given objects.

_Remark:_ By convention, 0! = 1.

_Example:_ How many codes with 3 distinct digits can be generated with the digits: 0, 1, 2, 3, 4? A: _A_3 5= 2!<u>5!</u>= 60.

3. _Permutations of n objects_ : arrangements of _n_ objects taken _n_ .

_Pn_ = number of permutations of _n_ objects = _A__n_ _n_=_n_!

_Example:_ In how many ways can 4 persons sit on a bench? A: _P_ 4 = 4!

4. _Combinations of n objects taken k_ ( _k, n ∈_ N _, n ≥ k_ ): selections of _k_ distinct and not ordered items from _n_ distinct given objects, i.e., subsets with _k_ elements of a set with _n_ elements.

_Remark: Cn__k_=_C_ _n__n−k_ .

_Example:_ How many football teams can be formed out of a group of 15 persons? A: _C_ 1511=_C_ 154= 1365. 5. _Number of functions_ from a set _A_ with _k_ elements to a set _B_ with _n_ elements: _n__k_ ( _k, n ∈_ N_∗_ ). _Remark:_ A function can be identified with selections of _k_ items that are not necessarily distinct (i.e., an item can be chosen multiple times), but ordered , from _n_ distinct objects. Hence, we can say that the _functions_ are _arrangements with repetitions_ .

_Example:_ How many codes with 3 digits can be generated with the digits: 0, 1, 2, 3, 4? A: 53 = 125.

6. _Permutations with repetitions:_ Consider _n_ objects such that _n_ 1 are alike, _n_ 2 are alike,..., _nm_ are alike ( _n, m ∈_ N_∗_ _, m ≤ n_ ; _n_ 1 _, . . . , nm ∈_ N _, n_ 1 + _. . ._ + _nm_ = _n_ ). The number of distinct permutations of these _n_ objects is

_Example:_ In how many ways can we order 3 white marbles, 4 black marbles and 2 gray marbles on a line? Example: _• ◦• ◦• ◦ • • •_ A: 3!4!2!9!= 1260. _Example:_ In how many ways can we order 3 white marbles and 4 black marbles on a line? Example: _◦• ◦◦• • •_ A: 3!4!<u>7!</u>= 35. _Remark:_ In the above example we get the same value as _C_ 73=_C_ 74,becausethenumberofpermutations

<!-- page 2 -->
with repetitions for _m_ = 2 types of objects is the same as the number of ways to choose the distinct and not ordered positions (i.e., combinations), in each permutation, for the objects of the first type (the remaining positions are automatically left for the second type objects).

7. _Combinations with repetitions of n objects taken k_ ( _n ∈_ N_∗_ _, k ∈_ N): selections of _k_ items that are not necessarily distinct (i.e., an item can be chosen multiple times) and not ordered , from _n_ distinct given objects (i.e., arrangements with repetitions in which we neglect the order). Their number is

_Example:_ In how many ways can we distribute 5 identical marbles to 3 children (C1, C2, C3)? (A child may receive one marble/several marbles/none.) A: Examples of distributing the marbles to the children (“o” stands for a _marble_ ):

|C1|C2|C3|
|---|---|---|
|oo||ooo|
|o|o|ooo|
|ooo|oo||
|||ooooo|

We identify the configurations above with strings of 7 bits, where 0 stands for a marble and 1 stands for the separator between two groups of marbles (some groups may be empty) held by two successive children:

Hence, we reformulate the question: in how many ways can we place 5 digits equal to 0 and 2 digits equal to 1 on 7 positions? A: _C_ 75=_C_ 72= 5!2!7!= 21_._

<!-- page 3 -->
## Problems

1. How many different 7-place license plates are possible in Romania, given that the digit group runs from 01 to 99 for counties and from 100 to 999 for Bucharest, _Q_ cannot be used at all and all 3-letter groups starting with _O_ or _I_ are forbidden? Examples of 7-place license plates in Romania: CJ-01-YYR, IF-12-XYZ, B-101-ABC.

2. In how many ways can we put on a shelf the 7 _Harry Potter_ books, the 3 volumes of _The Lord of the Rings_ and the 4 _Twilight_ books, given that

   - a) the books of the same series are grouped together?

   - b) only the _Harry Potter_ books are necessarily grouped together?

3. X goes to the theater with 10 girls and 9 boys. In how many ways can they occupy an entire row such that X seats between two girls?

4. a) How many 5-place codes contain exactly 3 decimal digits and 2 capital latin letters? Examples: 01 _DD_ 0, _A_ 21 _Z_ 0, 999 _XX_ .

b) How many 5-place codes contain exactly 3 distinct decimal digits and 2 distinct capital latin letters? Example: _A_ 21 _Z_ 0.

5. How many anagrams does the word MISSISSIPPI have?

6. In how many ways can 6 persons sit at a round table? Example:

<!-- Start of picture text -->
P 1 P 6 P 3 P 2 P 4 P 5 <!-- End of picture text -->

7. a) In how many distinct ways can the characters: A, A, A, B, B, 0, 0, 0, 1 be ordered on a line? Example: 1 B A 0 A 0 0 B A.

b) In how many distinct ways can the characters: A, A, A, B, B, 0, 0, 0, 1 be ordered on a circle? Example:

8. An ice cream shop has 7 flavors. A customer orders one cone with 3 scoops. In how many ways can the flavors be chosen, if a flavor may be used for several scoops and the order of the scoops on the cone is irrelevant?

9. a) How many solutions ( _x_ 1 _, . . . , xk_ ) _∈_ N_∗_ _×· · ·×_ N_∗_ does the equation _x_ 1 + _. . ._ + _xk_ = _n_ have ( _k, n ∈_ N_∗_ , _n ≥ k_ )?

b) How many solutions ( _x_ 1 _, . . . , xk_ ) _∈_ N _× · · · ×_ N does the equation _x_ 1 + _. . ._ + _xk_ = _n_ have ( _k, n ∈_ N_∗_ )?
