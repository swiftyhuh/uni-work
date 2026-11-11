package ro.ubb.value;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class IntValueTest {

    @Test
    void testEqual() {
        var int1 = new IntValue(1);
        var int2 = new IntValue(1);
        assertEquals(int1, int2);
    }


}