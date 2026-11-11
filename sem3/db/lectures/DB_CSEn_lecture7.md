<!-- page 1 -->
# Databases

Lecture 7

Relational Algebra (II)

Sabina S. CS

<!-- page 2 -->
#### • the _renaming_ operator

𝜌(R′(A1 →A1′, A2 →A2′, A3 →A3′), E)

- E - relational algebra expression

- the result, relation R′ , has the same tuples as the result of E • attributes A1 , A2 , and A3 are renamed to A1′ , A2′ , and A3′ , respectively

Sabina S. CS

<!-- page 3 -->
#### _<u>An Independent Subset of Operators</u>_

- independent set of operators M:

   - eliminating any operator _op_ from M: there will be a relation that can be obtained using M's operators, but cannot be obtained with the operators in M-{ _op_ }

- for the previously described query language, with operators: { 𝜎 , 𝜋 , × , ∪ , −, ∩ , ⨂ , ∗ , ⋉ , ⋊ , ⋈ , ⊳ , ⊲ , ÷}

an independent set of operators is { 𝜎 , 𝜋 , × , ∪ , −}

- the other operators are obtained as follows (some expressions have already been introduced):

   - 𝑅1 ∩𝑅2 = 𝑅1 −(𝑅1−𝑅2)

   - 𝑅1⨂C𝑅2 = 𝜎𝐶(𝑅1 × 𝑅2)

Sabina S. CS

<!-- page 4 -->
- the other operators are obtained as follows (some expressions have already been introduced):

   - 𝑅1[𝛼] , 𝑅2[𝛽] , 𝛼∩𝛽= 𝐴1, 𝐴2, … , 𝐴𝑚 , then: 𝑅1 ∗𝑅2 = 𝜋𝛼⋃𝛽(𝑅1⨂𝑅1.𝐴1=𝑅2.𝐴1 𝐴𝑁𝐷… 𝐴𝑁𝐷𝑅1.𝐴𝑚=𝑅2.𝐴𝑚𝑅2)

   - 𝑅1[𝛼] , 𝑅2[𝛽] , 𝑅3 𝛽= {(𝑛𝑢𝑙𝑙, … , 𝑛𝑢𝑙𝑙)} , 𝑅4 𝛼= {(𝑛𝑢𝑙𝑙, … , 𝑛𝑢𝑙𝑙)} 𝑅1 ⋉C 𝑅2 = (𝑅1⨂c𝑅2) ∪(𝑅1 −𝜋α(𝑅1⨂c𝑅2)) × 𝑅3 𝑅1 ⋊C 𝑅2 = (𝑅1⨂c𝑅2) ∪𝑅4 × (𝑅2 −𝜋β(𝑅1⨂c𝑅2)) 𝑅1 ⋈C 𝑅2 = (𝑅1 ⋉C 𝑅2) ∪(𝑅1 ⋊C 𝑅2)

• 𝑅1[𝛼] , 𝑅2[𝛽] 𝑅1⊳𝑅2 = 𝜋𝛼(𝑅1 ∗𝑅2) 𝑅1⊲𝑅2 = 𝜋𝛽(𝑅1 ∗𝑅2)

Sabina S. CS

<!-- page 5 -->
- the other operators are obtained as follows (some expressions have already been introduced):

   - if 𝑅1[𝛼] , 𝑅2[𝛽] , 𝛽⊂𝛼 , then 𝑟∈𝑅1 ÷ 𝑅2 if ∀𝑟2 ∈𝑅2, ∃𝑟1 ∈𝑅1 such that: 𝜋𝛼−𝛽 𝑟1 = 𝑟 and 𝜋𝛽 𝑟1 = 𝑟2 𝛽

   - R1

   - => 𝑟 is in 𝜋𝛼−𝛽 𝑅1 , but not all the elements in 𝜋𝛼−𝛽 𝑅1 are in the result r r2 r1 𝛽

   - • (𝜋𝛼−𝛽(𝑅1)) × 𝑅2 contains all the elements with one part in 𝜋𝛼−𝛽 𝑅1 and the second part in 𝑅2

r1 𝛽 R2 r2

- to obtain values that are disqualified, 𝑅1 is subtracted from the obtained relation, and the result is projected on 𝛼−𝛽

r2

- the final expression:

- 𝑅1 ÷ 𝑅2 = 𝜋𝛼−𝛽 𝑅1 −𝜋𝛼−𝛽((𝜋𝛼−𝛽(𝑅1)) × 𝑅2 −𝑅1)

𝛼

Sabina S. CS

<!-- page 6 -->
- the next examples use the statements below:

- assignment

R list ≔expression

      - the expression's result (a relation) is assigned to a variable (R[list]), specifying the name of the relation [and the names of its columns]

- eliminating duplicates from a relation

   - δ R

- sorting records in a relation

   - S{list} R

- grouping

   - R

   - γ list1 group by list2

      - R 's records are grouped by the columns in _list2_

      - _list1_ (that can contain aggregate functions) is evaluated for each group of records

Sabina S. CS

<!-- page 7 -->
```
students[id, name, sgroup, gpa, dob]
groups [id, year, program]
```

`schedule [day, starthour, endhour, activtype, room, sgroup, facultym_id] faculty_members [id, name]` 1. The names of students in a given group: 𝑅≔𝜋 𝑠𝑡𝑢𝑑𝑒𝑛𝑡𝑠 𝑛𝑎𝑚𝑒 𝜎𝑠𝑔𝑟𝑜𝑢𝑝=′222′

```
SELECTname
FROMstudents
WHEREsgroup='222'
```

Sabina S. CS

<!-- page 8 -->
#### 2. The students in a given program (alphabetical list, by groups):

𝐺≔𝜋 𝑖𝑑 𝜎𝑝𝑟𝑜𝑔𝑟𝑎𝑚=′𝐼𝐺′ 𝑔𝑟𝑜𝑢𝑝𝑠 𝑅≔𝑆 𝑠𝑡𝑢𝑑𝑒𝑛𝑡𝑠 𝑠𝑔𝑟𝑜𝑢𝑝,𝑛𝑎𝑚𝑒 𝜎𝑠𝑔𝑟𝑜𝑢𝑝𝑖𝑠𝑖𝑛𝐺

```
SELECT *
FROM students
WHERE sgroupIN
(SELECT id
FROM groups
WHERE program='IG')
ORDER BY sgroup, name
```

```
students[id, name, sgroup, gpa, dob]
groups [id, year, program]
```

```
schedule [day, starthour, endhour, activtype, room,
sgroup, facultym_id]
faculty_members[id, name]
```

Sabina S. CS

<!-- page 9 -->
3. The number of students in every group of a given program: 𝑆𝑇≔𝜎 𝑠𝑡𝑢𝑑𝑒𝑛𝑡𝑠 𝜋 𝑠𝑔𝑟𝑜𝑢𝑝𝑖𝑠𝑖𝑛 𝑖𝑑 𝑔𝑟𝑜𝑢𝑝𝑠 𝜎𝑝𝑟𝑜𝑔𝑟𝑎𝑚=′𝐼𝐺′ 𝑆𝑇 𝑁𝑅≔𝛾 ∗ 𝑠𝑔𝑟𝑜𝑢𝑝, 𝑐𝑜𝑢𝑛𝑡 𝑔𝑟𝑜𝑢𝑝𝑏𝑦 𝑠𝑔𝑟𝑜𝑢𝑝

```
SELECT sgroup,COUNT(*)
FROM(SELECT *
```

```
students[id, name, sgroup, gpa, dob]
FROM students
groups [id, year, program]
WHERE sgroupIN
schedule [day, starthour, endhour, activtype, room,
(SELECTid
sgroup, facultym_id]
FROMgroupsfaculty_members[id, name]
WHEREprogram='IG')
) t
```

```
GROUP BYsgroup
```

Sabina S. CS

<!-- page 10 -->
#### 4. A student's schedule (the student is given by name):

𝜋 𝑠𝑡𝑢𝑑𝑒𝑛𝑡𝑠 𝑇≔𝜎𝑠𝑔𝑟𝑜𝑢𝑝𝑖𝑠𝑖𝑛 𝑠𝑔𝑟𝑜𝑢𝑝 𝜎𝑛𝑎𝑚𝑒=′𝐼𝑜𝑛𝑒𝑠𝑐𝑢𝑀. 𝑅𝑎𝑧𝑣𝑎𝑛′

(𝑠𝑐ℎ𝑒𝑑𝑢𝑙𝑒)

5. The number of hours per week for every group: 𝐹 𝑠𝑐ℎ𝑒𝑑𝑢𝑙𝑒 𝑛𝑜, 𝑠𝑔𝑟𝑜𝑢𝑝≔𝜋 𝑒𝑛𝑑ℎ𝑜𝑢𝑟−𝑠𝑡𝑎𝑟𝑡ℎ𝑜𝑢𝑟,𝑠𝑔𝑟𝑜𝑢𝑝 𝑁𝑜𝐻𝑜𝑢𝑟𝑠 𝐹 𝑠𝑔𝑟𝑜𝑢𝑝, 𝑛𝑜ℎ𝑜𝑢𝑟𝑠≔𝛾 𝑛𝑜 𝑠𝑔𝑟𝑜𝑢𝑝,𝑠𝑢𝑚 𝑔𝑟𝑜𝑢𝑝𝑏𝑦 𝑠𝑔𝑟𝑜𝑢𝑝

```
students[id, name, sgroup, gpa, dob]
```

```
groups [id, year, program]
```

```
schedule [day, starthour, endhour, activtype, room, sgroup, facultym_id]
faculty_members[id, name]
```

Sabina S. CS

<!-- page 11 -->
##### 6. The faculty members (their names) who teach a given student:

𝐴≔(𝜎𝑛𝑎𝑚𝑒=′𝐼𝑜𝑛𝑒𝑠𝑐𝑢𝑀. 𝑅𝑎𝑧𝑣𝑎𝑛′(𝑠𝑡𝑢𝑑𝑒𝑛𝑡𝑠))⨂𝑠𝑡𝑢𝑑𝑒𝑛𝑡𝑠.𝑠𝑔𝑟𝑜𝑢𝑝=𝑠𝑐ℎ𝑒𝑑𝑢𝑙𝑒.𝑠𝑔𝑟𝑜𝑢𝑝𝑠𝑐ℎ𝑒𝑑𝑢𝑙𝑒 𝐵≔𝜋 𝑓𝑎𝑐𝑢𝑙𝑡𝑦𝑚_𝑖𝑑(𝐴) 𝐶≔𝑓𝑎𝑐𝑢𝑙𝑡𝑦_𝑚𝑒𝑚𝑏𝑒𝑟𝑠⨂𝑓𝑎𝑐𝑢𝑙𝑡𝑦_𝑚𝑒𝑚𝑏𝑒𝑟𝑠.𝑖𝑑=𝐵.𝑓𝑎𝑐𝑢𝑙𝑡𝑦𝑚_𝑖𝑑𝐵 𝐷≔𝜋 𝐶 𝑛𝑎𝑚𝑒

```
students[id, name, sgroup, gpa, dob]
```

```
groups [id, year, program]
```

```
schedule [day, starthour, endhour, activtype, room, sgroup, facultym_id]
faculty_members[id, name]
```

Sabina S. CS

<!-- page 12 -->
7. The faculty members with no teaching assignments (i.e., not on the schedule): 𝐶≔𝜋 𝑛𝑎𝑚𝑒(𝑓𝑎𝑐𝑢𝑙𝑡𝑦_𝑚𝑒𝑚𝑏𝑒𝑟𝑠) −

𝜋 𝑛𝑎𝑚𝑒(𝑠𝑐ℎ𝑒𝑑𝑢𝑙𝑒⨂ 𝑠𝑐ℎ𝑒𝑑𝑢𝑙𝑒.𝑓𝑎𝑐𝑢𝑙𝑡𝑦𝑚_𝑖𝑑=𝑓𝑎𝑐𝑢𝑙𝑡𝑦_𝑚𝑒𝑚𝑏𝑒𝑟𝑠.𝑖𝑑𝑓𝑎𝑐𝑢𝑙𝑡𝑦_𝑚𝑒𝑚𝑏𝑒𝑟𝑠)

* Is there a problem if two different faculty members have the same name?

```
students[id, name, sgroup, gpa, dob]
```

```
groups [id, year, program]
```

```
schedule [day, starthour, endhour, activtype, room, sgroup, facultym_id]
faculty_members[id, name]
```

Sabina S. CS

<!-- page 13 -->
8. Students with school activities on every day of the week (all days with school activities considered):

𝐴≔𝛿 𝜋 𝑠𝑐ℎ𝑒𝑑𝑢𝑙𝑒 𝑑𝑎𝑦

𝐵≔𝑠𝑡𝑢𝑑𝑒𝑛𝑡𝑠⨂𝑠𝑡𝑢𝑑𝑒𝑛𝑡𝑠.𝑠𝑔𝑟𝑜𝑢𝑝=𝑠𝑐ℎ𝑒𝑑𝑢𝑙𝑒.𝑠𝑔𝑟𝑜𝑢𝑝𝑠𝑐ℎ𝑒𝑑𝑢𝑙𝑒 𝐶≔𝛿 𝜋 𝑛𝑎𝑚𝑒,𝑑𝑎𝑦(𝐵) 𝐷≔𝐶÷ 𝐴

- Is there a problem if two different students have the same name?

```
students[id, name, sgroup, gpa, dob]
```

```
groups [id, year, program]
```

```
schedule [day, starthour, endhour, activtype, room, sgroup, facultym_id]
```

```
faculty_members[id, name]
```

Sabina S. CS

<!-- page 14 -->
#### Milestone - review

- Databases Fundamentals

- • The Relational Model

- • SQL

- Functional Dependencies. Normal Forms

- • Relational Algebra

Sabina S. CS

<!-- page 15 -->
### See lecture problem (solved at the board)

- Create a database for a system that manages several funding portals, which bring together investors and entrepreneurs seeking funding for their startups. The entities of interest to the problem domain are: Funding Portals, Investors, Entrepreneurs, Startups, and Investments. A funding portal has a name and a website URL. An investor can offer funding through several portals, has a first name, last name, and date of birth. An entrepreneur has a first name, last name, and a startup success probability score; (s)he can own several startups. A startup has a name and description; it belongs to an entrepreneur. An investment is made by an investor for a startup through one of the funding portals the investor is registered on; it has a value (the invested amount of money) and a date. An investor can finance the same startup multiple times (through the same portal or through different portals).

Sabina S. CS

<!-- page 16 -->
## References

- [Ta13] ȚÂMBULEA, L., Curs Baze de date, Facultatea de Matematică și Informatică, UBB, 2013-2014

- [Ra00] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems (2nd Edition), McGraw-Hill, 2000

- [Da03] DATE, C.J., An Introduction to Database Systems (8th Edition), AddisonWesley, 2003

- [Ga08] GARCIA-MOLINA, H., ULLMAN, J., WIDOM, J., Database Systems: The Complete Book, Prentice Hall Press, 2008

- [Ra07] RAMAKRISHNAN, R., GEHRKE, J., Database Management Systems, McGraw-Hill, 2007, <u>http://pages.cs.wisc.edu/~dbbook/openAccess/thirdEdition/slides/slides3ed. html</u>

- [Ul11] ULLMAN, J., WIDOM, J., A First Course in Database Systems, <u>http://infolab.stanford.edu/~ullman/fcdb.html</u>

Sabina S. CS
