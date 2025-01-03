public class TransferTask implements Runnable {
    private final BankAccount sourceAccount;
    private final BankAccount destinationAccount;
    private final double amount;

    public TransferTask(BankAccount sourceAccount, BankAccount destinationAccount, double amount) {
        this.sourceAccount = sourceAccount;
        this.destinationAccount = destinationAccount;
        this.amount = amount;
    }

    @Override
    public void run() {
        boolean successW = sourceAccount.withdraw(amount);
        if (successW) {
            boolean successD = destinationAccount.deposit(amount);
            if (successD) {
                System.out.println("Transfer of " + amount + " from " + sourceAccount.getAccountName() +
                        " to " + destinationAccount.getAccountName() + " was successful.");
            } else {
                System.out.println("Destination Account is freezed");
            }
        } else {
            System.out.println("Insufficient funds for transfer of " + amount);
        }
    }
}
