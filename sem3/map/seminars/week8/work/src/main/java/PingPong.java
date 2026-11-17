public class PingPong {
    private boolean pingTurn = true;

    synchronized void play(String word, boolean isPing) {
        for (int i = 0; i < 3; i++) {
            while (isPing != pingTurn) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }
            System.out.println(word);

            pingTurn = !pingTurn;

            notifyAll();
        }
    }
}


void main() throws InterruptedException {
    PingPong game = new PingPong();
    Thread ping = new Thread(() -> game.play("ping", true));
    Thread pong = new Thread(() -> game.play("pong", false));
    ping.start();
    pong.start();
    ping.join();
    pong.join();
}