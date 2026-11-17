<!-- page 1 -->
SEMINAR 8  ·  WEEK 8  ·  16–20 NOVEMBER 2026

# Threads and Synchronization and a Model for the Test from week 11

Threads, synchronized, wait / notify (Lecture 6) · the seminar test of week 11: generics and Java streams

||Agenda|
|---|---|
|A|Two problems with threads(Lecture 6): a race condition, and two threads that take turns.|
|B|The seminar testof week 11: what it contains and how it works.|
|C|A model test: one problem with generics and three problems with Java streams.|

Seminar test: week 11 (7–11 December 2026)

In week 11 there is a closed-book test during the seminar. It consists of one problem with generics and three problems with Java functional streams – like the model test in part C.

## A. Problems with threads

### A1. A shared counter

Two threads increment the same counter 100 000 times each:

```
 SharedCounter.java
```

```
public class SharedCounter {
    private int count = 0;
    public void increment() { count++; }
    public int get() { return count; }
    public static void main(String[] args) throws InterruptedException {
        SharedCounter c = new SharedCounter();
        Runnable task = () -> {
            for (int i = 0; i < 100_000; i++)
                c.increment();
        };
        Thread t1 = new Thread(task);
        Thread t2 = new Thread(task);
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.println(c.get());
    }
}
```

- Which values can the program print? Why is the result not always 200 000? Describe an interleaving of the two threads that loses an increment.

- What happens if we remove the two calls of `join()` ? And if we call `t1.run()` and `t2.run()` instead of `start()` ?

- Fix the program in two ways: with a `synchronized` method, and with a `synchronized` block on a private lock object. Must `get()` be synchronized too – why?

- Would declaring `count` as `volatile` be enough? Justify.

Seminar 8 · Threads and a model test · page 1

<!-- page 2 -->
### A2. Ping-pong

Write a program with two threads: one prints `ping` , the other prints `pong` , each 3 times. The output must always be:

```
 expected output
```

```
ping
pong
ping
pong
ping
pong
```

Use a shared object with a flag that tells whose turn it is, and the methods `wait()` and `notifyAll()` . A skeleton:

```
 PingPong.java
```

```
class PingPong {
    private boolean pingTurn = true;
```

```
    synchronized void play(String word, boolean isPing) {
        // TODO: 3 times – wait until it is my turn, print the word,
        //       give the turn to the other thread, wake it up
    }
}
```

```
PingPong game = new PingPong();
Thread ping = new Thread(() -> game.play("ping", true));
Thread pong = new Thread(() -> game.play("pong", false));
```

- Why must `wait()` be called inside a `while` loop and not inside an `if` ?

- Why must `play` be `synchronized` ? What happens if it is not?

- What changes if we replace `notifyAll()` by `notify()` ? Is it still correct with two threads – and with three threads that print `ping` , `pong` and `pang` in turn?

- Where must `InterruptedException` be handled, and what should the handler do?

## B. The seminar test

||The seminar test|
|---|---|
|When|week 11 (7–11 December 2026), during your seminar|
|How|closed book: no notes, no laptop, no phone – you write the code on paper|
|What|1 problem with generics(as in Seminar 6) and3 problems with Java functional streams(as in Seminar 7)|
|Style|the stream problems must be solved in thefunctional style: streams, lambdas, method references and collectors – no loops and no variables that are modified|

To prepare: solve again the exercises of Seminar 6 (generics) and the 20 problems of Seminar 7 (streams) on paper, without an IDE. Learn the signatures of the common stream operations and collectors: `filter` , `map` , `flatMap` , `sorted` , `distinct` , `reduce` , `collect` , `Collectors.toList` , `joining` , `groupingBy` , `partitioningBy` , `counting` , `summingDouble` , `averagingDouble` , `maxBy` , `toMap` .

Seminar 8 · Threads and a model test · page 2

<!-- page 3 -->
## C. Model test

Instructions

Closed book. Write the code on paper. Problem 1: generics. Problems 2–4: Java streams, in the functional style.

### Problem 1 (generics)

Given the following classes in Java:

```
 Problem 1
```

```
class A { … }
class B extends A { … }
class C extends B { … }
```

```
class Amain {
    void method1(ArrayList<…> list, … elem) {
        list.add(elem);
    }
    … method2(ArrayList<…> list) {
        return list.get(0);
    }
    void method3() {
        ArrayList<A> listA = new ArrayList<A>(); listA.add(new A());
        ArrayList<B> listB = new ArrayList<B>(); listB.add(new B());
        ArrayList<C> listC = new ArrayList<C>(); listC.add(new C());
        this.method1(listA, new C());
        this.method1(listB, new C());
        this.method1(listC, new C());
        A x = this.method2(listB);
        B y = this.method2(listC);
    }
}
```

- Compute the most specific signatures of `method1` and `method2` (the types marked `…` : the type arguments of `ArrayList` , the type of `elem` and the return type of `method2` ) such that the entire program is correct. If it is not possible, justify your answer.

- Discuss line by line the correctness of the program for the signatures you found.

Problems 2–4 (Java streams)

#### <mark>`data`</mark>

```
record Product(String name, String category, double price, int stock) {}
List<Product> products = List.of(
        new Product("Java in Action", "books", 45.0, 10),
        new Product("Effective Java", "books", 60.0, 4),
        new Product("Clean Code", "books", 38.5, 0),
        new Product("Laptop", "electronics", 3200.0, 3),
        new Product("Mouse", "electronics", 75.0, 25),
        new Product("Monitor", "electronics", 950.0, 0),
        new Product("Desk", "furniture", 700.0, 5),
        new Product("Chair", "furniture", 450.0, 8));
```

Problem 2. Produce a single `String` with the names of the books cheaper than 50, in upper case , sorted alphabetically and separated by `", "` .

Seminar 8 · Threads and a model test · page 3

<!-- page 4 -->
_For the data above:_ `CLEAN CODE, JAVA IN ACTION`

Problem 3. Compute, for each category, the total value of the stock (the sum of `price * stock` over the products of the category), as a `Map<String, Double>` with the categories in alphabetical order.

_For the data above:_ `{books=690.0, electronics=11475.0, furniture=7100.0}`

Problem 4. Considering only the products that are in stock ( `stock > 0` ), find the name of the most expensive product of each category , as a `Map<String, String>` with the categories in alphabetical order.

_For the data above:_ `{books=Effective Java, electronics=Laptop, furniture=Desk}`

Seminar 8 · Threads and a model test · page 4
