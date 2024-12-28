Here's a full README file for the banking system project:

---

# Banking System

## Overview

This is a console-based banking system implemented in Java. The system allows users to perform transactions such as depositing and withdrawing money, viewing account details, applying for loans, and applying monthly commissions. The bank also manages multiple accounts and reserves, and clients can take loans as long as they meet the necessary criteria.

### Features:
- **Deposits**: Users can deposit money into their accounts.
- **Withdrawals**: Users can withdraw money from their accounts, with checks for insufficient funds.
- **Loans**: Clients can apply for loans, but their total loan debt cannot exceed $10,000.
- **Account Management**: Users can view their account balances, loan details, and apply monthly commissions.
- **Bank Management**: The bank tracks reserves and loans, ensuring that reserves meet required thresholds.
- **Client Management**: A client can have multiple accounts, and the bank can process multiple clients.

---

## Table of Contents
1. [Installation](#installation)
2. [Usage](#usage)
3. [Classes Overview](#classes-overview)
4. [Features and Functions](#features-and-functions)
5. [Error Handling](#error-handling)
6. [License](#license)

---

## Installation

### Prerequisites:
- **Java**: This project requires Java to be installed on your machine. You can download Java from the [official website](https://www.oracle.com/java/technologies/javase-jdk11-downloads.html).
- **IDE**: You can use any Java IDE (like IntelliJ IDEA, Eclipse, or Visual Studio Code) or a simple text editor and command line to compile and run the program.

### Steps to Set Up:
1. Clone or download this repository to your local machine.
   ```bash
   git clone https://github.com/yourusername/banking-system.git
   ```

2. Navigate to the project directory and open it in your IDE or text editor.

3. Compile and run the `BankingApp` class from your IDE or use the following commands in your terminal:
   ```bash
   javac bank/*.java
   java bank.BankingApp
   ```

---

## Usage

1. Run the `BankingApp` class, and the console will prompt you with a menu to interact with the banking system.

2. The menu will show options to:
   - **Deposit**: Deposit money into an account.
   - **Withdraw**: Withdraw money from an account.
   - **Take Loan**: Request a loan from the bank.
   - **View Account Balance**: Display the current balance of an account.
   - **View Account Loan Details**: View the loan debt associated with an account.
   - **Apply Monthly Commission**: Apply a commission on all accounts.
   - **View Bank Details**: View the bank's current reserve status.
   - **View Client Details**: View details of a specific client.
   - **Exit**: Exit the application.

---

## Classes Overview

### 1. `Bank` Class
This class manages multiple accounts and maintains the bank's reserves. It provides functionality to issue loans, collect commissions, and keep track of bank reserves.

#### Key Functions:
- **issueLoan**: Issues a loan to a client’s account if conditions are met (e.g., sufficient reserves, valid loan amount).
- **collectCommissions**: Applies a monthly commission to all accounts managed by the bank.
- **addAccount**: Adds an account to the bank’s list of accounts.
- **getAccounts**: Returns a list of accounts managed by the bank.

### 2. `Client` Class
Represents a client with one or more bank accounts. It allows the client to take out loans and manage their accounts.

#### Key Functions:
- **addAccount**: Adds an account to the client's list of accounts.
- **takeLoan**: Allows the client to apply for a loan from the bank if eligible.

### 3. `Account` Class
Represents a bank account with basic operations such as deposit, withdrawal, and loan management. The account can be frozen if the loan debt exceeds $10,000.

#### Key Functions:
- **deposit**: Deposits a specified amount into the account.
- **withdraw**: Withdraws a specified amount from the account.
- **canTakeLoan**: Checks if the account is eligible to take a loan.
- **applyMonthlyCommission**: Applies a monthly commission to the account balance.
- **freezeAccountIfNecessary**: Freezes the account if the loan debt exceeds $10,000.

### 4. `Transactable` Interface
An interface implemented by the `Account` class to allow basic transaction functionality such as deposit and withdrawal.

### 5. `AccountingException` Class
Custom exception class that handles errors related to transactions, loans, and account status.

#### Key Functions:
- **InsufficientFundsException**: Throws an exception if a withdrawal exceeds the account balance.
- **LoanDisapprovedException**: Throws an exception if a loan cannot be approved.
- **InactiveAccountException**: Throws an exception if an account is frozen due to exceeding the loan limit.

### 6. `BankingApp` Class
The main application class where the user interacts with the banking system through the console interface. It includes a menu system and processes user inputs.

---

## Features and Functions

### 1. **Deposit and Withdraw**:
Users can deposit and withdraw money to/from their accounts. Deposits and withdrawals are validated to ensure no negative amounts are entered, and sufficient balance is available for withdrawals.

### 2. **Loan System**:
Users can request loans from the bank, but certain conditions must be met:
- The bank's reserves must exceed 10 times the total outstanding loans.
- The client’s account must not exceed a total loan debt of $10,000.
- If these conditions are not met, an exception is raised.

### 3. **Monthly Commissions**:
The bank applies a commission rate (e.g., 1%) on all accounts to simulate monthly account fees.

### 4. **Account Freeze**:
If an account's total loan debt exceeds $10,000, the account is frozen, and no further transactions can be performed.

### 5. **Client and Bank Overview**:
Users can view detailed information about their account balance, loan status, and even the bank's reserves and the client’s details.

---

## Error Handling

### `AccountingException`:
This class defines multiple custom exceptions to handle various errors:
- **InsufficientFundsException**: Raised if an account has insufficient funds for a withdrawal.
- **LoanDisapprovedException**: Raised if the loan amount exceeds bank reserves or if the client is ineligible.
- **InactiveAccountException**: Raised if an account is frozen due to a loan exceeding the limit of $10,000.
- **InvalidDepositAmountException**: Raised if an invalid (non-positive) deposit amount is entered.
- **InvalidWithdrawalAmountException**: Raised if an invalid (non-positive) withdrawal amount is entered.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Conclusion

The banking system project demonstrates basic banking operations such as managing accounts, handling loans, applying commissions, and tracking the bank's reserves. The system is designed to be extended, with room for adding more features such as interest rates, account types, etc.


