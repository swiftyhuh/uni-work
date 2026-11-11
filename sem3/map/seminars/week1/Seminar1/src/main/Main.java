//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
import main.*;

void main() {
    //TIP Press <shortcut actionId="ShowIntentionActions"/> with your caret at the highlighted text
    // to see how IntelliJ IDEA suggests fixing it.
    Object object = new Object();
    // we will be using toSTring, equals, hashCode
    IO.println(String.format("Hello and welcome!"));

    //byte, float, double , char, int
    //we can use var( just like auto in cpp, will figure out from the context what type of variable it has)
    main.BasicItem apple = new Apple(5);
    var book = new Book(7);
    var cake = new Cake(8);

    Item item = cake; //polimorphism
    printItem(cake);

    var items = new Item[] {apple, book, cake};
    var box = new Box(items);

    IO.println(box.getWeight());
    IO.println(box);
}

void printItem(Item item){

    if (item instanceof Cake) {
        IO.println("It is a lie!!");
        return;
    } // how we check the object type of an item

    IO.println(item);
}