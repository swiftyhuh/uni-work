-- CREATE PROC uspNumberMission(@difficulty INT, @number_of_mission INT)
--     AS
--         SELECT @number_of_mission = Count(mid) FROM Missions as m
--         WHERE m.difficulty = @difficulty
--
-- DECLARE @nom INT = 0
-- SET @nom = 0
--
-- EXEC uspNumberMission 10, @num OUTPUT
-- PRINT @nom
--
-- SELECT mid, difficulty, name FROM Mission
--
-- go
-- CREATE or ALTER PROC uspNumberMission(@difficulty INT, @number_of_mission INT)
--     AS
--         begin
--         SELECT @number_of_mission = Count(mid) FROM Missions AS m
--         WHERE m.difficulty = @difficulty
--         if @number_of_mission = 0
--             raiseerror('No missions found', 9, 1)
--             -- ('Error message', Severity [0-25], state of the error [0-255])
--         end
--     GO
--
-- PRINT @@ERROR
-- SELECT @@ERROR



/*
 G V
 @@ERROR
 @@IDENTITY
 @@RowCOUNT
 @@VERSION - for the sql system
 @@SERVERNAME
 @@SPID
 */

-- Dynamic Execution
-- sys.tables - can see the tables names and all the values

EXEC ('SELECT * FROM Spies')
DECLARE @CMD VARCHAR(300), @param VARCHAR(200)
set @CMD = 'SELECT * FROM Spies WHERE id = 1'
-- set @param = '1; SELECT * FROM sys.tables; DROP table users --' sql injection
set @param = '1 OR 1=1 --' -- to prevent sql injection
EXEC (@CMD + @param)

-- prevent sql injection
exec sp_executesql
N'SELECT * FROM Spies WHERE id = @id'
N'@id INT',
@id=1

-- The OUTPUT clause (used with INSERT, UPDATE, DELETE)
-- inserted - new values, deleted - old values
SELECT * FROM LogChanges
UPDATE Spies
Set age = age + 2
OUTPUT INSERTED.id, INSERTED.age, DELETED.age, GETDATE(), SUSER_NAME()
INTO LogChanges
WHERE age >= 20

/*
-- CURSORS works like a iterator over a table
-- is not very efficiency. We need to declare it first
DECLARE CURSOR - name + select statement
OPEN - select stmt executed + stored
FETCH - first, next, last, prior, absolute (int, whith different attributes when n=0 - no rows, n>0 - the nth row or n<0, nth row from the last)
FETCH RELATIVE m, m = 0 - current row, m > 0 mth row after the current collum, m < 0 mth row before the current collum
CLOSE - name, resources are deallocated
DEALLOCATE - all resources related to the function are freed
@@FETCH_STATUS - is zero when no more elements
using only FETCH wihtout any parameters will use default FETCH
*/

 -- Cursor
DECLARE @mid INT, @location VARCHAR(100)
DECLARE MissionsCursor CURSOR FOR
    SELECT mid, location FROM Missions as m
    OPEN MissionsCursor
    FETCH MissionsCursor
    INTO @mid, @location
    WHILE @@FETCH_STATUS = 0
    BEGIN
        PRINT CAST(@mid AS VARCHAR(10)) + ' ' + @location
        FETCH MissionsCursor into @mid, @location
    end
    CLOSE MissionsCursor
    DEALLOCATE MissionsCursor


