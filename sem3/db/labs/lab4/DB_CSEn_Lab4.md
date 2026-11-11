<!-- page 1 -->
# <mark>Lab 4. Database Testing</mark>

# <mark> assigned: week 8; due: week 11</mark>

<mark>After you finished designing your database, the development team is interested in assessing the performance of your design. To record different test configurations and results, you create the following</mark> relational structure:

_Tests_ – holds data about different test configurations;

_Tables_ – holds data about tables that might take part in a test;

_TestTables_ – link table between _Tests_ and _Tables_ (which tables take part in which tests);

_<mark>Views</mark>_ <mark>– holds data about a set of views from the database, used to assess the performance of certain</mark> SELECT queries;

_TestViews_ – link table between _Tests_ and _Views_ (which views take part in which tests);

_<mark>TestRuns</mark>_ <mark>– contains data about different test runs; each test run involves:</mark>

- _<mark>deleting</mark>_ <mark>data from tables - in the order specified by the</mark> _<mark>Position</mark>_ <mark>field (table</mark> _<mark>TestTables</mark>_ <mark>);</mark>

- _<mark>inserting</mark>_ <mark>data into tables - reverse deletion order; the number of records to insert is stored in the</mark> _<mark>NoOfRows</mark>_ <mark>field (table</mark> _<mark>TestTables</mark>_ <mark>);</mark>

- _<mark>evaluating</mark>_ <mark>views;</mark>

_TestRunTables_ – contains performance data for all the tables affected by INSERT operations;

_TestRunViews_ – contains performance data for every view in every test.

<mark>Your task is to implement a set of stored procedures for running tests and storing their results. Your tests must include at least 3 tables:</mark>

- <mark>a table with a single-column primary key and no foreign keys;</mark>

- <mark>a table with a single-column primary key and at least one foreign key;</mark>

- <mark>a table with a multicolumn primary key,</mark>

<mark>and 3 views:</mark>

- <mark>a view with a SELECT statement operating on one table;</mark>

- <mark>a view with a SELECT statement operating on at least 2 tables;</mark>

- <mark>a view with a SELECT statement that has a GROUP BY clause and operates on at least 2 tables.</mark>

<mark>Obs. The way you implement the stored procedures and / or functions is up to you. Results which allow the system to be extended to new tables / views with minimal or no code at all will be more</mark> appreciated.

The script for creating the above relational structure can be downloaded here: Script_lab4.
