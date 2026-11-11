import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class SimpleTest {
//    @Test
//    void test() throws Exception { /* signature method */
//        throw new Exception(); cand asteptam un exception (numar, string etc)
//    }
//    @Test
//    void test() {
//        throw new RuntimeException();
//    }
    @Test
    void test() {
        Assertions.fail("fail");
    }
}