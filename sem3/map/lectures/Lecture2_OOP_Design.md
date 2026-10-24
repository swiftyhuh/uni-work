<!-- page 1 -->
## Advanced Programming Methods Lecture 2 – Object-Oriented Design in Java

```
sealed interface Forma permits Cerc, Patrat { }
```

<!-- page 2 -->
I N T R O D U C T I O N

#### Lecture overview

01 Composition and inheritance

02 Polymorphism and abstract classes

03

Interfaces (incl. default methods)

04

Casting and instanceof

05

06

07

08

The class Object: equals, hashCode, toString

Nested and anonymous classes

Enums, records, sealed types, pattern matching

Packages, access modifiers, modules

2

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 3 -->
# 01

### Code reuse: composition and inheritance

3

<!-- page 4 -->
0 1 · C O M P O S I T I O N A N D I N H E R I T A N C E

#### Two ways to reuse code

```
has-a
```

##### Composition

The new class contains fields that are objects of existing classes.

_Persoana has an Adresa_

```
is-a
```

##### Inheritance

The new class extends an existing class: it adds new fields and methods to those it inherits.

_Angajat is a Persoana_

4

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 5 -->
0 1 · C O M P O S I T I O N A N D I N H E R I T A N C E

#### Composition

###### ■ The new class contains fields that are objects of existing classes

```
Adresa.java
```

```
classAdresa {
privateString nr, strada,
localitate, tara;
privatelongcodPostal;
//...
}
```

```
Persoana.java
```

```
classPersoana {
privateString nume;
privateAdresa adresa;
privateString cnp;
//...
}
```

###### `Scrisoare.java`

```
classScrisoare {
privateString destinatar;
privateAdresa adresaDestinatar;
privateString expeditor;
privateAdresa adresaExpeditor;
//...
```

```
}
```

5

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 6 -->
0 1 · C O M P O S I T I O N A N D I N H E R I T A N C E

#### Inheritance

```
classNewClass extendsExistingClass {
//...
```

```
}
```

`NewClass` is the subclass (child class, derived class); `ExistingClass` is the superclass (parent class, base class).

i `NewClass` inherits all members of `ExistingClass` . It may override some of the inherited methods and add new fields and methods.

Private members are inherited but not directly accessible in the subclass.

6

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 7 -->
0 1 · C O M P O S I T I O N A N D I N H E R I T A N C E

#### Inheritance – example

```
Punct.java
```

```
publicclassPunct {
privateintx, y;
publicPunct(intx, inty) {
this.x = x;
this.y = y;
}
publicvoidmuta(intdx, intdy) {
//...
}
publicvoiddeseneaza() {
//...
}
```

```
PunctColorat.java
```

```
publicclassPunctColorat extendsPunct {
privateString culoare;
publicPunctColorat(intx, inty,
String culoare) { /*...*/}
publicvoiddeseneaza() { /*...*/}  // overridden
publicString culoare() { /*...*/}  // new
}
// muta(...) is inherited unchanged
```

```
}
```

7

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 8 -->
0 1 · C O M P O S I T I O N A N D I N H E R I T A N C E

#### Inheritance – notions and memory layout

`■ deseneaza` is an overridden method

Stack

<!-- Start of picture text -->
Heap <!-- End of picture text -->

`■ muta` is an inherited method

`■ culoare` is a newly added method

`punct` Punct `x = 2    y = 3`

```
Punct punct = newPunct(2, 3);
PunctColorat punctColorat =
newPunctColorat(2, 3, "alb");
```

<!-- Start of picture text -->
punctColorat <!-- End of picture text -->

PunctColorat _inherited from Punct_ `x = 2    y = 3 culoare = "alb"`

8

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 9 -->
0 1 · C O M P O S I T I O N A N D I N H E R I T A N C E

#### Method overriding

- A subclass may override methods of its base class

- Class `B` overrides method `mR` of class `A` if `B` defines `mR` with the same signature as in `A`

- For a call `a.mR()` , the method executed is chosen by the class of the object referred to by `a` , not by the declared type of `a`

   - `A a =` `new` `A(); a.mR();` _`// mR from A`_

   - `a =` `new` `B(); a.mR();` _`// mR from B`_

- Static methods are not overridden but _hidden_ : a call is resolved using the declared type

9

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 10 -->
0 1 · C O M P O S I T I O N A N D I N H E R I T A N C E

#### @Override and covariant return types

`■ @Override` asks the compiler to check that the method really overrides one from the base class

■ The return type of an overriding method may be a subtype of the original return type ( _covariant return type_ )

```
A.java / B.java
```

```
C.java / D.java
```

```
publicclassA {
publicvoidmR() { /*...*/}
}
```

```
publicclassB extendsA {
@Override
publicvoidmR() { /*...*/}
}
```

```
publicclassSubB extendsSuperA { /*...*/}
publicclassC {
publicSuperA m() { /*...*/}
}
publicclassD extendsC {
@Override
publicSubB m() { /*...*/}   // covariant
}
```

10

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 11 -->
0 1 · C O M P O S I T I O N A N D I N H E R I T A N C E

#### Method overloading in subclasses

- A subclass may overload a method inherited from the base class

- A subclass object can call all overloaded versions, including those from the superclass

```
A.java / B.java
```

```
usage
```

```
publicclassA {
publicvoidf(inth) { /*...*/}
publicvoidf(inti, charc) { /*...*/}
}
publicclassB extendsA {
publicvoidf(String s, inti) { /*...*/}
}
```

```
B b = newB();
b.f(23);        // from A
b.f(2, 'c');    // from A
b.f("mere", 5); // from B
```

11

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 12 -->
0 1 · C O M P O S I T I O N A N D I N H E R I T A N C E

#### Calling the superclass constructor: super(...)

- A subclass constructor can call a base class constructor using `super(...)`

- Traditionally the first statement ; since Java 25 it may be preceded by code that does not use `this` (e.g. argument validation)

- If it is missing, the compiler inserts `super()` – which must exist

```
Persoana.java
```

```
publicclassPersoana {
privateString nume;
privateintvarsta;
publicPersoana(String nume, intvarsta) {
this.nume = nume;
this.varsta = varsta;
```

```
}
```

```
}
```

```
Angajat.java
```

```
publicclassAngajat extendsPersoana {
privateString departament;
publicAngajat(String nume, intvarsta, String departament) {
super(nume, varsta);
this.departament = departament;
}
```

```
}
```

12

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 13 -->
0 1 · C O M P O S I T I O N A N D I N H E R I T A N C E

#### The keyword super

- Calls a constructor of the base class: `super(...)`

- Refers to a base-class member hidden in the subclass: `super.ac`

- Calls the overridden base-class method from the overriding method: `super.deseneaza()`

```
field hiding
```

```
calling the overridden method
```

```
publicclassA {
protectedintac = 3;
}
publicclassB extendsA {
protectedintac = 3;     // hides A.ac
publicvoidf() {
ac += 2;              // B.ac
super.ac--;           // A.ac
}
}
```

```
publicclassPunctColorat extendsPunct {
privateString culoare;
@Override
publicvoiddeseneaza() {
System.out.println(culoare);
super.deseneaza();    // Punct's version
}
}
```

13

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 14 -->
# 02

### Polymorphism and abstract classes

14

<!-- page 15 -->
0 2 · P O L Y M O R P H I S M A N D A B S T R A C T C L A S S E S

#### Polymorphism

- The ability of an object to behave differently depending on the context

Three kinds of polymorphism

- Ad-hoc – method overloading

- Parametric – generic types

- Inclusion (subtype) – inheritance

<!-- Start of picture text -->
FormaGeometrica +deseneaza() +muta(dx: int, dy: int) <!-- End of picture text -->

<!-- Start of picture text -->
Patrat Triunghi Cerc +deseneaza() +deseneaza() +deseneaza() +muta(dx, dy) +muta(dx, dy) +muta(dx, dy) <!-- End of picture text -->

15

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 16 -->
0 2 · P O L Y M O R P H I S M A N D A B S T R A C T C L A S S E S

#### Early and late binding

- Early binding: the method to execute is decided at compile time

- Late binding: the method to execute is decided at run time , from the class of the object

- Java uses late binding for instance methods

- Exceptions: `static` and `private` methods are bound at compile time

```
voiddeseneaza(FormaGeometrica fg) {
fg.deseneaza();
}
```

- _`//...`_

```
FormaGeometrica fg = newPatrat();
deseneaza(fg);   // calls deseneaza from Patrat
fg = newCerc();
```

```
deseneaza(fg);   // calls deseneaza from Cerc
```

16

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 17 -->
0 2 · P O L Y M O R P H I S M A N D A B S T R A C T C L A S S E S

#### Polymorphic collections

■ One array of the base type can hold objects of any subclass ■ Each element reacts with its own `muta` / `deseneaza`

```
publicFormaGeometrica[] genereaza(intdim) {
FormaGeometrica[] fg = newFormaGeometrica[dim];
Random rand = newRandom(47);
for(inti = 0; i < dim; i++) {
switch(rand.nextInt(3)) {
case0: fg[i] = newCerc(); break;
case1: fg[i] = newPatrat(); break;
case2: fg[i] = newTriunghi(); break;
}
}
returnfg;
}
```

```
publicvoidmuta(FormaGeometrica[] fg) {
for(FormaGeometrica f : fg)
f.muta(3, 3);
}
```

17

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 18 -->
0 2 · P O L Y M O R P H I S M A N D A B S T R A C T C L A S S E S

#### Abstract classes

■ An abstract method is declared but not implemented; it is marked `abstract`

- An abstract class may contain abstract methods, fields, constructors and implemented methods

```
syntax
```

```
[access] abstractReturnType name([params]);
```

- `[` `public` `]` `abstract class` `ClassName { [fields]`

   - `[` `abstract` `methods declaration] [methods declaration and implementation]`

```
}
```

```
Polinom.java
```

```
publicabstractclassPolinom {
//...
```

```
publicabstractvoidaduna(Polinom p);
```

```
}
```

18

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 19 -->
0 2 · P O L Y M O R P H I S M A N D A B S T R A C T C L A S S E S

#### Abstract classes – rules

- An abstract class cannot be instantiated : `new Polinom()` is a compile error

- A class with at least one abstract method must be declared abstract

- A class can be abstract without having any abstract method

- A subclass that does not implement all inherited abstract methods must also be abstract

```
A.java
```

```
publicabstractclassA {
publicA() {}
publicabstractvoidf();
publicabstractvoidg(inti);
}
```

```
B.java
publicabstractclassB extendsA {
privateinti = 0;        // f() is still abstract
publicvoidg(inti) {
this.i += i;
}
}
```

19

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 20 -->
0 2 · P O L Y M O R P H I S M A N D A B S T R A C T C L A S S E S

#### Abstract class example: Polinom

<!-- Start of picture text -->
Polinom #grad: int +getGrad(): int +getCoef(coef: int): int +setCoef(grad: int, val: int) +adunaMonom(grad: int, val: int) +aduna(pol: Polinom): Polinom +creazaPolinom(): Polinom PolinomTablou PolinomLM +adunaMonom(grad: int, val: int) +adunaMonom(grad: int, val: int) +getCoef(coef: int): int +getCoef(coef: int): int +getGrad(): int +getGrad(): int +setCoef(grad: int, val: int) +setCoef(grad: int, val: int) +creazaPolinom(): Polinom +creazaPolinom(): Polinom <!-- End of picture text -->

<!-- Start of picture text -->
abstract = italic <!-- End of picture text -->

20

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 21 -->
# 03

### Interfaces

21

<!-- page 22 -->
0 3 · I N T E R F A C E S

#### Java interfaces

- Declared with the keyword `interface` ; an interface is a type with no state

- No constructors, no instance fields

- Abstract methods are implicitly `public abstract`

- Fields are implicitly `public static final` (constants)

```
syntax
```

```
publicinterfaceInterfaceName {
[constants]
[method declarations]
```

```
}
```

- Since Java 8: `default` and `static` methods with a body; since Java 9: `private` methods

```
Shape.java
```

- An interface may be empty (a _marker interface_ , e.g. `Serializable` )

```
publicinterfaceShape {
doublePI2 = 2* Math.PI;   // constant
doublearea();              // abstract
defaultString describe() { // Java 8+
return"area = "+ area();
}
```

```
}
```

22

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 23 -->
0 3 · I N T E R F A C E S

#### Implementing an interface

- A class implements an interface with `implements`

- It must implement all abstract methods of the interface – or be declared `abstract`

<!-- Start of picture text -->
«interface» Comparable +compareTo(o: Object): int Rational <!-- End of picture text -->

```
syntax
```

- `[` `public` `]` `class` `ClassName` `implements` `InterfaceName { [` `interface` `method implementations]` _`// other definitions`_

- `}`

```
Rational.java
```

```
publicinterfaceComparable {
intcompareTo(Object o);
}
publicclassRational implementsComparable {
privateintnumarator, numitor;
//...
publicintcompareTo(Object o) { /*...*/}
}
```

23

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 24 -->
0 3 · I N T E R F A C E S

#### Extending interfaces

- An interface can extend one or more interfaces

- This is Java's form of multiple inheritance – of types, not of state

```
syntax
```

- `[` `public` `]` `interface` `Name` `extends` `I1[, I2, ...] { [` `new` `method declarations]`

- `}`

```
example
```

```
publicinterfaceA { intf(); }
publicinterfaceB { doubleh(inti); }
publicinterfaceC extendsA, B {
booleang(String s);
}   // C has f, h and g
```

24

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 25 -->
0 3 · I N T E R F A C E S

#### Inheritance and interfaces together

- A class can extend only one class, but can implement any number of interfaces

<!-- Start of picture text -->
Number «interface» Serializable «interface» Integer Comparable +compareTo(o: Object): int <!-- End of picture text -->

```
syntax
```

- `[` `public` `]` `class` `Name` `extends` `SuperClass` `implements` `I1, I2, ..., In {`

- _`//...`_

- `}`

```
simplified from java.lang
```

```
publicclassInteger extendsNumber
implementsComparable {
publicintcompareTo(Object o) { /*...*/}
}
// Number implements Serializable
```

25

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 26 -->
0 3 · I N T E R F A C E S

#### Variables of interface type

- An interface is a reference type : variables of interface type can be declared

- They can refer to objects of any class that implements the interface

- Through such a variable, only the interface methods can be called

```
publicinterfaceComparable { /*...*/}
publicclassRational implementsComparable { /*...*/}
Rational r = newRational();
Comparable c = r;
Comparable cr = newRational(2, 3);
cr.compareTo(c);
c.aduna(cr);    // ERROR: not in Comparable
```

26

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 27 -->
0 3 · I N T E R F A C E S

#### Interface example: Stiva

<!-- Start of picture text -->
«interface» Stiva The interface fixes what a stack can do; each class decides how (array vs. linked nodes). +adauga(elem: Object) +scoate(): Object +eVida(): boolean +ePlina(): boolean +varf(): Object <!-- End of picture text -->

<!-- Start of picture text -->
StivaTablou StivaDinamica <!-- End of picture text -->

27

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 28 -->
0 3 · I N T E R F A C E S

#### Interfaces before and after Java 8

###### Before Java 8

- An interface defines a contract

- Only abstract methods and constants ( `public static final` )

- Every implementing class must define all methods

###### Since Java 8 (and 9)

- `default` methods: have a body; implementing classes may override them

- `static` methods: have a body; cannot be overridden ; called as `Interface.method()`

- Java 9: `private` methods, to share code between default methods

- Classes must still define all abstract methods

28

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 29 -->
0 3 · I N T E R F A C E S

#### Why default methods?

- If the designers of a published interface add a new method, every implementing class stops compiling – each must now define it

- Default and static methods let an interface evolve without breaking existing implementations

- The JDK itself relies on this: Java 8 added `Collection.stream()` and `List.sort(...)` as default methods

<!-- Start of picture text -->
«interface» Collection + size(), add(), … + default stream() ArrayList HashSet your own class <!-- End of picture text -->

_existing implementations keep compiling_

_Example on the next slides adapted from examples.javacodegeeks.com (Interface vs Abstract Class)_

29

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 30 -->
0 3 · I N T E R F A C E S

#### Example: an interface with default and static methods

- `printWelcomeMessage` – static : cannot be overridden; `makeACall` – default : may be overridden; `capturePhoto` – abstract : must be defined

```
MobileInterface.java
```

```
publicinterfaceMobileInterface {
// static: called as MobileInterface.printWelcomeMessage()
staticvoidprintWelcomeMessage() {
```

```
System.out.println("*STATIC METHOD* Welcome!!");
```

```
}
// default: implementing classes inherit or override it
defaultvoidmakeACall(longnumber) {
```

```
System.out.println("*DEFAULT METHOD* Calling ... "+ number);
}
// abstract: every implementing class must define it
voidcapturePhoto();
```

```
}
```

30

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 31 -->
0 3 · I N T E R F A C E S

#### Implementing classes

###### `BasicPhone.java`

###### `SmartPhone.java`

```
// defines only the abstract method;
// makeACall() uses the default version
classBasicPhone implementsMobileInterface {
@Override
publicvoidcapturePhoto() {
System.out.println(
"*BASIC PHONE* Cannot capture photo");
}
}
```

```
// overrides the default method too
classSmartPhone implementsMobileInterface {
@Override
publicvoidmakeACall(longnumber) {
System.out.println("*SMART PHONE* "
+ "Voice and video call to "+ number);
}
@Override
publicvoidcapturePhoto() {
System.out.println(
"*SMART PHONE* Can capture photo");
}
```

```
}
```

i Overriding methods must be `public` : interface methods are implicitly public, and access cannot be reduced.

31

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 32 -->
0 3 · I N T E R F A C E S

#### Using the interface

###### `MobileInterfaceDemo.java`

```
publicclassMobileInterfaceDemo {
publicstaticvoidmain(String[] args) {
MobileInterface basicPhone = newBasicPhone();
MobileInterface smartPhone = newSmartPhone();
```

```
MobileInterface.printWelcomeMessage(); // static
```

###### `output`

- _`*STATIC METHOD* Welcome!!`_

- _`*DEFAULT METHOD* Calling ... 1234567890`_

- _`*BASIC PHONE* Cannot capture photo`_

- _`*SMART PHONE* Voice and video`_ `call to 1234567890`

- _`*SMART PHONE* Can capture photo`_

```
basicPhone.makeACall(1234567890L);   // default
basicPhone.capturePhoto();           // BasicPhone
```

```
smartPhone.makeACall(1234567890L);   // overridden
smartPhone.capturePhoto();           // SmartPhone
```

```
}
```

```
}
```

32

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 33 -->
0 3 · I N T E R F A C E S

#### Abstract class vs. interface

||Abstract class|Interface|
|---|---|---|
|Methods|public, protected, package-private, private; abstract or implemented|public abstract by default; default and static (Java 8+), private (Java 9+)|
|Fields|any fields (instance and static)|only public static final constants|
|Constructors|yes (called via super(...))|no|
|Inheritance|a class extends one class|a class implements many interfaces|
|Abstract methods|may have none|may have none (marker interface)|
|Instances|cannot be instantiated|cannot be instantiated|

33

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 34 -->
# 04

### Casting and instanceof

34

<!-- page 35 -->
0 4 · C A S T I N G A N D I N S T A N C E O F

#### Upcasting and downcasting

- Upcasting (subclass → superclass) is implicit and always safe

- Downcasting (superclass → subclass) needs an explicit cast

- The compiler accepts the cast; the JVM checks it at run time and throws `ClassCastException` if the object is not of that type

```
classBase { /*...*/}
classSubBase extendsBase { /*...*/}
Base objB = newBase();
SubBase objSB1 = newSubBase();
SubBase objSB2;
```

```
objB = objSB1;               // OK: upcasting
objSB2 = objB;               // compile error
objSB2 = (SubBase) objB;     // OK: objB refers to a SubBase
objSB2 = (SubBase) newBase();
// compiles, but ClassCastException at run time
```

35

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 36 -->
0 4 · C A S T I N G A N D I N S T A N C E O F

#### The instanceof operator

- Tests whether an object is an instance of a type:

`interface` `MyInterface {}` type: `class` `Parent {}` `class` `Child` `extends` `Parent` `implements` `MyInterface {}` – the class itself, a subclass, or a class that implements an interface `Parent obj1 =` `new` `Parent(); Parent obj2 =` `new` `Child(); ■ null instanceof T` is always `false` – `null` is not an instance of anything `obj1` `instanceof` `Parent` _`// true`_ `obj1` `instanceof` `Child` _`// false`_ ■ Used before a downcast to avoid `obj1` `instanceof` `MyInterface` _`// false`_ `ClassCastException obj2` `instanceof` `Parent` _`// true`_ `obj2` `instanceof` `Child` _`// true`_ `obj2` `instanceof` `MyInterface` _`// true`_

36

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 37 -->
0 4 · C A S T I N G A N D I N S T A N C E O F

#### instanceof in practice

```
classic: test, then cast
```

```
interfacePrintable {}
```

```
classA implementsPrintable {
publicvoida() { System.out.println("a method"); }
```

```
}
```

```
classB implementsPrintable {
publicvoidb() { System.out.println("b method"); }
```

```
}
classCall {
voidinvoke(Printable p) {
```

```
Java 16+: pattern matching
```

```
classCall {
voidinvoke(Printable p) {
if(p instanceofA a)
a.a();
elseif(p instanceofB b)
b.b();
}
}
```

```
if(p instanceofA a)   // test + cast + bind
a.a();
```

```
if(p instanceofA) {
```

```
A a = (A) p;        // downcasting
a.a();
```

```
}
if(p instanceofB) {
B b = (B) p;        // downcasting
b.b();
```

```
}
```

```
}
```

```
}
```

37

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 38 -->
# 05 The class Object

38

<!-- page 39 -->
0 5 · T H E C L A S S O B J E C T

#### Object: the root of the hierarchy

- `java.lang.Object` is the top of the Java class hierarchy

```
publicclassPunct {             // extends Object
//...
```

```
}
```

- A class without an explicit `extends` implicitly extends `Object`

```
publicclassPunctColorat extendsPunct {
//...
```

```
}
```

- So every class inherits the methods of `Object`

<!-- Start of picture text -->
Object <!-- End of picture text -->

```
PunctColorat → Punct → Object
```

Punct String Integer*

_* Integer extends Number, which extends Object_

39

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 40 -->
0 5 · T H E C L A S S O B J E C T

#### Methods of Object

`■ toString()` – called automatically when a `String` is expected

`■ equals(Object)` – checks equality of two objects; the default implementation compares references (same as `==` )

`■ hashCode()` – must be consistent with `equals`

###### Object

+equals(o: Object): boolean +toString(): String +hashCode(): int +getClass(): Class<?> +notify(), notifyAll(), wait() #clone(): Object _#finalize()  (deprecated)_

```
Punct p1 = newPunct(2, 3);
Punct p2 = newPunct(2, 3);
booleanegale = (p1 == p2);   // false
egale = p1.equals(p2);        // true only if Punct
// overrides equals
System.out.println(p1);       // calls p1.toString()
```

40

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 41 -->
0 5 · T H E C L A S S O B J E C T

#### Overriding equals, hashCode and toString

- `equals` takes an `Object` parameter – otherwise it overloads instead of overriding

- Objects that are `equals` must have the same `hashCode` – required by `HashMap` , `HashSet`

- `@Override` catches signature mistakes

```
Punct.java
```

```
publicclassPunct {
privateintx, y;
publicPunct(intx, inty) {
this.x = x;
this.y = y;
}
@Override
publicbooleanequals(Object obj) {
if(!(obj instanceofPunct))
returnfalse;
Punct p = (Punct) obj;
returnx == p.x && y == p.y;
}
@Override
publicinthashCode() {
return31* x + y;    // or Objects.hash(x, y)
}
@Override
publicString toString() {
return"("+ x + ", "+ y + ")";
}
}
```

41

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 42 -->
# 06

### Nested and anonymous classes

42

<!-- page 43 -->
0 6 · N E S T E D A N D A N O N Y M O U S C L A S S E S

#### Classes inside classes

|Kind|Declared|Has an outer object?|Typical use|
|---|---|---|---|
|static nested|static class Nod {…} inside a class|no|helper types: list nodes, builders|
|inner|class Cursor {…} inside a class|yes – Outer.this|iterators, views on the outer object|
|local|inside a method body|yes, if in an instance method|small helpers used by one method|
|anonymous|new Interface() {…} in an expression|yes, if in an instance method|one-off implementations (now mostly lambdas)|

Nested classes can access the private members of the enclosing class – and vice versa. Prefer `static` nested classes unless i you really need the outer object.

43

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 44 -->
0 6 · N E S T E D A N D A N O N Y M O U S C L A S S E S

#### Static nested and inner classes

- `Nod` is static : it needs no `Lista` object

- `Cursor` is an inner class: every cursor is tied to a `Lista` object and reads its `head`

- An inner object is created from an outer one: `l.new Cursor()`

```
Lista.java
```

```
publicclassLista {
privateNod head;
```

```
privatestaticclassNod {          // static nested
intinfo; Nod next;
```

```
Nod(intinfo, Nod next) { this.info = info; this.next = next; }
}
```

```
publicclassCursor {               // inner
privateNod crt = head;         // Lista.this.head
publicbooleanareUrmator() { returncrt != null; }
publicinturmator() {
```

```
intv = crt.info; crt = crt.next; returnv;
}
}
publicvoidadauga(intx) { head = newNod(x, head); }
}
```

```
Lista l = newLista();  l.adauga(3);  l.adauga(7);
Lista.Cursor c = l.newCursor();
while(c.areUrmator()) System.out.println(c.urmator()); // 7 3
```

44

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 45 -->
0 6 · N E S T E D A N D A N O N Y M O U S C L A S S E S

#### Anonymous classes

- Declare and instantiate a class in one expression – the class has no name

- Used for classes needed only once: event handlers, callbacks, comparators

- For interfaces with a single abstract method, Java 8 lambdas are the concise replacement (Lecture 4)

```
Runnable r = newRunnable() {
@Override
publicvoidrun() {
System.out.println("rulez");
}
};
r.run();
```

```
Swing event handler
JButton b = newJButton("Test");
b.addActionListener(newActionListener() {
@Override
publicvoidactionPerformed(ActionEvent e) {
System.out.println("Click detected");
}
});
// Lecture 4: b.addActionListener(e -> System.out.println("Click"));
```

45

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 46 -->
0 6 · N E S T E D A N D A N O N Y M O U S C L A S S E S

#### Local and anonymous classes capture variables

- A local or anonymous class can use local variables and parameters of the enclosing method

- Those variables must be effectively final : never reassigned after initialization

- The same rule applies to lambdas

```
intnumaraPestePrag(int[] v, intprag) {
classContor {                 // local class
intn;
voidverifica(intx) {
if(x > prag) n++;     // uses the parameter prag
}
}
Contor c = newContor();
for(intx : v) c.verifica(x);
// prag = 0;  would make prag not effectively final
//            -> compile error at 'x > prag'
returnc.n;
}
```

46

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 47 -->
# 07

### Enums, records and sealed types

47

<!-- page 48 -->
0 7 · E N U M S , R E C O R D S , S E A L E D T Y P E S

#### Enums: a fixed set of named constants

```
the old way –int constantswith an enum
publicinterfaceLuniAn {publicenumZi {
intIANUARIE = 1, FEBRUARIE = 2,
/*...*/DECEMBRIE = 12;LUNI, MARTI, MIERCURI, JOI,
}
VINERI, SAMBATA, DUMINICA
voidplanifica(intluna) { /*...*/}
planifica(42);      // compiles –but is meaningless}
Zi z = Zi.SAMBATA;
booleanweekend = switch(z) {
caseSAMBATA, DUMINICA -> true;
default-> false;
};
Zi.valueOf("LUNI");   // Zi.LUNI
z.ordinal();          // 5
```

An enum is a type : only its constants are valid values. Enums can be used in `switch` , compared with `==` , and stored i efficiently in `EnumSet` / `EnumMap` .

48

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 49 -->
0 7 · E N U M S , R E C O R D S , S E A L E D T Y P E S

#### Enums with fields, constructors and methods

- Each constant is an object , created once, when the enum is loaded

- ■ Enums can have fields, constructors (always private) and methods

- ■ Enums can implement interfaces

```
Calificativ.java
```

```
publicenumCalificativ {
FOARTE_BINE(10), BINE(8), SUFICIENT(5), INSUFICIENT(0);
privatefinalintpuncte;
Calificativ(intpuncte) { this.puncte = puncte; }
publicintpuncte() { returnpuncte; }
publicbooleanpromovat() { returnthis!= INSUFICIENT; }
}
for(Calificativ c : Calificativ.values())
System.out.println(c + " "+ c.puncte() + " "+ c.promovat());
```

49

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 50 -->
0 7 · E N U M S , R E C O R D S , S E A L E D T Y P E S

#### Records: transparent data carriers (Java 16)

```
one line…
```

```
…the compiler generates
```

```
publicrecordPunct(intx, inty) { }
Punct p1 = newPunct(2, 3);
Punct p2 = newPunct(2, 3);
p1.x();            // 2 –accessor
p1.equals(p2);     // true
System.out.println(p1); // Punct[x=2, y=3]
```

```
publicfinalclassPunct {
privatefinalintx, y;
publicPunct(intx, inty) { this.x = x; this.y = y; }
publicintx() { returnx; }
publicinty() { returny; }
publicbooleanequals(Object o) { /* by components */}
publicinthashCode() { /* by components */}
publicString toString() { /* Punct[x=2, y=3] */}
}
```

Compare with the hand-written `equals` / `hashCode` / `toString` of `Punct` in section 05. Records are immutable (final fields) i and cannot extend other classes, but can implement interfaces.

50

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 51 -->
0 7 · E N U M S , R E C O R D S , S E A L E D T Y P E S

#### Records: validation and extra methods

- A compact constructor validates or normalizes the components

- Records may add methods and static factories

- Immutability is shallow : a record holding a mutable list does not protect the list

```
Student.java
```

```
publicrecordStudent(String nume, doublemedia) {
```

```
publicStudent {                       // compact constructor
Objects.requireNonNull(nume);
if(media < 1|| media > 10)
thrownewIllegalArgumentException("media: "+ media);
}
publicbooleanintegralist() { returnmedia >= 5; }
publicstaticStudent parse(String linie) {   // "Pop Ion|9.3"
String[] p = linie.split("\\|");
returnnewStudent(p[0].strip(), Double.parseDouble(p[1]));
}
}
```

51

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 52 -->
0 7 · E N U M S , R E C O R D S , S E A L E D T Y P E S

#### Sealed classes and interfaces (Java 17)

`■ sealed … permits` fixes the complete list of direct subtypes

```
publicsealedinterfaceForma
```

```
permitsCerc, Patrat, Dreptunghi { }
```

- Each permitted subtype must be `final` , `sealed` or `non-sealed` (records are implicitly final)

■ The compiler now knows every possible shape – useful for exhaustive `switch`

```
publicrecordCerc(doubler) implementsForma { }
publicrecordPatrat(doublel) implementsForma { }
publicrecordDreptunghi(doublel, doubleh)
implementsForma { }
```

```
publicrecordTriunghi(doublea, doubleb, doublec)
implementsForma { }   // compile error: not permitted
```

- Models closed domains: shapes, expressions, payment methods, results

52

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 53 -->
0 7 · E N U M S , R E C O R D S , S E A L E D T Y P E S

#### Pattern matching for switch (Java 21)

`■ case Tip var ->` tests the type and binds a variable

- `when` adds a guard condition

■ Over a sealed type the switch is exhaustive without `default` – adding a new shape makes this code fail to compile until it is handled

- `case null` handles null explicitly

```
staticdoublearie(Forma f) {
returnswitch(f) {
```

```
caseCerc c whenc.r() == 0-> 0;
```

```
caseCerc c       -> Math.PI * c.r() * c.r();
casePatrat p     -> p.l() * p.l();
caseDreptunghi d -> d.l() * d.h();
};          // no default needed
}
```

```
staticString descrie(Object o) {
returnswitch(o) {
```

```
casenull-> "nimic";
caseInteger i -> "intreg "+ i;
caseString s  -> "text de "+ s.length() + " caractere";
default-> "altceva";
};
}
```

53

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 54 -->
0 7 · E N U M S , R E C O R D S , S E A L E D T Y P E S

#### Record patterns: deconstructing data (Java 21)

■ A record pattern extracts the components directly ■ Patterns can be nested

`■ var` infers component types; `_` (Java 22) ignores a component

```
staticdoublearie(Forma f) {
returnswitch(f) {
caseCerc(doubler)       -> Math.PI * r * r;
casePatrat(doublel)     -> l * l;
caseDreptunghi(doublel, doubleh) -> l * h;
};
}
```

```
recordSegment(Punct a, Punct b) { }
```

```
staticbooleanvertical(Object o) {
returno instanceofSegment(Punct(varx1, _), Punct(varx2, _))
&& x1 == x2;
}
```

54

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 55 -->
0 7 · E N U M S , R E C O R D S , S E A L E D T Y P E S

#### Polymorphism or pattern matching?

```
OOP
```

```
data-oriented
```

###### Abstract method + overriding

###### Sealed type + switch

Each subclass implements `arie()` itself. Best when the set of types is open (new subclasses are added often) and the operations are few and stable.

Data types are plain records; operations are `switch` es in one place.

Best when the set of types is closed and new operations are added often (compilers, parsers, protocols).

?

Both are type-safe. Modern Java supports both styles – choose per problem, not by habit.

55

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 56 -->
# 08

### Packages, access control and modules

56

<!-- page 57 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### Packages

- Group related classes and interfaces

- Manage the name space : `java.lang` contains `System` , `Integer` , `String` , …

- Declared with `package name;` – it must be the first statement in the file

```
structuri/Stiva.java
```

```
packagestructuri;
publicinterfaceStiva {
//...
```

```
}
```

- The file is stored in a folder with the same name as the package (case-sensitive)

```
structuri/liste/Lista.java
```

- Subpackages map to subfolders: `structuri.liste` → `structuri/liste/`

```
packagestructuri.liste;
publicclassLista {
//...
```

```
}
```

57

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 58 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### Using classes from packages: qualified names

■ Without `import` , a class from another package is referred to by its fully qualified name : `[pac1.[pac2.[...]]]ClassName`

```
structuri/ArboreBinar.java
```

```
TestStructuri.java
```

```
packagestructuri;
publicclassArboreBinar {
//...
}
```

```
publicclassTestStructuri {
publicstaticvoidmain(String[] args) {
structuri.ArboreBinar ab = newstructuri.ArboreBinar();
//...
}
}
```

58

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 59 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### The import statement

■ One class: `import pac1.[pac2.[...]]ClassName;`

■ All classes of a package, not its subpackages: `import pac1.[pac2.[...]]*;`

■ A file may contain several `import` statements, placed before any class declaration

```
structuri/Heap.java
```

```
packagestructuri;
publicclassHeap {
//...
}
```

###### `Test.java – without import`

```
publicclassTest {
publicstaticvoidmain(String[] args) {
structuri.ArboreBinar ab = newstructuri.ArboreBinar();
structuri.Heap hp = newstructuri.Heap();
}
```

```
}
```

59

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 60 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### The import statement – examples

```
Test.java –single-class import
```

```
importstructuri.ArboreBinar;
```

```
publicclassTest {
publicstaticvoidmain(String[] args) {
ArboreBinar ab = newArboreBinar();
structuri.Heap hp = newstructuri.Heap();
}
```

```
}
```

```
Test.java –on-demand import
```

```
importstructuri.*;
importstructuri.liste.*;  // needed: * excludes
// subpackages
publicclassTest {
publicstaticvoidmain(String[] args) {
ArboreBinar ab = newArboreBinar();
Heap hp = newHeap();
Lista li = newLista();
}
```

```
}
```

60

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 61 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### package + import

- The `package` statement comes before any `import`

- `java.lang` is imported implicitly by the compiler

Order in a source file: `package` → `import` s → type declarations

```
algoritmi/Backtracking.java
```

```
packagealgoritmi;
importstructuri.*;
```

```
publicclassBacktracking {
//...
}
```

61

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 62 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### The unnamed (default) package

```
// Persoana.java
publicclassPersoana { /*...*/}
// Complex.java
classComplex { /*...*/}
// Test.java
publicclassTest {
publicstaticvoidmain(String[] args) {
Persoana p = newPersoana();
Complex c = newComplex();
//...
}
```

A `.java` file without a `package` statement belongs to the unnamed i package . Fine for small tests; real projects always use named packages.

```
}
```

62

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 63 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### Name collisions

###### ■ Two imported packages may contain classes with the same name: use the qualified name

```
unu/A.java
```

```
packageunu;
publicclassA {
//...
}
```

```
doi/A.java
```

```
packagedoi;
publicclassA {
//...
}
```

```
Test.java
importunu.*;
importdoi.*;
publicclassTest {
publicstaticvoidmain(String[] args) {
A a = newA();          // compile error: ambiguous
unu.A a1 = newunu.A();
doi.A a2 = newdoi.A();
}
}
```

63

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 64 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### Access modifiers for class members

|Modifier|Same class|Same package|Subclass (other package)|Everywhere|
|---|---|---|---|---|
|`public`|✓|✓|✓|✓|
|`protected`|✓|✓|✓|–|
|`(none) – package-private`|✓|✓|–|–|
|`private`|✓|–|–|–|

Top-level classes and interfaces can only be `public` or package-private (no modifier). `private` and `protected` are i allowed only for nested classes.

64

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 65 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### Access modifiers – example

`■ Test` is in the unnamed package and imports `structuri.*` . Which statements compile?

```
structuri/Nod.java
```

```
packagestructuri;
classNod {
privateNod urm;
publicNod getUrm() {...}
voidsetUrm(Nod p) {...}
}
```

```
structuri/Coada.java
```

```
packagestructuri;
publicclassCoada {
Nod cap;
publicCoada() { cap = null; }
Coada(inti) {...}
}
```

```
Test.java
```

```
importstructuri.*;
classTest {
voidmain() {
Coada c = newCoada();
Nod n = newNod();
Coada c2 = newCoada(2);
}
```

```
}
```

`new Coada()` – OK (public). `new Nod()` – error: class `Nod` is not public. `new Coada(2)` – error: constructor is package- ? private.

65

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 66 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### protected vs. package-private across packages

```
unu/A.java
```

```
packageunu;
publicclassA {
A(intc, intd) {...}
protectedA(intc) {...}
publicA() {...}
protectedvoidf() {...}
voidh() {...}
}
```

```
unu/DA.java
```

```
packageunu;
classDA extendsA {
DA(intc) {
super(c);
}
}
```

```
doi/DDA.java
```

```
packagedoi;
importunu.*;
classDDA extendsA {
DDA(intc) {
super(c);       // ?
}
DDA(intc, intd) {
super(c, d);    // ?
}
protectedvoidf() {
super.h();      // ?
}
}
```

66

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 67 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### private members are not accessible in subclasses

```
Persoana.java
```

```
Angajat.java
```

```
publicclassPersoana {
privateString nume;
privateintvarsta;
publicPersoana(String nume, intvarsta) {
this.nume = nume;
this.varsta = varsta;
}
```

```
}
```

```
publicclassAngajat extendsPersoana {
privateString departament;
publicAngajat(String nume, intvarsta, String dep) {
super(nume, varsta);
departament = dep;
}
publicString descriere() {
returnnume + ", "+ varsta;  // ERROR: private
}
}
```

`nume` and `varsta` exist in every `Angajat` object, but they are `private` in `Persoana` : the subclass cannot use them by ! name.

67

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 68 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### protected members

###### `Persoana.java`

```
Angajat.java
```

```
publicclassPersoana {
protectedString nume;
protectedintvarsta;
publicPersoana(String nume, intvarsta) {
this.nume = nume;
this.varsta = varsta;
}
```

```
}
```

```
publicclassAngajat extendsPersoana {
protectedString departament;
publicAngajat(String nume, intvarsta, String dep) {
super(nume, varsta);
departament = dep;
}
publicString descriere() {
returnnume + ", "+ varsta;  // OK: protected
}
}
```

`protected` members are visible in the class, in its subclasses and in the same package. Alternative: keep fields `private` i and expose `protected` or `public` getters.

68

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 69 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### Modules (Java 9): a brief look

- A module groups packages and declares, in `module-info.java` :

   - which modules it requires

   - which packages it exports – all others are hidden, even if `public`

```
module-info.java
```

```
modulero.ubb.catalog {
requiresjava.sql;
exportsro.ubb.catalog.api;
```

```
// ro.ubb.catalog.internal stays hidden
```

   - `}`

- The JDK itself is split into modules ( `java.base` , `java.sql` , …)

- Java 25: `import module java.base;` imports all packages exported by a module

- Small projects and this course can ignore modules (classpath mode)

###### `Java 25 – module import`

```
importmodulejava.base;   // List, Map, Path, ...
```

```
publicclassDemo {
```

```
publicstaticvoidmain(String[] args) {
List<String> l = List.of("a", "b");
System.out.println(l);
```

```
}
```

```
}
```

69

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 70 -->
0 8 · P A C K A G E S , A C C E S S , M O D U L E S

#### Summary

- Reuse code by composition (has-a) or inheritance (is-a); override with `@Override` , reach the parent with `super`

- Late binding selects the method from the object's class – the basis of polymorphism

- Abstract classes share state and code; interfaces define types and, since Java 8, can carry default methods

- Override `equals` and `hashCode` together – or use a record

- Enums for fixed sets of constants; sealed types + pattern matching `switch` for closed hierarchies

- Packages organize code; access modifiers and modules control visibility

70

Advanced Programming Methods  ·  Lecture 2 – Object-Oriented Design in Java

<!-- page 71 -->
## Questions?

Next: Lecture 3 – Exceptions and Generics
