package main;

import java.util.Arrays;

public class Box implements Item{
    private final Item[] items;

    public Box(Item[] items) {
        this.items = items;
    }
    @Override
    public int getWeight() {
        int sum = 0;
        for (var item : items){
            sum+=item.getWeight();
        }
        return sum;
    }

    @Override
    public String toString() {
        return "Box{" +
                "items=" + Arrays.toString(items) +
                '}';
    }
}
