<!-- page 1 -->
Databases Seminar 1

Mapping Entity-Relationship Diagrams to Relational Schemas SQL – Data Definition Language

<u>Concepts in the entity-relationship (ER) model. The ER diagram</u>

<!-- Start of picture text -->
     entity set      relationship set       attribute Example: o cnp  – primary key for the  Employee  entity set <!-- End of picture text -->

<u>The degree of a relationship set – the number of entity sets that participate in the relationship set</u> Examples:

- Unary relationship set (degree = 1)

<!-- Start of picture text -->
• Binary relationship set (degree = 2) <!-- End of picture text -->

`o` _remuneration_ – descriptive attribute for the _Performs_in_ relationship set

1

<!-- page 2 -->
Databases Seminar 1

Mapping Entity-Relationship Diagrams to Relational Schemas SQL – Data Definition Language

- Ternary relationship set (degree = 3)

<!-- Start of picture text -->
Mapping cardinalities - binary relationship sets 1:1 1:n m:n 2 <!-- End of picture text -->

<!-- page 3 -->
Databases Seminar 1

Mapping Entity-Relationship Diagrams to Relational Schemas SQL – Data Definition Language

# <u>Translation to the Relational Model</u>

Entity set -> relation

- the name of the entity set becomes the name of the relation;

- the attributes of the entity set become attributes in the relation;

- the primary key of the entity set becomes the primary key of the relation.

# m:n relationship set -> relation

- the name of the relationship set becomes the name of the relation;

- the primary key attributes for each entity set that takes part in the relationship set:

   - become attributes in the relation;

   - are foreign keys in the relation;

   - can become the primary key of the relation;

- the relationship set descriptive attributes become attributes in the relation.

n:1 (or 1:n) relationship set

- one can avoid creating an additional relation.

3

<!-- page 4 -->
Databases Seminar 1

## Mapping Entity-Relationship Diagrams to Relational Schemas SQL – Data Definition Language

- the _Employee_ entity set is on the _n_ ( _many_ ) side of the _Works_in_ relationship set, while the _Department_ entity set is on the _1_ side;

- the relationship set data is included in the _Employee_ relation, corresponding to the entity set that lies on the _n_ side of the relationship set; this relation will store every employee's department along with the date when he/she started working there;

- the key in the _Department_ relation (corresponding to the entity set that lies on the _1_ side of the relationship set) becomes a foreign key in the _Employee_ relation.

Note: conceptual modeling is detailed in a next lecture. The current seminar aims to provide support for the first lab.

# SQL – Data Definition Language

Statement that creates the _Movie_ table (relation):

```
CREATE TABLE Movie
  (mid CHAR(10),
  title VARCHAR(70),
  year_of_release TINYINT,
  running_time INT,
```

```
  box_office DECIMAL(12, 2))
```

- the type (domain) of each field (attribute) is enforced by the DBMS whenever tuples are added or modified.

Statement that creates the _MovieCast_ table:

```
CREATE TABLE MovieCast
  (mid CHAR(10),
  aid CHAR(10),
  remuneration DECIMAL(12, 2))
```

- stored data - which actors perform in which movies, and their corresponding remuneration `.`

# Statement that drops the _Movie_ table:

```
DROP TABLE Movie
```

- both the schema information and the tuples in the table are removed.

Statement that alters the schema of the _Movie_ table by adding a new field:

```
ALTER TABLE Movie
```

```
ADD synopsis VARCHAR(500)
```

- every tuple in the current instance is extended with the _null_ value in the new field;

- this statement assumes a table named _Movie_ exists.

4

<!-- page 5 -->
Databases Seminar 1

Mapping Entity-Relationship Diagrams to Relational Schemas SQL – Data Definition Language

Statement that alters the schema of the _Movie_ table by removing a field: `ALTER TABLE Movie DROP COLUMN running_time`

Statement that alters the schema of the _Movie_ table by changing the type of a field and adding a NOT NULL constraint:

```
ALTER TABLE Movie
ALTER COLUMN year_of_release SMALLINT NOT NULL
```

* careful when altering columns with associated constraints

The _MovieCast_ table creation statement with the primary key declaration:

```
CREATE TABLE MovieCast
  (mid CHAR(10),
  aid CHAR(10),
  remuneration DECIMAL(12, 2),
  PRIMARY KEY(mid, aid))
```

- multiple candidate keys can be declared using UNIQUE;

- a table can have at most one primary key;

- primary key _{mid, aid}_ : no two tuples in the relation have identical values in both the _mid_ and the _aid_ fields.

The _MovieCast_ table creation statement with unrealistic constraints:

```
CREATE TABLE MovieCast
  (mid CHAR(10),
  aid CHAR(10),
  remuneration DECIMAL(12, 2),
  PRIMARY KEY(aid),
  UNIQUE(mid, remuneration))
```

Statement that adds a primary key to the _Movie_ table:

```
ALTER TABLE Movie
ADD CONSTRAINT PK_Movie PRIMARY KEY(mid)
```

- _mid_ must be NOT NULL.

The _MovieCast_ table creation statement with a foreign key declaration:

```
CREATE TABLE MovieCast
  (mid CHAR(10),
  aid CHAR(10),
  remuneration DECIMAL(12, 2),
  PRIMARY KEY(mid, aid),
```

```
  FOREIGN KEY(mid) REFERENCES Movie(mid))
```

- the _mid_ column in _MovieCast_ can take on only values that appear in the _mid_ column in the _Movie_ table.

The _MovieCast_ table creation statement with foreign key actions: `CREATE TABLE MovieCast (mid CHAR(10), aid CHAR(10), remuneration DECIMAL(12, 2), PRIMARY KEY(mid, aid), FOREIGN KEY(mid) REFERENCES Movie(mid) ON DELETE CASCADE`

5

<!-- page 6 -->
Databases Seminar 1

Mapping Entity-Relationship Diagrams to Relational Schemas SQL – Data Definition Language

```
    ON UPDATE NO ACTION
```

```
)
```

- in the case of update / delete operations, in order to enforce referential integrity constraints, the system can execute 4 actions:

   - NO ACTION – the update / delete is not allowed if it violates the specified integrity constraint (default option);

   - CASCADE – the update / delete is allowed on the parent table, but it also generates updates / deletes on the child table;

   - SET NULL – the foreign key column value is replaced by _null_ (only if it's nullable);

   - SET DEFAULT – the foreign key column value is replaced by its default value (specified with DEFAULT); if a column is nullable and doesn't have a DEFAULT definition, _null_ will be considered as the default value for the column.

- what happens if we replace the ON UPDATE action with SET NULL in the above statement?

Statement that adds a foreign key to the _MovieCast_ table (table _Actor_ is assumed to exist with _{aid}_ as

# primary key):

```
ALTER TABLE MovieCast
```

```
ADD CONSTRAINT FK_MovieCast_Actor FOREIGN KEY(aid) REFERENCES Actor(aid)
```

Statement that removes a foreign key from the _MovieCast_ table:

```
ALTER TABLE MovieCast
DROP FK_MovieCast_Actor
```

# Statement that adds a DEFAULT definition to the _MovieCast_ table:

```
ALTER TABLE MovieCast
ADD DEFAULT 0 FOR remuneration
```

The _Movie_ table creation statement with a CHECK constraint:

```
CREATE TABLE Movie
  (mid CHAR(10),
  title VARCHAR(70),
  year_of_release SMALLINT,
  running_time INT,
  box_office DECIMAL(12, 2),
  CONSTRAINT PK_Movie PRIMARY KEY(mid),
  CONSTRAINT year_range
    CHECK(year_of_release >= 1905 AND year_of_release <= 2022))
```

6
