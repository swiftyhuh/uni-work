package main;

public class Apple extends BasicItem implements Item{
    @Override
    public int getWeight(){
        return 5;
    }

    @Override
    public String toString() {
        return "Apple{weight=" + getWeight() + '}';
    }

    public Apple(int weight) {
        super(weight);
    }
}
