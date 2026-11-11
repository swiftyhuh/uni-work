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

