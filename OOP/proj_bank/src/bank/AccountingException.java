package bank;

public class AccountingException extends Exception {

    // Constructor to accept a custom message
    public AccountingException(String message) {
        super(message);
    }

    // Insufficient funds exception (for withdrawals)
    public static void InsufficientFundsException(double withdrawAmount) throws AccountingException {
        throw new AccountingException("Insufficient funds for withdrawal of: " + withdrawAmount);
    }

    // Loan disapproval exception
    public static void LoanDisapprovedException(double loanAmount) throws AccountingException {
        throw new AccountingException("Loan of " + loanAmount + " was disapproved due to insufficient bank reserves or account status.");
    }

    // Inactive account exception (frozen account)
    public static void InactiveAccountException(String accountName) throws AccountingException {
        throw new AccountingException("Account " + accountName + " is frozen due to exceeding the loan limit of 10K.");
    }

    // Invalid loan approval exception (insufficient bank reserves)
    public static void InvalidLoanApprovalException(double loanAmount) throws AccountingException {
        throw new AccountingException("Loan of " + loanAmount + " could not be approved due to insufficient bank reserves.");
    }

    // Invalid deposit amount exception
    public static void InvalidDepositAmountException(double depositAmount) throws AccountingException {
        throw new AccountingException("Deposit amount must be positive, but got: " + depositAmount);
    }

    // Invalid withdrawal amount exception
    public static void InvalidWithdrawalAmountException(double withdrawAmount) throws AccountingException {
        throw new AccountingException("Withdrawal amount must be positive, but got: " + withdrawAmount);
    }

    // Exceeds loan limit exception
    public static void ExceedsLoanLimitException(double loanLimit) throws AccountingException {
        throw new AccountingException("Total loan limit exceeded. The limit is " + loanLimit);
    }
}
