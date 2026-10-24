<!-- page 1 -->
SEMINAR 4  ·  WEEK 4  ·  19–23 OCTOBER 2026

# Discussion of Assignment A2

Toy-language interpreter (Laboratory 3 document) – completing the discussion of the implementation

Agenda

|A|Discussion of the lab assignment A2: complete the discussion of the implementation, topic by topic.|
|---|---|
|B|Exerciseson the execution rules and on testing.|

## A. Discussion of the A2 implementation

Bring your current code. For each topic, be ready to show where it is implemented in your project and to answer the guiding questions.

|Topic|Guiding questions|
|---|---|
|1. Architecture (MVC)|Which packages does your project have? In which direction do the dependencies go (view → controller → repository → model)? Why does the controller hold an`IRepository`and not a`Repository`?|
|2. Statements|Why does`IStmt.execute`receive and return a`PrgState`? How does`CompStmt` decompose a program on the stack? Where is each error of rules S1–S6 detected?|
|3. Types and values|Why is it useful that an`IType`knows its default value? How do you compare two types – and why do records make this easy?|
|4. Expressions|How are the operand types checked in`ArithExp`and`LogicExp`? Why use an`enum`for operators instead of`int`codes or characters? Do expressions ever change the program state?|
|5. Generic ADTs|Why define our own interfaces`IStack`,`IDictionary`,`IList`instead of using`java.util` types directly? Which collection does each class wrap, and why?|
|6. Program state and controller|What exactly does`oneStep`do? When does`allStep`stop? How is the display flag used?|
|7. Exceptions|How is your exception hierarchy organized? Checked or unchecked – what did you choose and why? Where are the exceptions finally caught, so that the menu does not crash?|
|8. Tests, Gradle, Git|Which test classes do you have, and which rule or error does each test cover? What does `./gradlew build`do? How many commits do you have so far?|

## B. Exercises

### B1. Execution trace

Trace Example 3 step by step, as in section 3.3 of the Laboratory 3 document: for each step, write the rule applied and the contents of ExeStack, SymTable and Out.

#### <mark>`Example 3`</mark>

```
bool a; int v; a = true; (if a then v = 2 else v = 3); print(v)
```

Seminar 4 · Assignment A2 · page 1

<!-- page 2 -->
### B2. Errors

For each program, say which rule fails, which exception your interpreter throws and with which message. Then write the JUnit test that checks this behaviour.

||Prog|ram||
|---|---|---|---|
|a)|`int`|`x;`|`x = 10 / (2 - 2); print(x)`|
|b)|`int`|`x;`|`bool x`|
|c)|`int`|`x;`|`x = true`|
|d)|`int`|`x;`|`if x then print(1) else print(0)`|
|e)|`y =`|`3;`|`print(y)`|
|f)|`bool`|`b;`|`b = 1 and true`|

### B3. Programs as Java objects

Write the Java object tree (as in section 4.9 of the Laboratory 3 document) for the program below, and predict its output:

```
program
int a; int b; bool c; a = 5; b = a * 2 - 3; c = true or false; if c then print(b) else print(a)
```

Seminar 4 · Assignment A2 · page 2
