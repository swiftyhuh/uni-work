package controller;

import model.Vehicle;
import repository.Repository;


public class Controller {
    private final Repository repo;

    public Controller(Repository repo) {
        this.repo = repo;
    }

    public void add(Vehicle vehicle) {
        repo.add(vehicle);
    }

    public void remove(Vehicle vehicle) {
        repo.remove(vehicle);
    }

    public Vehicle[] getAll() {
        return repo.getAll();
    }

//    public int countRed(){
//        int count = 0;
//        Vehicle[] all = repo.getAll();
//        for (Vehicle vehicle : all)
//            if (vehicle.getColor().equalsIgnoreCase("red"))
//                count++;
//
//        return count;
//    }
//
//    public Vehicle[] getAllRed() {
//        int count = countRed();
//        int index = 0;
//        Vehicle[] all = repo.getAll();
//        Vehicle[] red = new Vehicle[count];
//
//        for (Vehicle vehicle : all)
//            if (vehicle.getColor().equalsIgnoreCase("red")){
//                red[index] = vehicle;
//                index++;
//            }
//
//        return red;
//    }

    private boolean isRed(Vehicle vehicle) {
        return vehicle.getColor().equalsIgnoreCase("red");
    }

    private int countRed() {
        int count = 0;
        for (Vehicle vehicle : repo.getAll())
            if (isRed(vehicle))
                count++;
        return count;
    }

    public Vehicle[] getAllRed() {
        Vehicle[] red = new Vehicle[countRed()];
        int index = 0;
        for (Vehicle vehicle : repo.getAll())
            if (isRed(vehicle)) {
                red[index] = vehicle;
                index++;
            }
        return red;
    }

}
