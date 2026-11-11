package org.example;

import org.junit.jupiter.api.*;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.CsvSource;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class CalculatorTest {

//    private final Calculator c = new Calculator();

//    CalculatorTest(Calculator c) {
//        this.c = c;
//    }

    @Test
    void testDivide() {
//        Calculator c = new Calculator();
//        Nu mai avem nevoie de instanta, putem apela direct clasa
        assertEquals(2, Calculator.divide(6, 3));
    }

    @Test
    void testDivideZero() {
        assertThrows(ArithmeticException.class, () -> Calculator.divide(3, 0));
        // ()-> = lambda
    }

    @BeforeAll
    static void setUp() {
        IO.println("Before All");
    }

    @BeforeEach
    void eachSetUp() {
        IO.println("Before Each");
    }

    @AfterEach
    void eachCleanUp() {
        IO.println("After Each");
    }

    @AfterAll
    static void cleanUp() {
        IO.println("After all");
    }

    @BeforeEach
    void eachSetUp2() {
        IO.println("Before Each2");
    }

    @AfterEach
    void eachCleanUp2() {
        IO.println("After Each2");
    }

    @ParameterizedTest
//    @CsvSource()
//    @CsvSource({"1,2,3",
//                "3,2,1",
//                "0,0,0"})
//    @CsvSource("""
//            1,2,3
//            3,2,1
//            0,0,0
//            """)
    public static Stream<Arguments> parameters() {
        return Stream.of(
                Arguments.of(1, 2, 3),
                Arguments.of(0, 0, 0),
                Arguments.of(3, 2, 1)

        );
    }

    @MethodSource("parameters")
    void addTest(int a, int b, int expected) {
        assertEquals(expected, Calculator.add(a, b));

    }
}
