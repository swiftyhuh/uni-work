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


/* lab 3
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

/* seminar 2
-- Find the distinct age of the spies whose name start with a and have at least 4 letters in they name
SELECT DISTINCT age From Spies
WHERE codeName like 'A____%'

-- Find the real name of the spies who have a task assigned for mission 100
SELECT s realName From Spies as s, Tasks as t
WHERE t_mid = 100 and t_spyId = s.id
-- vs
SELECT realName From Spies, Tasks
WHERE Tasks.mid = 100 and Tasks.spyId = Spices.id

-- BMI for the spies and if they are over 18

SELECT weight / (height * height) AS BMI,
        over18 = age - 18
FROM Spies

-- the ids of the spies who have task assigned for an online
-- mission and tey have also assigned a task for mission

select s.id from Spies as s, Mission as m
where m.location = 'Online'
and m.id = t.mid
intersect
select t.spyId from Tasks as T
where t.mid = 100
-- vs
select t.spyId from Missions as m, Tasks as t
where a.location = 'Online
and m.id = t.mid
UNION
select t.spyId from Tasks as t
where t.mid = 100

-- find all the spies whose names contain a starting from the second letter
-- but they don't have a task assigned for mission 100
SELECT s id from Spies as s,
where s.realName like '_%a%'
except
select t.spyId from Tasks as t
where t.mid = 100

-- find the real names of the spies who haven't assigned a task for mission 200
Select s.realName from Spies as s
where not in
    (select t.spyId
    from Tasks as t
    where t.mid = 200 and t.spyId = s.id)

-- find the real names of the spies that are taller than some spy whose age is over 20
Select s.realName from Spies as s
where s.height > ALL (
    select s1 height from Spies s1 where s1.age > 19
)

Joins

Spies
id | realName
1    Sam
2    Clover
3    Alex

Tasks
mid | spyId
100
100
800

-- AGGREGATION FUNCTIONS
COUNT(*)
COUNT / SUM / AVG([DISTINCT] A)
MIN / MAX (A)

-- count all the missions and the average difficulty level
SELECT COUNT(*) as no_of_missions, AVG(missions.difficulty) as avg_difficulty
from missions

-- Find the most difficult missions
SELECT * FROM Missions
WHERE m.difficulty = (
   SELECT MAX(difficulty) FROM Missions

-- find for each mission location the number of tasks associated and the average salary for a task
SELECT m.location, COUNT(*) as NO_TASKS,
AVG(t.salary) as AVG_SALLARY
FROM Missions as m, Tasks as t
WHERE T.mid = m.mid
GROUP BY m.location
   
SELECT * FROM Missions as m, Tasks as t
WHERE T.mid = m.mid
GROUP BY m.location



 */