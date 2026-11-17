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
