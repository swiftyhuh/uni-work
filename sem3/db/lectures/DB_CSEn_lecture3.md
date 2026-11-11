<!-- page 1 -->
# Databases

Lecture 3

The Relational Model (II) Querying Relational Databases Using SQL

Sabina S. CS

<!-- page 2 -->
## Managing Relational Databases with SQL

- ALTER TABLE – changes the structure of a defined table ALTER TABLE table_name operation

```
ALTER TABLE Students
ADD FavSymphonyVARCHAR(50)
```

- possible operations (differences among DBMSs)

   - add / change / remove a column

      - ADD column_definition

      - {ALTER COLUMN | MODIFY} column_definition

      - DROP COLUMN column_name

Sabina S. CS

<!-- page 3 -->
## Managing Relational Databases with SQL

- add / remove a constraint

   - ADD [CONSTRAINT constraint_name] PRIMARY KEY(column_list)

   - ADD [CONSTRAINT constraint_name] UNIQUE(column_list)

   - ADD [CONSTRAINT constraint_name] FOREIGN KEY (column_list) REFERENCES table_name[(column_list)] [ON UPDATE action] [ON DELETE action]

   - DROP [CONSTRAINT] constraint_name

Sabina S. CS

<!-- page 4 -->
## Managing Relational Databases with SQL

- DROP TABLE – removes a table DROP TABLE table_name

```
DROP TABLE Students
```

- Data Definition Language (DDL) - subset of SQL used to create / remove / change components (e.g., tables)

Sabina S. CS

<!-- page 5 -->
## Managing Relational Databases with SQL

- changing data in a table

• the INSERT command – adding records INSERT INTO table_name[(column_list)] VALUES (value_list) INSERT INTO table_name[(column_list)] subquery,

where _subquery_ refers to a set of records (generated with the SELECT statement)

```
INSERT INTO Students(sid, cnp, lastname, firstname, age)
VALUES (1, '123456789012', 'Popescu', 'Maria', 20)
```

Sabina S. CS

<!-- page 6 -->
## Managing Relational Databases with SQL

- changing data in a table

- the UPDATE command – changing records

UPDATE table_name SET column_name=expression [, column_name=expression] ... [WHERE condition]

- the command changes the records in the table that satisfy the condition in the WHERE clause; if the WHERE clause is omitted, all the records in the table are changed; the values of the columns specified in SET are changed to the associated expressions' values

```
UPDATEStudents
```

```
SET age = age + 1
```

```
WHERE cnp = '123456789012'
```

Sabina S. CS

<!-- page 7 -->
## Managing Relational Databases with SQL

- changing data in a table

- the DELETE command – removing records DELETE FROM table_name [WHERE condition]

- the command deletes the records in the table that satisfy the condition in the WHERE clause; if the WHERE clause is omitted, all the table's records are deleted `DELETE`

```
FROM Students
WHERE lastname = 'Popescu'
```

- Data Manipulation Language (DML) - subset of SQL used to pose queries, to add / update / remove data

Sabina S. CS

<!-- page 8 -->
## Managing Relational Databases with SQL

- filter conditions

   - expression comparison_operator expression

   - expression [NOT] BETWEEN valmin AND valmax

   - expression [NOT] LIKE pattern ("%" - any substring, "_" - one character)

   - expression IS [NOT] NULL

   - expression [NOT] IN (value [, value] ...)

   - expression [NOT] IN (subquery)

   - expression comparison_operator {ALL | ANY} (subquery)

   - [NOT] EXISTS (subquery)

Sabina S. CS

<!-- page 9 -->
## Managing Relational Databases with SQL

- filter conditions

   - elementary condition (previously described)

   - (condition)

   - NOT condition

   - condition1 AND condition2

   - condition1 OR condition2

Sabina S. CS

<!-- page 10 -->
## Managing Relational Databases with SQL

• 3-valued logic (truth values: _true_ , _false_ , _unknown_ )

||TRUE|FALSE|NULL|
|---|---|---|---|
|NOT|FALSE|TRUE|NULL|

|AND|TRUE|FALSE|NULL|
|---|---|---|---|
|TRUE|TRUE|FALSE|NULL|
|FALSE|FALSE|FALSE|FALSE|
|NULL|NULL|FALSE|NULL|

|OR|TRUE|FALSE|NULL|
|---|---|---|---|
|TRUE|TRUE|TRUE|TRUE|
|FALSE|TRUE|FALSE|NULL|
|NULL|TRUE|NULL|NULL|

Sabina S. CS

<!-- page 11 -->
### Querying Relational Databases Using SQL

Sabina S. CS

<!-- page 12 -->
### • basic SELECT query:

```
SELECT [DISTINCT] select-list
FROM from-list
```

```
WHERE qualification
```

- select-list

   - list of (expressions involving) attributes from relations in the from-list

- from-list

   - list of relation names; each of them can be followed by a range variable

- qualification

   - selection conditions on the data from the relations in the from-list

   - conditions ( _expr op expr_ , where _op_ ∈ { <, ≤, =, >, ≥, ≠ } and _expr_ is an expression that can include attributes, constants, etc) combined with the Sabina S. CS

   - logical operators AND, OR, NOT

<!-- page 13 -->
### • basic SELECT query:

```
SELECT [DISTINCT] select-list
FROM from-list
```

```
WHERE qualification
```

- the SELECT, FROM clauses - mandatory

- the WHERE clause - optional

Sabina S. CS

<!-- page 14 -->
### • the conceptual evaluation strategy:

```
SELECT [DISTINCT] select-list
```

```
FROM from-list
```

```
WHERE qualification
```

- compute the cross product of tables in the from-list

- remove the rows that don't meet qualification

- eliminate unwanted columns, i.e., those that don't appear in the select-list

- if DISTINCT is specified, remove duplicates

   - by default, duplicates are not eliminated

Sabina S. CS

<!-- page 15 -->
### • examples on the schema

Researchers( _<u>RID</u>_ : integer, _Name_ : string, _ImpactFactor_ : integer, _Age*_ : integer) Papers( _<u>PID</u>_ : integer, _Title_ : string, _Conference_ : string) AuthorContribution( _<u>RID</u>_ : integer, _<u>PID</u>_ : integer, _<u>Year</u>_ : integer)

* we use the _Age_ attribute for simplicity; it is preferable to store the date of birth, as it doesn't change every year

Sabina S. CS

<!-- page 16 -->
• Find the names of researchers who have worked on the paper with PID = 307. `SELECT R.Name`

```
FROM Researchers R, AuthorContributionA
WHERE R.RID = A.RID AND A.PID = 307
```

#### Researchers

|RID|Name|ImpactFactor|Age|
|---|---|---|---|
|1|Popescu|10|30|
|2|Ionescu|10|40|
|4|Andreescu|5|24|

#### AuthorContribution

|RID|PID|Year|
|---|---|---|
|1|307|2011|
|1|200|2012|
|2|307|2011|

Sabina S. CS

<!-- page 17 -->
### • compute the cross product of tables _Researchers_ and _AuthorContribution_

|RID|Name|ImpactFactor|Age|RID|PID|Year|
|---|---|---|---|---|---|---|
|1|Popescu|10|30|1|307|2011|
|1|Popescu|10|30|1|200|2012|
|1|Popescu|10|30|2|307|2011|
|2|Ionescu|10|40|1|307|2011|
|2|Ionescu|10|40|1|200|2012|
|2|Ionescu|10|40|2|307|2011|
|4|Andreescu|5|24|1|307|2011|
|4|Andreescu|5|24|1|200|2012|
|4|Andreescu|5|24|2|307|2011|

- _RID_ appears in both _Researchers_ and _AuthorContribution_ => it must be qualified (e.g., in the WHERE clause)

Sabina S. CS

<!-- page 18 -->
• remove the rows in the cross product that don't satisfy the condition `R.RID = A.RID AND A.PID = 307`

|RID|Name|ImpactFactor|Age|RID|PID|Year|
|---|---|---|---|---|---|---|
|1|Popescu|10|30|1|307|2011|
|1|Popescu|10|30|1|200|2012|
|1|Popescu|10|30|2|307|2011|
|2|Ionescu|10|40|1|307|2011|
|2|Ionescu|10|40|1|200|2012|
|2|Ionescu|10|40|2|307|2011|
|4|Andreescu|5|24|1|307|2011|
|4|Andreescu|5|24|1|200|2012|
|4|Andreescu|5|24|2|307|2011|

Sabina S. CS

<!-- page 19 -->
• remove the rows in the cross product that don't satisfy the condition `R.RID = A.RID AND A.PID = 307`

|RID|Name|ImpactFactor|Age|RID|PID|Year|
|---|---|---|---|---|---|---|
|1|Popescu|10|30|1|307|2011|
|1|Popescu|10|30|1|200|2012|
|1|Popescu|10|30|2|307|2011|
|2|Ionescu|10|40|1|307|2011|
|2|Ionescu|10|40|1|200|2012|
|2|Ionescu|10|40|2|307|2011|
|4|Andreescu|5|24|1|307|2011|
|4|Andreescu|5|24|1|200|2012|
|4|Andreescu|5|24|2|307|2011|

Sabina S. CS

<!-- page 20 -->
• remove the rows in the cross product that don't satisfy the condition `R.RID = A.RID AND A.PID = 307`

|RID|Name|ImpactFactor|Age|RID|PID|Year|
|---|---|---|---|---|---|---|
|1|Popescu|10|30|1|307|2011|
|1|Popescu|10|30|1|200|2012|
|1|Popescu|10|30|2|307|2011|
|2|Ionescu|10|40|1|307|2011|
|2|Ionescu|10|40|1|200|2012|
|2|Ionescu|10|40|2|307|2011|
|4|Andreescu|5|24|1|307|2011|
|4|Andreescu|5|24|1|200|2012|
|4|Andreescu|5|24|2|307|2011|

Sabina S. CS

<!-- page 21 -->
- remove the rows in the cross product that don't satisfy the condition `R.RID = A.RID AND A.PID = 307`

|RID|Name|ImpactFactor|Age|RID|PID|Year|
|---|---|---|---|---|---|---|
|1|Popescu|10|30|1|307|2011|
|2|Ionescu|10|40|2|307|2011|

Sabina S. CS

<!-- page 22 -->
### • remove the columns that don't appear in R.Name

<!-- Start of picture text -->
Name Popescu Ionescu <!-- End of picture text -->

Sabina S. CS

<!-- page 23 -->
### • basic queries

Find the names and ages of all researchers. Eliminate duplicates. `SELECT DISTINCT R.Name, R.Age FROM Researchers R`

Find the researchers with an impact factor > 3 (all the data about researchers). `SELECT R.RID, R.Name, R.ImpactFactor, R.Age FROM Researchers AS R`

```
WHERE R.ImpactFactor> 3
```

```
--SELECT *
```

Sabina S. CS

<!-- page 24 -->
Find the names of researchers who have published in the EDBT conference. `SELECT R.Name`

```
FROM Researchers R, AuthorContributionA, Papers P
WHERE R.RID = A.RID AND A.PID = P.PID AND P.Conference=
'EDBT'
```

Find the ids of researchers who have published in the EDBT conference. `SELECT A.RID`

```
FROM AuthorContributionA, Papers P
WHERE A.PID = P.PID AND P.Conference= 'EDBT'
```

Sabina S. CS

<!-- page 25 -->
Find the names of researchers who have published at least one paper. `SELECT R.Name`

```
FROM Researchers R, AuthorContributionA
```

```
WHERE R.RID = A.RID
```

Find the conferences that published Ionescu's papers. `SELECT P.Conference`

```
FROM Researchers R, AuthorContributionA, Papers P
WHERE R.RID = A.RID AND A.PID = P.PID AND R.Name= 'Ionescu'
```

- obs. There can be more than one researcher named Ionescu.

Sabina S. CS

<!-- page 26 -->
### • expressions in SELECT

Compute an incremented impact factor for researchers who worked on two different papers in the same year.

```
SELECT R.Name, R.ImpactFactor+ 1 ASNewIF
```

```
FROM Researchers R, AuthorContributionA1, AuthorContribution
A2
```

```
WHERE R.RID= A1.RID AND R.RID= A2.RID
AND A1.PID<> A2.PID
AND A1.Year= A2.Year
```

Sabina S. CS

<!-- page 27 -->
### • nested queries

– the WHERE clause

• IN

Find the names of researchers who have worked on the paper with PID = 307.

```
SELECT R.Name
```

```
FROM Researchers R
```

```
WHERE R.RIDIN
(SELECT A.RID
FROM AuthorContributionA
WHERE A.PID = 307)
```

Sabina S. CS

<!-- page 28 -->
Find the names of researchers who have published in EDBT. `SELECT R.Name FROM Researchers R WHERE R.RID IN`

```
(SELECT A.RID
FROM AuthorContributionA
WHERE A.PIDIN
(SELECT P.PID
FROM Papers P
WHERE P.Conference= 'EDBT'
)
```

```
)
```

Sabina S. CS

<!-- page 29 -->
Find the names of researchers who haven't published in EDBT. `SELECT R.Name FROM Researchers R WHERE R.RID NOT IN`

```
(SELECT A.RID
FROM AuthorContributionA
WHERE A.PIDIN
(SELECT P.PID
FROM Papers P
WHERE P.Conference= 'EDBT'
)
```

```
)
```

Sabina S. CS

<!-- page 30 -->
### • EXISTS

Find the names of researchers who have worked on the paper with PID = 307.

```
SELECT R.Name
```

```
FROM Researchers R
```

```
WHERE EXISTS(SELECT *
```

```
FROM AuthorContributionA
WHERE A.PID = 307 AND A.RID = R.RID)
```

Sabina S. CS

<!-- page 31 -->
### • operators ANY and ALL

Find researchers whose IF is greater than the IF of some researcher called _Ionescu._

```
SELECT R.RID
FROM Researchers R
WHERE R.ImpactFactor>ANY
(SELECT R2.ImpactFactor
FROMResearchers R2
WHERER2.Name = 'Ionescu')
```

Sabina S. CS

<!-- page 32 -->
expression = ANY(subquery)                expression IN(subquery) `SELECT R.Name FROM Researchers R WHERE R.RID = ANY`

```
(SELECT A.RID
FROMAuthorContributionA
WHEREA.PID= 300)
```

```
SELECT R.Name
FROM Researchers R
WHERE R.RID IN
(SELECT A.RID
FROMAuthorContributionA
WHEREA.PID= 300)
```

Sabina S. CS

<!-- page 33 -->
Find researchers whose IF is greater than the IF of every researcher called _Ionescu._

```
SELECT R.RID
FROM Researchers R
WHERE R.ImpactFactor>ALL
(SELECT R2.ImpactFactor
FROMResearchers R2
WHERER2.Name = 'Ionescu')
```

Sabina S. CS

<!-- page 34 -->
expression <> ALL(subquery)             expression NOT IN(subquery) `SELECT R.Name FROM Researchers R WHERE R.RID <> ALL`

```
(SELECT A.RID
FROMAuthorContributionA
WHEREA.PID= 300)
```

```
SELECT R.Name
FROM Researchers R
WHERE R.RID NOT IN
(SELECT A.RID
FROMAuthorContributionA
WHEREA.PID= 300)
```

Sabina S. CS

<!-- page 35 -->
- union, intersection, set-difference

Find the names of researchers who have published in EDBT or IDEAS. `SELECT R.Name`

```
FROM Researchers R, AuthorContributionA, Papers P
WHERE R.RID = A.RID AND A.PID = P.PID AND
```

- `(P.Conference = 'IDEAS' OR P.Conference = 'EDBT')`

Find the names of researchers who have published in EDBT and IDEAS. * Don't replace OR with AND!

```
SELECT R.Name
```

```
FROM Researchers R, AuthorContributionA, Papers P
WHERE R.RID = A.RID AND A.PID = P.PID AND
```

- `(P.Conference = 'IDEAS' AND P.Conference = 'EDBT')`

Sabina S. CS

<!-- page 36 -->
Find the names of researchers who have published in EDBT and IDEAS. `SELECT R.Name`

```
FROM Researchers R, AuthorContribution A1, Papers P1,
AuthorContribution A2, Papers P2
```

```
WHERE R.RID = A1.RID AND A1.PID = P1.PID AND
```

```
P1.Conference= 'IDEAS'AND
```

```
R.RID = A2.RID AND A2.PID = P2.PID AND
P2.Conference= 'EDBT'
```

Sabina S. CS

<!-- page 37 -->
Find the names of researchers who have published in EDBT but not in IDEAS. `SELECT R.Name`

```
FROM Researchers R, AuthorContributionA, Papers P
```

```
WHERE R.RID = A.RID AND A.PID = P.PID AND P.Conference= 'EDBT'
AND A.RID NOT IN(SELECT A2.RID
FROM AuthorContributionA2, Papers P2
WHERE A2.PID = P2.PID AND P2.Conference = 'IDEAS')
```

Sabina S. CS

<!-- page 38 -->
### • the JOIN operators

### • JOIN examples are described on the following relational database:

||Students|||Courses||Exa|ms||
|---|---|---|---|---|---|---|---|---|
|SID|Name|Group|CID|Name|StdId|CrsId|Grade|Credits|
|135|Alexandra|922|BD|Baze de date|135|BD|10|6|
|82|Paul|926|SGBD|Sisteme de Gestiune a Bl d D|82|SGBD|10|6|
|294|Ștefania|925|DMBD|azeor e ate Data Mining in Big Data|135|SGBD|10|6|

Sabina S. CS

<!-- page 39 -->
#### Students

||Students||E|xams|||
|---|---|---|---|---|---|---|
|SID|Name|Group|StdId|CrsId|Grade|Credits|
|135|Alexandra|922|135|BD|10|6|
|82|Paul|926|82|SGBD|10|6|
|294|Ștefania|925|135|SGBD|10|6|

- find all the students' grades; include the students' names in the answer set

1. inner join : source1 [alias] [INNER] JOIN source2 [alias] ON condition `SELECT *`

```
FROM Students S INNER JOIN Exams E ON S.SID = E.StdId
```

|SID|Name|Group|StdId|CrsId|Grade|Credits|
|---|---|---|---|---|---|---|
|135|Alexandra|922|135|BD|10|6|
|135|Alexandra|922|135|SGBD|10|6|
|82|Paul|926|82|SGBD|10|6|

Sabina S. CS

<!-- page 40 -->
#### Students

#### Exams

|SID|Name|Group|StdId|CrsId|Grade|Credits|
|---|---|---|---|---|---|---|
|135|Alexandra|922|135|BD|10|6|
|82|Paul|926|82|SGBD|10|6|
|294|Ștefania|925|135|SGBD|10|6|

- find all the students' grades; include students with no exams; the students' names must appear in the answer set

- 2. left outer join : source1 [alias] LEFT [OUTER] JOIN source2 [alias] ON condition `SELECT *`

```
FROM Students S LEFT JOIN Exams E ON S.SID = E.StdId
```

|SID|Name|Group|StdId|CrsId|Grade|Credits|
|---|---|---|---|---|---|---|
|135|Alexandra|922|135|BD|10|6|
|135|Alexandra|922|135|SGBD|10|6|
|82|Paul|926|82|SGBD|10|6|
|294|Ștefania|925|null|null|null|null|

Sabina S. CS

<!-- page 41 -->
#### Courses

#### Exams

|CID|Name|StdId|CrsId|Grade|Credits|
|---|---|---|---|---|---|
|BD|Baze de date|135|BD|10|6|
|SGBD|Sisteme de Gestiune a|82|SGBD|10|6|
|DMBD|Bazelor de Date Data Mining in Big Data|135|SGBD|10|6|

find all the exams (including the names of the courses); include courses with no exams 3. right outer join : source1 [alias] RIGHT [OUTER] JOIN source2 [alias] ON condition `SELECT *`

```
FROM Exams E RIGHT JOIN Courses C ON E.CrsId= C.CID
```

|StdId|CrsId|Grade|Credits|CID|Name|
|---|---|---|---|---|---|
|135|BD|10|6|BD|Baze de date|
|135|SGBD|10|6|SGBD|Sisteme de Gestiune a Bazelor de Date|
|82|SGBD|10|6|SGBD|Sisteme de Gestiune a Bazelor de Date|
|null|null|null|null|DMBD|Data Mining in Big Data|

Sabina S. CS

<!-- page 42 -->
#### Students

<!-- Start of picture text -->
Students Exams StdId CrsId Grade Credits SID Name Group 135 BD 10 6 135 Alexandra  922 82 SGBD 10 6 82 Paul 926 135 SGBD 10 6 294 Ștefania 925 737 SGBD 9 6 <!-- End of picture text -->

find all the exams; include students with no exams and grades given by mistake to nonexistent students; the result should also contain students' names

#### 4. full outer join : source1 [alias] FULL [OUTER] JOIN source2 [alias] ON condition `SELECT *`

```
FROM StudentsSFULL JOIN ExamsEON S.SID= E.StdId
```

|SID|Name|Group|StdId|CrsId|Grade|Credits|
|---|---|---|---|---|---|---|
|135|Alexandra|922|135|BD|10|6|
|135|Alexandra|922|135|SGBD|10|6|
|82|Paul|926|82|SGBD|10|6|
|294|Ștefania|925|null|null|null|null|
|null|null|null|737|SGBD|9|6|

Sabina S. CS

<!-- page 43 -->
- other JOIN expressions

source1 [alias1] JOIN source2 [alias2] USING (column_list) source1 [alias1] NATURAL JOIN source2 [alias2] source1 [alias1] CROSS JOIN source2 [alias2]

Sabina S. CS

<!-- page 44 -->
### • subquery in the FROM clause

```
SELECT R.*
```

```
FROM Researchers RINNER JOIN
```

```
(SELECT *
```

```
FROM AuthorContributionA
WHERE A.PID= 400) t
```

```
ON R.RID = t.RID
```

Sabina S. CS

<!-- page 45 -->
### • copy data from one table to another

```
INSERT INTO T2
SELECT * FROM T1
```

Sabina S. CS

<!-- page 46 -->
### • GROUP BY, HAVING

```
SELECT [DISTINCT] select-list
FROM from-list
```

```
WHERE qualification
GROUP BY grouping-list
HAVING group-qualification
```

- optional GROUP BY clause

   - list of (expressions involving) columns used for grouping

- optional HAVING clause

   - group qualification conditions

- aggregation operators

```
COUNT, AVG, SUM, MIN, MAX
```

Sabina S. CS

<!-- page 47 -->
### • GROUP BY, HAVING

```
SELECT [DISTINCT] select-list
FROM from-list
```

```
WHERE qualification
GROUP BY grouping-list
HAVING group-qualification
```

- group

• a collection of rows with identical values for the grouping-list

columns in

- every row in the result of the query corresponds to a group

Sabina S. CS

<!-- page 48 -->
### • GROUP BY, HAVING

```
SELECT [DISTINCT] select-list
FROM from-list
```

```
WHERE qualification
GROUP BY grouping-list
HAVING group-qualification
```

- select-list

   - columns (that must appear in grouping-list )

   - terms of the form _aggop(column) [AS NewName]_

      - e.g., MAX(R.ImpactFactor) AS MaxImpactFactor

      - _NewName_ assigns a name to the column in the result table

Sabina S. CS

<!-- page 49 -->
### • GROUP BY, HAVING

```
SELECT [DISTINCT] select-list
FROM from-list
```

```
WHERE qualification
GROUP BY grouping-list
HAVING group-qualification
```

- group-qualification

   - expressions with a single value / group

   - a column in group-qualification appears in grouping-list or as an argument to an aggregation operator

- records that meet qualification are partitioned into groups based on the values of the columns in grouping-list

- an answer row is generated for every group that meets group-qualification

Sabina S. CS

<!-- page 50 -->
Find the age of the youngest researcher for each impact factor. `SELECT R.ImpactFactor, MIN(R.Age) FROM Researchers R`

```
GROUP BY R.ImpactFactor
```

* discussion: using the GROUP BY clause vs writing _n_ queries, one for each of the _n_ values of the impact factor, where _n_ depends on the relation instance

Find the age of the youngest researcher who is at least 18 years old for each impact factor with at least 10 such researchers.

```
SELECT R.ImpactFactor, MIN(R.Age) AS MinAge
FROM Researchers R
WHERE R.Age>= 18
```

```
GROUP BY R.ImpactFactor
HAVING COUNT(*) >= 10
```

Sabina S. CS

<!-- page 51 -->
### See seminar 2:

- range variables

- the LIKE operator

- the UNION [ALL], INTERSECT, EXCEPT operators

- joins with more than 2 tables

- aggregation operators

Sabina S. CS

<!-- page 52 -->
## References

- [Ta13] ȚÂMBULEA, L., Curs Baze de date, Facultatea de Matematică și Informatică, UBB, 2013-2014

- [Ra00] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems (2nd Edition), McGraw-Hill, 2000

- [Da03] DATE, C.J., An Introduction to Database Systems (8th Edition), AddisonWesley, 2003

- [Ga08] GARCIA-MOLINA, H., ULLMAN, J., WIDOM, J., Database Systems: The Complete Book, Prentice Hall Press, 2008

- [Ha96] HANSEN, G., HANSEN, J., Database Management And Design (2nd Edition), Prentice Hall, 1996

- [Ra07] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems, McGrawHill, 2007, <u>http://pages.cs.wisc.edu/~dbbook/openAccess/thirdEdition/slides/slides3ed.html</u>

- [Si10] SILBERSCHATZ, A., KORTH, H., SUDARSHAN, S., Database System Concepts, McGraw-Hill, 2010, <u>http://codex.cs.yale.edu/avi/db-book/</u>

- [Ul11] ULLMAN, J., WIDOM, J., A First Course in Database Systems, <u>http://infolab.stanford.edu/~ullman/fcdb.html</u>

• [Ta03] ȚÂMBULEA, L., Baze de date, Litografiat Cluj-Napoca 2003

Sabina S. CS
