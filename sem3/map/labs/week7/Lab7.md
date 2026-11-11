<!-- page 1 -->
LABORATORY 7  ·  WEEK 7  ·  9–13 NOVEMBER 2026

# Assignment A4: Heap, Garbage Collector and While

Toy-language interpreter, continued · reference types · heap allocation, reading and writing · garbage collection · while loops

- # This week

- 1 Present assignment A3 orally to the lab instructor (tagged `A3` , see the checklist in the Laboratory 5 document).

- 2 Start assignment A4 in the same Gradle project and Git repository. Work in class and continue at home.

- 3 Check `LabAssignmentsSchedule.pdf` regularly for the assignment schedule.

Deadline for A4: week 9 (23–27 November 2026)

A4 is presented orally to the lab instructor during the laboratory : you pull the version tagged `A4` , run `./gradlew build` (compilation + all tests, those of A2 and A3 included), run the heap and while examples from the menu, show in a log file how the garbage collector works and explain your design and code.

## Overview

A4 extends the interpreter from A3. All the A3 code stays; you add five features:

|#|Feature|What you add or change|
|---|---|---|
|1|Reference types and values|`RefType`,`RefValue`|
|2|The heap|`IHeap`,`MyHeap`; the Heap in`PrgState`and in the log file; a new parameter of `IExp.eval`|
|3|Heap statements and expressions|`new(v, exp)`(`NewStmt`),`rH(exp)`(`ReadHeapExp`),`wH(v, exp)` (`WriteHeapStmt`)|
|4|Garbage collector|`GarbageCollector`, called by`Controller.allStep`after every step|
|5|While statement|`WhileStmt`|

### Suggested order of work

Work in small steps. Each step ends with green tests ( `./gradlew test` ) and a commit.

|Step|Done when|Tests|
|---|---|---|
|1. Reference types|`RefType`,`RefValue`; a`Ref`variable gets the default value`(0, type)`|default value;`equals`of nested types such as`Ref(Ref(int))`|
|2. The heap|`IHeap`,`MyHeap`; Heap in`PrgState`,`PrgState.of`, the log file|addresses 1, 2, 3 …; reading a missing address throws|
|3. New signature of eval|`eval(symTable, heap)`in all expressions and all callers|all A2 and A3 tests still pass|
|4. Heap statements|`NewStmt`,`ReadHeapExp`,`WriteHeapStmt`(rules S11, S12, E6)|each rule and each of its errors|
|5. While|`WhileStmt`(rule S13)|a loop that runs 0, 1 and n times; non-boolean condition|

Laboratory 7 · Assignment A4 · page 1

<!-- page 2 -->
|Step|Done when|Tests|
|---|---|---|
|6. Garbage collector|the unsafe version, then the safe one|Ex9 prints`20`with the safe collector|
|7. Examples|Ex6–Ex10 in the menu|the expected Out of section 1.4|

## 1. Language extensions

### 1.1 Syntax

A reference type is recursive : it is built from any type, including another reference type. The grammar gets a new type, a new kind of value, three statements and one expression:

```
grammar – new parts
```

```
Type  ::= int | bool | string | Ref Type        (RefType)
Value ::= Number | true | false | "text"
        | (address, Type)                       (RefValue)
Stmt  ::= …                                     (the statements of A2 and A3)
        | new(Id, Exp)                          (NewStmt)
        | wH(Id, Exp)                           (WriteHeapStmt)
        | while (Exp) Stmt                      (WhileStmt)
Exp   ::= …                                     (the expressions of A2 and A3)
        | rH(Exp)                               (ReadHeapExp)
```

Examples of declarations with reference types:

#### <mark>`reference types`</mark>

```
Ref int x1;                     // a reference to an int
Ref bool x2;
Ref Ref int x3;                 // a reference to a reference to an int
Ref Ref Ref string x4;
Ref Ref Ref Ref bool x5;
```

A reference value is a pair `(address, locationType)` : the address of a heap location (an `int` ) and the type of the value stored there. For example, `(1, int)` has type `Ref int` , and `(10, Ref int)` has type `Ref Ref int` . The address 0 is invalid – it plays the role of `null` .

### 1.2 Program state

The program state gets a fifth structure, the Heap :

|Structure|Content|Notation|
|---|---|---|
|ExeStack|the statements that still have to be executed|`{s1 | s2 | s3}`|
|SymTable|the declared variables and their values|`{v -> (1, int), a -> (2, Ref` `int)}`|
|Out|the printed values|`{20, 25}`|
|FileTable|the open files|`{"test.in" -> reader}`|
|Heap|_new:_the dynamically allocated locations – an address (`int`, from 1) mapped to the value stored there; the heap also knows thenext free address|`{1 -> 20, 2 -> (1, int)}`|

Laboratory 7 · Assignment A4 · page 2

<!-- page 3 -->
### 1.3 Execution rules

All the rules of A2 and A3 stay unchanged. Rule S3 gives a `Ref T` variable the default value `(0, T)` . As before, the controller pops the statement before applying its rule.

|Rule|Top of ExeStack|Effect|Errors|
|---|---|---|---|
|S11|`new(v, exp)`|`val = Eval(exp)`; store`val`at anewaddress`a`of the Heap; update`v -> (a, T)`in SymTable, where `(_, T)`is the old value of`v`|`v`not declared;`v`is not a reference; the type of`val`is not`T`|
|S12|`wH(v, exp)`|`(a, T)`= the value of`v`;`val = Eval(exp)`; update`a` `-> val`in the Heap|`v`not declared;`v`is not a reference;`a`is not in the Heap; the type of`val`is not`T`|
|S13|`while (exp) s`|if`Eval(exp)`is`true`: push`while (exp) s`, then push`s`; if`false`: nothing (the loop ends)|`exp`is not a boolean|
|Rule|Expression|Value|Errors|
|E6|`rH(exp)`|`Eval(exp)`must be a reference`(a, T)`; the value is the content of the Heap at address`a`|`exp`is not a reference;`a`is not in the Heap|

The while rule, in the notation of A2 (the other structures do not change):

|`rule S13 `||
|---|---|
|`ExeStack1 = {while (exp1`|`) Stmt1 | Stmt2 | …}`|
|`==>`||
|`if Eval(exp1) = false:`|`ExeStack2 = {Stmt2 | …}`|
|`if Eval(exp1) = true:`|`ExeStack2 = {Stmt1 | while (exp1) Stmt1 | Stmt2 | …}`|
|`otherwise:`|`error "condition exp1 is not a boolean"`|

### 1.4 New example programs

||Program|At the end of the execution|
|---|---|---|
|Ex6|`Ref int v; new(v, 20); Ref Ref int a; new(a, v);` `print(v); print(a)`|Heap`{1 -> 20, 2 -> (1, int)}`, SymTable `{v -> (1, int), a -> (2, Ref(int))}`, Out `{(1, int), (2, Ref(int))}`|
|Ex7|`Ref int v; new(v, 20); Ref Ref int a; new(a, v);` `print(rH(v)); print(rH(rH(a)) + 5)`|Heap and SymTable as in Ex6, Out`{20, 25}`|
|Ex8|`Ref int v; new(v, 20); print(rH(v)); wH(v, 30);` `print(rH(v) + 5)`|Heap`{1 -> 30}`, SymTable`{v -> (1, int)}`, Out`{20, 35}`|
|Ex9|`Ref int v; new(v, 20); Ref Ref int a; new(a, v);` `new(v, 30); print(rH(rH(a)))`|Out`{20}`– but only with acorrectgarbage collector (section 2.6)|
|Ex10|`int v; v = 4; (while (v > 0) (print(v); v = v -` `1)); print(v)`|Out`{4, 3, 2, 1, 0}`|

## 2. Implementation requirements

The fragments below continue the design of A2 and A3: records for types, values, expressions and statements, interfaces starting with I . Complete the parts marked _TODO_ .

Laboratory 7 · Assignment A4 · page 3

<!-- page 4 -->
### 2.1 Reference types and values

Both are new records – once more, nothing in the existing code has to change. Because `RefType` is a record, `equals` compares the inner types recursively : `Ref(Ref(int))` equals `Ref(Ref(int))` but not `Ref(int)` , with no hand-written `equals` .

```
 model/type/RefType.java, model/value/RefValue.java
```

```
public record RefType(IType inner) implements IType {
    @Override public IValue defaultValue() { return new RefValue(0, inner); } // null
    @Override public String toString() { return "Ref(" + inner + ")"; }
}
```

```
public record RefValue(int address, IType locationType) implements IValue {
    @Override public IType getType() { return new RefType(locationType); }
    @Override public String toString() {
        return "(" + address + ", " + locationType + ")";
    }
}
```

If you write classes instead of records

Override `equals(Object other)` with a pattern: `return other instanceof RefType r && inner.equals(r.inner);` – a plain `other.getInner()` does not compile, because `other` has the static type `Object` . Override `hashCode` as well.

### 2.2 The heap

The heap is a map from addresses to values, but it is not an ordinary dictionary: the heap itself chooses the address of every new value, so that addresses are unique. It gets its own interface and class; inside, it uses a `HashMap` and the next free address.

#### <mark>`model/adt`</mark>

```
public interface IHeap {
    int allocate(IValue value);                     // stores value at a new address
    IValue get(int address) throws ADTException;
    void update(int address, IValue value) throws ADTException;
    boolean isDefined(int address);
    Map<Integer, IValue> getContent();              // a read-only copy
    void setContent(Map<Integer, IValue> content);  // used by the garbage collector
}
```

```
public class MyHeap implements IHeap {
    private Map<Integer, IValue> heap = new HashMap<>();
    private int nextFree = 1;                       // address 0 means null
    @Override
    public int allocate(IValue value) {
        int address = nextFree++;
        heap.put(address, value);
        return address;
    }
    @Override public void setContent(Map<Integer, IValue> content) {
        heap = new HashMap<>(content);
    }
    // TODO: get and update (a missing address -> ADTException), isDefined,
    //       getContent (Map.copyOf(heap)), toString
}
```

Add the Heap to `PrgState` – a field, a constructor parameter, a getter – and to the factory method. Since A3 creates every state with `PrgState.of(…)` , the examples and the tests do not change:

Laboratory 7 · Assignment A4 · page 4

<!-- page 5 -->
#### <mark>`model/PrgState.java`</mark>

```
public static PrgState of(IStmt program) {
    return new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(),
                        new MyDictionary<>(), new MyHeap(), program);
}
```

The log file gets a fifth section, `Heap:` , after `FileTable:` , with one `address --> value` line per location. Sort the addresses, so that two logs of the same program are identical: `new TreeMap<>(heap.getContent()).forEach(…)` .

### 2.3 A new parameter for eval

`rH` reads the heap, so an expression needs the heap to be evaluated. Change the interface:

```
 model/exp/IExp.java
```

```
public interface IExp {
    IValue eval(IDictionary<String, IValue> symTable, IHeap heap) throws MyException;
}
```

Let the compiler guide the refactoring

Change `IExp` first and run `./gradlew build` : the compiler lists every class that implements `eval` and every place that calls it. Fix them one by one – expressions pass the heap on to their operands, statements call `exp.eval(state.getSymTable(), state.getHeap())` . When the build is green again, all A2 and A3 tests must still pass. Commit this step alone , before adding anything new.

### 2.4 Heap statements and expressions

`new` is given in full; write `rH` and `wH` in the same style, following rules E6 and S12.

#### <mark>`model/stmt/NewStmt.java`</mark>

```
public record NewStmt(String varName, IExp exp) implements IStmt {               // S11
    @Override
    public PrgState execute(PrgState state) throws MyException {
        var symTable = state.getSymTable();
        if (!symTable.isDefined(varName))
            throw new StatementException("new: " + varName + " is not declared");
        if (!(symTable.lookup(varName) instanceof RefValue ref))
            throw new StatementException("new: " + varName + " is not a reference");
        IValue value = exp.eval(symTable, state.getHeap());
        if (!value.getType().equals(ref.locationType()))
            throw new StatementException("new: " + exp + " has type " + value.getType()
                    + ", expected " + ref.locationType());
        int address = state.getHeap().allocate(value);
        symTable.update(varName, new RefValue(address, ref.locationType()));
        return state;
    }
    @Override public String toString() { return "new(" + varName + ", " + exp + ")"; }
}
// TODO: ReadHeapExp(IExp exp)                       – E6, toString "rH(" + exp + ")"
//         the value of exp must be a RefValue; its address must be in the heap
// TODO: WriteHeapStmt(String varName, IExp exp)     – S12, toString "wH(…, …)"
//         check the variable, the address and the type, then heap.update(…)
```

### 2.5 The while statement

A loop needs no Java loop: `WhileStmt` puts itself back on the stack, under its body, as long as the condition is true. Implement it following rule S13.

Laboratory 7 · Assignment A4 · page 5

<!-- page 6 -->
#### <mark>`model/stmt/WhileStmt.java`</mark>

```
public record WhileStmt(IExp cond, IStmt body) implements IStmt {                // S13
    @Override
    public PrgState execute(PrgState state) throws MyException {
        // TODO: evaluate cond; not a BoolValue -> StatementException
        //       true: push this, then push body; false: do nothing
    }
    @Override public String toString() { return "(while (" + cond + ") " + body + ")"; }
}
```

### 2.6 The garbage collector

A heap location is garbage when the program can no longer reach it. After every step, the controller removes the garbage from the heap. We start with an unsafe collector, which keeps only the addresses that occur directly in the SymTable. Put the methods in a class `controller.GarbageCollector` ; they use the streams from Lecture 5.

#### <mark>`controller/GarbageCollector.java`</mark>

```
public final class GarbageCollector {
    private GarbageCollector() {}
    /** The addresses that occur in the RefValues of the SymTable. */
    public static Set<Integer> getAddrFromSymTable(Collection<IValue> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> ((RefValue) v).address())
                .collect(Collectors.toSet());
    }
    /** UNSAFE: keeps only the heap entries referred to directly from the SymTable. */
    public static Map<Integer, IValue> unsafeGarbageCollector(Set<Integer> symTableAddr,
                                                              Map<Integer, IValue> heap) {
        return heap.entrySet().stream()
                .filter(e -> symTableAddr.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }
}
```

The controller calls the collector after each step and logs the state before and after the collection:

#### <mark>`controller/Controller.java`</mark>

```
public void allStep() throws MyException {
    PrgState prg = repo.getCrtPrg();
    repo.logPrgStateExec();
    while (!prg.getExeStack().isEmpty()) {
        oneStep(prg);
        repo.logPrgStateExec();
        prg.getHeap().setContent(unsafeGarbageCollector(
                getAddrFromSymTable(prg.getSymTable().toMap().values()),
                prg.getHeap().getContent()));
        repo.logPrgStateExec();
        display(prg);
    }
}
```

Run Ex9 with this collector. After `new(v, 30)` , the location 1 is no longer referred to from the SymTable – but it is still reachable through location 2, which `a` refers to. The unsafe collector removes it anyway, and the last `rH` fails. The log shows the moment:

Laboratory 7 · Assignment A4 · page 6

<!-- page 7 -->
#### <mark>`log9.txt – before and after the unsafe collection`</mark>

```
ExeStack:                         ExeStack:
print(rH(rH(a)))                  print(rH(rH(a)))
SymTable:                         SymTable:
a --> (2, Ref(int))               a --> (2, Ref(int))
v --> (3, int)                    v --> (3, int)
Out:                              Out:
FileTable:                        FileTable:
Heap:                             Heap:
1 --> 20                          2 --> (1, int)
2 --> (1, int)                    3 --> 30
3 --> 30
```

```
 the menu, at the next step
```

```
Error: rH: address 1 is not in the heap
```

TODO: a safe garbage collector

Write `safeGarbageCollector` , which also keeps the locations reachable through the heap , and use it in `allStep` instead of the unsafe one. Ex9 must then print `20` .

Hint: start from the addresses of the SymTable; whenever a kept location contains a `RefValue` , keep its address too; repeat until no new address is found. Write it as a separate method `Set<Integer> reachableAddresses(Set<Integer> roots, Map<Integer, IValue> heap)` , so that it can be tested on its own.

### 2.7 Examples and the menu

Add Ex6–Ex10 to `view.Examples` and to the list of programs in `Main` – the command menu of A3 needs no other change. For example, Ex10 as an object tree:

```
 view/Examples.java
```

```
// int v; v = 4; (while (v > 0) (print(v); v = v - 1)); print(v)
public static final IStmt EX10 =
    new CompStmt(new VarDeclStmt("v", new IntType()),
    new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
    new CompStmt(new WhileStmt(
            new RelationalExp(RelOp.GT, new VarExp("v"), new ValueExp(new IntValue(0))),
            new CompStmt(new PrintStmt(new VarExp("v")),
                         new AssignStmt("v", new ArithExp(ArithOp.SUB,
                                 new VarExp("v"), new ValueExp(new IntValue(1)))))),
                 new PrintStmt(new VarExp("v")))));
```

The new errors of rules S11–S13 are `StatementException` s, those of rule E6 `ExpressionException` s, and a missing heap address inside `MyHeap` is an `ADTException` .

## 3. Testing with JUnit

All the A2 and A3 tests must still pass after the change of `eval` (section 2.3). Add tests for every new feature.

### 3.1 Minimum tests for A4

|Area|Test at least|
|---|---|
|Reference types|a`Ref T`variable gets`(0, T)`;`Ref(Ref(int))`equals`Ref(Ref(int))`and differs from `Ref(int)`|
|Heap|`allocate`returns 1, 2, 3 …;`get`and`update`of a missing address throw|

Laboratory 7 · Assignment A4 · page 7

<!-- page 8 -->
|Area|Test at least|
|---|---|
|new|allocates and updates the variable; variable not declared, not a reference, value of the wrong type throw|
|rH|reads the value; non-reference expression and address not in the heap throw|
|wH|changes the heap location; variable not a reference, address not in the heap, value of the wrong type throw|
|while|a loop that runs 0, 1 and several times; non-boolean condition throws|
|Garbage collector|unreachable locations are removed; a location reachable only through the heap is kept|
|Controller|Ex6–Ex10 give the results of section 1.4|

### 3.2 Example tests

```
 src/test/java/interpreter/model/stmt/HeapStmtTest.java
```

```
class HeapStmtTest {
    private PrgState state;
    @BeforeEach
    void setUp() throws MyException {
        state = PrgState.of(new NopStmt());
        new VarDeclStmt("v", new RefType(new IntType())).execute(state);   // Ref int v
    }
    @Test
    void newAllocatesAtAddressOneAndUpdatesTheVariable() throws MyException {
        new NewStmt("v", new ValueExp(new IntValue(20))).execute(state);
        assertEquals(new RefValue(1, new IntType()), state.getSymTable().lookup("v"));
        assertEquals(new IntValue(20), state.getHeap().get(1));
    }
    @Test
    void newWithAValueOfTheWrongTypeThrows() {
        var exp = new ValueExp(new BoolValue(true));
        assertThrows(StatementException.class, () -> new NewStmt("v", exp).execute(state));
    }
    @Test
    void whileWithANonBooleanConditionThrows() {
        var loop = new WhileStmt(new ValueExp(new IntValue(1)), new NopStmt());
        assertThrows(StatementException.class, () -> loop.execute(state));
    }
}
```

The garbage collector works on plain Java maps, so it can be tested without running a program:

#### <mark>`src/test/java/interpreter/controller/GarbageCollectorTest.java`</mark>

```
class GarbageCollectorTest {
    // the state of Ex9 after new(v, 30): v -> (3, int), a -> (2, Ref(int))
    private final List<IValue> symTable = List.of(
            new RefValue(3, new IntType()), new RefValue(2, new RefType(new IntType())));
    private final Map<Integer, IValue> heap = Map.of(
            1, new IntValue(20), 2, new RefValue(1, new IntType()),
            3, new IntValue(30), 4, new IntValue(7));
    @Test
    void keepsTheLocationsReachableThroughTheHeap() {
        Set<Integer> roots = GarbageCollector.getAddrFromSymTable(symTable);
        Map<Integer, IValue> kept = GarbageCollector.safeGarbageCollector(roots, heap);
        assertEquals(Set.of(1, 2, 3), kept.keySet());          // 4 is garbage, 1 is not
    }
}
```

Laboratory 7 · Assignment A4 · page 8

<!-- page 9 -->
## 4. Submission checklist (A4)

- ☐  A4 is implemented in the A3 project and repository; `./gradlew build` succeeds on a fresh clone.

- ☐ `RefType` , `RefValue` , the Heap, `new` , `rH` , `wH` and `while` follow sections 1 and 2.

- ☐ `eval` takes the heap; all the A2 and A3 tests still pass.

- ☐  Every error of rules S11–S13 and E6 produces an interpreter exception with a clear message.

- ☐  The log file contains the Heap; the garbage collector runs after every step and is safe : Ex9 prints `20` .

- ☐  Examples Ex1–Ex10 run from the menu with `./gradlew run` .

- ☐  The tests of section 3.1 pass.

- ☐  The Git history shows incremental work with meaningful messages – the change of `eval` in a commit of its own.

- ☐  The submitted version is tagged `A4` ( `git tag A4` , `git push --tags` ) before the deadline.

- ☐ The project is presented orally to the lab instructor at the laboratory: you run the build, the tests and the examples, show a log file before and after a garbage collection and explain the design and any part of your code. Code you cannot explain is not accepted.

Deadline: week 9 (23–27 November 2026).

Laboratory 7 · Assignment A4 · page 9
