<!-- page 1 -->
# Databases

Lecture 5

Functional Dependencies. Normal Forms (II)

Sabina S. CS

<!-- page 2 -->
Obs. The following simple properties for functional dependencies can be easily demonstrated:

1. If _K_ is a key of 𝑅[𝐴1, 𝐴2, … , 𝐴𝑛] , then 𝐾→𝛽 _,_ ∀𝛽 a subset of 𝐴1, 𝐴2, … , 𝐴𝑛 .

- such a dependency is always true, hence it will not be eliminated through decompositions

2. If 𝛽⊆𝛼 , then 𝛼→𝛽 - _trivial functional dependency_ ( _reflexivity_ ). 𝛱𝛼 𝑟1 = 𝛱𝛼 𝑟2 ⇒𝛱𝛽 𝑟1 = 𝛱𝛽 𝑟2 ⇒𝛼→𝛽 𝛽⊆𝛼 3. If 𝛼→𝛽 , then 𝛾→𝛽 , ∀𝛾 with 𝛼⊂𝛾. 𝛱𝛾 𝑟1 = 𝛱𝛾 𝑟2 ⇒𝛱𝛼 𝑟1 = 𝛱𝛼 𝑟2 ⇒𝛱𝛽 𝑟1 = 𝛱𝛽 𝑟2 ⇒𝛾→𝛽 𝛼⊂𝛾, 𝑝𝑟𝑜𝑝. 2 𝛼→𝛽

Sabina S. CS

<!-- page 3 -->
Obs. The following simple properties for functional dependencies can be easily demonstrated:

4. If 𝛼→𝛽 and 𝛽→𝛾 , then 𝛼→𝛾 - _transitivity_ . 𝛱𝛼 𝑟1 = 𝛱𝛼 𝑟2 ⇒𝛱𝛽 𝑟1 = 𝛱𝛽 𝑟2 ⇒𝛱𝛾 𝑟1 = 𝛱𝛾 𝑟2 ⇒𝛼→𝛾 𝛼→𝛽 𝛽→𝛾 5. If 𝛼→𝛽 and 𝛾 a subset of 𝐴1, … , 𝐴𝑛 , then 𝛼𝛾→𝛽𝛾 , where 𝛼𝛾= 𝛼∪𝛾 _._ 𝑟2 ⇒Π𝛼 𝑟1 = Π𝛼 𝑟2 ⇒Π𝛽 𝑟1 = Π𝛽 𝑟2 Π𝛼𝛾 𝑟1 = Π𝛼𝛾 ⇒Π𝛽𝛾𝛽𝛾 𝑟11 = Π𝛽𝛾𝛽𝛾 𝑟2 Π𝛾 𝑟1 = Π𝛾

𝑟2 ⇒Π𝛽𝛾𝛽𝛾 𝑟11 = Π𝛽𝛾𝛽𝛾

Sabina S. CS

<!-- page 4 -->
Definition. An attribute A (simple or composite) is said to be _prime_ if there is a key K and A ⊆ K (K can be a composite key; A can itself be a key). If an attribute isn't included in any key, it is said to be _non-prime_ .

Definition. Let 𝑅[𝐴1, 𝐴2, … , 𝐴𝑛] be a relation, and let 𝛼, 𝛽 be two subsets of attributes of 𝑅 . Attribute 𝛽 is _fully functionally dependent on_ 𝛼 if:

- 𝛽 is functionally dependent on 𝛼 (i.e., 𝛼→𝛽 ) and

- 𝛽 is not functionally dependent on any proper subset of 𝛼 , i.e., ∀𝛾⊂𝛼,

- 𝛾→𝛽 is not true.

Definition. A relation is in the second normal form (2NF) if:

1. it is in the first normal form and

2. every (simple or composite) non-prime attribute is fully functionally dependent on every key of the relation.

Sabina S. CS

<!-- page 5 -->
- obs. Let 𝑅 be a 1NF relation that is not 2NF. Then 𝑅 has a composite key (and a functional dependency 𝛼→𝛽 , where 𝛼 (simple or composite) is a proper subset of a key and 𝛽 is a non-prime attribute).

- decomposition

   - relation 𝑅[𝐴] ( 𝐴 - the set of attributes), 𝐾 - a key

   - 𝛽 non-prime, 𝛽 functionally dependent on 𝛼, 𝛼⊂𝐾 ( 𝛽 is functionally dependent on a proper subset of attributes from a key)

   - the 𝛼→𝛽 dependency can be eliminated if 𝑅 is decomposed into the following 2 relations:

      - 𝑅′ 𝛼⋃𝛽= 𝛱𝛼⋃𝛽 𝑅

      - 𝑅′′ 𝐴−𝛽= 𝛱𝐴−𝛽 𝑅

Sabina S. CS

<!-- page 6 -->
- we'll analyze the relation from Example 6

- EXAM[StudentName, Course, Grade, FacultyMember]

- key: {StudentName, Course}

- the functional dependency _{Course}_ → _{FacultyMember}_ holds => attribute _FacultyMember_ is not fully functionally dependent on a key, hence the EXAM relation is not in 2NF

- this dependency can be eliminated if EXAM is decomposed into the following 2 relations:

RESULTS[StudentName, Course, Grade] COURSES[Course, FacultyMember]

Sabina S. CS

<!-- page 7 -->
Example 7. Consider the following relation, storing students' learning contracts: CONTRACTS[LastName, FirstName, CNP, <u>CourseId, CourseName]</u> • key: {CNP, CourseId}

- functional dependencies: _{CNP}_ → _{LastName, FirstName}_ , _{CourseId}_ → _{CourseName}_

- to eliminate these dependencies, the relation is decomposed into the following three relations:

- STUDENTS[CNP, LastName, FirstName] COURSES[CourseId, CourseName] LEARNING_CONTRACTS[CNP, <u>CourseId]</u>

Sabina S. CS

<!-- page 8 -->
- the notion of _transitive dependency_ is required for the third normal form

Definition. An attribute _Z_ is transitively dependent on an attribute _X_ if ∃𝑌 such that 𝑋→𝑌 , 𝑌→𝑍 _,_ 𝑌→𝑋 does not hold (and _Z_ is not in 𝑋 or 𝑌 ). Definition. A relation is in the third normal form (3NF) if it is in the second normal form and no non-prime attribute is transitively dependent on any key in the relation.

Another definition: A relation 𝑅 is in the third normal form (3NF) if, for every non-trivial functional dependency 𝑋→𝐴 that holds over 𝑅 :

- 𝑋 is a superkey, or

- 𝐴 is a prime attribute.

Sabina S. CS

<!-- page 9 -->
### Example 8. The BSc examination results are stored in the relation:

BSC_EXAM [StudentName, Grade, Supervisor, Department]

- the relation stores the supervisor and the department in which she works

- since the relation contains data about students (i.e., one row per student), _StudentName_ can be chosen as the key

- the following functional dependency holds: _{Supervisor}_ → _{Department}_ ⇒ the relation is not in 3NF

- to eliminate this dependency, the relation is decomposed into the following 2 relations:

RESULTS [StudentName, Grade, Supervisor] SUPERVISORS [Supervisor, Department]

Sabina S. CS

<!-- page 10 -->
### Example 9. The following relation stores addresses for a group of people:

ADDRESSES [CNP, LastName, FirstName, ZipCode, City, Street, No]

- key: {CNP}

- identified dependency: _{ZipCode}_ → dependency in this relation?)

_{City}_ (can you identify another

- since this dependency holds, relation ADDRESSES is not in 3NF, therefore it must be decomposed:

ADDRESSES'[CNP, LastName, FirstName, ZipCode, Street, No] ZIPCODES[ZipCode, City]

Sabina S. CS

<!-- page 11 -->
Example 10. The following relation stores the exam session schedule: EX_SCHEDULE[Date, Hour, Faculty_member, Room, Group]

• the following restrictions are expressed via <u>key definitions</u> and <u>functional</u> : <u>dependencies</u>

1. a group of students has at most one exam per day

=> _{Date, Group}_ is a key

2. on a certain date and time, a faculty member has at most one exam

_=> {Faculty_member, Date, Hour}_ is a key

3. on a certain date and time, there is at most one exam in a room

=> _{Room, Date, Hour}_ is a key

4. a faculty member doesn't change the room in a day

=> the following dependency holds: _{Faculty_member, Date}_ → _{Room}_

Sabina S. CS

<!-- page 12 -->
- all attributes appear in at least one key, i.e., there are no non-prime attributes

- given the normal forms' definitions specified thus far, the relation is in 3NF • objective: eliminate the _{Faculty_member, Date}_ → _{Room}_ functional dependency

Definition. A relation is in the Boyce-Codd (BCNF) normal form if every determinant (for a functional dependency) is a key (informal definition - simplifying assumption: determinants are not too big; only non-trivial functional dependencies are considered).

Sabina S. CS

<!-- page 13 -->
- to eliminate the functional dependency, the original relation must be decomposed into:

EX_SCHEDULE'[Date, Hour, Faculty_member, Group], ROOM_ALLOCATION[Faculty_member, Date, Room]

- these relations don't contain other functional dependencies, i.e., they are in BCNF

- however, the key associated with the 3rd constraint, _{Room, Date, Hour}_ , does not exist anymore

- if this constraint is to be kept, it needs to be checked in a different manner (e.g., through the program)

Sabina S. CS

<!-- page 14 -->
- R[A] - a relation

- F - a set of functional dependencies

- 𝛼 – a subset of attributes

- problems

- I. compute the closure of F: F+

II. compute the closure of a set of attributes under a set of functional dependencies, e.g., the closure of 𝛼 under F: 𝛼+

Sabina S. CS

<!-- page 15 -->
- R[A] - a relation

- F - a set of functional dependencies

- problems

- I. compute the closure of F: F+

- the set F+ contains all the functional dependencies implied by F

- F implies a functional dependency _f_ if _f_ holds on every relation that satisfies F

- the following 3 rules can be repeatedly applied to compute F+ (Armstrong's Axioms):

   - 𝛼 , 𝛽 , 𝛾 - subsets of attributes of 𝐴

   1. reflexivity: if 𝛽⊆𝛼 , then 𝛼→𝛽

   2. augmentation: if 𝛼→𝛽 , then 𝛼𝛾→𝛽𝛾

   3. transitivity: if 𝛼→𝛽 and 𝛽→𝛾 , then 𝛼→𝛾

- these rules are complete (they compute the closure) and sound (no erroneous Sabina S. CS

- functional dependencies can be derived)

<!-- page 16 -->
- R[A] - a relation

• F - a set of functional dependencies

- problems

I. compute the closure of F: F+

- the following rules can be derived from Armstrong's Axioms:

4. union: if 𝛼→𝛽 and 𝛼→𝛾 ,then 𝛼→𝛽𝛾

𝛼→𝛽 => 𝛼𝛼→𝛼𝛽

augmentation

𝛼→𝛾 => 𝛼𝛽→𝛽𝛾

augmentation

=> 𝛼→𝛽𝛾 transitivity

5. decomposition: if 𝛼→𝛽𝛾 , then 𝛼→𝛽 and 𝛼→𝛾 => 𝛼→𝛽𝛾 𝛼→𝛽 ( 𝛼→𝛾 transitivity 𝛽𝛾→𝛽 (reflexivity)

=> 𝛼→𝛽 ( 𝛼→𝛾 can similarly be shown to hold) transitivity

Sabina S. CS

<!-- page 17 -->
- R[A] - a relation

- F - a set of functional dependencies

- problems

- I. compute the closure of F: F+

- the following rules can be derived from Armstrong's Axioms:

6. pseudotransitivity: if 𝛼→𝛽 and 𝛽𝛾→𝛿 , then 𝛼𝛾→𝛿 =>

𝛼→𝛽 => 𝛼𝛾→𝛽𝛾 𝛼𝛾→𝛿 transitivity

𝛽𝛾→𝛿

- 𝛼 , 𝛽 , 𝛾 , 𝛿 - subsets of attributes of 𝐴

Sabina S. CS

<!-- page 18 -->
- R[A] - a relation

- F - a set of functional dependencies

- 𝛼 – a subset of attributes

- problems

II. compute the closure of a set of attributes under a set of functional dependencies

- determine the closure of 𝛼 under F, denoted as 𝛼+

- 𝛼+ - the set of attributes that are functionally dependent on attributes in 𝛼 (under F)

Sabina S. CS

<!-- page 19 -->
- R[A] - a relation

• F - a set of functional dependencies

• 𝛼 – a subset of attributes

- problems

II. compute the closure of a set of attributes under a set of functional dependencies

- algorithm

`closure :=` 𝛼 ;

```
repeatuntilthereisnochange:
```

`for every functional dependency` 𝛽→𝛾 `in F if` 𝛽⊆ `closure`

`then closure := closure` ⋃𝛾 `;`

Sabina S. CS

<!-- page 20 -->
- see lecture problems

   - R - a relation, F - a set of functional dependencies, _f -_ a functional dependency

      - show that _f_ is in F+

   - R - a relation, F - a set of functional dependencies, 𝛼 - a subset of the set of attributes of R

      - compute 𝛼+

Sabina S. CS

<!-- page 21 -->
## References

- [Ta13] ȚÂMBULEA, L., Curs Baze de date, Facultatea de Matematică și Informatică, UBB, 2013-2014

- [Ra00] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems (2nd Edition), McGraw-Hill, 2000

- [Da03] DATE, C.J., An Introduction to Database Systems (8th Edition), AddisonWesley, 2003

- [Ga08] GARCIA-MOLINA, H., ULLMAN, J., WIDOM, J., Database Systems: The Complete Book, Prentice Hall Press, 2008

- [Ha96] HANSEN, G., HANSEN, J., Database Management And Design (2nd Edition), Prentice Hall, 1996

- [Ra07] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems, McGrawHill, 2007, <u>http://pages.cs.wisc.edu/~dbbook/openAccess/thirdEdition/slides/slides3ed.html</u>

- • [Ul11] ULLMAN, J., WIDOM, J., A First Course in Database Systems, <u>http://infolab.stanford.edu/~ullman/fcdb.html</u>

Sabina S. CS
