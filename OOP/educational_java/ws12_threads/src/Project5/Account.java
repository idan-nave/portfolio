import java.util.concurrent.locks.ReentrantLock;

// - **Project 5**: Multiple bank account transfers occurring concurrently with proper synchronization using `ReentrantLock`.

public class Account {
    private double balance;
    private String id;
    private ReentrantLock lock = new ReentrantLock();

    public Account(String id, double initialBalance) {
        this.id = id;
        this.balance = initialBalance;
    }

    public ReentrantLock getLock() {
        return lock;
    }

    public double getBalance() {
        return balance;
    }

    public String getId() {
        return id;
    }

    public void transfer(Account destination, double amount) {
        // Lock accounts in a consistent order (by id)
        Account first = this.id.compareTo(destination.getId()) < 0 ? this : destination;
        Account second = this.id.compareTo(destination.getId()) < 0 ? destination : this;

        first.getLock().lock();
        second.getLock().lock();

        try {
            if (this.balance >= amount) {
                this.balance -= amount;
                destination.balance += amount;
                System.out.println(Thread.currentThread().getName() + " transferred " + amount + " from " + this.id + " to " + destination.getId());
            }
        } finally {
            second.getLock().unlock();
            first.getLock().unlock();
        }
    }
}

// Summary:

//     What is locked?
//         The ReentrantLock objects associated with the first and second Account objects are locked.
//         The critical section that is protected by the locks is the balance modification logic (i.e., this.balance -= amount; and destination.balance += amount;).
//     Is it only the try block that’s protected?
//         The critical section inside the try block, where the actual money transfer occurs, is protected by the locks.
//         The locking itself occurs before the try block, but the actual operations on the account balances (which could lead to data inconsistency) are inside the try block.

// By locking the accounts in a consistent order and ensuring that only one thread can modify the balances of both accounts at the same time, the code avoids race conditions and ensures thread safety.