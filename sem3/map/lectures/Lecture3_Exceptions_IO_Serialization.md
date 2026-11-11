<!-- page 1 -->
## Advanced Programming Methods Lecture 3 – Exceptions, I/O and Serialization

```
try (var out = new ObjectOutputStream(new FileOutputStream(f))) { … }
```

<!-- page 2 -->
I N T R O D U C T I O N

#### Lecture overview

Exceptions: try, catch, finally, throw, throws

01

02

Exceptions: modern practice

03 java.io: byte and character streams

04

05

06

Text files and the keyboard

Binary data and random access

Object serialization – and its alternatives

2

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 3 -->
# 01

### Java exceptions

3

<!-- page 4 -->
0 1 · E X C E P T I O N S

#### The exception hierarchy

<!-- Start of picture text -->
Throwable Error Exception VirtualMachineError IOException RuntimeException NullPointerException IllegalArgumentException ArithmeticException IndexOutOfBoundsException ↳ NumberFormatException ↳ ArrayIndexOutOfBoundsException checked – must be caught or declared with throws unchecked – Error (external to the program) and RuntimeException (bugs) <!-- End of picture text -->

4

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 5 -->
0 1 · E X C E P T I O N S

#### Example 1: an uncaught exception

■ Solve `ax + b = 0` for integers `a` , `b`

`■ java P1 1 1` → `Solutie -1` ; `java P1 0 3` → division by zero at (3): lines (4) and (5) are no longer executed

```
P1.java
```

```
java P1 0 3
```

```
classP1 {
publicstaticvoidmain(String[] args) {
inta = Integer.parseInt(args[0]);  // (1)
intb = Integer.parseInt(args[1]);  // (2)
if(b % a == 0)  // (3)
```

```
Exception in thread "main"
java.lang.ArithmeticException:
/ by zero
at P1.main(P1.java:5)
```

```
System.out.println("Solutie "+ (-b / a)); // (4)
else
System.out.println("Nu exista solutie intreaga"); // (5)
```

```
}
```

```
}
```

5

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 6 -->
0 1 · E X C E P T I O N S

#### What happens when an exception occurs

- The JVM creates an exception object describing the abnormal situation

   - 1 abnormal situation

- The object is thrown from the statement that caused it

- It can be caught (handled) – or ignored, as `P1` does

   - 2 exception object created

- An exception nobody catches stops the thread and prints the stack trace

- 3 thrown up the call stack

- caught by a matching catch – or

- 4 the program stops

6

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 7 -->
0 1 · E X C E P T I O N S

#### Catching exceptions: try-catch

- If an exception occurs in the `try` block, the JVM creates the exception object and jumps to the `catch` blocks

- If no exception occurs, the `try` block executes normally and the `catch` blocks are skipped

- A `catch` block executes if the thrown object is compatible with its type (same class or subclass)

- `try` `{`

   - _`// code that might cause // abnormal situations`_

- `}` `catch` `(TipExceptie numeVariabila) {` _`// handling of the // abnormal situation`_

- `}`

7

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 8 -->
0 1 · E X C E P T I O N S

#### Example 2: catching ArithmeticException

```
P2.java
```

```
classP2 {
```

```
publicstaticvoidmain(String[] args) {
try{
```

```
inta = Integer.parseInt(args[0]);  // (1)
intb = Integer.parseInt(args[1]);  // (2)
if(b % a == 0)  // (3)
```

```
run
```

```
java P2 11
Solutie -1
```

```
java P2 03
Nu exista solutie
// executed:
// (1)(2)(3)(6)
```

```
System.out.println("Solutie "+ (-b / a));  // (4)
else
```

```
System.out.println("Nu exista solutie intreaga"); // (5)
} catch(ArithmeticException e) {
```

```
System.out.println("Nu exista solutie");  // (6)
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

8

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 9 -->
0 1 · E X C E P T I O N S

#### Multiple catch clauses

- The `catch` clauses are tried in order ; the first compatible one executes

- At most one `catch` block executes

- Java 7+: one clause can catch several unrelated types: `catch (AE | BE e)`

```
try{
```

   - `// code with possible errors`

- `}` `catch` `(TipExceptie1 numeVariabila1) {` _`// instructions`_

- `}` `catch` `(TipExceptie2 numeVariabila2) {` _`// instructions`_

- `}`

- _`// ...`_

```
catch(TipExceptieN numeVariabilaN) {
// instructions
```

```
}
```

9

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 10 -->
0 1 · E X C E P T I O N S

#### Example 3: two catch clauses

```
P3.java
```

```
classP3 {
```

```
publicstaticvoidmain(String[] args) {
try{
```

```
inta = Integer.parseInt(args[0]);  // (1)
intb = Integer.parseInt(args[1]);  // (2)
if(b % a == 0)  // (3)
```

```
run
```

```
java P3 11
Solutie -1
```

```
java P3 03
Nu exista solutie
```

```
java P3 1
java P3 a b
```

```
System.out.println("Solutie "+ (-b / a));  // (4)
else
```

```
System.out.println("Nu exista solutie intreaga"); // (5)
} catch(ArithmeticException e) {
```

```
System.out.println("Nu exista solutie");  // (6)
} catch(ArrayIndexOutOfBoundsException e) {
System.out.println("java P3 a b");  // (7)
}
```

```
}
```

```
}
```

10

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 11 -->
0 1 · E X C E P T I O N S

#### Nested try statements

```
P4.java
```

```
classP4 {
```

```
publicstaticvoidmain(String[] args) {
try{
```

```
inta = Integer.parseInt(args[0]);  // (1)
intb = Integer.parseInt(args[1]);  // (2)
try{
if(b % a == 0)  // (3)
```

```
run
```

```
java P4 11
Solutie -1
```

```
java P4 03
Nu exista solutie
```

```
java P4 1
java P4 a b
```

```
System.out.println("Solutie "+ (-b / a)); // (4)
else
```

```
System.out.println("Nu exista solutie intreaga"); // (5)
```

```
} catch(ArithmeticException e) {
```

```
System.out.println("Nu exista solutie");  // (6)
}
```

- `}` `catch` `(ArrayIndexOutOfBoundsException e) { System.out.println("java P4 a b");` _`// (7)`_

- `}`

```
}
```

```
}
```

11

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 12 -->
0 1 · E X C E P T I O N S

#### The finally clause

- The `finally` block executes in every situation : normal completion, caught exception, uncaught exception, `return`

- Typical use: releasing resources (files, connections, locks)

- `try` `{` _`//...`_

- `}` `catch` `(TipExceptie1 numeVar1) {` _`// instructions`_

<!-- Start of picture text -->
} [ catch (TipExceptieN numeVarN) { // ... }] [ finally { // instructions }] <!-- End of picture text -->

12

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 13 -->
0 1 · E X C E P T I O N S

#### When does finally execute?

<!-- Start of picture text -->
A Situation Executed blocks try { B }  catch (TipExceptie nume) { C No exception in B A  B  D  E }  finally { D } Exception in B, caught by C A  B…  C  D  E E A  B…  D  → exits the Exception in B, not caught method Exception in B, caught, C contains return A  B…  C  D  → returns B contains return A  B  D  → returns <!-- End of picture text -->

_B… = only part of B executes_

13

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 14 -->
0 1 · E X C E P T I O N S

#### finally in practice – and try-with-resources

```
with finally
```

```
Java 7+: try-with-resources
```

```
publicvoidwriteElem(int[] vec) {
PrintWriter out = null;
try{
out = newPrintWriter(
newFileWriter("fisier.txt"));
for(intelem : vec)
out.print(" "+ elem);
} catch(IOException e) {
System.err.println("IOException: "+ e);
} finally{
if(out != null)
out.close();
}
```

```
publicvoidwriteElem(int[] vec) {
try(PrintWriter out = newPrintWriter(
newFileWriter("fisier.txt"))) {
for(intelem : vec)
out.print(" "+ elem);
} catch(IOException e) {
System.err.println("IOException: "+ e);
}   // out.close() is called automatically
```

```
}
```

```
}
```

Any class implementing `AutoCloseable` can be used in try-with-resources; resources are closed in reverse order of i creation.

14

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 15 -->
0 1 · E X C E P T I O N S

#### Defining exception classes

- Derive from `Exception` → a checked exception

- Derive from `RuntimeException` → an unchecked exception

- Provide at least a no-arg constructor and one taking a message

```
ExceptieNoua.java
```

```
publicclassExceptieNoua extendsException {
publicExceptieNoua() { }
publicExceptieNoua(String mesaj) {
super(mesaj);
}
}
```

15

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 16 -->
0 1 · E X C E P T I O N S

#### Declaring exceptions: throws

■ A method declares the checked exceptions it may throw with `throws` in its header

```
A.java
```

```
publicclassExceptieNoua extendsException { }
```

■ Several exceptions can be listed; their order does not matter

```
publicclassA {
publicvoidf() throwsExceptieNoua {
//...
}
```

```
}
```

###### `B.java`

```
publicclassExceptie1 extendsException { }
```

```
publicclassB {
```

```
publicintg(intd) throwsExceptieNoua, Exceptie1 {
//...
```

```
}
```

```
}
```

16

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 17 -->
0 1 · E X C E P T I O N S

#### Throwing exceptions: throw

- `throw` raises an exception object; the method's execution stops immediately

■ Every checked exception that can leave the method must be declared in its `throws` clause

```
B.java
```

```
publicclassB {
publicintg(intd) throwsExceptieNoua, Exceptie1 {
if(d == 3)
return10;
if(d == 7)
thrownewExceptieNoua();
if(d == 5)
thrownewExceptie1();
return0;
}
//...
}
```

17

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 18 -->
0 1 · E X C E P T I O N S

#### Calling a method that throws

- Handle the exception with `try-catch` , or

- Propagate it: an exception that is not caught must be declared in the caller's `throws`

<!-- Start of picture text -->
handle handle one, propagate the other public class C { public class C { public void h(A a) { public void t(B b)  throws ExceptieNoua { try { try { a.f(); int rez = b.g(8); }  catch (ExceptieNoua e) { }  catch (Exceptie1 e) {    // only Exceptie1 is caught System.err.println("Exceptie " + e); System.err.println("Exceptie " + e); } } } } } } <!-- End of picture text -->

18

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 19 -->
0 1 · E X C E P T I O N S

#### Exceptions and constructors

■ A subclass constructor must declare all exceptions of the base-class constructor it calls – explicitly or implicitly

■ It may declare additional exceptions

```
A.java
```

```
publicclassA {
publicA() throwsExceptie1 { }
publicA(inti) { }
```

```
}
```

###### `B.java`

```
publicclassB extendsA {
```

```
publicB() throwsExceptie1 { }    // implicit super()
publicB(inti) {
```

```
super(i);                      // A(int) throws nothing
}
publicB(charc) throwsExceptie1, ExceptieNoua { }
}
```

19

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 20 -->
0 1 · E X C E P T I O N S

#### Exceptions and method overriding

- An overriding method may declare fewer exceptions than the overridden one

- It may declare only exceptions that are the same as or subclasses of the declared ones – never new checked exceptions

- The same rules apply to methods implementing interfaces

```
publicclassExceptie3 extendsExceptie1 { }
```

```
publicclassAA {
```

```
publicvoidf() throwsExceptie1, Exceptie2 { }
publicvoidg() { }
publicvoidh() throwsExceptie1 { }
```

```
}
```

```
publicclassBB extendsAA {
```

```
publicvoidf() throwsExceptie1 { }  // OK: fewer
publicvoidg() throwsExceptie2 { }  // ERROR: new
publicvoidh() throwsExceptie3 { }  // OK: subclass
```

```
}
```

20

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 21 -->
0 1 · E X C E P T I O N S

#### Overriding and exceptions – which versions compile?

```
publicclassA {
publicvoidf() throwsAE, BE { }
publicvoidg() throwsAE { }
}
```

```
publicclassB extendsA {        // consider each alone:
publicvoidg() { }                       // (1) ?
publicvoidf() throwsAE, BE, CE { }     // (2) ?
publicvoidf() throwsAE, BE, DE { }     // (3) ?
publicvoidg() throwsDE { }             // (4) ?
```

```
}
```

<!-- Start of picture text -->
Exception AE BE DE CE <!-- End of picture text -->

21

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 22 -->
0 1 · E X C E P T I O N S

#### Order of catch clauses

- The JVM selects the first `catch` clause whose type matches the thrown exception

- Exception `X` matches clause type `Y` if `X` is `Y` or a subclass of `Y` → catch specific types first

<!-- Start of picture text -->
✗ does not compile public class C { public void g(B b) { try { b.f(); }  catch (Exception e) {  /*...*/ } catch (CE ce) {  /*...*/ }    // ERROR catch (AE ae) {  /*...*/ } catch (BE be) {  /*...*/ } } } <!-- End of picture text -->

✓ `correct` `public class` `C {` `public void` `g(B b) {` `try` `{ b.f(); }` `catch` `(CE ce) {` _`/*...*/`_ `}` `catch` `(AE ae) {` _`/*...*/`_ `}` `catch` `(BE be) {` _`/*...*/`_ `}` `catch` `(Exception e) {` _`/*...*/`_ `} } }`

22

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 23 -->
0 1 · E X C E P T I O N S

#### Re-throwing and wrapping exceptions

- A caught exception can be re-thrown : `throw be;`

- Or wrapped in a new exception that keeps the original as its _cause_ (exception chaining)

■ The cause is available later through `getCause()`

```
C.java
```

```
Exceptie4.java
```

```
publicclassC {
publicinth(A a) throwsExceptie4, BE {
try{
a.f();
```

```
} catch(BE be) {
System.out.println("Rearuncata: "+ be);
throwbe;
```

```
} catch(AE ae) {
thrownewExceptie4("mesaj", ae);
}
return0;
}
```

```
publicclassExceptie4 extendsException {
publicExceptie4() { }
publicExceptie4(String message) {
super(message);
}
publicExceptie4(String message,
Throwable cause) {
super(message, cause);
}
```

```
}
```

```
}
```

23

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 24 -->
# 02 Exceptions: modern practice

24

<!-- page 25 -->
0 2 · E X C E P T I O N S : M O D E R N P R A C T I C E

#### Exceptions: good practice

##### Catch what you can handle

Catch specific types where you can do something useful; let the rest propagate.

##### Fail fast

Validate arguments at the start of a method: `Objects.requireNonNull(x, "x")` .

##### Never swallow exceptions

An empty `catch {}` hides bugs. At least log the exception – or rethrow it wrapped.

##### Useful messages

Put context in the message and keep the cause: `new AppException("cannot load " + file, e)` .

##### Checked vs. unchecked

Checked: recoverable conditions (missing file). Unchecked: programming errors – `IllegalArgumentException` , `IllegalStateException` .

##### Not for control flow

Exceptions are for exceptional situations – test conditions with `if` , not with `try` .

25

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 26 -->
0 2 · E X C E P T I O N S : M O D E R N P R A C T I C E

#### NullPointerException: prevent it, read it

- Java 14 added helpful messages that name the null expression (on by default since Java 15)

```
Persoana p = newPersoana(null, 20);
intn = p.getNume().length();
```

- Validate early with

```
Objects.requireNonNull
```

###### `Java 15+ message`

- Return empty collections or `Optional` (Lecture 5) instead of `null`

```
Exception in thread "main"java.lang.NullPointerException:
Cannot invoke "String.length()"because the return
value of "Persoana.getNume()"is null
```

###### `fail fast`

```
publicPersoana(String nume, intvarsta) {
this.nume = Objects.requireNonNull(nume, "nume");
this.varsta = varsta;
```

```
}
```

26

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 27 -->
0 2 · E X C E P T I O N S : M O D E R N P R A C T I C E

#### Modern exception syntax in one slide

###### `multi-catch (Java 7)`

###### `unnamed variable (Java 22)`

```
try{
```

```
proceseaza(fisier);
```

- `}` `catch` `(IOException | ParseException e) { System.err.println("cannot process: " + e);`

- `}`

```
intn;
try{
```

- `n = Integer.parseInt(text);`

- `}` `catch` `(NumberFormatException _) {` _`// not used`_ `n = 0;`

- `}`

###### `try-with-resources on an existing variable (Java 9)`

###### `custom unchecked exception`

```
varbr = Files.newBufferedReader(path);
try(br) {                        // br is effectively final
System.out.println(br.readLine());
```

```
}
```

```
publicclassStocInsuficientException
extendsRuntimeException {
publicStocInsuficientException(String msg) {
super(msg);
}
```

```
}
```

27

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 28 -->
# 03

### java.io streams

28

<!-- page 29 -->
0 3 · J A V A . I O S T R E A M S

#### java.io at a glance

An I/O stream is a sequence of data flowing from a source (file, memory, network, keyboard) or to a destination. Some streams only pass data on; others transform it.

```
bytes
```

##### Byte streams

`InputStream` , `OutputStream` – raw bytes: images, binary files, network data

```
chars
```

##### Character streams

`Reader` , `Writer` – text, decoded with a character set (UTF-8, …)

```
byte
```

```
char
```

##### Bridges

`InputStreamReader` , `OutputStreamWriter` – convert between bytes and characters

```
tools
```

##### Utilities

`Scanner` (parsing), `PrintWriter` (formatting), `RandomAccessFile` , `File`

Almost every I/O method can throw a checked `IOException` ( `FileNotFoundException` , `EOFException` …). Every ! stream must be closed – use try-with-resources.

29

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 30 -->
0 3 · J A V A . I O S T R E A M S

#### Byte streams: InputStream and OutputStream

|InputStream (abstract)|OutputStream (abstract)|
|---|---|
|`int read()`– one byte, or -1 at the end|`void write(int b)`– one byte|
|`int read(byte[] b)`– up to b.length bytes; count or -1|`void write(byte[] b)`|
|`int read(byte[] b, int off, int len)`|`void write(byte[] b, int off, int len)`|
|`int available()`– bytes readable without blocking|`void flush()`– force buffered data out|
|`byte[] readAllBytes()`(Java 9)|–|
|`long transferTo(OutputStream out)`(Java 9)|–|
|`void close()`|`void close()`|

_Subclasses decide where the bytes come from or go to: FileInputStream, ByteArrayInputStream, socket streams …_

30

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 31 -->
0 3 · J A V A . I O S T R E A M S

#### Copying a file: before and after try-with-resources

###### `before Java 7`

###### `Java 7+`

```
FileInputStream in = null;
FileOutputStream out = null;
try{
in = newFileInputStream("fisier.txt");
out = newFileOutputStream("fisier2.txt");
intc;
while((c = in.read()) != -1)
out.write(c);
} catch(IOException e) {
System.err.println("Eroare "+ e);
} finally{
if(in != null)
try{ in.close(); }
catch(IOException e) { System.err.println("Eroare "+ e); }
if(out != null)
try{ out.close(); }
catch(IOException e) { System.err.println("Eroare "+ e); }
}
```

```
try(varin = newFileInputStream("fisier.txt");
varout = newFileOutputStream("fisier2.txt")) {
intc;
while((c = in.read()) != -1)
out.write(c);
} catch(IOException e) {
System.err.println("Eroare "+ e);
}
```

```
// Java 9: in.transferTo(out);
// NIO.2:  Files.copy(src, dst);
```

Resources are closed automatically, in reverse order, even when an exception occurs. Byte-by-byte copying is slow without i buffering – see decorators.

31

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 32 -->
0 3 · J A V A . I O S T R E A M S

#### Character streams: Reader and Writer

- Same shape as byte streams, but for `char` values (UTF-16 code units in memory)

- Bytes on disk are decoded with a charset; since Java 18 the default is UTF-8

- `Writer` adds `write(String)` and `append`

```
try(FileReader input = newFileReader("Fisier.txt");
FileWriter output = newFileWriter("Fisier2out.txt")) {
intc;
while((c = input.read()) != -1)
output.write(c);
} catch(IOException e) {
System.err.println("Eroare la citire/scriere "+ e);
}
```

32

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 33 -->
0 3 · J A V A . I O S T R E A M S

#### The java.io class map

|Purpose|Byte streams|Character streams|
|---|---|---|
|Files|`FileInputStream`,`FileOutputStream`|`FileReader`,`FileWriter`|
|Memory|`ByteArrayInputStream`, `ByteArrayOutputStream`|`CharArrayReader`,`StringReader`, `StringWriter`|
|Buffering|`BufferedInputStream`,`BufferedOutputStream`|`BufferedReader`,`BufferedWriter`|
|Formatting|`PrintStream`|`PrintWriter`|
|Primitive data|`DataInputStream`,`DataOutputStream`|–|
|Objects|`ObjectInputStream`,`ObjectOutputStream`|–|
|Conversion|`InputStreamReader`(bytes → chars)|`OutputStreamWriter`(chars → bytes)|

33

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 34 -->
0 3 · J A V A . I O S T R E A M S

#### Wrapping streams: the Decorator pattern

<!-- Start of picture text -->
file FileInputStream BufferedInputStream DataInputStream program reads bytes from disk adds a buffer adds readInt, readUTF … DataInputStream in =  new DataInputStream( new BufferedInputStream( new FileInputStream("date.bin"))); <!-- End of picture text -->

- Each wrapper is itself a stream and adds one capability

- ■ Combine them freely: buffering + data + compression ( `GZIPInputStream` ) … ■ Closing the outer stream closes the whole chain

34

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 35 -->
0 3 · J A V A . I O S T R E A M S

#### Standard streams

- `System.in` – an `InputStream` (keyboard)

- `System.out` , `System.err` – `PrintStream` s (console)

```
System.setOut(newPrintStream(newFile("Output.txt")));
System.setErr(newPrintStream(newFile("Erori.txt")));
System.out.println("goes to Output.txt");
System.err.println("goes to Erori.txt");
```

- They can be redirected: `System.setIn` , `System.setOut` , `System.setErr`

- `System.console()` – interactive console (e.g. reading passwords)

35

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 36 -->
# 04 Text files and the keyboard

36

<!-- page 37 -->
0 4 · T E X T F I L E S A N D T H E K E Y B O A R D

#### Running example: a list of students

```
Studenti.txt
```

```
Student.java –a record (Lecture 2)
```

```
Vasilescu Maria|8.9
Popescu Ion|6.7
Marinescu Ana|9.6
Ionescu George|7.53
Pop Vasile|9.3
```

```
publicrecordStudent(String nume, doublemedia)
implementsSerializable {
publicstaticStudent parse(String linie) {
String[] p = linie.split("\\|");
if(p.length < 2)
```

```
thrownewIllegalArgumentException("Linie invalida: "+ linie);
returnnewStudent(p[0].strip(), Double.parseDouble(p[1].strip()));
}
```

```
}
```

i Task: read the list (from a file or the keyboard) and save it sorted by average – in text, binary and serialized form.

37

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 38 -->
0 4 · T E X T F I L E S A N D T H E K E Y B O A R D

#### Reading text: BufferedReader

- `BufferedReader` reads large blocks and offers `readLine()` – `null` at the end

- Invalid lines are reported and skipped

- The `IOException` is declared – the caller decides how to react

```
List<Student> citesteStudenti(String numeFis) throwsIOException {
List<Student> ls = newArrayList<>();
try(BufferedReader br = newBufferedReader(newFileReader(numeFis))) {
String linie;
while((linie = br.readLine()) != null) {
try{
ls.add(Student.parse(linie));
} catch(IllegalArgumentException e) {   // incl. NumberFormatException
System.err.println(e.getMessage());
}
}
}
returnls;
```

```
}
```

38

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 39 -->
0 4 · T E X T F I L E S A N D T H E K E Y B O A R D

#### Writing text: BufferedWriter and PrintWriter

###### `BufferedWriter`

```
PrintWriter –print, println, printf
```

```
voidscrieBW(List<Student> studs, String numeFis)
throwsIOException {
```

```
try(varbw = newBufferedWriter(newFileWriter(numeFis))) {
for(Student s : studs) {
```

```
bw.write(s.nume() + "|"+ s.media());
bw.newLine();                // line separator
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

```
// append instead of overwrite:
```

```
// new FileWriter(numeFis, true)
```

```
voidscriePW(List<Student> studs, String numeFis)
throwsIOException {
```

```
try(varpw = newPrintWriter(numeFis)) {
for(Student s : studs)
```

```
pw.println(s.nume() + "|"+ s.media());
```

```
}
```

```
}
```

```
// PrintWriter never throws IOException
```

```
// while writing –check pw.checkError()
```

39

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 40 -->
0 4 · T E X T F I L E S A N D T H E K E Y B O A R D

#### Formatted output to a file

```
voidscrieTabel(List<Student> studs, String numeFis)result
throwsIOException {
try(varpw = newPrintWriter(numeFis)) {------------------------------------------------
String linie = "-".repeat(48);|   1| Popescu Ion                    |  6.70|
------------------------------------------------
intcrt = 0;
for(Student s : studs) {|   2| Ionescu George                 |  7.53|
pw.println(linie);------------------------------------------------
pw.printf(Locale.ROOT, "| %3d | %-30s | %5.2f |%n",|   3| Vasilescu Maria                |  8.90|
++crt, s.nume(), s.media());------------------------------------------------
}
|   4| Pop Vasile                     |  9.30|
if(crt > pw.println(linie);0)------------------------------------------------
|   5| Marinescu Ana                  |  9.60|
}
}------------------------------------------------
```

40

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 41 -->
0 4 · T E X T F I L E S A N D T H E K E Y B O A R D

#### Reading from the keyboard: Scanner

- `Scanner` (in `java.util` ) splits input into tokens and parses them

`■ nextInt` , `nextDouble` , `nextLine` , `next` … and the tests `hasNextInt` , `hasNextDouble` …

- Locale-dependent: in a Romanian locale `nextDouble` expects `9,5` – use `useLocale(Locale.ROOT)` for `9.5`

- After `nextDouble` , the rest of the line is still there – consume it with `nextLine`

```
List<Student> citesteDeLaTastatura() {
List<Student> lista = newArrayList<>();
Scanner sc = newScanner(System.in).useLocale(Locale.ROOT);
System.out.println("Scrieti \"gata\" la final");
while(true) {
System.out.print("Nume: ");
String nume = sc.nextLine();
if(nume.equalsIgnoreCase("gata")) break;
System.out.print("Media: ");
while(!sc.hasNextDouble()) {
System.out.println("Trebuie sa introduceti media");
sc.nextLine();                     // discard bad input
}
doublemedia = sc.nextDouble();
sc.nextLine();                         // consume <Enter>
lista.add(newStudent(nume, media));
```

```
}
returnlista;      // do not close a Scanner over System.in
}
```

41

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 42 -->
0 4 · T E X T F I L E S A N D T H E K E Y B O A R D

#### Scanner over a file

- A `Scanner` can read from a `Path` , `File` , `InputStream` or `String`

- `useDelimiter` changes the token separator (default: whitespace)

- Alternative for reading from the keyboard: `new BufferedReader(new InputStreamReader(System.in))`

```
try(Scanner in = newScanner(Path.of("intregi.txt"))) {
// in.useDelimiter(",");
while(in.hasNextInt()) {
intnr = in.nextInt();
System.out.println("nr = "+ nr);
}
```

- `}` `catch` `(IOException e) { System.err.println("Eroare " + e);`

- `}`

42

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 43 -->
# 05

### Binary data and random access

43

<!-- page 44 -->
0 5 · B I N A R Y D A T A A N D R A N D O M A C C E S S

#### Binary data: DataOutputStream and DataInputStream

`■ writeInt` , `writeDouble` , `writeUTF` … and the matching `readXxx`

- Data must be read back in exactly the order and types it was written

- Writing the count first avoids using `EOFException` for control flow

```
voidscrieBinar(List<Student> studs, String f) throwsIOException {
try(varout = newDataOutputStream(
```

```
newBufferedOutputStream(newFileOutputStream(f)))) {
out.writeInt(studs.size());           // header: how many
for(Student s : studs) {
```

```
out.writeUTF(s.nume());
out.writeDouble(s.media());
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

```
List<Student> citesteBinar(String f) throwsIOException {
try(varin = newDataInputStream(
```

```
newBufferedInputStream(newFileInputStream(f)))) {
intn = in.readInt();
```

```
List<Student> rez = newArrayList<>(n);
```

```
for(inti = 0; i < n; i++)
```

```
rez.add(newStudent(in.readUTF(), in.readDouble()));
returnrez;
```

```
}
```

```
}
```

44

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 45 -->
0 5 · B I N A R Y D A T A A N D R A N D O M A C C E S S

#### RandomAccessFile

- Read and write anywhere in a file; mode `"r"` or `"rw"`

- A file pointer marks the current position; reads and writes advance it

- `■ seek(pos)` , `getFilePointer()` , `length()`

- Same `readXxx` / `writeXxx` methods as the data streams

```
append at the end
```

```
voidadaugaStudent(Student s, String f) throwsIOException {
try(varraf = newRandomAccessFile(f, "rw")) {
raf.seek(raf.length());        // jump to the end
raf.writeUTF(s.nume());
raf.writeDouble(s.media());
```

```
}
}
```

###### `read until the end`

```
List<Student> citesteRAF(String f) throwsIOException {
List<Student> rez = newArrayList<>();
try(varraf = newRandomAccessFile(f, "r")) {
while(raf.getFilePointer() < raf.length())
rez.add(newStudent(raf.readUTF(), raf.readDouble()));
}
returnrez;
}
```

45

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 46 -->
# 06

### Serialization

46

<!-- page 47 -->
0 6 · S E R I A L I Z A T I O N

#### Serialization: objects bytes

<!-- Start of picture text -->
ObjectOutputStream bytes ObjectInputStream object graph writeObject file · network readObject serialization deserialization <!-- End of picture text -->

- Serialization converts the state of an object into a byte stream – to save it or send it over the network

- Deserialization rebuilds an equivalent object from those bytes

- An object is _persistent_ if it can be written to and read back from external storage

- Built into Java since 1.1 – powerful, but with important pitfalls (see the end of this section)

47

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 48 -->
0 6 · S E R I A L I Z A T I O N

#### Writing and reading objects

###### `serialize`

###### `deserialize`

```
voidserializeaza(String f) throwsIOException {
try(varout = newObjectOutputStream(
newFileOutputStream(f))) {
out.writeObject(23);              // Integer
out.writeObject("Vasilescu Ana");
out.writeObject(23.45f);          // Float
}
```

```
}
```

```
voiddeserializeaza(String f)
throwsIOException, ClassNotFoundException {
try(varin = newObjectInputStream(
newFileInputStream(f))) {
Integer intreg = (Integer) in.readObject();
String text = (String) in.readObject();
Float nr = (Float) in.readObject();
System.out.println(intreg + " "+ text + " "+ nr);
}
```

```
}
```

`readObject` returns `Object` : cast to the expected type, in the same order. `ClassNotFoundException` signals that the i class of the stored object is not available.

48

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 49 -->
0 6 · S E R I A L I Z A T I O N

#### Making a class serializable

- The class must implement the marker interface `java.io.Serializable` (no methods)

- All non-static, non-transient fields are saved

- Every object referenced by a field must be serializable too – otherwise `NotSerializableException`

- Records are serialized by their components and rebuilt through the canonical constructor – so validation runs again

   - `class` `Student` `implements` `Comparable<Student>, Serializable {` _`//...`_

   - `}`

   - _`// or simply:`_

```
recordStudent(String nume, doublemedia) implementsSerializable { }
```

- `try` `(` `var` `out =` `new` `ObjectOutputStream(` `new` `FileOutputStream("s.bin"))) { out.writeObject(` `new` `Student("Popescu Ioan", 7.9));`

- `}`

49

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 50 -->
0 6 · S E R I A L I Z A T I O N

#### Object graphs: each object is written once

###### `writing`

###### `reading`

```
ObjectOutputStream out = ...;
out.writeObject(newProdus("A"));
Produs produs2 = newProdus("B");
out.writeObject(produs2);
produs2.setNume("BB");
out.writeObject(produs2);   // only a back-reference!
out.close();
```

```
ObjectInputStream in = ...;
Produs p1 = (Produs) in.readObject();
Produs p2 = (Produs) in.readObject();
Produs p3 = (Produs) in.readObject();
// p3.getNume() = ?   p2 == p3 ?
```

All objects reachable through references are saved – once . Shared and circular references (e.g. a circular list) survive intact. ? Static fields are not saved.

50

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 51 -->
0 6 · S E R I A L I Z A T I O N

#### Saving a whole collection

###### `save`

```
load
```

```
voidsalveaza(List<Student> studs, String f)
throwsIOException {
try(varout = newObjectOutputStream(
newFileOutputStream(f))) {
out.writeObject(newArrayList<>(studs));
}
}
```

```
@SuppressWarnings("unchecked")
List<Student> incarca(String f)
throwsIOException, ClassNotFoundException {
try(varin = newObjectInputStream(
newFileInputStream(f))) {
return(List<Student>) in.readObject();
}
}
```

The standard collections are serializable when their elements are. The cast to `List<Student>` is unchecked – type erasure, i explained in Lecture 4.

51

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 52 -->
0 6 · S E R I A L I Z A T I O N

#### What readObject and writeObject really do

- `writeObject(o)` saves the class description and the non-static, non-transient fields – recursively

- `readObject()` reads the class description, creates the object without calling its constructor , and fills the fields byte by byte

   - only the no-arg constructor of the first non-serializable superclass runs

- Consequence: constructor validation is bypassed – a crafted byte stream can create invalid objects

- Records are the exception: they are always rebuilt through the canonical constructor

52

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 53 -->
0 6 · S E R I A L I Z A T I O N

#### Class evolution: serialVersionUID

- Scenario: objects are serialized, the class changes, the old objects must be read again

- Without an explicit `serialVersionUID` , the JVM computes one from the class structure (fields, interfaces, non-private methods and constructors) – typical changes such as adding a field or method make old data unreadable

```
publicclassStudent implementsSerializable {
privatestaticfinallongserialVersionUID = 1L;
privateString nume;
privatedoublemedia;
privateintgrupa;      // added later: 0 when reading old data
//...
}
```

   - ( `InvalidClassException` )

- With a fixed value, compatible changes are tolerated: new fields get default values

53

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 54 -->
0 6 · S E R I A L I Z A T I O N

#### Excluding fields: transient

- Some fields must not be saved: passwords, caches, file handles, connections

- Declare them `transient`

- After deserialization they hold the default value of their type

```
publicclassStudent implementsSerializable {
privateString nume;
privatedoublemedia;
privatetransientString parola;   // not written
//...
```

- `}`

54

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 55 -->
0 6 · S E R I A L I Z A T I O N

#### Serialization and security

- Never deserialize untrusted data : a crafted stream can instantiate unexpected classes ("gadget chains") – a long list of real vulnerabilities

- Java 9: deserialization filters ( `ObjectInputFilter` ) – allow-list the expected classes

- Java 17: JVM-wide filter factories

- Modern advice (Effective Java, item 85): prefer other formats for new designs

   - `ObjectInputFilter filtru = ObjectInputFilter.Config.createFilter(`

         - `"ro.ubb.catalog.*;java.base/*;!*");` _`// allow these, reject rest`_

   - `try` `(` `var` `in =` `new` `ObjectInputStream(` `new` `FileInputStream(f))) {`

      - `in.setObjectInputFilter(filtru);`

      - `Object o = in.readObject();` `// InvalidClassException if rejected`

   - `}`

55

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 56 -->
0 6 · S E R I A L I Z A T I O N

#### Alternatives: text and schema-based formats

■ JSON – readable, language-neutral; libraries such as Jackson or Gson map records directly

- XML , CSV – for documents and tabular data

```
Jackson (library, not part of the JDK)
```

```
ObjectMapper om = newObjectMapper();
```

```
String json = om.writeValueAsString(newStudent("Ana", 9.5));
// {"nume":"Ana","media":9.5}
```

```
Student s = om.readValue(json, Student.class);
```

- Protocol Buffers , Avro – compact, schema-based, versioned

```
List<Student> lista = om.readValue(Path.of("studenti.json").toFile(),
newTypeReference<List<Student>>() { });
```

- Advantages: inspectable data, other languages can read it, no arbitrary class instantiation

56

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 57 -->
0 6 · S E R I A L I Z A T I O N

#### Summary

- Checked exceptions must be caught or declared; unchecked ones signal bugs

- `finally` always runs; prefer try-with-resources for anything `AutoCloseable`

- Overriding methods may not add new checked exceptions; catch specific types first

- Byte streams for binary data, character streams for text; bridges convert with a charset (UTF-8 by default since Java 18)

- Decorators add capabilities: buffering, primitive data, objects

- Serialization is convenient but risky: `serialVersionUID` , `transient` , filters – prefer JSON or schemas for exchange

57

Advanced Programming Methods  ·  Lecture 3 – Exceptions, I/O and Serialization

<!-- page 58 -->
## Questions?

Next: Lecture 4 – Generics and Collections
