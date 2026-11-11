<!-- page 1 -->
SEMINAR 6  ·  WEEK 6  ·  2–6 NOVEMBER 2026

# A3 Review and Generics with Wildcards

Assignment A3 (Laboratory 5 document) · generic methods, bounds and wildcards (Lecture 4)

Agenda

A Discussion of the lab assignment A3 – in the View: how can the same example be executed many times? B Generics exercises : find the most specific signatures – wildcards, bounds and generic methods – for four programs.

## A. Discussion of the A3 implementation

Bring your A3 code. Be ready to show where each topic is implemented and to answer the questions.

|Topic|Guiding questions|
|---|---|
|1. File statements|Where is each error of rules S8–S10 detected? Which Java exceptions are caught, and where are they turned into`StatementException`s?|
|2. FileTable and strings|What is the type of your FileTable? What would go wrong if`StringValue`had no `hashCode`?|
|3. Log file|Show a log file. Why is it opened in append mode, and why is it opened and closed at every step?|
|4. Relational expressions|One class or six? How is the operand type checked? What does`toString`produce?|
|5. Tests|Which tests did you write for the file statements? Do they depend on files in the project folder?|

### A1. Running the same example more than once

In the A3 menu an example can be executed only once: `RunExampleCommand` remembers that it has run. We want to remove this restriction, so that the user can select the same example again and again. Discuss:

- What exactly is left in the `PrgState` after a complete execution? And after an execution that stopped with an error, for example `readFile` on a line that is not a number?

- What would happen if we simply called `allStep()` again on the same controller? And if we only pushed the original program back on the ExeStack?

- Which parts must be new for each run (ExeStack, SymTable, Out, FileTable, …) and which can be shared ? Can the same `IStmt` object be reused – why does the answer depend on whether statements are immutable records or mutable classes (deep copy)?

- Where should the new program state be created: in the command (view), in the controller or in the repository? What does each choice mean for the MVC separation?

- A run that stopped with an error may leave files open in the FileTable. Who closes them?

- The log file is opened in append mode. How can the runs be told apart in the log? Should a new run clear the log file?

Seminar 6 · A3 and generics · page 1

<!-- page 2 -->
|Design|Idea|To discuss|
|---|---|---|
|1. A fresh state per run|The command keeps the program and the log file name; each`execute`creates `PrgState.of(program)`, a`Repository`and a `Controller`.|Simple – but the view now creates model objects. Is that acceptable?|
|2. Reset in the controller|`Controller.reset()`(or`Repository.reset()`) builds a new`PrgState`from `getOriginalProgram()`.|The view stays unchanged. What happens to the files of the old state?|
|3. A factory for the command|The command receives a`Supplier<Controller>` (a lambda, Lecture 5):`() -> new Controller(new` `Repository(PrgState.of(ex1), "log1.txt"),` `true)`and calls`get()`at every run.|Who decides how a run is set up? How does this compare with design 1?|
|`view/RunAgainCommand.j  `|`ava – design 1, a sketch`||

```
public class RunAgainCommand extends Command {
    private final IStmt program;            // immutable: safe to share
    private final String logFilePath;
    public RunAgainCommand(String key, IStmt program, String logFilePath) {
        super(key, program.toString());
        this.program = program;
        this.logFilePath = logFilePath;
    }
    @Override
    public void execute() {
        PrgState state = PrgState.of(program);          // a fresh state at each run
        var controller = new Controller(new Repository(state, logFilePath), true);
        try {
            controller.allStep();
        } catch (MyException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
```

## B. Generics exercises

Before you start (Lecture 4)

Is `ArrayList<B>` a subtype of `ArrayList<A>` when `B extends A` ? What can you read from an `ArrayList<? extends A>` , and what can you add to it? What can you add to an `ArrayList<? super C>` ?

### B1. Exercise 1

Given the following four classes in Java:

Seminar 6 · A3 and generics · page 2

<!-- page 3 -->
```
 Exercise 1
```

```
class A { … }
class B extends A { … }
class C extends A { … }
```

```
class Amain {
    A method1(ArrayList<…> list) {
        if (list.isEmpty()) return null;
        else return list.get(0);
    }
    void method2(ArrayList<…> list) {
        list.add(null);
    }
    void method3() {
        ArrayList<A> listA = new ArrayList<A>(); listA.add(new A());
        ArrayList<B> listB = new ArrayList<B>(); listB.add(new B());
        ArrayList<C> listC = new ArrayList<C>(); listC.add(new C());
        this.method1(listA); this.method1(listB); this.method1(listC);
        this.method2(listA); this.method2(listB); this.method2(listC);
    }
}
```

- Compute the most specific signatures of the methods `method1` and `method2` of class `Amain` (replace `…` in `ArrayList<…>` ) such that the entire program is correct. If it is not possible to find the types, justify your answer.

- Discuss line by line the correctness of the program. Use the table: for each candidate parameter type, does the call compile, and does the body of the method compile?

|Parameter type|listA|listB|listC|body of method1|body of method2|
|---|---|---|---|---|---|
|`ArrayList<A>`||||||
|`ArrayList<Object>`||||||
|`ArrayList<?>`||||||
|`ArrayList<? extends A>`||||||
|`ArrayList<? super A>`||||||

### B2. Exercise 2

Given the following four classes in Java – note the new hierarchy and the new `method2` :

Seminar 6 · A3 and generics · page 3

<!-- page 4 -->
```
 Exercise 2
```

```
class A { … }
class B extends A { … }
class C extends B { … }
```

```
class Amain {
    A method1(ArrayList<…> list) {
        if (list.isEmpty()) return null;
        else return list.get(0);
    }
    void method2(ArrayList<…> list, C elem) {
        list.add(elem);
    }
    void method3(C elem) {
        ArrayList<A> listA = new ArrayList<A>(); listA.add(new A());
        ArrayList<B> listB = new ArrayList<B>(); listB.add(new B());
        ArrayList<C> listC = new ArrayList<C>(); listC.add(new C());
        this.method1(listA); this.method1(listB); this.method1(listC);
        this.method2(listA, elem); this.method2(listB, elem); this.method2(listC, elem);
    }
}
```

- Compute the most specific signatures of `method1` and `method2` such that the entire program is correct. If it is not possible, justify your answer.

- Discuss line by line the correctness of the program, as in Exercise 1.

- Compare the two exercises: which parameter is a _producer_ and which a _consumer_ (PECS)? Would `method2` of Exercise 2 still work if `C` extended `A` directly, as in Exercise 1?

- Could `method1` be written as a generic method, `<T extends A> T method1(ArrayList<T> list)` ? What does the caller gain?

### B3. Exercise 3

Given the following four classes in Java – `method1` copies the elements of one list into another:

```
 Exercise 3
```

```
class A { … }
class B extends A { … }
class C extends B { … }
```

```
class Amain {
    void method1(ArrayList<…> src, ArrayList<…> dst) {
        for (… x : src)
            dst.add(x);
    }
    void method2() {
        ArrayList<A> listA = new ArrayList<A>(); listA.add(new A());
        ArrayList<B> listB = new ArrayList<B>(); listB.add(new B());
        ArrayList<C> listC = new ArrayList<C>(); listC.add(new C());
        this.method1(listC, listB); this.method1(listB, listA);
        this.method1(listC, listA); this.method1(listB, listB);
    }
}
```

- Compute the most specific signature of `method1` (both parameters and the type of `x` ) such that the entire program is correct. If it is not possible, justify your answer.

- Discuss line by line the correctness of the program: which list is a _producer_ and which a _consumer_ ?

- Add the call `this.method1(listA, listC)` . Is there any signature that makes it correct? Justify.

- Write `method1` as a generic method that copies from any list to any compatible list (compare with `Collections.copy` from the Java API). Which of the calls above still compile?

Seminar 6 · A3 and generics · page 4

<!-- page 5 -->
### B4. Exercise 4

Given the following classes in Java – `method1` returns the largest element of a non-empty list:

```
 Exercise 4
```

```
class A implements Comparable<A> {
    public int compareTo(A other) { … }
}
class B extends A { … }
class Amain {
    … method1(ArrayList<…> list) {
        … max = list.get(0);
        for (… x : list)
            if (x.compareTo(max) > 0) max = x;
        return max;
    }
    void method2() {
        ArrayList<Integer> listI = new ArrayList<Integer>();
        listI.add(3); listI.add(7);
        ArrayList<String> listS = new ArrayList<String>();
        listS.add("ana"); listS.add("bogdan");
        ArrayList<B> listB = new ArrayList<B>();
        listB.add(new B()); listB.add(new B());
        Integer i = this.method1(listI);
        String  s = this.method1(listS);
        B       b = this.method1(listB);
    }
}
```

- Can `method1` have a non-generic signature such that the program is correct? Justify.

- Compute the most specific generic signature of `method1` (the type parameter, its bound, the parameter and the return type) such that the entire program is correct.

- Does the bound `<T extends Comparable<T>>` work for all three calls? Which call fails and why? Note that `B` is a `Comparable<A>` , not a `Comparable<B>` .

- Compare your signature with that of `Collections.max` in the Java API.

Seminar 6 · A3 and generics · page 5
