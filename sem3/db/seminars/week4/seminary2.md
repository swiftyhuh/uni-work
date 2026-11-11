<!-- page 1 -->
# _<u>SEMINARY 2</u>_

```
-- Seminary 2
-- Students[sid, sname, email, age, sgroup]
-- Courses[cid, cname, credits]
-- Exams[sid, cid, grade]
createdatabase Seminary2
go
use Seminary2
go
-- create tables
-- create table Groups(gid int primary key, noofs int)
CREATETABLE Students(
sidintprimarykey,
sname varchar(50)notnull,
email varchar(50),
age intdefault 20,
sgroup intnotnull)-- gid int foreign key references Groups(gid))
createtable Courses(
cid varchar(10)primarykey,
cname varchar(50)notnull,
credits int)
createtable Exams(
sidintforeignkeyreferences Students(sid),
cid varchar(10)foreignkeyreferences Courses(cid),
grade int,
constraint pk_Examns primarykey(sid, cid))
```

```
-- insert values in the tables
Insertinto Students(sid, sname, email, age, sgroup)values (1234,'Ada','a@cs.ro', 20, 921),
(1235,'Razvan','r@cs.ro', 21, 921),(1236,'Monica','m@cs.ro', 20, 922),(1237,'Paula',
'p@cs.ro', 20, 924)
insertinto Courses(cid, cname, credits)values ('Alg1','Algorithms 1', 7),('DB1','Databases 1',
6),('DB2','Databases 2', 6),('MAP1','MAP 1', 5),('MAP2','MAP 2', 4)
insertinto Exams(sid, cid,grade)values (1234,'Alg1', 9),(1235,'Alg1', 10),(1237,'DB2', 9)
(4 row(s) affected)
(5 row(s) affected)
(3 row(s) affected)
```

1

<!-- page 2 -->
```
select*from Students
select*from Courses
select*from Exams
```

# _<u>QUERIES</u>_

|`-- I1. Find all the 21-year-old` `students from the Students table.` `SELECT *` `FROM Students S` `WHERE S.age= 21`|`-- I2. Find the names and email addresses of all the 21-year-` `old students from the Students table. Eliminate duplicates.` `SELECT DISTINCT S.sname, S.email` `FROM Students S` `WHERE S.age= 21`|
|---|---|
||`-- also the duplicates` `SELECT S.sname, S.email` `FROM Students S` `WHERE S.age= 21`|
||`-- without alias` `SELECT sname, email` `FROM Students` `WHERE age = 21`|

```
-- Range variable
```

```
-- alias used for a table in a SQL query;
```

```
-- needed when the same relation appears twice in the FROM clause (to solve the ambiguity);
-- it is good style to always use range variables; compare the following versions of the same
query:
```

2

<!-- page 3 -->
```
-- I3. Find the names of the students who got 10 grades and the
ids of the corresponding courses.
SELECT S.sname, E.cid
FROM Students S, Exams E
WHERE S.sid= E.sidAND E.grade = 10
SELECT sname, cid
FROM Students, Exams
WHERE Students.sid= Exams.sidAND grade = 10
-- all the students with the grade 10, even if they do not have
the grade 10
SELECT sname, cid
FROM Students, Exams
WHERE grade = 10
```

```
-- Arithmetic expressions and the LIKE operator
-- 'AS' and '=' can be used to name fields in the result set;
-- the LIKE operator is used for string pattern matching:
-- '_' matches any one character;
```

```
-- '%' matches 0 or more arbitrary characters.-- I4. For all the
students whose names start and end with B and have at least 3
characters, find triples of the form: student age, student age –
18, student age * 2.
SELECT S.age, age1 = S.age-18, 2*S.age AS age2
FROM Students S
WHERE S.sname LIKE'B_%B'
SELECT S.age, age1 = S.age-18, 2*S.age AS age2
FROM Students S
WHERE S.sname LIKE'A_%A'
```

```
-- after another insert
SELECT S.age, S.age-18, 2*S.age
FROM Students S
WHERE S.sname LIKE'A_%A'
SELECT S.name, S.age, S.age-18, 2*S.age
FROM Students S
WHERE S.sname LIKE'A_%A'
```

## `-- Set operations`

```
-- UNION, INTERSECT, EXCEPT: compute the union / intersection / difference of two union-
compatible sets of tuples that are themselves results of SQL queries. Duplicate rows are
eliminated.
```

```
-- I5. Find the ids of students who are older than 20 or
have a grade in the Alg1 course.
-- no duplicates
-- union - OR between conditions
SELECT S.sid
FROM Students S
```

3

<!-- page 4 -->
|`WHERE S.age> 20` `UNION`||
|---|---|
|`SELECT E.sid` `FROM Exams E` `WHERE E.cid= 'Alg1'` `'`||
|`--UNION ALL doesnt eliminate duplicates`||
|`-- ERROR, types different (from the first select to the` `second select)` `SELECT S.sid, S.age` `FROM Students S` `WHERE S.age> 20` `UNION` `SELECT E.sid, E.cid` |`Msg 245, Level 16, State 1, Line 99` `Conversion failed when converting the` `varchar value 'Alg1' to data type int.` `-- so, the number of columns must be the` `same as number and also as type`|
|`FROM Exams E`||
|`WHERE E.cid= 'Alg1'`||
|`--UNION ALL doesn't eliminate duplicates` `-- here we have duplicates`||
| `SELECT S.sid` `FROM Students S` `WHERE S.age> 20`||
|`UNION ALL` `SELECT E.sid` `FROM Exams E`||
|`WHERE E.cid= 'Alg1'`||
|`-- intersect - AND between conditions -- I51. Find the ids` `of students who are older than 20 or have a grade in the` `Alg1 course.` `SELECT S.sid` `FROM Students S` `WHERE S.age> 20` `INTERSECT` `SELECT E.sid` `FROM Exams E`   `''`||
|`WHERE E.cid= Alg1`||
|`-- except - it is in the first, but not in the second --` `I5. Find the ids of students who are older than 20 and do` `NOT have a grade in the Alg1 course.` `SELECT S.sid` `FROM Students S` `WHERE S.age> 20` `EXCEPT` `SELECT E.sid` `FROM Exams E` `WHERE E.cid= 'Alg1'`||
|`-- I6. Find the ids of students who received a grade in` `both a 4 credits course and a 5 credits one.`||
|`SELECT E.sid` `FROM Exams E, Courses C` `WHERE E.cid= C.cidAND C.credits= 4`||
|`INTERSECT` ||
|`SELECT E2.sid`||
|`FROM Exams E2, Courses C2`||
|`WHERE E2.cid= C2.cidAND C2.credits= 5`||
|`-- I7. Find the ids of students who received a grade in a` `4 credits course, but have no grades in 5 credits courses.` `SELECT E.sid`||

4

<!-- page 5 -->
```
FROM Exams E, Courses C
WHERE E.cid = C.cid AND C.credits = 4
EXCEPT
SELECT E2.sid
FROM Exams E2, Courses C2
WHERE E2.cid = C2.cid AND C2.credits = 5
```

- `-- Nested queries`

- `-- a query can contain another query (a subquery), e.g., in the WHERE, FROM, HAVING clauses; -- the semantics of a nested query: the subquery is evaluated when the condition in the WHERE clause is tested.`

```
-- I8. Find the names of students who are not graded in -- OR
Alg1.SELECT S.sname
SELECT S.sname FROM Students S
FROM Students S WHERENOTEXISTS
WHERE S.sidNOTIN(SELECT E.sid(SELECT*
FROM Exams E FROM Exams E
WHERE E.cid ='Alg1')WHERE E.sid= S.sidAND E.cid ='Alg1')
```

- `-- The IN operator - tests whether a value belongs to a set of elements; the latter can be explicitly specified or generated by a query.`

- `-- The EXISTS operator - tests whether a set is nonempty.`

- `-- The ANY operator - the value is true if the condition is true for at least one item in the subquery result.`

- `-- The ALL operator - the value is true if the condition is true for all the items in the subquery result.`

```
-- I9. Find the students whose age is greater than
the age of some student called Ion.
SELECT*
FROM Students S
WHERE S.age >ANY(SELECT S2.age
FROM Students S2
WHERE S2.sname ='Ion')
-- I10. Find the students whose age is greater
than the age of all the students called Ion.
SELECT*
FROM Students S
WHERE S.age >ALL(SELECT S2.age
FROM Students S2
WHERE S2.sname ='Ion')
```

`-- JOIN operations -- INNER JOIN SELECT S.sname, C.cname FROM Students S INNER JOIN Exams E ON S.sid =E.sid INNER JOIN Courses C ON E.cid= C.cid -- not null, all the correspondences` -- similar `SELECT S.sname, C.cname`

5

<!-- page 6 -->
```
FROM Students S, Exams E, Courses C
WHERE S.sid=E.sid AND E.cid= C.cid
-- LEFT OUTER JOIN (e.g., the students with no grades
should also appear in the result set)
SELECT S.sname, C.cname
FROM Students S
LEFTOUTERJOIN Exams E ON S.sid= E.sid
LEFTOUTERJOIN Courses C ON E.cid = C.cid
-- null in the right side, all values in the left side
```

```
-- RIGHT OUTER JOIN (e.g., also find the grades given by
mistake to nonexisting students)
SELECT S.sname, C.cname
FROM Students S
RIGHTOUTERJOIN Exams E ON S.sid= E.sid
INNERJOIN Courses C ON E.cid = C.cid
```

```
-- no null, all the correspondences
-- RIGHT OUTER JOIN (e.g., also find the grades given by
mistake to nonexisting students)
SELECT S.sname, C.cname
```

```
FROM Students S
```

```
RIGHTOUTERJOIN Exams E ON S.sid= E.sid
RIGHTOUTERJOIN Courses C ON E.cid = C.cid
```

```
-- null in the left side, all the values in the right side
```

```
-- FULL OUTER JOIN (LEFT + RIGHT OUTER JOIN)
SELECT S.sname, C.cname
```

```
FROM Students S
```

```
FULLOUTERJOIN Exams E ON S.sid= E.sid
```

```
FULLOUTERJOIN Courses C ON E.cid = C.cid
```

```
-- null in the left + right part, all values from both left
and right sides
```

```
-- Obs. The followingqueries return the same result set:
```

```
SELECT*
FROM Students S INNERJOIN Exams E ON S.sid=
E.sid
```

```
SELECT*
FROM Students S, Exams E
WHERE S.sid= E.sid
```

- `-- Aggregation operators`

- `-- COUNT (*)`

- `-- COUNT ([DISTINCT] A)`

- `-- SUM ([DISTINCT] A)`

- `-- AVG ([DISTINCT] A)`

6

<!-- page 7 -->
```
-- MAX (A)
-- MIN (A)
-- , where A is an attribute name in a table.
```

```
-- evaluated over a set of values, corresponding to a group of records;
```

```
-- NULL values: seminar discussion – SELECT COUNT(*), SELECT COUNT(A), SELECT COUNT(DISTINCT A);
-- expressions.
```

`-- I11. Compute the total number of students. SELECT COUNT(*) FROM Students S -- with column name SELECT COUNT(*) AS noS FROM Students S -- I12. Find the average and minimum age for group 924. SELECT AVG(S.age), MIN(S.age) FROM Students S WHERE S.sgroup = 924 -- I13. Find the number of groups that have at least one student called Mihai. SELECT COUNT(DISTINCT S.sgroup) FROM Students S WHERE S.sname = 'Mihai' SELECT COUNT(S.sgroup) FROM Students S WHERE S.sname = 'Mihai' -- I14. Find the name and age of the oldest students. SELECT S.sname, S.age FROM Students S WHERE S.age = ANY (SELECT MAX(S2.age) FROM Students S2)` -- error SELECT S.sname, max(S.age) FROM Students S -- ok, if we add the GROUP BY clause Group by S.sname -- error SELECT S.sname, S.age FROM Students S where age=max(age)

```
-- GROUP BY - works for aggregation operators
SELECT C.cid
FROM Exams E, Courses C
WHERE E.cid = C.cid AND C.credits = 6
-- I15. For every 6 credits course, find the
number of grades and their average.
SELECT C.cid,COUNT(*)AS no_gr,AVG(grade)AS
gr_avg
```

7

<!-- page 8 -->
|`FROM Exams E, Courses C`|
|---|
|`WHERE E.cid= C.cidAND C.credits= 6` `GROUP BY C.cid`|
|`-- error, without GROUP BY clause` `SELECT C.cid, COUNT(*) AS no_gr, AVG(grade) AS` `gr_avg` `FROM Exams E, Courses C` `WHERE E.cid= C.cidAND C.credits= 6`|
|`-- error, conditions for the aggregate` `functions should be put it in the HAVING clause` `SELECT C.cid, COUNT(*) AS no_gr, AVG(grade) AS`|
|`gr_avg` `FROM Exams E, Courses C` `WHERE E.cid= C.cidAND C.credits= 6 AND` `AVG(grade)>9` `GROUP BY C.cid`|
|`-- ok`|
|`SELECT C.cid, COUNT(*) AS no_gr, AVG(grade) AS` `gr_avg` `FROM Exams E, Courses C` `WHERE E.cid= C.cidAND C.credits= 6` `GROUP BY C.cid` `HAVINGAVG(grade)>9`|
|`-- error, not the same number of fields in`|
|`select and group by`|
|`SELECT C.cid, C.cname,COUNT(*) AS no_gr,` `AVG(grade) AS gr_avg` `FROMExams E, Courses C` `WHERE E.cid = C.cid AND C.credits = 6` `GROUP BY C.cid`|
|`-- ok`|
|`SELECT C.cid, C.cname,COUNT(*) AS no_gr,` `AVG(grade) AS gr_avg` `FROMExams E, Courses C` `WHERE E.cid = C.cid AND C.credits = 6` `GROUP BY C.cid, C.cname`|

8
