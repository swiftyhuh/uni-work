CREATE TABLE LegalFaction
(
    factionId   TINYINT PRIMARY KEY IDENTITY (1,1),
    factionName VARCHAR(50) UNIQUE NOT NULL,
    budget      DECIMAL(12, 2) DEFAULT 0,
    maxMembers  INT
)

INSERT INTO LegalFaction(factionName)
VALUES ('Civilian')

CREATE TABLE Job
(
    jobId            TINYINT PRIMARY KEY IDENTITY (1,1),
    jobName          VARCHAR(50) UNIQUE NOT NULL,
    salary           MONEY,
    mandatoryUniform BIT DEFAULT 0
)

INSERT INTO Job(jobName, salary)
VALUES ('Unemployed', 0)

CREATE TABLE Offense
(
    offenseId   TINYINT PRIMARY KEY IDENTITY (1,1),
    offenseName VARCHAR(50) NOT NULL UNIQUE,
    fine        DECIMAL(12, 2) DEFAULT 0,
    jailMinutes INT            DEFAULT 0
)

CREATE TABLE Player
( -- main
    playerId  INT PRIMARY KEY IDENTITY (1,1),
    firstName VARCHAR(50) NOT NULL,
    lastName  VARCHAR(50) NOT NULL,
    dob       DATE,
    height    DECIMAL(3, 2),
    cashMoney DECIMAL(12, 2)       DEFAULT 500,
    bankMoney DECIMAL(12, 2)       DEFAULT 5000,
    factionId TINYINT     NOT NULL DEFAULT 1 FOREIGN KEY REFERENCES LegalFaction (factionId),
    jobId     TINYINT     NOT NULL DEFAULT 1,
    CONSTRAINT fk_Player_Job FOREIGN KEY (jobId) REFERENCES Job (jobId)
)

CREATE TABLE Phone
(
    phoneId     INT PRIMARY KEY,
    phoneNumber VARCHAR(20) NOT NULL UNIQUE,
    brand       VARCHAR(50),
    model       VARCHAR(50),
    FOREIGN KEY (phoneId) REFERENCES Player (playerId)
)

CREATE TABLE Vehicle
(
    vehicleId INT PRIMARY KEY IDENTITY (1,1),
    ownerId   INT         NOT NULL,
    plate     VARCHAR(20) NOT NULL UNIQUE,
    brand     VARCHAR(50),
    model     VARCHAR(50),
    color     VARCHAR(30),
    fuelLevel FLOAT       NOT NULL DEFAULT 100
)

ALTER TABLE Vehicle
    ADD CONSTRAINT fk_Vehicle_Player FOREIGN KEY (ownerId) REFERENCES Player (playerId)

CREATE TABLE Jail
(
    jailId      INT PRIMARY KEY IDENTITY (1,1),
    playerId    INT NOT NULL FOREIGN KEY REFERENCES Player (playerId),
    jailDate    DATETIME DEFAULT GETDATE(),
    jailMinutes INT
)

CREATE TABLE JailOffense
(
    jailId    INT     NOT NULL FOREIGN KEY REFERENCES Jail (jailId),
    offenseId TINYINT NOT NULL FOREIGN KEY REFERENCES Offense (offenseId),
    CONSTRAINT pk_JailOffense PRIMARY KEY (jailId, offenseId)
)

CREATE TABLE Business
(
    businessId   INT PRIMARY KEY IDENTITY (1,1),
    businessName VARCHAR(50) NOT NULL,
    businessType VARCHAR(50) CHECK (businessType IN ('Barbershop', 'Gas station', 'Clothing shop')),
    ownerId      INT         NOT NULL FOREIGN KEY REFERENCES Player (playerId)
)

CREATE TABLE Home
(
    homeId      INT PRIMARY KEY IDENTITY (1,1),
    homeAddress VARCHAR(100) NOT NULL,
    price       DECIMAL(12, 2),
    ownerId     INT          NOT NULL,
    CONSTRAINT fk_Home_Player FOREIGN KEY (ownerId) REFERENCES Player (playerId)
)

ALTER TABLE Jail
    DROP COLUMN jailMinutes

INSERT INTO Player(firstName, lastName, dob, height)
VALUES ('Mihai', 'Szabo', '2006-09-26', 1.78)

-- violates
--INSERT INTO JailOffense(jailId, offenseId)
--VALUES (1, 2)

INSERT INTO LegalFaction(factionName, budget, maxMembers)
VALUES ('Police', 50000, 30)
INSERT INTO LegalFaction(factionName, budget, maxMembers)
VALUES ('Ambulance', 30000, 20)
INSERT INTO LegalFaction(factionName, budget, maxMembers)
VALUES ('Firefighters', 20000, 15)
INSERT INTO LegalFaction(factionName, budget)
VALUES ('Mechanics', 8000)

INSERT INTO Job(jobName, salary, mandatoryUniform)
VALUES ('Bus Driver', 2200, 1)
INSERT INTO Job(jobName, salary, mandatoryUniform)
VALUES ('Taxi Driver', 1800, 0)
INSERT INTO Job(jobName, salary, mandatoryUniform)
VALUES ('Trash Collector', 1500, 1)
INSERT INTO Job(jobName, salary)
VALUES ('Miner', 3000)
INSERT INTO Job(jobName)
VALUES ('Street Sweeper')

INSERT INTO Offense(offenseName, fine)
VALUES ('Speeding', 250)
INSERT INTO Offense(offenseName, fine)
VALUES ('Illegal Parking', 100)
INSERT INTO Offense(offenseName, fine, jailMinutes)
VALUES ('Assault', 1000, 30)
INSERT INTO Offense(offenseName, fine, jailMinutes)
VALUES ('Armed Robbery', 5000, 90)
INSERT INTO Offense(offenseName, fine, jailMinutes)
VALUES ('Bank Robbery', 10000, 120)
INSERT INTO Offense(offenseName, jailMinutes)
VALUES ('Evading Police', 45)
INSERT INTO Offense(offenseName, fine, jailMinutes)
VALUES ('Vandalism', NULL, 10)

UPDATE LegalFaction
SET budget = budget + 5000
WHERE factionName IN ('Police', 'Ambulance')

UPDATE Job
set mandatoryUniform = 1
WHERE jobName like '%Driver'
  AND salary
    BETWEEN 1500 and 2500

UPDATE Offense
SET jailMinutes = jailMinutes + 15
WHERE fine >= 1000
  AND NOT offenseName = 'Assault'

DELETE
FROM Job
WHERE salary IS NULL
   or (salary < 1600 AND salary > 0)

DELETE
FROM Offense
WHERE fine <= 100
  AND jailMinutes <> 45

INSERT INTO Player(firstName, lastName, dob, height, cashMoney, bankMoney, factionId, jobId)
VALUES ('Alex', 'Popescu', '1999-03-14', 1.82, 1200, 1500, 2, 1),
       ('Marian', 'Unghie', '1967-09-26', 1.68, 22000, 800, 3, 1),
       ('Mihai', 'Scorbura', '1995-11-02', 1.90, 300, 200, 1, 2),
       ('Marcel', 'Ureche', '2003-01-09', 2.12, 100000, 4000, 1, 3),
       ('Elena', 'Ciupearca', '2006-02-27', 1.20, 1000, 60000, 4, 1),
       ('Diana', 'Sosoaca', '1975-11-13', 1.70, 0, 0, 5, 5)

INSERT INTO Player(firstName, lastName, dob, height)
VALUES ('Antonia', 'BEMVEU', '2002-12-05', 1.70),
       ('Bogdan', 'Pop', '1997-08-21', 1.80)

SELECT playerId, firstName, lastName
FROM Player

INSERT INTO Phone(phoneId, phoneNumber, brand, model)
VALUES (1, '0712345678', 'Apple', 'iPhone 13'),
       (2, '0723456789', 'Samsung', 'Galaxy S21'),
       (4, '0734567890', 'Samsung', 'Galaxy A52'),
       (5, '0745678901', 'Apple', 'iPhone 15 Pro'),
       (7, '0756789012', 'Apple', 'iPhone 15')

INSERT INTO Vehicle(ownerId, plate, brand, model, color, fuelLevel)
VALUES (1, 'CJ01MIB', 'Skoda', 'Superb', 'Black', 85.5),
       (1, 'CJ02MIB', 'Audi', 'A4', 'Gray', 40),
       (1, 'B03MIB', 'BMW', 'X5', 'White', 100),
       (2, 'CJ10ALX', 'Dacia', 'Logan', 'Blue', 15.2),
       (2, 'CJ11ALX', 'Dacia', 'Duster', 'Green', 60),
       (4, 'B20SCR', 'Mercedes', 'C220', 'Black', 92),
       (4, 'B21SCR', 'Mercedes', 'G63', 'Black', 100),
       (5, 'CJ30URE', 'Ford', 'Focus', NULL, 5),
       (7, 'IS40DNA', 'Volkswagen', 'Golf', 'Red', 70)

INSERT INTO Jail(playerId, jailDate)
VALUES (2, '2026-10-02'),
       (2, '2026-10-20'),
       (5, '2026-10-08'),
       (4, '2026-10-15'),
       (8, '2026-11-01')

SELECT *
FROM Offense

INSERT INTO JailOffense(jailId, offenseId)
VALUES (1, 4),
       (2, 6),
       (3, 5),
       (3, 6),
       (4, 3),
       (5, 7)

INSERT INTO Home(homeAddress, price, ownerId)
VALUES ('Memorandumului 5, Cluj-Napoca', 85000, 2),
       ('Stefan cel Mare, Teius', 120000, 1),
       ('Fabricii 3, Cluj-Napoca', 450000, 5),
       ('Observatorului 18, Cluj-Napoca', 300000, 5),
       ('Horea 44, Cluj-Napoca', 60000, 6)

INSERT INTO Business(businessName, businessType, ownerId)
VALUES ('M6 Barbershop', 'Barbershop', 3),
       ('Bershka', 'Clothing shop', 2),
       ('OMV', 'Gas station', 4),
       ('Petrom', 'Gas station', 5),
       ('Zara', 'Clothing shop', 5)

INSERT INTO Vehicle(ownerId, plate, brand, model, color, fuelLevel)
VALUES (3, 'B50MAR', 'Dacia', 'Sandero', 'Gray', 55),
       (6, 'CJ60ELE', 'Opel', 'Astra', 'Red', 30)

INSERT INTO Phone(phoneId, phoneNumber, brand, model)
VALUES (8, '0767890123', 'Samsung', 'Galaxy S23')

CREATE TABLE Item
(
    itemId   INT PRIMARY KEY IDENTITY (1,1),
    itemName VARCHAR(50) NOT NULL UNIQUE,
    itemType VARCHAR(30) CHECK (itemType IN ('Food', 'Drink', 'Medical', 'Tool')),
    price    DECIMAL(12, 2)
)

CREATE TABLE Inventory
(
    playerId INT NOT NULL FOREIGN KEY REFERENCES Player (playerId),
    itemId   INT NOT NULL FOREIGN KEY REFERENCES Item (itemId),
    quantity INT NOT NULL DEFAULT 1,
    CONSTRAINT pk_Inventory PRIMARY KEY (playerId, itemId)
)

INSERT INTO Item(itemName, itemType, price)
VALUES ('Water', 'Drink', 2),
       ('Energy Drink', 'Drink', 5),
       ('Sandwich', 'Food', 4),
       ('Burger', 'Food', 8),
       ('Bandage', 'Medical', 15),
       ('First Aid Kit', 'Medical', 50),
       ('Lockpick', 'Tool', 100),
       ('Repair Kit', 'Tool', 150)

INSERT INTO Inventory(playerId, itemId, quantity)
VALUES (2, 1, 5),
       (2, 3, 3),
       (2, 7, 2),
       (5, 1, 10),
       (5, 4, 4),
       (5, 7, 1),
       (5, 8, 1),
       (4, 2, 6),
       (4, 8, 2),
       (7, 1, 2),
       (7, 8, 3),
       (6, 1, 3),
       (6, 5, 4),
       (6, 6, 1),
       (3, 3, 2),
       (3, 5, 2)

-- a1) UNION players who own a home or a business
SELECT H.ownerId
FROM Home H
UNION
SELECT B.ownerId
FROM Business B

-- a2) OR vehicles that are black or low on fuel + parentheses + AND NOT
SELECT V.plate, V.brand, V.color, V.fuelLevel
FROM Vehicle V
WHERE (V.color = 'Black' or V.fuelLevel < 20)
  AND NOT V.brand = 'Dacia'

-- b1) INTERSECT players who have a phone and a home
SELECT P.phoneId
FROM Phone P
INTERSECT
SELECT H.ownerId
FROM Home H

-- b2) IN players who own a business and have been jailed, with money and employed
SELECT P.firstName, P.lastName
FROM Player P
WHERE P.playerId IN (SELECT B.ownerId
                     FROM Business B)
  AND P.playerId IN (SELECT J.playerId
                     FROM Jail J)
  AND (P.cashMoney > 10000 OR P.bankMoney > 10000)
  AND NOT P.jobId = 1

-- c1) EXCEPT players who own a home but no business
SELECT H.ownerId
FROM Home H
EXCEPT
SELECT B.ownerId
FROM Business B

-- c2) NOT IN players who have a vehicle but no phone
SELECT P.firstName, P.lastName
FROM Player P
WHERE P.playerId IN (SELECT V.ownerId
                     FROM Vehicle V)
  AND P.playerId NOT IN (SELECT PH.phoneId
                         FROM Phone PH)

-- d1) INNER JOIN (two m:n) jailed players, their offenses, and who carries a Lockpick + arithmetic
SELECT P.firstName, P.lastName, o.offenseName, IT.itemName, I.quantity, I.quantity * IT.price AS totalValue
FROM Player P
         INNER JOIN Jail J on J.playerId = P.playerId
         INNER JOIN JailOffense JO on JO.jailId = J.jailId
         INNER JOIN Offense O on O.offenseId = JO.offenseId
         INNER JOIN Inventory I on I.playerId = P.playerId
         INNER JOIN Item IT ON IT.itemId = I.itemId
WHERE IT.itemName = 'Lockpick'

-- d2) LEFT JOIN (3 tables) every player with phone brand and vehicle plate
SELECT P.firstName, P.lastName, PH.brand, V.plate
FROM Player P
         LEFT JOIN Phone PH ON PH.PhoneId = P.playerId
         LEFT JOIN Vehicle V on V.ownerId = P.playerId

-- d3) RIGHT JOIN every offense and the arrest it appears in
SELECT O.offenseName, JO.jailId
FROM JailOffense JO
         RIGHT JOIN Offense O ON O.offenseId = JO.offenseId

-- d4) FULL JOIN phone owners vs vehicle owners
SELECT PH.phoneId, PH.phoneNumber, V.ownerId, V.plate
FROM Phone PH
         FULL JOIN Vehicle V ON V.ownerId = PH.phoneId

-- e1) IN players who own a gas station
SELECT P.firstName, P.lastName
FROM Player P
WHERE P.playerID IN (SELECT B.ownerId
                     FROM Business B
                     WHERE B.businessType = 'Gas station')

-- e2) IN (nested) players who carry a tool item
SELECT P.firstName, P.lastName
FROM Player P
WHERE P.playerId IN (SELECT I.playerId
                     FROM Inventory I
                     WHERE I.itemId In (SELECT IT.itemId
                                        FROM Item IT
                                        WHERE IT.itemType = 'Tool'))

-- f1) EXISTS players who have been jailed
SELECT P.firstName, P.lastName
FROM Player P
WHERE EXISTS (SELECT *
              FROM Jail J
              WHERE J.playerId = P.playerId)

-- f2) EXISTS players who own a very expensive or very cheap home, not in Teius
SELECT P.firstName, P.lastName
FROM Player P
WHERE EXISTS (SELECT *
              FROM Home H
              WHERE H.ownerId = P.playerId
                AND (H.price > 100000 or H.price < 70000)
                AND NOT H.homeAddress LIKE '%Teius')

-- g1) subquery in FROM + TOP + ORDER BY expensive homes and their owners, most expensive first
SELECT TOP 2 P.firstName, P.lastName, H.homeAddress, H.price
FROM Player P
         INNER JOIN (SELECT ownerId, homeAddress, price
                     FROM Home
                     WHERE price > 100000) H ON H.ownerId = P.playerId
ORDER BY H.price DESC

-- g2) subquery in FROM total value of the items each player carries
SELECT P.firstName, P.lastName, T.stockValue
FROM Player P
         INNER JOIN(SELECT I.playerId, SUM(I.quantity * IT.price) AS stockValue
                    FROM INVENTORY I
                             INNER JOIN Item IT ON IT.itemId = I.itemId
                    GROUP BY I.playerId) T
                   ON T.playerId = P.playerId

-- h1) GROUP BY vehicles per brand, most common brand
SELECT TOP 1 V.brand,
             COUNT(*)         AS noVehicles,
             AVG(V.fuelLevel) AS avgFuel
FROM Vehicle V
GROUP BY V.brand
ORDER BY noVehicles DESC

-- h2) GROUP BY + HAVING owners whose homes add up to more than 100000
SELECT P.firstName, P.lastName, COUNT(*) AS noHomes, SUM(H.price) as totalValue
FROM Player P
         INNER JOIN Home H ON H.ownerId = P.playerId
GROUP BY P.playerId, P.firstName, P.lastName
HAVING SUM(H.price) > 100000

-- h3) GROUP BY + HAVING with subquery factions with above-average player money
SELECT F.factionName, COUNT(*) AS noPlayers, AVG(P.cashMoney + P.bankMoney) AS avgMoney
FROM LegalFaction F
         INNER JOIN Player P ON P.factionId = F.factionId
GROUP BY F.factionName
HAVING AVG(P.cashMoney + P.bankMoney) > (SELECT AVG(cashMoney + bankMoney) FROM Player)

-- h4) GROUP BY + HAVING with subquery owners whose vehicles are low on fuel on average
SELECT P.firstName, P.lastName, MIN(V.fuelLevel) as minFuel, MAX(V.fuelLevel) as maxFuel
FROM Player P
         INNER JOIN Vehicle V ON V.ownerId = P.playerId
GROUP BY P.playerId, P.firstName, P.lastName
HAVING AVG(V.fuelLevel) < (SELECT AVG(fuelLevel) FROM Vehicle)

-- i1) ANY vehicles with more fuel than some Dacia
SELECT V.plate, V.brand, V.model, V.fuelLevel
FROM Vehicle V
WHERE V.fuelLevel > ANY (SELECT V2.fuelLevel
                         FROM Vehicle V2
                         WHERE V2.brand = 'Dacia')

-- i1) rewritten with MIN
SELECT V.plate, V.brand, V.model, V.fuelLevel
FROM Vehicle V
WHERE V.fuelLevel > (SELECT MIN(V2.fuelLevel)
                     FROM Vehicle V2
                     where V2.brand = 'Dacia')

-- i2) ALL items that cost more than all Food items
SELECT IT.itemName, IT.itemType, IT.price
FROM Item IT
WHERE IT.price > ALL (SELECT IT2.price
                      FROM Item IT2
                      WHERE IT2.itemType = 'Food')

-- i2) rewritten with max
SELECT IT.itemName, IT.itemType, IT.price
FROM Item IT
WHERE IT.price > (SELECT MAX(IT2.PRICE)
                  FROM Item IT2
                  WHERE IT2.itemType = 'Food')

-- i3) ANY players who carry a Lockpick (itemId 7)
SELECT P.firstName, P.lastName
FROM Player P
WHERE P.playerId = ANY (SELECT I.playerId
                        FROM Inventory I
                        WHERE I.itemId = 7)

-- i3) rewritten with IN
SELECT P.firstName, P.lastName
FROM Player P
WHERE P.playerId IN (SELECT I.playerId
                     FROM Inventory I
                     WHERE I.itemId = 7)

-- i4) <> ALL players who have never been jailed
SELECT P.firstName, P.lastName
FROM Player P
WHERE P.playerId <> ALL (SELECT J.playerId
                         FROM Jail J)

-- i4) rewritten with NOT IN
SELECT P.firstName, P.lastName
FROM Player P
WHERE P.playerId NOT IN (SELECT J.playerId
                         FROM Jail J)

-- i forgot about distinct sorry

-- vehicle brands that exists
SELECT DISTINCT V.brand
FROM Vehicle V

-- item types that players carry
SELECT DISTINCT IT.itemType
FROM Inventory I
         INNER JOIN Item IT ON IT.itemId = I.itemId

-- offenses that were actually used in an arrest
SELECT DISTINCT O.offenseName
FROM JailOffense JO
         INNER JOIN Offense O ON O.offenseId = JO.offenseId

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

