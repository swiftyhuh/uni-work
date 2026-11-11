<!-- page 1 -->
<mark>Lab 3. Altering the Database</mark>

<mark> assigned: week 6; due: week 8</mark>

<mark>Sometimes, after you design a database, you need to change its structure. Unfortunately, changes aren't correct every time, so they must be reverted. Your task is to create a versioning mechanism that allows</mark> you to easily switch between database versions.

Write SQL scripts that:

a. modify the type of a column;

b. add / remove a column;

c. add / remove a DEFAULT constraint;

d. add / remove a primary key;

e. add / remove a candidate key;

f. add / remove a foreign key;

g. create / drop a table.

<mark>For each of the scripts above, write another one that reverts the operation. Create a new table that holds the current version of the database schema. For simplicity, the version is assumed to be an integer</mark> number.

<mark>Place each of the scripts in a stored procedure. Use a simple, intuitive</mark> naming convention.

<mark>Write another stored procedure that receives as a parameter a version</mark> number and brings the database to that version.

<!-- page 2 -->
<mark>Useful references:</mark>

- seminars 1, 3

- <mark>T-SQL</mark>

<mark>`o` DECLARE, SET, BEGIN, END</mark>

<u>http://msdn.microsoft.com/en-us/library/ms188927.aspx http://msdn.microsoft.com/en-us/library/ms189484.aspx http://msdn.microsoft.com/en-us/library/ms190487.aspx</u>

`o` WHILE <u>http://msdn.microsoft.com/en-us/library/ms178642.aspx</u>

`o` sp_executesql <u>http://msdn.microsoft.com/en-us/library/ms188001.aspx</u>

- Stored Procedures

- <u>http://msdn.microsoft.com/en-us/library/ms190782.aspx</u>

 SQL Server technical documentation <u>https://docs.microsoft.com/en-us/sql/sql-server/sql-server-technicaldocumentation</u>
