<!-- page 1 -->
Databases Seminary 4

# _<u>Functions, views, system tables, triggers, MERGE instruction – in SQL Server</u>_

## _<u>Functions defined by users</u>_

   - the programmer can define his/her own functions; these ones can be use later in SQL queries;

   - 3 types of functions defined by users in SQL Server

- a. scalar

- b. inline table-valued

- c. multi-statement table valued

<!-- Start of picture text -->
CREATE FUNCTION <Inline_Function_Name, CREATE FUNCTION <Table_Function_Name, CREATE FUNCTION <Scalar_Function_Name, sysname, FunctionName> sysname, FunctionName> sysname, FunctionName> ( ( ( -- Add the parameters for the function  -- Add the parameters for the function here -- Add the parameters for the function here here <@param1, sysname, @p1> <@Param1, sysname, @p1> <@param1, sysname, @p1> <data_type_for_param1, , int>, <Data_Type_For_Param1, , int> <Data_Type_For_Param1, , int>, <@param2, sysname, @p2> ) <@param2, sysname, @p2> <data_type_for_param2, , char> RETURNS <Function_Data_Type, ,int> <Data_Type_For_Param2, , char> ) AS ) RETURNS BEGIN RETURNS TABLE <@Table_Variable_Name, sysname, @Table_Var> -- Declare the return variable here AS TABLE DECLARE <@ResultVar, sysname, RETURN ( @Result> <Function_Data_Type, ,int> ( -- Add the column definitions for the -- Add the SELECT statement with  TABLE variable here -- Add the T-SQL statements to compute the parameter references here <Column_1, sysname, c1> return value here SELECT 0  <Data_Type_For_Column1, , int>, SELECT <@ResultVar, sysname, ) <Column_2, sysname, c2> @Result> = <@Param1, sysname, @p1> GO <Data_Type_For_Column2, , int> ) -- Return the result of the function AS RETURN <@ResultVar, sysname, BEGIN @Result> <!-- End of picture text -->

1

<!-- page 2 -->
Databases Seminary 4

|-- Fill the table variable with the rows for your result set|END GO|
|---|---|
|RETURN||
|END GO||

## a. Scalar functions

- return a value

- disadvantage – in the case of a scalar function that operates on more rows, SQL Server executes the function once for each row from the result, fact that can have a significant impact through the performance

- example

|`select * from Students`|
|---|
|`-- drop function ufNoStudents`|
|`CREATE FUNCTION ufNoStudents(@ageINT)` `RETURNS INT AS` `BEGIN`|
|`DECLARE @noINT`|
|`SET @no= 0`|
|`SELECT @no= COUNT(*)`|
|`FROM Students`|
|`WHERE age= @age` `RETURN @no` `END` `GO`|
|`PRINT dbo.ufNoStudents(20)`|

## b. Inline table-valued functions

- return a table

- can be used anywhere where a table can be inside of a T-SQL query (ussualy in the FROM clause)

- example

```
CREATEFUNCTION ufStudentsName(@age INT)Command(s) completed successfully.
RETURNSTABLE
AS
RETURN
SELECT sname
FROM Students
WHERE age= @age
GO
SELECT*
FROM ufStudentsName(20)
```

2

<!-- page 3 -->
Databases Seminary 4

## c. Multi-statement table-valued functions

- returns a table

- the difference with the inline table-valued functions is that these ones can have more than one instruction

|`select * from Courses`|
|---|
|`CREATE FUNCTION ufCoursesWithCredits(@creditsINT)` `RETURNS @CoursesWithCreditsTABLE(cid` `varchar(10), cnameVARCHAR(50))` `AS` `BEGIN` `INSERT INTO @CoursesWithCredits` `SELECT cid, cname` `FROM Courses` `WHERE credits= @credits` `IF @@ROWCOUNT = 0` `INSERT INTO @CoursesWithCredits`|
|`VALUES(0,'No course was found for that number of` `credits.')` `RETURN` `END` `GO`|
|`SELECT * FROM ufCoursesWithCredits(5)`|
|`SELECT * FROM ufCoursesWithCredits(6)`|
|`SELECT * FROM ufCoursesWithCredits(8)`|

## _<u>Views</u>_

- a view creates a virtual table that represent the dates from one or more tables in an alternative way;

- the content of the virtual table (columns and rows) is defined by a query; - it can have a maximum of 1024 columns;

- the syntax

CREATE VIEW view_name AS SELECT_instruction

- example

3

<!-- page 4 -->
Databases Seminary 4

<!-- Start of picture text -->
CREATE VIEW vStudentsExam  select * from vStudentsExam AS SELECT s.sid, sname, sgroup, grade FROM Students s INNER JOIN Exams e ON s.sid=e.sid GO -- Command(s) completed successfully. -- with encryption CREATE VIEW vStudentsAge WITH ENCRYPTION AS SELECT sname, age FROM Students WHERE age>=19; GO select * from vStudentsAge -- with check option CREATE VIEW vSEC AS SELECT s.sname, c.cname, e.grade FROM Students s INNER JOIN Exams e ON s.sid=e.sid INNER JOIN Courses c ON c.cid=e.cid WHERE e.grade>=5 WITH CHECK OPTION ; GO select * from vSEC ALTER TABLE test ADD tDate DATETIME -- using built-in functions CREATE VIEW vTest AS SELECT TOP (10) tid, SUM(code) AS CodeSum FROM test WHERE tDate > CONVERT(DATETIME,'20001231',101) GROUP BY tid; GO select * from vTest <!-- End of picture text -->

## _<u>System Tables</u>_

4

<!-- page 5 -->
## Databases Seminary 4

- special tables with information about all the objects created in a database (tables, columns, indexes, stored procedures, functions defined by the user, views, and so on)

- are managed by the server (are not modified directly by the user)

- examples: - _<mark>sys.objects</mark>_ – contains a row for each object  (constraint, stored procedure, table and so on) created in a database;

- _<mark>sys.columns</mark>_ – a row for each column of an object that has columns, e.g. tables or views;

- - _<mark>sys.sql_modules</mark>_ – a row for each object that it is a defined  module in the SQL language in SQL <u>Server (e.g., objects like procedures, functions, with a SQL module asociated).</u>

```
select*fromsys.objects
```

```
select*fromsys.columns
```

```
select*fromsys.sql_modules
```

```
SELECTSCHEMA_NAME(schema_id)ASschema_name,nameAS
table_name
FROMsys.tables
WHEREOBJECTPROPERTY(object_id,'TableHasPrimaryKey')= 0
ORDERBYschema_name, table_name;
GO
```

## _<u>Triggers</u>_

- a special type of stored procedures;

- are automatically executed when a DML (Data Manipulation Language) instruction is executed (INSERT, UPDATE, DELETE) or a DDL (Data Definition Language) instruction (e.g. CREATE_DATABASE, CREATE_TABLE, DROP_TABLE, DROP_LOGIN, UPDATE_STATISTICS, DROP_TRIGGER, ALTER_TABLE);

- are not executed directly

- trigger syntax for the instruction INSER/UPDATE/DELETE on a table or view:

CREATE TRIGGER < trigger_name> ON { table | view} <u>[ WITH <trigger_option_DML > [ ,...n ] ]</u>

5

<!-- page 6 -->
Databases Seminary 4

- { FOR | AFTER | INSTEAD OF } { [INSERT] [,] [UPDATE] [,] [DELETE] } [ WITH APPEND ] [ NOT FOR REPLICATION ] AS { sql_instruction [;] [ ,...n ] | EXTERNAL NAME <method specifier[;] > }

- the execution moment for a trigger is specified through one of the options:

- FOR, AFTER – the DML trigger is starting only when all the operations specified in the

- starting instruction have been executed with success (more triggers can be defined);

   - INSTEAD OF - the DML trigger is executed instead of the starting action.

- if more triggers are defined for the same action, these ones are executed random;

- when a trigger is executed, one can access 2 special tables called _inserted_ and _deleted_ .

- example `Create table Product( Pid int primary key identity, Name varchar(50), OperationDate date, Quantity int ) insert into Product Values ('cherries', '2018-11-11', 5), ('oranges', '2018-12-11', 6) create table BuyLog( Bid int primary key identity, Name varchar(50), OperationDate date, Quantity int ) select * from Product select * from BuyLog`

6

<!-- page 7 -->
## Databases

## Seminary 4

```
CREATETRIGGER Add_Product
ON Product
FORINSERT
AS
BEGIN
INSERTINTO BuyLog(Name, OperationDate, Quantity)
SELECTName,GETDATE(), Quantity
FROM inserted
END
GO
--
select*from Product
select*from BuyLog
insertinto Product Values ('tomatoes','2018-11-11', 5),
('potatoes','2018-12-11', 6)
select*from Product
select*from BuyLog
-- after create trigger - one obtain the values inserted in
table Product also in table BuyLog
```

```
select*from Product
select*from BuyLog
CREATETRIGGER Delete_Product
ON Product
FORDELETE
AS
BEGIN
SETNOCOUNTON;
INSERTINTO BuyLog(Name, OperationDate, Quantity)
SELECTName,GETDATE(), Quantity
FROM deleted Command(s) completed successfully.
END
GO
deletefrom Product
Where Quantity=6 andNameLIKE'p%'
-- the rows with potatoes should be deleted from
Product and introduced in BuyLog
select*from Product
select*from BuyLog
```

7

<!-- page 8 -->
## Databases

## Seminary 4

|`create table SellLog(`||
|---|---|
|`Sid int primary key identity,`||
|`Name varchar(50),` ||
|`OperationDatedate,` ||
|`Quantityint)`||
|`select * from Product` `select * from BuyLog` `*  `||
|`select  from SellLog`||
|`CREATE TRIGGER Modify_Update_Product` `ON Product` `FOR UPDATE` `AS` `BEGIN` `SET NOCOUNT ON;` `INSERT INTO SellLog(Name, OperationDate, Quantity)` `SELECT d.Name, GETDATE(), d.Quantity- i.Quantity` `FROM deleted dINNER JOIN inserted iON d.Pid= i.Pid` `WHERE i.Quantity< d.Quantity` `INSERT INTO BuyLog(Name, OperationDate, Quantity)` `SELECT i.Name, GETDATE(), i.Quantity- d.Quantity` `FROM deleted dINNER JOIN inserted iON d.Pid= i.Pid` `WHERE i.Quantity> d.Quantity` `END` `GO` `Command(`|`s) completed successfully.`|
|`update Product`||
|`set Quantity=8 ` `WHERE Quantity=6 `||
|`select * from Product`||
|`select * from BuyLog`||
| `select * from SellLog`||

8

<!-- page 9 -->
Databases

Seminary 4

```
update Product
set Quantity=Quantity+1
whereNameLIKE'%es'
select*from Product
select*from BuyLog
select*from SellLog
```

## _<u>SET NOCOUNT</u>_

## SET NOCOUNT ON/OFF

- the number of the affected rows by a T-SQL instruction or by a stored procedure:

   - no run (ON) – the count is not returned.

   - run (OFF)  - the count is returned.

- @@ROWCOUNT always is modifying.

```
select*from test
SETNOCOUNTON1
insertinto test(tname,description, code)
values ('t','d', 9)
print@@ROWCOUNT
SETNOCOUNTOFF(1 row(s) affected)
insertinto test(tname,description, code)1
values ('t','d', 10)
print@@ROWCOUNT
select*from test
```

## _<u>Change Data Capture</u> (CDC)_

- information about the DML changes on the table/database;

- introduced in SQL Server 2008;

- sys.sp_cdc_enable_db – CDC for the database;

- sys.sp_cdc_enable_table – CDC for the monitories tables;

9

<!-- page 10 -->
## Databases Seminary 4

- allows the data archiving and monitoring without a supplementary programming effort (e.g., by writing triggers);

- the changing from the tables created by the user are monitored;

- the result data from the monitoring are stored in tables that can queried with SQL;

- mirror tables are created and contain the columns of the monitoring tables + the metadata that describe the changes.

```
EXECUTEsys.sp_cdc_enable_db
```

```
Msg 22988, Level 16, State 1, Procedure sp_cdc_enable_db, Line 14 [Batch Start Line 256]
This instance of SQL Server is the Express Edition (64-bit). Change data capture is only
available in the Enterprise, Developer, and Enterprise Evaluation editions.
```

```
EXECUTEsys.sp_cdc_enable_table
@source_schema =N'dbo'
, @source_name =N'test'
,@role_name =N'cdc_Admin';
Msg 22988, Level 16, State 1, Procedure sp_cdc_enable_table, Line 24 [Batch Start Line
257]
```

```
This instance of SQL Server is the Express Edition (64-bit). Change data capture is only
available in the Enterprise, Developer, and Enterprise Evaluation editions.
```

10

<!-- page 11 -->
Databases Seminary 4

## _<u>MERGE instruction</u>_

- allows the comparison between the rows from a source table and a destination table;

- based on the result of the comparison, one can execute INSERT, UPDATE or DELETE commands, e.g., one can execute modification operations / delete operations on a destination table based on the result of a join with a source table.

MERGE Table_Definition AS Destination USING (Source_Table) AS Source ON (Search_terms) WHEN MATCHED THEN UPDATE SET or DELETE WHEN NOT MATCHED [BY TARGET] THEN INSERT WHEN NOT MATCHED BY SOURCE THEN UPDATE SET or DELETE

- example

```
createtable Books(
Bid intprimarykey,
Title varchar(50),
Author varchar(50),
ISBN varchar(20),
Pages int)
select*from Books
insertinto Books(Bid, Title, Author)values (1,'Searching the lost time','Marcel
Proust')
insertinto Books(Bid, Title, Pages)values (2,'Searching the lost time', 350)
insertinto Books(Bid, Title, ISBN)values (3,'Searching the lost time',
'9789731246420')
select*from Books
```

```
MERGE Books
USING
(SELECTMAX(Bid) Bid, Title,MAX(Author) Author,MAX(ISBN) ISBN,MAX(Pages) Pages
FROM Books
GROUPBY Title) MergeData ON Books.Bid = MergeData.Bid
WHENMATCHEDTHEN
```

11

<!-- page 12 -->
Databases Seminary 4

```
UPDATESET Books.Title = MergeData.Title,
Books.Author = MergeData.Author,
Books.ISBN = MergeData.ISBN,
Books.Pages = MergeData.Pages
WHENNOTMATCHEDBYSOURCETHENDELETE;
Warning: Null value is eliminated by an aggregate or other SET operation.
(3 row(s) affected)
select*from Books
```

12
