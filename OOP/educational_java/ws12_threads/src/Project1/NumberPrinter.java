// - **Project 1**: Multiple threads printing numbers from 1 to 10 concurrently.
// $ javac -d bin src/Project1/*.java
// $ java -cp bin src/Project1/*.java

public class NumberPrinter extends Thread {
    @Override
    public void run() {
        for (int i = 1; i <= 10; i++) {
            System.out.println(Thread.currentThread().getName() + ": " + i);
            try {
                Thread.sleep(500); // Sleep for 500ms between prints
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        for (int i = 1; i <= 5; i++) {
            NumberPrinter thread = new NumberPrinter();
            thread.setName("Thread-" + i);
            thread.start();
        }
    }
}
