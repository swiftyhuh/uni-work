package view;

import controller.Controller;
import model.Bicycle;
import model.Car;
import model.Motorcycle;
import model.Vehicle;
import repository.ArrayRepository;

public class View {
    private final Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    private void printMenu(){
        IO.println("");
        IO.println("1. Add a vehicle");
        IO.println("2. Remove a vehicle");
        IO.println("3. Show all vehicles");
        IO.println("4. Show red vehicles");
        IO.println("0. Exit");
    }

    private void entries(){
        var hellcat = new Car("Hellcat","Red");
        var superb = new Car("SKoda Superb","Black");
        var trackhawk = new Car("TrackHawk","Red");
        var ducati = new Motorcycle("Ducati","Green");
        var ktm = new Motorcycle("KTM","Red");
        var bmx = new Bicycle("BMX","Red");

        controller.add(hellcat);
        controller.add(superb);
        controller.add(trackhawk);
        controller.add(ducati);
        controller.add(ktm);
        controller.add(bmx);
    }

    private Vehicle addRemoveMenu(){
        IO.println("");
        IO.println("1. Car");
        IO.println("2. Motorcycle");
        IO.println("3. Bicycle");
        IO.println("4. Back to the main menu");
        int choice = Integer.parseInt(IO.readln("Enter your choice: "));
        if (choice == 4)
            return null;
        else if (choice < 1 || choice > 3) {
            IO.println("Invalid option!");
            return null;
        }
        String name = IO.readln("Name: ");
        String color = IO.readln("Color: ");
        Vehicle vehicle;
        if (choice == 1)
            return vehicle = new Car(name, color);
        else if (choice == 2)
            return vehicle = new Motorcycle(name, color);
        else
            return vehicle = new Bicycle(name, color);
    }

    private void addVehicle(){
        Vehicle vehicle = addRemoveMenu();
        if (vehicle == null)
            return;
        controller.add(vehicle);
        IO.println("Vehicle added successfully");

    }

    private void removeVehicle(){
        Vehicle vehicle = addRemoveMenu();
        if (vehicle == null)
            return;
        controller.remove(vehicle);
        IO.println("Vehicle removed successfully");
    }

//    private void removeVehicle(){
//        IO.println("");
//        IO.println("1. Car");
//        IO.println("2. Motorcycle");
//        IO.println("3. Bicycle");
//        IO.println("4. Back to the main menu");
//        int choice = Integer.parseInt(IO.readln("Enter your choice: "));
//        if (choice == 4)
//            return;
//        else if (choice < 1 || choice > 3) {
//            IO.println("Invalid option!");
//            return;
//        }
//        String name = IO.readln("Name: ");
//        String color = IO.readln("Color: ");
//        Vehicle vehicle;
//        if (choice == 1)
//            vehicle = new Car(name, color);
//        else if (choice == 2)
//            vehicle = new Motorcycle(name, color);
//        else
//            vehicle = new Bicycle(name, color);
//        controller.remove(vehicle);
//        IO.println("Vehicle removed successfully");
//
//    }

    private void showAll(){
        Vehicle[] all = controller.getAll();
        if (all.length == 0)
            IO.println("Parking lot is empty");
        for (Vehicle vehicle : all)
            IO.println(vehicle);
    }

    private void showRed(){
        Vehicle[] red = controller.getAllRed();
        if (red.length == 0)
            IO.println("No red vehicles");
        for (Vehicle vehicle : red)
            IO.println(vehicle);
    }

    public void run(){
        entries();
        while(true){
            printMenu();
            try{
                int choice = Integer.parseInt(IO.readln("Enter your choice: "));
                if(choice == 1)
                    addVehicle();
                else if (choice == 2)
                    removeVehicle();
                else if (choice == 3)
                    showAll();
                else if (choice == 4)
                    showRed();
                else if (choice == 0)
                    return;
                else
                    IO.println("Invalid Option!");
            } catch (RuntimeException e){
                IO.println("Error: " + e.getMessage());
            }
        }
    }

    static void main(){
        var repo = new ArrayRepository(10);
        var controller = new Controller(repo);
        var view = new View(controller);
        view.run();
    }
}
