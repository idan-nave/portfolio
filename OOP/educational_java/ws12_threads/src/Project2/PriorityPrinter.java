// - **Project 2**: Threads printing multiples of their priority (from 1 to 50).
// $ javac -d bin src/Project2/*.java
// $ java -cp bin src/Project2/*.java

public class PriorityPrinter implements Runnable {

    @Override
    public void run() {
        for (int i = 1; i <= 50; i++) {
            if (i % Thread.currentThread().getPriority() == 0) {
                System.out.println(Thread.currentThread().getName() + ": " + i);
            }
        }
    }

    public static void main(String[] args) {
        for (int i = 1; i <= 5; i++) {
            Thread thread = new Thread(new PriorityPrinter());
            thread.setName("PriorityThread-" + i);
            thread.setPriority(i);  // Set priority between 1 (min) to 5 (max)
            thread.start();
        }
    }
}
