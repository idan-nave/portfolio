package bank;

import java.io.Serializable;

public class Account implements Transactable, Serializable {

    // that the bank must hold in reserves. This ensures the bank maintains
    // liquidity.
    private final double TOTAL_ACCOUNT_DEBT_ALLOWED = 1000;

    // Account properties
    private String accountName;  // Name associated with the account (e.g., holder's name or account ID)
    private double balance;      // The current balance in the account
    private boolean isFrozen;    // A flag to indicate if the account is frozen (inactive)
    private double totalLoanDebt;  // The total amount of loan debt that the account has

    /**
     * Constructor to initialize an account with a name and balance.
     * The account starts with an unfrozen status and no loan debt.
     *
     * @param accountName The name or identifier of the account.
     * @param balance The initial balance of the account.
     */
    public Account(String accountName, double balance) {
        this.accountName = accountName;
        this.balance = balance;
        this.isFrozen = false;  // Account is not frozen when it is created.
        this.totalLoanDebt = 0;  // No loans initially.
    }

    /**
     * Method to deposit an amount into the account.
     * 
     * @param amount The amount to deposit into the account.
     * @return true if deposit is successful, false otherwise.
     */
    @Override
    public boolean deposit(double amount) {
        if (amount <= 0) {
            try {
                // If deposit amount is invalid (negative or zero), throw an exception
                AccountingException.InvalidDepositAmountException(amount);
            } catch (AccountingException e) {
                System.out.println(e.getMessage());  // Output the exception message
            }
            return false;  // Deposit failed
        }

        balance += amount;  // Add the amount to the account's balance
        return true;  // Deposit was successful
    }

    /**
     * Method to withdraw an amount from the account.
     * 
     * @param amount The amount to withdraw from the account.
     * @return true if withdrawal is successful, false otherwise.
     */
    @Override
    public boolean withdraw(double amount) {
        if (amount <= 0) {
            try {
                // If withdrawal amount is invalid (negative or zero), throw an exception
                AccountingException.InvalidWithdrawalAmountException(amount);
            } catch (AccountingException e) {
                System.out.println(e.getMessage());  // Output the exception message
            }
            return false;  // Withdrawal failed
        }

        if (amount > balance) {
            try {
                // If withdrawal amount exceeds balance, throw an exception
                AccountingException.InsufficientFundsException(amount);
            } catch (AccountingException e) {
                System.out.println(e.getMessage());  // Output the exception message
            }
            return false;  // Withdrawal failed due to insufficient funds
        }

        balance -= amount;  // Deduct the withdrawal amount from the balance
        return true;  // Withdrawal was successful
    }

    /**
     * Method to freeze the account if necessary based on the loan debt.
     * If the total loan debt exceeds 10,000, the account is frozen.
     * 
     * @throws AccountingException if the account is frozen due to exceeding loan limit.
     */
    public void freezeAccountIfNecessary() throws AccountingException {
        // Check if the total loan debt exceeds the threshold
        if (totalLoanDebt > TOTAL_ACCOUNT_DEBT_ALLOWED) {
            isFrozen = true;  // Mark the account as frozen
            try {
                // Throw an exception indicating the account is frozen
                AccountingException.InactiveAccountException(accountName);
            } catch (AccountingException e) {
                System.out.println(e.getMessage());  // Output the exception message
            }
        }
    }

    /**
     * Method to apply a monthly commission to the account. The commission is deducted
     * from the account balance based on a specified commission rate.
     * 
     * @param commissionRate The percentage rate for the commission (e.g., 0.05 for 5%).
     * @return The amount collected as commission.
     */
    public double applyMonthlyCommission(double commissionRate) {
        // Calculate the commission based on the balance and commission rate
        double collected = balance * commissionRate;
        balance -= collected;  // Deduct the commission from the account balance
        return collected;  // Return the amount collected as commission
    }

    /**
     * Method to check if the account can take a loan. The account can take a loan if
     * the total balance (including the loan) doesn't exceed the maximum allowed loan debt of 10,000.
     * 
     * @param loanAmount The amount of the loan to check.
     * @return true if the loan can be taken, false otherwise.
     */
    public boolean canTakeLoan(double loanAmount) {
        // Check if the total balance including the loan would be at or above -10,000
        return (balance - loanAmount) >= -TOTAL_ACCOUNT_DEBT_ALLOWED;
    }

    /**
     * Getter method to check if the account is frozen.
     * 
     * @return true if the account is frozen, false otherwise.
     */
    public boolean isFrozen() {
        return this.isFrozen;  // Return the frozen status of the account
    }

    /**
     * Method to add loan debt to the account. This increases the total loan debt of the account.
     * 
     * @param loanAmount The amount of the loan to add to the account's total debt.
     */
    public void addLoan(double loanAmount) {
        totalLoanDebt += loanAmount;  // Add the loan amount to the total loan debt
    }

    /**
     * Getter method to retrieve the account name.
     * 
     * @return The name of the account.
     */
    public String getAccountName() {
        return accountName;  // Return the account name
    }

    /**
     * Getter method to retrieve the current balance of the account.
     * 
     * @return The balance of the account.
     */
    public double getBalance() {
        return balance;  // Return the account balance
    }

    // toString Method for Account details
    @Override
    public String toString() {
        return "Account Name: " + accountName +
               ", Balance: $" + balance +
               ", Loan Debt: $" + totalLoanDebt +
               ", Frozen: " + isFrozen;
    }
}

