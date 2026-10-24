<!-- page 1 -->
# Seminar 3

week3( 12- 16 October 2026 )

<!-- page 2 -->
# Unit testing in Java with JUnit

Seminar material has been prepared by Tudor Jinga and Diana Timiș

<!-- page 3 -->
## Why test?

Consider the following method:

public static int divide(int a, int b) { return a / b; }

What cases should we test?

<!-- page 4 -->
## Test Folder Structure

Tests are written in test classes which are classes belonging to the src/test/java folder. Usually, we want the package structure of the test classes to mirror the package structure of the main classes. In the example on the right, the Calculator class is defined in package _ro.ubb.calculator_ under src/main/java. Its test class is also defined in package _ro.ubb.calculator_ , but under src/test/java.

<!-- page 5 -->
## Creating a Test Class

IntelliJ helps with this: To create a test class for any class, just press CTRL + SHIFT + T while you are hovering over the class body or its name :

If the test already exists, pressing the same key combination will open that test. Otherwise, IntelliJ opens a window for creating it. By default, the test’s package is the same as the one of the class under test.

<!-- page 6 -->
## Basic JUnit Features

- The @Test annotation is the default choice for marking a method in a test class as a test . Note that _not all_ methods have to be tests (some can be helper methods shared by multiple tests).

- Write assertions using any of the many static methods found in the Assertions class from Junit Jupiter (imported by IntelliJ by default).

<!-- page 7 -->
## EXERCISE I

- Write tests for all basic arithmetic operations of a Calculator class (+, -, *, /).

- • Use different kinds of assertions: assertEquals(...), assertNotEquals(...), assertTrue(...), assertFalse(...), assertThrows(...)

<!-- page 8 -->
## EXERCISE II

- Declare a Validator class with a single method that validates a username received as parameter. What constraints should the validator enforce? Write test methods to cover all of them

- Then implement the actual validation method.

- This is an example of TDD (test driven development) : write the tests first, defining what the code should do, then implement it accordingly.

<!-- page 9 -->
## Lifecycle methods

These are methods that are called by the Junit platform at various points in a test class execution lifecycle.

@BeforeAll – is placed on a static method of the class. The test framework calls this method exactly once before executing the tests. Used for setting-up any shared test state. @BeforeEach – placed on a non-static method. The method is called once before each test method of the class. Used to set-up state before each test.

@AfterEach and @AfterAll are analogous. They are used for any clean-ups.

<!-- page 10 -->
## The Whole Lifecycle

- Each test class goes through the following lifecycle: 1. Static fields are initialized

2. @BeforeAll methods are executed

3. For each test method (taken in an undefined order): a. A new instance of the test class is constructed. b. @BeforeEach annotated methods are executed c. The test method is executed.

d. @AfterEach annotated methods are executed.

4. @AfterAll methods are executed.

<!-- page 11 -->
## EXERCISE III

Try using the lifecycle annotations to reduce code duplication in your test classes. Remember you can also declare fields in test classes, just like in a regular class. They are effectively reset before each test method (as explained in the previous slide).

<!-- page 12 -->
## Parameterized Tests

Do you have multiple test cases with the same code, but different data? Use parameterized tests to avoid repetition.

Each @ParameterizedTest annotated method must have a source annotation (there are multiple options) with the test data. The data is passed to the method through parameters. As an exercise, try upgrading your existing tests to parameterized tests.

<!-- page 13 -->
## Avoid Writing Bad Tests

Each good test method:

- has a descriptive name

- only tests one concept (Single Responsibility Principle)

- is independent from the others (if it fails, the others are not be affected)

- is deterministic: the execution is not random in any way

- does not use mutable shared state: it may violate independence

<!-- page 14 -->
## Assignment 2 Discussion

• Discuss the assignment 2 (see Lab3)
