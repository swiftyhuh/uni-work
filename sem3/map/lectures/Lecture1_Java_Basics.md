<!-- page 1 -->
Advanced Programming Methods Lecture 1 – Java Basics

```
public static void main(String[] args)
```

<!-- page 2 -->
I N T R O D U C T I O N

#### Lecture overview

01 Recap OO concepts

02

Classes and objects

03

Primitive data and var

05

06

07

Arrays and for-each

Strings, StringBuilder, text blocks

Modern control flow: switch expressions

04 Passing arguments

2

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 3 -->
I N T R O D U C T I O N

#### Course overview

Object-oriented languages – Java part of the course:

Join the course team on MS Teams

```
s0p8jb7
```

team code

```
L1
```

Java basics: classes, objects, arrays, strings

`L2` OOP design: inheritance, interfaces, records, enums, sealed types

`L3` Exceptions and generics

_All examples target Java 25 (current LTS) unless stated otherwise._

`L4` Collections, lambdas and streams

`L5` I/O, NIO.2 and serialization

```
Next
```

Concurrency · GUI · Metaprogramming

3

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 4 -->
I N T R O D U C T I O N

#### Java today: a new release every 6 months

2014 · LTS 2018 · LTS ~~8 11~~

2021 · LTS ~~17~~

2023 · LTS

~~21~~

2025 · LTS

~~2~~ 5

lambdas, streams, default var, String/Files helpers, HTTP records, sealed types, text pattern matching for switch, compact source files, flexible methods client blocks, switch expressions virtual threads, sequenced constructor bodies, stream collections gatherers

_Between LTS versions, features arrive as previews first and become final later. This course uses only final features._

4

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 5 -->
I N T R O D U C T I O N

#### Java references

Book

Bruce Eckel – _Thinking in Java_

Classic introduction to OO thinking in Java.

Book

Joshua Bloch – _Effective Java_ (3rd ed.)

Best practices; read after the basics.

Online

dev.java/learn

Official, up-to-date Java tutorials (successor of The Java Tutorials).

Docs

docs.oracle.com/en/java/javase/25

Java SE 25 (current LTS) – API and language specification.

_…and any good Java book or tutorial._

5

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 6 -->
I N T R O D U C T I O N

#### Java technology: compile once, run anywhere

HelloWorld.java source code

JDK = compiler + tools + JRE JRE = JVM + standard library

javac HelloWorld.class compiler bytecode

JVM JVM

Windows

Linux

The same `.class` file runs unchanged on every platform that has a Java Virtual Machine (JVM). The JVM interprets bytecode and JIT-compiles hot code to native instructions.

JVM macOS

6

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 7 -->
I N T R O D U C T I O N

#### A simple Java program

###### Compilation

```
Test.java
```

`■ javac Test.java` → produces `Test.class`

###### Execution

```
■java Test
```

- `java Test ana 1 2 3` → `args = {"ana","1","2","3"}`

```
publicclassTest {
publicstaticvoidmain(String[] args) {
System.out.println("Hello");
for(String el : args)
System.out.println(el);
}
}
```

###### Shortcut (Java 11+)

- `java Test.java` compiles in memory and runs

i Command-line arguments are always strings. Convert them with `int value = Integer.parseInt(args[i]);`

7

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 8 -->
I N T R O D U C T I O N

#### Trying code quickly: jshell and source files

```
jshell (Java 9+)
```

```
Hello.java –compact source file (Java 25)
```

```
$ jshell
jshell> intx = 21* 2
x ==> 42
jshell> "Java".repeat(3)
$2==> "JavaJavaJava"
jshell> /exit
```

```
voidmain() {
IO.println("Hello, students!");
}
// run directly, no javac step:
// $ java Hello.java
```

Compact source files and `jshell` are great for experiments. Real programs – and this course – use classes, packages and i the full `public static void main(String[] args)` .

8

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 9 -->
0 1 · R E C A P O O C O N C E P T S

#### Object-oriented programming concepts

C Class

A new data type – the implementation of an abstract data type (ADT).

Encapsulation

##### E

Data (state) and operations (behaviour) bundled together; internal details are hidden.

O Object

An instance of a class. Objects interact by sending messages.

Inheritance

I

Reuse code by defining a new class as an extension of an existing one.

M Message

The way objects communicate: a message is a method call.

P Polymorphism

The ability of an entity to behave differently depending on the context.

9

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 10 -->
# 02 Java classes and objects

10

<!-- page 11 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Class declaration

- A `public` class must be saved in a file with the same name: `ClassName.java`

- A `.java` file may contain several classes, but at most one can be `public`

```
ClassName.java
```

- `[` `public` `] [` `final` `]` `class` `ClassName { [fields declaration]`

   - `[methods declaration and implementation]`

- `}`

###### Java vs. C++

- no separate header and implementation files ( `.h` / `.cpp` )

- methods are implemented where they are declared

- a class declaration does not end with `;`

11

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 12 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Class declaration – examples

```
Persoana.java
```

###### `Complex.java`

```
publicclassPersoana {
//...
}
```

<!-- Start of picture text -->
class Rational { //... } class Natural { //... } <!-- End of picture text -->

```
publicclassComplex {   // the only public class
//...
}
```

? `Complex.java` compiles into three files: `Rational.class` , `Natural.class` and `Complex.class` .

12

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 13 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Fields

- Fields can be declared anywhere inside the class body

- The access modifier ( `public` , `protected` , `private` ) must be given for each field

- No access modifier → the field is visible only inside the same package (package-private)

```
syntax
```

```
Persoana.java / Punct.java
```

- `...` `class` `ClassName {`

   - `[access_modifier] [` `static` `] [` `final` `] Type name [= init_val];`

- `}`

```
publicclassPersoana {
privateString nume;
privateintvarsta;
```

```
}
publicclassPunct {
privatedoublex;
privatedoubley;
}
```

13

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 14 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Initializing fields

- 1. At the declaration site

   - `private double x = 0;`

- 2. In an initialization block

   - runs before the constructor body, for every new object

- 3. In a constructor

- A field that is not explicitly initialized gets the default value of its type ( `0` , `false` , `null` , …)

```
Rational.java
```

```
publicclassRational {
privateintnumarator;
privateintnumitor;
```

```
{                  // initialization block
numarator = 0;
numitor = 1;
}
//...
```

```
}
```

14

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 15 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Constructors

- Executed after memory for the object is allocated, to initialize it

- Same name as the class (case-sensitive)

- No return type – not even `void`

```
syntax
```

   - `[...]` `class` `ClassName {`

      - `[access_modifier] ClassName([formal_params]) {` _`// body`_

      - `}`

   - `}`

- If a class declares no constructor, the compiler generates a _default constructor_ : no parameters, same access as the class

- _`// access_modifier: public | protected | private`_

```
// formal_params: Type1 n1[, Type2 n2, ...]
```

15

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 16 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Overloading constructors

■ A class may have several constructors with different parameter lists

■ The compiler picks the one matching the arguments of `new`

```
Complex.java
```

```
publicclassComplex {
privatedoublereal, imag;
publicComplex() {                  // no-arg constructor
real = 0;
imag = 0;
}
publicComplex(doublereal) {
this.real = real;
imag = 0;
}
publicComplex(doublereal, doubleimag) { /*...*/}
publicComplex(Complex c) { /*...*/}  // copy constructor
}
```

16

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 17 -->
0 2 · C L A S S E S A N D O B J E C T S

#### The keyword this

- `this` refers to the current (receiver) object

- Used to access the fields and methods of the current object

■ Typical use: a parameter shadows a field with the same name → `this.real = real`

`■ return this;` allows chained calls

```
Complex.java
```

```
publicclassComplex {
privatedoublereal, imag;
publicComplex(doublereal) {
this.real = real;
imag = 0;
}
publicComplex(doublereal, doubleimag) {
this.real = real;
this.imag = imag;
}
publicComplex suma(Complex c) {
//...
returnthis;
}
```

```
}
```

17

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 18 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Calling another constructor: this(...)

`■ this(...)` calls another constructor of the same class

- Must come before any use of `this` : traditionally the first statement ; since Java 25, statements that do not touch `this` may precede it

- Avoids duplicating initialization code

```
Complex.java
```

```
publicclassComplex {
privatedoublereal, imag;
publicComplex() {
this(0, 0);
```

```
}
publicComplex(doublereal) {
this(real, 0);
```

```
}
```

```
publicComplex(doublereal, doubleimag) {
this.real = real;
this.imag = imag;
}
```

```
}
```

18

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 19 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Creating objects: new

- `new` allocates memory for the object on the heap and then calls a constructor

- A variable of a class type holds a reference , not the object itself

```
Punct p = newPunct();            // parentheses are mandatory
Complex c1 = newComplex();
Complex c2 = newComplex(2.3);
Complex c3 = newComplex(1, 1.5);
```

```
Complex cc;     // a field would be null; a local variable is uninitialized
cc = c3;        // c3 and cc refer to the same object in memory
```

19

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 20 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Static fields

- A `static` field belongs to the class , not to an object

- It is allocated once and shared by all instances

```
Natural.java
```

```
publicclassNatural {
privatelongval;
publicstaticfinallongMAX = Long.MAX_VALUE; // 2^63-1
}
```

- Typical uses: constants ( `static final` ) and counters

###### `Produs.java`

```
publicclassProdus {
privatestaticlongcounter;
privatefinallongid = counter++;   // unique id per object
publicString toString() {
return""+ id;
}
}
```

20

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 21 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Defining methods

```
syntax
```

```
[...] classClassName {
[access_modifier] ResultType methodName([formal_params]) {
// method body
}
```

```
}
```

`ResultType` can be any primitive type, reference type, array type, or `void` . i No access modifier → the method can be called from any class in the same package . If the return type is not `void` , every execution path must end with a `return` statement.

21

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 22 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Defining methods – example

- Getters / setters give controlled access to `private` fields

■ Methods can take objects of their own class as parameters: `maiTanara(Persoana p)`

■ A private field of `p` is accessible here – access control is per class , not per object

```
Persoana.java
```

```
publicclassPersoana {
privateString nume;
privateintvarsta;
```

```
publicPersoana() {
this("", 0);
}
publicPersoana(String nume, intvarsta) {
this.nume = nume;
this.varsta = varsta;
}
publicintgetVarsta() { returnvarsta; }
publicvoidsetNume(String nume) { this.nume = nume; }
publicbooleanmaiTanara(Persoana p) {
returnvarsta < p.varsta;
}
```

```
}
```

22

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 23 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Overloading methods

- A class may contain several methods with the same name but different signatures

- Signature = method name + list of parameter types

- The return type is not part of the signature

```
Complex.java
```

```
publicclassComplex {
privatedoublereal, imag;
publicvoidaduna(doublereal) {
this.real += real;
}
publicvoidaduna(Complex c) {
this.real += c.real;
this.imag += c.imag;
}
publicComplex aduna(Complex cc) {
this.real += cc.real;
this.imag += cc.imag;
returnthis;
}
```

```
}                                    // Errors?
```

23

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 24 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Operators and destructors

- Java does not allow operator overloading

- Exception built into the language: `String` supports `+` and `+=` for concatenation

- There are no destructors in Java

- Unreachable objects are reclaimed automatically by the garbage collector

```
String s = "abc";
String t = "EFG";
String r = s + t;      // r = "abcEFG"
s += 23;
s += ' ';
s += 4.5;              // s = "abc23 4.5"
```

24

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 25 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Static methods

- Declared with the keyword `static`

- They belong to the class and are called without an object

- There is no `this` inside a static method

```
Complex.java
```

```
publicclassComplex {
privatedoublereal, imag;
```

```
publicComplex(doublere, doubleim) {
//...
}
publicstaticComplex suma(Complex a, Complex b) {
returnnewComplex(a.real + b.real, a.imag + b.imag);
}
}
```

25

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 26 -->
0 2 · C L A S S E S A N D O B J E C T S

#### Calling static methods

■ Static methods are called using the class name :

```
Complex a, b;
//... initialize a and b
Complex c = Complex.suma(a, b);
```

A static method can only use static fields and call static methods directly. Instance members need an object: ! `obj.field` , `obj.method()` .

26

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 27 -->
0 3 · P R I M I T I V E D A T A A N D V A R

#### Java primitive data types

|`type name1`|`[= expr1]`|`[, name2`|`[= expr2]]...;`||
|---|---|---|---|---|
|Type|Size (by|tes)|Values|Default value|
|`boolean`||–|true, false|`false`|
|`byte`||1|-27 … 27-1  (-128 … 127)|`(byte) 0`|
|`short`||2|-215 … 215-1|`(short) 0`|
|`int`||4|-231 … 231-1|`0`|
|`long`||8|-263 … 263-1|`0L`|
|`float`||4|IEEE 754, 32-bit|`0.0f`|
|`double`||8|IEEE 754, 64-bit|`0.0d`|
|`char`||2|Unicode  '\u0000' … '\uffff'  (0 … 216-1)|`'\u0000'`|

_Default values apply to fields and array elements. Local variables have no default – they must be assigned before use._

27

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 28 -->
0 3 · P R I M I T I V E D A T A A N D V A R

#### Local variable type inference: var (Java 10)

- `var` lets the compiler infer the type of a local variable from its initializer

- The variable is still statically typed – `var` is not dynamic typing

```
varcount = 10;                 // int
varname = "Ana";               // String
varp = newPersoana("Ana", 20); // Persoana
for(vari = 0; i < 3; i++) { /*...*/}
```

- Only for local variables with an initializer (also in `for` loops); not for fields, parameters or return types

```
count = "zece";   // compile error: count is an int
varx;            // compile error: no initializer
varn = null;     // compile error: type cannot be inferred
```

- Use it when the type is obvious from the right-hand side

28

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 29 -->
# 04

### Passing arguments in Java

29

<!-- page 30 -->
0 4 · P A S S I N G A R G U M E N T S

#### Arguments are always passed by value

- Primitive arguments ( `boolean` , `int` , `byte` , `long` , `double` , …): the value is copied on the stack

- Reference arguments: the reference is copied – the method sees the same object and can modify its content (fields, array elements) if it has access

- There is no way to choose another passing mode (like `&` in C++)

```
Parametrii.java
```

```
classParametrii {
staticvoidinterschimba(intx, inty) {
inttmp = x;
x = y;
y = tmp;
```

```
}
```

```
publicstaticvoidmain(String[] args) {
intx = 2, y = 4;
interschimba(x, y);
System.out.println("x="+ x + " y="+ y);  // ?
```

```
}
```

```
}
```

30

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 31 -->
0 4 · P A S S I N G A R G U M E N T S

#### Swapping references

```
B.java
```

```
classB {
```

```
intval;
publicB(intx) { this.val = x; }
publicString toString() { return""+ val; }
```

The method swaps its copies ? of the references. What do `bx` and `by` refer to after the call?

```
staticvoidinterschimba(B x, B y) {
B tmp = x;
x = y;
y = tmp;
System.out.println("[interschimba] x="+ x + " y="+ y);
```

```
}
publicstaticvoidmain(String[] args) {
B bx = newB(2);
B by = newB(4);
System.out.println("bx="+ bx + " by="+ by);
interschimba(bx, by);
```

```
System.out.println("bx="+ bx + " by="+ by);  // ?
```

```
}
```

```
}
```

31

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 32 -->
0 4 · P A S S I N G A R G U M E N T S

#### Modifying the object's content

```
B.java
```

```
classB {
intval;
publicB(intx) { this.val = x; }
publicString toString() { return""+ val; }
```

Now the method changes the ? fields of the objects both sides share. What is printed now?

```
staticvoidinterschimbaData(B x, B y) {
inttmp = x.val;
x.val = y.val;
y.val = tmp;
System.out.println("[interschimbaData] x="+ x + " y="+ y);
}
publicstaticvoidmain(String[] args) {
B bx = newB(2);
B by = newB(4);
System.out.println("bx="+ bx + " by="+ by);
interschimbaData(bx, by);
System.out.println("bx="+ bx + " by="+ by);  // ?
}
```

```
}
```

32

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 33 -->
# 05 Java arrays

33

<!-- page 34 -->
0 5 · A R R A Y S

#### One-dimensional arrays

- Declaration: `type[] name;` or `type name[];`

- Allocation: `name = new type[dim];`

   - indexes go from `0` to `dim-1`

- Access: `name[index]`

```
float[] vec;
vec = newfloat[10];
int[] sir = newint[3];
```

```
floattmp[];
tmp = vec;    // vec and tmp refer to the same array
```

- Arrays are objects: an array variable holds a reference

34

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 35 -->
0 5 · A R R A Y S

#### Array length

- Every array has a built-in, read-only field `length`

- Index checks are done at run time: an invalid index throws `ArrayIndexOutOfBoundsException`

- Shortcut to create and initialize: `int[] dx = {-1, 0, 1};`

```
int[] sir = newint[5];
intlungSir = sir.length;    // 5
sir[0] = sir.length;
sir.length = 2;              // compile error: length is final
```

```
int[] y;
```

```
intlungY = y.length;        // compile error: y not initialized
```

```
double[] t = newdouble[0];
intlungT = t.length;        // 0
```

```
t[0] = 2.3;                  // runtime: ArrayIndexOutOfBoundsException
```

35

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 36 -->
0 5 · A R R A Y S

#### The enhanced for statement (for-each)

- `for (Type elem : array) instr;` visits every element in order

- No index, no off-by-one errors

- Works for arrays and for every `Iterable` (collections – Lecture 4)

- Use the classic `for` when you need the index or want to modify the array

```
int[] x = {1, 4, 6, 9, 10};
for(intel : x)                  // for-each
System.out.println(el);
```

```
for(inti = 0; i < x.length; i++) // classic for
System.out.println(x[i]);
```

```
for(intel : x)
el = 0;     // has no effect on the array!
```

36

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 37 -->
0 5 · A R R A Y S

#### Rectangular multidimensional arrays

- Declaration: `type name[][]…[];` or `type[][]…[] name;`

- Creation: `name = new type[dim1][dim2]…[dimN];`

- Access: `name[i1][i2]…[iN]`

   - `int` `[][] a; a =` `new int` `[5][5]; a[0][0] = 2;` `int` `x = a[2][2];` _`// 0`_

- A 2D array is an array of arrays

37

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 38 -->
0 5 · A R R A Y S

#### Non-rectangular (jagged) arrays

```
creation
```

```
int[][] a = newint[3][];
for(inti = 0; i < 3; i++)
a[i] = newint[i + 1];
```

```
intx = a.length;      // x = ?
inty = a[2].length;   // y = ?
```

```
declaration + creation + initialization
```

```
char[][] lit = {{'a'}, {'b'}};
int[][] b = {{1, 2},
{2, 5, 8},
{1}};
double[][] mat = newdouble[][]{{1.3, 0.5},
{2.3, 4.5}};
```

38

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 39 -->
0 5 · A R R A Y S

#### Arrays of objects

- `new Complex[n]` creates an array of `n` null references

- Each element must be allocated and initialized separately

```
TablouriObiecte.java
```

```
publicclassTablouriObiecte {
staticvoidgenereaza(intnrElem, Complex[] t) {
t = newComplex[nrElem];
for(inti = 0; i < nrElem; i++)
t[i] = newComplex(i, i);
```

```
}
staticComplex[] genereaza(intnrElem) {
Complex[] t = newComplex[nrElem];
for(inti = 0; i < nrElem; i++)
t[i] = newComplex(i, i);
returnt;
}
staticvoidmodifica(Complex[] t) {
for(inti = 0; i < t.length; i++)
t[i].suma(t[i]);
```

```
}
//...
```

39

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 40 -->
0 5 · A R R A Y S

#### Arrays of objects (continued)

```
TablouriObiecte.java
```

```
staticComplex suma(Complex[] t) {
Complex suma = newComplex(0, 0);
for(inti = 0; i < t.length; i++)
suma.aduna(t[i]);
returnsuma;
}
publicstaticvoidmain(String[] args) {
Complex[] t = genereaza(3);
Complex cs = suma(t);
System.out.println("suma "+ cs);
Complex[] t1 = null;
genereaza(3, t1);
Complex cs1 = suma(t1);    // ?
System.out.println("suma "+ cs1);
modifica(t);
System.out.println("suma dupa modificare "+ suma(t));
}
```

Which version of ? `genereaza` actually gives the caller a new array?

```
}
```

40

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 41 -->
0 5 · A R R A Y S

#### java.util.Arrays: ready-made algorithms

- `Arrays.toString` / `deepToString` – readable output

- `Arrays.sort` – sorting (also with a comparator)

- `Arrays.binarySearch` – on sorted arrays

- `Arrays.fill` , `Arrays.copyOf` , `Arrays.equals`

```
int[] v = {5, 3, 9, 1};
System.out.println(v);                   // [I@1b6d3586
System.out.println(Arrays.toString(v));  // [5, 3, 9, 1]
Arrays.sort(v);                          // [1, 3, 5, 9]
intpos = Arrays.binarySearch(v, 5);     // 2
```

```
int[] w = Arrays.copyOf(v, 6);           // [1, 3, 5, 9, 0, 0]
booleaneq = Arrays.equals(v, w);        // false
int[][] m = {{1, 2}, {3, 4}};
System.out.println(Arrays.deepToString(m)); // [[1, 2], [3, 4]]
```

- Don't reimplement what the library already offers

41

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 42 -->
# 06 Strings and text

42

<!-- page 43 -->
0 6 · S T R I N G S A N D T E X T

#### char arrays and String

- A `char[]` is a mutable array; it is compared and printed character by character

- A string literal `"Ana are mere"` is an object of type `String`

- `String` is immutable : operations create new objects; the content can never change

```
char[] sir = {'a', 'n', 'a'};
sir[0] = 'A';               // OK: arrays are mutable
String s = "abc";
s = s + "123";              // new String object
String t = s;               // t = "abc123"
t += "12";                  // t = ?, s = ?
t[0] = 'A';                 // compile error: not an array
charc = t.charAt(0);       // read-only access
```

43

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 44 -->
0 6 · S T R I N G S A N D T E X T

#### Useful String methods

- `s.length()` – number of characters (a method , unlike `array.length` )

- `s.charAt(i)` – character at index `i`

- `t.equals(s)` – `true` if and only if `s` is a `String` with the same sequence of characters

```
String s = "abc";
intlen = s.length();         // 3
booleaneq = s.equals("abc"); // true
intrez = "abd".compareTo(s); // > 0
```

- `t.compareTo(s)` – lexicographic comparison: result `< 0` , `0` or `> 0`

! Never compare strings with `==` : it compares references , not content. Use `equals` .

44

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 45 -->
0 6 · S T R I N G S A N D T E X T

#### Building strings efficiently: StringBuilder

- `String` is immutable: `s += x` in a loop creates a new object at every step

- `StringBuilder` is a mutable sequence of characters

- Use it when a string is built step by step

- Methods return `this` , so calls can be chained

```
// slow: creates n intermediate String objects
String s = "";
for(inti = 0; i < n; i++)
s += i + ",";
// fast: one mutable buffer
StringBuilder sb = newStringBuilder();
for(inti = 0; i < n; i++)
sb.append(i).append(',');
String rez = sb.toString();
sb.reverse();  sb.insert(0, "[");  sb.setLength(0);
```

45

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 46 -->
0 6 · S T R I N G S A N D T E X T

#### Text blocks (Java 15)

```
before
```

###### `with a text block`

```
String json = "{\n"+
"  \"nume\": \"Ana\",\n"+
"  \"media\": 9.5\n"+
"}\n";
```

```
String json = """
{
"nume": "Ana",
"media": 9.5
}
""";
```

A text block starts with `"""` followed by a line break. Common indentation is removed automatically; quotes need no i escaping. Ideal for JSON, SQL, HTML and test data.

46

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 47 -->
0 6 · S T R I N G S A N D T E X T

#### Modern String methods

■ Java 11: `isBlank` , `strip` , `lines` , `repeat`

■ Java 12: `indent` ; Java 15: `formatted`

- `String.join` and `split` for lists of words

- `strip` is Unicode-aware – prefer it to `trim`

```
"   ".isBlank();               // true
"  Ana  ".strip();             // "Ana"
```

```
"ab".repeat(3);                // "ababab"
"l1\nl2\nl3".lines().count();  // 3
```

```
String msg = "%s are media %.2f".formatted("Ana", 9.456);
// "Ana are media 9.46"
```

```
String csv = String.join(";", "Ana", "Ion", "Maria");
String[] parts = csv.split(";");   // {"Ana","Ion","Maria"}
"Java".chars().filter(c -> c == 'a').count(); // 2
```

47

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 48 -->
# 07 Modern control flow

48

<!-- page 49 -->
0 7 · M O D E R N C O N T R O L F L O W

#### switch: from statement to expression (Java 14)

```
classic switch statement
```

```
switch expression with arrows
```

```
String tip;
switch(zi) {
case1: case2: case3: case4: case5:
tip = "lucratoare";
break;
case6: case7:
tip = "weekend";
break;
default:
tip = "invalida";
}
// a forgotten break = fall-through bug
```

```
String tip = switch(zi) {
case1, 2, 3, 4, 5-> "lucratoare";
case6, 7-> "weekend";
default-> "invalida";
};
// no fall-through, no break,
// the switch produces a value
```

Arrow labels never fall through. A `switch` expression must be exhaustive : every possible value must be covered (here by i `default` ).

49

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 50 -->
0 7 · M O D E R N C O N T R O L F L O W

#### switch expressions: blocks and yield

- A case can execute a block ; `yield` returns the value of the block

- `switch` works on `int` , `char` , `String` , enums – and, since Java 21, on any type with patterns (Lecture 2)

- Arrow form also works as a statement (no value)

```
intpuncte = switch(nota) {
case"A"-> 10;
case"B"-> 8;
case"C"-> {
System.out.println("acceptabil");
yield6;
}
default-> thrownewIllegalArgumentException(nota);
};
```

```
arrow form as a statement
```

```
switch(comanda) {
case"start"-> porneste();
case"stop"-> opreste();
default-> System.out.println("?");
}
```

50

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 51 -->
0 7 · M O D E R N C O N T R O L F L O W

#### Formatted output

- `printf` / `String.format` / `formatted` use format specifiers

`■ %d` integer, `%f` real, `%s` string, `%n` line break

■ Width, precision and alignment: `%-30s` , `%5.2f` , `%3d`

```
System.out.printf("| %3d | %-15s | %5.2f |%n", 1, "Popescu Ion", 6.7);
System.out.printf("| %3d | %-15s | %5.2f |%n", 2, "Marinescu Ana", 9.6);
// output:
// |   1 | Popescu Ion     |  6.70 |
// |   2 | Marinescu Ana   |  9.60 |
```

```
String s = String.format("%08.3f", Math.PI);  // "0003.142"
```

Formatting is locale-dependent : on a Romanian system `%.2f` prints `6,70` . Use `String.format(Locale.ROOT, ...)` ! when a dot is required (files, CSV).

51

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 52 -->
0 7 · M O D E R N C O N T R O L F L O W

#### Summary

- A class defines state (fields) and behaviour (methods); objects are created with `new` and live on the heap

- Constructors initialize objects; `this(...)` and overloading avoid duplication; `static` members belong to the class

- Java passes everything by value – for objects, the value is a reference

- Arrays are objects with a fixed `length` ; use for-each and `java.util.Arrays`

- `String` is immutable; build strings with `StringBuilder` ; text blocks for multi-line literals

- Modern syntax: `var` , `switch` expressions with `->` and `yield`

52

Advanced Programming Methods  ·  Lecture 1 – Java Basics

<!-- page 53 -->
## Questions?

Next: Lecture 2 – Object-Oriented Design in Java
