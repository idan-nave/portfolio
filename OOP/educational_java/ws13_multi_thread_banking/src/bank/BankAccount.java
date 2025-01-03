import java.util.concurrent.locks.ReentrantLock;

public class BankAccount {
    private double balance;
    private boolean freezed;
    private final ReentrantLock lock;
    private final String accountName;

    public BankAccount(String accountName, double initialBalance) {
        this.accountName = accountName;
        this.balance = initialBalance;
        this.freezed = false;
        this.lock = new ReentrantLock();
    }

    public boolean deposit(double amount) {
        lock.lock();
        try {
            if (!this.freezed) {
                balance += amount;
                return true;
            }
            return false;
        } finally {
            lock.unlock();
        }
    }

    public boolean withdraw(double amount) {
        lock.lock();
        try {
            if (balance >= amount) {
                balance -= amount;
                return true;
            }
            return false;
        } finally {
            lock.unlock();
        }
    }

    public double getBalance() {
        return balance;
    }

    public String getAccountName() {
        return accountName;
    }
}
