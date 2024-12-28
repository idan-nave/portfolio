package bank;

/**
 * The Transactable interface defines the basic transaction operations for accounts,
 * specifically deposit and withdrawal methods.
 * Any class that implements this interface is expected to provide implementations
 * for depositing and withdrawing money from the account.
 */
public interface Transactable {

    /**
     * Method to deposit a certain amount of money into the account.
     * The implementing class should define the logic to handle deposits.
     * 
     * @param amount The amount of money to be deposited into the account.
     * @return true if the deposit was successful, false otherwise.
     */
    boolean deposit(double amount);

    /**
     * Method to withdraw a certain amount of money from the account.
     * The implementing class should define the logic to handle withdrawals.
     * If the withdrawal exceeds the available balance, an exception (AccountingException)
     * may be thrown.
     * 
     * @param amount The amount of money to be withdrawn from the account.
     * @return true if the withdrawal was successful, false otherwise.
     * @throws AccountingException if there are issues with the withdrawal (e.g., insufficient funds).
     */
    boolean withdraw(double amount) throws AccountingException;
}
