// - **Project 3**: A synchronized counter value after multiple threads increment it.
// $ javac -d bin src/Project3/*.java
// $ java -cp bin src/Project3/IncrementTask.java

public class IncrementTask implements Runnable {
    private Counter counter;

    public IncrementTask(Counter counter) {
        this.counter = counter;
    }

    @Override
    public void run() {
        for (int i = 0; i < 1000; i++) {
            counter.increment();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Counter counter = new Counter();

        // Create and start multiple threads
        Thread[] threads = new Thread[10];
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new Thread(new IncrementTask(counter));
            threads[i].start();
        }

        // Wait for threads to finish
        for (Thread thread : threads) {
            thread.join();
        }

        System.out.println("Final counter value: " + counter.getCount());
        // we have omly one instance of Counter. so- multiple threads are working on the same instance of Counter, while only one thread can execute the increment() method at any given time.
    }
}
