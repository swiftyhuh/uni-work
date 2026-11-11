<!-- page 1 -->
## Advanced Programming Methods Lecture 5 – Lambdas, Streams and NIO

```
persoane.stream().filter(p -> p.varsta() >= 18).toList()
```

<!-- page 2 -->
I N T R O D U C T I O N

#### Lecture overview

01

02

Lambdas, functional interfaces, method references

Streams: pipelines, collectors, Optional

03

04

NIO.2: Path, Files and file streams

NIO: channels, buffers, asynchronous I/O

2

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 3 -->
# 01

### Lambdas and functional interfaces

3

<!-- page 4 -->
0 1 · L A M B D A S A N D F U N C T I O N A L I N T E R F A C E S

#### From anonymous classes to lambdas (Java 8)

###### `anonymous classes`

###### `lambda expressions`

```
Runnable r1 = newRunnable() {
@Override
publicvoidrun() {
System.out.println("Hello one!");
}
};
albums.sort(newComparator<CD>() {
@Override
publicintcompare(CD a, CD b) {
returna.titlu().compareTo(b.titlu());
}
});
```

```
Runnable r2 = () -> System.out.println("Hello two!");
albums.sort((a, b) -> a.titlu().compareTo(b.titlu()));
```

```
// both are objects implementing the interface:
r1.run();
r2.run();
```

A lambda is a short way to write an object of a _functional interface_ : the parameter list, an arrow, and the body of its single i abstract method.

4

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 5 -->
0 1 · L A M B D A S A N D F U N C T I O N A L I N T E R F A C E S

#### Lambda syntax

- `(parameters) -> expression` or `(parameters) -> { statements }`

- Parameter types are usually inferred

- One parameter: parentheses optional

- Block body: use `return` for the result; expression body: no `return`

- Captured local variables must be effectively final (Lecture 2)

```
(intx, inty) -> x + y           // explicit types
(x, y) -> x + y                   // inferred types
x -> x * x                        // one parameter
() -> 42// no parameters
(String s) -> { System.out.println(s); }
```

```
(a1, a2) -> { returna1 > a2; }   // block: return
(a1, a2) -> a1 > a2               // same, expression
```

```
(oldState, newState) -> {
System.out.println("Old state: "+ oldState);
System.out.println("New state: "+ newState);
}
```

5

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 6 -->
0 1 · L A M B D A S A N D F U N C T I O N A L I N T E R F A C E S

#### Functional interfaces

- An interface with exactly one abstract method (default/static methods allowed)

- `@FunctionalInterface` makes the compiler check it

- A lambda gets its type from the context: it becomes an instance of the target interface

```
@FunctionalInterface
publicinterfaceMyComparator {
booleancompare(inta1, inta2);
```

```
}
```

```
MyComparator mai = (a1, a2) -> a1 > a2;   // a lambda is an object
booleanr = mai.compare(2, 5);             // false
```

```
MyComparator invers = (a1, a2) -> a1 < a2;
sorteaza(vector, invers);                  // passed around like data
```

- Examples in the JDK: `Runnable` , `Comparator` , `ActionListener` , `Callable`

6

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 7 -->
0 1 · L A M B D A S A N D F U N C T I O N A L I N T E R F A C E S

#### Standard functional interfaces: java.util.function

|Interface|Method|Meaning|Example|
|---|---|---|---|
|`Predicate<T>`|`boolean test(T t)`|a condition on a T|`p -> p.varsta() >= 18`|
|`Function<T,R>`|`R apply(T t)`|transforms a T into an R|`s -> s.length()`|
|`Consumer<T>`|`void accept(T t)`|an action on a T|`s -> System.out.println(s)`|
|`Supplier<T>`|`T get()`|produces a T (factory)|`() -> new ArrayList<>()`|
|`UnaryOperator<T>`|`T apply(T t)`|T → T|`s -> s.toUpperCase()`|
|`BinaryOperator<T>`|`T apply(T a, T b)`|(T, T) → T|`(a, b) -> a + b`|
|`BiFunction<T,U,R>`|`R apply(T t, U u)`|(T, U) → R|`(s, n) -> s.repeat(n)`|

_Primitive specializations avoid boxing:_ _`IntPredicate` ,_ _`IntFunction<R>` ,_ _`ToIntFunction<T>` ,_ _`IntBinaryOperator` , …_

7

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 8 -->
0 1 · L A M B D A S A N D F U N C T I O N A L I N T E R F A C E S

#### Method references

When a lambda only calls an existing method, write `Class::method` instead:

|Kind|Method reference|Equivalent lambda|
|---|---|---|
|static method|`Integer::parseInt`|`s -> Integer.parseInt(s)`|
|method of a given object|`System.out::println`|`x -> System.out.println(x)`|
|instance method of the parameter|`String::length`|`s -> s.length()`|
|constructor|`ArrayList::new`|`() -> new ArrayList<>()`|

```
lista.forEach(System.out::println);
List<Integer> lungimi = cuvinte.stream().map(String::length).toList();
```

8

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 9 -->
0 1 · L A M B D A S A N D F U N C T I O N A L I N T E R F A C E S

#### Case study: contacting people – without lambdas

■ Drivers (age ≥ 16) get phone calls; draftees (male, 18–25) get e-mails; pilots (23–65) get letters

- Each method repeats the loop – the DRY principle is violated

- Criteria are hard-coded: every change of a rule means editing code in several places

```
RoboContactMethods.java
```

```
publicclassRoboContactMethods {
publicvoidcallDrivers(List<Person> pl) {
for(Person p : pl)
if(p.getAge() >= 16)
roboCall(p);
```

```
}
```

```
publicvoidemailDraftees(List<Person> pl) {
for(Person p : pl)
```

```
if(p.getAge() >= 18&& p.getAge() <= 25
&& p.getGender() == Gender.MALE)
roboEmail(p);
```

```
}
publicvoidmailPilots(List<Person> pl) {
for(Person p : pl)
```

```
if(p.getAge() >= 23&& p.getAge() <= 65)
roboMail(p);
```

```
}
```

```
}
```

9

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 10 -->
0 1 · L A M B D A S A N D F U N C T I O N A L I N T E R F A C E S

#### Case study: behaviour as a parameter

■ Step 1: extract the criterion into a `Predicate<Person>`

■ Step 2: one generic method receives the criterion and the action

- Step 3: pass lambdas – new rules need no new methods

```
publicvoidcontact(List<Person> pl,
Predicate<Person> criteriu,
Consumer<Person> actiune) {
for(Person p : pl)
if(criteriu.test(p))
actiune.accept(p);
}
```

```
Predicate<Person> drivers  = p -> p.getAge() >= 16;
Predicate<Person> draftees = p -> p.getAge() >= 18&& p.getAge() <= 25
&& p.getGender() == Gender.MALE;
Predicate<Person> pilots   = p -> p.getAge() >= 23&& p.getAge() <= 65;
robo.contact(pl, drivers, robo::roboCall);
robo.contact(pl, pilots.and(draftees.negate()), robo::roboMail);
```

10

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 11 -->
0 1 · L A M B D A S A N D F U N C T I O N A L I N T E R F A C E S

#### Building comparators with lambdas

`■ Comparator.comparing(keyExtra ctor)` – compare by a key

- `thenComparing` – tie-breaker; `reversed()` – opposite order

- `comparingInt` , `comparingDouble` avoid boxing

- `nullsFirst` / `nullsLast` handle `null`

```
// by price
albums.sort(Comparator.comparing(CD::pret));
// by artist, then by title
albums.sort(Comparator.comparing(CD::artist)
.thenComparing(CD::titlu));
// most expensive first
albums.sort(Comparator.comparing(CD::pret).reversed());
persons.sort(Comparator.comparingInt(Person::getAge));
Set<CD> s = newTreeSet<>(Comparator.comparing(CD::titlu));
```

11

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 12 -->
0 1 · L A M B D A S A N D F U N C T I O N A L I N T E R F A C E S

#### Lambdas in the Collections API

```
List / Collection
```

###### `Map`

```
lista.forEach(System.out::println);
lista.removeIf(String::isBlank);
lista.replaceAll(String::toUpperCase);
lista.sort(Comparator.naturalOrder());
```

```
// word count
```

```
Map<String, Integer> frecv = newHashMap<>();
for(String w : cuvinte)
frecv.merge(w, 1, Integer::sum);
```

```
// group words by first letter
Map<Character, List<String>> grup = newTreeMap<>();
for(String w : cuvinte)
grup.computeIfAbsent(w.charAt(0),
k -> newArrayList<>()).add(w);
frecv.forEach((k, v) -> System.out.println(k + " = "+ v));
```

12

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 13 -->
# 02 Streams

13

<!-- page 14 -->
0 2 · S T R E A M S

#### Streams: declarative data processing

- A stream is a sequence of elements from a source (collection, array, file …) supporting aggregate operations

- Describe what to compute, not how to loop

- SQL-like operations: `filter` , `map` , `sorted` , `reduce` , `collect` …

- Streams do not store elements – they are computed on demand

```
List<String> myList = List.of("a1", "a2", "b1", "c2", "c1");
```

```
myList.stream()
.filter(s -> s.startsWith("c"))
.map(String::toUpperCase)
.sorted()
.forEach(System.out::println);
// C1
// C2
```

14

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 15 -->
0 2 · S T R E A M S

#### Streams vs. collections

```
Collection
```

##### Collections are about data

An in-memory data structure: every element exists before it is added.

You iterate explicitly (external iteration: for, Iterator). Can be traversed many times.

```
Stream
```

##### Streams are about computation

Elements are computed on demand . The library iterates for you (internal iteration), so it can optimize: laziness, short-circuiting, parallelism. A stream can be consumed only once .

15

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 16 -->
0 2 · S T R E A M S

#### Anatomy of a stream pipeline

<!-- Start of picture text -->
filter source map sorted terminal .filter(p -> persoane.stream() .map(Persoana::nume) .sorted() .toList() p.varsta() >= 18) intermediate operations – lazy, return a Stream produces the result <!-- End of picture text -->

- Intermediate operations ( `filter` , `map` , `sorted` , `distinct` , `limit` …) only configure the pipeline – nothing runs yet

- The terminal operation ( `toList` , `collect` , `forEach` , `count` , `reduce` …) triggers the processing and closes the stream

- Stateless operations ( `filter` , `map` ) pass elements through one at a time ; stateful ones like `sorted` must first see all elements

16

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 17 -->
0 2 · S T R E A M S

#### Running example

```
recordPersoana(String nume, intvarsta, String oras) { }
List<Persoana> persoane = List.of(
newPersoana("Ana", 23, "Cluj"),
newPersoana("Ion", 17, "Iasi"),
newPersoana("Maria", 31, "Cluj"),
newPersoana("Paul", 45, "Brasov"),
newPersoana("Petra", 12, "Cluj"));
```

The next slides use this list. Records (Lecture 2) are ideal i stream elements: immutable, with accessors and `toString` .

17

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 18 -->
0 2 · S T R E A M S

#### Filtering and slicing

- `filter(Predicate)` – keeps matching elements

- `distinct()` – removes duplicates (by `equals` )

- `limit(n)` / `skip(n)` – first n / all but the first n

```
persoane.stream()
.filter(p -> p.oras().equals("Cluj"))
.map(Persoana::nume)
.toList();                     // [Ana, Maria, Petra]
```

```
Stream.of(1, 2, 2, 3, 3, 3).distinct().toList();   // [1, 2, 3]
Stream.of(5, 6, 7, 8).skip(1).limit(2).toList();    // [6, 7]
Stream.of(1, 3, 6, 7, 9).takeWhile(n -> n % 2== 1)
.toList();                // [1, 3]
```

- `takeWhile` / `dropWhile` (Java 9) – while a condition holds

18

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 19 -->
0 2 · S T R E A M S

#### Mapping: transforming elements

- `map(Function)` – one element in, one element out

- `mapToInt` / `mapToDouble` – to numeric streams

- `flatMap` – one element in, a stream of elements out (flattening)

```
List<Integer> lungimi = List.of("Oracle", "Java", "Magazine")
.stream()
.map(String::length)
.toList();                         // [6, 4, 8]
intsumaVarste = persoane.stream()
.mapToInt(Persoana::varsta)
.sum();                            // 128
List<String> litere = List.of("ab", "cd").stream()
.flatMap(w -> w.chars().mapToObj(c -> String.valueOf((char) c)))
.toList();                         // [a, b, c, d]
```

19

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 20 -->
0 2 · S T R E A M S

#### Laziness and short-circuiting

```
List<Integer> numbers = List.of(1, 2, 3, 4, 5, 6, 7, 8);
List<Integer> twoEvenSquares = numbers.stream()
.filter(n -> {
System.out.println("filtering "+ n);
returnn % 2== 0;
})
.map(n -> {
System.out.println("mapping "+ n);
returnn * n;
})
.limit(2)
.toList();
```

```
output
```

```
filtering 1
filtering 2
mapping 2
filtering 3
filtering 4
mapping 4
```

Only the elements needed for the result are processed: `limit(2)` short-circuits the pipeline after two results; 5–8 are i never examined.

20

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 21 -->
0 2 · S T R E A M S

#### Order of operations matters

###### `map, then filter – 10 calls`

```
filter, then map –6 calls
```

```
Stream.of("d2", "a2", "b1", "b3", "c")
.map(s -> { System.out.println("map: "+ s);
returns.toUpperCase(); })
.filter(s -> { System.out.println("filter: "+ s);
returns.startsWith("A"); })
.forEach(s -> System.out.println("forEach: "+ s));
// map: d2   filter: D2
// map: a2   filter: A2   forEach: A2
// map: b1   filter: B1
// map: b3   filter: B3
// map: c    filter: C
```

```
Stream.of("d2", "a2", "b1", "b3", "c")
.filter(s -> { System.out.println("filter: "+ s);
returns.startsWith("a"); })
.map(s -> { System.out.println("map: "+ s);
returns.toUpperCase(); })
.forEach(s -> System.out.println("forEach: "+ s));
// filter: d2
// filter: a2   map: a2   forEach: A2
// filter: b1
// filter: b3
// filter: c
```

With stateless operations like `map` and `filter` , each element travels through the whole pipeline before the next one starts. ? Filter early to do less work.

21

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 22 -->
0 2 · S T R E A M S

#### Collecting results

`■ toList()` (Java 16) – unmodifiable list `■ collect(Collectors.…)` – any result shape `■ joining` – delimiter, prefix, suffix `■ toMap` – keys must be unique, otherwise `IllegalStateException` – unless a merge function is given

```
List<String> adulti = persoane.stream()
.filter(p -> p.varsta() >= 18).map(Persoana::nume).toList();
Set<String> orase = persoane.stream()
.map(Persoana::oras).collect(Collectors.toSet());
String fraza = persoane.stream()
.filter(p -> p.varsta() >= 18).map(Persoana::nume)
.collect(Collectors.joining(", ", "In Romania ", " sunt majori."));
// In Romania Ana, Maria, Paul sunt majori.
Map<String, String> peOras = persoane.stream()
.collect(Collectors.toMap(Persoana::oras, Persoana::nume,
(n1, n2) -> n1 + ";"+ n2));
// {Brasov=Paul, Cluj=Ana;Maria;Petra, Iasi=Ion} (HashMap: any order)
```

22

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 23 -->
0 2 · S T R E A M S

#### Grouping and partitioning

`■ groupingBy(key)` – a `Map<K, List<T>>`

```
Map<String, List<Persoana>> dupaOras = persoane.stream()
.collect(Collectors.groupingBy(Persoana::oras));
```

■ A second collector aggregates each group: `counting` , `averagingInt` , `mapping` … `■ partitioningBy(pred)` – a map with keys `true` / `false`

```
Map<String, Long> cateInOras = persoane.stream()
.collect(Collectors.groupingBy(Persoana::oras, Collectors.counting()));
// {Brasov=1, Cluj=3, Iasi=1} (HashMap: any order)
Map<String, Double> varstaMedie = persoane.stream()
.collect(Collectors.groupingBy(Persoana::oras,
TreeMap::new, Collectors.averagingInt(Persoana::varsta)));
// {Brasov=45.0, Cluj=22.0, Iasi=17.0}
Map<Boolean, List<String>> majori = persoane.stream()
.collect(Collectors.partitioningBy(p -> p.varsta() >= 18,
Collectors.mapping(Persoana::nume, Collectors.toList())));
// {false=[Ion, Petra], true=[Ana, Maria, Paul]}
```

23

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 24 -->
0 2 · S T R E A M S

#### Reduction: from many values to one

`■ reduce(identity, op)` – combines all elements with a `BinaryOperator`

■ Without identity, `reduce(op)` returns an `Optional` (the stream may be empty)

- Prefer the specialized forms: `sum()` , `max()` , `count()`

```
intsum = 0;                         // imperative
for(intx : numbers) sum += x;
```

```
intsum2 = numbers.stream().reduce(0, (a, b) -> a + b);
intprod = numbers.stream().reduce(1, (a, b) -> a * b);
Optional<Integer> max = numbers.stream().reduce(Integer::max);
String concat = Stream.of("one", "two", "three")
.reduce("", (acc, item) -> acc + " "+ item);
// " one two three"
```

```
longn = items.stream().filter(s -> s.startsWith("t")).count();
```

24

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 25 -->
0 2 · S T R E A M S

#### Optional<T>: a value that may be absent

■ Returned by `min` , `max` , `findFirst` , `reduce(op)` …

```
Optional<String> cel_mai_scurt = items.stream()
.min(Comparator.comparing(String::length));
```

- Don't call `get()` blindly – on an empty `Optional` it throws `NoSuchElementException`

- Use `orElse` , `orElseGet` ,

`orElseThrow` , `ifPresent` , `map`

```
String s1 = cel_mai_scurt.orElse("");             // default value
String s2 = cel_mai_scurt.orElseThrow();          // fail explicitly
cel_mai_scurt.ifPresent(System.out::println);     // only if present
```

```
Optional<Persoana> p = persoane.stream()
.filter(x -> x.oras().equals("Sibiu")).findFirst();
String oras = p.map(Persoana::nume).orElse("nimeni");  // "nimeni"
```

- Meant for return values – not for

   - fields or parameters

25

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 26 -->
0 2 · S T R E A M S

#### Numeric streams

`■ IntStream` , `LongStream` , `DoubleStream` – no boxing

■ Ranges: `range(a, b)` (b excluded), `rangeClosed(a, b)`

- Built-in `sum` , `average` , `min` , `max` , `summaryStatistics`

`■ boxed()` converts back to `Stream<Integer>`

```
IntStream oddNumbers = IntStream.rangeClosed(10, 30)
.filter(n -> n % 2== 1);
OptionalDouble medie = persoane.stream()
.mapToInt(Persoana::varsta).average();     // 25.6
IntSummaryStatistics st = persoane.stream()
.mapToInt(Persoana::varsta).summaryStatistics();
st.getMin(); st.getMax(); st.getAverage(); st.getCount();
Stream.of("a1", "a2", "a3")
.map(s -> s.substring(1))
.mapToInt(Integer::parseInt)
.max()
.ifPresent(System.out::println);         // 3
```

26

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 27 -->
0 2 · S T R E A M S

#### Creating streams

■ From collections, arrays, values, files …

■ Infinite streams with `iterate` and `generate` – bounded by `limit` or a condition

■ A file stream must be closed – use try-with-resources

```
Stream<String> s1 = lista.stream();
IntStream s2 = Arrays.stream(newint[]{1, 2, 3, 4});
Stream<Integer> s3 = Stream.of(1, 2, 3, 4);
Stream.iterate(0, n -> n + 10).limit(5)
.forEach(System.out::println);           // 0 10 20 30 40
Stream.iterate(1, n -> n < 100, n -> n * 2)    // Java 9: with condition
.toList();                               // [1, 2, 4, ..., 64]
Stream.generate(Math::random).limit(3).toList();
try(Stream<String> linii = Files.lines(Path.of("fisier.txt"))) {
longnr = linii.count();
}
```

27

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 28 -->
0 2 · S T R E A M S

#### Matching and finding

- `anyMatch` , `allMatch` , `noneMatch` – take a predicate, return `boolean`

- `findFirst` , `findAny` – return an `Optional`

- All of them are terminal and shortcircuiting

```
booleanexistaMinori = persoane.stream()
.anyMatch(p -> p.varsta() < 18);              // true
booleantotiDinCluj = persoane.stream()
.allMatch(p -> p.oras().equals("Cluj"));      // false
booleannimeniPeste100 = persoane.stream()
.noneMatch(p -> p.varsta() > 100);            // true
Optional<Persoana> primulMajor = persoane.stream()
.filter(p -> p.varsta() >= 18)
.findFirst();                                 // Ana
```

28

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 29 -->
0 2 · S T R E A M S

#### A stream can be consumed only once

###### ✗ `reusing a stream`

✓ `a Supplier creates a new stream each time`

```
Stream<String> stream = Stream.of("d2", "a2", "b1", "b3", "c")
.filter(s -> s.startsWith("a"));
```

```
stream.anyMatch(s -> true);    // OK
stream.noneMatch(s -> true);
// IllegalStateException: stream has
// already been operated upon or closed
```

```
Supplier<Stream<String>> streamSupplier =
() -> Stream.of("d2", "a2", "b1", "b3", "c")
.filter(s -> s.startsWith("a"));
streamSupplier.get().anyMatch(s -> true);    // OK
streamSupplier.get().noneMatch(s -> true);   // OK
```

29

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 30 -->
0 2 · S T R E A M S

#### Imperative vs. declarative: the same task

###### `loops – how`

```
streams –what
```

```
Map<String, List<String>> rez = newTreeMap<>();
for(Persoana p : persoane) {
if(p.varsta() >= 18) {
List<String> l = rez.get(p.oras());
if(l == null) {
l = newArrayList<>();
rez.put(p.oras(), l);
}
l.add(p.nume().toUpperCase());
}
}
for(List<String> l : rez.values())
Collections.sort(l);
```

```
Map<String, List<String>> rez = persoane.stream()
.filter(p -> p.varsta() >= 18)
.sorted(Comparator.comparing(Persoana::nume))
.collect(Collectors.groupingBy(
Persoana::oras,
TreeMap::new,
Collectors.mapping(p -> p.nume().toUpperCase(),
Collectors.toList())));
// {Brasov=[PAUL], Cluj=[ANA, MARIA]}
```

? Task: adults' names in upper case, grouped by city, cities and names sorted. Which version is easier to read – and to change?

30

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 31 -->
0 2 · S T R E A M S

#### Looking ahead: stream gatherers (Java 24)

`■ Stream::gather` adds custom intermediate operations

■ Built-in gatherers in `java.util.stream.Gatherers` : fixed and sliding windows, `fold` , `scan` , `mapConcurrent`

- Just as `collect` is extensible with collectors, the middle of the pipeline is now extensible too

```
Stream.of(1, 2, 3, 4, 5, 6, 7)
.gather(Gatherers.windowFixed(3))
.toList();
// [[1, 2, 3], [4, 5, 6], [7]]
Stream.of(1, 2, 3, 4)
.gather(Gatherers.windowSliding(2))
.toList();
// [[1, 2], [2, 3], [3, 4]]
```

31

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 32 -->
# 03

### NIO.2: Path and Files

32

<!-- page 33 -->
0 3 · N I O . 2 : P A T H A N D F I L E S

#### java.io.File vs. java.nio.file (NIO.2, Java 7)

||java.io.File (legacy)|Path + Files (modern)|
|---|---|---|
|Represents|a file name, not its content|a path;`Files`holds the operations|
|Errors|`boolean`results –`delete()`just returns false|meaningful exceptions (`NoSuchFileException`…)|
|Content|needs streams|one-liners:`readString`,`readAllLines`,`write`|
|Directories|`list()`loads everything|lazy streams:`list`,`walk`,`find`|
|Extras|–|symbolic links, attributes, file watching, zip file systems|

<!-- Start of picture text -->
i <!-- End of picture text -->

Convert when needed: `file.toPath()` and `path.toFile()` . Use `Path` / `Files` in new code.

33

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 34 -->
0 3 · N I O . 2 : P A T H A N D F I L E S

#### Path: platform-independent file names

- `Path.of` (Java 11) / `Paths.get` builds paths with the right separator

- Paths can be absolute or relative, to files or directories

- Operations on the _name_ only – the file need not exist

```
Path p = Path.of("data", "studenti.txt");   // data/studenti.txt
p.getFileName();                            // studenti.txt
p.getParent();                              // data
p.toAbsolutePath();      // /home/ana/proiect/data/studenti.txt
p.resolveSibling("note.txt");               // data/note.txt
Path.of("a/b/../c").normalize();            // a/c
Path.of("/x/y").relativize(Path.of("/x/z/w")); // ../z/w
Path dirCurent = Path.of("").toAbsolutePath(); // current directory
```

34

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 35 -->
0 3 · N I O . 2 : P A T H A N D F I L E S

#### Files: common operations in one line

```
String text        = Files.readString(p);                  // Java 11
List<String> linii = Files.readAllLines(p);
byte[] octeti      = Files.readAllBytes(p);
Files.writeString(Path.of("out.txt"), "Salut\n");          // Java 11
Files.write(Path.of("out.txt"), linii, StandardOpenOption.APPEND);
booleanexista = Files.exists(p);
longdim       = Files.size(p);
Files.createDirectories(Path.of("rezultate", "2026"));
Files.copy(p, Path.of("backup.txt"), StandardCopyOption.REPLACE_EXISTING);
Files.move(Path.of("a.txt"), Path.of("arhiva", "a.txt"));
Files.deleteIfExists(Path.of("erori.txt"));
```

```
try(BufferedReader br = Files.newBufferedReader(p)) { /* large files */}
```

`readString` / `readAllLines` load the whole file into memory – fine for small files. For large files use `Files.lines` or i `newBufferedReader` .

35

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 36 -->
0 3 · N I O . 2 : P A T H A N D F I L E S

#### The student example, the modern way

```
Path in = Path.of("Studenti.txt"), out = Path.of("Sortati.txt");
List<Student> studenti;
try(Stream<String> linii = Files.lines(in)) {
studenti = linii.filter(l -> !l.isBlank())
.map(Student::parse)
.toList();
}
```

Records (L2), exceptions (L3), streams, method references and ? NIO.2 (L5) together: the whole task in about 15 lines.

```
List<String> rezultat = studenti.stream()
.sorted(Comparator.comparingDouble(Student::media))
.map(s -> s.nume() + "|"+ s.media())
.toList();
```

```
Files.write(out, rezultat);
```

36

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 37 -->
0 3 · N I O . 2 : P A T H A N D F I L E S

#### Listing and walking directories

`■ Files.list` – one level; `Files.walk` – recursive

- Both return lazy streams that must be closed

- `newDirectoryStream` accepts glob patterns

```
try(Stream<Path> s = Files.list(Path.of("."))) {           // one level
s.filter(p -> p.toString().endsWith(".txt"))
.forEach(System.out::println);
```

```
}
```

```
try(Stream<Path> s = Files.walk(Path.of("src"))) {          // recursive
longn = s.filter(p -> p.toString().endsWith(".java")).count();
}
```

```
try(vards = Files.newDirectoryStream(Path.of("."), "*.txt")) {
for(Path p : ds) System.out.println(p);
}
```

```
// legacy java.io.File, with a lambda instead of an anonymous FilenameFilter
String[] txt = newFile(".").list((dir, name) -> name.endsWith(".txt"));
```

37

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 38 -->
0 3 · N I O . 2 : P A T H A N D F I L E S

#### Character encodings

- Text on disk is bytes; a charset maps bytes to characters

- Before Java 18 the default charset depended on the OS (e.g. Windows-1250 on a Romanian Windows) – diacritics broke between machines

- Java 18 (JEP 400): UTF-8 is the default on every platform

- Specify the charset explicitly when exchanging files with other systems

```
Files.readString(p, StandardCharsets.UTF_8);
Files.writeString(p, "Știință, ăîâșț", StandardCharsets.UTF_8);
```

```
newFileReader("vechi.txt", Charset.forName("windows-1250")); // Java 11
```

- `new` `InputStreamReader(System.in, StandardCharsets.UTF_8);`

38

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 39 -->
# 04

### Channels and buffers

39

<!-- page 40 -->
0 4 · C H A N N E L S A N D B U F F E R S

#### NIO: channels and buffers (Java 1.4)

<!-- Start of picture text -->
Channel Buffer Program file · socket block of memory read / write get / put <!-- End of picture text -->

- Data always moves between a channel and a buffer – never directly to the program

- Channels are two-way (read and write), can be non-blocking or asynchronous

- Implementations: `FileChannel` , `SocketChannel` , `ServerSocketChannel` (TCP), `DatagramChannel` (UDP)

- Buffers: `ByteBuffer` (incl. `MappedByteBuffer` for memory-mapped files), `CharBuffer` , `IntBuffer` , `LongBuffer` , `DoubleBuffer` …

40

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 41 -->
0 4 · C H A N N E L S A N D B U F F E R S

#### Buffer state: capacity, position, limit

###### Write mode – after putting 4 bytes

<!-- Start of picture text -->
x x x x position <!-- End of picture text -->

limit

capacity = 10

- capacity – fixed size of the buffer

- position – next cell to write (write mode) or to read (read mode)

###### Read mode – after flip()

<!-- Start of picture text -->
x x x x position limit <!-- End of picture text -->

- limit – how far you may write (= capacity) or read (= bytes written)

- `flip()` – write → read; `clear()` – empty everything; `compact()` – keep unread data, move it to the start

41

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 42 -->
0 4 · C H A N N E L S A N D B U F F E R S

#### Reading a file through a FileChannel

- 1. the channel writes into the buffer

- 2. `flip()` switches the buffer to reading

- 3. the program reads from the buffer

- 4. `clear()` (or `compact()` ) prepares it for writing again

```
try(FileChannel ch = FileChannel.open(Path.of("data/nio-data.txt"))) {
ByteBuffer buf = ByteBuffer.allocate(48);   // capacity 48 bytes
while(ch.read(buf) != -1) {                // channel -> buffer
buf.flip();                             // write -> read mode
while(buf.hasRemaining())
System.out.print((char) buf.get()); // one byte at a time
buf.clear();                            // ready for writing
}
}
```

42

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 43 -->
0 4 · C H A N N E L S A N D B U F F E R S

#### Scatter, gather and channel-to-channel transfer

```
scattering read / gathering write
```

```
direct transfer between channels
```

```
ByteBuffer header = ByteBuffer.allocate(128);
ByteBuffer body   = ByteBuffer.allocate(1024);
ByteBuffer[] bufs = { header, body };
```

```
channel.read(bufs);   // fills header, then body
// ...
channel.write(bufs);  // writes header, then body
```

```
try(FileChannel from = FileChannel.open(Path.of("fromFile.txt"));
FileChannel to = FileChannel.open(Path.of("toFile.txt"),
StandardOpenOption.CREATE, StandardOpenOption.WRITE)) {
to.transferFrom(from, 0, from.size());
}   // may use zero-copy support of the OS
```

i Scatter/gather suits fixed-size message headers; transfers between channels avoid copying data through the Java heap.

43

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 44 -->
0 4 · C H A N N E L S A N D B U F F E R S

#### Asynchronous file I/O (NIO.2)

###### `via a Future`

```
try(varch = AsynchronousFileChannel.open(
path, StandardOpenOption.READ)) {
ByteBuffer buffer = ByteBuffer.allocate(1024);
Future<Integer> op = ch.read(buffer, 0);
```

```
// ... do other work meanwhile ...
```

```
intn = op.get();     // waits only if not done
buffer.flip();
System.out.println(
StandardCharsets.UTF_8.decode(buffer));
```

###### `via a CompletionHandler (callback)`

```
ByteBuffer buffer = ByteBuffer.wrap("test data".getBytes());
ch.write(buffer, 0, buffer,
```

```
newCompletionHandler<Integer, ByteBuffer>() {
@Override
```

```
publicvoidcompleted(Integer result, ByteBuffer att) {
System.out.println("bytes written: "+ result);
}
@Override
```

```
publicvoidfailed(Throwable exc, ByteBuffer att) {
System.out.println("Write failed: "+ exc);
}
```

```
});
```

```
}
```

44

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 45 -->
0 4 · C H A N N E L S A N D B U F F E R S

#### Selectors and non-blocking I/O

- A Selector lets one thread watch many channels (typically network sockets)

- Channels are registered with the selector; `select()` blocks until at least one is ready (new connection, data arrived …)

- The thread then processes only the ready channels – the basis of scalable servers (Netty, Tomcat NIO connector)

- Java 21 virtual threads offer an alternative: plain blocking code, one cheap thread per connection – covered in the concurrency lecture

45

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 46 -->
0 4 · C H A N N E L S A N D B U F F E R S

#### Summary

- Lambdas and method references implement functional interfaces concisely

- Streams: source → lazy intermediate operations → one terminal operation

- Collectors build lists, maps, groups; `Optional` models absence – avoid blind `get()`

- `Path` + `Files` (NIO.2) replace most `java.io.File` code – often in one line

- `Files.lines` / `Files.walk` return streams – close them with try-with-resources

- NIO channels and buffers: `flip()` between writing and reading; async channels and selectors for scalability

46

Advanced Programming Methods  ·  Lecture 5 – Lambdas, Streams and NIO

<!-- page 47 -->
Questions? Next: Concurrency
