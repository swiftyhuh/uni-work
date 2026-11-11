<!-- page 1 -->
## Advanced Programming Methods Lecture 4 – Generics and Collections

```
static <T extends Comparable<? super T>> void sort(List<T> list)
```

<!-- page 2 -->
I N T R O D U C T I O N

#### Lecture overview

01 Wrapper classes and autoboxing

02

Generic classes and methods

03

Bounds and wildcards (PECS)

04

Type erasure and its consequences

The Collections Framework 05

06

Lists, iteration, queues

07

Ordering: Comparable and Comparator

08

Sets and maps

2

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 3 -->
# 01

### Wrapper classes and autoboxing

3

<!-- page 4 -->
0 1 · W R A P P E R C L A S S E S A N D A U T O B O X I N G

#### Wrapper classes

|Primitive|Wrapper|
|---|---|
|`boolean`|`Boolean`|
|`byte`|`Byte`|
|`short`|`Short`|
|`char`|`Character`|
|`int`|`Integer`|
|`long`|`Long`|
|`float`|`Float`|
|`double`|`Double`|

Each primitive type has an immutable wrapper class in `java.lang` . Generic types and collections accept only objects, so they use wrappers.

```
intmax = Integer.MAX_VALUE;           // 2147483647
intx = Integer.parseInt("123");       // String -> int
doubled = Double.parseDouble("9.5");
Integer i = Integer.valueOf(42);       // not new Integer(42) –
// deprecated since Java 9
String bin = Integer.toBinaryString(10); // "1010"
booleancifra = Character.isDigit('7');  // true
```

4

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 5 -->
0 1 · W R A P P E R C L A S S E S A N D A U T O B O X I N G

#### Autoboxing and unboxing – and their traps

```
automatic conversions (Java 5)
```

###### `pitfalls`

```
Stiva<int> s0;              // compile error
Stiva<Integer> si = newStiva<>();
```

```
si.push(23);                // autoboxing:  int -> Integer
intval = si.pop();         // unboxing:    Integer -> int
Character ch = 'x';         // boxing
charc = ch;                // unboxing
```

```
Integer a = 127, b = 127;
booleanr1 = a == b;   // true  –cached -128..127
Integer m = 128, n = 128;
booleanr2 = m == n;   // false –different objects!
booleanr3 = m.equals(n); // true –compare with equals
```

```
Integer z = null;
intk = z;             // NullPointerException
longs = 0;      // use primitives in hot loops,
for(inti = 0; i < 1_000_000; i++) s += i;
```

5

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 6 -->
# 02

### Generic classes and methods

6

<!-- page 7 -->
0 2 · G E N E R I C C L A S S E S A N D M E T H O D S

#### Why generics? A box for any object

- Storing `Object` makes a class reusable for any type…

- …but the type information is lost : every read needs a cast

- A wrong cast compiles and fails only at run time with `ClassCastException`

```
SingleBox.java –without generics
```

```
publicclassSingleBox {
privateObject first;
publicvoidsetFirst(Object o) { first = o; }
publicObject getFirst() { returnfirst; }
```

```
}
```

```
SingleBox ob = newSingleBox();
ob.setFirst(10);                       // stored as Object
Integer a = (Integer) ob.getFirst();   // cast needed
String s = (String) ob.getFirst();     // compiles...
// ...ClassCastException at run time
```

7

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 8 -->
0 2 · G E N E R I C C L A S S E S A N D M E T H O D S

#### A generic class

- `T` is a type parameter ; it is fixed when the class is used: `SingleBox<Integer>`

- The compiler checks types and inserts the casts

- Errors move from run time to compile time

- The diamond `<>` (Java 7) lets the compiler infer the type argument

```
SingleBox.java
```

```
publicclassSingleBox<T> {        // T = "type"
protectedT first;
```

```
publicvoidsetFirst(T t) { first = t; }
publicT getFirst() { returnfirst; }
```

```
}
```

```
SingleBox<Integer> ob = newSingleBox<>();
ob.setFirst(10);
```

```
Integer a = ob.getFirst();   // no cast
String s = ob.getFirst();    // compile error
```

8

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 9 -->
0 2 · G E N E R I C C L A S S E S A N D M E T H O D S

#### Declaring generic classes

- `class Name<T1, T2, ...> { ...`

```
}
```

- By convention, type parameters are single upper-case letters: `E` element, `K` key, `V` value, `T` , `U` , `S` types

```
Stiva.java
```

```
publicclassStiva<E> {
```

```
privatestaticclassNod<T> {
T info;
```

```
Nod<T> next;
```

```
Nod(T info, Nod<T> next) { this.info = info; this.next = next; }
```

```
}
```

```
privateNod<E> top;
```

- Generic types were added in Java 5; unlike C++ templates, no new class is generated per type argument

```
publicvoidpush(E e) { top = newNod<>(e, top); }
publicE pop() {
```

```
if(top == null) thrownewIllegalStateException("stiva vida");
E e = top.info;
top = top.next;
returne;
```

```
}
```

```
publicbooleanisEmpty() { returntop == null; }
```

```
}
```

9

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 10 -->
0 2 · G E N E R I C C L A S S E S A N D M E T H O D S

#### Using generic classes

■ The compiler rejects elements of the wrong type ■ Reading needs no cast ■ Several type parameters: `Dictionar<K, V>`

```
Stiva<String> ss = newStiva<>();
ss.push("Ana");
ss.push("Maria");
ss.push(newPersoana("Ana", 23));   // compile error
String elem = ss.pop();             // no cast
Stiva<Persoana> sp = newStiva<>();
sp.push(newPersoana("Ana", 23));
Dictionar<String, String> dic = newDictionar<>();
dic.add("abc", "ABC");
dic.add(23, "acc");                 // compile error
dic.add("acc", 23);                 // compile error
varst = newStiva<Integer>();      // var: type argument on the right
```

10

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 11 -->
0 2 · G E N E R I C C L A S S E S A N D M E T H O D S

#### Generic classes and inheritance

- A generic subclass can forward type parameters to its superclass…

- …or fix them: `class IntBox extends SingleBox<Integer>`

- A non-generic class can extend a parameterized type

```
PairBox.java
```

```
publicclassPairBox<T1, T2> extendsSingleBox<T1> {
privateT2 second;
```

```
publicPairBox(T1 f, T2 s) {
first = f;
second = s;
}
publicT2 getSecond() { returnsecond; }
publicvoidsetSecond(T2 s) { second = s; }
}
```

```
PairBox<String, Integer> p = newPairBox<>("Ana", 20);
String n = p.getFirst();      // inherited, T1 = String
Integer v = p.getSecond();
```

```
classIntBox extendsSingleBox<Integer> { }
```

11

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 12 -->
0 2 · G E N E R I C C L A S S E S A N D M E T H O D S

#### Generic methods

■ A method can declare its own type parameters, before the return type: `<T> void f(T x)`

- Generic methods can live in non-generic classes

- Static methods cannot use the type parameters of their class – they declare their own

```
GenericMethods.java
```

```
publicclassGenericMethods {
```

```
public<T> voidprint(T x) {
System.out.println(x);
}
```

```
publicstatic<T> voidcopy(T[] elems, Stiva<T> st) {
for(T e : elems)
st.push(e);
}
}
```

12

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 13 -->
0 2 · G E N E R I C C L A S S E S A N D M E T H O D S

#### Calling generic methods

■ Usually the compiler infers the type arguments from the actual arguments ■ They can also be given explicitly: `obj.<Type>method(...)` , `Class.<Type>method(...)` , `this.<Type>method(...)`

```
GenericMethods g = newGenericMethods();
g.print(23);                            // T = Integer
g.print("ana");                         // T = String
g.<Persoana>print(newPersoana("Ana", 23)); // explicit
Integer[] ielem = {2, 3, 4};
Stiva<Integer> st = newStiva<>();
GenericMethods.copy(ielem, st);           // inferred
GenericMethods.<Integer>copy(ielem, st);  // explicit
```

13

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 14 -->
0 2 · G E N E R I C C L A S S E S A N D M E T H O D S

#### Raw types: legacy – avoid them

- A raw type is a generic class used without type arguments: `SingleBox`

- Allowed only for compatibility with preJava 5 code

- Raw types switch off type checking – the compiler can only warn

```
SingleBox<String> stringBox = newSingleBox<>();
SingleBox rawBox = stringBox;       // raw type
rawBox.setFirst(8);                 // warning: unchecked call
String s = stringBox.getFirst();    // ClassCastException!
SingleBox<Integer> intBox = newSingleBox(); // warning:
// unchecked conversion
```

- Treat unchecked warnings as errors

14

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 15 -->
# 03

### Bounds and wildcards

15

<!-- page 16 -->
0 3 · B O U N D S A N D W I L D C A R D S

#### Bounded type parameters

■ Without a bound, `E` offers only the methods of `Object` – no `compareTo`

- `E extends Comparable<E>` : `E` must be comparable with itself

```
ListOrd.java –a sorted list
```

```
publicclassListOrd<E extendsComparable<E>> {
```

```
privatestaticclassNod<E> {
E info; Nod<E> next;
```

```
Nod(E info, Nod<E> next) { this.info = info; this.next = next; }
}
```

```
privateNod<E> head;
```

■ General form: `T extends C & I1 & … & In` (class first, then interfaces)

```
publicvoidadd(E elem) {
if(head == null|| elem.compareTo(head.info) < 0) {
head = newNod<>(elem, head);       // new first element
return;
}
```

```
Nod<E> p = head;
```

```
while(p.next != null&& p.next.info.compareTo(elem) <= 0)
p = p.next;
```

```
p.next = newNod<>(elem, p.next);
}
```

```
}
```

16

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 17 -->
0 3 · B O U N D S A N D W I L D C A R D S

#### Bounds on generic methods

- The bound makes `compareTo` available inside the method

- Calls with non-comparable types are rejected at compile time

- The JDK uses the more flexible `<T extends Comparable<? super T>>` – explained by the wildcard slides

```
publicstatic<T extendsComparable<T>> T max(T[] v) {
T m = v[0];
for(T x : v)
if(x.compareTo(m) > 0)
m = x;
returnm;
}
```

```
max(newInteger[]{3, 9, 2});          // 9
max(newString[]{"pere", "mere"});    // "pere"
max(newObject[]{1, 2});              // compile error
```

17

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 18 -->
0 3 · B O U N D S A N D W I L D C A R D S

#### Generics are invariant

```
suppose SingleBox<String> were a SingleBox<Object>
```

```
arrays are covariant –checked at run time
```

```
SingleBox<String> bs = newSingleBox<>();
SingleBox<Object> bo = bs;   // compile error –and rightly so:
bo.setFirst(23);             // an Integer would enter...
String s = bs.getFirst();    // ...a box of String
```

```
Object[] a = newString[2];  // compiles
a[0] = 23;                   // ArrayStoreException
```

Even if `Sub` is a subtype of `Super` , `G<Sub>` is not a subtype of `G<Super>` . A method `void` ! `print(SingleBox<Object> b)` does not accept a `SingleBox<String>` – wildcards solve this.

18

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 19 -->
0 3 · B O U N D S A N D W I L D C A R D S

#### The unbounded wildcard ?

- `SingleBox<?>` = a box of some unknown type

- Every `SingleBox<X>` is a `SingleBox<?>`

- Elements can be read as `Object` ; nothing except `null` can be written

```
staticvoidafiseaza(SingleBox<?> b) {
Object o = b.getFirst();    // OK: read as Object
System.out.println(o);
b.setFirst("x");            // compile error
b.setFirst(null);           // the only accepted value
}
```

```
afiseaza(newSingleBox<String>());
afiseaza(newSingleBox<Integer>());
```

19

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 20 -->
0 3 · B O U N D S A N D W I L D C A R D S

#### Upper bounded wildcards: ? extends T

`■ SingleBox<? extends Number>` : a box of `Number` or a subtype ■ Safe to read as `Number`

- Not safe to write : it might be a box of `Double`

- Covariant subtyping: a _producer_ of `Number` s

```
staticdoublevaloare(SingleBox<? extendsNumber> b) {
Number n = b.getFirst();    // OK: read as Number
b.setFirst(3);              // compile error
returnn.doubleValue();
}
valoare(newSingleBox<Integer>());   // OK
valoare(newSingleBox<Double>());    // OK
valoare(newSingleBox<String>());    // compile error
SingleBox<? extendsNumber>  x = newSingleBox<Integer>(); // OK
SingleBox<? extendsInteger> y = newSingleBox<Number>();  // error
```

20

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 21 -->
0 3 · B O U N D S A N D W I L D C A R D S

#### Lower bounded wildcards: ? super T

- `SingleBox<? super Integer>` : a box of `Integer` or a supertype

- ■ Safe to write an `Integer` ■ Reading gives only `Object`

- Contravariant subtyping: a _consumer_ of `Integer` s

```
staticvoidpune(SingleBox<? superInteger> b, intx) {
b.setFirst(x);              // OK: write an Integer
Object o = b.getFirst();    // read only as Object
}
pune(newSingleBox<Integer>(), 1);   // OK
pune(newSingleBox<Number>(), 1);    // OK
pune(newSingleBox<Object>(), 1);    // OK
pune(newSingleBox<Double>(), 1);    // compile error
```

21

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 22 -->
0 3 · B O U N D S A N D W I L D C A R D S

#### PECS: Producer Extends, Consumer Super

- A parameter that produces values for you → `? extends T`

- A parameter that consumes values from you → `? super T`

- Both read and write → no wildcard

```
// java.util.Collections
```

```
static<T> voidcopy(List<? superT> dest,
List<? extendsT> src)
```

```
static<T extendsComparable<? superT>>
voidsort(List<T> list)
```

<!-- Start of picture text -->
SingleBox<?> SingleBox<? extends Number> SingleBox<? super Integer> SingleBox<Number> SingleBox<Integer> <!-- End of picture text -->

_arrows: "is a subtype of"_

22

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 23 -->
# 04

### Type erasure

23

<!-- page 24 -->
0 4 · T Y P E E R A S U R E

#### Type erasure

■ The compiler checks types, then erases type parameters (replaced by their bound, usually `Object` ) and inserts casts

■ One class at run time for all parameterizations – reason: compatibility with pre-generics code

###### `source`

###### `after erasure (conceptually)`

```
publicclassA {
publicString f(Integer ix) {
Stiva<String> st = newStiva<>();
Stiva sts = st;      // raw: warning
sts.push(ix);
returnst.pop();
}
}
```

```
publicclassA {
publicString f(Integer ix) {
Stiva st = newStiva();
Stiva sts = st;
sts.push(ix);
return(String) st.pop();  // ClassCastException
}
}
```

24

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 25 -->
0 4 · T Y P E E R A S U R E

#### What erasure forbids – and workarounds

|Not allowed|Why|Workaround|
|---|---|---|
|`Stiva<int>`|type arguments must be reference types|`Stiva<Integer>`+ autoboxing|
|`new T()`|T is unknown at run time|pass a`Supplier<T>`(Lecture 5) or `Class<T>`|
|`new T[n]`|an array needs its runtime element type|`(T[]) new Object[n]`or an `ArrayList<T>`|
|`o instanceof Stiva<String>` (o : Object)|the type argument is erased – the check would be unchecked|`o instanceof Stiva<?>`|
|`static T camp;`|static members are shared by all parameterizations|–|
|`class Ex<T> extends` `Exception`|catch needs the runtime type|–|

25

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 26 -->
0 4 · T Y P E E R A S U R E

#### Generic arrays: two workarounds

```
Object[] + cast on read
```

```
Array.newInstance with Class<E>
```

```
publicclassStiva<E> {
privateObject[] elems = newObject[10];
privateinttop;
publicvoidpush(E elem) {
elems[top++] = elem;
}
@SuppressWarnings("unchecked")
publicE pop() {
return(E) elems[--top];   // safe: only E's
}                              // were pushed
}
```

```
publicclassStiva<E> {
privateE[] elems;
privateinttop;
@SuppressWarnings("unchecked")
publicStiva(Class<E> tip) {
elems = (E[]) Array.newInstance(tip, 10);
}
}
Stiva<Integer> si = newStiva<>(Integer.class);
```

i In practice: use `ArrayList<E>` (later in this lecture) and avoid generic arrays altogether.

26

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 27 -->
# 05

### The Collections Framework

27

<!-- page 28 -->
0 5 · T H E C O L L E C T I O N S F R A M E W O R K

#### The Java Collections Framework

A collection is an object that holds references to other objects. The framework lives in `java.util` and has three parts:

<!-- Start of picture text -->
what <!-- End of picture text -->

##### Interfaces

Define the operations and the contract of each kind of collection: `List` , `Set` , `Queue` , `Map` , …

```
how
```

Implementations

Reusable classes implementing the interfaces: `ArrayList` , `HashSet` , `TreeMap` , `ArrayDeque` , …

```
tools
```

##### Algorithms

Polymorphic utility methods: sorting, searching, reversing, shuffling – in `Collections` and in the interfaces themselves.

Program to an interface: declare `List<String> l = new ArrayList<>();` – the code depends only on `List` , so the i implementation can change in one place.

28

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 29 -->
0 5 · T H E C O L L E C T I O N S F R A M E W O R K

#### The interface hierarchy

<!-- Start of picture text -->
Iterable<E> Collection<E> Map<K,V> SequencedCollection<E> Set<E> Queue<E> SequencedMap<K,V> List<E> Deque<E> SequencedSet<E> SortedMap<K,V> Map  is  not  a  Collection . The  Sequenced…  interfaces were added in SortedSet<E> Java 21 for collections with a defined encounter order. <!-- End of picture text -->

29

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 30 -->
0 5 · T H E C O L L E C T I O N S F R A M E W O R K

#### Collection<E>: the common contract

Method Meaning add elements; return `true` if the `add(E e)` / `addAll(c)` collection changed `remove(Object o)` / remove elements `removeIf(pred) contains(Object o)` membership test – uses `equals` `size()` / `isEmpty()` / `clear()` size information, emptying `iterator()` traversal (also used by for-each) `stream()` start a stream pipeline (Lecture 5) `toArray()` / copy into an array `toArray(IntFunction)`

```
Collection<String> c = newArrayList<>();
c.add("mere");
c.add("pere");
c.contains("pere");    // true
c.remove("mere");      // true
c.size();              // 1
String[] a = c.toArray(String[]::new);
```

30

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 31 -->
0 5 · T H E C O L L E C T I O N S F R A M E W O R K

#### Creating collections (Java 9+)

- `List.of` , `Set.of` , `Map.of` create unmodifiable collections

- Modifying them throws `UnsupportedOperationException` ; `null` elements are rejected

- For a modifiable collection, copy: `new ArrayList<>(List.of(...))`

```
List<String> fructe = List.of("mere", "pere", "prune");
Set<Integer> prime = Set.of(2, 3, 5, 7);
Map<String, Integer> stoc = Map.of("mere", 10, "pere", 4);
```

```
fructe.add("kiwi");        // UnsupportedOperationException
List<String> lista = newArrayList<>(fructe);
lista.add("kiwi");         // OK
```

```
List<String> copie = List.copyOf(lista);   // unmodifiable copy
```

- `Arrays.asList` gives a fixed-size view of an array

31

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 32 -->
# 06

### Lists, iteration and queues

32

<!-- page 33 -->
0 6 · L I S T S , I T E R A T I O N , Q U E U E S

#### List<E>: an indexed sequence

- Ordered, allows duplicates , grows automatically

- Index-based access: `get` , `set` , `add(i, e)` , `remove(int i)`

- Search: `indexOf` , `lastIndexOf` , `contains`

- Views: `subList(from, to)`

```
List<String> l = newArrayList<>();
l.add("Ana");                 // [Ana]
l.add("Ion");                 // [Ana, Ion]
l.add(0, "Maria");            // [Maria, Ana, Ion]
l.set(1, "Ioana");            // [Maria, Ioana, Ion]
String s = l.get(2);          // "Ion"
l.remove("Maria");            // [Ioana, Ion]
l.indexOf("Ion");             // 1
```

```
List<Integer> v = newArrayList<>(List.of(10, 20, 30));
v.remove(1);                  // by index -> [10, 30]
v.remove(Integer.valueOf(30)); // by value -> [10]
```

33

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 34 -->
0 6 · L I S T S , I T E R A T I O N , Q U E U E S

#### Choosing a List implementation

|Operation|ArrayList (dynamic array)|LinkedList (doubly linked)|
|---|---|---|
|`get(i)` /`set(i, e)`|O(1)|O(n)|
|`add(e)` at the end|amortized O(1)|O(1)|
|insert / remove in the middle|O(n) – shifts elements|O(1) once positioned, O(n) to get there|
|memory per element|compact|a node object with two links|

Use `ArrayList` by default. For stacks and queues use `ArrayDeque` . `Vector` and `Stack` are legacy synchronized i classes – avoid them in new code.

34

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 35 -->
0 6 · L I S T S , I T E R A T I O N , Q U E U E S

#### Traversal with Iterator

- An `Iterator` traverses any collection, whatever its implementation

- `hasNext()` – more elements? `next()` – the next one; `remove()` – removes the last returned element

- The for-each statement uses an iterator behind the scenes

- Code depends only on the interface – program to an interface!

```
publicstatic<T> voidlist(Collection<T> items) {
Iterator<T> it = items.iterator();
while(it.hasNext()) {
T item = it.next();
System.out.println(item);
}
}
```

```
equivalent for-each
```

```
for(T item : items)
System.out.println(item);
```

35

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 36 -->
0 6 · L I S T S , I T E R A T I O N , Q U E U E S

#### Making your own class Iterable

■ for-each works on any `Iterable<T>` – a type with a single method `iterator()`

```
Stiva.java
```

```
publicclassStiva<E> implementsIterable<E> {
// ... Nod<E>, top, push, pop as before
```

■ Here the generic `Stiva<E>` (section 02) returns an anonymous iterator (Lecture 2)

```
@Override
publicIterator<E> iterator() {
returnnewIterator<>() {
privateNod<E> crt = top;
publicbooleanhasNext() { returncrt != null; }
publicE next() {
```

```
if(crt == null) thrownewNoSuchElementException();
E e = crt.info;
crt = crt.next;
returne;
}
};
}
```

```
}
```

```
for(String s : stiva)          // now possible
System.out.println(s);
```

36

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 37 -->
0 6 · L I S T S , I T E R A T I O N , Q U E U E S

#### Removing elements while iterating

✗ `ConcurrentModificationException`

```
for(String s : lista)
if(s.isBlank())
lista.remove(s);
// the list changes behind
// the iterator's back
```

✓ `Iterator.remove`

```
Iterator<String> it = lista.iterator();
while(it.hasNext())
if(it.next().isBlank())
it.remove();
```

✓ `Java 8: removeIf`

```
lista.removeIf(s -> s.isBlank());
// or, shorter:
lista.removeIf(String::isBlank);
```

i `removeIf` takes a lambda – the topic of Lecture 5. Most modern collection code looks like this.

37

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 38 -->
0 6 · L I S T S , I T E R A T I O N , Q U E U E S

#### Queues and deques

```
ArrayDeque as stack and as queue
```

```
Deque<Integer> stiva = newArrayDeque<>();
stiva.push(1); stiva.push(2); stiva.push(3);
stiva.pop();          // 3 –LIFO
Deque<String> coada = newArrayDeque<>();
coada.offer("a"); coada.offer("b");
coada.poll();         // "a" –FIFO
coada.peek();         // "b" –look, don't remove
```

```
PriorityQueue –smallest first
```

```
Queue<Integer> pq = newPriorityQueue<>();
pq.addAll(List.of(5, 1, 4, 2));
while(!pq.isEmpty())
System.out.print(pq.poll() + " ");
// 1 2 4 5
```

38

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 39 -->
0 6 · L I S T S , I T E R A T I O N , Q U E U E S

#### Sequenced collections (Java 21)

- Uniform access to the first and last element of ordered collections

`■ getFirst` , `getLast` , `addFirst` , `addLast` , `removeFirst` , `removeLast` , `reversed()`

■ Implemented by `List` , `Deque` , `LinkedHashSet` , `TreeSet` ; maps get `firstEntry` , `lastEntry` , `reversed()`

```
List<String> l = newArrayList<>(List.of("a", "b", "c"));
l.getFirst();          // "a"   (before: l.get(0))
l.getLast();           // "c"   (before: l.get(l.size() -1))
l.addFirst("z");       // [z, a, b, c]
l.reversed();          // [c, b, a, z] –a view, no copy
LinkedHashMap<String, Integer> m = newLinkedHashMap<>();
m.put("x", 1); m.put("y", 2);
m.firstEntry();        // x=1
m.lastEntry();         // y=2
```

39

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 40 -->
# 07

### Ordering: Comparable and Comparator

40

<!-- page 41 -->
0 7 · O R D E R I N G : C O M P A R A B L E A N D C O M P A R A T O R

#### Comparable<T>: natural ordering

■ One method: `int compareTo(T other)` – negative, zero or positive

■ Defines the natural ordering of a type ( `String` , `Integer` , `LocalDate` …) ■ Use `Integer.compare` / `Long.compare` – subtraction ( `a - b` ) can overflow

■ Should be consistent with `equals`

```
Money.java
```

```
publicrecordMoney(intlei, intbani) implementsComparable<Money> {
publicMoney {                       // keeps compareTo consistent with equals
if(bani < 0|| bani > 99) thrownewIllegalArgumentException();
}
publicinttotal() { returnlei * 100+ bani; }
@Override
publicintcompareTo(Money o) {
returnInteger.compare(total(), o.total());
}
@Override
publicString toString() { return"%d.%02d".formatted(lei, bani); }
}
newMoney(100, 0).compareTo(newMoney(50, 0));   // 1
```

41

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 42 -->
0 7 · O R D E R I N G : C O M P A R A B L E A N D C O M P A R A T O R

#### Sorting by natural order

- `Collections.sort(list)` or `list.sort(null)` – stable sort (TimSort, a merge sort variant)

- Compiles only if the elements are `Comparable` :

   - `<T extends Comparable<? super T>> void sort(List<T> list)` – PECS from section 03

```
List<Money> funds = newArrayList<>();
funds.add(newMoney(100, 0));
funds.add(newMoney(5, 50));
funds.add(newMoney(-40, 0));
funds.add(newMoney(5, 50));
funds.add(newMoney(30, 0));
Collections.sort(funds);
System.out.println(funds);
// [-40.00, 5.50, 5.50, 30.00, 100.00]
recordCD(String titlu, String artist, Money pret) { }
List<CD> albums = newArrayList<>();
Collections.sort(albums);   // compile error: CD is not Comparable
```

42

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 43 -->
0 7 · O R D E R I N G : C O M P A R A B L E A N D C O M P A R A T O R

#### Comparator<T>: alternative orderings

■ A separate object that compares two values: `int compare(T a, T b)`

- Use it when the type has no natural order – or you need another order

- A given comparator overrides natural ordering

```
PriceComparator.java
```

```
publicclassPriceComparator implementsComparator<CD> {
@Override
publicintcompare(CD c1, CD c2) {
returnc1.pret().compareTo(c2.pret());
}
}
```

```
List<CD> albums = newArrayList<>();
albums.add(newCD("Street Signs", "Ozomatli", newMoney(3, 50)));
albums.add(newCD("Jazzinho", "Jazzinho", newMoney(2, 80)));
albums.add(newCD("Space Cowboy", "Jamiroquai", newMoney(5, 0)));
albums.sort(newPriceComparator());   // or Collections.sort(albums, ...)
```

43

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 44 -->
# 08

### Sets and maps

44

<!-- page 45 -->
0 8 · S E T S A N D M A P S

#### Set<E>: no duplicates

- `e1` and `e2` are duplicates if `e1.equals(e2)`

- `HashSet` – hashing, O(1) operations, unspecified order

- `LinkedHashSet` – keeps insertion order

- `TreeSet` – sorted (red-black tree), O(log n)

```
Set<String> words = newHashSet<>();
words.add("Bats");
words.add("Ants");
words.add("Crabs");
words.add("Ants");                 // returns false
System.out.println(words.size());  // ?
for(String w : words)
System.out.println(w);         // order?
Set<String> sorted = newTreeSet<>(words);  // Ants, Bats, Crabs
```

45

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 46 -->
0 8 · S E T S A N D M A P S

#### Hash-based collections need equals and hashCode

```
class without equals/hashCode
```

```
record: correct by construction
```

```
classPunct {
intx, y;
Punct(intx, inty) { this.x = x; this.y = y; }
}
Set<Punct> s = newHashSet<>();
s.add(newPunct(1, 2));
s.add(newPunct(1, 2));
s.size();                     // 2 –"duplicates"!
s.contains(newPunct(1, 2));  // false
```

```
recordPunct(intx, inty) { }
Set<Punct> s = newHashSet<>();
s.add(newPunct(1, 2));
s.add(newPunct(1, 2));
s.size();                     // 1
```

Do not modify an object while it is a key in a `HashSet` / `HashMap` – its hash code changes and the element becomes ! unreachable.

46

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 47 -->
0 8 · S E T S A N D M A P S

#### TreeSet: sorted – by natural order or a Comparator

■ No natural order? Pass a `Comparator` to the constructor

■ Caution: `TreeSet` considers `x` and `y` duplicates when `compare(x, y) == 0` – not when `equals` is true `■ first()` , `last()` , `headSet` , `tailSet` , `ceiling` , `floor` …

```
Set<CD> albums = newTreeSet<>(newPriceComparator());
albums.add(newCD("Street Signs", "O", newMoney(3, 50)));
albums.add(newCD("Jazzinho", "J", newMoney(2, 80)));
albums.add(newCD("Space Cowboy", "J", newMoney(5, 0)));
albums.add(newCD("Maiden Voyage", "HH", newMoney(4, 0)));
albums.add(newCD("Here's the Deal", "LS", newMoney(2, 80)));
System.out.println(albums.size());    // ?
for(CD a : albums)
System.out.println(a.titlu());    // ?
```

47

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 48 -->
0 8 · S E T S A N D M A P S

#### Map<K,V>: from keys to values

■ Unique keys, each mapped to one value `Map<String, Integer> directory =` `new` `HashMap<>();` – like an array indexed by objects `directory.put("Mum", 9998888); directory.put("Dad", 9998888); ■ put` returns the previous value (or `directory.put("Bob", 12345678); null` ) `directory.put("Edward", 5553535); directory.put("Bob", 1000000);` _`// returns 12345678`_ `■ get` returns `null` for a missing key – or use `getOrDefault System.out.println(directory.size());` `// ?` `directory.get("Bob");` `// ?` `■ keySet()` , `values()` , `entrySet() directory.get("Ann");` _`// null`_ are views of the map `directory.getOrDefault("Ann", 0);` _`// 0`_ `directory.containsKey("Dad");` _`// true`_

48

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 49 -->
0 8 · S E T S A N D M A P S

#### HashMap, LinkedHashMap, TreeMap

- `HashMap` – fastest, key order unspecified

```
Map<String, Integer> directory = newTreeMap<>();
```

```
// ... same puts as before
```

- `LinkedHashMap` – insertion order (or access order: LRU caches)

- `TreeMap` – keys sorted; natural order or a `Comparator`

■ Others: `EnumMap` , `ConcurrentHashMap` (concurrency lecture)

```
for(Map.Entry<String, Integer> e : directory.entrySet())
System.out.println(e.getKey() + "'s #: "+ e.getValue());
// Bob's #: 1000000
// Dad's #: 9998888
// Edward's #: 5553535
// Mum's #: 9998888
```

```
System.out.println(directory.values());
// [1000000, 9998888, 5553535, 9998888] –in key order
```

49

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 50 -->
0 8 · S E T S A N D M A P S

#### Which collection should I use?

|I need …|Use|Notes|
|---|---|---|
|an indexed list|`ArrayList`|the default choice|
|a stack or a FIFO queue|`ArrayDeque`|faster than`Stack`/`LinkedList`|
|the smallest/largest first|`PriorityQueue`|a binary heap|
|unique elements|`HashSet`|`LinkedHashSet`to keep insertion order|
|unique elements, sorted|`TreeSet`|range queries:`headSet`,`ceiling`|
|key → value lookup|`HashMap`|`LinkedHashMap`for predictable order|
|key → value, sorted keys|`TreeMap`|`firstKey`,`floorKey`,`subMap`|
|a fixed, read-only collection|`List.of`/`Set.of`/`Map.of`|unmodifiable|

50

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 51 -->
0 8 · S E T S A N D M A P S

#### java.util.Collections: ready-made algorithms

- Sorting, searching, min/max, reversing, shuffling, frequency …

- Wrappers: `unmodifiableList` , `synchronizedList`

- Don't reimplement what the library already offers

```
List<Integer> l = newArrayList<>(List.of(5, 3, 9, 3, 1));
Collections.sort(l);                     // [1, 3, 3, 5, 9]
Collections.binarySearch(l, 5);          // 3
Collections.max(l);                      // 9
Collections.frequency(l, 3);             // 2
Collections.reverse(l);                  // [9, 5, 3, 3, 1]
Collections.swap(l, 0, 4);               // [1, 5, 3, 3, 9]
Collections.shuffle(l);                  // random order
List<Integer> ro = Collections.unmodifiableList(l); // read-only view
List<String> z = Collections.nCopies(3, "ab");      // [ab, ab, ab]
```

51

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 52 -->
0 8 · S E T S A N D M A P S

#### Summary

- Wrappers make primitives usable as objects – watch out for `==` and `null` unboxing

- Generics move type errors to compile time; bounds unlock methods of the bound

- Generics are invariant – use `? extends` for producers, `? super` for consumers (PECS)

- Type information is erased at run time: no `new T()` , no `new T[]` , no `instanceof G<String>`

- Program to interfaces: `List` , `Set` , `Map` , `Deque` – pick implementations by access pattern

- Hash collections need consistent `equals` / `hashCode` ; sorted ones need `Comparable` or a `Comparator`

52

Advanced Programming Methods  ·  Lecture 4 – Generics and Collections

<!-- page 53 -->
## Questions?

Next: Lecture 5 – Lambdas, Streams and NIO
