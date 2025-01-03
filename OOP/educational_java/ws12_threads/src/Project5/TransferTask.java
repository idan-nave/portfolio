// - **Project 5**: Multiple bank account transfers occurring concurrently with proper synchronization using `ReentrantLock`.
// $ javac -d bin src/Project5/*.java
// $ java -cp bin src/Project5/TransferTask.java

public class TransferTask implements Runnable {
    private Account source;
    private Account destination;
    private double amount;

    public TransferTask(Account source, Account destination, double amount) {
        this.source = source;
        this.destination = destination;
        this.amount = amount;
    }

    @Override
    public void run() {
        source.transfer(destination, amount);
    }

    public static void main(String[] args) throws InterruptedException {
        // Create three Account objects with initial balances of 1000 each
        Account account1 = new Account("A1", 1000); // Account A1 with 1000 balance
        Account account2 = new Account("A2", 1000); // Account A2 with 1000 balance
        Account account3 = new Account("A3", 1000); // Account A3 with 1000 balance

        // Create an array to hold 10 threads
        Thread[] threads = new Thread[10];

        // Loop to create and start 10 transfer threads
        for (int i = 0; i < threads.length; i++) {
            // For each thread, choose the source and destination accounts based on the
            // index
            // Every even index will transfer from account1 to account2
            // Every odd index will transfer from account2 to account3
            Account source = i % 2 == 0 ? account1 : account2;
            Account destination = i % 2 == 0 ? account2 : account3;

            // Create a new TransferTask with the chosen source and destination accounts,
            // and an amount of 50
            // Each thread will execute this task to perform the transfer
            threads[i] = new Thread(new TransferTask(source, destination, 50));

            // Start the thread immediately
            threads[i].start();
        }

        // Wait for all threads to finish before proceeding to print the final balances
        // This ensures that all transfers are completed before displaying the results
        for (Thread thread : threads) {
            thread.join(); // This call ensures the main thread waits for each thread to finish
        }

        // Print the final balances of each account
        System.out.println("Final balances:");
        System.out.println("Account A1: " + account1.getBalance()); // Display the final balance of Account A1
        System.out.println("Account A2: " + account2.getBalance()); // Display the final balance of Account A2
        System.out.println("Account A3: " + account3.getBalance()); // Display the final balance of Account A3
    }

}