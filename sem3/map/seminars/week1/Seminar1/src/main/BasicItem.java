package main;

public abstract class BasicItem implements Item {
    private  final int weight;

    protected BasicItem(int weight) {
        this.weight = weight;
    }

    @Override
    public int getWeight() {
        return weight;
    }
}
