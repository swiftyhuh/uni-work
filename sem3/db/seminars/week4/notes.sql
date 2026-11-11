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
