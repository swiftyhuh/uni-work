import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.platform.commons.util.StringUtils;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class TestSeminar {

    List<String> words = List.of("hi", "hello", "bye", "goodbye", "java", "stream",
            "lambda", "map", "filter", "reduce", "eye", "queue", "collect", "Hello");

    record Student(String name, int group, double grade) {
    }

    List<Student> students = List.of(
            new Student("Ana", 921, 9.5), new Student("Bogdan", 922, 4.0),
            new Student("Carmen", 921, 7.0), new Student("Dan", 923, 8.5),
            new Student("Elena", 922, 10.0), new Student("Florin", 923, 5.0),
            new Student("Gabriela", 921, 3.5), new Student("Horia", 922, 6.5));
    String text = "The stream API is lazy. A stream is not a collection: "
            + "the stream is consumed once, and the collection is not.";

    @Test
    void test1() {
//        for (var word : words) {
//            IO.println(" " + word);
//        }

//        words.forEach(new MyConsumer());

//        words.forEach((String word) -> {
//            IO.println(" " + word);
//        });
//        words.forEach(word -> IO.println(" " + word));
//        words.forEach(word -> IO.println(word)); lambda can be replaced with method reference
        words.forEach(IO::println); // this method reference

    }

    static class MyConsumer implements Consumer<String> {

        @Override
        public void accept(String word) {
            IO.println(" " + word);
        }
    }

    interface Function1<T> {
        T app(T t);
    }

    List<String> excitingWords =
            transformedList(words, s -> s + "!");
    List<String> eyeWords =
            transformedList(words, s -> s.replace("i", "eye"));
    List<String> upperCaseWords =
            transformedList(words, String::toUpperCase); // String::toUpperCase is not a static method, is a string one

//    List<String> transformedList(List<String> list, Function<String, String> function) {
//        List<String> newList = new ArrayList<>();
//
//        for (var s : list) {
//            newList.add(function.apply(s));
//        }
//
//        return newList;
//    }

    List<String> transformedList(List<String> list, Function<String, String> function) {
        return list.stream()
//        return list.parallelStream() to be more efficient
                .map(function)
//                .collect(Collectors.toList());stream
                .toList();
    } // same complexity as a simple for loop and have a worse efficiency but is smaller

    List<String> shortWords = allMatches(words, s -> s.length() < 4);
    List<String> wordsWithB = allMatches(words, s -> s.contains("b"));
    List<String> evenLengthWords = allMatches(words, s -> s.length() % 2 == 0);

    List<String> allMatches(List<String> list, Predicate<String> condition) {
        return list.stream().filter(condition).toList();
    }

    @Test
    void test2() {
        String result = findFirstShortString("E");
        Assertions.assertEquals("BYE", result);
        Assertions.assertNull(findFirstShortString("Q"));
    }

    private String findFirstShortString(String toContain) {
        return words.stream()
                .map(String::toUpperCase)
                .filter(s -> s.length() < 4)
                .filter(s -> s.contains(toContain))
                .findFirst()
//                .ifPresent(IO::println);
                .orElse(null);
    }

    @Test
    void test3() {
        var result = words.stream()
                .reduce((s1, s2) -> s1.toUpperCase() + s2.toUpperCase());
        IO.println(result);
        var result2 = words.stream().reduce("", (s1, s2) -> s1.toUpperCase() + s2.toUpperCase());
        Assertions.assertEquals(result.orElse(null), result2);
    }

    @Test
    void test4() {
        var result = words.stream().map(String::toUpperCase).reduce(String::concat);
        var result2 = words.stream().reduce("", (s1, s2) -> s1 + s2.toUpperCase());
        Assertions.assertEquals(result.orElse(null), result2);

        var result3 = words.stream()
                .map(String::toUpperCase)
                .reduce("", String::concat);
        Assertions.assertEquals(result2, result3);

        var result4 = words.stream().reduce((s1, s2) -> s1 + "," + s2);
        IO.println(result4);

        var result5 = words.stream()
                .collect(Collectors.joining(","));
    }

    // p.16

    @Test
    void p16() {
        List<Integer> fibonacci = Stream.iterate(
                        new int[]{0, 1}, p -> new int[]{p[1], p[0] + p[1]}
                )
                .limit(15)
                .map(p -> p[0])
                .toList();

        int p16 = Stream.iterate(
                        new int[]{0, 1}, p -> new int[]{p[1], p[0] + p[1]}
                )
                .map(p -> p[0])
                .filter(x -> x > 1000)
                .findFirst()
                .orElse(0);

        System.out.println(fibonacci);
        System.out.println(p16);
    }


}


