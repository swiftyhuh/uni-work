<!-- page 1 -->
# Databases

Lecture 4

Querying Relational Databases Using SQL (II) Functional Dependencies. Normal Forms

Sabina S. CS

<!-- page 2 -->
Find the average age of researchers who are at least 18 years old for each impact factor with at least 10 researchers.

```
SELECT R.ImpactFactor, AVG(R.Age) AS AvgAge
FROM Researchers R
```

```
WHERE R.Age>= 18
GROUP BY R.ImpactFactor
HAVING 9 < (SELECT COUNT(*)
```

```
FROM Researchers R2
WHERE R2.ImpactFactor = R.ImpactFactor)
```

Sabina S. CS

<!-- page 3 -->
### Problem

See lecture query: _Find the most prolific researchers, i.e., those with the largest number of papers_ , on schema _AuthorContribution(RID,_ _<u>PID, Year).</u>_ Does it compute the same result on _AuthorContribution(RID,_ _<u>PID, Year)</u>_ ? If not, change it so the intended result is computed on this schema as well.

Sabina S. CS

<!-- page 4 -->
Find the name and age of the oldest researcher. `SELECT R.Name, MAX(R.Age) FROM Researchers R`

--error: if the SELECT clause contains an aggregation operator, then it must contain only aggregation operators, unless the query has a GROUP BY clause

### Correct query:

```
SELECT R.Name, R.Age
FROMResearchers R
WHERE R.Age=(SELECT MAX(R2.Age)
FROMResearchers R2)
```

Sabina S. CS

<!-- page 5 -->
### • ORDER BY, TOP

Sort researchers by impact factor (in descending order) and age (in ascending order).

```
SELECT*
```

```
FROM Researchers R
ORDER BY R.ImpactFactorDESC, R.AgeASC
```

Retrieve the names and ages of the top 10 researchers ordered by name. `SELECT TOP 10 R.Name, R.Age FROM Researchers R ORDER BY R.Name`

Sabina S. CS

<!-- page 6 -->
Find the top 25% researchers (all the data) ordered by age (descending). `SELECT TOP 25 PERCENT *`

```
FROM Researchers R
```

```
ORDER BY R.AgeDESC
```

Find the number of researchers for each impact factor. Order the result by the number of researchers.

```
SELECT R.ImpactFactor, COUNT(*) AS NoR
FROM Researchers R
```

```
GROUP BY R.ImpactFactor
ORDER BY NoR
```

Sabina S. CS

<!-- page 7 -->
• obs. intersection queries can be expressed with IN. Find the names of researchers who have published in IDEAS and EDBT. `SELECT R.Name FROM Researchers R INNER JOIN AuthorContribution A ON R.RID = A.RID`

```
INNER JOIN Papers P ON A.PID = P.PID
WHERE P.Conference= 'IDEAS' AND
R.RID IN (SELECT A2.RID
```

```
FROM AuthorContributionA2 INNER JOIN Papers P2
ON A2.PID = P2.PID
WHERE P2.Conference = 'EDBT')
```

Sabina S. CS

<!-- page 8 -->
• obs. set-difference queries can be expressed with NOT IN. Find the researchers who have published in EDBT but not in IDEAS. `SELECT A.RID`

```
FROM AuthorContributionA INNER JOIN Papers P ON A.PID = P.PID
WHERE P.Conference= 'EDBT' AND
```

```
A.RID NOT IN (SELECT A2.RID
```

```
FROM AuthorContributionA2 INNER JOIN Papers P2
ON A2.PID = P2.PID
WHERE P2.Conference = 'IDEAS')
```

Sabina S. CS

<!-- page 9 -->
Find researchers whose IF is greater than the IF of some researcher called _Ionescu_ .

```
SELECT R.RID
FROM Researchers R
WHERE R.ImpactFactor>
(SELECT MIN(R2.ImpactFactor)
FROM Researchers R2
WHERE R2.Name = 'Ionescu')
```

Sabina S. CS

<!-- page 10 -->
Find researchers whose IF is greater than the IF of every researcher called _Ionescu._

```
SELECT R.RID
FROM Researchers R
WHERE R.ImpactFactor>
(SELECT MAX(R2.ImpactFactor)
FROM Researchers R2
WHERE R2.Name = 'Ionescu')
```

Sabina S. CS

<!-- page 11 -->
### • the SELECT statement:

ALL ∗ SELECT DISTINCT expr1 [AS column1] [, expr2 [AS column2]] … TOP n PERCENT FROM source1 alias1 [, source2 [alias2]] … [WHERE qualification] [GROUP BY grouping_list] [HAVING group_qualification] UNION [ALL] INTERSECT SELECT_statement EXCEPT column1 ASC column2 ASC ORDER BY … column1_number DESC , column2_number DESC

Sabina S. CS

<!-- page 12 -->
- non-procedural query

- SELECT statement evaluation: the result is a relation (table)

- data can be obtained from one or multiple data sources; a source can have an associated _alias_ , used only in the SELECT statement

- various expressions are evaluated on the data (from the above-mentioned sources)

- a source column can be qualified with the source's name (or alias)

Sabina S. CS

<!-- page 13 -->
- a data source can be:

   1. table / view in the database

   2. (SELECT_statement)

   3. join_expression:

• source1 [alias1] join_operator source2 [alias2] ON join_condition

   - (join_expression)

- a join condition can be of the form:

   - elementary_cond

   - (condition)

   - NOT condition

   - condition1 AND condition2

   - condition1 OR condition2

Sabina S. CS

<!-- page 14 -->
- an elementary join condition (elementary_cond) among two data

- sources can be of the form:

- [source1_alias.]column1 relational_operator [source2_alias.]column2 • expression1 relational_operator expression2 (expression1 and expression2 use columns from different sources)

Sabina S. CS

<!-- page 15 -->
- the WHERE clause can contain filter and join conditions

- filter conditions:

   - expression relational_operator expression

   - expression [NOT] BETWEEN valmin AND valmax

   - expression [NOT] LIKE pattern

   - expression IS [NOT] NULL

   - expression [NOT] IN (value [, value] ...)

   - expression [NOT] IN (subquery)

   - expression relational_operator {ALL | ANY} (subquery)

   - [NOT] EXISTS (subquery)

- filter conditions can be:

   - elementary (described above)

   - composed with logical operators and parentheses

Sabina S. CS

<!-- page 16 -->
- obs: not all DBMSs support TOP

   - MySQL: SELECT ... LIMIT n

   - Oracle: SELECT ... WHERE ROWNUM <= n

- rules for building expressions:

   - operands: constants, columns, system functions, user functions

   - operators: corresponding to operands

- ordering records: the ORDER BY clause

Sabina S. CS

<!-- page 17 -->
### • the SELECT statement - logical processing (Transact-SQL)

### FROM

### WHERE

### GROUP BY

### HAVING

### SELECT

### DISTINCT

### ORDER BY

### TOP

Sabina S. CS

<!-- page 18 -->
### Functional Dependencies. Normal Forms

Sabina S. CS

<!-- page 19 -->
- there are multiple ways to model a data collection in the relational model (using tables)

- database design should be carried out in such a manner that subsequent queries and operations are performed as smoothly as possible, i.e.:

   - no additional tests are required when changing data

   - operations can be performed through SQL statements alone

- the above mentioned operations can be easily carried out when relations satisfy certain conditions (i.e., relations are in a certain normal form)

Sabina S. CS

<!-- page 20 -->
- the most common normal forms: 1NF, 2NF, 3NF, BCNF, 4NF, 5NF

- they were defined by Codd (the first 3), Boyce and Codd (BCNF), and Fagin (4NF, 5NF)

- the following inclusions hold (for relations that satisfy various normal forms):

<!-- Start of picture text -->
1NF 2NF 3NF BCNF 4NF 5NF <!-- End of picture text -->

Sabina S. CS

<!-- page 21 -->
### data redundancy

- generates a series of problems; some can be tackled by replacing a relation with a collection of smaller relations; each of the latter contains a (strict) subset of attributes from the original relation

- such decompositions can generate new problems (e.g., some data could be lost)

- ideally, only redundancy-free schemas should be allowed

- one should at least be able to identify schemas with redundancy, even if such schemas are allowed (e.g., for performance reasons)

Sabina S. CS

<!-- page 22 -->
- if a relation is not in normal form X, it can be decomposed into multiple relations that are in normal form X

Definition. The projection operator is used to decompose a relation. Let 𝑅 𝐴1, 𝐴2, … , 𝐴𝑛 be a relation and 𝛼= 𝐴𝑖1, 𝐴𝑖2, … , 𝐴𝑖𝑝 a subset of attributes, 𝛼⊂{𝐴1, 𝐴2, … , 𝐴𝑛} . The projection of relation 𝑅 on 𝛼 is: 𝑅′ 𝑅= 𝛱 𝑅= 𝑟 𝐴𝑖1, 𝐴𝑖2, … , 𝐴𝑖𝑝 = 𝛱𝛼 𝛼𝑟∈𝑅} 𝐴𝑖1,𝐴𝑖2,…,𝐴𝑖𝑝

where ∀𝑟= 𝑎1, 𝑎2, … , 𝑎𝑛 ∈𝑅⇒𝛱𝛼 𝑟= 𝑟 𝛼= 𝑎𝑖1, 𝑎𝑖2, … , 𝑎𝑖𝑝 and all elements in 𝑅′ are distinct.

∈𝑅′ ,

Definition. The natural join operator is used to compose relations. Let _R[_ 𝛼 _,_ 𝛽 _]_ , _S[_ 𝛽 _,_ 𝛾 _]_ be two relations over the specified sets of attributes, 𝛼∩𝛾 _=_ ∅ . The natural join of relations _R_ and _S_ is the relation:

𝑅∗𝑆 𝑠 𝑠 𝛼, 𝛽, 𝛾= 𝛱𝛼 𝑟, 𝛱𝛽 𝑟, 𝛱𝛾 𝑟∈𝑅, 𝑠∈𝑆𝑎𝑛𝑑𝛱𝛽 𝑟= 𝛱𝛽

Sabina S. CS

<!-- page 23 -->
- a relation 𝑅 can be decomposed into multiple new relations 𝑅1, 𝑅2, … , 𝑅𝑚; the decomposition is good if 𝑅= 𝑅1 ∗𝑅2 ∗⋯∗𝑅𝑚 , i.e., 𝑅 's data can be obtained from the data stored in relations 𝑅1, 𝑅2, … , 𝑅𝑚 (no data is added / lost through decomposition / composition)

- e.g., a decomposition that is not good:

Example 1. LearningContracts[Student, FacultyMember, Course], and two new relations obtained by applying the projection operator to this relation: SF[Student, FacultyMember] and FC[FacultyMember, Course]

- assume the original relation contains the following values:

|LearningContracts|Student|FacultyMember|Course|
|---|---|---|---|
|r1|s1|f1|c1|
|r2|s2|f2|c2|
|r3|s1|f2|c3|

Sabina S. CS

<!-- page 24 -->
• using the 𝛱 and * operators, the following values are obtained for the 2 projections and their natural join:

|SF|Student|FacultyMember|
|---|---|---|
|r1|s1|f1|
|r2|s2|f2|
|r3|s1|f2|

|FC|FacultyMember|Course|
|---|---|---|
|r1|f1|c1|
|r2|f2|c2|
|r3|f2|c3|

|SF*FC|Student|FacultyMember|Course|
|---|---|---|---|
|r1|s1|f1|c1|
|r2|s2|f2|c2|
|?|s2|f2|c3|
|?|s1|f2|c2|
|r3|s1|f2|c3|

Sabina S. CS

<!-- page 25 -->
|SF*FC|Student|FacultyMember|Course|
|---|---|---|---|
|r1|s1|f1|c1|
|r2|s2|f2|c2|
|?|s2|f2|c3|
|?|s1|f2|c2|
|r3|s1|f2|c3|

- the decomposition is not good, since the SF*FC relation contains extra records, i.e., records that were not present in the original relation

Sabina S. CS

<!-- page 26 -->
- _simple attribute_

- _composite attribute_ - a set of attributes in a relation (with at least two attributes)

- in some applications, attributes (simple or composite) can take on multiple values for a record in the relation - _repeating_ attributes

- when defining a relation (in the relational model), attribute values must be scalar, atomic (they cannot be further decomposed)

Sabina S. CS

<!-- page 27 -->
### Example 2. Consider the relation:

STUDENT [NAME, BIRTHYEAR, GROUP, COURSE, GRADE]

- key: NAME

- _composite repeating attribute:_ the pair {COURSE, GRADE}

- this relation could store the following values:

|NAME|BIRTHYEAR|GROUP|COURSE|GRADE|
|---|---|---|---|---|
|Ioana|2000|921|Databases|10|
||||Distributed Operating Systems Probabilities and Statistics|9.99 10|
|Vasile|2000|925|Databases|10|
||||Distributed Operating Systems|9.98|
||||Probabilities and Statistics|10|
||||Logical and Functional Programming|10|

Sabina S. CS

<!-- page 28 -->
### Example 3. Consider the relation:

BOOK [BId, AuthorsNames, Title, Publisher, PublishingYear, Keywords]

- key: BId

- _simple repeating attributes_ : AuthorsNames, Keywords

- the BId attribute

   - could have an actual meaning (an id could be associated with each book)

   - could be introduced as a key (with distinct values that are automatically generated)

Sabina S. CS

<!-- page 29 -->
- repeating attributes cannot be used in the relational model, hence they are to be avoided, without losing data

- let 𝑅 𝐴 be a relation; 𝐴 - the set of attributes

- let 𝛼 be a repeating attribute in 𝑅 (simple or composite)

- 𝑅 can be decomposed into 2 relations, such that 𝛼 is not a repeating attribute anymore

- if 𝐾 is a key in 𝑅 , the two relations into which 𝑅 is decomposed are:

   - 𝑅′ 𝐾⋃𝛼= 𝛱𝐾⋃𝛼 𝑅

   - 𝑅′′ 𝐴−𝛼= 𝛱𝐴−𝛼 𝑅

Sabina S. CS

<!-- page 30 -->
Example 4. The STUDENT relation from example 2 is decomposed into the following 2 relations:

GENERAL_DATA [NAME, BIRTHYEAR, GROUP], RESULTS [NAME, COURSE, GRADE].

### • the values in these relations are:

|NAME|BIRTHYEAR|GROUP|
|---|---|---|
|Ioana|2000|921|
|Vasile|2000|925|

|NAME|COURSE|GRADE|
|---|---|---|
|Ioana|Databases|10|
|Ioana|Distributed Operating Systems|9.99|
|Ioana|Probabilities and Statistics|10|
|Vasile|Databases|10|
|Vasile|Distributed Operating Systems|9.98|
|Vasile|Probabilities and Statistics|10|
|Vasile|Logical and Functional Programming|10|

Sabina S. CS

<!-- page 31 -->
Example 5. The BOOK relation in example 3 is decomposed into the following 3 relations (there are two repeating attributes in the BOOK relation): BOOKS [BId, Title, Publisher, PublishingYear], AUTHORS [BId, AuthorName], KEYWORDS [BId, Keyword].

- is a book is not associated with any authors / keywords, it needs to have one corresponding tuple in AUTHORS / KEYWORDS, with the second attribute set to _null_ ; in the absence of such tuples, the BOOK relation can't be obtained from the three relations using just the natural join (outer join operators are required)

Sabina S. CS

<!-- page 32 -->
Definition. A relation is in the first normal form (1NF) if it doesn't have any repeating attributes.

• obs. some DBMSs can manage non-1NF relations (e.g., Oracle)

Sabina S. CS

<!-- page 33 -->
- the following 3 relational normal forms use a very important notion: the _functional dependency_ among subsets of attributes

- the database administrator is responsible with determining the functional dependencies; these depend on the nature, the semantics of the data stored in the relation

->

Sabina S. CS

<!-- page 34 -->
Definition. Let 𝑅[𝐴1, 𝐴2, … , 𝐴𝑛] be a relation and 𝛼, 𝛽 two subsets of attributes of 𝑅 . The (simple or composite) attribute 𝛼 functionally determines attribute 𝛽 (simple or composite), notation:

𝛼→𝛽

if and only if every value of 𝛼 in 𝑅 is associated with a precise, unique value for 𝛽 (this association holds throughout the entire existence of relation 𝑅 ); if an 𝛼 value appears in multiple rows, each of these rows will contain the same value for 𝛽 :

𝛱𝛼 𝑟= 𝛱𝛼 𝑟′ 𝑖𝑚𝑝𝑙𝑖𝑒𝑠𝛱𝛽 𝑟= 𝛱𝛽 𝑟′

- in the dependency 𝛼→𝛽 , 𝛼 is the _determinant_ , and 𝛽 is the _dependent_

- the functional dependency can be regarded as a property (restriction) that must be satisfied by the database throughout its existence: values can be added / changed in the relation only if the functional dependency is satisfied

Sabina S. CS

<!-- page 35 -->
- if a relation contains a functional dependency, some associations among values will be stored multiple times (data redundancy)

- to describe some of the problems that can arise in this context, we'll consider the EXAM relation, storing students' final exam results

- Example 6. EXAM [StudentName, Course, Grade, FacultyMember]

- key: {StudentName, Course}

- a course is associated with one faculty member, a faculty member can be associated with several courses ⇒ the following restriction (functional dependency) must be satisfied: _{Course}_ → _{FacultyMember}_

|EXAM|StudentName|Course|Grade|FacultyMember|
|---|---|---|---|---|
|1|Pop Ioana|Computer Networks|10|Matei Ana|
|2|Vlad Ana|Operating Systems|10|Simion Bogdan|
|3|Vlad Ana|Computer Networks|9.98|Matei Ana|
|4|Dan Andrei|Computer Networks|10|Matei Ana|
|5|Popescu Alex|Operating Systems|9.99|Simion Bogdan|

Sabina S. CS

<!-- page 36 -->
- if the relation contains such a functional dependency, the following problems can arise (some of them need to be solved through additional programming efforts - executing a SQL command is not enough):

   - <u>wasting space: the same associations are stored multiple times, e.g., the</u> one among _Computer Networks_ and _Matei Ana_ is stored 3 times;

   - <u>update anomalies:</u> if the _FacultyMember_ is changed for course _c_ , the change must be carried out in all associations involving course _c_ (without knowing how many such associations exist), otherwise the database will contain errors (it will be inconsistent); if the _FacultyMember_ value is changed in the 2nd record, but not in the 5th record, the operation will introduce an error in the relation (the data will be incorrect);

   - <u>insertion anomalies: one cannot specify the</u> _FacultyMember_ for a course _c_ , unless there’s at least one student with a grade in course _c_ ;

Sabina S. CS

<!-- page 37 -->
- <u>deletion anomalies:</u> when some records are deleted, data that is not intended to be removed can be deleted as well; e.g., if records 1, 3 and 4 are deleted, the association among _Course_ and _FacultyMember_ is also removed from the database

- the functional dependency among sets of attributes is what causes the previous anomalies; to eliminate these problems, the associations (dependencies) among values should be kept once in a separate relation, the initial relation should be a

- therefore, decomposed (via good decomposition - data should not be lost or added); such a decomposition is performed in the database design phase, when functional dependencies can be identified

Sabina S. CS

<!-- page 38 -->
### Appendix - More SQL Queries

Sabina S. CS

<!-- page 39 -->
### • more query examples on the database:

Sabina S. CS

<!-- page 40 -->
• A student's trajectory (academic year and group). `SELECT acad_year, sgroup FROM Trajectory WHERE program = 2 AND reg_number = '7654'`

• A student's grades. `SELECT acad_year, course, no_credits, grade FROM Results WHERE program = 2 AND reg_number = '7654'`

Sabina S. CS

<!-- page 41 -->
• Students who belonged to group 915 in the academic year 2017-2018. `SELECT last_name, first_name, s.reg_number FROM Students s INNER JOIN Trajectory t ON s.program=t.program AND s.reg_number=t.reg_number WHERE acad_year=2017 AND sgroup='915' SELECT last_name, first_name, s.reg_number FROM Students s INNER JOIN`

```
(SELECT *
FROM Trajectory
WHERE acad_year=2017 AND sgroup='915') t
ON s.reg_number=t.reg_numberAND s.program=t.program
```

Sabina S. CS

<!-- page 42 -->
• Students who belong to a group, but have no grades - in the academic year 2017-2018. `SELECT last_name, first_name FROM Students AS s WHERE EXISTS (SELECT * FROM Trajectory t WHERE acad_year=2017 AND t.program=s.program AND t.reg_number=s.reg_number) AND NOT EXISTS (SELECT * FROM Results r WHERE acad_year=2017 AND s.program=r.program AND s.reg_number=r.reg_number) --ORDER BY last_name, first_name`

Sabina S. CS

<!-- page 43 -->
• Students who belong to a group, but have no grades - in the academic year 2017-2018.

```
SELECT last_name, first_name
FROM (Students s INNER JOIN
(SELECT *
FROM Trajectory WHERE acad_year=2017) t
ON s.program=t.programAND s.reg_number=t.reg_number
)
LEFT JOIN
(SELECT *
FROM Results
WHERE acad_year=2017) r
ON s.program=r.programAND s.reg_number=r.reg_number
WHERE grade IS NULL
```

Sabina S. CS

<!-- page 44 -->
### • The number of students in the database.

```
SELECT COUNT(*) AS NoS
```

```
FROM Students
```

• The number of students born on the same day, regardless of year and month. `SELECT SUBSTRING(cnp,6,2) AS day, COUNT(*) AS NoS FROM Students`

```
GROUP BY SUBSTRING(cnp,6,2)
```

- The grades of a given student (only the maximum grade is required for each course).

```
SELECT course, no_credits, MAX(grade) AS maxgrade
FROM Results
```

```
WHERE program = 3 AND reg_number='virtualstudent11'
GROUP BY course, no_credits
```

```
--ORDER BY course
```

Sabina S. CS

<!-- page 45 -->
• The grades of a given student (only the maximum grade is required for each course). Include the name of the course in the answer set. `SELECT id, name, no_credits, maxgrade AS grade FROM Courses c INNER JOIN`

```
(SELECT course, no_credits, MAX(grade) AS maxgrade
FROM Results
```

```
WHERE program = 3 AND reg_number='virtualstudent11'
GROUP BY course, no_credits) r
ON c.id = r.course
```

```
--ORDER BY name
```

Sabina S. CS

<!-- page 46 -->
• For each student name that appears at least 3 times, retrieve all students with that name.

`SELECT * FROM Students WHERE last_name IN (SELECT last_name FROM Students GROUP BY last_name HAVING COUNT(*)>=3) --ORDER BY last_name, first_name` * rewrite the query without IN

Sabina S. CS

<!-- page 47 -->
• The number of students in each program and year of study in 2018. `SELECT g.program, g.year_of_study, COUNT(*) AS NoS FROM Trajectory t INNER JOIN Groups g ON t.program=g.program AND t.sgroup=g.id AND t.acad_year=g.acad_year WHERE t.acad_year=2018 GROUP BY g.program, g.year_of_study`

Sabina S. CS

<!-- page 48 -->
• The last name, first name, program (id), registration number, number of passed exams, number of credits, and gpa for each student with at least 30 credits in passed courses at the end of 2017.

```
SELECT last_name, first_name, s.program, s.reg_number, COUNT(*)
AS noc, SUM(no_credits) AS nocr,
SUM(gradem*no_credits)/SUM(no_credits) AS gpa
FROM Students s INNER JOIN
```

```
(SELECT program, reg_number, course, no_credits, MAX(grade)
AS gradem
FROM Results
WHERE acad_year=2017 AND grade>=5
GROUP BY program, reg_number, course, no_credits
) r
```

```
ON s.program=r.programAND s.reg_number=r.reg_number
GROUP BY s.program, s.reg_number, last_name, first_name
HAVING SUM(no_credits)>=30
ORDER BY 3,1,2
```

Sabina S. CS

<!-- page 49 -->
• For every course, the number of grades and the number of passing grades in 2017.

* a. MySQL *

```
SELECT name, COUNT(*) AS nrg, SUM(IF(r.grade>= 5,1,0))
AS nrpg
FROM Courses c INNER JOIN
(SELECT * FROM Results WHERE acad_year= 2017) r
ON c.id = r.course
GROUP BY name
--ORDER BY 1
```

Sabina S. CS

<!-- page 50 -->
• For every course, the number of grades and the number of passing grades in 2017.

* b. Oracle *

```
SELECT name, COUNT(*) AS nrg, SUM(CASE WHEN (r.grade>= 5) THEN
1 ELSE 0 END) AS nrpg
FROM Courses c INNER JOIN
```

```
(SELECT * FROM Results WHERE acad_year= 2017) r
ON c.id = r.course
```

```
GROUP BY name
```

```
--ORDER BY 1
```

Sabina S. CS

<!-- page 51 -->
### • * The grade average for each group in 2017. *

a. Maximum & passing grades in 2017. `CREATE VIEW studgrades AS SELECT program, reg_number, course, no_credits, MAX(grade) AS mgrade`

```
FROM Results
WHERE acad_year=2017 AND grade>=5
GROUP BY program, reg_number, course, no_credits
```

b. Students' grade average (in 2017). `CREATE VIEW studavg AS SELECT program, reg_number,`

```
SUM(no_credits*mgrade)/SUM(no_credits) AS gradeavg
FROM studgrades
```

```
GROUP BY program, reg_number
HAVING SUM(no_credits) >= 30
```

Sabina S. CS

<!-- page 52 -->
### • * The grade average for each group in 2017. *

c. Final query: `SELECT sgroup, AVG(gradeavg) AS gravg FROM`

```
(SELECT program, reg_number, sgroup
FROM Trajectory
WHERE acad_year=2017) t
INNER JOIN studavgAS s
```

```
ON t.reg_number=s.reg_numberAND t.program=s.program
GROUP BY sgroup
```

- what happens if two groups in different programs have the same id?

Sabina S. CS

<!-- page 53 -->
• * The grade average for each program in 2017. * `CREATE VIEW programsavg AS SELECT id, name, AVG(gradeavg) AS pravg FROM Programs p INNER JOIN studavg s ON p.id=s.program GROUP BY id, name`

```
SELECT * FROM programsavg
```

Sabina S. CS

<!-- page 54 -->
## References

- [Ta13] ȚÂMBULEA, L., Curs Baze de date, Facultatea de Matematică și Informatică, UBB, 2013-2014

- [Ra00] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems (2nd Edition), McGraw-Hill, 2000

- [Da03] DATE, C.J., An Introduction to Database Systems (8th Edition), AddisonWesley, 2003

- [Ga08] GARCIA-MOLINA, H., ULLMAN, J., WIDOM, J., Database Systems: The Complete Book, Prentice Hall Press, 2008

- [Ha96] HANSEN, G., HANSEN, J., Database Management And Design (2nd Edition), Prentice Hall, 1996

- [Ra07] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems, McGrawHill, 2007, <u>http://pages.cs.wisc.edu/~dbbook/openAccess/thirdEdition/slides/slides3ed.html</u>

- [Si10] SILBERSCHATZ, A., KORTH, H., SUDARSHAN, S., Database System Concepts, McGraw-Hill, 2010, <u>http://codex.cs.yale.edu/avi/db-book/</u>

- [Ul11] ULLMAN, J., WIDOM, J., A First Course in Database Systems, <u>http://infolab.stanford.edu/~ullman/fcdb.html</u>

Sabina S. CS
