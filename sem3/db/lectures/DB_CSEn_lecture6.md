<!-- page 1 -->
# Databases

Lecture 6

Functional Dependencies. Normal Forms (III) Relational Algebra

Sabina S. CS

<!-- page 2 -->
- R[A] - a relation

• F - a set of functional dependencies

- 𝛼 – a subset of attributes

- problems

- I. compute the closure of F: F+

II. compute the closure of a set of attributes under a set of functional dependencies, e.g., the closure of 𝛼 under F: 𝛼+

III. compute the minimal cover for a set of dependencies

Sabina S. CS

<!-- page 3 -->
- R[A] - a relation

• F - a set of functional dependencies

- problems

III. compute the minimal cover for a set of dependencies

Definition: F, G - two sets of functional dependencies; F and G are equivalent (notation F ≡G) if F+ = G+ .

->

Sabina S. CS

<!-- page 4 -->
- R[A] - a relation

• F - a set of functional dependencies

- problems

III. compute the minimal cover for a set of dependencies

Definition: F - set of functional dependencies; a minimal cover for F is a set of functional dependencies FM that satisfies the following conditions:

1. FM ≡F

2. the right side of every dependency in FM has a single attribute;

3. the left side of every dependency in FM is irreducible (i.e., no attribute can be removed from the determinant of a dependency in FM without changing FM's closure);

4. no dependency _f_ in FM is redundant (no dependency can be discarded without changing FM’s closure).

Sabina S. CS

<!-- page 5 -->
- see lecture problem

• R - a relation, F - a set of functional dependencies

• compute FM - minimal cover for F

Sabina S. CS

<!-- page 6 -->
Example 11. Consider relation DFM[Department, FacultyMembers, MeetingDates], with repeating attributes _FacultyMembers_ and _MeetingDates_ .

• a possible instance is given below:

<!-- Start of picture text -->
Department FacultyMembers MeetingDates Computer Science FCS1 DCS1 FCS2 DCS2 … … FCSm DCSn Mathematics FM1 DM1 FM2 DM2 … … FMp DMq <!-- End of picture text -->

Sabina S. CS

<!-- page 7 -->
### • eliminate repeating attributes (such that the relation is at least in 1NF) - replace DFM by a relation DFM' in which _FacultyMember_ and _MeetingDate_ are scalar attributes:

|Department|FacultyMember|MeetingDate|
|---|---|---|
|Computer Science|FCS1|DCS1|
|Computer Science|FCS1|DCS2|
|…|…|…|
|Computer Science|FCS1|DCSn|
|Computer Science|FCS2|DCS1|
|Computer Science|FCS2|DCS2|
|…|…|…|
|Mathematics|FM1|DM1|
|…|…|…|
|Mathematics|FMp|DMq|

Sabina S. CS

<!-- page 8 -->
<mark>Department FacultyMember MeetingDate</mark> <mark>Computer Science FCS1 DCS1 Computer Science FCS1 DCS2 … … … Computer Science FCS1 DCSn Computer Science FCS2 DCS1 Computer Science FCS2 DCS2 … … … Mathematics FM1 DM1 \ … … … Mathematics FMp DMq</mark>

- in this table, each faculty member has the same meeting dates

- therefore, when adding / changing / removing rows, additional checks must be carried out

Sabina S. CS

<!-- page 9 -->
- a simple functional dependency 𝛼→𝛽 means, by definition, that every value 𝑢 of 𝛼 is associated with a unique value 𝑣 for 𝛽

Definition. Let 𝑅[𝐴] be a relation, with the set of attributes 𝐴= 𝛼∪𝛽∪𝛾 . The multi-valued dependency 𝛼⇉𝛽 (read 𝛼 _multi-determines_ 𝛽 ) is said to hold over 𝑅 if each value 𝑢 of 𝛼 is associated with a set of values 𝑣 for 𝛽: 𝛽 𝑢= {𝑣1, 𝑣2, … , 𝑣𝑛} , and this association holds regardless of the values of 𝛾 .

->

Sabina S. CS

<!-- page 10 -->
- obs. 𝜎𝛼=𝑢 𝑅 produces a relation that contains the tuples of 𝑅 where 𝛼= 𝑢

- let 𝑅[𝐴] be a relation, 𝛼 ⇉𝛽 a multi-valued dependency, and 𝐴= 𝛼∪𝛽∪𝛾 , with 𝛾 a non-empty set

- the association among the values in 𝛽(𝑢) for 𝛽 and the value 𝑢 of 𝛼 holds regardless of the values of 𝛾 (the context)

- i.e., these associations (between 𝑢 and an element in 𝛽(𝑢) ) exist for any value 𝑤 in 𝛾 :

   - 𝑅

   - 𝜎𝛼=𝑢 , ∃𝑟1, 𝑟2, … , 𝑟𝑛 such that 𝛱𝛼 𝑟𝑖 = 𝑣𝑖 ,

   - • ∀𝑤∈𝛱𝛾 𝑟𝑖 = 𝑢 , 𝛱𝛽 𝑟𝑖 = 𝑤

   - 𝛱𝛾

Sabina S. CS

<!-- page 11 -->
### • if 𝛼⇉𝛽 and the following rows exist:

<!-- Start of picture text -->
𝜶 𝜷 𝛾 𝑢 1 𝑣 1 𝑤 1 𝑢 1 𝑣 2 𝑤 2 <!-- End of picture text -->

### then the following rows must exist as well:

<!-- Start of picture text -->
𝜶 𝜷 𝛾 𝑢 1 𝑣 1 𝑤 2 𝑢 1 𝑣 2 𝑤 1 <!-- End of picture text -->

Sabina S. CS

<!-- page 12 -->
Property. Let 𝑅[𝐴] be a relation, 𝐴= 𝛼∪𝛽∪𝛾 . If 𝛼⇉𝛽 , then 𝛼⇉𝛾 . Justification.

• Let 𝑢 be a value of 𝛼 in 𝑅 . 𝑅 𝑅 • Let 𝛽 𝜎𝛼=𝑢 , 𝛾 𝜎𝛼=𝑢 𝑢= 𝛱𝛽 𝑢= 𝛱𝛾 tuples where 𝛼= 𝑢 ). Since 𝛼⇉𝛽⇒ ∀𝑤∈𝛾 _(u),_ ∀𝑣∈𝛽 _(u),_ ∃𝑟= (𝑢, 𝑣, 𝑤) _,_ or ∀𝑣∈𝛽 _(u)_ , ∀𝑤∈𝛾 _(u),_ ∃𝑟= (𝑢, 𝑣, 𝑤) , therefore 𝛼⇉𝛾 .

(the 𝛽 and 𝛾 values in the

- for relation DFM' (in the previous example): _{Department}_ ⇉ _{FacultyMember}_ , _{Department}_ ⇉ _{MeetingDate}_

Sabina S. CS

<!-- page 13 -->
Definition. A relation 𝑅 is in 4NF if, for every multi-valued dependency 𝛼⇉𝛽 that holds over 𝑅 , one of the statements below is true:

- 𝛽⊆𝛼 or 𝛼∪𝛽= 𝑅 , or

- 𝛼 is a superkey.

- trivial multi-valued dependency 𝛼⇉𝛽 in relation 𝑅 : 𝛽⊆𝛼 or 𝛼∪𝛽= 𝑅

- if 𝑅[𝛼 , 𝛽 , 𝛾] and 𝛼⇉𝛽 (non-trivial, 𝛼 not a superkey), 𝑅 is decomposed into the following relations:

- 𝑅1[𝛼 , 𝛽] = 𝛱𝛼⋃𝛽 𝑅

- 𝑅2[𝛼 , 𝛾] = 𝛱𝛼⋃𝛾 𝑅

- relation DFM' is decomposed into: DF [Department, FacultyMember] DM [Department, MeetingDate]

Sabina S. CS

<!-- page 14 -->
- a dependency (simple, multi-valued) in a relation can be eliminated via decompositions (the original relation is decomposed into a collection of new relations)

- nevertheless, there are relations without such dependencies that can still contain redundant information, which can be a source of errors in the database

->

Sabina S. CS

<!-- page 15 -->
Example 12. Consider relation FaPrCo[FacultyMember, Program, Course], storing the programs and courses for different faculty members; this relation has no functional dependencies; its key is {FacultyMember, Program, Course}

- consider the following data in the relation:

|Fa|Pr|Co|
|---|---|---|
|F1|P1|C2|
|F1|P2|C1|
|F2|P1|C1|
|F1|P1|C1|

- some associations appear in multiple records (redundant data):

   - faculty member F1 is teaching in program P1

   - faculty member F1 is teaching course C1

   - course C1 is taught in program P1

Sabina S. CS

<!-- page 16 -->
|Fa|Pr|Co|
|---|---|---|
|F1|P1|C2|
|F1|P2|C1|
|F2|P1|C1|
|F1|P1|C1|

- if some values in the relation are changed, e.g., "F1 will teach course C3 instead of course C1", several updates should be carried out (without knowing in how many records)

- the same is true for the following changes: "in P1, course C3 should replace course C1", "F1 is switching from program P1 to P3"

Sabina S. CS

<!-- page 17 -->
- the previous relation cannot be decomposed into 2 relations (via projection), because new data would be introduced through the join

- this claim can be justified by considering the three possible projections on two attributes:

|FaPr|Fa|Pr|
|---|---|---|
||F1|P1|
||F1|P2|
||F2|P1|

|FaCo|Fa|Co|
|---|---|---|
||F1|C2|
||F1|C1|
||F2|C1|

<!-- Start of picture text -->
PrCo Pr Co P1 C2 P2 C1 P1 C1 <!-- End of picture text -->

Sabina S. CS

<!-- page 18 -->
### • when evaluating FaPr ∗PrCo , the following data is obtained:

|𝐑′ = 𝐅𝐚𝐏𝐫∗𝐏𝐫𝐂𝐨|Fa|Pr|Co|
|---|---|---|---|
||F1|P1|C2|
||F1|P1|C1|
||F1|P2|C1|
||F2|P1|C2|
||F2|P1|C1|

- this result set contains an extra tuple, which didn't exist in the original relation

- the same is true for the other join combinations: FaPr ∗FaCo and PrCo ∗FaCo

Sabina S. CS

<!-- page 19 -->
- when evaluating R′ ∗FaCo (i.e., FaPr ∗PrCo ∗FaCo ), the original relation FaPrCo is obtained

- conclusion: FaPrCo cannot be decomposed into 2 projections, but it can be decomposed into 3 projections, i.e., FaPrCo is _3-decomposable_ : FaPrCo = FaPr ∗PrCo ∗FaCo , or FaPrCo = ∗ FaPr, PrCo, FaCo

- this conclusion ( FaPrCo is 3-decomposable) is true for the data in the relation • 3-decomposability can be specified as a constraint:

- _if (F1, P1)_ ∈ _FaPr and (F1, C1)_ ∈ _FaCo and (P1, C1)_ ∈ _PrCo then_

- _(F1, P1, C1)_ ∈ _FaPrCo_

- this restriction can be expressed on FaPrCo (all legal instances must satisfy the constraint):

- _if (F1, P1, C2)_ ∈ 𝐹𝑎𝑃𝑟𝐶𝑜 _and (F1, P2, C1)_ ∈ 𝐹𝑎𝑃𝑟𝐶𝑜 _and_

- _(F2, P1, C1)_ ∈𝐹𝑎𝑃𝑟𝐶𝑜 _then (F1, P1, C1)_ ∈𝐹𝑎𝑃𝑟𝐶𝑜

Sabina S. CS

<!-- page 20 -->
### • consider the following relation instance:

|Fa|Pr|Co|
|---|---|---|
|F1|P1|C2|
|F1|P2|C1|

- if the previous restriction holds, then, if (F2, P1, C1) is added to the relation, (F1, P1, C1) must be also added:

|Fa|Pr|Co|
|---|---|---|
|F1|P1|C2|
|F1|P2|C1|
|F2|P1|C1|
|F1|P1|C1|

### * what if (F1, P1, C1) is removed from the instance?

Sabina S. CS

<!-- page 21 -->
Definition. Let 𝑅[𝐴] be a relation and 𝑅𝑖[𝛼𝑖] , i=1,2, ...,m, the projections of 𝑅 on 𝛼𝑖 . 𝑅 satisfies the join dependency ∗{𝛼1 , 𝛼2 , ..., 𝛼m} if 𝑅= 𝑅1 ∗𝑅2 ∗⋯∗ 𝑅𝑚 .

- FaPrCo has a join dependency because FaPrCo = FaPr ∗PrCo ∗FaCo

Definition. Relation 𝑅 is in 5NF if every non-trivial JD is implied by the candidate keys in 𝑅 .

- JD ∗{𝛼1 , 𝛼2 , ..., 𝛼m} on 𝑅 is trivial if at least one 𝛼𝑖 is the set of all attributes of 𝑅 .

- JD ∗{𝛼1 , 𝛼2 , ..., 𝛼m} on 𝑅 is implied by the candidate keys of 𝑅 if each 𝛼𝑖 is a superkey in 𝑅 .

- => FaPrCo not in 5NF

   - decomposition: projections on FaPr , PrCo , FaCo

Sabina S. CS

<!-- page 22 -->
### Relational Algebra

Sabina S. CS

<!-- page 23 -->
- query languages in the relational model

   - relational algebra and calculus - formal query languages with a significant influence on SQL

      - relational algebra

         - queries are specified in an operational manner

      - relational calculus

         - queries describe the desired answer, without specifying how it will be computed (declarative)

   - not expected to be Turing complete

   - not intended for complex calculations

   - provide efficient access to large datasets

   - allow optimizations

Sabina S. CS

<!-- page 24 -->
- relational algebra

   - used by DBMSs to represent query execution plans

   - a relational algebra query:

      - is built using a collection of operators

      - describes a step-by-step procedure for computing the result set

      - is evaluated on the input relations' instances

      - produces an instance of the output relation

   - every operation returns a relation, so operators can be composed; the algebra is closed

   - the result of an algebra expression is a relation, and a relation is a set of tuples

- relational algebra on bags (multisets) - duplicates are not eliminated

Sabina S. CS

<!-- page 25 -->
### Conditions

- conditions that can be used in several algebraic operators

- similar to the SELECT filter conditions

1. _attribute_name relational_operator value_

- _value_ - attribute name, expression

2. _attribute_name IS [NOT] IN single_column_relation_

- a relation with one column can be considered a set

- the condition tests whether a value belongs to a set

3. _relation {IS [NOT] IN | = | <>} relation_

- the relations in the condition must be union-compatible

Sabina S. CS

<!-- page 26 -->
### Conditions

4. _(condition) NOT condition condition1 AND condition2 condition1 OR condition2_ , where _condition_ , _condition1_ , _condition2_ are conditions of type 1-4.

Sabina S. CS

<!-- page 27 -->
### _<u>Operators in the Algebra</u>_

• equivalent SELECT statements can be specified for the relational algebra expressions

- _selection_

   - notation: 𝜎𝐶 𝑅

   - resulting relation:

      - schema: 𝑅 's schema

      - tuples: records in 𝑅 that satisfy condition C

   - equivalent SELECT statement `SELECT * FROM R WHERE C`

Sabina S. CS

<!-- page 28 -->
- _projection_

   - notation: 𝜋𝛼 𝑅

• resulting relation:

   - schema: attributes in 𝛼

   - tuples: every record in 𝑅 is projected on 𝛼

- 𝛼 can be extended to a set of expressions, specifying the columns of the relation being computed

- equivalent SELECT statement

`SELECT DISTINCT` 𝛼 `FROM R`

`SELECT` 𝛼 `FROM R`

```
--algebraonbags
```

Sabina S. CS

<!-- page 29 -->
- _cross-product_

• notation: 𝑅1 × 𝑅2

• resulting relation:

• schema: the attributes of 𝑅1 followed by the attributes of 𝑅2

• tuples: every tuple 𝑟1 in 𝑅1 is concatenated with every tuple 𝑟2 in 𝑅2

• equivalent SELECT statement

```
SELECT *
FROM R1 CROSS JOIN R2
```

Sabina S. CS

<!-- page 30 -->
- _union, set-difference, intersection_

   - notation: 𝑅1 ∪𝑅2 , 𝑅1 −𝑅2 , 𝑅1 ∩𝑅2

   - 𝑅1 and 𝑅2 must be union-compatible:

      - same number of columns

      - corresponding columns, taken in order from left to right, have the same domains

   - equivalent SELECT statements

```
SELECT*SELECT*SELECT*
FROMR1FROMR1FROMR1
UNIONEXCEPTINTERSECT
SELECT*SELECT*SELECT*
FROMR2FROMR2FROMR2
```

```
--algebraonbags:SELECTstatementsthatdon'teliminate
duplicates(e.g.,UNIONALL)
```

Sabina S. CS

<!-- page 31 -->
- join operators

   - _condition join_ (or _theta join_ )

      - notation: 𝑅1⨂Θ𝑅2

      - result: the records in the cross-product of 𝑅1 and 𝑅2 that satisfy a certain condition

   - definition ⇒𝑅1⨂Θ𝑅2 = 𝜎𝛩(𝑅1 × 𝑅2)

   - equivalent SELECT statement

      - `SELECT *`

`FROM R1 INNER JOIN R2 ON` Θ

Sabina S. CS

<!-- page 32 -->
- join operators

   - _natural join_

      - notation: 𝑅1 ∗𝑅2

      - resulting relation:

         - schema: the union of the attributes of the two relations (attributes with the same name in 𝑅1 and 𝑅2 appear once in the result)

         - tuples: obtained from tuples < 𝑟1 , 𝑟2 >, where 𝑟1 in 𝑅1 , 𝑟2 in 𝑅2 , and 𝑟1 and 𝑟2 agree on the common attributes of 𝑅1 and 𝑅2

      - let 𝑅1[𝛼] , 𝑅2[𝛽] , 𝛼∩𝛽= 𝐴1, 𝐴2, … , 𝐴𝑚 ; then:

𝑅1 ∗𝑅2 = 𝜋𝛼⋃𝛽(𝑅1⨂𝑅1.𝐴1=𝑅2.𝐴1 𝐴𝑁𝐷… 𝐴𝑁𝐷𝑅1.𝐴𝑚=𝑅2.𝐴𝑚𝑅2)

- equivalent SELECT statement

   - `SELECT *`

```
FROMR1NATURALJOINR2
```

Sabina S. CS

<!-- page 33 -->
- join operators

   - _left outer join_

      - notation (in these notes): 𝑅1 ⋉C 𝑅2

      - resulting relation:

         - schema: the attributes of 𝑅1 followed by the attributes of 𝑅2

         - tuples: tuples from the condition join 𝑅1⨂c𝑅2 + the tuples in 𝑅1 that were not used in 𝑅1⨂c𝑅2 combined with the _null_ value for the attributes of 𝑅2

      - equivalent SELECT statement

         - `SELECT *`

```
FROMR1LEFTOUTERJOINR2ONC
```

Sabina S. CS

<!-- page 34 -->
- join operators

   - _right outer join_

      - notation: 𝑅1 ⋊C 𝑅2

      - resulting relation:

         - schema: the attributes of 𝑅1 followed by the attributes of 𝑅2

         - tuples: tuples from the condition join 𝑅1⨂c𝑅2 + the tuples in 𝑅2 that were not used in 𝑅1⨂c𝑅2 combined with the _null_ value for the attributes of 𝑅1

      - equivalent SELECT statement

         - `SELECT *`

```
FROMR1RIGHTOUTERJOINR2ONC
```

Sabina S. CS

<!-- page 35 -->
- join operators

   - _full outer join_

      - notation: 𝑅1 ⋈C 𝑅2

      - resulting relation:

         - schema: the attributes of 𝑅1 followed by the attributes of 𝑅2

         - tuples:

            - tuples from the condition join 𝑅1⨂c𝑅2 +

            - the tuples in 𝑅1 that were not used in 𝑅1⨂c𝑅2 combined with the _null_ value for the attributes of 𝑅2 +

            - the tuples in 𝑅2 that were not used in 𝑅1⨂c𝑅2 combined with the _null_ value for the attributes of 𝑅1

      - equivalent SELECT statement

         - `SELECT *`

```
FROMR1FULLOUTERJOINR2ONC
```

Sabina S. CS

<!-- page 36 -->
- join operators

   - _left semi join_

      - notation: 𝑅1⊳𝑅2

      - resulting relation:

         - schema: 𝑅1 's schema

         - tuples: the tuples in 𝑅1 that are used in the natural join 𝑅1 ∗𝑅2

Sabina S. CS

<!-- page 37 -->
- join operators

   - _right semi join_

      - notation: 𝑅1⊲𝑅2

      - resulting relation:

         - schema: 𝑅2 's schema

         - tuples: the tuples in 𝑅2 that are used in the natural join 𝑅1 ∗𝑅2

Sabina S. CS

<!-- page 38 -->
- _division_ • notation: 𝑅1 ÷ 𝑅2 • 𝑅1[𝛼] , 𝑅2[𝛽] , 𝛽⊂𝛼 • resulting relation: • schema: 𝛼 _−_ 𝛽 • tuples: a record 𝑟∈𝑅1 ÷ 𝑅2 if ∀𝑟2 ∈𝑅2, ∃𝑟1 ∈𝑅1 such that:

   - 𝜋𝛼−𝛽 𝑟1 = 𝑟

   - • 𝜋𝛽 𝑟1 = 𝑟2

𝛽

R1

<!-- Start of picture text -->
r r2 r1 𝛽 R2 r2 r2 𝛼 <!-- End of picture text -->

- i.e., a record 𝑟 belongs to the result if in 𝑅1 𝑟 is concatenated with every record in 𝑅2

Sabina S. CS

<!-- page 39 -->
- see lecture examples (at the board) with algebra queries:

- selection

- projection

- division

- selection, projection

- natural join, selection, projection

- set-difference, natural join, selection, projection

- different algebra expressions producing the same result (optimization -

- reducing the size of intermediate relations)

Sabina S. CS

<!-- page 40 -->
## References

- [Ta13] ȚÂMBULEA, L., Curs Baze de date, Facultatea de Matematică și Informatică, UBB, 2013-2014

- [Ra00] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems (2nd Edition), McGraw-Hill, 2000

- [Da03] DATE, C.J., An Introduction to Database Systems (8th Edition), AddisonWesley, 2003

- [Ga08] GARCIA-MOLINA, H., ULLMAN, J., WIDOM, J., Database Systems: The Complete Book, Prentice Hall Press, 2008

- [Ha96] HANSEN, G., HANSEN, J., Database Management And Design (2nd Edition), Prentice Hall, 1996

- [Ra07] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems, McGrawHill, 2007, <u>http://pages.cs.wisc.edu/~dbbook/openAccess/thirdEdition/slides/slides3ed.html</u>

- • [Ul11] ULLMAN, J., WIDOM, J., A First Course in Database Systems, <u>http://infolab.stanford.edu/~ullman/fcdb.html</u>

Sabina S. CS
