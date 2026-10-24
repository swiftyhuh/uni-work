package repository;
import model.Vehicle;

public interface Repository {
    void add(Vehicle vehicle);
    void remove(Vehicle vehicle);
    Vehicle[] getAll();
}
