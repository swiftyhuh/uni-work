<!-- page 1 -->
# LECTURE 7. FUNCTIONAL PROGRAMMING From mathematical foundations to Lisp

# Contents

1. Why Functional Programming?

2. Mathematical Foundations: Computability and Lambda Calculus

3. The Birth of Lisp: McCarthy, MIT, and Symbolic AI

4. Fundamental Principles and Functional Languages

5. Functional, Imperative, and Object-Oriented Programming

6. The Evolution of Lisp

7. Lisp’s Legacy and Modern Functional Programming

1

<!-- page 2 -->
# 1. Why Functional Programming?

A question to begin with. Suppose we want to compute the sum of the squares of all even numbers in a list. An imperative solution tells the computer how to proceed: initialize a variable, iterate, test, and update. A functional solution describes a transformation: filter the even numbers, square them, and reduce the results by addition. The two approaches may compute the same answer, but they encourage different ways of thinking.

Object-oriented programming organizes programs around objects that combine state and behavior . Functional programming emphasizes the evaluation and composition of functions , often favoring immutable data and minimizing side effects. Most practical languages, including Common Lisp, support several programming styles.

There are two main things needed to be known to understand the concept:

- Immutable data : Immutability is a common functionalprogramming principle, not a universal requirement. An immutable value is not modified in place; instead, an updated value or data structure is produced. Many functional and multi-paradigm languages also permit mutable data.

- Stateless functions : A pure function returns the same result for the same arguments and has no observable side effects. While functional languages may also contain stateful functions, stateless functions are the essence.

2

<!-- page 3 -->
Functional programming is a programming paradigm — a style of building the structure and elements of computer programs — that treats computation as the evaluation of mathematical functions and avoids changing-state and mutable data.

An intellectual shift. A conventional program is often explained as a sequence of changes to memory. A functional program is more naturally explained as the evaluation and composition of expressions. The distinction is about how we describe computation, not merely about syntax. Even a programmer working in C++ or Python can adopt the functional perspective.

Functional programming is primarily a new programming paradigm, comparable in importance to the promotion of structured programming. It is important to emphasize that functional programming brings with it a new programming discipline, usable even in the absence of programming languages. A complete approach to the issue of functional programming must contain all three hypostases under which it can be used, namely:

1. method for developing reliable programs;

2. means of analyzing the efficiency of programs;

3. method of analyzing the correctness of programs.

Functional programming is a paradigm that can be adopted within both dedicated functional languages and multi-paradigm languages. Its effectiveness depends on the problem, implementation, and programming discipline; it is not necessarily equally efficient in every language.

3

<!-- page 4 -->
Functional programming is also known as application programming or value-oriented programming. Its importance for the current moment results from the following reasons (which also represent defining features of functional programming):

- assignment instruction : pure functional code avoids assignments that mutate shared state; many functional languages, including Lisp dialects, also support assignment and mutable objects; these are usually isolated or controlled when a functional style is desired;

- functional programming encourages thinking at a higher level of abstraction , allowing through higher order functions (socalled functional forms) to change the behavior of existing programs and combine them (practice called programming in the large - working with larger units than individual instructions ).

- parallel execution : pure functions and immutable data can simplify parallel execution by reducing interference between computations; this advantage does not imply that functional languages will necessarily replace imperative languages, or that evaluation order is irrelevant when effects are present;

- denotational semantics : Denotational semantics assigns mathematical meanings to programs, often using functions and domains. It is not simply the translation of every imperative program into an equivalent functional program.

- Artificial intelligence has been the basis for promoting

- functional programming. Artificial intelligence, through the problems of specific applications (simulation of human cognitive processes, automatic translation, retrieval of information) requires, first of all, symbolic processing and less numerical calculations. This increased "power" of expressing (symbolic) calculations could be obtained on the basis of formal

4

<!-- page 5 -->
mathematical logical models such as lambda calculus (Lisp) or Markov normal algorithms (Snobol). AI today also relies heavily on statistical learning and numerical optimization. Lambda calculus was introduced by Church in the 1930s, and Markov normal algorithms were developed in 1954.

The characteristic of symbolic data processing languages consists in the possibility of manipulating data structures, no matter how complex, structures that are built dynamically (during the execution of the program). The information provided by this data mainly highlights the properties of the objects as well as the relationships between them. Data is usually strings, lists, or binary trees.

A concrete symbolic problem. Differentiate the expression x² + 3x symbolically. The expected output is another expression, 2x + 3, not a numerical answer at one chosen value of x. To do this, a program must recognize the internal structure of an expression, apply algebraic rules, and construct a new expression. This is a natural motivation for Lisp and its recursive list structures.

Not much emphasis will be placed on issues of functional language implementation, for the following reasons:

- Functional languages on conventional computers are implemented using compilers, interpreters, runtime systems, and calling conventions. Implementations may employ closures, garbage collection, tail-call optimization, specialized representations, and techniques also used by other language families.

- Implementation remains worth studying: modern functionallanguage systems are shaped by compilers, garbage collectors, runtime support for concurrency, and hardware architectures, techniques relevant to performance and safety.

5

<!-- page 6 -->
# 2. Mathematical Foundations: Computability and Lambda Calculus

Before electronic computers. The striking historical fact is that the foundations of functional programming were developed as mathematical investigations into the nature of computation. Church introduced the lambda calculus in the 1930s, while Turing presented his machine model in 1936. Their ideas did not begin as convenient programming features; programming languages later gave them an executable form.

Georg Cantor (1845–1918) and Leopold Kronecker (1823– 1891) represented contrasting views on the foundations of mathematics. Cantor developed set theory, including the study of infinite sets, while Kronecker insisted that mathematical objects should be constructible through finite procedures. This debate contributed to a fundamental question: what does it mean for a mathematical object to be effectively constructible? During the early 20th century, attempts to formalize this idea, particularly through recursive functions and mathematical logic, eventually led to precise models of computation and the modern concept of computability.

Giuseppe Peano (1858-1932) showed that natural numbers can be constructed by a large number of applications of the successor function. Since 1923, Thoralf Skolem (1887-1963) has shown that almost all natural number theory can be developed constructively based on the extensive use of recursive definitions. Thus, the beginning of the 20th century brings with it considerable experience in the field of recursive definitions of natural number functions.

6

<!-- page 7 -->
To avoid using infinity, the buildable object was defined as an object that can be built in a finite number of steps, each step requiring a finite amount of effort. Attempts to formalize such a definition began in the 1930s, leading to the term calculability.

During the 1930s, several mathematicians independently developed formal models to answer a fundamental question: „ What does it mean for a function to be effectively computable? ” Although their approaches differed considerably, they eventually led to equivalent mathematical descriptions of computation.

The most important contributions were:

- General recursive functions , developed through the work of Jacques Herbrand, Kurt Gödel, and Stephen Kleene. This approach describes computation through functions defined using a finite collection of basic operations, recursion, and other precisely specified rules.

- Lambda calculus , introduced by Alonzo Church in the early 1930s and further developed with Stephen Kleene and others. It describes computation through function definition, application, and substitution, without relying on assignment statements or an explicit machine model.

- Turing machines , introduced by Alan Turing in 1936. These abstract machines perform elementary reading, writing, and movement operations on an unbounded tape, according to a finite set of rules. They provide a simple mathematical model of algorithmic computation.

- Post's formal systems , developed by Emil Post, who independently investigated computation through mechanical procedures and symbolic manipulation. His work provided another approach to formalizing effective computation.

7

<!-- page 8 -->
- Markov algorithms , developed later by Andrey Markov in the 1950s. They describe computation through the systematic application of string-rewriting rules and provide another equivalent model of computability.

One of the most remarkable discoveries was that these apparently different approaches describe the same class of computable functions . In particular, Church, Kleene, and Turing established the equivalence of lambda-definable functions, general recursive functions, and Turing-computable functions. This means that a function computable using one of these models can also be computed using the others.

These results provided strong support for the Church– Turing thesis , which states that every function that can be calculated by an effective algorithm can be computed by a Turing machine, or equivalently expressed using general recursive functions or lambda calculus. Unlike the mathematical equivalence of the formal models, the Church–Turing thesis is not a theorem: it connects the informal notion of an algorithm with mathematically defined models of computation.

Remarkably, these fundamental results were established before the development of modern electronic computers . They demonstrated that computation could be studied mathematically, independently of any particular machine or programming language.

For functional programming, the significance of these developments is particularly important. Lambda calculus and recursive-function theory showed that complex computations could be expressed through the definition and application of functions. These ideas later became the theoretical foundations of functional programming languages, most notably Lisp, developed by John McCarthy beginning in 1958.

8

<!-- page 9 -->
# 3. The Birth of Lisp: McCarthy, MIT, and Symbolic AI

Two pioneering languages. Fortran dates from the 1950s and Lisp from 1958; Lisp is therefore one of the oldest high-level programming-language families still in use. From the beginning, the two languages addressed different needs: numerical computation on the one hand, symbolic processing on the other. Lisp was not a late reaction to contemporary AI; it grew alongside the earliest research in artificial intelligence.

The 1956 Dartmouth Summer Research Project on Artificial Intelligence, organized by John McCarthy together with Marvin Minsky, Nathaniel Rochester, and Claude Shannon, helped establish AI as a research field. Lisp was developed subsequently, beginning in 1958, to support symbolic computation in AI research. Until 1958, McCarthy developed a first form of a language (Lisp - LISt Processing) for list processing, a form based on the idea of transcribing into that language the programming of algebraic expressions.

The imposition of Lisp as the basic language for programming artificial intelligence applications was made only after some concessions from the author, concessions intended to obtain more efficient implementations as well as more concise expressions. The last version developed by the author was Lisp 1.5 (1962). Subsequent implementations have remedied some of the shortcomings of that version, creating a number of new versions, most extensions. Lisp is now a language family rather than a single language: Common Lisp was standardized as ANSI X3.226 in 1994. Scheme has its own standardization tradition, and Clojure is a much later member of the Lisp family. Lisp is better understood as a family of related languages than as one unchanged language from 1958.

9

<!-- page 10 -->
The next major event in the history of functional programming was the publication in 1960 by John McCarthy of an article on the Lisp language. In 1958 McCarthy investigated the use of list operations in implementing a symbolic differentiation program. As differentiation is a recursive process, McCarthy was led to use recursive functions. Moreover, it needed the ability to transmit functions as arguments to other functions. Lambda calculus helped him in this, and so McCarthy came to use Church's notations for his programs.

This is the motivation for starting a project in 1958 at MIT that aimed to implement a language that incorporated such ideas. The result was Lisp 1, described by McCarthy in the article "Recursive Functions of Symbolic Expressions and Their Computation by Machine" (1960). This article (which shows how a very large number of important programs can be expressed as pure functions operating on list-type structures) is considered as a starting point for functional programming.

The eval story. One of Lisp’s most remarkable ideas is an evaluator for Lisp expressions described using Lisp-like functions themselves. McCarthy’s mathematical definition of eval helped establish the possibility of describing a language in terms of the language. The early practical interpreter emerged when this idea was implemented on a machine. A language that can process representations of its own programs opens the door to interpreters, program transformations, and macros.

10

<!-- page 11 -->
# 3.1. The symbolic-programming breakthrough

Here is a brief presentation of Lisp, made by the author himself:

- calculations with symbolic expressions instead of numbers;

- representation of symbolic expressions and other information through the list structure;

- composing functions as a tool for forming more complex functions;

- the use of recursion in the definition of functions;

- representation of Lisp programs as Lisp data;

- the Lisp eval function which serves both as a formal definition of language and as an interpreter;

- garbage collection as a means of dealing with the problem of allocation;

- Lisp instructions are interpreted as commands when a conversational environment is used.

Code as data. Lisp expressions are represented using the same basic list-and-symbol structures that Lisp programs manipulate. A program can therefore inspect or construct expressions as data. This property is often called homoiconicity. It provides a natural foundation for powerful macro systems, although a macro is not merely a text substitution.

The field of use of the language Lisp is that of symbolic calculation, ie of the processing performed on a series of symbols grouped in expressions. One of the causes of the force of Lisp language is the possibility of manipulating objects with a hierarchical structure.

11

<!-- page 12 -->
# 4. Fundamental Principles of Functional Languages

# 4.1. Pure functions

The first fundamental concept we learn when we want to understand functional programming is pure functions. But what does that really mean? What makes a function pure? How do we know if a function is pure or not? Here is a very strict definition of purity:

- It returns the same result if given the same arguments (it is also referred as deterministic)

- It does not cause any observable side effects

A practical test of purity. Imagine a function that returns the current time. Calling it twice with identical arguments can produce different results: it is not pure. A function that computes the number of seconds between two time values passed as arguments can be pure. Purity depends on the inputs and observable behavior, not on the name of the function.

Remarks:

- A function whose result depends on other values than the function parameters is not pure. Such a call may return different results for different calls with same parameters.

- A function reading external files is not a pure function, as the file’s contents may change.

- A function depending on a random number generator is not a pure function.

- Modifying a global object is discouraged, as it leads to impure functions.

12

<!-- page 13 -->
# 4.2. Immutability

Immutable values cannot be changed after creation; a transformation produces a new value while preserving the original. For example, adding an element to an immutable list [1, 2, 3] produces a new list [1, 2, 3, 4], while the original list remains unchanged. This makes programs easier to understand, test, and debug, since existing values remain predictable and can be safely shared between functions. Immutability also simplifies concurrent and parallel programming by avoiding conflicts caused by shared mutable state.

13

<!-- page 14 -->
# 4.3. Referential transparency

Let’s implement a _square_ function. This (pure) function will always have the same output, given the same input. Passing “2” as a parameter of the _square_ function will always return 4. So now we can replace the _(square 2)_ with _4_ . Basically, if a function consistently yields the same result for the same input, it is referentially transparent.

Why does this matter? If an expression can be replaced by its value without changing the program, reasoning and testing become simpler. A compiler may also have more freedom to optimize it. But real applications still require input, output, and changing state: functional programming tries to isolate such effects, not pretend they do not exist.

pure functions + immutable data => referential transparency

Referential transparency means that an expression can be replaced by its value without changing a program’s observable behavior. Pure functions operating on immutable inputs make this property easier to maintain.

14

<!-- page 15 -->
# 4.4. First-class functions

The idea of functions as first-class entities is that functions are also treated as values and used as data. Functions as first-class entities can:

- refer to it from constants and variables

- pass it as a parameter to other functions

- return it as result from other functions

The idea is to treat functions as values and pass functions like data. This way we can combine different functions to create new functions with new behavior.

15

<!-- page 16 -->
# 4.5. Higher-order functions

When we talk about higher-order functions, we mean a function that either:

- takes one or more functions as arguments, or

- returns a function as its result

For example:

- Filter – Given a collection, filter by an attribute according to a logical test

- Map – Transform a collection by applying a function to all its elements

- Reduce – Given a function and a collection, return a value created from the items

The idea in one line. For the list [1, 2, 3, 4, 5, 6], filter the even values to obtain [2, 4, 6], map the square function to obtain [4, 16, 36], and reduce by addition to obtain 56. Notice that the stages can be understood independently. In Lisp we will soon express similar computations with ordinary function calls.

16

<!-- page 17 -->
# 4.6. Languages, data structures, and abstraction

Any programming language can be divided into two components:

- The application domain-independent component , called the framework, which includes the basic syntactic (linguistic) mechanisms used in the construction of programs. For an imperative language the frame contains the control structures, the procedure call mechanism and the assignment operation. The framework of an application language includes the function definition and the function application mechanism.

- The application-specific component supplies useful domain data types and operations. For numerical computing, examples include numbers, arithmetic operations, and numerical relations. It is the domain-specific component—not the language framework—that provides these.

So the framework provides the form and the components the content on the basis of which the programs are built. The choice of framework determines the type of language (applied or imperative). The choice of components orients the language to a class of problems (for example, numerical or symbolic).

A data type is called abstract if it is specified in terms of a (abstract) set of values and operations and not in terms of a concrete implementation.

Sequences and lists occur in functional, imperative, and object-oriented languages. In Lisp, linked lists are constructed from cons cells, while other sequence types (such as vectors) also exist. CONS adds an element at the front of a list and is a particularly simple primitive for list construction and recursion.

Sequences are an abstract data type. They also are a generic type (sequences of integers, of strings, for example). One possible implementation uses singly linked lists. Recursion

17

<!-- page 18 -->
helps deciding on the primitive operations on the sequence, considering our need for as few operations as possible. The prefix (cons) operation was preferred to the postfix due to the way the singly linked linear lists are implemented.

Regarding the operations we need to define an abstract type of data, they must be:

- (i) constructors - operations that construct an abstract type of data in a finite number of steps based on the supply of components;

- (ii) selectors - element selection operations according to desired criteria;

- (iii) discriminators - operations capable of comparing different classes and instances of the abstract data type to verify that selectors can be applied to them.

Functional languages use a variety of syntaxes and evaluation strategies, and many are standardized or well established. Lambda calculus is an important theoretical influence, but implementations differ substantially. Lisp-family systems typically provide definitions and expression evaluation, as well as stateful operations.

- (1) Definitions of functions

- (2) Data definitions

- (3) Expression evaluations

Functional programs are closer to the formal specifications of program systems. Unlike conventional languages, functional languages treat the function as a fundamental object (the principle of regularity or uniformity) that can be transmitted as a parameter, returned as a result of a processing, constituted as part of a data structure, etc. This increases the abstracting power of a language.

18

<!-- page 19 -->
# 5. Functional, Imperative, and Object-Oriented Programming

A historical contrast. Fortran emerged in the 1950s to make numerical computation practical; Lisp emerged in 1958 to make symbolic computation practical. The important distinction is not simply old versus new languages, but numbers and array calculations versus expressions, lists, and symbolic structure. Both traditions still shape modern programming.

A surviving family of languages. Lisp is not a single frozen language: Common Lisp, Scheme, Racket and Clojure represent different choices about language size, teaching, metaprogramming and interoperability. For example, Clojure runs on the Java platform, while Common Lisp has actively developed native compilers.

Functional programming emphasizes function application, composition, and, frequently, immutable data. Lisp and Clojure are multi-paradigm languages with strong functional capabilities; Erlang and Haskell emphasize functional programming; Python supports functional idioms but is not primarily a functional language.

19

<!-- page 20 -->
Functional programming languages are categorized into two groups, i.e. −

   - Pure Functional Languages − Predominantly pure functional languages, such as Haskell, organize ordinary computations around pure functions while explicitly representing effects (for example, through IO). “Pure” does not mean that programs are unable to perform input/output.

   - Impure Functional Languages − These types of functional languages support the functional paradigms and imperative style programming. For example − LISP.

- The most prominent characteristics of functional programming are as follows −

   - Functional programming languages are designed on the concept of mathematical functions that use conditional expressions and recursion to perform computation.

   - Higher-order functions are central to functional programming. Lazy evaluation is an independent evaluation strategy: it is fundamental in Haskell but not required by functional programming or used by default in every functional language.

   - Functional use conditional programs expressions,

   - recursion, and often higher-order operations such as map and fold. Some functional languages also provide loops or imperative constructs; Common Lisp has IF, COND, LOOP, and other control forms.

- Functional programming offers the following advantages −

   - Bugs-Free Code − Pure functions and controlled side effects can make programs easier to test and reason about. Pure functions do not guarantee bug-free programs. They can still implement the wrong algorithm. Their advantage is more precise: fewer hidden dependencies and side effects

20

<!-- page 21 -->
make some errors easier to prevent, reproduce, and test.

- Efficient Parallel Programming − Immutable data and pure functions reduce the need for synchronization when computations run concurrently. Such code supports easier reusability and testability.

- Efficiency − Independent computations can be evaluated concurrently, potentially improving performance on suitable hardware.

- Supports Nested Functions − Functional programming supports nested functions.

- Lazy Evaluation − Some functional languages provide lazy evaluation or lazy sequences; others are strict by default. Laziness can enable demand-driven computation but may also complicate performance and memory use.

Persistent data structures can share unchanged portions instead of copying entire collections. Functional programming may introduce allocation overhead in some cases, but its memory use depends on data structures, compiler optimizations, and the application.

Functional Programming is used in situations where we have to perform lots of different operations on the same set of data.

- Historically, Lisp was particularly influential in symbolic AI, including theorem proving, expert systems, symbolic algebra, and natural-language research. Lisp still remains useful in various specialized settings.

- Embedded Lisp interpreters add programmability to some systems like Emacs.

21

<!-- page 22 -->
# 5.1. Functional versus programming object-oriented programming

The following highlights the major differences between functional programming and object-oriented programming. Functional and object-oriented programming can coexist in the same language.

# Primary abstraction

FP: Functions and function composition.

OOP: Objects, classes, and interactions.

Data and behavior

FP: Operations are separate from data. OOP: Objects encapsulate state and behavior.

State and mutability

FP: Prefers immutable values.

OOP: Commonly modifies state through methods.

# Programming model

FP: Describes computations using expressions.

OOP: Models entities and their responsibilities.

# Side effects

FP: Pure functions have no side effects.

OOP: Methods may change state or the environment. Composition and reuse

FP: Combines functions and higher-order functions. OOP: Uses delegation, interfaces, polymorphism.

22

<!-- page 23 -->
# Iteration

FP: Recursion, map, filter, and fold.

OOP: Loops, iterators, and method calls.

Evaluation order

FP: Order is flexible for independent pure calls.

OOP: State changes often impose an order.

Parallel programming

FP: Immutable data limits interference.

OOP: Shared mutable state needs synchronization.

Main focus

FP: Abstraction over behavior.

OOP: Abstraction over data and state.

These are characteristic differences between paradigms; remember that individual languages can support both styles.

23

<!-- page 24 -->
# 6. The Evolution of Lisp

# 6.1. Early programming languages and semantic models

Towards the end of the 1960s Peter Landin tried to define the non-functional language Algol 60 through lambda calculus. This approach was continued by Strachey and Scott and led to a method of defining the semantics of programming languages known as denotational semantics. In essence, denotational semantics defines the meaning of a program in terms of an equivalent functional program.

# 6.2. Lisp dialects and computer algebra

Historically influential Lisp dialects and environments include MacLisp, Interlisp, and Franz Lisp. Later important branches include Common Lisp, Scheme, and Clojure.

- Interlisp originated in the BBN Lisp tradition and was later developed at Xerox PARC, notably as Interlisp-D on Xerox workstations.

- MacLisp developed at MIT during the 1960s and became influential on the PDP-6/PDP-10 family; it was not first created in 1970.

- Franz Lisp originated at the University of California, Berkeley, around the late 1970s, and brought a MacLisprelated dialect to Unix systems.

- MACSYMA was an influential early computer algebra system developed at MIT Project MAC beginning in the late 1960s. It was implemented in MacLisp and helped drive improvements in that Lisp dialect.

24

<!-- page 25 -->
Why garbage collection mattered. Symbolic computation constantly creates short-lived lists and trees. Requiring programmers to reclaim every abandoned structure manually would make these programs much harder to write. Lisp helped establish automatic collection as a garbage practical programming-language technique. Today that idea is familiar from languages such as Java, Python, and JavaScript.

# 6.3. Backus, Lisp machines, Scheme, Common Lisp, and Clojure

John Backus’s 1977 Turing Award lecture, published in Communications of the ACM in 1978, was titled “Can Programming Be Liberated from the von Neumann Style? A Functional Style and Its Algebra of Programs.” He severely criticized the assignment-centered style of conventional languages and proposed his functional programming system. His critique generated extensive research on functional programming.

An unexpected critic. John Backus, the principal designer of Fortran, used his 1977 Turing Award lecture (published in 1978) to criticize the conventional von Neumann programming style. His question, “Can Programming Be Liberated from the von Neumann Style?”, was especially striking because Fortran had helped make that style so influential. Backus proposed reasoning in terms of function composition rather than an endless succession of assignments.

The 1980s: Lisp machines and the AI boom. During the 1980s, specialized Lisp workstations became closely associated with artificial-intelligence research. Companies such as

25

<!-- page 26 -->
Symbolics built interactive environments in which editing, compiling, debugging and inspecting running programs formed a continuous workflow. The commercial Lisp-machine market later contracted, but its development-environment ideas survived.

Two important branches: Scheme and Common Lisp. Scheme emerged in the 1970s through the work of Guy L. Steele Jr. and Gerald Jay Sussman, emphasizing a small language, lexical scope and the central role of procedures. Common Lisp, developed through cooperation among several Lisp communities in the 1980s, aimed instead at consolidating a large, practical language. Its ANSI standard appeared in 1994 (ANSI X3.226). These are different design philosophies within the Lisp family.

The 2000s: Clojure. Rich Hickey introduced Clojure in 2007. It brought Lisp notation and interactive development to the Java platform, emphasizing persistent immutable data structures and practical concurrency. The point is not that Lisp returned unchanged, but that its basic ideas were adapted to modern software engineering.

Lisp in 2026: still maintained. The Lisp family is not merely a historical curiosity. Steel Bank Common Lisp (SBCL) released version 2.6.10 on 29 October 2026. The current stable Clojure release is 1.12.6 (2 September 2026), with development of 1.13 ongoing. These version numbers are a snapshot as of November 2026, not timeless language characteristics.

26

<!-- page 27 -->
# 7. Lisp’s Legacy and Modern Functional Programming

Areas of Artificial Intelligence the Lisp language has found a wide field of applications are the demonstration of theorems, learning, the study of natural language, speech comprehension, image interpretation, expert systems, robot planning, etc.

From symbolic AI to modern AI. Classical AI often represented knowledge explicitly as symbols, rules, and logical relations. Lisp was a natural environment for theorem proving, planning, and expert systems. Modern machine learning relies heavily on numerical optimization and statistical models, but symbolic techniques remain useful for theorem proving, constraint solving, program analysis and knowledge representation. Contemporary systems can combine both approaches. Lisp’s historic role was to make symbolic representations and transformations unusually convenient, not to guarantee that all AI would be written in Lisp.

A closing question. If Lisp is almost seventy years old, why do so many ideas associated with it—functions as values, automatic memory management, interactive evaluation, and code transformation—still look modern?

Why the history matters. Lisp connects three eras of computing: mathematical theories of computability, symbolic artificial intelligence, and modern language features such as higher-order functions, automatic memory management, interactive development and code-generating macros. Studying Lisp is therefore also a way of studying the evolution of programming-language design.

27
