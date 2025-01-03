// $ javac -d bin src/Project6/*.java
// $ java -cp bin src/Project6/ThreadMethodsDemo.java

public class ThreadMethodsDemo {
    public static void main(String[] args) {
        // Create threads with names
        WorkerThread worker1 = new WorkerThread("Worker-1");
        WorkerThread worker2 = new WorkerThread("Worker-2");

        // Set priorities
        worker1.setPriority(Thread.MIN_PRIORITY); // 1
        worker2.setPriority(Thread.MAX_PRIORITY); // 10

        // Start threads
        System.out.println("Starting threads...");
        worker1.start();
        worker2.start();

        // Demonstrate currentThread()
        Thread current = Thread.currentThread();
        System.out.println("Current thread is: " + current.getName() + " (priority " + current.getPriority() + ")");
  
        // Check status of threads
        System.out.println("Is Worker-1 alive? " + worker1.isAlive());
        System.out.println("Is Worker-2 alive? " + worker2.isAlive());
        
        // Wait (join) for threads to finish
        try {
            System.out.println("Main thread waiting for Worker-1 and Worker-2 to finish...");
            worker1.join();
            worker2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Check status of threads
        System.out.println("Is Worker-1 alive? " + worker1.isAlive());
        System.out.println("Is Worker-2 alive? " + worker2.isAlive());

        // Sleep the main thread for demonstration
        System.out.println("Main thread sleeping for 500ms...");
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Main thread finished.");
    }
}
