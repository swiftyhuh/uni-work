package model;

public class Bicycle implements Vehicle {
    private final String name;
    private final String color;

    public Bicycle(String name, String color) {
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
        return "Bicycle{" +
                "name='" + name + '\'' +
                ", color='" + color + '\'' +
                '}';
    }
}
