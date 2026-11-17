import java.util.concurrent.atomic.AtomicInteger;

public class SharedCounter {
    private final Object lock = new Object();
//    private int count = 0;
    private final AtomicInteger count = new AtomicInteger(0);

    public void increment() {
        synchronized (lock) {
            //count++;
        }
    }

    public int get() {
        return count.get();
    }

    public static void main(String[] args) throws InterruptedException {
        SharedCounter c = new SharedCounter();
        Runnable task = () -> {
            for (int i = 0; i < 100_000; i++)
                c.increment();
        };
        Thread t1 = new Thread(task);
        Thread t2 = new Thread(task);
        t1.start();
        t2.start();
        // t2.run();
        // t1.run(); starts the task, and wait till it finished, returns 200.000 everytime
        t1.join();
        t2.join();
        System.out.println(c.get());
    }
}