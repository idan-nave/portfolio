package bank;

import java.util.ArrayList;
import java.util.List;

public class Client {
    // Instance variables to store the client's name and their list of accounts
    private String name;
    private List<Account> accounts;

    /**
     * Constructor to initialize the client with their name and an empty list of
     * accounts.
     *
     * @param name The name of the client.
     */
    public Client(String name) {
        this.name = name;
        this.accounts = new ArrayList<>(); // Initializing the list of accounts
    }

    /**
     * Method to add an account to the client's list of accounts.
     *
     * @param account The account to be added.
     */
    public void addAccount(Account account) {
        accounts.add(account); // Add the given account to the list of accounts
    }

    /**
     * Method to attempt taking a loan from the bank. It checks if the client has
     * any account
     * eligible for the loan, and if so, applies for the loan.
     *
     * @param bank       The bank from which the loan is being taken.
     * @param loanAmount The amount of the loan being requested.
     * @return true if the loan was successfully issued, false otherwise.
     */
    public boolean takeLoan(Bank bank, double loanAmount) {

        if (loanAmount <= 0) {
            try {
                // If withdrawal amount is invalid (negative or zero), throw an exception
                AccountingException.InvalidWithdrawalAmountException(loanAmount);
            } catch (AccountingException e) {
                System.out.println(e.getMessage()); // Output the exception message
            }
            return false; // Withdrawal failed
        }

        // Iterate through the list of accounts to find an account that can take the
        // loan
        for (Account account : accounts) {
            // Check if the account can take the specified loan amount
            if (account.canTakeLoan(loanAmount)) {
                try {
                    // Attempt to issue the loan from the bank
                    bank.issueLoan(account, loanAmount);
                    return true; // If successful, return true
                } catch (AccountingException e) {
                    // If an exception is thrown (e.g., loan disapproved, account frozen), print the
                    // message
                    System.out.println(e.getMessage());
                    return false; // If the loan failed, return false
                }
            }
        }
        // If no account is eligible for the loan, print a message and return false
        System.out.println("No accounts eligible for the loan.");
        return false;
    }

    /**
     * Getter method to retrieve the client's name.
     *
     * @return The name of the client.
     */
    public String getName() {
        return name; // Return the client's name
    }

    /**
     * Getter method to retrieve the list of accounts owned by the client.
     *
     * @return The list of accounts.
     */
    public List<Account> getAccounts() {
        return accounts; // Return the list of accounts
    }

    // toString Method for Client details
    @Override
    public String toString() {
        return "Client Name: " + name + ", Accounts: " + accounts.size();
    }
}
