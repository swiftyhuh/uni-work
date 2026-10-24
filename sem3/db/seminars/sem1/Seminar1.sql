CREATE TABLE Student(
    sid TINYINT PRIMARY KEY IDENTITY(1,1), /* IDENTITY is a function that works like
                                              auto increment, 1st argument is the
                                              starting point, second one is the steps */
    sname VARCHAR(100) NOT NULL,
    dob DATE,
    second_faculty BIT DEFAULT 0, /* default false */
    email VARCHAR(100) UNIQUE
)

ALTER TABLE Student
add hobbies VARCHAR(200)

ALTER TABLE Student
ALTER COLUMN sname varchar(200)

ALTER TABLE Student
ALTER COLUMN sname VARCHAR(200) NOT NULL

ALTER TABLE Student
DROP COLUMN dob

CREATE TABLE Course(
    /*cid TINYINT PRIMARY KEY IDENTITY (1,1), or we can use (last line) */
    cid TINYINT IDENTITY (1,1),
    cname VARCHAR(100),
    no_credits TINYINT CHECK(no_credits>0),
    professor VARCHAR(100),
    exam_date DATETIME DEFAULT GETDATE(), /* get current date function */
    CONSTRAINT pk_course PRIMARY KEY (cid)
)

CREATE TABLE Attendance
(
    aid    TINYINT PRIMARY KEY IDENTITY (1,1),
    sid    TINYINT FOREIGN KEY REFERENCES Student (sid),
    /* a different way to define foreign keys */
    cid    TINYINT,
    room   VARCHAR(100),
    atime  TIME, /* we need to have a different name for the field
                   we can write [time] instead */
    [date] DATE,
    grade  DECIMAL(4, 2) /* no. of digits , no. after floating point */
    --constraint fk_course FOREIGN KEY (cid)
    --REFERENCES Course(cid) (its optional to name the key)
    FOREIGN KEY (cid)
    REFERENCES Course (cid)
    ON DELETE cascade on update set default
)

ALTER TABLE Attendance
add default 0.0 FOR grade

ALTER TABLE Attendance
add constraint uq_attendance UNIQUE(sid,cid,room,date)

ALTER TABLE Attendance
drop CONSTRAINT uq_attendance

/* if we delete a student that have n attendances, we need to use
   ON DELETE to don't have any errors
   ON DELETE have many options
   CASCADE - will delete everything related to that student
   NO ACTION (def) nothing else is deleted (error)
   SET NULL associated attendance sid is set to null
   SET DEFAULT - associated attendance sid is set to default/null
   
   Same options available for update
 */

DROP TABLE Attendance

DROP TABLE Course

DROP TABLE Student

