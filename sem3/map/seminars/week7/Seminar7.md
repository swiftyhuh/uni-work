<!-- page 1 -->
SEMINAR 7  ·  WEEK 7  ·  9–13 NOVEMBER 2026

# Functional Programming with Java Streams

Assignment A4 and the garbage collector (Laboratory 7 document) · lambdas and streams (Lecture 5) · the Vavr library

||Agenda|
|---|---|
|A|Short discussion of assignment A4– especially the garbage collector.|
|B|20 problemsin the functional style with Java streams: from`forEach`and`map`to collectors, grouping and function composition.|
|C|Discussion of the Vavr library(vavr.io): functional data structures and control types for Java.|

## A. Assignment A4: a short discussion

|Topic|Questions to discuss|
|---|---|
|1. References and the heap|Why is a reference value a pair`(address, type)`and not just an address? Why is the address 0 never allocated? Why does the heap choose the addresses itself instead of being an ordinary dictionary?|
|2. The new eval|Why does`eval`need the heap? Which classes did the change of the signature affect – and how does the compiler help with such a refactoring?|
|3. new, rH, wH|Which type checks does each one perform? What is the difference between`v = …` (assignment) and`wH(v, …)`?|
|4. The unsafe collector|Trace Ex9: why does the unsafe collector remove location 1, and at which step does the program fail?|
|5. The safe collector|How do you compute the locations reachable through the heap? When does the computation stop? Can the heap of our toy language contain acycle– and would your collector still terminate if it could?|
|6. Streams in the collector|Read`getAddrFromSymTable`and`unsafeGarbageCollector`aloud: what does each stream operation do? Which part of the safe collector is easier to write with a loop than with a stream?|

## B. Problems with Java streams

Solve the problems in the functional style : streams, lambdas and method references – no `for` loops and no variables that are modified. Use the data below; the expected results refer to it.

Seminar 7 · Java streams · page 1

<!-- page 2 -->
#### <mark>`data`</mark>

```
List<String> words = List.of("hi", "hello", "bye", "goodbye", "java", "stream",
        "lambda", "map", "filter", "reduce", "eye", "queue", "collect", "Hello");
record Student(String name, int group, double grade) {}
List<Student> students = List.of(
        new Student("Ana", 921, 9.5),    new Student("Bogdan", 922, 4.0),
        new Student("Carmen", 921, 7.0), new Student("Dan", 923, 8.5),
        new Student("Elena", 922, 10.0), new Student("Florin", 923, 5.0),
        new Student("Gabriela", 921, 3.5), new Student("Horia", 922, 6.5));
String text = "The stream API is lazy. A stream is not a collection: "
            + "the stream is consumed once, and the collection is not.";
```

### B1. Basic operations: forEach, map, filter, reduce

P1. Loop over the words and print each one on a separate line, with two spaces in front of each word. Do not use `map` .

P2. Repeat P1, but without the two spaces in front. This is trivial with the approach of P1, so the point here is to use a method reference instead of an explicit lambda.

P3. Assume that we have a method `StringUtils.transformedList(List<String>,`

`Function1<String>)` and that we produced transformed lists like this:

```
 P3 – the old style
```

```
interface Function1<T> { T app(T t); }
List<String> excitingWords =
        StringUtils.transformedList(words, s -> s + "!");
List<String> eyeWords =
        StringUtils.transformedList(words, s -> s.replace("i", "eye"));
List<String> upperCaseWords =
        StringUtils.transformedList(words, String::toUpperCase);
```

Produce the same lists with streams and the built-in `map` . Which interface of `java.util.function` replaces `Function1` ?

P4. Assume a method `StringUtils.allMatches(List<String>, Predicate1<String>)` , with `interface Predicate1<T> { boolean check(T t); }` , and the filtered lists:

#### <mark>`P4 – the old style`</mark>

```
List<String> shortWords      = StringUtils.allMatches(words, s -> s.length() < 4);
List<String> wordsWithB      = StringUtils.allMatches(words, s -> s.contains("b"));
List<String> evenLengthWords = StringUtils.allMatches(words, s -> s.length() % 2 == 0);
```

Produce the same lists with `filter` .

P5. Turn the strings into upper case, keep only those shorter than 4 characters, of the remaining ones keep only those that contain `"E"` , and print the first result. Repeat the process, checking for a `"Q"` instead of an `"E"` – without repeating the code of the first version. What is the type of the result, and what happens when nothing matches?

_Expected:_ `Optional[BYE]` , and `Optional.empty` for `"Q"` .

P6. Produce a single `String` that concatenates the upper-case versions of all the words. Use a single `reduce` , without `map` .

Seminar 7 · Java streams · page 2

<!-- page 3 -->
P7. Produce the same `String` with a `map` that turns the words into upper case, followed by a `reduce` that concatenates them. Write the reduction with a method reference.

P8. Produce the words concatenated with commas in between: `"hi,hello,bye,…"` – no comma at the beginning and none at the end. Major hint: there are two versions of `reduce` . Then solve it again with a collector.

P9. Find the total number of characters (the sum of the lengths) of the words.

_Expected:_ `68`

P10. Find the number of words that contain an `"h"` . Then count them ignoring the case. Why are the two results different?

_Expected:_ `2` , and `3` ignoring the case.

### B2. Collectors: grouping, partitioning, sorting

P11. Group the words by their length: build a `Map<Integer, List<String>>` , with the lengths in increasing order.

_Expected:_ `{2=[hi], 3=[bye, map, eye], 4=[java], 5=[hello, queue, Hello], 6=[stream, lambda, filter, reduce], 7=[goodbye, collect]}`

P12. Split the words into those of even and those of odd length and count each part, in one pass over the stream ( `partitioningBy` with a downstream collector).

_Expected:_ `{false=8, true=6}`

P13. Produce the list of distinct words, ignoring the case, sorted by decreasing length and, for equal lengths, alphabetically . Build the comparator with

`Comparator.comparing(…).reversed().thenComparing(…)` .

_Expected:_ `[collect, goodbye, filter, lambda, reduce, stream, hello, queue, java, bye, eye, map, hi]`

P14. Count how many times each letter occurs in all the words, ignoring the case: a `Map<Character, Long>` sorted by letter. Hint: `String::chars` gives an `IntStream` ; you need `flatMap` .

_Expected:_ `{a=6, b=3, c=3, d=3, e=13, f=1, …, y=3}` – the most frequent letter is `e` .

P15. Find all the words of maximal length. Solve it twice: with two streams (first the maximal length, then the words), and with a single stream, using the map of P11.

_Expected:_ `[goodbye, collect]`

### B3. Harder problems

P16. Generate the first 15 Fibonacci numbers with `Stream.iterate` , without any variable outside the stream. Then find the first Fibonacci number greater than 1000. Hint: iterate over pairs of consecutive numbers.

_Expected:_ `[0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377]` and `1597` .

P17. Compute the average grade of each group of students, with the groups in increasing order.

_Expected:_ `{921=6.67, 922=6.83, 923=6.75}` (rounded).

P18. a) Find the best student of each group – once with `groupingBy` and `maxBy` , once with `toMap` and `BinaryOperator.maxBy` . Why does the first version give `Optional` values? b) Produce the names of the

Seminar 7 · Java streams · page 3

<!-- page 4 -->
students who passed (grade ≥ 5) in alphabetical order, as one string separated by `", "` . c) Compute the number of students, the minimum, the maximum and the average grade with a single terminal operation.

_Expected:_ a) `921 → Ana, 922 → Elena, 923 → Dan` ; b) `Ana, Carmen, Dan, Elena, Florin, Horia` ; c) `count=8, min=3.5, average=6.75, max=10.0` .

P19. Given a list of transformations, compose them into one function with `reduce` and apply it to every word:

#### <mark>`P19`</mark>

```
List<Function<String, String>> steps = List.of(
        String::trim, String::toUpperCase, s -> s + "!", s -> s.replace("E", "3"));
```

What is the identity element of the reduction? Does the order of composition matter – what changes with `Function::compose` instead of `Function::andThen` ?

_Expected:_ `[HI!, H3LLO!, BY3!, GOODBY3!, …, COLL3CT!, H3LLO!]`

P20. From `text` , find the 3 most frequent words with their number of occurrences: ignore the case and the punctuation, sort by decreasing frequency and, for equal frequencies, alphabetically. Write it as one stream pipeline (you may start a second stream from the entries of a map).

_Expected:_ `[is=4, stream=3, the=3]`

For each problem, also discuss

Which operations are intermediate and which terminal ? Is the pipeline lazy – would it work on an infinite stream? Could it run as a `parallelStream()` and give the same result?

## C. The Vavr library

Vavr (https://www.vavr.io/) is a functional library for Java: immutable, persistent collections , control types such as `Option` , `Try` and `Either` , tuples and function types. Add it to a Gradle project as the dependency `io.vavr:vavr` (see the site for the current version). An illustration:

```
 Vavr – an illustration
```

```
import io.vavr.collection.List;          // not java.util.List
import io.vavr.control.Option;
import io.vavr.control.Try;
List<Integer> xs = List.of(1, 2, 3);
List<Integer> ys = xs.prepend(0);       // a new list [0, 1, 2, 3]; xs is unchanged
List<Integer> zs = xs.map(x -> x * 2);  // no stream() and no collect() needed
Try<Integer> n = Try.of(() -> Integer.parseInt("12x"));   // a Failure, no exception
int value = n.getOrElse(0);                               // 0
Option<String> name = Option.of(null);  // None
```

Discuss:

- What is the difference between `java.util.List.of(…)` (unmodifiable) and a Vavr `List` (persistent)? How can `prepend` return a new list without copying the old one?

- A lambda in `stream().map(…)` cannot throw a checked exception such as `IOException` . How does `Try` solve this problem? Compare it with the way our interpreter turns Java exceptions into `MyException` s.

- `Option` versus `java.util.Optional` : what does Vavr add? When would you use `Either<String, IValue>` instead of throwing an exception?

Seminar 7 · Java streams · page 4

<!-- page 5 -->
- Which structures of the interpreter (ExeStack, SymTable, Heap) could be persistent, and what would we gain – for example for the log file or for running a program step by step backwards?

Seminar 7 · Java streams · page 5
