<!-- page 1 -->
LABORATORY 6  ·  WEEK 6  ·  2–6 NOVEMBER 2026

# Work on Assignment A3

Files, logging, relational expressions and a command menu · Gradle + Git + JUnit

- # This week 1 Continue assignment A3 (described in the Laboratory 5 document) in the same project and repository as A2. Work in class and continue at home.

- 2 Commit and push your progress at the end of the lab; every step that compiles should come with its JUnit tests.

- 3 Check `LabAssignmentsSchedule.pdf` regularly for the assignment schedule.

Reminder – deadline for A3: week 7 (9–13 November 2026)

A3 is presented orally to the lab instructor during the laboratory in week 7: you pull the version tagged `A3` , run `./gradlew build` (compilation + all tests, the A2 tests included), run the examples from the menu – among them the file example – open a log file and explain your design and code. This is the last laboratory before the deadline. Use it to finish the implementation and to ask your questions.

## Where you should be by the end of this lab

Use this list to check your progress (the order of section _Suggested order of work_ in the Laboratory 5 document). Each step should end with green tests and a commit.

|Step|Done when|Tests|
|---|---|---|
|1. String type|`StringType`,`StringValue`;`string`variables get the default value`""`|default value;`equals`and`hashCode` of string values|
|2. Relational expressions|`RelOp`,`RelationalExp`with the six operators|each operator, true and false; non- integer operand|
|3. FileTable|`remove`and`toMap`in the ADTs; FileTable in `PrgState`;`PrgState.of(…)`used everywhere|all A2 tests still pass|
|4. File statements|`OpenRFileStmt`,`ReadFileStmt`,`CloseRFileStmt` (rules S8–S10)|each rule and each of its errors, with `@TempDir`|
|5. Log file|`logPrgStateExec`in`IRepository`/`Repository`; `allStep`logs every state|the log contains the four sections in order|
|6. Command menu|`Command`,`ExitCommand`,`RunExampleCommand`, `TextMenu`, new`Main`|– (run with`./gradlew run`)|
|7. Examples|Ex1–Ex5 in the menu;`test.in`next to the program|Ex4 prints 15, 50 (0, 0 for an empty file); Ex5 prints 5|

If you are behind, finish steps 1–5 in class – they hold most of the logic – and ask your questions now. Week 7 is for the presentation, not for finishing the work.

Laboratory 6 · Assignment A3 · page 1

<!-- page 2 -->
## Common problems

|Symptom|Likely cause|
|---|---|
|`openRFile` reports that`test.in` does not exist|the working directory:`./gradlew run`starts in`app/`– set `workingDir = rootDir`in the`run`task (Laboratory 5, section 2.4)|
|`readFile` cannot find a file that was opened|`StringValue`is a class without`equals`/`hashCode`– the FileTable lookup compares references|
|the log file is empty or incomplete|the`PrintWriter`is not closed – use try-with-resources in `logPrgStateExec`|
|the log file contains only the last state|`FileWriter`opened without`true`(append mode)|
|the menu options appear in a random order|`HashMap`instead of`LinkedHashMap`in`TextMenu`|
|a Java exception (e.g.`NumberFormatException`)  reaches the menu|it is not caught inside the statement and turned into a `StatementException`|

## Before you leave the lab

- ☐ `./gradlew build` succeeds and all tests pass – the A2 tests included.

- ☐  Your work is committed with meaningful messages and pushed to the remote repository.

- ☐  You know what is still missing and have a plan to finish it before week 7.

- ☐  You have written down the questions you still have.

Laboratory 6 · Assignment A3 · page 2
