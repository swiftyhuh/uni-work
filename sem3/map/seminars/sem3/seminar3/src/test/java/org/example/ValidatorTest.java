package org.example;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class ValidatorTest {

    @Test
    public void testValidatorSpace(){
        assertThrows(ValidationException.class, () -> Validator.validate("Alex 123"));
    }

    @Test
    public void testValidatorUnderscore(){
        assertThrows(ValidationException.class, ()-> Validator.validate("Alex_1234"));
    }

    @Test
    public void testValidatorOkay(){
//      assertThrows(true, ()-> Validator.validate("Alex1234"));
//        assertTrue(Validator.validate("Alex1234"));
        assertDoesNotThrow(()->Validator.validate("Alex1234"));
    }


}