CREATE TABLE LegalFaction(
                             factionId TINYINT PRIMARY KEY IDENTITY(1,1),
                             factionName VARCHAR(50) UNIQUE NOT NULL,
                             budget DECIMAL(12,2) DEFAULT 0,
                             maxMembers INT
)

INSERT INTO LegalFaction(factionName) VALUES ('Civilian')

CREATE TABLE Job(
                    jobId TINYINT PRIMARY KEY IDENTITY(1,1),
                    jobName VARCHAR(50) UNIQUE NOT NULL,
                    salary MONEY,
                    mandatoryUniform BIT DEFAULT 0
)

INSERT INTO Job(jobName, salary) VALUES ('Unemployed',0)

CREATE TABLE Offense(
                        offenseId TINYINT PRIMARY KEY IDENTITY(1,1),
                        offenseName VARCHAR(50) NOT NULL UNIQUE,
                        fine DECIMAL(12,2) DEFAULT 0,
                        jailMinutes INT DEFAULT 0
)

CREATE TABLE Player( -- main
                       playerId INT PRIMARY KEY IDENTITY(1,1),
                       firstName VARCHAR(50) NOT NULL,
                       lastName VARCHAR(50) NOT NULL,
                       dob DATE,
                       height DECIMAL(3,2),
                       cashMoney DECIMAL(12,2) DEFAULT 500,
                       bankMoney DECIMAL(12,2) DEFAULT 5000,
                       factionId TINYINT NOT NULL DEFAULT 1 FOREIGN KEY REFERENCES LegalFaction(factionId),
                       jobId TINYINT NOT NULL DEFAULT 1,
                       CONSTRAINT fk_Player_Job FOREIGN KEY (jobId) REFERENCES Job(jobId)
)

CREATE TABLE Phone(
                      phoneId INT PRIMARY KEY,
                      phoneNumber VARCHAR(20) NOT NULL UNIQUE,
                      brand VARCHAR(50),
                      model VARCHAR(50),
                      FOREIGN KEY (phoneId) REFERENCES Player(playerId)
)

CREATE TABLE Vehicle(
                        vehicleId INT PRIMARY KEY IDENTITY(1,1),
                        ownerId INT NOT NULL,
                        plate VARCHAR(20) NOT NULL UNIQUE,
                        brand VARCHAR(50),
                        model VARCHAR(50),
                        color VARCHAR(30),
                        fuelLevel FLOAT NOT NULL DEFAULT 100
)

ALTER TABLE Vehicle
    ADD CONSTRAINT fk_Vehicle_Player FOREIGN KEY (ownerId) REFERENCES Player(playerId)

CREATE TABLE Jail(
                     jailId INT PRIMARY KEY IDENTITY(1,1),
                     playerId INT NOT NULL FOREIGN KEY REFERENCES Player(playerId),
                     jailDate DATETIME DEFAULT GETDATE(),
                     jailMinutes INT
)

CREATE TABLE JailOffense(
                            jailId INT NOT NULL FOREIGN KEY REFERENCES Jail(jailId),
                            offenseId TINYINT NOT NULL FOREIGN KEY REFERENCES Offense(offenseId),
                            CONSTRAINT pk_JailOffense PRIMARY KEY (jailId, offenseId)
)

CREATE TABLE Business(
                         businessId INT PRIMARY KEY IDENTITY(1,1),
                         businessName VARCHAR(50) NOT NULL,
                         businessType VARCHAR(50) CHECK(businessType IN('Barbershop','Gas station','Clothing shop')),
                         ownerId INT NOT NULL FOREIGN KEY REFERENCES Player(playerId)
)

CREATE TABLE Home(
                     homeId INT PRIMARY KEY IDENTITY(1,1),
                     homeAddress VARCHAR(100) NOT NULL,
                     price DECIMAL(12,2),
                     ownerId INT NOT NULL,
                     CONSTRAINT fk_Home_Player FOREIGN KEY (ownerId) REFERENCES Player(playerId)
)


/* lab 2
5) SELECT [TOP n] expr [as alias] - top is the last thing
1) FROM source [join...on]
2) WHERE condition - filters the rows
3) GROUP BY columns
4) HAVING condition - filters the groups, cannot exist without group by
6) [UNION, INTERSECT, EXCEPT]
7) SORT BY condition [ASC/DESC..]

(st - name | subject | grade ) names can repeat(different subject)!
SELECT TOP 1 subject COUNT(*) as student, AVG(grade) as avg_grade
FROM R
WHERE grade >= 5
GROUP BY subject - you can only select the columns which the data group by
                 - you can't select any of the other columns
HAVING COUNT(*) >= 2
ORDER BY avg_grade DESC

- will return the average grade of the subject that have the best avg grade with >= 2 grades
- practical exam - 3 queries with multiple choice questions

(Sid | Name | year) ~ (Cid | title | credits) ~ (Sid | Cid | grade) grade can be null

 */

 /* lab 3
    Sid | name | year     -- Student
    1     Ana    2
    2     Mihai  2
    3     Ioana  3
    4     Radu   1

    Cid | title | credits -- Class
    10     DB       6
    20    NetW      5
    30     AI       5

    Sid | Cid | grade     -- Enrollments
    1     10     9
    1     20     7
    2     10     NULL
    3     10     8

    Get all students (name) enrolled in at least one class

    -- first thing:     SELECT DISTINCT sid -- what we need exactly
                        FROM Enrollments

    SELECT
    FROM Student
    WHERE sid IN (SELECT DISTINCT sid
                  FROM Enrollments)

    another way to query multiple table at the same time is JOIN

    SELECT *
    FROM Student S INNER JOIN
         Enrollments E  ON S sid = E sid
         -- we join on condition sid from Student table = sid from Enrollments

    First type of JOIN is INNER (only what is common in all tables)
    JOIN does a Cartesian equation (all tables from first Table concatenate with the second tables

    S.sid | S.name | S.year | E.sid | E.cid | E.grade
    1       Ana      2          1       10      9
    1       Ana      2          1       20      7
    2       Mihai    2          2       10      NULL
    3       Ioana    3          3       10      8

    Second type of JOIN is LEFT
    LEFT take every student, look it up in Enrollments, do the cartesian product, also include the
    students that we don't find in enrollments
    (include all students regardless if they have a enrollments or not)


    S.sid | S.name | S.year | E.sid | E.cid | E.grade
    1       Ana      2          1       10      9
    1       Ana      2          1       20      7
    2       Mihai    2          2       10      NULL
    3       Ioana    3          3       10      8
    4       Radu     1          NULL    NULL    NULL

    Third type of JOIN is RIGHT
    RIGHT JOIN same as LEFT, but include all enrollments even tho it doesnt have any students
    because we don't have enrollments that don't have a student, that means is the same as INNER

    S.sid | S.name | S.year | E.sid | E.cid | E.grade
    1       Ana      2          1       10      9
    1       Ana      2          1       20      7
    2       Mihai    2          2       10      NULL
    3       Ioana    3          3       10      8


    Forth type of JOIN is FULL
    FULL JOIN means include every student regardless of whether they have enrollments
    and include every enrollment regardless of whether it has any students

    INNER join is za best!
    LJURJ

    SELECT * S.name
    FROM Student S INNER JOIN
         Enrollments E ON S sid = E sid



    Views        (vw_ is not mandatory, you can name it however you want)
    good for security, consistency, optimized (you write it once, is optimized
    nobody can see student id for example, only the name, and everybody can use the view)

    CREATE VIEWS vw_student_enrollments AS
        SELECT Student S INNER JOIN
               Enrollments E on S sid = E sid
    SELECT * FROM vw_student_enrollments



    Stored Procedure / Functions (functions like any other programming language,
    but they don't return functions where functions must return values)
    (the most use case is inserting multiple data in a table, add another column in a table)

    -- sp = stored procedure
    -- we are allow only classes and student that exist
    -- firstly we need to validate if student exist (first check)

    CREATE PROCEDURE sp_enroll_student @sid INT, @cid INT AS
    BEGIN
        IF NOT EXIST (SELECT * FROM Student
                        WHERE sid = @sid)
            THROW "error syntax idono"

    -- than we need to validate if classes exist
    CREATE PROCEDURE sp_enroll_student @sid INT, @cid INT AS
    BEGIN
        IF NOT EXIST (SELECT * FROM Class
                        WHERE cid = @cid)
            THROW "error syntax idono"

    -- after that, if both if pass, we insert the enrollment
    CREATE PROCEDURE sp_enroll_student @sid INT, @cid INT AS
    BEGIN
        IF NOT EXIST (SELECT * FROM Student
                        WHERE sid = @sid)
            THROW "error syntax idono"
        IF NOT EXIST (SELECT * FROM Class
                        WHERE cid = @cid)
            THROW "error syntax idono"
        INSERT Enrollments VALUES (@sid, @cid, NULL)
    END

    -- if not exist = return null
    -- the syntax may be wrong somewhere!!!

  */


/* lab 4 (week 8)

   MIGRATIONS - changing things in a table, but be able to revert the code

   ALTER TABLE Student -- up operation
   ADD Column email

   ALTER TABLE Student -- down operation
   DROP Column email

   at the lab we need to write 7 scripts for down and 7 for up (14 in total)
   we will have 14 stored procedures
   is not mandatory up to be always add and down remove, it can be otherwise

    Sid | name | year     -- Student
    1     Ana    2
    2     Mihai  2
    3     Ioana  3

    CREATE PROCEDURE sp_addEmail AS
        ALTER TABLE Student
        ADD COLUMN email

    CREATE PROCEDURE sp_removeEmail AS
        ALTER TABLE Student
        DROP COLUMN email

   V1 - is the current structure
   V1 -> V2 (after adding email)
    Sid | name | year | email    -- Student
     1    Ana     2
     2    Mihai   2
     3    Ioana   3
   V2 -> V1 (after dropping the email)
   (init structure)

   Version  -- table
      1     -- if we wanna go to version 4, we need to execute all up functions till version 4
      2     -- we are at v4, if we wanna go to v2, that mean we need to execute down from v4 and v3
      3
      4

   -- very basic migration system
   -- some hundreds line of code, if we go way further that means the code is generated



 */

