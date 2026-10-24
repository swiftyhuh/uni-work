<!-- page 1 -->
# Databases

Lecture 2

The Relational Model

<!-- page 2 -->
## The Relational Data Model

- proposed by Edgar Codd in 1970

   - 1981 – Turing Award

- the dominant data model today (represented by DBMSs like Oracle, SQL Server, etc)

- advantages

   - simple data representation

   - queries, even complex ones, can be easily expressed, using a simple, high-level language

- even non-technical users can understand the contents of a database

<!-- page 3 -->
## The Relational Data Model

1. relations

2. integrity constraints

3. relational databases

4. managing relational databases

<!-- page 4 -->
## 1. Relations

- in an application, a data collection is used according to a model

- in the relational model , the data collection is organized as a set of relations (tables)

- a relation has a relation schema and a relation instance

- the relation instance can be thought of as a table

- the relation schema describes the table's column heads

<!-- page 5 -->
## 1. Relations

- the schema specifies the relation's name, and the name and domain for each field

- the domain of a field is specified through its name and has a set of associated values

• schema example for the Students relation: Students[ _name_ , _year_of_study_ , _email_ ] or notation:

Students( _name_ : string, _year_of_study_ : integer, _email_ : string)

<!-- page 6 -->
## 1. Relations

### • instance example for the Students relation:

##### attributes (columns, fields)

|name|year_of_study|email|
|---|---|---|
|PITIC BIANCA|2|pb @cs.ubb.ro|
|GROZA IONUȚ|2|gi @cs.ubb.ro|
|TUDORESCU ALEXANDRA|2|ta @cs.ubb.ro|

##### rows (records, tuples)

<!-- page 7 -->
## 1. Relations

- {A1, A2, ..., An} - a set of attributes

- Di = Dom(Ai) U {?} - the domain of possible values for attribute Ai • the undefined ( null ) value is denoted here by {?}; it is used to check if a value has been assigned to an attribute (the attribute could have the _undefined_ value); this value doesn't have a certain data type; attribute values of different types can be compared against this value (numeric, string, etc)

- relation of arity (degree) n: _R_ ⊆ _D1_ × _D2_ × ... × _Dn_

- R[A1, A2, ... , An] - the relation schema

<!-- page 8 -->
## 1. Relations

### • the relation can be stored in a table of the form:

|R|A1|...|Aj|...|An|
|---|---|---|---|---|---|
|r1|a11|...|a1j|...|a1n|
|...|...|...|...|...|...|
|ri|ai1|...|aij|...|ain|
|...|...|...|...|...|...|
|rm|am1|...|amj|...|amn|

where _aij_ ∈ _Dj_ , _j =_ 1,..., _n_ , _i =_ 1,..., _m_ .

<!-- page 9 -->
## 1. Relations

- the values of an attribute are atomic and scalar

- the rows in a table are not ordered

   - e.g., 2 representations of the same _Students_ relation instance

|name|year_of_study|email|
|---|---|---|
|PITIC BIANCA|2|pb @cs.ubb.ro|
|GROZA IONUȚ|2|gi @cs.ubb.ro|
|TUDORESCU ALEXANDRA|2|ta @cs.ubb.ro|
|name|year_of_study|email|
|GROZA IONUȚ|2|gi @cs.ubb.ro|
|PITIC BIANCA|2|pb @cs.ubb.ro|
|TUDORESCU ALEXANDRA|2|ta @cs.ubb.ro|

- the records in a table are distinct - a relation is defined as a set of distinct tuples (however, DBMSs allow tables to contain duplicates)

<!-- page 10 -->
1. Relations

• the cardinality of an instance is the number of tuples it contains

<!-- page 11 -->
## 1. Relations

### • a relation that is not well-designed:

### Students[name, program, year_of_study, group]

|name|program|year_of_study|group|
|---|---|---|---|
|Alexandra Mihai|CS ro|2|222|
|Vlad Dan|CS ro|2|222|
|Andreea Stancu|CS ro|2|226|
|Flaviu Pop|CS ro|3|226|

   - the association between group=222 and (program='CS ro', year_of_study=2) is stored 2 times, for the first 2 students

   - the last 2 students are in the same group, but in different years - error

- to avoid such situations, relations must be normalized

<!-- page 12 -->
2. Integrity Constraints

- integrity constraints (restrictions) are conditions specified on the database schema , restricting the data that can be stored in the database

- these constraints are checked when the data is changed ; operations that violate the constraints are not allowed (e.g., introducing a student with a CNP identical to a different student's CNP, entering data of the wrong type in a column, etc)

- examples: domain constraints, key constraints, foreign key constraints

- domain constraints - conditions that must be satisfied by every relation instance: a column's values belong to its associated domain

<!-- page 13 -->
## 2. Integrity Constraints

- key constraint - a constraint stating that a subset of the attributes in a relation is a unique identifier for every tuple in the relation; this subset of attributes is minimal

- K ⊆ {A1, A2,..., An} is a key for relation R[A1, A2, ... , An] if:

   - the attributes in K can be used to identify every record in R

   - no subset of K has this property

- two different records are not allowed to have identical values in all the fields that constitute a key, hence specifying a key is a restriction for the database

<!-- page 14 -->
## 2. Integrity Constraints

- e.g., in the Doctors[dep, did, lastname, firstname] relation, we can define the constraint: a doctor is uniquely identified by his / her department and did, i.e., 2 different doctors can have the same department or the same did, but not both; the key is the group of attributes {dep, did}

• e.g., Books[author, title, publisher, year]

|author|title|publisher|year|
|---|---|---|---|
|C. J. Date|An Introduction to|Addison-Wesley|2004|
||Database Systems|Publishing Comp.||
|P. G. Wodehouse|Summer Lightning|Polirom|2003|
|Simon Singh|Fermat's Last Theorem|Humanitas|2012|
|Stephen Hawking|A Brief History of Time|Humanitas|2012|

- a possible key is the group of attributes {author, title, publisher, year} ; in such a case, the schema can be augmented to include another attribute (with distinct values; the latter can be automatically generated when records are ->

- added)

<!-- page 15 -->
## 2. Integrity Constraints

|bid|author|title|publisher|year|
|---|---|---|---|---|
|457|C. J. Date|An Introduction to|Addison-Wesley|2004|
|||Database Systems|Publishing Comp.||
|4|P. G. Wodehouse|Summer Lightning|Polirom|2003|
|34|Simon Singh|Fermat's Last Theorem|Humanitas|2012|
|769|Stephen Hawking|A Brief History of Time|Humanitas|2012|

- {bid} can now be chosen as the key; two different tuples will always have different values in the bid column

- the user must be careful not to define a key constraint that prevents the storage of correct tuple sets, e.g., if {title} is declared to be a key, the _Books_ relation can't contain tuples describing different books with the same title

- superkey - a set of fields that contains the key (e.g., the set {bid, title} is a superkey)

<!-- page 16 -->
## 2. Integrity Constraints

|bid|author|title|publisher|year|
|---|---|---|---|---|
|457|C. J. Date|An Introduction to|Addison-Wesley|2004|
|||Database Systems|Publishing Comp.||
|4|P. G. Wodehouse|Summer Lightning|Polirom|2003|
|34|Simon Singh|Fermat's Last Theorem|Humanitas|2012|
|769|Stephen Hawking|A Brief History of Time|Humanitas|2012|

- non-key fields can contain identical values in different tuples: the relation can contain 2 different books from the same year, i.e., 2 tuples with _year = 2004_ ; or 3 different books written by the same author, i.e., 3 tuples with _author = Stephen Hawking_ , etc

<!-- page 17 -->
## 2. Integrity Constraints

- a relation can have multiple keys: one key (an attribute or a group of attributes) is chosen as the primary key , while the others are considered candidate keys

- e.g., Schedule[day, hour, room, teacher, group, subject] with the schedule for a week

- the following sets of attributes can be chosen as keys: {day, hour, room}; {day, hour, teacher}; {day, hour, group}

<!-- page 18 -->
## 2. Integrity Constraints

- foreign key constraints - the values of some attributes in a relation can also appear in another relation

- in the figure below, A is defined as a foreign key in R2; it refers to R1's key

- R1 and R2 need not be distinct

#### A = foreign key

<!-- Start of picture text -->
R2 R1 key v v <!-- End of picture text -->

<!-- page 19 -->
## 2. Integrity Constraints

### • e.g., Departments[did, name, budget]

Doctors[cnp, name, department]

<!-- Start of picture text -->
Departments Doctors 1 did cnp name name budget ∞ department <!-- End of picture text -->

- establishing a link betwen _Departments_ (as the parent relation) and _Doctors_ (child relation): Departments.did = Doctors.department

- a department stored in the _Departments_ relation and identified through a code corresponds to all doctors with the department's code; the _department_ attribute in the _Doctors_ relation is a foreign key

- a foreign key can be used to store 1:n associations among entities: a department can correspond to several doctors, and a doctor can be associated with at most one department

<!-- page 20 -->
## 2. Integrity Constraints

- foreign keys can be used to store m:n associations among entities

- e.g., a student can enroll in several courses; multiple students can take a course; storing such associations requires an additional table

- any value that appears in the _student_ field of the _Contracts_ relation must appear in the _cnp_ field of the _Students_ relation, but there may be students who haven't enrolled in any courses yet (i.e., _cnp_ values in _Students_ that don't appear in the _student_ column from _Contracts_ )

<!-- page 21 -->
## 2. Integrity Constraints

- the foreign key in the _Contracts_ relation must have the same number of columns as the referenced key from _Students_ (preferably, the primary key); the data types of the corresponding columns must be compatible, however, the column names can be different

<!-- page 22 -->
## 2. Integrity Constraints

### enforcing integrity constraints

- when the data is changed, the DBMS rejects operations that violate the specified integrity constraints

   - e.g., entering a row in _Contracts_ that has no corresponding student row in _Students_

- in some cases, instead of rejecting the operation, the DBMS will make additional changes to the data, so in the end all integrity constraints are satisfied

   - e.g., when removing a _Students_ row that has referencing _Contracts_ rows, the operation can be:

      - rejected – the row is not deleted

      - cascaded, i.e., the _Students_ row and the referencing rows in _Contracts_ are deleted

* other options - see the CREATE TABLE statement in this lecture

<!-- page 23 -->
## 3. Relational Databases

- relational database

   - collection of relations with distinct names

- relational database schema

   - collection of schemas for the relations in the database

- database instance

   - collection of relation instances, one / relational schema in the database schema

   - must be legal , i.e., it must satisfy all the specified integrity constraints

<!-- page 24 -->
## 3. Relational Databases

• ex1:

<!-- page 25 -->
## 3. Relational Databases

• ex2:

<!-- page 26 -->
4. Managing Relational Databases with SQL

- SQL – Structured Query Language

- 1970 - E.F. Codd formalizes the relational model

- 1974 - the SEQUEL language (Structured English Query Language) is defined at IBM (in San Jose)

- 1976 - SEQUEL/2, a changed version of SEQUEL, is defined at IBM; following a revision, it becomes the SQL language

- 1986 - SQL adopted by ANSI (American National Standards Institute)

- 1987 - SQL adopted by ISO (International Standards Organization)

- versions (extensions): SQL-86, SQL-89, SQL-92, SQL:1999, SQL:2006, SQL:2008, SQL:2011, SQL:2016

SQL:2003,

<!-- page 27 -->
## 4. Managing Relational Databases with SQL

- defining components

   - CREATE , ALTER , DROP (SQL DDL)

- managing and retrieving data

   - SELECT, INSERT , UPDATE , DELETE (SQL DML)

- managing transactions

   - START TRANSACTION , COMMIT , ROLLBACK

<!-- page 28 -->
## 4. Managing Relational Databases with SQL

- CREATE TABLE – defines a new table

CREATE TABLE table_name (column_definition [, column_definition] ... [, table_restrictions]) column_definition: column_name data_type[(length)] [ DEFAULT value ] [column_restriction ] `CREATE TABLE Students (sid INT PRIMARY KEY, cnp CHAR(13), lastname VARCHAR(50), firstname VARCHAR(50) DEFAULT 'TBA', age INT CHECK (age >= 18))`

- data type categories: numeric, string, date-time, etc

* we use the _age_ attribute for simplicity; it is preferable to store the date of birth, as it doesn't change every year

<!-- page 29 -->
## 4. Managing Relational Databases with SQL

- restrictions associated with a column :

   - NOT NULL - can't have undefined values

   - PRIMARY KEY - the column is a primary key

   - UNIQUE - the values in the column are unique

   - CHECK(condition) - the condition that must be satisfied by the column's values (simple conditions that evaluate to _true_ or _false_ )

   - FOREIGN KEY REFERENCES parent_table[(column_name)] [ON UPDATE action] [ON DELETE action]

<!-- page 30 -->
## 4. Managing Relational Databases with SQL

- restrictions associated with a table :

   - PRIMARY KEY(column_list) - defining the primary key for the table

   - UNIQUE(column_list) - the values in the column list are unique

   - CHECK(condition) - the condition that must be satisfied by a row • FOREIGN KEY(column_list) REFERENCES parent_table[(column_list)][ON UPDATE action][ON DELETE action]

<!-- page 31 -->
## 4. Managing Relational Databases with SQL

- possible actions for a foreign key:

   - NO ACTION

      - the operation is not allowed if it violates integrity constraints

   - SET NULL

      - the foreign key value is set to _null_

   - SET DEFAULT

      - the foreign key value is set to the default value

   - CASCADE

      - the delete / update is performed on the parent table, but it generates corresponding deletes / updates in the child table

<!-- page 32 -->
###### `CREATE TABLE Programs`

```
(id SMALLINTPRIMARYKEY,
nameVARCHAR(70))
```

###### `CREATE TABLE Students`

```
(program SMALLINTREFERENCESPrograms(id),
reg_numberCHAR(10),
last_nameCHAR(30),
first_nameCHAR(30),
cnpCHAR(13)UNIQUE,
```

```
PRIMARYKEY(program,reg_number))
```

```
CREATETABLEGroups
```

```
(acad_yearSMALLINT,
program SMALLINTREFERENCESPrograms(id),
year_of_studySMALLINT,
```

```
id CHAR(10),
```

```
PRIMARYKEY (acad_year,program,id))
```

###### `CREATE TABLE Courses`

###### `CREATE TABLE Trajectory`

```
(id INTPRIMARYKEYIDENTITY(1,1),
acad_yearSMALLINT,
```

```
program SMALLINT,
reg_numberCHAR(10),
sgroupCHAR(10),
```

```
FOREIGNKEY(program,reg_number)REFERENCES
Students(program,reg_number),
```

```
FOREIGNKEY(acad_year,program,sgroup)
REFERENCESGroups(acad_year,program,id))
```

```
CREATETABLEResults
```

```
(id INTPRIMARYKEYIDENTITY(1,1),
program SMALLINT,
reg_numberCHAR(10),
acad_yearSMALLINT,
```

```
semester SMALLINT,
```

```
course CHAR(10)REFERENCESCourses(id),
no_creditsDECIMAL(3,1),
grade SMALLINT,
```

```
FOREIGNKEY(program,reg_number)REFERENCES
Students(program,reg_number))
```

```
(id CHAR(10)PRIMARYKEY,
nameVARCHAR(70))
```

<!-- page 33 -->
###### `CREATE TABLE Universities`

```
(UnivIDSMALLINTPRIMARYKEYIDENTITY(1,1),
UnivNameNVARCHAR(100)NOTNULL,
```

```
Country NVARCHAR(40))
```

###### `CREATE TABLE Sensors`

```
(SensorIDINTPRIMARYKEYIDENTITY(1,1),
STID TINYINTREFERENCESSensorTypesONDELETENOACTION
ONUPDATECASCADE,
```

```
BirdIDINTREFERENCESBirds(BID))
```

###### `CREATE TABLE ResearchTeams`

- `(RTID SMALLINT IDENTITY(1,1), RTName NVARCHAR(100) UNIQUE,`

```
CONSTRAINTPK_ResearchTeamsPRIMARYKEY(RTID))
```

###### `CREATE TABLE ResearchTeams_Universities`

- `(RTID SMALLINT FOREIGN KEY REFERENCES`

- `ResearchTeams(RTID) ,`

   - `UnivID SMALLINT REFERENCES Universities(UnivID), PRIMARY KEY(RTID, UnivID))`

###### `CREATE TABLE SensorTypes`

- `(STID TINYINT PRIMARY KEY IDENTITY(1,1), STName NVARCHAR(50) UNIQUE,`

```
STBriefDescriptionNVARCHAR(300)DEFAULT'TBW')
```

###### `CREATE TABLE Birds`

- `(BID INT PRIMARY KEY IDENTITY(1,1), BNickName NVARCHAR(50),`

```
Species VARCHAR(100),
```

```
RTID SMALLINT,
```

```
CONSTRAINTFK_Birds_ResearchTeamsFOREIGNKEY(RTID)
REFERENCESResearchTeams(RTID))
```

###### `CREATE TABLE SensorData`

```
(SDID INTPRIMARYKEYIDENTITY(1,1),
SensorIDINTREFERENCESSensors(SensorID),
SensorDataValueREAL,
```

```
SensorDataTimeDATETIME2)
```

###### `CREATE TABLE Researchers`

- `(RID SMALLINT PRIMARY KEY IDENTITY(1,1), RFName NVARCHAR(90) NOT NULL, RLName NVARCHAR(90) NOT NULL,`

```
RTID SMALLINTREFERENCESResearchTeams(RTID))
```

###### `CREATE TABLE PublishedPapers`

```
(PID INTPRIMARYKEYIDENTITY(1,1),
Title NVARCHAR(200),
Conference NVARCHAR(200))
```

###### `CREATE TABLE Researchers_PublishedPapers`

```
(RID SMALLINTREFERENCESResearchers(RID),
PID INTREFERENCESPublishedPapers(PID),
PRIMARYKEY(RID,PID))
```

<!-- page 34 -->
## References

- [Ta13] ȚÂMBULEA, L., Curs Baze de date, Facultatea de Matematică și Informatică, UBB, 2013-2014

- [Ra00] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems (2nd Edition), McGraw-Hill, 2000

- [Da03] DATE, C.J., An Introduction to Database Systems (8th Edition), AddisonWesley, 2003

- [Ga08] GARCIA-MOLINA, H., ULLMAN, J., WIDOM, J., Database Systems: The Complete Book, Prentice Hall Press, 2008

- [Ha96] HANSEN, G., HANSEN, J., Database Management And Design (2nd Edition), Prentice Hall, 1996

- [Ra07] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems, McGrawHill, 2007, <u>http://pages.cs.wisc.edu/~dbbook/openAccess/thirdEdition/slides/slides3ed.html</u>

- [Si10] SILBERSCHATZ, A., KORTH, H., SUDARSHAN, S., Database System Concepts, McGraw-Hill, 2010, <u>http://codex.cs.yale.edu/avi/db-book/</u>

- [Ul11] ULLMAN, J., WIDOM, J., A First Course in Database Systems, <u>http://infolab.stanford.edu/~ullman/fcdb.html</u>
