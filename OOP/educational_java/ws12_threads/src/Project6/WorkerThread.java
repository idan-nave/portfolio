public class WorkerThread extends Thread {
    public WorkerThread(String name) {
        super(name); // Set thread name
    }

    @Override
    public void run() {
        System.out.println("Thread started: " + this.getName() + ", Priority: " + this.getPriority());
        try {
            // Simulating work
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            System.out.println("Thread " + this.getName() + " was interrupted.");
        }
        System.out.println("Thread finishing: " + this.getName());
    }
}
