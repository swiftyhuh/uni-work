<!-- page 1 -->
_<u>Seminar 3 – Documentations – Examples</u>_

Stored procedures:

<!-- Start of picture text -->
select * from Students <!-- End of picture text -->

FIRST – the stored procedure is CREATED

<!-- Start of picture text -->
CREATE PROCEDURE uspNameStudents   Command(s) completed successfully. AS SELECT sname FROM Students GO -- DROP PROCEDURE uspNameStudents <!-- End of picture text -->

1

<!-- page 2 -->
# SECOND – the stored procedure is EXECUTED

|`EXEC uspNameStudents `|
|---|
|`EXECUTE uspNameStudents `|
|`uspNameStudents`|

# Raiserror - generate an error message and initiates the error processing to the session

|`RAISERROR`         `-- The mes` `GO  `|`(N'This is message %s %d.', -- Message text.` `10, -- Severity,` `1, -- State,`  `N'number', -- First argument.` `5); -- Second argument.` `sage text returned is: This is message number 5.`|`This is message number` `5.`|
|---|---|---|
|`RAISERROR`           `-- The mes` `GO`|`(N'<\<%*.*s>>', -- Message text.` `10, -- Severity,` `1, -- State,` `7, -- First argument used for width.` `3, -- Second argument used for precision.`  `N'abcde'); -- Third argument supplies the string.` `sage text returned is: <<    abc>>.`|`<\<    abc>>`|
|`RAISERROR`       `-- The mes` `GO`|`(N'<\<%7.3s>>', -- Message text.` `10, -- Severity,` `1, -- State,`  `N'abcde'); -- First argument supplies the string.` `sage text returned is: <<    abc>>.`|`<\<    abc>>`|
|`OR`|||
|`DECLARE @S` `SET @Strin`|`tringVariableNVARCHAR(50);` `gVariable= N'<\<%7.3s>>';`||
|`RAISERROR`       `-- The mes` `GO`|`(@StringVariable, -- Message text.` `10, -- Severity,` `1, -- State,`  `N'abcde'); -- First argument supplies the string.` `sage text returned is: <<    abc>>.`||

# <u>Global Variables</u>

```
-- - @@ERROR – the error number for the last Command(s) completed successfully.
executed T-SQL statement; 0 - no error occurred
IF@@ERROR<> 0
PRINT'Your error message';
```

2

<!-- page 3 -->
|`-- @@IDENTITY - the last inserted IDENTITY value` `SELECT @@IDENTITY AS 'Identity';`||
|---|---|
|`create table test(` `tidint primary key identity,` `tnamevarchar(50),` `description varchar(50),` `codeint)`|`(0 row(s) affected)` `Msg 544, Level 16, State 1, Line 112` `Cannot insert explicit value for identity column` `in table 'test' when IDENTITY_INSERT is set to` `OFF.`|
|`select * from test`|`(1 row(s) affected)`|
|`INSERT INTO test(tid, tname, description, code)` `Values(1, 'test1', 'decription 1', 8)` `go` `select @@IDENTITY As 'Identity'`||
|`INSERT INTO test(tname, description, code) Values` `('test2', 'decription 2', 88)` `INSERT INTO test(tname, description, code) Values` `('test3', 'decription 3', 888)` `go` `INSERT INTO test(tname, description, code) Values` `('test4', 'decription 4', 8888)`||
|`select @@IDENTITY As 'Identity'`||
|`-- @@ROWCOUNT - the number of rows affected by the` `last statement` `IF @@ROWCOUNT = 0`  `PRINT 'Warning: No rows were updated';`  `select @@ROWCOUNT`|`(1 row(s) affected)`|
|`-- @@SERVERNAME - the name of the local server on` `which SQL Server is running`  `SELECT @@SERVERNAME AS 'Server Name'`||
|`-- @@SPID - the session id for the current user` `process`||
|`SELECT @@SPID AS 'ID', SYSTEM_USER AS 'Login` `Name', USER AS 'User Name'`||
|`-- @@VERSION - system and build information`||
|`SELECT @@VERSION AS 'SQL Server Version'`||

|Select INTO– the resultwill be displayed in another table|
|---|
|`-- SELECT INTO`|
|`select * from Students`|
|`IF OBJECT_ID ('dbo.StudentsCopy', 'U') IS NOT NULL` `DROP TABLE dbo.StudentsCopy;`|
|`select sname, age`|
|`INTO dbo.StudentsCopy`|
|`from Students`|
|`where emaillike'%@cs.ro'`|

3

<!-- page 4 -->
|`select * from StudentsCopy`|
|---|

|TheOUTPUTClause `create table ModifiedCourses(` `cidvarchar(10) primary key,`||
|---|---|
|`cnamevarchar(50) not null,`||
|`creditsint,`||
|`dateMdate,`||
|`snvarchar(128))`||
|`Select * from Courses` `select * from ModifiedCourses`||
|`UPDATE Courses` `SET cname= 'Database Management Systems'` `OUTPUT inserted.cid, deleted.cname, inserted.credits, GETDATE()` `optional login security identification number` `INTO ModifiedCourses` `WHERE cid= 'DB2'` `--(1 row(s) affected)`|`, SUSER_SNAME()  -- Is the`|
|`select * from Courses` `select * from ModifiedCourses`||

<u>Cursors</u> `DECLARE @sid INT, @sname VARCHAR(50) DECLARE CursorStudents CURSOR FOR SELECT sid, sname FROM Students OPEN CursorStudents FETCH CursorStudents INTO @sid, @sname WHILE @@FETCH_STATUS = 0 BEGIN --code to proccess @sid, @sname print 'The record with the sid=' + CAST(@sid AS varchar(50)) + ' has the name ' + CONVERT(varchar(50), @sname) FETCH CursorStudents INTO @sid, @sname END CLOSE CursorStudents DEALLOCATE CursorStudents`

4
