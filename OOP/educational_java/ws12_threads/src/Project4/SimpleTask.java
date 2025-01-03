// - **Project 4**: Tasks executed by threads in a thread pool, with a shutdown after completion.
// $ javac -d bin src/Project4/*.java
// $ java -cp bin src/Project4/*.java

import java.util.concurrent.TimeUnit;

public class SimpleTask implements Runnable {
    @Override
    public void run() {
        System.out.println(Thread.currentThread().getName() + " is executing a task");
    }

    public static void main(String[] args) throws InterruptedException {
        java.util.concurrent.ExecutorService executor = java.util.concurrent.Executors.newFixedThreadPool(4);

        // Submit tasks to the thread pool
        for (int i = 0; i < 10; i++) {
            executor.submit(new SimpleTask());
        }

        // Shut down the executor service
        executor.shutdown();
        executor.awaitTermination(1, TimeUnit.MINUTES);
        System.out.println("All tasks completed.");

    }
}

// executor.shutdown(): Starts an orderly shutdown, stopping the submission of new tasks but allowing running tasks to finish.
// executor.awaitTermination(long timeout, TimeUnit unit): Blocks the calling thread (typically the main thread) until all tasks are completed or the specified timeout is reached. It ensures that the program waits for task completion before proceeding.