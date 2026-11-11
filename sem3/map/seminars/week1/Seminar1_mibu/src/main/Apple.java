package main;

public class Apple {
    private final int weight;

    public Apple(int weight) {
        this.weight = weight;
    }

    public int getWeight() {
        return weight;
    }

    @Override
    public String toString() {
        return "Apple{" +
                "weight=" + weight +
                '}';
    }
}
