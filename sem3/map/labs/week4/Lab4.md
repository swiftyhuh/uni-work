<!-- page 1 -->
LABORATORY 4  ·  WEEK 4  ·  19–23 OCTOBER 2026

# Work on Assignment A2

Toy-language interpreter · Gradle + Git + JUnit

|#|This week|
|---|---|
|1|Continue assignment A2(the toy-language interpreter, described in the Laboratory 3 document). Work in class and continue at home.|
|2|Commit and pushyour progress at the end of the lab; every step that compiles should come with its JUnit tests.|
|3|Check`LabAssignmentsSchedule.pdf`regularly for the assignment schedule.|

Deadline for A2: week 5 (26–30 October 2026)

A2 is presented orally to the lab instructor during the laboratory in week 5: you run `./gradlew build` (compilation + all tests), run the three example programs and explain your design and code.

## Where you should be by the end of this lab

Use this list to check your progress. Each step should end with green tests and a commit.

|Step|Done when|Tests|
|---|---|---|
|1. Project set-up|Gradle project generated, Git repository with a remote, first commit pushed|`./gradlew test`runs|
|2. ADTs|`IStack`/`MyStack`,`IDictionary`/`MyDictionary`, `IList`/`MyList`wrap`java.util`collections|LIFO order, empty pop, missing key, index out of bounds|
|3. Types and values|`IType`,`IntType`,`BoolType`;`IValue`,`IntValue`, `BoolValue`|default values;`equals`of types|
|4. Expressions|`IExp`,`ValueExp`,`VarExp`,`ArithExp`,`LogicExp`|every operator; division by zero; wrong operand types; undefined variable|
|5. Statements|`IStmt`and the six statements, rules S1–S6|each rule and each of its errors|
|6. State, repository, controller|`PrgState`,`IRepository`/`Repository`,`Controller` with`oneStep`/`allStep`|the three examples give the expected Out|
|7. View|text menu: select an example program, run it, display the states|– (run with`./gradlew run`)|

If you are behind, finish steps 1–4 in class and ask your questions now – week 5 is for the presentation, not for starting the work.

## Before you leave the lab

- ☐ `./gradlew build` succeeds and all tests pass.

- ☐  Your work is committed with meaningful messages and pushed to the remote repository.

- ☐  You have written down the questions you still have, for the seminar or the next lab.

Laboratory 4 · Assignment A2 · page 1
