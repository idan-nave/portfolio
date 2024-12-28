package bank;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Bank implements Serializable {

    // Constant for the reserve requirement factorial, defining the multiple of
    // loans
    // that the bank must hold in reserves. This ensures the bank maintains
    // liquidity.
    private final double RESERVES_REQUIREMENT_FACTORIAL = 10;

    // List of accounts that the bank manages.
    private List<Account> accounts;

    // The current reserves of the bank. This represents the money the bank has
    // available.
    private double bankReserves;

    /**
     * Constructor to initialize a bank with its reserves and an empty list of
     * accounts.
     *
     * @param bankReserves The amount of money the bank has in reserves.
     */
    public Bank(double bankReserves) {
        this.accounts = new ArrayList<>();
        this.bankReserves = bankReserves;
    }

    /**
     * Method to issue a loan to an account. It checks if the bank has sufficient
     * reserves
     * and if the account meets all requirements for the loan.
     *
     * @param account    The account requesting the loan.
     * @param loanAmount The amount of the loan.
     * @return true if the loan is successfully issued, false otherwise.
     * @throws AccountingException if any error occurs while processing the loan.
     */
    public boolean issueLoan(Account account, double loanAmount) throws AccountingException {
        if (loanAmount <= 0) {
            try {
                // If loan amount is invalid (negative or zero), throw an exception
                AccountingException.InvalidWithdrawalAmountException(loanAmount);
            } catch (AccountingException e) {
                System.out.println(e.getMessage()); // Output the exception message
            }
            return false;
        }

        // Bank checks: Ensure that the total loans do not exceed the reserve
        // requirements
        double totalLoans = getTotalLoans();
        double reserveRequirement = totalLoans * RESERVES_REQUIREMENT_FACTORIAL;

        // Check if the bank has sufficient reserves to issue the loan
        if (bankReserves < reserveRequirement) {
            try {
                // If reserves are insufficient, throw an exception and return false
                AccountingException.InvalidLoanApprovalException(loanAmount);
            } catch (AccountingException e) {
                System.out.println(e.getMessage());
                return false;
            }
        }

        // Account checks: Ensure that the account is not frozen (inactive)
        if (account.isFrozen()) {
            try {
                // If the account is frozen, throw an exception
                AccountingException.InactiveAccountException(account.getAccountName());
            } catch (AccountingException e) {
                System.out.println(e.getMessage());
                return false;
            }
        }

        // Check if the account can take the loan (e.g., has sufficient credit, hasn't
        // exceeded loan limit)
        if (!account.canTakeLoan(loanAmount)) {
            try {
                // If the loan is disapproved, throw an exception
                AccountingException.LoanDisapprovedException(loanAmount);
            } catch (AccountingException e) {
                System.out.println(e.getMessage());
                return false;
            }
        }

        // If all checks pass, allow the loan to be granted:
        // - Deduct the loan amount from the bank's reserves
        // - Deposit the loan amount into the account
        // - Add the loan amount to the account's loan balance
        bankReserves -= loanAmount;
        account.deposit(loanAmount);
        account.addLoan(loanAmount);

        // After issuing the loan, check if the account should be frozen due to loan
        // limits
        try {
            account.freezeAccountIfNecessary();
        } catch (AccountingException e) {
            System.out.println(e.getMessage());
        }
        return true; // Loan successfully issued
    }

    /**
     * Method to calculate the total loans across all accounts managed by the bank.
     * This is the sum of all negative account balances (indicating a loan).
     *
     * @return The total amount of loans the bank has issued.
     */
    private double getTotalLoans() {
        double totalLoans = 0;
        // Iterate through all accounts and sum up the negative balances (loans)
        for (Account account : accounts) {
            if (account.getBalance() < 0) {
                totalLoans += Math.abs(account.getBalance()); // Add the absolute value of the negative balance
            }
        }
        return totalLoans; // Return the total loan amount
    }

    /**
     * Method to collect monthly commissions from all accounts and add them to the
     * bank's reserves.
     *
     * @param commissionRate The percentage rate for the monthly commission.
     */
    public void collectCommissions(double commissionRate) {
        double totalCollections = 0;

        // Iterate through all accounts and apply the commission
        for (Account account : accounts) {
            totalCollections += account.applyMonthlyCommission(commissionRate);
        }

        // Add the collected commission amount to the bank's reserves
        bankReserves += totalCollections;
    }

    /**
     * Method to add an account to the bank's list of managed accounts.
     *
     * @param account The account to be added to the bank's list.
     */
    public void addAccount(Account account) {
        accounts.add(account); // Add the provided account to the list of accounts
    }

    /**
     * Getter method to retrieve the list of all accounts managed by the bank.
     *
     * @return The list of accounts.
     */
    public List<Account> getAccounts() {
        return accounts; // Return the list of all accounts
    }

    // toString Method for Bank details
    @Override
    public String toString() {
        return "Bank Reserves: $" + bankReserves +
               ", Total Accounts Managed: " + accounts.size();
    }
}