package repository;
import model.Vehicle;

import java.util.Objects;

public class ArrayRepository implements Repository{
    private final Vehicle[] vehicles;
    private int size = 0;

    public ArrayRepository(int cap){
        if (cap<= 0)
            throw new RuntimeException("Capacity must be an integer greater than 0");
        vehicles = new Vehicle[cap];
    }

    @Override
    public void add(Vehicle vehicle) {
        if(size >= vehicles.length)
            throw new RuntimeException("The parking lot is full");
        vehicles[size] = vehicle;
        size++;
    }

    @Override
    public void remove(Vehicle vehicle){
        for(int i = 0; i < size; i++){
            if (Objects.equals(vehicles[i].getName(), vehicle.getName())
                    && Objects.equals(vehicles[i].getColor(), vehicle.getColor())
                    && Objects.equals(vehicles[i].getClass(), vehicle.getClass())){
                for(int j = i; j < size-1; j++)
                    vehicles[j] = vehicles[j+1];
                vehicles[size-1] = null;
                size--;
                return;
            }
        }
        throw new RuntimeException("Vehicle: " + vehicle + " is not in the parking lot");
    }

    @Override
    public Vehicle[] getAll(){
        Vehicle[] result = new Vehicle[size];
        for(int i = 0; i < size; i++)
            result[i] = vehicles[i];
        return result;
    }

}
