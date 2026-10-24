package model;

public class Motorcycle implements Vehicle {
    private final String name;
    private final String color;

    public Motorcycle(String name, String color) {
        this.name = name;
        this.color = color;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getColor() {
        return color;
    }

    @Override
    public String toString() {
        return "Motorcycle{" +
                "name='" + name + '\'' +
                ", color='" + color + '\'' +
                '}';
    }
}
