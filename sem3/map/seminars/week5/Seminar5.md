<!-- page 1 -->
SEMINAR 5  ·  WEEK 5  ·  26–30 OCTOBER 2026

# Java I/O – and a First Look at A3

Byte and character streams, decorators, text and binary files (Lecture 3) · the new assignment A3 (Laboratory 5 document)

||Agenda|
|---|---|
|A|Assignment A3, a first look: what has to be done and which Java I/O it needs – a discussion before you start.|
|B|Java I/O(Lecture 3): concepts, code reading and short exercises.|
|C|Problem: read a text file, report the invalid lines, write a report.|

## A. Assignment A3: a first look

Read the Laboratory 5 document before the seminar. We discuss the assignment before you write any code – there is no code to show yet.

|Topic|Questions to discuss|
|---|---|
|1. What is new|Which four features does A3 add to the interpreter? Which of them depend on each other – in which order would you implement them?|
|2. Strings and the FileTable|Why can a new type`string`be added without changing the existing classes? Why can the FileTable reuse the generic`IDictionary`from A2? What must the key type `StringValue`provide so that the lookup works?|
|3. From toy statements to Java I/O|Which Java classes and methods does each of`openRFile`,`readFile`,`closeRFile`need? Which Java exceptions can they throw, and why must the interpreter turn them into its own exceptions?|
|4. Two ways of handling a file|The file of`openRFile`stays open across several statements; the log file is opened and closed at every step. Which of the two uses try-with-resources, and why?|
|5. The log file|What does each object in`new PrintWriter(new BufferedWriter(new` `FileWriter(path, true)))`add? What would go wrong without`true`?|
|6. The command menu and the tests|What is the idea of the Command pattern – how do you add a new menu option? How can file statements be tested without files in the project folder?|

## B. Java I/O

### B1. Concepts

Discuss each question with a short example.

|Concept|Questions|
|---|---|
|Byte vs. character streams|What is the difference between`InputStream`/`OutputStream`and`Reader`/`Writer`? Which family for a text file, a`.dat`file, an image, a network connection?|
|Bridges and encodings|What do`InputStreamReader`and`OutputStreamWriter`do, and what do they need to know? Why did a file with Romanian diacritics written on Windows look wrong on Linux before Java 18?|
|Decorators|Why does Java build streams by wrapping one object in another instead of offering one class`File`with all the methods? Name a decorator that adds buffering, one for primitive data, one for lines of text.|

Seminar 5 · Java I/O · page 1

<!-- page 2 -->
|Concept|Questions|
|---|---|
|Buffering and flush|Why is buffered I/O faster? When are the bytes from the buffer actually written? What does`flush()`do, and what happens if the program ends without`close()`?|
|Closing and exceptions|Why is`IOException`checked? What does try-with-resources guarantee when an exception is thrown? In which order are two resources of the same`try`closed?|
|Reading text|`BufferedReader.readLine()`or`Scanner`? What does each return at the end of the file? Why does`Scanner.nextDouble()`depend on the locale?|
|Binary data|What does`DataOutputStream.writeInt(7)`write in the file – how many bytes? Why must the data be read in exactly the order it was written? When is`RandomAccessFile` useful?|

### B2. What is wrong with this code?

Each fragment compiles. Say what happens when it runs, why, and how to fix it (Lecture 3).

##### `1`

```
PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("out.txt")));
pw.println("result: " + 42);
// end of main – out.txt is empty. Why?
```

##### `2`

```
try (var br = new BufferedReader(new FileReader("in.txt"))) {   // in.txt: a, b, c
    while (br.readLine() != null)
        System.out.println(br.readLine());                       // prints b, null
}
 3
```

```
void log(String msg) throws IOException {                        // called after every step
    try (var w = new FileWriter("log.txt")) {
        w.write(msg + "\n");
    }
}                                                 // log.txt keeps one line only
 4
try (var out = new DataOutputStream(new FileOutputStream("s.dat"))) {
    out.writeUTF("Ana");
    out.writeInt(10);
}
try (var in = new DataInputStream(new FileInputStream("s.dat"))) {
    int grade = in.readInt();
    String name = in.readUTF();                                  // garbage or EOFException
}
```

##### `4`

##### `5`

```
Scanner sc = new Scanner(new File("grades.txt"));                // line: Ana 9.50
String name = sc.next();
double grade = sc.nextDouble();     // InputMismatchException on a Romanian system
```

### B3. Short exercises

Write the code on paper or on the board; use try-with-resources everywhere.

|Task|
|---|

|a)|Copy a file of any type (e.g. an image) with`FileInputStream`/`FileOutputStream`, using a`byte[]`buffer of 8 KB. Why does reading one byte at a time take much longer?|
|---|---|
|b)|Count the lines, the words and the characters of a text file (like the Unix command`wc`). Which reader do you use, and how do you split a line into words?|

Seminar 5 · Java I/O · page 2

<!-- page 3 -->
||Task|
|---|---|
|c)|Write the numbers 1 … 10 and their squares into`squares.txt`, one pair per line (`3 9`). Then read the file back with a`Scanner`and print the sum of the squares (385).|
|d)|Write the same ten pairs with a`DataOutputStream`into`squares.dat`and read them back with a `DataInputStream`. Compare the sizes of the two files.|

## C. Problem: a grades report

Write a Java program `GradesReport` that reads the grades of a group of students from a text file and writes a report. Each line of the input file has the form `name|grade` :

##### <u><mark>`grades.txt`</mark></u>

```
Popescu Ion|7.50
Ionescu Maria|9.25
Pop Ana|abc
Marinescu Dan|5.00
Vasilescu Elena|8.75
Georgescu Radu|11
Dumitru Vlad
```

### Requirements

1. Read the name of the input file from the keyboard with a `Scanner` .

2. Read the file line by line with a `BufferedReader` . Skip blank lines.

3. A line is invalid if it does not have exactly two fields, if the grade is not a number, or if the grade is not between 1 and 10. Do not stop: print a message with the line number on `System.err` and continue with the next line.

4. Write `report.txt` with a `PrintWriter` : one line per valid student, aligned, then the number of students, the average and the best student – exactly as below.

5. Use try-with-resources for every file. If the input file cannot be opened, print an error message – the program must not end with a stack trace.

For the file above, the program prints the messages below on `System.err` and writes `report.txt` :

##### <mark>`System.err`</mark>

```
line 3 skipped: Pop Ana|abc (For input string: "abc")
line 7 skipped: Georgescu Radu|11 (grade out of range)
line 8 skipped: Dumitru Vlad (expected name|grade)
```

##### <mark>`report.txt`</mark>

```
Name                 Grade
Popescu Ion           7.50
Ionescu Maria         9.25
Marinescu Dan         5.00
Vasilescu Elena       8.75
--------------------------
Students: 4
Average:  7.63
Best:     Ionescu Maria (9.25)
```

#### Hints

Model a student with a record `Student(String name, double grade)` . Split a line with `line.split("\\|")` – the bar is a special character in regular expressions.

Seminar 5 · Java I/O · page 3

<!-- page 4 -->
`Double.parseDouble` throws `NumberFormatException` , a subclass of `IllegalArgumentException` : one `catch` can handle both a bad number and your own range check.

Format with `pw.printf(Locale.ROOT, "%-20s %5.2f%n", name, grade)` – without `Locale.ROOT` , a Romanian system writes `7,50` .

Separate reading from writing: `List<Student> read(BufferedReader br)` and `void write(List<Student> s, PrintWriter pw)` . The `main` method only opens the files.

### Extensions

- Binary file: also save the valid students in `grades.dat` with a `DataOutputStream` (first their number, then name and grade for each) and write a method that reads them back with a `DataInputStream` . Compare the size of `grades.dat` with that of `grades.txt` .

- Testing: because `read` takes a `BufferedReader` , it can be tested without any file – wrap a string in a `StringReader` . Write JUnit tests for a valid file, a blank line, each kind of invalid line and an empty file.

##### <mark>`GradesReportTest.java`</mark>

```
@Test
void skipsInvalidLines() throws IOException {
    var br = new BufferedReader(new StringReader("Ana|9\nBogdan|x\n\nCarmen|7.5\n"));
    List<Student> s = GradesReport.read(br);
    assertEquals(List.of(new Student("Ana", 9), new Student("Carmen", 7.5)), s);
}
```

Seminar 5 · Java I/O · page 4
