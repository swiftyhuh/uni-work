package org.example;

public class Validator {
    public static void validate(String username){
        if(username.contains(" ")){
            throw new ValidationException("Contains space");
        }
        if(username.contains("_")){
            throw new ValidationException("Contains underscore!");
        }

    }
}
