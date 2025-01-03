import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        // Create two bank accounts
        BankAccount account1 = new BankAccount("Account-1", 5000);
        BankAccount account2 = new BankAccount("Account-2", 3000);

        // Create a thread pool
        ExecutorService executor = Executors.newFixedThreadPool(2);

        // Create and submit transfer tasks
        executor.submit(new TransferTask(account1, account2, 1000));
        executor.submit(new TransferTask(account2, account1, 500));

        // Shutdown the executor
        executor.shutdown();

        // Wait for all tasks to finish
        try {
            while (!executor.isTerminated()) {
                Thread.sleep(100);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Print final balances
        System.out.println("Final Balance of " + account1.getAccountName() + ": " + account1.getBalance());
        System.out.println("Final Balance of " + account2.getAccountName() + ": " + account2.getBalance());
    }
}
